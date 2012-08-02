#!/usr/bin/python -B

objFormulae = {
    'Buffers' : {
        'entries' : [ 'gl(GenBuffers|DeleteBuffers|BindBuffer)(ARB|)' ],
        'impl' : [ 'rCtx->obj->${m1}( rCtx, ${arg0plus} );', ],
    },
    'VAOs' : {
        'entries' : [ 'gl(GenVertexArrays|DeleteVertexArrays|BindVertexArray|IsVertexArray)(ARB|)' ],
        'impl' : [ 'rCtx->obj->${m1}( rCtx, ${arg0plus} );', ],
    },
    'IsObj' : {
        'entries' : [ 'glIs(Buffer|VertexArray)(ARB|)' ],
        'impl' : [ 'return rCtx->obj->Is${m1}( rCtx, ${arg0plus} );', ],
    },
}
