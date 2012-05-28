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

#include <cstdio>
#include <cstdarg>
using namespace std;

#include <boost/print/print_string.hpp>
using boost::print::print_string;

#include "RegalLog.h"
#include "RegalMarker.h"
#include "RegalContext.h"
#include "RegalPrivate.h"

#ifndef REGAL_SYS_WGL
#include <pthread.h>
#endif

// Otherwise we'd need to #include <windows.h>

#ifdef REGAL_SYS_WGL
extern "C"
{
  __declspec(dllimport) void __stdcall OutputDebugStringA( __in_opt const char* lpOutputString);
}
#endif

#if REGAL_SYS_ANDROID
#include <android/log.h>
#endif

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

namespace Logging {

  bool enableError    = true;
  bool enableWarning  = true;
  bool enableInfo     = true;
  bool enableRegal    = false;
  bool enableOpenGL   = false;
  bool enableInternal = false;

  inline size_t indent()
  {
    // For OSX we need avoid GET_REGAL_CONTEXT implicitly
    // trying to create a RegalContext and triggering more
    // (recursive) logging.

#ifndef REGAL_SYS_WGL
    if (!regalPrivateCurrentContextKey || !pthread_getspecific(regalPrivateCurrentContextKey))
      return 0;
#endif

    RegalContext *rCtx = GET_REGAL_CONTEXT();
    return rCtx && rCtx->marker ? rCtx->marker->indent() : 0;
  }

  inline string message(const char *prefix, const string &str)
  {
    // TODO - prefix and indent each line of multi-line str
    return print_string(prefix ? prefix : "", string(indent(),' '), str, '\n');
  }

#if defined(REGAL_SYS_WGL)

  void Output(const char *prefix, const string &str)
  {
    if (str.length())
    {
      string m = message(prefix,str);
      OutputDebugStringA( m.c_str() );
      fprintf( stderr, "%s", m.c_str() );
      fflush( stderr );
    }
  }

#elif defined(REGAL_SYS_ANDROID)

#define  LOG_TAG    "Regal"

  // ANDROID_LOG_INFO
  // ANDROID_LOG_WARN
  // ANDROID_LOG_ERROR

  void Output(const char *prefix, const string &str)
  {
    if (str.length())
      __android_log_print(ANDROID_LOG_INFO, LOG_TAG, message(prefix,str).c_str());
  }

#else

  void Output(const char *prefix, const string &str)
  {
    if (str.length())
      printf("%s",message(prefix,str).c_str());
  }

#endif

}

REGAL_NAMESPACE_END
