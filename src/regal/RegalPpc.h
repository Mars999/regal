/*
 Copyright (c) 2011 NVIDIA Corporation
 Copyright (c) 2011-2012 Cass Everitt
 Copyright (c) 2012 Scott Nations
 Copyright (c) 2012 Mathias Schott
 Copyright (c) 2012 Nigel Stewart
 All rights reserved.

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*

 Regal push / pop client attrib
 Scott Nations

 TODO:

   check vertex-array state against spec
   track dsa versions of routines
   are we handling all ARB version of routines
   what do do about deletebuffers
   journal changes

*/

#ifndef __REGAL_PPC_H__
#define __REGAL_PPC_H__

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include "RegalUtil.h"
#include "RegalPrivate.h"
#include "RegalEmu.h"

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

#define REGAL_PPC_MAX_CLIENT_ATTRIB_STACK_DEPTH 16
#define REGAL_PPC_MAX_VERTEX_ATTRIBS 16
#define REGAL_PPC_MAX_TEXTURE_COORDS 16


struct RegalPpc : public RegalEmu {

    struct ClientPixelStoreState {

        ClientPixelStoreState()
        : pixelPackBufferBinding( 0 )
        , pixelUnpackBufferBinding( 0 )
        , packSwapBytes( GL_FALSE )
        , packLsbFirst( GL_FALSE )
        , packRowLength( 0 )
        , packImageHeight( 0 )
        , packSkipRows( 0 )
        , packSkipPixels( 0 )
        , packSkipImages( 0 )
        , packAlignment( 4 )
        , unpackSwapBytes( GL_FALSE )
        , unpackLsbFirst( GL_FALSE )
        , unpackRowLength( 0 )
        , unpackImageHeight( 0 )
        , unpackSkipRows( 0 )
        , unpackSkipPixels( 0 )
        , unpackSkipImages( 0 )
        , unpackAlignment( 4 )
        {
        }

        void Restore(RegalContext * ctx)
        {
            RegalAssert( ctx );

            DispatchTable &tbl = ctx->dsp.emuTbl;

            tbl.glBindBuffer( GL_PIXEL_PACK_BUFFER, pixelPackBufferBinding );
            tbl.glBindBuffer( GL_PIXEL_UNPACK_BUFFER, pixelUnpackBufferBinding );

            tbl.glPixelStorei( GL_PACK_ALIGNMENT, packAlignment );
            tbl.glPixelStorei( GL_PACK_IMAGE_HEIGHT, packImageHeight );
            tbl.glPixelStorei( GL_PACK_LSB_FIRST, packLsbFirst );
            tbl.glPixelStorei( GL_PACK_ROW_LENGTH, packRowLength );
            tbl.glPixelStorei( GL_PACK_SKIP_IMAGES, packSkipImages );
            tbl.glPixelStorei( GL_PACK_SKIP_PIXELS, packSkipPixels );
            tbl.glPixelStorei( GL_PACK_SKIP_ROWS, packSkipRows );
            tbl.glPixelStorei( GL_PACK_SWAP_BYTES, packSwapBytes );
            tbl.glPixelStorei( GL_UNPACK_ALIGNMENT, unpackAlignment );
            tbl.glPixelStorei( GL_UNPACK_IMAGE_HEIGHT, unpackImageHeight );
            tbl.glPixelStorei( GL_UNPACK_LSB_FIRST, unpackLsbFirst );
            tbl.glPixelStorei( GL_UNPACK_ROW_LENGTH, unpackRowLength );
            tbl.glPixelStorei( GL_UNPACK_SKIP_IMAGES, unpackSkipImages );
            tbl.glPixelStorei( GL_UNPACK_SKIP_PIXELS, unpackSkipPixels );
            tbl.glPixelStorei( GL_UNPACK_SKIP_ROWS, unpackSkipRows );
            tbl.glPixelStorei( GL_UNPACK_SWAP_BYTES, unpackSwapBytes );
        }

        GLuint pixelPackBufferBinding;
        GLuint pixelUnpackBufferBinding;
        GLboolean packSwapBytes;
        GLboolean packLsbFirst;
        GLint packRowLength;
        GLint packImageHeight;
        GLint packSkipRows;
        GLint packSkipPixels;
        GLint packSkipImages;
        GLint packAlignment;
        GLboolean unpackSwapBytes;
        GLboolean unpackLsbFirst;
        GLint unpackRowLength;
        GLint unpackImageHeight;
        GLint unpackSkipRows;
        GLint unpackSkipPixels;
        GLint unpackSkipImages;
        GLint unpackAlignment;
    };

    struct VertexArrayState {

        VertexArrayState()
        {
            Init( GL_NONE );
        }

        VertexArrayState(GLenum _cap)
        {
            Init( _cap );
        }

        void Init(GLenum _cap)
        {
            cap = _cap;
            index = 0;
            enabled = GL_FALSE;
            buffer = 0;
            size = 4;
            type = GL_FLOAT;
            normalized = GL_FALSE;
            stride = 0;
            pointer = NULL;
            integer = GL_FALSE;
            divisor = 0;
        }

        void SetPointer( GLuint _buffer,
                         GLuint _index,
                         GLint _size,
                         GLenum _type,
                         GLboolean _normalized,
                         GLboolean _integer,
                         GLsizei _stride,
                         const GLvoid * _pointer )
        {
            buffer = _buffer;
            index = _index;
            size = _size;
            type = _type;
            normalized = _normalized;
            integer = integer;
            stride = _stride;
            pointer = _pointer;
        }

        void Restore(RegalContext * ctx)
        {
            RegalAssert( ctx );

            DispatchTable &tbl = ctx->dsp.emuTbl;

            tbl.glBindBuffer(GL_ARRAY_BUFFER, buffer);

            switch (cap)
            {
                case GL_NONE:
                    tbl.glVertexAttribDivisor(index, divisor);
                    tbl.glVertexAttribPointer(index, size, type, normalized,
                                              stride, pointer);
                    break;
                case GL_COLOR_ARRAY:
                    tbl.glColorPointer(size, type, stride, pointer);
                    break;
                case GL_EDGE_FLAG_ARRAY:
                    tbl.glEdgeFlagPointer(stride, pointer);
                    break;
                case GL_FOG_COORD_ARRAY:
                    tbl.glFogCoordPointer(type, stride, pointer);
                    break;
                case GL_INDEX_ARRAY:
                    tbl.glIndexPointer(type, stride, pointer);
                    break;
                case GL_NORMAL_ARRAY:
                    tbl.glNormalPointer(type, stride, pointer);
                    break;
                case GL_SECONDARY_COLOR_ARRAY:
                    tbl.glSecondaryColorPointer(size, type, stride, pointer);
                    break;
                case GL_TEXTURE_COORD_ARRAY:
                    tbl.glTexCoordPointer(size, type, stride, pointer);
                    break;
                case GL_VERTEX_ARRAY:
                    tbl.glVertexPointer(size, type, stride, pointer);
                    break;
                default:
                    RegalAssert( !"unhandled cap value" );
                    break;
            }

            if ( enabled == GL_TRUE ) {
                if ( cap == GL_NONE ) {
                    tbl.glEnableVertexAttribArray( index );
                } else {
                    tbl.glEnableClientState( cap );
                }
            } else {
                if ( cap == GL_NONE ) {
                    tbl.glDisableVertexAttribArray( index );
                } else {
                    tbl.glDisableClientState( cap );
                }
            }
        }

        GLenum cap;
        GLuint index;
        GLboolean enabled;
        GLint buffer;
        GLint size;
        GLenum type;
        GLboolean normalized;
        GLsizei stride;
        const GLvoid * pointer;
        GLboolean integer;
        GLint divisor;
    };

    struct ClientVertexArrayState {

        ClientVertexArrayState()
        : vertexBuffer( 0 )
        , indexBuffer( 0 )
        , vertexArrayObject( 0 )
        , clientActiveTexture( GL_TEXTURE0 )
        , primitiveRestart( GL_FALSE )
        , primitiveRestartIndex( 0 )
        , edgeFlagArrayState( GL_EDGE_FLAG_ARRAY )
        , indexArrayState( GL_INDEX_ARRAY )
        {
        }

        ClientVertexArrayState(const ClientVertexArrayState &rhs)
        : vertexBuffer( rhs.vertexBuffer )
        , indexBuffer( rhs.indexBuffer )
        , vertexArrayObject( rhs.vertexArrayObject )
        , clientActiveTexture( rhs.clientActiveTexture )
        , primitiveRestart( rhs.primitiveRestart )
        , primitiveRestartIndex( rhs.primitiveRestartIndex )
        , edgeFlagArrayState( rhs.edgeFlagArrayState )
        , indexArrayState( rhs.indexArrayState )
        {
            for (int ii=0; ii<REGAL_PPC_MAX_VERTEX_ATTRIBS; ii++) {
                genericArrayState[ii] = rhs.genericArrayState[ii];
            }
        }

        ClientVertexArrayState&
        operator= (const ClientVertexArrayState &rhs)
        {
            if (this == &rhs)
                return *this;

            vertexBuffer = rhs.vertexBuffer;
            indexBuffer = rhs.indexBuffer;
            vertexArrayObject = rhs.vertexArrayObject;
            clientActiveTexture = rhs.clientActiveTexture;
            primitiveRestart = rhs.primitiveRestart;
            primitiveRestartIndex = rhs.primitiveRestartIndex;
            edgeFlagArrayState = rhs.edgeFlagArrayState;
            indexArrayState = rhs.indexArrayState;

            for (int ii=0; ii<REGAL_PPC_MAX_VERTEX_ATTRIBS; ii++) {
                genericArrayState[ii] = rhs.genericArrayState[ii];
            }

            return *this;
        }

        void Restore(RegalContext * ctx)
        {
            RegalAssert( ctx );

            ctx->dsp.emuTbl.glClientActiveTexture( clientActiveTexture );

            ctx->dsp.emuTbl.glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );

            if ( primitiveRestart == GL_TRUE ) {
                ctx->dsp.emuTbl.glEnable( GL_PRIMITIVE_RESTART );
            } else {
                ctx->dsp.emuTbl.glDisable( GL_PRIMITIVE_RESTART );
            }
            ctx->dsp.emuTbl.glPrimitiveRestartIndex( primitiveRestartIndex );

            ctx->dsp.emuTbl.glBindVertexArray( vertexArrayObject );

            if (vertexArrayObject != 0) {

                LoadStateFromGL( ctx );

            } else {

                edgeFlagArrayState.Restore( ctx );
                indexArrayState.Restore( ctx );

                ctx->dsp.emuTbl.glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );

                for (int ii=0; ii<REGAL_PPC_MAX_VERTEX_ATTRIBS; ii++) {
                    genericArrayState[ii].Restore( ctx );
                }

                ctx->dsp.emuTbl.glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
            }
        }

        void LoadStateFromGL( RegalContext * ctx )
        {
            GLint bah = 0;
            GLvoid* bah2 = NULL;

            DispatchTable &tbl = ctx->dsp.emuTbl;

            for (int ii=0; ii<REGAL_PPC_MAX_VERTEX_ATTRIBS; ii++) {
                VertexArrayState &gas = genericArrayState[ii];
                tbl.glGetVertexAttribiv( ii, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &gas.buffer );
                tbl.glGetVertexAttribiv( ii, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &bah );
                gas.enabled = bah;
                tbl.glGetVertexAttribiv( ii, GL_VERTEX_ATTRIB_ARRAY_SIZE, &gas.size );
                tbl.glGetVertexAttribiv( ii, GL_VERTEX_ATTRIB_ARRAY_DIVISOR, &gas.divisor );
                tbl.glGetVertexAttribiv( ii, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &gas.stride );
                tbl.glGetVertexAttribiv( ii, GL_VERTEX_ATTRIB_ARRAY_TYPE, &bah );
                gas.type = bah;
                tbl.glGetVertexAttribiv( ii, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &bah );
                gas.normalized = bah;
                tbl.glGetVertexAttribiv( ii, GL_VERTEX_ATTRIB_ARRAY_INTEGER, &bah );
                gas.integer = bah;
                tbl.glGetVertexAttribPointerv( ii, GL_VERTEX_ATTRIB_ARRAY_POINTER, &bah2 );
                gas.pointer = bah2;
            }

            VertexArrayState &gas = indexArrayState;
            gas.enabled = tbl.glIsEnabled( GL_INDEX_ARRAY  );
            tbl.glGetIntegerv( GL_INDEX_ARRAY_TYPE, &bah );
            gas.type = bah;
            tbl.glGetIntegerv( GL_INDEX_ARRAY_STRIDE, &gas.stride );
            tbl.glGetPointerv( GL_INDEX_ARRAY_POINTER, &bah2 );
            gas.pointer = bah2;
            tbl.glGetIntegerv( GL_INDEX_ARRAY_BUFFER_BINDING, &gas.buffer );

            gas = edgeFlagArrayState;
            gas.enabled = tbl.glIsEnabled( GL_EDGE_FLAG_ARRAY );
            tbl.glGetIntegerv( GL_EDGE_FLAG_ARRAY_STRIDE, &gas.stride );
            tbl.glGetPointerv( GL_EDGE_FLAG_ARRAY_POINTER, &bah2 );
            gas.pointer = bah2;
            tbl.glGetIntegerv( GL_EDGE_FLAG_ARRAY_BUFFER_BINDING, &gas.buffer );

            tbl.glGetIntegerv( GL_ELEMENT_ARRAY_BUFFER_BINDING, &bah );
            indexBuffer = bah;
        }

        GLuint vertexBuffer;
        GLuint indexBuffer;
        GLuint vertexArrayObject;
        GLenum clientActiveTexture;
        GLboolean primitiveRestart;
        GLint primitiveRestartIndex;
        VertexArrayState edgeFlagArrayState;
        VertexArrayState indexArrayState;
        VertexArrayState genericArrayState[REGAL_PPC_MAX_VERTEX_ATTRIBS];
    };

    struct ClientState {

        ClientState()
        : pushPopMask( 0 )
        {
        }

        void Restore( RegalContext * ctx )
        {
            RegalAssert( ctx );

            switch ( pushPopMask )
            {
                case GL_CLIENT_ALL_ATTRIB_BITS:
                case GL_CLIENT_PIXEL_STORE_BIT:
                    pixelStoreState.Restore( ctx );
                    if ( pushPopMask == GL_CLIENT_PIXEL_STORE_BIT )
                        break;
                case GL_CLIENT_VERTEX_ARRAY_BIT:
                    vertexArrayState.Restore( ctx );
                    break;
                default:
                    RegalAssert( !"unhandled pushPopMask value" );
                    return;
            }
        }

        GLbitfield pushPopMask;
        ClientPixelStoreState  pixelStoreState;
        ClientVertexArrayState vertexArrayState;
    };

    bool insideBeginEnd;
    int topOfStack;
    ClientState stack[REGAL_PPC_MAX_CLIENT_ATTRIB_STACK_DEPTH];
    ClientState currentClientState;

    // to alias vertex arrays to generic attribs
    GLuint ffAttrMap[ REGAL_PPC_MAX_VERTEX_ATTRIBS ];
    GLuint ffAttrInvMap[ REGAL_PPC_MAX_VERTEX_ATTRIBS ];
    GLuint ffAttrTexBegin;
    GLuint ffAttrTexEnd;
    GLuint ffAttrNumTex;
    GLuint maxVertexAttribs;

    void Init( RegalContext * ctx )
    {
        insideBeginEnd = false;
        topOfStack = -1;

        maxVertexAttribs = ctx->ctxInf->maxVertexAttribs;

        // we have RFF2A maps for sets of 8 and 16 attributes. if
        // REGAL_PPC_MAX_VERTEX_ATTRIBS > 16 a new map needs to be added

        RegalAssert( REGAL_PPC_MAX_VERTEX_ATTRIBS <= 16 );

        if ( maxVertexAttribs >= 16 ) {
            RegalAssert( REGAL_PPC_MAX_VERTEX_ATTRIBS == 16);
            //RegalOutput( "Setting up for %d Vertex Attribs\n", maxVertexAttribs );
            for( int i = 0; i < 16; i++ ) {
                ffAttrMap[i] = RFF2AMap16[i];
                ffAttrInvMap[i] = RFF2AInvMap16[i];
            }
            ffAttrTexBegin = RFF2ATexBegin16;
            ffAttrTexEnd = RFF2ATexEnd16;
        } else {
            RegalAssert( maxVertexAttribs >= 8 );
            //RegalOutput( "Setting up for 8 Vertex Attribs" );
            for( int i = 0; i < 8; i++ ) {
                ffAttrMap[i] = RFF2AMap8[i];
                ffAttrInvMap[i] = RFF2AInvMap8[i];
            }
            for( int i = 8; i < REGAL_PPC_MAX_VERTEX_ATTRIBS; i++ ) {
                ffAttrMap[i] = -1;
                ffAttrInvMap[i] = -1;
            }
            ffAttrTexBegin = RFF2ATexBegin8;
            ffAttrTexEnd = RFF2ATexEnd8;
        }
        ffAttrNumTex = ffAttrTexEnd - ffAttrTexBegin;
    }

    GLuint ClientStateToAttribIndex( GLenum array )
    {
        switch ( array )
        {
            case GL_VERTEX_ARRAY:
                return ffAttrMap[ RFF2A_Vertex ];
            case GL_NORMAL_ARRAY:
                return ffAttrMap[ RFF2A_Normal ];
            case GL_COLOR_ARRAY:
                 return ffAttrMap[ RFF2A_Color ];
            case GL_SECONDARY_COLOR_ARRAY:
                return ffAttrMap[ RFF2A_SecondaryColor ];
            case GL_FOG_COORD_ARRAY:
                return ffAttrMap[ RFF2A_FogCoord ];
            case GL_TEXTURE_COORD_ARRAY:
                {
                    GLuint index = currentClientState.vertexArrayState.clientActiveTexture - GL_TEXTURE0;
                    RegalAssert(index >= 0);
                    RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);
                    if ( index < ffAttrNumTex )
                        return ffAttrTexBegin + index;
                }
                break;
            default:
                break;
        }
        return ~0;
    }

    VertexArrayState*
    ClientStateToAttribState( GLenum array )
    {
        VertexArrayState* pAS = NULL;
        switch ( array )
        {
            case GL_EDGE_FLAG_ARRAY:
                pAS = &currentClientState.vertexArrayState.edgeFlagArrayState;
                break;
            case GL_INDEX_ARRAY:
                pAS = &currentClientState.vertexArrayState.indexArrayState;
                break;
            case GL_NORMAL_ARRAY:
            case GL_FOG_COORD_ARRAY:
            case GL_COLOR_ARRAY:
            case GL_SECONDARY_COLOR_ARRAY:
            case GL_VERTEX_ARRAY:
            case GL_TEXTURE_COORD_ARRAY:
                {
                    const GLuint index = ClientStateToAttribIndex( array );
                    if ( index != GLuint(~0) )
                        pAS = &currentClientState.vertexArrayState.genericArrayState[index];
                }
                break;
            default:
                RegalAssert( !"unhandled state value" );
                break;
        }
        return pAS;
    }

    void Begin( RegalContext * ctx, GLenum mode )
    {
        if ( insideBeginEnd == false ) {
            insideBeginEnd = true;
        }
    }

    void End( RegalContext * ctx )
    {
        if ( insideBeginEnd == true ) {
            insideBeginEnd = false;
        }
    }

    void BindBuffer( RegalContext * ctx, GLenum target, GLuint buffer)
    {
        switch (target)
        {
            case GL_ARRAY_BUFFER:
                currentClientState.vertexArrayState.vertexBuffer = buffer;
                break;
            case GL_ELEMENT_ARRAY_BUFFER:
                currentClientState.vertexArrayState.indexBuffer = buffer;
                break;
            case GL_PIXEL_PACK_BUFFER_BINDING:
                currentClientState.pixelStoreState.pixelPackBufferBinding = buffer;
                break;
            case GL_PIXEL_UNPACK_BUFFER_BINDING:
                currentClientState.pixelStoreState.pixelUnpackBufferBinding = buffer;
                break;
            default:
                break;
        }
    }

    void DeleteBuffers( RegalContext * ctx, GLsizei n, const GLuint *buffers )
    {
        //<> hmmm... what to do here?
    }

    void BindVertexArray( RegalContext * ctx, GLuint array)
    {
        currentClientState.vertexArrayState.vertexArrayObject = array;
        ctx->dsp.emuTbl.glBindVertexArray( array );
        if ( array != 0 )
            currentClientState.vertexArrayState.LoadStateFromGL( ctx );
    }

    void DeleteVertexArrays( RegalContext * ctx, GLsizei n, const GLuint *arrays )
    {
        //<> hmmm... what to do here?
    }

    void ClientActiveTexture( RegalContext * ctx, GLenum _texture)
    {
        if ( insideBeginEnd == true )
            return;

        GLint index = _texture - GL_TEXTURE0;

        if (index >= 0 && index < REGAL_PPC_MAX_TEXTURE_COORDS)
            currentClientState.vertexArrayState.clientActiveTexture = _texture;
    }

    void InterleavedArrays( RegalContext * ctx, GLenum format,
                            GLsizei stride, const GLvoid *pointer)
    {
        if ( insideBeginEnd == true )
            return;

        //<> how can stride be invalid?
        //<> if ( stride is invalid )
            //<> return;

        switch ( format )
        {
            case GL_V2F:
            case GL_V3F:
            case GL_C4UB_V2F:
            case GL_C4UB_V3F:
            case GL_C3F_V3F:
            case GL_N3F_V3F:
            case GL_C4F_N3F_V3F:
            case GL_T2F_V3F:
            case GL_T4F_V4F:
            case GL_T2F_C4UB_V3F:
            case GL_T2F_C3F_V3F:
            case GL_T2F_N3F_V3F:
            case GL_T2F_C4F_N3F_V3F:
            case GL_T4F_C4F_N3F_V4F:
                break;
            default:
                RegalAssert( !"unhandled format value" );
                return;
        }

        GLsizei f = sizeof(GL_FLOAT);
        GLsizei c = 4 * sizeof(GL_UNSIGNED_BYTE);
        //<> need to round up c to the nearest multiple of f

        GLsizei pc = 0;
        GLsizei pn = 0;
        GLsizei pv = 0;
        GLsizei s  = 0;

        switch ( format )
        {
            case GL_V2F:
                pc = 0;
                pn = 0;
                pv = 0;
                s  = 2 * f;
                break;
            case GL_V3F:
                pc = 0;
                pn = 0;
                pv = 0;
                s  = 3 * f;
                break;
            case GL_C4UB_V2F:
                pc = 0;
                pn = 0;
                pv = c + 0;
                s  = c + 2 * f;
                break;
            case GL_C4UB_V3F:
                pc = 0;
                pn = 0;
                pv = c + 0;
                s  = c + 3 * f;
                break;
            case GL_C3F_V3F:
                pc = 0;
                pn = 0;
                pv = 3 * f;
                s  = 6 * f;
                break;
            case GL_N3F_V3F:
                pc = 0;
                pn = 0;
                pv = 3 * f;
                s  = 6 * f;
                break;
            case GL_C4F_N3F_V3F:
                pc = 0;
                pn = 4 * f;
                pv = 7 * f;
                s  = 10;
                break;
            case GL_T2F_V3F:
                pc = 0;
                pn = 0;
                pv = 2 * f;
                s  = 5 * f;
                break;
            case GL_T4F_V4F:
                pc = 0;
                pn = 0;
                pv = 4 * f;
                s  = 8 * f;
                break;
            case GL_T2F_C4UB_V3F:
                pc = 2 * f;
                pn = 0;
                pv = c + 2 * f;
                s  = c + 5 * f;
                break;
            case GL_T2F_C3F_V3F:
                pc = 2 * f;
                pn = 0;
                pv = 5 * f;
                s  = 8 * f;
                break;
            case GL_T2F_N3F_V3F:
                pc = 0;
                pn = 2 * f;
                pv = 5 * f;
                s  = 8 * f;
                break;
            case GL_T2F_C4F_N3F_V3F:
                pc = 2 * f;
                pn = 6 * f;
                pv = 9 * f;
                s  = 12 * f;
                break;
            case GL_T4F_C4F_N3F_V4F:
                pc = 4 * f;
                pn = 8 * f;
                pv = 11 * f;
                s  = 15 * f;
                break;
            default:
                RegalAssert( !"unhandled format value" );
                break;
        }

        GLubyte* pointerc = static_cast<GLubyte*>( const_cast<GLvoid *>(pointer) ) + pc;
        GLubyte* pointern = static_cast<GLubyte*>( const_cast<GLvoid *>(pointer) ) + pn;
        GLubyte* pointerv = static_cast<GLubyte*>( const_cast<GLvoid *>(pointer) ) + pv;

        if ( stride == 0 ) {
            stride = s;
        }

        ShadowEnableDisableClientState( ctx, GL_EDGE_FLAG_ARRAY, GL_FALSE );
        ShadowEnableDisableClientState( ctx, GL_INDEX_ARRAY, GL_FALSE );
        ShadowEnableDisableClientState( ctx, GL_SECONDARY_COLOR_ARRAY, GL_FALSE );
        ShadowEnableDisableClientState( ctx, GL_FOG_COORD_ARRAY, GL_FALSE );

        GLint size = 0;
        GLenum type = GL_FLOAT;

        switch ( format )
        {
            case GL_T2F_V3F:
            case GL_T4F_V4F:
            case GL_T2F_C4UB_V3F:
            case GL_T2F_C3F_V3F:
            case GL_T2F_N3F_V3F:
            case GL_T2F_C4F_N3F_V3F:
            case GL_T4F_C4F_N3F_V4F:
                size = ((format == GL_T4F_V4F) || (format == GL_T4F_C4F_N3F_V4F)) ? 4 : 2;
                ShadowEnableDisableClientState( ctx, GL_TEXTURE_COORD_ARRAY, GL_TRUE );
                TexCoordPointer(ctx, size, GL_FLOAT, stride, pointer);
                break;
            default:
                ShadowEnableDisableClientState( ctx, GL_TEXTURE_COORD_ARRAY, GL_FALSE );
                break;
        }

        switch ( format )
        {
            case GL_C4UB_V2F:
            case GL_C4UB_V3F:
            case GL_C3F_V3F:
            case GL_C4F_N3F_V3F:
            case GL_T2F_C4UB_V3F:
            case GL_T2F_C3F_V3F:
            case GL_T2F_C4F_N3F_V3F:
            case GL_T4F_C4F_N3F_V4F:
                size = ((format == GL_C3F_V3F) || (format == GL_T2F_C3F_V3F)) ? 3 : 4;
                ShadowEnableDisableClientState( ctx, GL_COLOR_ARRAY, GL_TRUE );
                ColorPointer(ctx, size, type, stride, pointerc);
                break;
            default:
                ShadowEnableDisableClientState( ctx, GL_COLOR_ARRAY, GL_FALSE );
                break;
        }

        switch ( format )
        {
            case GL_N3F_V3F:
            case GL_C4F_N3F_V3F:
            case GL_T2F_N3F_V3F:
            case GL_T2F_C4F_N3F_V3F:
            case GL_T4F_C4F_N3F_V4F:
                ShadowEnableDisableClientState( ctx, GL_NORMAL_ARRAY, GL_TRUE );
                NormalPointer(ctx, GL_FLOAT, stride, pointern);
                break;
            default:
                ShadowEnableDisableClientState( ctx, GL_NORMAL_ARRAY, GL_FALSE );
                break;
        }

        switch ( format )
        {
            case GL_V2F:
            case GL_C4UB_V2F:
                size = 2;
                break;
            case GL_V3F:
            case GL_C4UB_V3F:
            case GL_C3F_V3F:
            case GL_N3F_V3F:
            case GL_C4F_N3F_V3F:
            case GL_T2F_V3F:
            case GL_T2F_C4UB_V3F:
            case GL_T2F_C3F_V3F:
            case GL_T2F_N3F_V3F:
            case GL_T2F_C4F_N3F_V3F:
                size = 3;
                break;
            case GL_T4F_V4F:
            case GL_T4F_C4F_N3F_V4F:
                size = 4;
                break;
            default:
                RegalAssert( !"unhandled format value" );
                break;
        }

        ShadowEnableDisableClientState( ctx, GL_VERTEX_ARRAY, GL_TRUE );
        VertexPointer(ctx, size, GL_FLOAT, stride, pointerv);
    }

    template <typename T> void PixelStore( RegalContext * ctx, GLenum pname, T param )
    {
        if ( insideBeginEnd == true )
            return;

        switch (pname)
        {
            case GL_PACK_SWAP_BYTES:
                currentClientState.pixelStoreState.packSwapBytes =
                       (param ? GL_TRUE : GL_FALSE);
                return;

            case GL_PACK_LSB_FIRST:
                currentClientState.pixelStoreState.packLsbFirst =
                       (param ? GL_TRUE : GL_FALSE);
                return;

            case GL_PACK_ROW_LENGTH:
                if ( param >= 0 ) {
                    currentClientState.pixelStoreState.packRowLength =
                       static_cast<GLint>(param);
                }
                return;

            case GL_PACK_IMAGE_HEIGHT:
                if ( param >= 0 ) {
                   currentClientState.pixelStoreState.packImageHeight =
                       static_cast<GLint>(param);
                }
                return;

            case GL_PACK_SKIP_ROWS:
                if ( param >= 0 ) {
                   currentClientState.pixelStoreState.packSkipRows =
                       static_cast<GLint>(param);
                }
                return;

            case GL_PACK_SKIP_PIXELS:
                if ( param >= 0 ) {
                   currentClientState.pixelStoreState.packSkipPixels =
                       static_cast<GLint>(param);
                }
                return;

            case GL_PACK_SKIP_IMAGES:
                if ( param >= 0 ) {
                   currentClientState.pixelStoreState.packSkipImages =
                       static_cast<GLint>(param);
                }
                return;

            case GL_PACK_ALIGNMENT:
                if ( param == 1 || param == 2 || param == 4 || param == 8 ) {
                   currentClientState.pixelStoreState.packAlignment =
                       static_cast<GLint>(param);
                }
                return;

            case GL_UNPACK_SWAP_BYTES:
                currentClientState.pixelStoreState.unpackSwapBytes =
                       (param ? GL_TRUE : GL_FALSE);
                return;

            case GL_UNPACK_LSB_FIRST:
                currentClientState.pixelStoreState.unpackLsbFirst =
                       (param ? GL_TRUE : GL_FALSE);
                return;

            case GL_UNPACK_ROW_LENGTH:
                if ( param >= 0 ) {
                   currentClientState.pixelStoreState.unpackRowLength =
                       static_cast<GLint>(param);
                }
                return;

            case GL_UNPACK_IMAGE_HEIGHT:
                if ( param >= 0 ) {
                   currentClientState.pixelStoreState.unpackImageHeight =
                       static_cast<GLint>(param);
                }
                return;

            case GL_UNPACK_SKIP_ROWS:
                if ( param >= 0 ) {
                   currentClientState.pixelStoreState.unpackSkipRows =
                       static_cast<GLint>(param);
                }
                return;

            case GL_UNPACK_SKIP_PIXELS:
                if ( param >= 0 ) {
                   currentClientState.pixelStoreState.unpackSkipPixels =
                       static_cast<GLint>(param);
                }
                return;

            case GL_UNPACK_SKIP_IMAGES:
                if ( param >= 0 ) {
                   currentClientState.pixelStoreState.unpackSkipImages =
                       static_cast<GLint>(param);
                }
                return;

            case GL_UNPACK_ALIGNMENT:
                if ( param == 1 || param == 2 || param == 4 || param == 8 ) {
                   currentClientState.pixelStoreState.unpackAlignment =
                       static_cast<GLint>(param);
                }
                return;

            default:
                RegalAssert( !"unhandled pname value" );
                break;
        }
    }

    void ShadowEnableDisable( RegalContext * ctx, GLenum target, GLboolean enabled )
    {
        switch (target)
        {
            case GL_PRIMITIVE_RESTART:
                currentClientState.vertexArrayState.primitiveRestart = enabled;
                break;
            default:
                break;
        }
    }

    void Enable( RegalContext * ctx, GLenum target )
    {
        ShadowEnableDisable( ctx, target, GL_TRUE );
    }

    void Disable( RegalContext * ctx, GLenum target )
    {
        ShadowEnableDisable( ctx, target, GL_FALSE );
    }

    void ShadowEnableDisableClientState( RegalContext * ctx, GLenum array, GLboolean enabled )
    {
        VertexArrayState* pAS = ClientStateToAttribState( array );
        if (pAS)
            pAS->enabled = enabled;
    }

    void EnableClientState( RegalContext * ctx, GLenum array )
    {
        if ( insideBeginEnd == true )
            return;

        ShadowEnableDisableClientState( ctx, array, GL_TRUE );
    }

    void DisableClientState( RegalContext * ctx, GLenum array )
    {
        if ( insideBeginEnd == true )
            return;

        ShadowEnableDisableClientState( ctx, array, GL_FALSE );
    }

    void ShadowEnableDisableVertexAttribArray( RegalContext * ctx, GLuint index,
                                               GLboolean enabled )
    {
        if (index < REGAL_PPC_MAX_VERTEX_ATTRIBS)
            currentClientState.vertexArrayState.genericArrayState[index].enabled = enabled;
    }

    void EnableVertexAttribArray( RegalContext * ctx, GLenum cap )
    {
        ShadowEnableDisableVertexAttribArray( ctx, cap, GL_TRUE );
    }

    void DisableVertexAttribArray( RegalContext * ctx, GLenum cap )
    {
        ShadowEnableDisableVertexAttribArray( ctx, cap, GL_FALSE );
    }

    void ShadowVertexAttribPointer( RegalContext * ctx,
                                    GLuint _index,
                                    GLint _size,
                                    GLenum _type,
                                    GLboolean _normalized,
                                    GLboolean _integer,
                                    GLsizei _stride,
                                    const GLvoid * _pointer)
    {
        // do nothing for these various error conditions

        if ( insideBeginEnd == true )
            return;

        if (_index >= REGAL_PPC_MAX_VERTEX_ATTRIBS)
            return;

        switch (_size)
        {
            case 1:
            case 2:
            case 3:
            case 4:
                break;
            case GL_BGRA:
                switch (_type)
                {
                    case GL_UNSIGNED_BYTE:
                    case GL_INT_2_10_10_10_REV:
                    case GL_UNSIGNED_INT_2_10_10_10_REV:
                        break;
                    default:
                        return;
                }
                break;
            default:
                return;
        }

        switch (_type)
        {
            case GL_BYTE:
            case GL_UNSIGNED_BYTE:
            case GL_SHORT:
            case GL_UNSIGNED_SHORT:
            case GL_INT:
            case GL_UNSIGNED_INT:
            case GL_FLOAT:
            case GL_DOUBLE:
                break;
            case GL_INT_2_10_10_10_REV:
            case GL_UNSIGNED_INT_2_10_10_10_REV:
                if (_size != 4 && _size != GL_BGRA)
                    return;
                break;
            default:
                return;
        }

        if (_size == GL_BGRA && _normalized == GL_FALSE) {
            return;
        }

        if (_stride < 0) {
            return;
        }

        if ( ( currentClientState.vertexArrayState.vertexArrayObject != 0 ) &&
             ( currentClientState.vertexArrayState.vertexBuffer == 0 ) &&
             ( _pointer != NULL ) ) {
            return;
        }

        // otherwise shadow the generic vertex array state

        currentClientState.vertexArrayState.genericArrayState[_index].SetPointer(
             currentClientState.vertexArrayState.vertexBuffer,
             _index, _size, _type, _normalized, _integer, _stride, _pointer );
    }

    void VertexAttribPointer( RegalContext * ctx,
                              GLuint _index,
                              GLint _size,
                              GLenum _type,
                              GLboolean _normalized,
                              GLsizei _stride,
                              const GLvoid * _pointer)
    {
        ShadowVertexAttribPointer( ctx, _index, _size, _type, _normalized, GL_FALSE,
                                   _stride, _pointer );
    }

    void VertexAttribIPointer( RegalContext * ctx,
                               GLuint _index,
                               GLint _size,
                               GLenum _type,
                               GLsizei _stride,
                               const GLvoid * _pointer)
    {
        ShadowVertexAttribPointer( ctx, _index, _size, _type, GL_FALSE, GL_TRUE,
                                   _stride, _pointer );
    }


    void VertexAttribDivisor( RegalContext * ctx, GLuint index, GLint divisor )
    {
        if (index < REGAL_PPC_MAX_VERTEX_ATTRIBS)
            currentClientState.vertexArrayState.genericArrayState[index].divisor = divisor;
    }

    void PrimitiveRestartIndex( RegalContext * ctx, GLuint index )
    {
        if (index < REGAL_PPC_MAX_VERTEX_ATTRIBS)
            currentClientState.vertexArrayState.primitiveRestartIndex = index;
    }

    void ShadowVertexArrayPointer( RegalContext * ctx, GLenum array, GLint size,
                                 GLenum type, GLsizei stride, const GLvoid * pointer)
    {
        if ( ( currentClientState.vertexArrayState.vertexArrayObject != 0 ) &&
             ( currentClientState.vertexArrayState.vertexBuffer == 0 ) &&
             ( pointer != NULL ) ) {
            return;
        }

        VertexArrayState* pAS = ClientStateToAttribState( array );
        GLuint index = ClientStateToAttribIndex( array );

        if (pAS)
            pAS->SetPointer( currentClientState.vertexArrayState.vertexBuffer,
                             index, size, type, GL_TRUE, GL_FALSE, stride, pointer );

    }

    void ColorPointer(RegalContext * ctx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
    {
        if ( insideBeginEnd == true )
            return;

        switch (size)
        {
            case 3:
            case 4:
                break;
            default:
                return;
        }

        switch (type)
        {
            case GL_BYTE:
            case GL_UNSIGNED_BYTE:
            case GL_SHORT:
            case GL_UNSIGNED_SHORT:
            case GL_INT:
            case GL_UNSIGNED_INT:
            case GL_FLOAT:
            case GL_DOUBLE:
                break;
            default:
                return;
        }

        if (stride < 0)
            return;

        ShadowVertexArrayPointer(ctx, GL_COLOR_ARRAY, size, type, stride, pointer);
    }

    void SecondaryColorPointer(RegalContext * ctx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
    {
        if ( insideBeginEnd == true )
            return;

        if (size != 3)
            return;

        switch (type)
        {
            case GL_BYTE:
            case GL_UNSIGNED_BYTE:
            case GL_SHORT:
            case GL_UNSIGNED_SHORT:
            case GL_INT:
            case GL_UNSIGNED_INT:
            case GL_FLOAT:
            case GL_DOUBLE:
                break;
            default:
                return;
        }

        if (stride < 0)
            return;

        ShadowVertexArrayPointer(ctx, GL_SECONDARY_COLOR_ARRAY, size, type, stride, pointer);
    }

    void TexCoordPointer(RegalContext * ctx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
    {
        if ( insideBeginEnd == true )
            return;

        switch (size)
        {
            case 1:
            case 2:
            case 3:
            case 4:
                break;
            default:
                return;
        }

        switch (type)
        {
            case GL_SHORT:
            case GL_INT:
            case GL_FLOAT:
            case GL_DOUBLE:
                break;
            default:
                return;
        }

        if (stride < 0)
            return;

        ShadowVertexArrayPointer(ctx, GL_TEXTURE_COORD_ARRAY, size, type, stride, pointer);
    }

    void VertexPointer(RegalContext * ctx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
    {
        if ( insideBeginEnd == true )
            return;

        switch (size)
        {
            case 2:
            case 3:
            case 4:
                break;
            default:
                return;
        }

        switch (type)
        {
            case GL_SHORT:
            case GL_INT:
            case GL_FLOAT:
            case GL_DOUBLE:
                break;
            default:
                return;
        }

        if (stride < 0)
            return;

        ShadowVertexArrayPointer(ctx, GL_VERTEX_ARRAY, size, type, stride, pointer);
    }

    void IndexPointer(RegalContext * ctx, GLenum type, GLsizei stride, const GLvoid * pointer)
    {
        if ( insideBeginEnd == true )
            return;

        switch (type)
        {
            case GL_UNSIGNED_BYTE:
            case GL_SHORT:
            case GL_INT:
            case GL_FLOAT:
            case GL_DOUBLE:
                break;
            default:
                return;
        }

        if (stride < 0)
            return;

        ShadowVertexArrayPointer(ctx, GL_INDEX_ARRAY, 0, type, stride, pointer);
    }

    void NormalPointer(RegalContext * ctx, GLenum type, GLsizei stride, const GLvoid * pointer)
    {
        if ( insideBeginEnd == true )
            return;

        switch (type)
        {
            case GL_BYTE:
            case GL_SHORT:
            case GL_INT:
            case GL_FLOAT:
            case GL_DOUBLE:
                break;
            default:
                return;
        }

        if (stride < 0)
            return;

        ShadowVertexArrayPointer(ctx, GL_NORMAL_ARRAY, 0, type, stride, pointer);
    }

    void FogCoordPointer(RegalContext * ctx, GLenum type, GLsizei stride, const GLvoid * pointer)
    {
        if ( insideBeginEnd == true )
            return;

        switch (type)
        {
            case GL_FLOAT:
            case GL_DOUBLE:
                break;
            default:
                return;
        }

        if (stride < 0)
            return;

        ShadowVertexArrayPointer(ctx, GL_FOG_COORD_ARRAY, 0, type, stride, pointer);
    }

    void EdgeFlagPointer(RegalContext * ctx, GLsizei stride, const GLvoid * pointer)
    {
        if ( insideBeginEnd == true )
            return;

        if (stride < 0)
            return;

        ShadowVertexArrayPointer(ctx, GL_EDGE_FLAG_ARRAY, 0, GL_FLOAT, stride, pointer);
    }

    void PushClientAttrib( RegalContext * ctx, GLbitfield mask )
    {
        if ( insideBeginEnd == true )
            return;

        if (topOfStack >= REGAL_PPC_MAX_CLIENT_ATTRIB_STACK_DEPTH-1) {
            // GL_STACK_OVERFLOW. Don't do anything
            return;
        }

        switch (mask)
        {
            case GL_CLIENT_ALL_ATTRIB_BITS:
            case GL_CLIENT_VERTEX_ARRAY_BIT:
            case GL_CLIENT_PIXEL_STORE_BIT:
                break;
            default:
                RegalAssert( !"unhandled mask value" );
                return;
        }

        currentClientState.pushPopMask = mask;
        topOfStack++;
        RegalAssert( topOfStack < REGAL_PPC_MAX_CLIENT_ATTRIB_STACK_DEPTH );
        stack[topOfStack] = currentClientState;
    }

    void PopClientAttrib( RegalContext * ctx )
    {
        if ( insideBeginEnd == true )
            return;

        if (topOfStack < 0) {
            // GL_STACK_UNDERFLOW. Don't do anything
            return;
        }

        GLbitfield mask = stack[topOfStack].pushPopMask;

        switch ( mask )
        {
            case GL_CLIENT_PIXEL_STORE_BIT:
            case GL_CLIENT_VERTEX_ARRAY_BIT:
            case GL_CLIENT_ALL_ATTRIB_BITS:
                break;
            default:
                RegalAssert( !"unhandled mask value" );
                return;
        }

        RegalAssert( topOfStack >= -1);

        currentClientState = stack[topOfStack];
        topOfStack--;

        currentClientState.Restore( ctx );
    }

    template <typename T> bool Get( GLenum pname, T * params )
    {
        VertexArrayState* pAS = NULL;

        switch (pname)
        {
            case GL_PACK_SWAP_BYTES:
                *params = static_cast<T>(currentClientState.pixelStoreState.packSwapBytes );
                break;

            case GL_PACK_LSB_FIRST:
                *params = static_cast<T>(currentClientState.pixelStoreState.packLsbFirst );
                break;

            case GL_PACK_ROW_LENGTH:
                *params = static_cast<T>(currentClientState.pixelStoreState.packRowLength );
                break;

            case GL_PACK_IMAGE_HEIGHT:
                *params = static_cast<T>(currentClientState.pixelStoreState.packImageHeight );
                break;

            case GL_PACK_SKIP_ROWS:
                *params = static_cast<T>(currentClientState.pixelStoreState.packSkipRows );
                break;

            case GL_PACK_SKIP_PIXELS:
                *params = static_cast<T>(currentClientState.pixelStoreState.packSkipPixels );
                break;

            case GL_PACK_SKIP_IMAGES:
                *params = static_cast<T>(currentClientState.pixelStoreState.packSkipImages );
                break;

            case GL_PACK_ALIGNMENT:
                *params = static_cast<T>(currentClientState.pixelStoreState.packAlignment );
                break;

            case GL_UNPACK_SWAP_BYTES:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackSwapBytes );
                break;

            case GL_UNPACK_LSB_FIRST:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackLsbFirst );
                break;

            case GL_UNPACK_ROW_LENGTH:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackRowLength );
                break;

            case GL_UNPACK_IMAGE_HEIGHT:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackImageHeight );
                break;

            case GL_UNPACK_SKIP_ROWS:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackSkipRows );
                break;

            case GL_UNPACK_SKIP_PIXELS:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackSkipPixels );
                break;

            case GL_UNPACK_SKIP_IMAGES:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackSkipImages );
                break;

            case GL_UNPACK_ALIGNMENT:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackAlignment );
                break;

            case GL_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(currentClientState.vertexArrayState.vertexBuffer);
                break;

            case GL_ELEMENT_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(currentClientState.vertexArrayState.indexBuffer);
                break;

            case GL_PIXEL_PACK_BUFFER_BINDING:
                *params = static_cast<T>(currentClientState.pixelStoreState.pixelPackBufferBinding);
                break;

            case GL_PIXEL_UNPACK_BUFFER_BINDING:
                *params = static_cast<T>(currentClientState.pixelStoreState.pixelUnpackBufferBinding);
                break;

            case GL_ATTRIB_STACK_DEPTH:
                *params = static_cast<T>(topOfStack+1);
                break;

            case GL_MAX_VERTEX_ATTRIBS:
                *params = static_cast<T>(REGAL_PPC_MAX_VERTEX_ATTRIBS);
                break;

            case GL_MAX_CLIENT_ATTRIB_STACK_DEPTH:
                *params = static_cast<T>(REGAL_PPC_MAX_CLIENT_ATTRIB_STACK_DEPTH);
                break;

            case GL_MAX_TEXTURE_COORDS:
                *params = static_cast<T>(ffAttrNumTex);
                break;

            case GL_CLIENT_ACTIVE_TEXTURE:
                *params = static_cast<T>(currentClientState.vertexArrayState.clientActiveTexture);
                break;

            case GL_VERTEX_ARRAY_BUFFER_BINDING:
                pAS = ClientStateToAttribState( GL_VERTEX_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->buffer);
                break;

            case GL_COLOR_ARRAY_BUFFER_BINDING:
                pAS = ClientStateToAttribState( GL_COLOR_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->buffer);
                break;

            case GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING:
                pAS = ClientStateToAttribState( GL_SECONDARY_COLOR_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->buffer);
                break;

            case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:
                pAS = ClientStateToAttribState( GL_TEXTURE_COORD_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->buffer);
                break;

            case GL_FOG_COORD_ARRAY_BUFFER_BINDING:
                pAS = ClientStateToAttribState( GL_FOG_COORD_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->buffer);
                break;

            case GL_NORMAL_ARRAY_BUFFER_BINDING:
                pAS = ClientStateToAttribState( GL_NORMAL_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->buffer);
                break;

            case GL_INDEX_ARRAY_BUFFER_BINDING:
                pAS = ClientStateToAttribState( GL_INDEX_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->buffer);
                break;

            case GL_EDGE_FLAG_ARRAY_BUFFER_BINDING:
                pAS = ClientStateToAttribState( GL_EDGE_FLAG_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->buffer);
                break;

            case GL_COLOR_ARRAY_SIZE:
                pAS = ClientStateToAttribState( GL_COLOR_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->size);
                break;

            case GL_VERTEX_ARRAY_SIZE:
                pAS = ClientStateToAttribState( GL_VERTEX_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->size);
                break;

            case GL_SECONDARY_COLOR_ARRAY_SIZE:
                *params = static_cast<T>(3);
                break;

            case GL_TEXTURE_COORD_ARRAY_SIZE:
                pAS = ClientStateToAttribState( GL_TEXTURE_COORD_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->size);
                break;

            case GL_SECONDARY_COLOR_ARRAY_TYPE:
                pAS = ClientStateToAttribState( GL_SECONDARY_COLOR_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->type);
                break;

            case GL_COLOR_ARRAY_TYPE:
                pAS = ClientStateToAttribState( GL_COLOR_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->type);
                break;

            case GL_VERTEX_ARRAY_TYPE:
                pAS = ClientStateToAttribState( GL_VERTEX_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->type);
                break;

            case GL_TEXTURE_COORD_ARRAY_TYPE:
                pAS = ClientStateToAttribState( GL_TEXTURE_COORD_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->type);
                break;

            case GL_FOG_COORD_ARRAY_TYPE:
                pAS = ClientStateToAttribState( GL_FOG_COORD_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->type);
                break;

            case GL_NORMAL_ARRAY_TYPE:
                pAS = ClientStateToAttribState( GL_NORMAL_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->type);
                break;

            case GL_SECONDARY_COLOR_ARRAY_STRIDE:
                pAS = ClientStateToAttribState( GL_SECONDARY_COLOR_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->stride);
                break;

            case GL_COLOR_ARRAY_STRIDE:
                pAS = ClientStateToAttribState( GL_COLOR_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->stride);
                break;

            case GL_VERTEX_ARRAY_STRIDE:
                pAS = ClientStateToAttribState( GL_VERTEX_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->stride);
                break;

            case GL_FOG_COORD_ARRAY_STRIDE:
                pAS = ClientStateToAttribState( GL_FOG_COORD_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->stride);
                break;

            case GL_TEXTURE_COORD_ARRAY_STRIDE:
                pAS = ClientStateToAttribState( GL_TEXTURE_COORD_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->stride);
                break;

            case GL_NORMAL_ARRAY_STRIDE:
                pAS = ClientStateToAttribState( GL_NORMAL_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->stride);
                break;

            case GL_INDEX_ARRAY_TYPE:
                pAS = ClientStateToAttribState( GL_INDEX_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->type);
                break;

            case GL_INDEX_ARRAY_STRIDE:
                pAS = ClientStateToAttribState( GL_INDEX_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->stride);
                break;

            case GL_EDGE_FLAG_ARRAY_STRIDE:
                pAS = ClientStateToAttribState( GL_EDGE_FLAG_ARRAY );
                if (pAS)
                    *params = static_cast<T>(pAS->stride);
                break;

            case GL_PRIMITIVE_RESTART_INDEX:
                *params = static_cast<T>(currentClientState.vertexArrayState.primitiveRestartIndex);
                break;

            case GL_VERTEX_ARRAY_BINDING:
                *params = static_cast<T>(currentClientState.vertexArrayState.vertexArrayObject);
                break;

            default:
                return false;
        }
        return true;
    }

    template <typename T> bool GetIndexed( GLenum pname, GLuint index, T * params )
    {
        RegalAssert(index >= 0);
        RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);

        if ( index >= ffAttrNumTex )
            return false;

        index += ffAttrTexBegin;

        VertexArrayState* pAS =
             &currentClientState.vertexArrayState.genericArrayState[index];

        switch (pname)
        {
            case GL_TEXTURE_COORD_ARRAY_SIZE:
                *params = static_cast<T>(pAS->size);
                break;

            case GL_TEXTURE_COORD_ARRAY_TYPE:
                *params = static_cast<T>(pAS->type);
                break;

            case GL_TEXTURE_COORD_ARRAY_STRIDE:
                *params = static_cast<T>(pAS->stride);
                break;

            case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(pAS->buffer);
                break;

            default:
                return false;
        }
        return true;
    }

    bool IsEnabled( GLenum cap, GLboolean &enabled )
    {
        VertexArrayState* pAS = NULL;

        switch (cap)
        {
            case GL_PRIMITIVE_RESTART:
                enabled = currentClientState.vertexArrayState.primitiveRestart;
                break;

            case GL_EDGE_FLAG_ARRAY:
            case GL_NORMAL_ARRAY:
            case GL_INDEX_ARRAY:
            case GL_FOG_COORD_ARRAY:
            case GL_VERTEX_ARRAY:
            case GL_COLOR_ARRAY:
            case GL_SECONDARY_COLOR_ARRAY:
            case GL_TEXTURE_COORD_ARRAY:
                pAS = ClientStateToAttribState( cap );
                if ( pAS == NULL )
                    return false;
                enabled = pAS->enabled;
                break;

            default:
                return false;
        }
        return true;
    }

    bool IsEnabledIndexed( GLenum array, GLuint index, GLboolean &enabled )
    {
        switch ( array )
        {
            case GL_TEXTURE_COORD_ARRAY:
                RegalAssert(index >= 0);
                RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);
                if ( index >= ffAttrNumTex )
                    return false;
                index += ffAttrTexBegin;
                enabled = currentClientState.vertexArrayState.genericArrayState[index].enabled;
                break;

            default:
                return false;
        }
        return true;
    }

    bool GetPointerv( GLenum pname, GLvoid ** params)
    {
        VertexArrayState* pAS = NULL;

        switch (pname)
        {
            case GL_EDGE_FLAG_ARRAY_POINTER:
                pAS = ClientStateToAttribState( GL_EDGE_FLAG_ARRAY );
                break;

            case GL_INDEX_ARRAY_POINTER:
                pAS = ClientStateToAttribState( GL_INDEX_ARRAY );
                break;

            case GL_NORMAL_ARRAY_POINTER:
                pAS = ClientStateToAttribState( GL_NORMAL_ARRAY );
                break;

            case GL_FOG_COORD_ARRAY_POINTER:
                pAS = ClientStateToAttribState( GL_FOG_COORD_ARRAY );
                break;

            case GL_VERTEX_ARRAY_POINTER:
                pAS = ClientStateToAttribState( GL_VERTEX_ARRAY );
                break;

            case GL_COLOR_ARRAY_POINTER:
                pAS = ClientStateToAttribState( GL_COLOR_ARRAY );
                break;

            case GL_SECONDARY_COLOR_ARRAY_POINTER:
                pAS = ClientStateToAttribState( GL_SECONDARY_COLOR_ARRAY );
                break;

            case GL_TEXTURE_COORD_ARRAY_POINTER:
                pAS = ClientStateToAttribState( GL_TEXTURE_COORD_ARRAY );
                break;

            default:
                return false;
        }

        if ( pAS == NULL )
            return false;

        *params = const_cast<GLvoid *>(pAS->pointer);
        return true;
    }

    bool GetVertexAttribPointerv( GLuint index, GLenum pname, GLvoid ** pointer)
    {
        if ( ( pname == GL_VERTEX_ATTRIB_ARRAY_POINTER ) &&
                 ( index < REGAL_PPC_MAX_VERTEX_ATTRIBS ) ) {
            *pointer = const_cast<GLvoid *>(currentClientState.vertexArrayState.genericArrayState[index].pointer);
            return true;
        }
        return false;
    }

    template <typename T> bool GetVertexAttribv( GLuint index, GLenum pname, T * params )
    {
        if ( index >= REGAL_PPC_MAX_VERTEX_ATTRIBS )
            return false;

        if ( index == 0 && pname == GL_CURRENT_VERTEX_ATTRIB)
            return false;

        VertexArrayState &gas = currentClientState.vertexArrayState.genericArrayState[index];

        switch (pname)
        {
            case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(gas.buffer);
                break;

            case GL_VERTEX_ATTRIB_ARRAY_ENABLED:
                *params = static_cast<T>(gas.enabled);
                break;

            case GL_VERTEX_ATTRIB_ARRAY_SIZE:
                *params = static_cast<T>(gas.size);
                break;

            case GL_VERTEX_ATTRIB_ARRAY_DIVISOR:
                *params = static_cast<T>(gas.divisor);
                break;

            case GL_VERTEX_ATTRIB_ARRAY_STRIDE:
                *params = static_cast<T>(gas.stride);
                break;

            case GL_VERTEX_ATTRIB_ARRAY_TYPE:
                *params = static_cast<T>(gas.type);
                break;

            case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:
                *params = static_cast<T>(gas.normalized);
                break;

            case GL_VERTEX_ATTRIB_ARRAY_INTEGER:
                *params = static_cast<T>(gas.integer);
                break;

            default:
                return false;
        }
        return true;
    }
};

REGAL_NAMESPACE_END

#endif // ! __REGAL_PPC_H__
