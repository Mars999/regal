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

// Visual Studio with /W4 complains about unused function
// parameters.

#ifndef UNUSED_PARAMETER
#ifdef _MSC_VER
#define UNUSED_PARAMETER(p) (p)
#else
#define UNUSED_PARAMETER(p)
#endif
#endif

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

// RegalAssertFunction depends on Error log, but
// ideally we wouldn't depend on RegalLog.h here

REGAL_GLOBAL_BEGIN

#include "RegalLog.h"

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

inline char* RegalGetEnv(const char* varname)
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

#ifdef NDEBUG
#define RegalAssert( foo )
#define RegalCheckGLError( ctx )
#else
#define RegalAssert( foo ) RegalAssertFunction( __FILE__ , __LINE__ , #foo, (foo) )
#define RegalCheckGLError( ctx ) RegalCheckForGLErrors( (ctx) )
#endif

template <typename T>
inline void RegalAssertFunction( const char * file, int line, const char * expr, T assertion )
{
    if( assertion ) {
        return;
    }
    Error( "Regal Assertion Failed: ", file, " ", line, ": ", expr );
}

struct RegalContext;

void RegalCheckForGLErrors( RegalContext * ctx );

void * RegalGetProcAddress( const char * entry );
template <typename T> void RegalGetProcAddress( T * &f, const char * entry )
{
    f = ( T * )RegalGetProcAddress( entry );
}

// Lightweight boost::algorithm::string::starts_with

inline bool starts_with(const std::string &input, const std::string &test) { return std::strncmp(input.c_str(),test.c_str(),test.length())==0; }
inline bool starts_with(const std::string &input, const char * const test) { return std::strncmp(input.c_str(),test,        strlen(test) )==0; }

REGAL_NAMESPACE_END

#endif
