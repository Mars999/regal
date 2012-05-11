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

   complete state & routines using spec
   track dsa versions of routines
   are we handling all ARB version of routines
   alias vertex arrays
   what do do about deletebuffers
   additional extensions
    - support for element routines from ARB_element_array
   journal changes

*/

#if ! __REGAL_PPC_H__
#define __REGAL_PPC_H__ 1

#include "RegalPrivate.h"
#include "RegalEmu.h"


#define REGAL_PPC_MAX_CLIENT_ATTRIB_STACK_DEPTH 16
#define REGAL_PPC_MAX_VERTEX_ATTRIBS 16
#define REGAL_PPC_MAX_TEXTURE_COORDS 8


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

            RegalDispatchTable &tbl = ctx->dsp.emuTbl;

            tbl.glBindBuffer( GL_PIXEL_PACK_BUFFER_BINDING, pixelPackBufferBinding );

            tbl.glBindBuffer( GL_PIXEL_UNPACK_BUFFER_BINDING, pixelUnpackBufferBinding );

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

    struct ClientArrayState {

        ClientArrayState()
        {
            Init( GL_NONE );
        }

        ClientArrayState(GLenum _cap)
        {
            Init( _cap );
        }

        void Init(GLenum _cap)
        {
            cap = _cap;
            enabled = GL_FALSE;
            integer = GL_FALSE;
            bufferBinding = 0;
            index = 0;
            type = GL_FLOAT;
            normalized = GL_FALSE;
            integer = GL_FALSE;
            stride = 0;
            pointer = NULL;
            size = ( cap == GL_SECONDARY_COLOR_ARRAY ) ? 3 : 4;
            divisor = 0;
        }

        ClientArrayState&
        operator= (const ClientArrayState &rhs)
        {
            if (this == &rhs)
                return *this;

            cap           = rhs.cap;
            enabled       = rhs.enabled;
            integer       = rhs.integer;
            bufferBinding = rhs.bufferBinding;
            index         = rhs.index;
            size          = rhs.size;
            divisor       = rhs.divisor;
            type          = rhs.type;
            normalized    = rhs.normalized;
            integer       = rhs.integer;
            stride        = rhs.stride;
            pointer       = rhs.pointer;

            return *this;
        }

        void SetPointer( GLuint _bufferBinding,
                         GLuint _index,
                         GLint _size,
                         GLenum _type,
                         GLboolean _normalized,
                         GLboolean _integer,
                         GLsizei _stride,
                         const GLvoid * _pointer )
        {
            bufferBinding = _bufferBinding;
            index         = _index;
            size          = _size;
            type          = _type;
            normalized    = _normalized;
            integer       = integer;
            stride        = _stride;
            pointer       = _pointer;
        }

        void Restore(RegalContext * ctx)
        {
            RegalAssert( ctx );

            RegalDispatchTable &tbl = ctx->dsp.emuTbl;

            switch (cap)
            {
                tbl.glBindBuffer(GL_ARRAY_BUFFER, bufferBinding);
                tbl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBufferBinding);

                tbl.glVertexAttribDivisor(index, divisor);

                case GL_NONE:
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
                tbl.glEnableClientState( cap );
            } else {
                tbl.glDisableClientState( cap );
            }
        }

        GLenum cap;
        GLboolean enabled;
        GLboolean normalized;
        GLboolean integer;
        GLint bufferBinding;
        GLint elementArrayBufferBinding;
        GLuint index;
        GLint size;
        GLint divisor;
        GLenum type;
        GLsizei stride;
        const GLvoid * pointer;
    };

    struct ClientVertexArrayState {

        ClientVertexArrayState()
        : arrayBufferBinding( 0 )
        , elementArrayBufferBinding( 0 )
        , vertexArrayBinding( 0 )
        , clientActiveTexture( GL_TEXTURE0 )
        , primitiveRestart( GL_FALSE )
        , primitiveRestartIndex( 0 )
        , colorArrayState( GL_COLOR_ARRAY )
        , edgeFlagArrayState( GL_EDGE_FLAG_ARRAY )
        , fogCoordArrayState( GL_FOG_COORD_ARRAY )
        , indexArrayState( GL_INDEX_ARRAY )
        , normalArrayState( GL_NORMAL_ARRAY )
        , secondaryColorArrayState( GL_SECONDARY_COLOR_ARRAY )
        , vertexArrayState( GL_VERTEX_ARRAY )
        {
            for (int ii=0; ii<REGAL_PPC_MAX_TEXTURE_COORDS; ii++) {
                textureCoordArrayState[ii].cap = GL_TEXTURE_COORD_ARRAY;
            }
        }

        ClientVertexArrayState(const ClientVertexArrayState &rhs)
        : arrayBufferBinding( rhs.arrayBufferBinding )
        , elementArrayBufferBinding( rhs.elementArrayBufferBinding )
        , vertexArrayBinding( rhs.vertexArrayBinding )
        , clientActiveTexture( rhs.clientActiveTexture )
        , primitiveRestart( rhs.primitiveRestart )
        , primitiveRestartIndex( rhs.primitiveRestartIndex )
        , colorArrayState( rhs.colorArrayState )
        , edgeFlagArrayState( rhs.edgeFlagArrayState )
        , fogCoordArrayState( rhs.fogCoordArrayState )
        , indexArrayState( rhs.indexArrayState )
        , normalArrayState( rhs.normalArrayState )
        , secondaryColorArrayState( rhs.secondaryColorArrayState )
        , vertexArrayState( rhs.vertexArrayState )
        {
            for (int ii=0; ii<REGAL_PPC_MAX_TEXTURE_COORDS; ii++) {
                textureCoordArrayState[ii] = rhs.textureCoordArrayState[ii];
            }
            for (int ii=0; ii<REGAL_PPC_MAX_VERTEX_ATTRIBS; ii++) {
                genericArrayState[ii] = rhs.genericArrayState[ii];
            }
        }

        ClientVertexArrayState&
        operator= (const ClientVertexArrayState &rhs)
        {
            if (this == &rhs)
                return *this;

            arrayBufferBinding        = rhs.arrayBufferBinding;
            elementArrayBufferBinding = rhs.elementArrayBufferBinding;
            vertexArrayBinding        = rhs.vertexArrayBinding;
            clientActiveTexture       = rhs.clientActiveTexture;
            primitiveRestart          = rhs.primitiveRestart;
            primitiveRestartIndex     = rhs.primitiveRestartIndex;
            colorArrayState           = rhs.colorArrayState;
            edgeFlagArrayState        = rhs.edgeFlagArrayState;
            fogCoordArrayState        = rhs.fogCoordArrayState;
            indexArrayState           = rhs.indexArrayState;
            normalArrayState          = rhs.normalArrayState;
            secondaryColorArrayState  = rhs.secondaryColorArrayState;
            vertexArrayState          = rhs.vertexArrayState;

            for (int ii=0; ii<REGAL_PPC_MAX_TEXTURE_COORDS; ii++) {
                textureCoordArrayState[ii] = rhs.textureCoordArrayState[ii];
            }

            for (int ii=0; ii<REGAL_PPC_MAX_VERTEX_ATTRIBS; ii++) {
                genericArrayState[ii] = rhs.genericArrayState[ii];
            }

            return *this;
        }

        void Restore(RegalContext * ctx)
        {
            RegalAssert( ctx );

            colorArrayState.Restore( ctx );
            edgeFlagArrayState.Restore( ctx );
            fogCoordArrayState.Restore( ctx );
            indexArrayState.Restore( ctx );
            normalArrayState.Restore( ctx );
            secondaryColorArrayState.Restore( ctx );
            vertexArrayState.Restore( ctx );

            for (int ii=0; ii<REGAL_PPC_MAX_TEXTURE_COORDS; ii++) {
                textureCoordArrayState[ii].Restore( ctx );
            }

            for (int ii=0; ii<REGAL_PPC_MAX_VERTEX_ATTRIBS; ii++) {
                genericArrayState[ii].Restore( ctx );
            }

            ctx->dsp.emuTbl.glClientActiveTexture( clientActiveTexture );

            if ( primitiveRestart == GL_TRUE ) {
                ctx->dsp.emuTbl.glEnable( GL_PRIMITIVE_RESTART );
            } else {
                ctx->dsp.emuTbl.glDisable( GL_PRIMITIVE_RESTART );
            }

            ctx->dsp.emuTbl.glPrimitiveRestartIndex( primitiveRestartIndex );

            ctx->dsp.emuTbl.glBindBuffer( GL_ARRAY_BUFFER, arrayBufferBinding );

            ctx->dsp.emuTbl.glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, elementArrayBufferBinding );

            ctx->dsp.emuTbl.glBindVertexArray( vertexArrayBinding );
        }

        GLuint arrayBufferBinding;
        GLuint elementArrayBufferBinding;
        GLuint vertexArrayBinding;
        GLenum clientActiveTexture;
        GLboolean primitiveRestart;
        GLint primitiveRestartIndex;
        ClientArrayState colorArrayState;
        ClientArrayState edgeFlagArrayState;
        ClientArrayState fogCoordArrayState;
        ClientArrayState indexArrayState;
        ClientArrayState normalArrayState;
        ClientArrayState secondaryColorArrayState;
        ClientArrayState vertexArrayState;
        ClientArrayState textureCoordArrayState[REGAL_PPC_MAX_TEXTURE_COORDS];
        ClientArrayState genericArrayState[REGAL_PPC_MAX_VERTEX_ATTRIBS];
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

    int topOfStack;
    ClientState stack[REGAL_PPC_MAX_CLIENT_ATTRIB_STACK_DEPTH];
    ClientState currentClientState;

    void Init( RegalContext * ctx )
    {
        topOfStack = -1;
    }

    void BindBuffer( RegalContext * ctx, GLenum target, GLuint buffer)
    {
        switch (target)
        {
            case GL_ARRAY_BUFFER:
                currentClientState.vertexArrayState.arrayBufferBinding = buffer;
                break;
            case GL_ELEMENT_ARRAY_BUFFER:
                currentClientState.vertexArrayState.elementArrayBufferBinding = buffer;
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
        currentClientState.vertexArrayState.vertexArrayBinding = array;
    }

    void DeleteVertexArrays( RegalContext * ctx, GLsizei n, const GLuint *arrays )
    {
        //<> hmmm... what to do here?
    }

    void ClientActiveTexture( RegalContext * ctx, GLenum _texture)
    {
        GLint index = _texture - GL_TEXTURE0;

        if (index >= 0 && index < REGAL_PPC_MAX_TEXTURE_COORDS)
            currentClientState.vertexArrayState.clientActiveTexture = _texture;
    }

    template <typename T> void PixelStore( RegalContext * ctx, GLenum pname, T param )
    {
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

    void ShadowEnableDisableClientState( RegalContext * ctx, GLenum cap,
                                         GLboolean enabled )
    {
        ClientArrayState* pAS = NULL;
        switch (cap)
        {
            case GL_COLOR_ARRAY:
                pAS = &currentClientState.vertexArrayState.colorArrayState;
                break;
            case GL_EDGE_FLAG_ARRAY:
                pAS = &currentClientState.vertexArrayState.edgeFlagArrayState;
                break;
            case GL_FOG_COORD_ARRAY:
                pAS = &currentClientState.vertexArrayState.fogCoordArrayState;
                break;
            case GL_INDEX_ARRAY:
                pAS = &currentClientState.vertexArrayState.indexArrayState;
                break;
            case GL_NORMAL_ARRAY:
                pAS = &currentClientState.vertexArrayState.normalArrayState;
                break;
            case GL_SECONDARY_COLOR_ARRAY:
                pAS = &currentClientState.vertexArrayState.secondaryColorArrayState;
                break;
            case GL_TEXTURE_COORD_ARRAY:
                {
                    GLuint index = currentClientState.vertexArrayState.clientActiveTexture - GL_TEXTURE0;
                    RegalAssert(index >= 0);
                    RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);
                    pAS = &currentClientState.vertexArrayState.textureCoordArrayState[index];
                }
                break;
            case GL_VERTEX_ARRAY:
                pAS = &currentClientState.vertexArrayState.vertexArrayState;
                break;
            default: 
                RegalAssert( !"unhandled cap value" );
                break;
        }

        if (pAS)
            pAS->enabled = enabled;

    }

    void EnableClientState( RegalContext * ctx, GLenum cap )
    {
        ShadowEnableDisableClientState( ctx, cap, GL_TRUE );
    }

    void DisableClientState( RegalContext * ctx, GLenum cap )
    {
        ShadowEnableDisableClientState( ctx, cap, GL_FALSE );
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

        // otherwise shadow the generic vertex array state

        currentClientState.vertexArrayState.genericArrayState[_index].SetPointer(
             currentClientState.vertexArrayState.arrayBufferBinding,
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

    void ShadowClientArrayState( RegalContext * ctx, GLenum cap, GLint size, GLenum type,
                                 GLsizei stride, const GLvoid * pointer)
    {
        ClientArrayState* pAS = NULL;
        switch (cap)
        {
            case GL_COLOR_ARRAY:
                pAS = &currentClientState.vertexArrayState.colorArrayState;
                break;
            case GL_EDGE_FLAG_ARRAY:
                pAS = &currentClientState.vertexArrayState.edgeFlagArrayState;
                break;
            case GL_FOG_COORD_ARRAY:
                pAS = &currentClientState.vertexArrayState.fogCoordArrayState;
                break;
            case GL_INDEX_ARRAY:
                pAS = &currentClientState.vertexArrayState.indexArrayState;
                break;
            case GL_NORMAL_ARRAY:
                pAS = &currentClientState.vertexArrayState.normalArrayState;
                break;
            case GL_SECONDARY_COLOR_ARRAY:
                pAS = &currentClientState.vertexArrayState.secondaryColorArrayState;
                break;
            case GL_TEXTURE_COORD_ARRAY:
                {
                    GLuint index = currentClientState.vertexArrayState.clientActiveTexture - GL_TEXTURE0;
                    RegalAssert(index >= 0);
                    RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);
                    pAS = &currentClientState.vertexArrayState.textureCoordArrayState[index];
                }
                break;
            case GL_VERTEX_ARRAY:
                pAS = &currentClientState.vertexArrayState.vertexArrayState;
                break;
            default: 
                RegalAssert( !"unhandled cap value" );
                break;
        }

        if (pAS)
            pAS->SetPointer( 0, 0, size, type, GL_TRUE, GL_FALSE, stride, pointer );

    }

    void ColorPointer(RegalContext * ctx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
    {
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

        ShadowClientArrayState(ctx, GL_COLOR_ARRAY, size, type, stride, pointer);
    }

    void SecondaryColorPointer(RegalContext * ctx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
    {
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

        ShadowClientArrayState(ctx, GL_SECONDARY_COLOR_ARRAY, size, type, stride, pointer);
    }

    void TexCoordPointer(RegalContext * ctx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
    {
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

        ShadowClientArrayState(ctx, GL_TEXTURE_COORD_ARRAY, size, type, stride, pointer);
    }

    void VertexPointer(RegalContext * ctx, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
    {
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

        ShadowClientArrayState(ctx, GL_VERTEX_ARRAY, size, type, stride, pointer);
    }

    void IndexPointer(RegalContext * ctx, GLenum type, GLsizei stride, const GLvoid * pointer)
    {
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

        ShadowClientArrayState(ctx, GL_INDEX_ARRAY, 0, type, stride, pointer);
    }

    void NormalPointer(RegalContext * ctx, GLenum type, GLsizei stride, const GLvoid * pointer)
    {
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

        ShadowClientArrayState(ctx, GL_NORMAL_ARRAY, 0, type, stride, pointer);
    }

    void FogCoordPointer(RegalContext * ctx, GLenum type, GLsizei stride, const GLvoid * pointer)
    {
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

        ShadowClientArrayState(ctx, GL_FOG_COORD_ARRAY, 0, type, stride, pointer);
    }

    void EdgeFlagPointer(RegalContext * ctx, GLsizei stride, const GLvoid * pointer)
    {
        if (stride < 0)
            return;

        ShadowClientArrayState(ctx, GL_EDGE_FLAG_ARRAY, 0, GL_FLOAT, stride, pointer);
    }

    void PushClientAttrib( RegalContext * ctx, GLbitfield mask )
    {
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

    template <typename T> void Get( GLenum pname, T * params )
    {
        switch (pname)
        {
            case GL_PACK_SWAP_BYTES:
                *params = static_cast<T>(currentClientState.pixelStoreState.packSwapBytes );
                return;

            case GL_PACK_LSB_FIRST:
                *params = static_cast<T>(currentClientState.pixelStoreState.packLsbFirst );
                return;

            case GL_PACK_ROW_LENGTH:
                *params = static_cast<T>(currentClientState.pixelStoreState.packRowLength );
                return;

            case GL_PACK_IMAGE_HEIGHT:
                *params = static_cast<T>(currentClientState.pixelStoreState.packImageHeight );
                return;

            case GL_PACK_SKIP_ROWS:
                *params = static_cast<T>(currentClientState.pixelStoreState.packSkipRows );
                return;

            case GL_PACK_SKIP_PIXELS:
                *params = static_cast<T>(currentClientState.pixelStoreState.packSkipPixels );
                return;

            case GL_PACK_SKIP_IMAGES:
                *params = static_cast<T>(currentClientState.pixelStoreState.packSkipImages );
                return;

            case GL_PACK_ALIGNMENT:
                *params = static_cast<T>(currentClientState.pixelStoreState.packAlignment );
                return;

            case GL_UNPACK_SWAP_BYTES:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackSwapBytes );
                return;

            case GL_UNPACK_LSB_FIRST:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackLsbFirst );
                return;

            case GL_UNPACK_ROW_LENGTH:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackRowLength );
                return;

            case GL_UNPACK_IMAGE_HEIGHT:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackImageHeight );
                return;

            case GL_UNPACK_SKIP_ROWS:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackSkipRows );
                return;

            case GL_UNPACK_SKIP_PIXELS:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackSkipPixels );
                return;

            case GL_UNPACK_SKIP_IMAGES:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackSkipImages );
                return;

            case GL_UNPACK_ALIGNMENT:
                *params = static_cast<T>(currentClientState.pixelStoreState.unpackAlignment );
                return;

            case GL_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(currentClientState.vertexArrayState.arrayBufferBinding);
                return;

            case GL_ELEMENT_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(currentClientState.vertexArrayState.elementArrayBufferBinding);
                return;

            case GL_PIXEL_PACK_BUFFER_BINDING:
                *params = static_cast<T>(currentClientState.pixelStoreState.pixelPackBufferBinding);
                return;

            case GL_PIXEL_UNPACK_BUFFER_BINDING:
                *params = static_cast<T>(currentClientState.pixelStoreState.pixelUnpackBufferBinding);
                return;

            case GL_ATTRIB_STACK_DEPTH:
                *params = static_cast<T>(topOfStack+1);
                return;

            case GL_MAX_VERTEX_ATTRIBS:
                *params = static_cast<T>(REGAL_PPC_MAX_VERTEX_ATTRIBS);
                return;

            case GL_MAX_CLIENT_ATTRIB_STACK_DEPTH:
                *params = static_cast<T>(REGAL_PPC_MAX_CLIENT_ATTRIB_STACK_DEPTH);
                return;

            case GL_MAX_TEXTURE_COORDS:
                *params = static_cast<T>(REGAL_PPC_MAX_TEXTURE_COORDS);
                return;

            case GL_CLIENT_ACTIVE_TEXTURE:
                *params = static_cast<T>(currentClientState.vertexArrayState.clientActiveTexture);
                return;

            case GL_VERTEX_ARRAY_SIZE:
                *params = static_cast<T>(currentClientState.vertexArrayState.vertexArrayState.size);
                return;

            case GL_VERTEX_ARRAY_TYPE:
                *params = static_cast<T>(currentClientState.vertexArrayState.vertexArrayState.type);
                return;

            case GL_VERTEX_ARRAY_STRIDE:
                *params = static_cast<T>(currentClientState.vertexArrayState.vertexArrayState.stride);
                return;

            case GL_VERTEX_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(currentClientState.vertexArrayState.vertexArrayState.bufferBinding);
                return;

            case GL_COLOR_ARRAY_SIZE:
                *params = static_cast<T>(currentClientState.vertexArrayState.colorArrayState.size);
                return;

            case GL_COLOR_ARRAY_TYPE:
                *params = static_cast<T>(currentClientState.vertexArrayState.colorArrayState.type);
                return;

            case GL_COLOR_ARRAY_STRIDE:
                *params = static_cast<T>(currentClientState.vertexArrayState.colorArrayState.stride);
                return;

            case GL_COLOR_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(currentClientState.vertexArrayState.colorArrayState.bufferBinding);
                return;

            case GL_SECONDARY_COLOR_ARRAY_SIZE:
                *params = static_cast<T>(currentClientState.vertexArrayState.secondaryColorArrayState.size);
                return;

            case GL_SECONDARY_COLOR_ARRAY_TYPE:
                *params = static_cast<T>(currentClientState.vertexArrayState.secondaryColorArrayState.type);
                return;

            case GL_SECONDARY_COLOR_ARRAY_STRIDE:
                *params = static_cast<T>(currentClientState.vertexArrayState.secondaryColorArrayState.stride);
                return;

            case GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(currentClientState.vertexArrayState.secondaryColorArrayState.bufferBinding);
                return;

            case GL_TEXTURE_COORD_ARRAY_SIZE:
                {
                    GLuint index = currentClientState.vertexArrayState.clientActiveTexture - GL_TEXTURE0;
                    RegalAssert(index >= 0);
                    RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);
                    *params = static_cast<T>(currentClientState.vertexArrayState.textureCoordArrayState[index].size);
                }
                return;

            case GL_TEXTURE_COORD_ARRAY_TYPE:
                {
                    GLuint index = currentClientState.vertexArrayState.clientActiveTexture - GL_TEXTURE0;
                    RegalAssert(index >= 0);
                    RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);
                    *params = static_cast<T>(currentClientState.vertexArrayState.textureCoordArrayState[index].type);
                }
                return;

            case GL_TEXTURE_COORD_ARRAY_STRIDE:
                {
                    GLuint index = currentClientState.vertexArrayState.clientActiveTexture - GL_TEXTURE0;
                    RegalAssert(index >= 0);
                    RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);
                    *params = static_cast<T>(currentClientState.vertexArrayState.textureCoordArrayState[index].stride);
                }
                return;

            case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:
                {
                    GLuint index = currentClientState.vertexArrayState.clientActiveTexture - GL_TEXTURE0;
                    RegalAssert(index >= 0);
                    RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);
                    *params = static_cast<T>(currentClientState.vertexArrayState.textureCoordArrayState[index].bufferBinding);
                }
                return;

            case GL_FOG_COORD_ARRAY_TYPE:
                *params = static_cast<T>(currentClientState.vertexArrayState.fogCoordArrayState.type);
                return;

            case GL_FOG_COORD_ARRAY_STRIDE:
                *params = static_cast<T>(currentClientState.vertexArrayState.fogCoordArrayState.stride);
                return;

            case GL_FOG_COORD_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(currentClientState.vertexArrayState.fogCoordArrayState.bufferBinding);
                return;

            case GL_INDEX_ARRAY_TYPE:
                *params = static_cast<T>(currentClientState.vertexArrayState.indexArrayState.type);
                return;

            case GL_INDEX_ARRAY_STRIDE:
                *params = static_cast<T>(currentClientState.vertexArrayState.indexArrayState.stride);
                return;

            case GL_INDEX_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(currentClientState.vertexArrayState.indexArrayState.bufferBinding);
                return;

            case GL_NORMAL_ARRAY_TYPE:
                *params = static_cast<T>(currentClientState.vertexArrayState.normalArrayState.type);
                return;

            case GL_NORMAL_ARRAY_STRIDE:
                *params = static_cast<T>(currentClientState.vertexArrayState.normalArrayState.stride);
                return;

            case GL_NORMAL_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(currentClientState.vertexArrayState.normalArrayState.bufferBinding);
                return;

            case GL_EDGE_FLAG_ARRAY_STRIDE:
                *params = static_cast<T>(currentClientState.vertexArrayState.edgeFlagArrayState.stride);
                return;

            case GL_EDGE_FLAG_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(currentClientState.vertexArrayState.edgeFlagArrayState.bufferBinding);
                return;

            case GL_PRIMITIVE_RESTART_INDEX:
                *params = static_cast<T>(currentClientState.vertexArrayState.primitiveRestartIndex);
                return;

            default:
                RegalAssert( !"unhandled pname value" );
                break;
        }
    }

    bool HandlesGet( GLenum pname )
    {
        switch (pname)
        {
            case GL_ARRAY_BUFFER_BINDING:
            case GL_ATTRIB_STACK_DEPTH:
            case GL_MAX_VERTEX_ATTRIBS:
            case GL_MAX_CLIENT_ATTRIB_STACK_DEPTH:
            case GL_COLOR_ARRAY_SIZE:
            case GL_COLOR_ARRAY_TYPE:
            case GL_COLOR_ARRAY_STRIDE:
            case GL_COLOR_ARRAY_BUFFER_BINDING:
            case GL_SECONDARY_COLOR_ARRAY_SIZE:
            case GL_SECONDARY_COLOR_ARRAY_TYPE:
            case GL_SECONDARY_COLOR_ARRAY_STRIDE:
            case GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING:
            case GL_TEXTURE_COORD_ARRAY_SIZE:
            case GL_TEXTURE_COORD_ARRAY_TYPE:
            case GL_TEXTURE_COORD_ARRAY_STRIDE:
            case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:
            case GL_FOG_COORD_ARRAY_TYPE:
            case GL_FOG_COORD_ARRAY_STRIDE:
            case GL_FOG_COORD_ARRAY_BUFFER_BINDING:
            case GL_INDEX_ARRAY_TYPE:
            case GL_INDEX_ARRAY_STRIDE:
            case GL_INDEX_ARRAY_BUFFER_BINDING:
            case GL_NORMAL_ARRAY_TYPE:
            case GL_NORMAL_ARRAY_STRIDE:
            case GL_NORMAL_ARRAY_BUFFER_BINDING:
            case GL_EDGE_FLAG_ARRAY_STRIDE:
            case GL_EDGE_FLAG_ARRAY_BUFFER_BINDING:
            case GL_PRIMITIVE_RESTART_INDEX:
                return true;
            default:
                break;
        }
        return false;
    }

    template <typename T> void GetIndexed( GLenum pname, GLuint index, T * params )
    {
        switch (pname)
        {
            case GL_TEXTURE_COORD_ARRAY_SIZE:
                RegalAssert(index >= 0);
                RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);
                *params = static_cast<T>(currentClientState.vertexArrayState.textureCoordArrayState[index].size);
                return;

            case GL_TEXTURE_COORD_ARRAY_TYPE:
                RegalAssert(index >= 0);
                RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);
                *params = static_cast<T>(currentClientState.vertexArrayState.textureCoordArrayState[index].type);
                return;

            case GL_TEXTURE_COORD_ARRAY_STRIDE:
                RegalAssert(index >= 0);
                RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);
                *params = static_cast<T>(currentClientState.vertexArrayState.textureCoordArrayState[index].stride);
                return;

            case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:
                RegalAssert(index >= 0);
                RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);
                *params = static_cast<T>(currentClientState.vertexArrayState.textureCoordArrayState[index].bufferBinding);
                return;

            default:
                RegalAssert( !"unhandled pname value" );
                break;
        }
    }

    bool HandlesGetIndexed( GLenum pname, GLuint index )
    {
        switch (pname)
        {
            case GL_TEXTURE_COORD_ARRAY_SIZE:
            case GL_TEXTURE_COORD_ARRAY_TYPE:
            case GL_TEXTURE_COORD_ARRAY_STRIDE:
            case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:
                return true;
            default:
                break;
        }
        return false;
    }

    GLboolean IsEnabled( GLenum cap )
    {
        switch (cap)
        {
            case GL_PRIMITIVE_RESTART:
                return currentClientState.vertexArrayState.primitiveRestart;

            case GL_EDGE_FLAG_ARRAY:
                return currentClientState.vertexArrayState.edgeFlagArrayState.enabled;

            case GL_NORMAL_ARRAY:
                return currentClientState.vertexArrayState.normalArrayState.enabled;

            case GL_INDEX_ARRAY:
                return currentClientState.vertexArrayState.indexArrayState.enabled;

            case GL_FOG_COORD_ARRAY:
                return currentClientState.vertexArrayState.fogCoordArrayState.enabled;

            case GL_VERTEX_ARRAY:
                return currentClientState.vertexArrayState.vertexArrayState.enabled;

            case GL_COLOR_ARRAY:
                return currentClientState.vertexArrayState.colorArrayState.enabled;

            case GL_SECONDARY_COLOR_ARRAY:
                return currentClientState.vertexArrayState.secondaryColorArrayState.enabled;

            case GL_TEXTURE_COORD_ARRAY:
                {
                    GLuint index = currentClientState.vertexArrayState.clientActiveTexture - GL_TEXTURE0;
                    RegalAssert(index >= 0);
                    RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);
                    return currentClientState.vertexArrayState.textureCoordArrayState[index].enabled;
                }

            default:
                RegalAssert( !"unhandled cap value" );
                break;
        }
        return GL_FALSE;
    }

    bool HandlesIsEnabled( GLenum cap )
    {
        switch (cap)
        {
            case GL_EDGE_FLAG_ARRAY:
            case GL_NORMAL_ARRAY:
            case GL_INDEX_ARRAY:
            case GL_FOG_COORD_ARRAY:
            case GL_VERTEX_ARRAY:
            case GL_COLOR_ARRAY:
            case GL_SECONDARY_COLOR_ARRAY:
            case GL_TEXTURE_COORD_ARRAY:
                return true;
            default:
                break;
        }
        return false;
    }

    GLboolean IsEnabledIndexed( GLenum cap, GLuint index )
    {
        switch (cap)
        {
            case GL_TEXTURE_COORD_ARRAY:
                RegalAssert(index >= 0);
                RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);
                return currentClientState.vertexArrayState.textureCoordArrayState[index].enabled;

            default:
                RegalAssert( !"unhandled cap value" );
                break;
        }
        return GL_FALSE;
    }

    bool HandlesIsEnabledIndexed( GLenum cap, GLuint index )
    {
        switch (cap)
        {
            case GL_TEXTURE_COORD_ARRAY:
                return true;
            default:
                break;
        }
        return false;
    }

    void GetPointerv( GLenum pname, GLvoid ** params)
    {
        switch (pname)
        {
            case GL_EDGE_FLAG_ARRAY_POINTER:
                *params = const_cast<GLvoid *>(currentClientState.vertexArrayState.edgeFlagArrayState.pointer);
                break;

            case GL_NORMAL_ARRAY_POINTER:
                *params = const_cast<GLvoid *>(currentClientState.vertexArrayState.normalArrayState.pointer);
                break;

            case GL_INDEX_ARRAY_POINTER:
                *params = const_cast<GLvoid *>(currentClientState.vertexArrayState.indexArrayState.pointer);
                break;

            case GL_FOG_COORD_ARRAY_POINTER:
                *params = const_cast<GLvoid *>(currentClientState.vertexArrayState.fogCoordArrayState.pointer);
                break;

            case GL_VERTEX_ARRAY_POINTER:
                *params = const_cast<GLvoid *>(currentClientState.vertexArrayState.vertexArrayState.pointer);
                break;

            case GL_COLOR_ARRAY_POINTER:
                *params = const_cast<GLvoid *>(currentClientState.vertexArrayState.colorArrayState.pointer);
                break;

            case GL_SECONDARY_COLOR_ARRAY_POINTER:
                *params = const_cast<GLvoid *>(currentClientState.vertexArrayState.secondaryColorArrayState.pointer);
                break;

            case GL_TEXTURE_COORD_ARRAY_POINTER:
                {
                    GLuint index = currentClientState.vertexArrayState.clientActiveTexture - GL_TEXTURE0;
                    RegalAssert(index >= 0);
                    RegalAssert(index < REGAL_PPC_MAX_TEXTURE_COORDS);
                    *params = const_cast<GLvoid *>(currentClientState.vertexArrayState.textureCoordArrayState[index].pointer);
                }
                break;

            default:
                RegalAssert( !"unhandled pname value" );
                *params = NULL;
                break;
        }
    }

    bool HandlesGetPointerv( GLenum pname )
    {
        switch (pname)
        {
            case GL_EDGE_FLAG_ARRAY_POINTER:
            case GL_NORMAL_ARRAY_POINTER:
            case GL_INDEX_ARRAY_POINTER:
            case GL_FOG_COORD_ARRAY_POINTER:
            case GL_VERTEX_ARRAY_POINTER:
            case GL_COLOR_ARRAY_POINTER:
            case GL_SECONDARY_COLOR_ARRAY_POINTER:
            case GL_TEXTURE_COORD_ARRAY_POINTER:
                return true;
            default:
                break;
        }
        return false;
    }

    void GetVertexAttribPointerv( GLuint index, GLenum pname, GLvoid ** pointer)
    {
        RegalAssert( pname == GL_VERTEX_ATTRIB_ARRAY_POINTER );
        RegalAssert( index < REGAL_PPC_MAX_VERTEX_ATTRIBS );

        *pointer = const_cast<GLvoid *>(currentClientState.vertexArrayState.genericArrayState[index].pointer);
    }

    bool HandlesGetVertexAttribPointerv( GLuint index, GLenum pname )
    {
        return ( ( pname == GL_VERTEX_ATTRIB_ARRAY_POINTER ) &&
                 ( index < REGAL_PPC_MAX_VERTEX_ATTRIBS ) );
    }

    template <typename T> void GetVertexAttribv( GLuint index, GLenum pname, T * params )
    {
        RegalAssert( index < REGAL_PPC_MAX_VERTEX_ATTRIBS );
        RegalAssert( !(index == 0 && pname == GL_CURRENT_VERTEX_ATTRIB) );

        ClientArrayState &gas = currentClientState.vertexArrayState.genericArrayState[index];

        switch (pname)
        {
            case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(gas.bufferBinding);
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
                RegalAssert( !"unhandled pname value" );
                break;
        }
    }

    bool HandlesGetVertexAttribv( GLuint index, GLenum pname )
    {
        if ( index >= REGAL_PPC_MAX_VERTEX_ATTRIBS )
            return false;

        if ( index == 0 && pname == GL_CURRENT_VERTEX_ATTRIB)
            return false;
        
        switch (pname)
        {
            case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
            case GL_VERTEX_ATTRIB_ARRAY_ENABLED:
            case GL_VERTEX_ATTRIB_ARRAY_SIZE:
            case GL_VERTEX_ATTRIB_ARRAY_DIVISOR:
            case GL_VERTEX_ATTRIB_ARRAY_STRIDE:
            case GL_VERTEX_ATTRIB_ARRAY_TYPE:
            case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:
                return true;

            default:
                break;
        }
        return false;

    }
};

#endif // ! __REGAL_PPC_H__
