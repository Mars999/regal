// dllmain.cpp : Defines the entry point for the DLL application.

#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <stdio.h>

extern void *RegalGetProcAddress(const char *entry);

void RegalOutputWin32( const char *fmt, ... ) {
	char str[1<<14];
	va_list args;
	va_start( args, fmt );
	vsprintf_s( str, sizeof( str ), fmt, args );
	va_end( args );
	OutputDebugStringA( str ); 
	fprintf( stderr, "%s", str );
}

BOOL APIENTRY
DllMain
(
  HMODULE module,
  DWORD   reason,
  LPVOID  reserved
)
{
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
