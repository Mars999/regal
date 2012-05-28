// dllmain.cpp : Defines the entry point for the DLL application.

#include "pch.h" /* For MS precompiled header support */

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#endif

REGAL_GLOBAL_END

#ifdef _WIN32

REGAL_NAMESPACE_BEGIN

extern void *RegalGetProcAddress(const char *entry);

REGAL_NAMESPACE_END

BOOL APIENTRY
DllMain
(
  HMODULE module,
  DWORD   reason,
  LPVOID  reserved
)
{
  UNUSED_PARAMETER(module);
  UNUSED_PARAMETER(reserved);

  switch (reason)
  {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}

#endif
