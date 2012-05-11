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

 Regal Vertex Array Object implementation
 Cass Everitt

 */

#if ! __REGAL_VAO_H__
#define __REGAL_VAO_H__ 1

#include "RegalEmu.h"

#include <map>
#include <string>

#define REGAL_VAO_NUM_ARRAYS 16



struct RegalVao : public RegalEmu {

    struct Array {

        Array()
        : enabled( GL_FALSE )
        , buffer( 0 )
        , size( 4 )
        , type( GL_FLOAT )
        , normalized( GL_FALSE )
        , integer( GL_FALSE )
        , stride( 0 )
        , pointer( NULL )
        {}

        GLboolean enabled;
        GLuint buffer;
        GLint size;
        GLenum type;
        GLboolean normalized;
        GLboolean integer;
        GLsizei stride;
        const GLvoid * pointer;
    };

    struct Vao {
        Vao() : vertexBuffer( 0 ), indexBuffer( 0 ) {}
        GLuint vertexBuffer;
        GLuint indexBuffer;
        Array a[ REGAL_VAO_NUM_ARRAYS ];
    };

    std::map<GLuint, Vao> objects;

    GLuint current;
    GLuint enables;
    Vao * currVao;

    bool core;
    GLuint coreVao;
    GLuint maxName;
    GLuint maxVertexAttribs;

    void Init( RegalContext * ctx ) {
        maxVertexAttribs = ctx->ctxInf->maxVertexAttribs;
        RegalAssert( maxVertexAttribs <= REGAL_VAO_NUM_ARRAYS );
        
        core = true;
        //std::string s = (const char *)ctx->dsp.driverTbl.glGetString( GL_RENDER );
        RegalEmuScopedActivate activate( ctx, this );
        // needed for core 3.2 {
        maxName = 1;
        ctx->dsp.driverTbl.glGenVertexArrays( 1, & coreVao );
        ctx->dsp.driverTbl.glBindVertexArray( coreVao );
        // }
        current = 9999999; // this is only to force the bind...
        currVao = NULL;
        Bind( ctx, 0 );
    }

    void ShadowBufferBinding( GLenum target, GLuint bufferBinding ) {
        RegalAssert( currVao != NULL );
        if( target == GL_ARRAY_BUFFER ) {
            currVao->vertexBuffer = bufferBinding;
        } else if( target == GL_ELEMENT_ARRAY_BUFFER ) {
            currVao->indexBuffer = bufferBinding;
        }
    }

    void Bind( RegalContext * ctx, GLuint name ) {
        if( name == current ) {
            return;
        }

        current = name;

        Vao & vao = objects[current]; // force VAO construction
        currVao = & vao;
        if( maxName < current ) {
            maxName = current;
        }
        RegalDispatchTable & tbl = ctx->dsp.emuTbl;
        tbl.glBindBuffer( GL_ARRAY_BUFFER, vao.vertexBuffer );
        tbl.glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vao.indexBuffer );
        GLuint lastBuffer = vao.vertexBuffer;
        for( GLuint i = 0; i < maxVertexAttribs; i++ ) {
            Array & a = vao.a[ i ];
            if( a.buffer != lastBuffer ) {
                //GLint e = tbl.glGetError();
                tbl.glBindBuffer( GL_ARRAY_BUFFER, a.buffer );
                //e = tbl.glGetError();
                //RegalOutput( "Binding ARRAY_BUFFER %d - %d\n", a.buffer, e );
                lastBuffer = a.buffer;
            }

            SetEnableArray( ctx, a.enabled, i );
            if( a.pointer || a.buffer ) {
                tbl.glVertexAttribPointer( i, a.size, a.type, a.normalized, a.stride, a.pointer );
            }
        }
        if( lastBuffer != vao.vertexBuffer ) {
            tbl.glBindBuffer( GL_ARRAY_BUFFER, vao.vertexBuffer );
        }
    }

    void Gen( GLsizei n, GLuint * arrays ) {
        if( maxName < 0x80000000 ) { // fast gen for sequential allocation
            for( GLsizei i = 0; i < n; i++ ) {
                arrays[ i ] = ++maxName;
                objects[ maxName ]; // gen allocates
            }
        } else { // otherwise plod through
            GLsizei i = 0;
            GLuint name = 1;
            while( i < n ) {
                if( objects.count( name ) == 0 ) {
                    arrays[ i++ ] = name;
                    objects[ name ]; // gen allocates
                }
                name++;
            }
        }
    }

    void Delete( GLsizei n, const GLuint * arrays ) {
        for( GLsizei i = 0; i < n; i++ ) {
            GLuint name = arrays[ i ];
            if( objects.count( name ) > 0 ) {
                objects.erase( name );
            }
        }
    }

    GLboolean Exists( GLuint name ) {
        return objects.count( name ) > 0 ? GL_TRUE : GL_FALSE;
    }

    void SetEnableArray( RegalContext * ctx, GLboolean enable, GLuint index ) {
        RegalAssert( index < maxVertexAttribs );
        RegalDispatchTable &tbl = ctx->dsp.emuTbl;
        Array & a = objects[current].a[index];
        a.enabled = enable;
        if( a.enabled == GL_TRUE ) {
            tbl.glEnableVertexAttribArray( index );
            enables |= 1 << index;
        } else {
            tbl.glDisableVertexAttribArray( index );
            enables &= ~( 1 << index );
        }
    }

    void EnableArray( RegalContext * ctx, GLuint index ) {
        SetEnableArray( ctx, GL_TRUE, index );
    }

    void DisableArray( RegalContext * ctx, GLuint index ) {
        SetEnableArray( ctx, GL_FALSE, index );
    }

    void AttribPointer( RegalContext * ctx, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer ) {
        if( index == GLuint(~0) ) {
            return;
        }
        RegalAssert( index < maxVertexAttribs );
        RegalAssert( currVao != NULL );
        Array & a = objects[current].a[index];
        a.buffer = currVao->vertexBuffer;
        a.size = size;
        a.type = type;
        a.normalized = normalized;
        a.stride = stride;
        a.pointer = pointer;

        RegalAssert( a.buffer == 0 || GLuint64( a.pointer ) < ( 1 << 22 ) );
        
        ctx->dsp.emuTbl.glVertexAttribPointer( index, size, type, normalized, stride, pointer );
    }
    
    void Validate( RegalContext * ctx ) {
        RegalAssert( currVao != NULL );
        for( GLuint i = 0; i < maxVertexAttribs; i++ ) {
            const Array &a = currVao->a[ i ];
            RegalAssert( !( a.enabled && a.buffer == 0 && GLuint64( a.pointer ) < 1024 ) );
        }
    }

    template <typename T> void GetAttrib( GLint index, GLenum pname, T * params ) {
        Array & a = objects[current].a[index];
        switch( pname ) {
            case GL_VERTEX_ATTRIB_ARRAY_ENABLED:
                *params = static_cast<T>(a.enabled);
                break;
            case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(a.buffer);
                break;
            case GL_VERTEX_ATTRIB_ARRAY_SIZE:
                //if( index == 3 ) RegalOutput( "Returning %d for index 3 from VAO GetAttrib for SIZE\n", a.size );
                *params = static_cast<T>(a.size);
                break;
            case GL_VERTEX_ATTRIB_ARRAY_TYPE:
                *params = static_cast<T>(a.type);
                break;
            case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:
                *params = static_cast<T>(a.normalized);
                break;
            case GL_VERTEX_ATTRIB_ARRAY_STRIDE:
                *params = static_cast<T>(a.stride);
                break;
            case GL_VERTEX_ATTRIB_ARRAY_DIVISOR:
		*params = static_cast<T>(0);
            default:
                break;
        }
    }
    template <typename T> void GetAttrib( GLint index, GLenum pname, T ** params ) {
        Array & a = objects[current].a[index];
        switch( pname ) {
            case GL_VERTEX_ATTRIB_ARRAY_POINTER:
                *params = const_cast<T*>(a.pointer);
                break;
            default:
                break;
        }
    }

    template <typename T> void Get( GLenum pname, T * params ) {

        switch (pname) {
            case GL_VERTEX_ARRAY_BINDING:
                *params = static_cast<T>( current );
                return;

            case GL_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(currVao->vertexBuffer);
                return;

            case GL_ELEMENT_ARRAY_BUFFER_BINDING:
                *params = static_cast<T>(currVao->indexBuffer);
                return;

            default:
                break;
        }
    }

    bool HandlesGet( GLenum pname ) {
        switch (pname) {
            case GL_VERTEX_ARRAY_BINDING:
            case GL_ARRAY_BUFFER_BINDING:
            case GL_ELEMENT_ARRAY_BUFFER_BINDING:
                return true;
            default:
                break;
        }
        return false;
    }

};



#endif // ! __REGAL_VAO_H__







