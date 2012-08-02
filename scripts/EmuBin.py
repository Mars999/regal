#!/usr/bin/python -B

binFormulae = {
    'ShaderBinary' : {
        'entries' : [ 'glShaderBinary(ARB|)' ],
        'impl' : [ 'rCtx->bin->ShaderBinary( rCtx, ${arg0plus} );', ],
    }
}
