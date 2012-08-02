#!/usr/bin/python -B

formulae = {
    'GetExtension' : {
        'entries' : [ 'glGetExtensionREGAL' ],
        'impl' : [ 'RegalAssert(rCtx->info);',
                   '// Emulate GL_REGAL_extension_query, if necessary.',
                   'if (!rCtx->info->gl_regal_extension_query)',
                   '  return rCtx->info->getExtension(ext) ? GL_TRUE : GL_FALSE;' ]
    },
    'IsSupported' : {
        'entries' : [ 'glIsSupportedREGAL' ],
        'impl' : [ 'RegalAssert(rCtx->info);',
                   '// Emulate GL_REGAL_extension_query, if necessary.',
                   'if (!rCtx->info->gl_regal_extension_query)',
                   '  return rCtx->info->isSupported(ext) ? GL_TRUE : GL_FALSE;' ]
    },
}
