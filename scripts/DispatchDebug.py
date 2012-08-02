#!/usr/bin/python -B

debugDispatchFormulae = {
    'MatrixMode' : {
        'entries' : [ 'glMatrixMode' ],
        'prefix' : [ 'rCtx->dbg->MatrixMode( rCtx, ${arg0plus} );', ],
    },
    'ClientActiveTexture' : {
        'entries' : [ 'gl(Client|)(ActiveTexture)' ],
        'prefix' : [ 'rCtx->dbg->${m1}${m2}( rCtx, ${arg0plus} );', ],
    },
}

