#!/usr/bin/python -B

iffFormulae = {
    'VaPointerOverride' : {
        'entries' : [ 'gl(Vertex|Normal|Color|SecondaryColor|FogCoord|EdgeFlag|TexCoord)Pointer' ],
        'impl' : [ 'rCtx->iff->${m1}Pointer( rCtx, ${arg0plus} );' ],
    },
    'VaClientStateOverride' : {
        'entries' : [ 'gl(Enable|Disable)ClientState' ],
        'impl' : [ 'rCtx->iff->${m1}ClientState( rCtx, ${arg0} );' ],
    },
    'IsEnabled' : {
        'entries' : [ 'glIsEnabled' ],
        'impl' : [
            '{',
            '    GLboolean enabled;',
            '    if ( !rCtx->iff->IsEnabled( rCtx, ${arg0plus}, enabled ) )',
            '        return rCtx->dsp->emuTbl.glIsEnabled( ${arg0plus} );',
            '    return enabled;',
            '}',
        ]
    },
    'ImmShadowVao' : {
        'entries' : [ 'glBindVertexArray.*', ],
        'prefix' : [ 'rCtx->iff->ShadowVao( rCtx, ${arg0} ); ', ],
    },
   'IsVertexArray' : {
        'entries' : [ 'glIsVertexArray(ARB|)' ],
        'impl' : [ 'return rCtx->iff->IsVertexArray( rCtx, ${arg0} );' ],
    },
   'DeleteVertexArrays' : {
        'entries' : [ 'glDeleteVertexArrays(ARB|)' ],
        'impl' : [ 'rCtx->iff->DeleteVertexArrays( rCtx, ${arg0}, ${arg1} );' ],
    },
    'ImmShadowClientActiveTexture' : {
        'entries' : [ 'glClientActiveTexture(|ARB)', ],
        'prefix' : [ 'rCtx->iff->ShadowClientActiveTexture( ${arg0} ); ', ],
    },
    'ImmBegin' : {
        'entries' : [ 'glBegin' ],
        'impl' : [ 'rCtx->iff->Begin( rCtx, ${arg0} );', ],
    },
    'ImmEnd' : {
        'entries' : [ 'glEnd' ],
        'impl' : [ 'rCtx->iff->End( rCtx );', ],
    },
    'ImmAttr' : {
        'entries' : [ 'glVertexAttrib(1|2|3|4)(N|)(b|d|f|i|s|ub|us)(v|)' ],
        'impl' : [ 'rCtx->iff->Attr${m2}<${m1}>( rCtx, ${arg0plus} );', ],
    },
    'ImmFixedAttrf' : {
        'entries' : [ 'gl(SecondaryColor|Color|Normal|FogCoord)(2|3|4)(d|f)(v|)(EXT)?' ],
        'impl' : [ 'rCtx->iff->Attr<${m2}>( rCtx, rCtx->iff->AttrIndex( RFF2A_${m1} ), ${arg0plus} );', ],
    },
    'ImmVertex' : {
        'entries' : [ 'gl(Vertex)(2|3|4)(d|f|i|s)(v|)' ],
        'impl' : [ 'rCtx->iff->Attr<${m2}>( rCtx, rCtx->iff->AttrIndex( RFF2A_${m1} ), ${arg0plus} );', ],
    },
    'ImmFixedAttri' : {
        'entries' : [ 'gl(SecondaryColor|Color|Normal)(2|3|4)(b|i|s|ub|ui|us)(v|)(EXT)?' ],
        'impl' : [ 'rCtx->iff->AttrN<${m2}>( rCtx, rCtx->iff->AttrIndex( RFF2A_${m1} ), ${arg0plus} );', ],
    },
    'ImmTexCoord' : {
        'entries' : [ 'glTexCoord(1|2|3|4)(d|f|i|s)(v|)' ],
        'impl' : [ 'rCtx->iff->Attr<${m1}>( rCtx, rCtx->iff->AttrIndex( RFF2A_TexCoord ), ${arg0plus} );', ],
    },
    'ImmMultiTexCoord' : {
        'entries' : [ 'glMultiTexCoord(1|2|3|4)(d|f|i|s)(v|)' ],
        'impl' : [ 'rCtx->iff->Attr<${m1}>( rCtx, rCtx->iff->AttrIndex( RFF2A_TexCoord, ${arg0} - GL_TEXTURE0 ), ${arg1plus} );', ],
    },
    'ImmRestore' : {
        'entries' : [
            'glBindBuffer',
            'gl(Enable|Disable)ClientState',
            'glVertexAttribPointer(ARB|)',
#           'gl(Vertex|Normal|Color|SecondaryColor|FogCoord|TexCoord)Pointer',
            'glGetVertexAttrib(d|f|i|Pointer)v(ARB|)',
            ],
        'prefix' : [ 'rCtx->iff->RestoreVao( rCtx );' ],
    },



    'FfnShadowARB' : {
        'entries' : [ 'glActiveTexture(|ARB)' ],
        'impl' : [
            'if( ! rCtx->iff->ShadowActiveTexture( ${arg0plus} ) ) {',
            '    rCtx->dsp->emuTbl.glActiveTexture${m1}( ${arg0plus} );',
            '}',
            ],
    },
    'FfnShadeModel' : {
        'entries' : [ 'glShadeModel' ],
        'prefix' : [ 'rCtx->iff->ShadeModel( ${arg0plus} );', ],
    },
    'FfnShadow' : {
        'entries' : [ 'gl(MatrixMode|UseProgram|Enable|Disable)' ],
        'impl' : [
            'if( ! rCtx->iff->Shadow${m1}( ${arg0plus} ) ) {',
            '    rCtx->dsp->emuTbl.gl${m1}( ${arg0plus} );',
            '}',
            ],
    },
    'FfnShadowIndexed' : {
        'entries' : [ 'gl(Enable|Disable)(i|IndexedEXT)' ],
        'impl' : [ 'rCtx->iff->${m1}Indexed( ${arg0plus} );', ],
    },
    'FfnShadowTexBinding' : {
        'entries' : [ 'glBind(Multi|)Texture(EXT|)' ],
        'prefix' : [ 'rCtx->iff->Shadow${m1}TexBinding( ${arg0plus} );', ],
    },
    'FfnShadowDsaTexInfo' : {
        'entries' : [ 'gl(MultiTex|Texture)Image.*EXT' ],
        'prefix' : [ 'rCtx->iff->Shadow${m1}Info( ${arg0}, ${arg1}, ${arg3} );', ],
    },
    'FfnShadowTexInfo' : {
        'entries' : [ 'glTexImage(1|2|3|4)D(Multisample)?(EXT|ARB|SGIS|)' ],
        'prefix' : [ 'rCtx->iff->ShadowTexInfo( ${arg0}, ${arg2} );', ],
    },
    'FfnShadowTexInfo2' : {
        'entries' : [ 'glTexImage(1|2|3|4)DMultisampleCoverageNV' ],
        'prefix' : [ 'rCtx->iff->ShadowTexInfo( ${arg0}, ${arg3} );', ],
    },
    'FfnTexEnv' : {
        'entries' : [ 'gl(Multi|)TexEnv(i|f)(v|)(EXT|)' ],
        'impl' : [ 'rCtx->iff->TexEnv( ${arg0plus} );', ],
    },
    'FfnGetTexEnv' : {
        'entries' : [ 'glGetTexEnv(i|f)(v|)(EXT|)' ],
        'impl' : [ 'rCtx->iff->GetTexEnv( ${arg0plus} );', ],
    },
    'FfnLightMatModel' : {
        'entries' : [ 'gl(Light|Material|GetMaterial|LightModel)(i|f)(v|)' ],
        'impl' : [ 'rCtx->iff->${m1}( ${arg0plus} );', ],
    },
    'FfnColorMaterial' : {
        'entries' : [ 'glColorMaterial' ],
        'impl' : [ 'rCtx->iff->ColorMaterial( ${arg0plus} );', ],
    },
    'FfnTexGen' : {
        'entries' : [ 'glTexGen(i|f|d)(v|)' ],
        'impl' : [ 'rCtx->iff->TexGen( ${arg0plus} );', ],
    },
    'FfnAlphaFunc' : {
        'entries' : [ 'glAlphaFunc' ],
        'impl' : [ 'rCtx->iff->AlphaFunc( ${arg0plus} );', ],
    },
    'FfnClipPlane' : {
        'entries' : [ 'glClipPlane' ],
        'impl' : [ 'rCtx->iff->ClipPlane( ${arg0plus} );', ],
    },
    'FfnFog' : {
        'entries' : [ 'glFog(f|i)(v|)' ],
        'impl' : [ 'rCtx->iff->Fog( ${arg0plus} );', ],
    },
    'FfnGet' : {
        'entries' : [ 'glGet(Integer|Float|Double)v' ],
        'impl' : [
            'rCtx->iff->RestoreVao( rCtx );',
            'if ( ! rCtx->iff->Get( rCtx, ${arg0plus} ) ) {',
            '    rCtx->dsp->emuTbl.glGet${m1}v( ${arg0plus} );',
            '}',
        ],
    },
    'FfnGetMultiTexGenv' : {
        'entries' : [ 'glGetMultiTexGen(d|f|i)vEXT' ],
        'impl' : [
            'rCtx->iff->RestoreVao( rCtx );',
            'if ( ! rCtx->iff->GetMultiTexGenv( rCtx, ${arg0plus} ) ) {',
            '    rCtx->dsp->emuTbl.glGetMultiTexGen${m1}vEXT( ${arg0plus} );',
            '}',
        ],
    },
    'FfnGetTexGenv' : {
        'entries' : [ 'glGetTexGen(d|f|i)v' ],
        'impl' : [
            'rCtx->iff->RestoreVao( rCtx );',
            'if ( ! rCtx->iff->GetTexGenv( rCtx, ${arg0plus} ) ) {',
            '    rCtx->dsp->emuTbl.glGetTexGen${m1}v( ${arg0plus} );',
            '}',
        ],
    },
    # TODO - GL_ARB_base_instance ?
    'FfnPreDraw' : {
        'entries' : [ 'gl(Multi|)Draw(Arrays|Element|Elements)(Instanced|Indirect|BaseVertex|InstancedBaseVertex|Array|)(ARB|EXT|AMD|ATI|APPLE|)' ],
        'prefix' : [ 'rCtx->iff->PreDraw( rCtx );', ],
    },
    'FfnModifyMatrix' : {
        'entries' : [
            'gl(Load|Mult)(Transpose|)(Matrix)(f|d)',
            'gl(LoadIdentity)()()',
            'gl(Rotate|Scale|Translate)()()(f|d)',
            'gl(Ortho|Frustum)()()',
            'gl(Push|Pop)(Matrix)()()',
            'gl(Matrix)(Load|Mult)(Transpose|)(f|d)EXT',
            'gl(Matrix)(LoadIdentity)()()EXT',
            'gl(Matrix)(Rotate|Scale|Translate)()(f|d)EXT',
            'gl(Matrix)(Ortho|Frustum)()()EXT',
            'gl(Matrix)(Push|Pop)()()EXT',
        ],
        'impl' : [ 'rCtx->iff->${m1}${m2}${m3}( ${arg0plus} );' ],
    },
    'EnableArray' : {
        'entries' : [ 'gl(Enable|Disable)VertexAttribArray(ARB|)' ],
        'prefix' : [
            'rCtx->iff->RestoreVao( rCtx );',
            'rCtx->iff->${m1}Array( rCtx, ${arg0} );',
        ],
    },

    'ShaderSource' : {
        'entries' : [ 'glShaderSource', ],
        'impl' : [ 'rCtx->iff->ShaderSource( rCtx, ${arg0plus} );', ],
    },
    'LinkProgram' : {
        'entries' : [ 'glLinkProgram', ],
        'impl' : [ 'rCtx->iff->LinkProgram( rCtx, ${arg0} );', ],
    },
    'CreateShader' : {
        'entries' : [ 'glCreateShader', ],
        'impl' : [ 'return rCtx->iff->CreateShader( rCtx, ${arg0} );', ],
    },
}

