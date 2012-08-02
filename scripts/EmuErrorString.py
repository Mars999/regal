#!/usr/bin/python -B

formulae = {
    'ErrorString' : {
        'entries' : [ 'glErrorStringREGAL' ],
        'impl' : [ 'RegalAssert(rCtx->info);',
                   '// Emulate GL_REGAL_error_string, if necessary.',
                   'if (!rCtx->info->gl_regal_error_string)',
                   '  return Token::GLerrorToString(error);' ]
    }
}
