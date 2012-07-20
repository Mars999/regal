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

#ifndef __REGAL_STATE_H__
#define __REGAL_STATE_H__

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include <string>
#include <algorithm>  // For std::swap

#include <boost/print/print_string.hpp>
#include <boost/print/string_list.hpp>

#include "RegalToken.h"
#include "RegalDispatch.h"

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

//
// OpenGL State Tracking
//
// Motivating requirements:
//
//  - Emulation of glPushAttrib and glPopAttrib for OpenGL ES and
//    core OpenGL that lack the functionality.
//
//  - OpenGL state capture, browsing, diff and serialization.
//
// See also:
//
//  - Gallium3D
//    http://wiki.freedesktop.org/wiki/Software/gallium
//    http://dri.freedesktop.org/doxygen/gallium/p__state_8h-source.html
//
//  - Tracking Graphics State For Networked Rendering
//    Ian Buck, Greg Humphreys and Pat Hanrahan.
//    Stanford University
//    Proceedings of the 2000 Eurographics/SIGGRAPH Workshop on Graphics Hardware
//    http://graphics.stanford.edu/papers/state_tracking/
//
//  - Chromium: A Stream Processing Framework for Interactive Rendering on Clusters
//    Greg Humphreys, Mike Houston, Ren Ng
//    Stanford University
//    SIGGRAPH 2002
//    http://graphics.stanford.edu/papers/cr/
//

namespace State {

  using   ::boost::print::hex;
  using   ::boost::print::print_string;
  typedef ::boost::print::string_list<std::string> string_list;

  //
  // glPushAttrib(GL_DEPTH_BUFFER_BIT)
  //

  struct Depth
  {
    GLboolean   enable;
    GLenum      func;
    GLclampd    clear;
    GLboolean   mask;

    inline Depth()
    : enable(GL_FALSE), func(GL_LESS), clear(1.0), mask(GL_TRUE)
    {
    }

    inline Depth &swap(Depth &other)
    {
      std::swap(enable,other.enable);
      std::swap(func,other.func);
      std::swap(clear,other.clear);
      std::swap(mask,other.mask);
      return *this;
    }

    inline void glClearDepth(GLclampd depth)
    {
      clear = depth;
    }

    inline void glDepthFunc(GLenum f)
    {
      func = f;
    }

    inline void glDepthMask(GLboolean m)
    {
      mask = m;
    }

    inline Depth &get(DispatchTable &dt)
    {
      RegalAssert(dt.glIsEnabled);
      enable = dt.glIsEnabled(GL_DEPTH_TEST);
  
      RegalAssert(dt.glGetIntegerv);
      dt.glGetIntegerv(GL_DEPTH_FUNC,reinterpret_cast<GLint *>(&func));

      RegalAssert(dt.glGetFloatv);
      dt.glGetFloatv(GL_DEPTH_CLEAR_VALUE,reinterpret_cast<GLfloat *>(&clear));

      RegalAssert(dt.glGetBooleanv);
      dt.glGetBooleanv(GL_DEPTH_WRITEMASK,&mask);

      return *this;
    }

    inline const Depth &set(DispatchTable &dt) const
    {
      RegalAssert(dt.glEnable);
      RegalAssert(dt.glDisable);
      if (enable)
        dt.glEnable(GL_DEPTH_TEST);
      else
        dt.glDisable(GL_DEPTH_TEST);

      RegalAssert(dt.glDepthFunc);
      dt.glDepthFunc(func);

      RegalAssert(dt.glClearDepth);
      dt.glClearDepth(clear);

      RegalAssert(dt.glDepthMask);
      dt.glDepthMask(mask);

      return *this;
    }

    inline std::string toString() const
    {
      string_list tmp;
      tmp << print_string(enable ? "glEnable" : "glDisable","(GL_DEPTH_TEST);\n");
      tmp << print_string("glDepthfunc(",Token::toString(func),");\n");
      tmp << print_string("glClearDepth(",clear,");\n");
      tmp << print_string("glDepthMask(",mask ? "GL_TRUE" : "GL_FALSE",");\n");
      return tmp;
    }
  };

  struct StencilFace
  {
    GLenum func;      // glStencilFunc
    GLint  ref;       // glStencilFunc
    GLuint valueMask; // glStencilFunc
    GLuint writeMask; // glStencilMask
    GLenum fail;      // glStencilOp
    GLenum zfail;     // glStencilOp
    GLenum zpass;     // glStencilOp

    inline StencilFace()
    : func     (GL_ALWAYS),
      ref      (0),
      valueMask(~0u),
      writeMask(~0u),
      fail     (GL_KEEP),
      zfail    (GL_KEEP),
      zpass    (GL_KEEP)
    {
    }

    inline StencilFace &swap(StencilFace &other)
    {
      std::swap(func,     other.func);
      std::swap(ref,      other.ref);
      std::swap(valueMask,other.valueMask);
      std::swap(writeMask,other.writeMask);
      std::swap(fail,     other.fail);
      std::swap(zfail,    other.zfail);
      std::swap(zpass,    other.zpass);
      return *this;
    }

    inline StencilFace &get(DispatchTable &dt, GLenum face)
    {
      RegalAssert(dt.glGetIntegerv);
      dt.glGetIntegerv(face==GL_FRONT ? GL_STENCIL_FUNC            : GL_STENCIL_BACK_FUNC,            reinterpret_cast<GLint *>(&func)     );
      dt.glGetIntegerv(face==GL_FRONT ? GL_STENCIL_REF             : GL_STENCIL_BACK_REF,             &ref                                 );
      dt.glGetIntegerv(face==GL_FRONT ? GL_STENCIL_VALUE_MASK      : GL_STENCIL_BACK_VALUE_MASK,      reinterpret_cast<GLint *>(&valueMask));
      dt.glGetIntegerv(face==GL_FRONT ? GL_STENCIL_WRITEMASK       : GL_STENCIL_BACK_WRITEMASK,       reinterpret_cast<GLint *>(&writeMask));
      dt.glGetIntegerv(face==GL_FRONT ? GL_STENCIL_FAIL            : GL_STENCIL_BACK_FAIL,            reinterpret_cast<GLint *>(&fail)     );
      dt.glGetIntegerv(face==GL_FRONT ? GL_STENCIL_PASS_DEPTH_FAIL : GL_STENCIL_BACK_PASS_DEPTH_FAIL, reinterpret_cast<GLint *>(&zfail)    );
      dt.glGetIntegerv(face==GL_FRONT ? GL_STENCIL_PASS_DEPTH_PASS : GL_STENCIL_BACK_PASS_DEPTH_PASS, reinterpret_cast<GLint *>(&zpass)    );
      return *this;
    }

    inline const StencilFace &set(DispatchTable &dt, GLenum face) const
    {
      RegalAssert(dt.glStencilFuncSeparate);
      dt.glStencilFuncSeparate(face,func,ref,valueMask);

      RegalAssert(dt.glStencilMaskSeparate);
      dt.glStencilMaskSeparate(face,writeMask);

      RegalAssert(dt.glStencilOpSeparate);
      dt.glStencilOpSeparate(face,fail,zfail,zpass);

      return *this;
    }

    inline std::string toString(GLenum face) const
    {
      string_list tmp;
      tmp << print_string("glStencilFuncSeparate(",Token::toString(face),",",Token::toString(func),",",ref,",0x",hex(valueMask),");\n");
      tmp << print_string("glStencilMaskSeparate(",Token::toString(face),",0x",hex(writeMask),");\n");
      tmp << print_string("glStencilOpSeparate(",Token::toString(face),",",Token::toString(fail),",",Token::toString(zfail),",",Token::toString(zpass),");\n");
      return tmp;
    }
  };

  //
  // glPushAttrib(GL_STENCIL_BUFFER_BIT)
  //

  struct Stencil
  {
    GLboolean   enable;
    GLint       clear;
    StencilFace front;
    StencilFace back;

    inline Stencil()
    : enable(GL_FALSE), clear(0)
    {
    }

    inline Stencil &swap(Stencil &other)
    {
      std::swap(enable,other.enable);
      std::swap(clear,other.clear);
      front.swap(other.front);
      back.swap(other.back);
      return *this;
    }

    inline void glClearStencil(GLint s)
    {
      clear = s;
    }

    inline void glStencilFunc(GLenum func, GLint ref, GLuint mask)
    {
      front.func      = back.func      = func;
      front.ref       = back.ref       = ref;
      front.valueMask = back.valueMask = mask;
    }

    inline void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
    {
      switch (face)
      {
        case GL_FRONT:
          front.func      = func;
          front.ref       = ref;
          front.valueMask = mask;
          break;
        case GL_BACK:
          back.func      = func;
          back.ref       = ref;
          back.valueMask = mask;
          break;
        case GL_FRONT_AND_BACK:
          front.func      = back.func      = func;
          front.ref       = back.ref       = ref;
          front.valueMask = back.valueMask = mask;
          break;
        default:
          RegalAssert(face==GL_FRONT || face==GL_BACK || face==GL_FRONT_AND_BACK);
          break;
      }
    }

    inline void glStencilMask(GLuint mask)
    {
      front.writeMask = back.writeMask = mask;
    }

    inline void glStencilMaskSeparate(GLenum face, GLuint mask)
    {
      switch (face)
      {
        case GL_FRONT:            front.writeMask = mask;                  break;
        case GL_BACK:             back.writeMask  = mask;                  break;
        case GL_FRONT_AND_BACK:   front.writeMask = back.writeMask = mask; break;
        default:
          RegalAssert(face==GL_FRONT || face==GL_BACK || face==GL_FRONT_AND_BACK);
          break;
      }
    }

    inline void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
    {
      front.fail  = back.fail  = fail;
      front.zfail = back.zfail = zfail;
      front.zpass = back.zpass = zpass;
    }

    inline void glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
    {
      switch (face)
      {
        case GL_FRONT:
          front.fail  = fail;
          front.zfail = zfail;
          front.zpass = zpass;
          break;
        case GL_BACK:
          back.fail  = fail;
          back.zfail = zfail;
          back.zpass = zpass;
          break;
        case GL_FRONT_AND_BACK:
          front.fail  = back.fail  = fail;
          front.zfail = back.zfail = zfail;
          front.zpass = back.zpass = zpass;
          break;
        default:
          RegalAssert(face==GL_FRONT || face==GL_BACK || face==GL_FRONT_AND_BACK);
          break;
      }
    }

    inline Stencil &get(DispatchTable &dt)
    {
      RegalAssert(dt.glIsEnabled);
      enable = dt.glIsEnabled(GL_STENCIL_TEST);
      RegalAssert(dt.glGetIntegerv);
      dt.glGetIntegerv(GL_STENCIL_CLEAR_VALUE,&clear);
      front.get(dt,GL_FRONT);
      back .get(dt,GL_BACK );   // What about GL < 2.0 ?
      return *this;
    }

    inline const Stencil &set(DispatchTable &dt) const
    {
      RegalAssert(dt.glEnable);
      RegalAssert(dt.glDisable);
      if (enable)
        dt.glEnable(GL_STENCIL_TEST);
      else
        dt.glDisable(GL_STENCIL_TEST);

      RegalAssert(dt.glClearStencil);
      dt.glClearStencil(clear);

      front.set(dt,GL_FRONT);
      back .set(dt,GL_BACK);
      return *this;
    }

    inline std::string toString() const
    {
      string_list tmp;
      tmp << print_string(enable ? "glEnable" : "glDisable","(GL_STENCIL_TEST);\n");
      tmp << print_string("glClearStencil(",clear,");\n");
      tmp << front.toString(GL_FRONT);
      tmp << front.toString(GL_BACK);
      return tmp;
    }
  };

  //
  // glPushAttrib(GL_POLYGON_BIT)
  //

  struct Polygon
  {
    GLboolean   cullEnable;
    GLenum      cull;
    GLenum      frontFace;
    GLenum      frontMode;
    GLenum      backMode;
    GLboolean   smoothEnable;
    GLboolean   stippleEnable;
    GLboolean   offsetFill;
    GLboolean   offsetLine;
    GLboolean   offsetPoint;
    GLfloat     factor;
    GLfloat     units;

    inline Polygon()
    : cullEnable(GL_FALSE), cull(GL_BACK), frontFace(GL_CCW), frontMode(GL_FILL), backMode(GL_FILL),
      smoothEnable(GL_FALSE), stippleEnable(GL_FALSE), offsetFill(GL_FALSE), offsetLine(GL_FALSE), offsetPoint(GL_FALSE),
      factor(0), units(0)
    {
    }

    inline Polygon &swap(Polygon &other)
    {
      std::swap(cullEnable,other.cullEnable);
      std::swap(cull,other.cull);
      std::swap(frontFace,other.frontFace);
      std::swap(frontMode,other.frontMode);
      std::swap(backMode,other.backMode);
      std::swap(smoothEnable,other.smoothEnable);
      std::swap(stippleEnable,other.stippleEnable);
      std::swap(offsetFill,other.offsetFill);
      std::swap(offsetLine,other.offsetLine);
      std::swap(offsetPoint,other.offsetPoint);
      std::swap(factor,other.factor);
      std::swap(units,other.units);
      return *this;
    }

    inline void glCullFace(GLenum mode)
    {
      cull = mode;
    }

    inline void glFrontFace(GLenum mode)
    {
      frontFace = mode;
    }

    inline void glPolygonMode(GLenum f, GLenum mode)
    {
      switch (f)
      {
        case GL_FRONT:          frontMode = mode;            break;
        case GL_BACK:           backMode  = mode;            break;
        case GL_FRONT_AND_BACK: frontMode = backMode = mode; break;
        default:                                             break;
      }
    }

    inline void glPolygonOffset(GLfloat f, GLfloat u)
    {
      factor = f;
      units  = u;
    }

    inline Polygon &get(DispatchTable &dt)
    {
      RegalAssert(dt.glIsEnabled);
      cullEnable = dt.glIsEnabled(GL_CULL_FACE);
  
      RegalAssert(dt.glGetIntegerv);
      dt.glGetIntegerv(GL_CULL_FACE_MODE,reinterpret_cast<GLint *>(&cull));
      dt.glGetIntegerv(GL_FRONT_FACE,reinterpret_cast<GLint *>(&frontFace));
      dt.glGetIntegerv(GL_POLYGON_MODE,reinterpret_cast<GLint *>(&frontMode));
      dt.glGetIntegerv(GL_FRONT_FACE,reinterpret_cast<GLint *>(&frontFace));

      smoothEnable  = dt.glIsEnabled(GL_POLYGON_SMOOTH);
      stippleEnable = dt.glIsEnabled(GL_POLYGON_STIPPLE);
      offsetFill    = dt.glIsEnabled(GL_POLYGON_OFFSET_FILL);
      offsetLine    = dt.glIsEnabled(GL_POLYGON_OFFSET_LINE);
      offsetPoint   = dt.glIsEnabled(GL_POLYGON_OFFSET_POINT);

      RegalAssert(dt.glGetFloatv);
      dt.glGetFloatv(GL_POLYGON_OFFSET_FACTOR,&factor);
      dt.glGetFloatv(GL_POLYGON_OFFSET_UNITS,&units);

      return *this;
    }

    inline const Polygon &set(DispatchTable &dt) const
    {
      RegalAssert(dt.glEnable);
      RegalAssert(dt.glDisable);
      if (cullEnable)
        dt.glEnable(GL_CULL_FACE);
      else
        dt.glDisable(GL_CULL_FACE);

      RegalAssert(dt.glCullFace);
      dt.glCullFace(cull);

      RegalAssert(dt.glFrontFace);
      dt.glFrontFace(frontFace);

      RegalAssert(dt.glPolygonMode);
      dt.glPolygonMode(GL_FRONT,frontMode);
      dt.glPolygonMode(GL_BACK,backMode);

      if (smoothEnable)
        dt.glEnable(GL_POLYGON_SMOOTH);
      else
        dt.glDisable(GL_POLYGON_SMOOTH);

      if (stippleEnable)
        dt.glEnable(GL_POLYGON_STIPPLE);
      else
        dt.glDisable(GL_POLYGON_STIPPLE);

      if (offsetFill)
        dt.glEnable(GL_POLYGON_OFFSET_FILL);
      else
        dt.glDisable(GL_POLYGON_OFFSET_FILL);

      if (offsetLine)
        dt.glEnable(GL_POLYGON_OFFSET_LINE);
      else
        dt.glDisable(GL_POLYGON_OFFSET_LINE);

      if (offsetPoint)
        dt.glEnable(GL_POLYGON_OFFSET_POINT);
      else
        dt.glDisable(GL_POLYGON_OFFSET_POINT);

      RegalAssert(dt.glPolygonOffset);
      dt.glPolygonOffset(factor,units);

      return *this;
    }

    inline std::string toString() const
    {
      string_list tmp;
      tmp << print_string(cullEnable ? "glEnable" : "glDisable","(GL_CULL_FACE);\n");
      tmp << print_string("glCullFace(",Token::toString(cull),");\n");
      tmp << print_string("glFrontFace(",Token::toString(frontFace),");\n");
      tmp << print_string("glPolygonMode(GL_FRONT,",Token::toString(frontMode),");\n");
      tmp << print_string("glPolygonMode(GL_BACK,",Token::toString(backMode),");\n");
      tmp << print_string(smoothEnable  ? "glEnable" : "glDisable","(GL_POLYGON_SMOOTH);\n");
      tmp << print_string(stippleEnable ? "glEnable" : "glDisable","(GL_POLYGON_STIPPLE);\n");
      tmp << print_string(offsetFill    ? "glEnable" : "glDisable","(GL_POLYGON_OFFSET_FILL);\n");
      tmp << print_string(offsetLine    ? "glEnable" : "glDisable","(GL_POLYGON_OFFSET_LINE);\n");
      tmp << print_string(offsetPoint   ? "glEnable" : "glDisable","(GL_POLYGON_OFFSET_POINT);\n");
      return tmp;
    }
  };
}

REGAL_NAMESPACE_END

#endif
