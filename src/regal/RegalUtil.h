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

#ifndef REGAL_UTIL_H
#define REGAL_UTIL_H

#include <cstdlib>
#include <cstdio>

#include <limits>

// Visual Studio with /W4 complains about unused function
// parameters.

#ifndef UNUSED_PARAMETER
#ifdef _MSC_VER
#define UNUSED_PARAMETER(p) (p)
#else
#define UNUSED_PARAMETER(p)
#endif
#endif

#define REGAL_QUOTE(str) #str
#define REGAL_EQUOTE(str) REGAL_QUOTE(str)

#define REGAL_NAMESPACE_INTERNAL Regal

// REGAL_GLOBAL_BEGIN and REGAL_GLOBAL_END for scoping externals
// such as C, C++ and boost includes.

// VC8, VC9  - C4127: conditional expression is constant in std::list
// VC10      - C4512:
// VC9, VC10 - C4996: 'vsprintf': This function or variable may be unsafe

#ifdef _MSC_VER
# define REGAL_GLOBAL_BEGIN         \
  __pragma(pack(push))              \
  __pragma(pack(8))                 \
  __pragma(warning(push))           \
  __pragma(warning(disable : 4127)) \
  __pragma(warning(disable : 4512)) \
  __pragma(warning(disable : 4996))
# define REGAL_GLOBAL_END           \
  __pragma(warning(pop))            \
  __pragma(pack(pop))
#else
# define REGAL_GLOBAL_BEGIN
# define REGAL_GLOBAL_END
#endif

// REGAL_NAMESPACE_BEGIN and REGAL_NAMESPACE_END for scoping Regal internals

#ifdef _MSC_VER
# define REGAL_NAMESPACE_BEGIN         \
  __pragma(pack(push))                 \
  __pragma(pack(8))                    \
  __pragma(warning(push))              \
  __pragma(warning(disable : 4996))    \
  namespace REGAL_NAMESPACE_INTERNAL   \
  {
# define REGAL_NAMESPACE_END           \
  }                                    \
  __pragma(warning(pop))               \
  __pragma(pack(pop))
#else
# define REGAL_NAMESPACE_BEGIN         \
  namespace REGAL_NAMESPACE_INTERNAL   \
  {
# define REGAL_NAMESPACE_END           \
  }
#endif

// Compile-time configuration
// - Emulation not forced by default
// - All emulation layers enabled by default

#ifndef REGAL_FORCE_EMULATION
#define REGAL_FORCE_EMULATION 0
#endif

#ifndef REGAL_EMU_PPA
#define REGAL_EMU_PPA 1
#endif

#ifndef REGAL_EMU_OBJ
#define REGAL_EMU_OBJ 1
#endif

#ifndef REGAL_EMU_BIN
#define REGAL_EMU_BIN 1
#endif

#ifndef REGAL_EMU_DSA
#define REGAL_EMU_DSA 1
#endif

#ifndef REGAL_EMU_IFF
#define REGAL_EMU_IFF 1
#endif

#ifndef REGAL_EMU_VAO
#define REGAL_EMU_VAO 1
#endif

// AssertFunction depends on Error log, but
// ideally we wouldn't depend on RegalLog.h here

REGAL_GLOBAL_BEGIN

#include <string>

#include "RegalLog.h"

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

inline const char * GetEnv(const char * const varname)
{
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4996)
#endif

    return std::getenv(varname);

#ifdef _MSC_VER
#pragma warning (pop)
#endif
}

//
// RegalCheckGLError
//

#ifdef NDEBUG
#  define RegalCheckGLError( ctx )
#else
#  define RegalCheckGLError( ctx ) RegalCheckForGLErrors( (ctx) )
#endif

//
// RegalAssert
//

#if defined(NDEBUG) && !defined(REGAL_NO_ASSERT)
#  define REGAL_NO_ASSERT
#endif

#ifdef REGAL_NO_ASSERT
#  define RegalAssert( foo )
#else
#  define RegalAssert( foo ) if (!(foo)) ::REGAL_NAMESPACE_INTERNAL::AssertFunction( __FILE__ , __LINE__ , #foo);
#endif

#ifndef REGAL_NO_ASSERT
void AssertFunction(const char *file, const std::size_t line, const char *expr);
#endif

//
//
//

struct RegalContext;

void RegalCheckForGLErrors( RegalContext * ctx );

void *GetProcAddress(const char *entry);

template <typename T>
T *GetProcAddress(T *&f, const char *entry )
{
  f = reinterpret_cast<T *>(GetProcAddress(entry));
  return f;
}

// Lightweight boost::algorithm::string::starts_with

inline bool starts_with(const std::string &input, const std::string &test) { return std::strncmp(input.c_str(),test.c_str(),test.length())==0; }
inline bool starts_with(const std::string &input, const char * const test) { return std::strncmp(input.c_str(),test,        strlen(test) )==0; }

// ToFloat for integer -> float

template <typename T> inline float ToFloat(const bool normalize, const T v ) {
  UNUSED_PARAMETER(normalize); return float(v);
}

template <> inline float ToFloat(const bool normalize, const signed char v ) {
  return normalize ? float(v)/float(std::numeric_limits<signed char>::max()) : float(v);
}

template <> inline float ToFloat(const bool normalize, const unsigned char v ) {
  return normalize ? float(v)/float(std::numeric_limits<unsigned char>::max()) : float(v);
}

template <> inline float ToFloat(const bool normalize, const signed short v ) {
  return normalize ? float(v)/float(std::numeric_limits<signed short>::max()) : float(v);
}

template <> inline float ToFloat(const bool normalize, const unsigned short v ) {
  return normalize ? float(v)/float(std::numeric_limits<unsigned short>::max()) : float(v);
}

template <> inline float ToFloat(const bool normalize, const signed int v ) {
  return normalize ? float(v)/float(std::numeric_limits<signed int>::max()) : float(v);
}

template <> inline float ToFloat(const bool normalize, const unsigned int v ) {
  return normalize ? float(v)/float(std::numeric_limits<unsigned int>::max()) : float(v);
}

template <> inline float ToFloat(const bool normalize, const signed long int v ) {
  return normalize ? float(v)/float(std::numeric_limits<signed long int>::max()) : float(v);
}

template <> inline float ToFloat(const bool normalize, const unsigned long int v ) {
  return normalize ? float(v)/float(std::numeric_limits<unsigned long int>::max()) : float(v);
}

REGAL_NAMESPACE_END

#endif
