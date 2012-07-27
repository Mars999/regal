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

 Regal push / pop attrib
 Nigel Stewart

*/

#ifndef __REGAL_PPA_H__
#define __REGAL_PPA_H__

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include <vector>

#include <GL/Regal.h>

#include "RegalState.h"
#include "RegalEmu.h"
#include "RegalLog.h"
#include "RegalToken.h"
#include "RegalDispatchState.h"

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

// Only glPushAttrib(GL_STENCIL_BUFFER_BIT) so far...

struct RegalPpa : public RegalEmu, State::Stencil, State::Depth, State::Polygon
{
  void Init(RegalContext *ctx)
  {
    UNUSED_PARAMETER(ctx);
  }

  void PushAttrib(RegalContext *ctx, GLbitfield mask)
  {
    UNUSED_PARAMETER(ctx);

    maskStack.push_back(mask);

    if (mask&GL_DEPTH_BUFFER_BIT)
    {
      depthStack.push_back(State::Depth());
      depthStack.back() = *this;
      mask &= ~GL_DEPTH_BUFFER_BIT;
    }

    if (mask&GL_STENCIL_BUFFER_BIT)
    {
      stencilStack.push_back(State::Stencil());
      stencilStack.back() = *this;
      mask &= ~GL_STENCIL_BUFFER_BIT;
    }

    if (mask&GL_POLYGON_BIT)
    {
      polygonStack.push_back(State::Polygon());
      polygonStack.back() = *this;
      mask &= ~GL_POLYGON_BIT;
    }

    // Pass the rest through, for now

    if (mask)
      ctx->dsp->emuTbl.glPushAttrib(mask);
  }

  void PopAttrib(RegalContext *ctx)
  {
    RegalAssert(ctx);
    RegalAssert(maskStack.size());

    if (maskStack.size())
    {
      GLbitfield mask = maskStack.back();
      maskStack.pop_back();

      if (mask&GL_DEPTH_BUFFER_BIT)
      {
        RegalAssert(depthStack.size());
        State::Depth::swap(depthStack.back());
        depthStack.pop_back();

        ITrace("RegalPpa::PopAttrib GL_DEPTH_BUFFER_BIT ",State::Depth::toString());

        // Ideally we'd only set the state that has changed
        // since the glPushAttrib() - revisit

        State::Depth::set(ctx->dsp->emuTbl);

        mask &= ~GL_DEPTH_BUFFER_BIT;
      }

      if (mask&GL_STENCIL_BUFFER_BIT)
      {
        RegalAssert(stencilStack.size());
        State::Stencil::swap(stencilStack.back());
        stencilStack.pop_back();

        ITrace("RegalPpa::PopAttrib GL_STENCIL_BUFFER_BIT ",State::Stencil::toString());

        // Ideally we'd only set the state that has changed
        // since the glPushAttrib() - revisit

        State::Stencil::set(ctx->dsp->emuTbl);

        mask &= ~GL_STENCIL_BUFFER_BIT;
      }

      if (mask&GL_POLYGON_BIT)
      {
        RegalAssert(polygonStack.size());
        State::Polygon::swap(polygonStack.back());
        polygonStack.pop_back();

        ITrace("RegalPpa::PopAttrib GL_POLYGON_BIT ",State::Polygon::toString());

        // Ideally we'd only set the state that has changed
        // since the glPushAttrib() - revisit

        State::Polygon::set(ctx->dsp->emuTbl);

        mask &= ~GL_POLYGON_BIT;
      }

      // Pass the rest through, for now

      if (mask)
        ctx->dsp->emuTbl.glPopAttrib();
    }
  }

  void Enable(GLenum cap)
  {
    ITrace("RegalPpa::Enable ",Token::toString(cap));
    switch (cap)
    {
      case GL_DEPTH_TEST:           State::Depth::enable          = GL_TRUE; break;
      case GL_STENCIL_TEST:         State::Stencil::enable        = GL_TRUE; break;
      case GL_CULL_FACE:            State::Polygon::cullEnable    = GL_TRUE; break;
      case GL_POLYGON_SMOOTH:       State::Polygon::smoothEnable  = GL_TRUE; break;
      case GL_POLYGON_STIPPLE:      State::Polygon::stippleEnable = GL_TRUE; break;
      case GL_POLYGON_OFFSET_FILL:  State::Polygon::offsetFill    = GL_TRUE; break;
      case GL_POLYGON_OFFSET_LINE:  State::Polygon::offsetLine    = GL_TRUE; break;
      case GL_POLYGON_OFFSET_POINT: State::Polygon::offsetPoint   = GL_TRUE; break;
      default:                                                               break;
    }
  }

  void Disable(GLenum cap)
  {
    ITrace("RegalPpa::Disable ",Token::toString(cap));
    switch (cap)
    {
      case GL_DEPTH_TEST:           State::Depth::enable          = GL_FALSE; break;
      case GL_STENCIL_TEST:         State::Stencil::enable        = GL_FALSE; break;
      case GL_CULL_FACE:            State::Polygon::cullEnable    = GL_FALSE; break;
      case GL_POLYGON_SMOOTH:       State::Polygon::smoothEnable  = GL_FALSE; break;
      case GL_POLYGON_STIPPLE:      State::Polygon::stippleEnable = GL_FALSE; break;
      case GL_POLYGON_OFFSET_FILL:  State::Polygon::offsetFill    = GL_FALSE; break;
      case GL_POLYGON_OFFSET_LINE:  State::Polygon::offsetLine    = GL_FALSE; break;
      case GL_POLYGON_OFFSET_POINT: State::Polygon::offsetPoint   = GL_FALSE; break;
      default:                                                                break;
    }
  }

  std::vector<GLbitfield>     maskStack;
  std::vector<State::Depth>   depthStack;
  std::vector<State::Stencil> stencilStack;
  std::vector<State::Polygon> polygonStack;
};

REGAL_NAMESPACE_END

#endif // ! __REGAL_PPA_H__
