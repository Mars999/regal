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

#include "pch.h" /* For MS precompiled header support */

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include "RegalHelper.h"

using std::size_t;

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

namespace helper { namespace size {

size_t
callLists(GLsizei n, GLenum type)
{
  size_t size = 0;

  switch (type)
  {
    case GL_BYTE:           size =     sizeof(GLbyte);   break;
    case GL_UNSIGNED_BYTE:  size =     sizeof(GLubyte);  break;
    case GL_SHORT:          size =     sizeof(GLshort);  break;
    case GL_UNSIGNED_SHORT: size =     sizeof(GLushort); break;
    case GL_INT:            size =     sizeof(GLint);    break;
    case GL_UNSIGNED_INT:   size =     sizeof(GLuint);   break;
    case GL_FLOAT:          size =     sizeof(GLfloat);  break;
    case GL_2_BYTES:        size = 2 * sizeof(GLubyte);  break;
    case GL_3_BYTES:        size = 3 * sizeof(GLubyte);  break;
    case GL_4_BYTES:        size = 4 * sizeof(GLubyte);  break;

    default: break;
  }

  size *= n > 0 ? (size_t)(n) : 0;

  return size;
}

size_t
fogv(GLenum pname)
{
  switch (pname)
  {
    case GL_FOG_MODE:             return 1;
    case GL_FOG_DENSITY:          return 1;
    case GL_FOG_START:            return 1;
    case GL_FOG_END:              return 1;
    case GL_FOG_INDEX:            return 1;
    case GL_FOG_COLOR:            return 4;
    case GL_FOG_COORD_SRC:        return 1;

    // GL_NV_fog_distance
    
    case GL_FOG_DISTANCE_MODE_NV: return 1;

    default:                      return 0;
  }
}

size_t
lightv(GLenum pname)
{
  switch (pname)
  {
    case GL_AMBIENT:               return 4;
    case GL_DIFFUSE:               return 4;
    case GL_SPECULAR:              return 4;
    case GL_POSITION:              return 4;
    case GL_SPOT_CUTOFF:           return 1;
    case GL_SPOT_DIRECTION:        return 3;
    case GL_SPOT_EXPONENT:         return 1;
    case GL_CONSTANT_ATTENUATION:  return 1;
    case GL_LINEAR_ATTENUATION:    return 1;
    case GL_QUADRATIC_ATTENUATION: return 1;
    default:                       return 0;
  }
}

size_t
lightModelv(GLenum pname)
{
  switch (pname)
  {
    case GL_LIGHT_MODEL_AMBIENT:       return 4;
    case GL_LIGHT_MODEL_COLOR_CONTROL: return 1;
    case GL_LIGHT_MODEL_LOCAL_VIEWER:  return 1;
    case GL_LIGHT_MODEL_TWO_SIDE:      return 1;
    default:                           return 0;
  }
}

size_t
materialv(GLenum pname)
{
  switch (pname)
  {
    case GL_AMBIENT:             return 4;
    case GL_DIFFUSE:             return 4;
    case GL_SPECULAR:            return 4;
    case GL_EMISSION:            return 4;
    case GL_SHININESS:           return 1;
    case GL_AMBIENT_AND_DIFFUSE: return 4;
    case GL_COLOR_INDEXES:       return 3;
    default:                     return 0;
  }
}

/* TODO: Review extensions later. */

size_t
texParameterv(GLenum pname)
{
  switch (pname)
  {
    case GL_TEXTURE_MIN_FILTER:   return 1;
    case GL_TEXTURE_MAG_FILTER:   return 1;
    case GL_TEXTURE_MIN_LOD:      return 1;
    case GL_TEXTURE_MAX_LOD:      return 1;
    case GL_TEXTURE_BASE_LEVEL:   return 1;
    case GL_TEXTURE_MAX_LEVEL:    return 1;
    case GL_TEXTURE_WRAP_S:       return 1;
    case GL_TEXTURE_WRAP_T:       return 1;
    case GL_TEXTURE_WRAP_R:       return 1;
    case GL_TEXTURE_BORDER_COLOR: return 4;
    case GL_TEXTURE_PRIORITY:     return 1;
    case GL_TEXTURE_COMPARE_MODE: return 1;
    case GL_TEXTURE_COMPARE_FUNC: return 1;
    case GL_DEPTH_TEXTURE_MODE:   return 1;
    case GL_GENERATE_MIPMAP:      return 1;

    // GL_EXT_texture_filter_anisotropic

    case GL_TEXTURE_MAX_ANISOTROPY_EXT:     return 1;

    // GL_SGIX_shadow

    case GL_TEXTURE_COMPARE_SGIX:           return 1;
    case GL_TEXTURE_COMPARE_OPERATOR_SGIX:  return 1;

    // GL_NV_texture_expand_normal

    case GL_TEXTURE_UNSIGNED_REMAP_MODE_NV: return 1;

    // GL_EXT_texture_swizzle

    case GL_TEXTURE_SWIZZLE_R_EXT:
    case GL_TEXTURE_SWIZZLE_G_EXT:
    case GL_TEXTURE_SWIZZLE_B_EXT:
    case GL_TEXTURE_SWIZZLE_A_EXT:          return 1;

    // GL_NV_texture_shader

    case GL_TEXTURE_BORDER_VALUES_NV:       return 4;

    // GL_EXT_texture_swizzle

    case GL_TEXTURE_SWIZZLE_RGBA_EXT:       return 4;

    default:                                return 0;
  }
}

size_t
texEnvv(GLenum target, GLenum pname)
{
  switch (target)
  {
    case GL_TEXTURE_ENV:
      switch (pname)
      {
        case GL_TEXTURE_ENV_MODE:  return 1;
        case GL_TEXTURE_ENV_COLOR: return 4;
        case GL_COMBINE_RGB:       return 1;
        case GL_COMBINE_ALPHA:     return 1;
        case GL_RGB_SCALE:         return 1;
        case GL_ALPHA_SCALE:       return 1;
        case GL_SRC0_RGB:
        case GL_SRC1_RGB:
        case GL_SRC2_RGB:          return 1;
        case GL_SRC0_ALPHA:
        case GL_SRC1_ALPHA:
        case GL_SRC2_ALPHA:        return 1;
        case GL_OPERAND0_RGB:
        case GL_OPERAND1_RGB:
        case GL_OPERAND2_RGB:      return 1;
        case GL_OPERAND0_ALPHA:
        case GL_OPERAND1_ALPHA:
        case GL_OPERAND2_ALPHA:    return 1;
        default:                   return 0;
      }

    case GL_TEXTURE_FILTER_CONTROL:
      switch (pname)
      {
        case GL_TEXTURE_LOD_BIAS:  return 1;
        default:                   return 0;
      }
  }
  return 0;
}

size_t
texGenv(GLenum pname)
{
  switch (pname)
  {
    case GL_TEXTURE_GEN_MODE: return 1;
    case GL_OBJECT_PLANE:     return 4;
    case GL_EYE_PLANE:        return 4;
    default:                  return 0;
  }
}

size_t
drawElements(GLenum mode, GLsizei count, GLenum type)
{
  /* TODO: Something about client state VBO affects output? */

  switch (mode)
  {
    case GL_POINTS:
    case GL_LINE_STRIP:
    case GL_LINE_LOOP:
    case GL_LINES:
    case GL_TRIANGLE_STRIP:
    case GL_TRIANGLE_FAN:
    case GL_TRIANGLES:
    case GL_QUAD_STRIP:
    case GL_QUADS:
    case GL_POLYGON:         break;

    default: return 0;
  }

  size_t size = count > 0 ? count : 0;

  switch (type)
  {
    case GL_UNSIGNED_BYTE:  size *= sizeof(GLubyte);  break;
    case GL_UNSIGNED_SHORT: size *= sizeof(GLushort); break;
    case GL_UNSIGNED_INT:   size *= sizeof(GLuint);   break;
    default:                                          break;
  }

  return size;
}

size_t
namedString(const GLint namelen, const GLchar *name)
{
  if (namelen > 0)
    return (size_t) namelen;

  return name ? strlen(name) : 0;
}

size_t
namedStringParams(const GLenum pname)
{
  switch (pname)
  {
    case GL_NAMED_STRING_LENGTH_ARB: return 1;
    case GL_NAMED_STRING_TYPE_ARB:   return 1;
    default:                         return 0;
  }
}

}

/* Convert glShaderSource parameters into NULL-terminated array of NUL-terminated strings. */

const GLchar **
shaderSourceStrings(const GLsizei count, const GLchar **string,  const GLint *length)
{
  size_t total;   /* Total size of copy (bytes)      */
  GLchar **tmp;   /* Copy of string array            */
  GLsizei i;      /* Input iterator                  */
  GLchar *j;      /* Output iterator                 */
  size_t  k;      /* Scratch space for string length */

  if (count<=0)
    return NULL;

  /* Determine single-allocation memory size */

  total = 0;
  for (i=0; i<count; ++i)
    total += length ? length[i] : (string[i] ? strlen(string[i]) : 0);
  total += count;                        /* One NUL-terminator per string */
  total *= sizeof(GLchar);
  total += (count + 1)*sizeof(GLchar *); /* One GLchar pointer per string, plus NULL terminator */

  /* Do the allocation */

  tmp = (GLchar **) malloc(total);

  /* Copy the strings */

  j = (GLchar *) (tmp + count + 1);
  for (i=0; i<count; ++i)
  {
    k = length ? length[i] : (string[i] ? strlen(string[i]) : 0);
    tmp[i] = j;
    memcpy(j,string[i],k);
    j += k;
    *(j++) = '\0';
  }

  tmp[count] = NULL;

  assert(((GLchar *) tmp) + total == j);

  return (const GLchar **) tmp;
}

}

REGAL_NAMESPACE_END
