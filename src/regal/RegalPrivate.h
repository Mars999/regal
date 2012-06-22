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

#ifndef __REGAL_PRIVATE_H__
#define __REGAL_PRIVATE_H__

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include <GL/Regal.h>

#include <cstdio>
#include <cstring>

#ifndef REGAL_SYS_WGL
#include <pthread.h>
#endif

#include "RegalUtil.h"
#include "RegalConfig.h"
#include "RegalLookup.h"
#include "RegalDispatch.h"

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

using ::RegalErrorCallback;

#define REGAL_DECL_EXPORT 1
#define REGAL_SYS_WGL_DECLARE_WGL 1

// attrib mapping

enum RegalFixedFunctionAttrib {
    RFF2A_Vertex = 0,
    RFF2A_Weights = 1,
    RFF2A_Normal = 2,
    RFF2A_Color = 3,
    RFF2A_SecondaryColor = 4,
    RFF2A_FogCoord = 5,
    RFF2A_EdgeFlag = 6,
    RFF2A_TexCoord = 7,
    RFF2A_Invalid = 99
};

const GLenum RFFA2Enum[] = {
    GL_VERTEX_ARRAY,
    GL_WEIGHT_ARRAY_ARB,
    GL_NORMAL_ARRAY,
    GL_COLOR_ARRAY,
    GL_SECONDARY_COLOR_ARRAY,
    GL_FOG_COORDINATE_ARRAY,
    GL_EDGE_FLAG_ARRAY,
    GL_TEXTURE_COORD_ARRAY
};

const GLuint RFF2AMap8[] = {  0, 99, 2, 1, 99, 7, 99, 3 };
const GLuint RFF2AInvMap8[] = {
    RFF2A_Vertex,
    RFF2A_Color,
    RFF2A_Normal,
    RFF2A_TexCoord,
    RFF2A_TexCoord,
    RFF2A_TexCoord,
    RFF2A_SecondaryColor,
    RFF2A_FogCoord
};
const GLuint RFF2ATexBegin8 = 3;
const GLuint RFF2ATexEnd8 = 6;
const GLuint RFF2AMap16[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
const GLuint RFF2AInvMap16[] = {
    RFF2A_Vertex,
    RFF2A_Weights,
    RFF2A_Normal,
    RFF2A_Color,
    RFF2A_SecondaryColor,
    RFF2A_FogCoord,
    RFF2A_EdgeFlag,
    RFF2A_Invalid,
    RFF2A_TexCoord, RFF2A_TexCoord, RFF2A_TexCoord, RFF2A_TexCoord,
    RFF2A_TexCoord, RFF2A_TexCoord, RFF2A_TexCoord, RFF2A_TexCoord
};
const GLuint RFF2ATexBegin16 = 8;
const GLuint RFF2ATexEnd16 = 16;

// end attrib mapping

extern void RegalPrivateMakeCurrent(RegalSystemContext sysCtx);

#if REGAL_SYS_WGL

    typedef DWORD Thread;

    extern __declspec( thread ) void * regalCurrentContext;

    inline void * RegalPrivateGetCurrentContext()
    {
        return regalCurrentContext;
    }

#else
    typedef pthread_t Thread;

    extern pthread_key_t regalPrivateCurrentContextKey;

    inline void * RegalPrivateGetCurrentContext()
    {
#if ! REGAL_SYS_OSX
        return pthread_getspecific( regalPrivateCurrentContextKey );
#else
        void * v = pthread_getspecific( regalPrivateCurrentContextKey );
        if( v == NULL ) {
           RegalMakeCurrent( CGLGetCurrentContext() );
           return pthread_getspecific( regalPrivateCurrentContextKey );
        }
        return v;
#endif
    }
#endif

extern DispatchTableGlobal dispatchTableGlobal;

#define REGAL_MAX_DISPATCH_TABLE_STACK_SIZE 4

void RegalPrivateInitErrorDispatchTable( DispatchTable & tbl );
void RegalPrivateInitLoaderDispatchTable( DispatchTable & tbl );
void RegalPrivateInitEmuDispatchTable( DispatchTable & tbl );
void RegalPrivateInitDebugDispatchTable( DispatchTable & tbl );

enum RegalDispatchTableEnum {
   RDT_Driver = 1,
   RDT_Emu = 2,
   RDT_Error  = 3,
   RDT_Debug  = 4
};

struct RegalDispatchState {
   void Init()
   {
      for( int i = 0; i < REGAL_MAX_DISPATCH_TABLE_STACK_SIZE + 1; i++ ) {
        stack[i] = NULL;
      }
      stackSize = 0;
      stackCurr = 0; // todo: remove stackCurr 
      curr = stack[ stackCurr ];
      RegalPrivateInitErrorDispatchTable( errorTbl );
      RegalPrivateInitLoaderDispatchTable( driverTbl );
      RegalPrivateInitLoaderDispatchTable( emuTbl );
      RegalPrivateInitEmuDispatchTable( emuTbl ); // overrides emulated functions only
      RegalPrivateInitDebugDispatchTable( dbgTbl );
      if( Config::config.enableDebug )
         Insert( 0, RDT_Debug );
      Insert( 0, RDT_Emu );
      Insert( 0, RDT_Driver );
   }
   void StepDown()
   {
      RegalAssert( stackCurr > 0 );
      stackCurr--;
      curr = stack[stackCurr];
   }
   void StepUp()
   {
      RegalAssert( stackCurr < REGAL_MAX_DISPATCH_TABLE_STACK_SIZE );
      stackCurr++;
      curr = stack[stackCurr];
   }
   DispatchTable *Table( RegalDispatchTableEnum dt )
   {
      switch( dt ) {
        case RDT_Debug: return &dbgTbl;
        case RDT_Emu: return &emuTbl;
        case RDT_Error:  return &errorTbl;
        case RDT_Driver: return &driverTbl;
        default: break;
      }
      return NULL;
   }

   void Insert( int loc, RegalDispatchTableEnum dt )
   {
      DispatchTable * tbl = Table( dt );
      if (loc > stackSize || loc < 0 || tbl == NULL) {
         return;
      }
      if (stackSize >= REGAL_MAX_DISPATCH_TABLE_STACK_SIZE) {
         return;
      }
      stackSize++;
      stackCurr = stackSize - 1;
      for( int i = stackSize-1; i > loc; i-- ) {
         stack[ i ] = stack[ i - 1 ];
      }
      stack[ loc ] = tbl;
      curr = stack[stackCurr];
   }

   void Erase( RegalDispatchTableEnum dt )
   {
      DispatchTable * tbl = Table( dt );
      int slot = 0;
      for( int i = 1; i < REGAL_MAX_DISPATCH_TABLE_STACK_SIZE; i++ ) {
         if (stack[i] == tbl) {
            slot = i;
            break;
         }
      }
      if (slot == REGAL_MAX_DISPATCH_TABLE_STACK_SIZE) {
         return;
      }
      for( int i = slot; i < REGAL_MAX_DISPATCH_TABLE_STACK_SIZE; i++ ) {
         stack[ i ] = stack[ i + 1 ];
      }
      stackSize--;
      stackCurr = stackSize - 1;
      curr = stack[stackCurr];
   }

   DispatchTable *stack[ REGAL_MAX_DISPATCH_TABLE_STACK_SIZE + 1 ];
   DispatchTable *curr;
   int stackSize;
   int stackCurr;
   DispatchTable driverTbl;
   DispatchTable emuTbl;
   DispatchTable errorTbl;
   DispatchTable dbgTbl;
};

struct RegalDspScopedStepDown {
    RegalDispatchState & dsp;
    RegalDspScopedStepDown( RegalDispatchState & rDsp ) : dsp( rDsp ) {
        dsp.StepDown();
    }
    ~RegalDspScopedStepDown() {
        dsp.StepUp();
    }

    private:
    // make them private since we don't need (and can't copy, due to dsp being a reference
    RegalDspScopedStepDown(const RegalDspScopedStepDown& rhs);
    RegalDspScopedStepDown& operator =(const RegalDspScopedStepDown& rhs);

};

struct RegalContext;

struct RegalErrorState {
   void Init()
   {
      callback = NULL;
      inBeginEnd = false;
   }
   RegalErrorCallback Set( RegalContext *ctx, RegalErrorCallback cb );
   RegalErrorCallback callback;
   bool inBeginEnd;
};

REGAL_NAMESPACE_END

#include "RegalContext.h"

#define GET_REGAL_CONTEXT() ((::REGAL_NAMESPACE_INTERNAL::RegalContext *) ::REGAL_NAMESPACE_INTERNAL::RegalPrivateGetCurrentContext())

#endif // REGAL_PRIVATE_H
