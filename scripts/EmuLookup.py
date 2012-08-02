#!/usr/bin/python -B

formulae = {
    'wglGetProcAddress' : {
        'entries' : [ 'wglGetProcAddress' ],
        'impl' : [
                  'RegalAssert(dispatchTableGlobal.wglGetProcAddress);',
                  'PROC drvproc = ret = dispatchTableGlobal.wglGetProcAddress(lpszProc);',
                  'if (!ret)',
                  '  return NULL;',
                  'ret = Lookup::gl_Lookup<PROC>(lpszProc);',
                  'if (ret)',
                  '  return ret;'
                   ],
        'suffix' : [
                  'size_t off = Lookup::wgl_LookupOffset(lpszProc);',
                  '((void **)(&dispatchTableGlobal))[off] = (void *)drvproc;',
                  'ret = Lookup::wgl_Lookup<PROC>(lpszProc);'
                   ]
    },

    'glXGetProcAddress' : {
        'entries' : [ 'glXGetProcAddress','glXGetProcAddressARB' ],
        'impl' : [
                  'ret = Lookup::gl_Lookup<void *>(reinterpret_cast<const char *>(procName));',
                  'if (ret)',
                  '  return ret;',
                  'ret = Lookup::glx_Lookup<void *>(reinterpret_cast<const char *>(procName));',
                  'if (ret)',
                  '  return ret;',
                   ]
    }
}
