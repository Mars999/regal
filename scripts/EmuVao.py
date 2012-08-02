#!/usr/bin/python -B

vaoFormulae = {
    'Begin' : {
        'entries' : [ 'glBegin' ],
        'prefix' : [ 'rCtx->vao->Begin( rCtx, ${arg0} );' ],
    },
    'End' : {
        'entries' : [ 'glEnd' ],
        'prefix' : [ 'rCtx->vao->End( rCtx );' ],
    },
    # TODO - GL_ARB_base_instance ?
    'Validate' : {
        'entries' : [ 'gl(Multi|)Draw(Arrays|Element|Elements)(Instanced|Indirect|BaseVertex|InstancedBaseVertex|Array|)(ARB|EXT|AMD|ATI|APPLE|)' ],
        'prefix' : [  '// rCtx->vao->Validate( rCtx );' ],
    },
    'BufferBinding' : {
        'entries' : [ 'glBindBuffer(ARB|)' ],
        'prefix' : [ 'rCtx->vao->ShadowBufferBinding( ${arg0}, ${arg1} );' ],
    },
    'BindVertexArray' : {
        'entries' : [ 'glBindVertexArray(ARB|)' ],
        'impl' : [ 'rCtx->vao->BindVertexArray( rCtx, ${arg0} );' ],
    },
   'GenVertexArrays' : {
        'entries' : [ 'glGenVertexArrays(ARB|)' ],
        'impl' : [ 'rCtx->vao->GenVertexArrays( ${arg0}, ${arg1} );' ],
    },
   'DeleteVertexArrays' : {
        'entries' : [ 'glDeleteVertexArrays(ARB|)' ],
        'impl' : [ 'rCtx->vao->DeleteVertexArrays( ${arg0}, ${arg1} );' ],
    },
   'IsVertexArray' : {
        'entries' : [ 'glIsVertexArray(ARB|)' ],
        'impl' : [ 'return rCtx->vao->IsVertexArray( ${arg0} );' ],
    },
   'EnableVertexAttribArray' : {
        'entries' : [ 'gl(Enable|Disable)VertexAttribArray(ARB|)' ],
        'impl' : [ 'return rCtx->vao->${m1}VertexAttribArray( rCtx, ${arg0} );' ],
    },
    'EnableDisableClientState' : {
        'entries' : [ 'gl(Enable|Disable)ClientState' ],
        'impl' : [ 'rCtx->vao->${m1}ClientState( rCtx, ${arg0} );' ],
    },
   'AttribPointer' : {
        'entries' : [ 'glVertexAttribPointer(ARB|)' ],
        'impl' : [ 'return rCtx->vao->AttribPointer( rCtx, ${arg0}, ${arg1plus} );' ],
    },
    'GetAttrib' : {
        'entries' : [ 'glGetVertexAttrib(d|f|i|Pointer)v(ARB|)' ],
        'impl' : [ 'rCtx->vao->GetAttrib( ${arg0}, ${arg1}, ${arg2} );' ],
    },
    'GetVertexAttribPointerv' : {
        'entries' : [ 'glGetVertexAttribPointerv(ARB|)' ],
        'impl' : [
            'if ( !rCtx->vao->GetVertexAttribPointerv( ${arg0}, ${arg1plus} ) ) {',
            '   rCtx->dsp->emuTbl.glGetVertexAttribPointerv${m1}( ${arg0}, ${arg1plus} );',
            '}',
        ]
    },
    'Get' : {
        'entries' : [ 'glGet(Boolean|Double|Float|Integer|Integer64)v' ],
        'impl' : [
            'if( !rCtx->vao->Get( ${arg0}, ${arg1} ) ) {',
            '   rCtx->dsp->emuTbl.glGet${m1}v( ${arg0}, ${arg1} );',
            '}',
        ]
    },
    'InterleavedArrays' : {
        'entries' : [ 'glInterleavedArrays' ],
        'impl' : [ 'rCtx->vao->InterleavedArrays( rCtx, ${arg0}, ${arg1plus} );' ],
    },
    'Pointer4' : {
        'entries' : [ 'gl(Color|SecondaryColor|TexCoord|Vertex)Pointer' ],
        'impl' : [ 'rCtx->vao->${m1}Pointer( rCtx, ${arg0}, ${arg1}, ${arg2}, ${arg3} );' ],
    },
    'Pointer3' : {
        'entries' : [ 'gl(FogCoord|Normal)Pointer' ],
        'impl' : [ 'rCtx->vao->${m1}Pointer( rCtx, ${arg0}, ${arg1}, ${arg2} );' ],
    },
    'ClientActiveTexture' : {
        'entries' : [ 'glClientActiveTexture' ],
        'prefix' : [ 'rCtx->vao->ClientActiveTexture( rCtx, ${arg0} );' ],
    },
}
