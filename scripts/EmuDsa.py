#!/usr/bin/python -B

dsaFormulae = {
    'SelectorGetCommands' : {
        'entries' : [ 'glGet(Boolean|Integer|Float|Double)v' ],
        'prefix' : [ 'rCtx->dsa->RestoreGet( rCtx, ${arg0} );' ],
    },
    'DsaGetCommands1' : {
        'entries' : [ 'glGet(Float|Double)(Indexed|i_)v(EXT|)' ],
        'impl' : [
            'if ( ! rCtx->dsa->GetIndexedv( rCtx, ${arg0}, ${arg1}, ${arg2} ) ) {',
            '    rCtx->dsp->emuTbl.glGet${m1}${m2}v${m3}( ${arg0}, ${arg1}, ${arg2} );',
            '}',
        ],
    },
    'DsaGetCommands2' : {
        'entries' : [ 'glGetPointerIndexedvEXT' ],
        'impl' : [
            '// if ( ! rCtx->dsa->GetIndexedv( rCtx, ${arg0}, ${arg1}, ${arg2} ) ) {',
            '//     rCtx->dsp->emuTbl.glGetPointerIndexedvEXT( ${arg0}, ${arg1}, ${arg2} );',
            '// }',
        ],
    },
    'DsaGetCommands3' : {
        'entries' : [ 'glGetFramebufferParameterivEXT' ],
        'impl' : [
            'rCtx->dsa->DsaFramebuffer( rCtx, GL_FRAMEBUFFER, ${arg0} );',
            'rCtx->dsp->emuTbl.glGetIntegerv( ${arg1plus} );',
        ],
    },
    'SelectorIsEnabled' : {
        'entries' : [ 'glIsEnabled' ],
        'prefix' : [ 'rCtx->dsa->RestoreIsEnabled( rCtx, ${arg0} );']
    },
    'DsaIsEnabled' : {
        'entries' : [ 'glIsEnabled(Indexed|i)EXT' ],
        'impl' : [
            'GLboolean ret;',
            'ret = rCtx->dsa->IsEnabledIndexed( rCtx, ${arg0}, ${arg1} );',
            'return ret;',
            ],
    },
    'SelectorMatrixCommands' : {
        'entries' : [
            'gl(Load|Mult)(Transpose|)Matrix(f|d)',
            'glLoadIdentity',
            'gl(Rotate|Scale|Translate)(f|d)',
            'gl(Push|Pop)Matrix',
        ],
        'prefix' : [ 'rCtx->dsa->RestoreMatrixMode( rCtx );' ],
    },
    'MatrixMode' : {
        'entries' : [ 'glMatrixMode' ],
        'impl' : [
            'if( false == rCtx->dsa->ShadowMatrixMode( ${arg0} ) ) {',
            '    rCtx->dsp->emuTbl.glMatrixMode( ${arg0} );',
            '}',
        ],
    },
    'MatrixLoadMultStack' : {
        'entries' : [
            'glMatrix(Load|Mult)(Transpose|)(f|d)EXT',
            'glMatrix(Push|Pop)()()EXT',
        ],
        'impl' : [
            'rCtx->dsa->DsaMatrixMode( rCtx, ${arg0} );',
            'rCtx->dsp->emuTbl.gl${m1}${m2}Matrix${m3}( ${arg1plus} );',
        ],
    },
    'MatrixTransform' : {
        'entries' : [
            'glMatrix(LoadIdentity|Ortho|Frustum)()EXT',
            'glMatrix(Rotate|Scale|Translate)(f|d)EXT',
        ],
        'impl' : [
            'rCtx->dsa->DsaMatrixMode( rCtx, ${arg0} );',
            'rCtx->dsp->emuTbl.gl${m1}${m2}( ${arg1plus} );',
        ],
    },

    'ClientActiveTexture' : {
        'entries' : [ 'glClientActiveTexture' ],
        'impl' : [
            'if( false == rCtx->dsa->ShadowClientActiveTexture( ${arg0} ) ) {',
            '    rCtx->dsp->emuTbl.glClientActiveTexture( ${arg0} );',
            '}',
        ],
    },
    'ClientActiveCommands' : {
        'entries' : [
            'gl(Enable|Disable)ClientState',
            'glTexCoordPointer',
        ],
        'prefix' : [
          'rCtx->dsa->RestoreClientActiveTexture( rCtx );',
          'rCtx->dsa->RestoreBuffer( rCtx );',
        ],
    },
    'ClientIndexed' : {
        'entries' : [ 'gl(Enable|Disable)ClientState(Indexed|i)EXT' ],
        'impl' : [
            'rCtx->dsa->DsaClientActiveTexture( rCtx, ${arg1} + GL_TEXTURE0 );',
            'rCtx->dsp->emuTbl.gl${m1}ClientState( ${arg0} );',
        ],
    },
    'ClientTexCoords' : {
        'entries' : [ 'glMultiTexCoordPointerEXT' ],
        'impl' : [
            'rCtx->dsa->DsaClientActiveTexture( rCtx, ${arg0} );',
            'rCtx->dsp->emuTbl.glTexCoordPointer( ${arg1plus} );',
        ],
    },
    'EnableIndexed' : {
        'entries' : [ 'gl(Enable|Disable)IndexedEXT'],
        'impl' : [
            'rCtx->dsa->DsaActiveTexture( rCtx, ${arg1} + GL_TEXTURE0 );',
            'rCtx->dsp->emuTbl.gl${m1}( ${arg0} );',
        ],
    },
    'ActiveTexture' : {
        'entries' : [ 'glActiveTexture' ],
        'impl' : [
            'if( false == rCtx->dsa->ShadowActiveTexture( ${arg0} ) ) {',
            '    rCtx->dsp->emuTbl.glActiveTexture( ${arg0} );',
            '}',
        ],
    },
    'TexCommands' : {
        'entries' : [
            'gl(Get|)Tex(Env|Parameter)(i|iv|f|fv)',
            'gl(Get|)TexParameter(Iiv|Iuiv)'
            'gl(Copy|Compressed|Get|)Tex(Sub|)Image(1|2|3)D',
            'glTex(Buffer|Renderbuffer)(NV|)',
            'glGenerateMipmap(ARB|EXT|)'
        ],
        'prefix' : [
            'rCtx->dsa->RestoreTexture( rCtx );',
            'rCtx->dsa->RestoreActiveTexture( rCtx );',
        ],
    },
    'TexCommands2' : {
        'entries' : [ 'glTexGen(i|iv|f|fv)', ],
        'prefix' : [ 'rCtx->dsa->RestoreActiveTexture( rCtx );', ],
    },
    'TexCommands3' : {
        'entries' : [ 'gl(Enable|Disable)', ], # check that it's a texture target!
        'prefix' : [ 'rCtx->dsa->RestoreActiveTexture( rCtx );', ],
    },
    'MultiActiveTexCommands' : {
        'entries' : [
            'gl(Get|)MultiTex(Env|Gen|Parameter|LevelParameter)(i|iv|f|fv|d|dv)EXT',
            'gl(Get|)MultiTex(Parameter|LevelParameter)(Iiv|Iuiv)EXT',
            'gl(Copy|Compressed|)MultiTex(Image|SubImage)(1D|2D|3D)EXT',
            'gl(Get|GetCompressed)MultiTex(Image|SubImage)()EXT',
            'gl()MultiTex(Buffer|Renderbuffer)()EXT',
            'gl(Generate)MultiTex(Mipmap)()EXT',
        ],
        'subst' : {
            'nondsa' : {
                '.*Renderbuffer.*' : 'glTexRenderbufferNV',
                'glGenerate.*' : 'glGenerateMipmap',
                'default' : 'gl${m1}Tex${m2}${m3}',
            },
        },
        'impl' : [
            'rCtx->dsa->DsaActiveTexture( rCtx, ${arg0} );',
            'rCtx->dsp->emuTbl.${nondsa}( ${arg1plus} );',
        ],
    },
    'BindTexture' : {
        'entries' : [ 'glBindTexture' ],
        'impl' : [
            'if( false == rCtx->dsa->ShadowTexture( ${arg0}, ${arg1} ) ) {',
            '    rCtx->dsp->emuTbl.glBindTexture( ${arg0}, ${arg1} );',
            '}',
        ],
    },
    'BindMultiTexture' : {
        'entries' : [ 'glBindMultiTextureEXT' ],
        'impl' : [
            'rCtx->dsa->DsaActiveTexture( rCtx, ${arg0} );',
            'rCtx->dsa->ShadowDsaTexture( ${arg1plus} );',
            'rCtx->dsp->emuTbl.glBindTexture( ${arg1plus} );',
        ],
    },
    'BoundTextureCommands' : {
        'entries' : [
            'gl()Texture(Parameter)(i|iv|f|fv|Iiv|Iuiv)EXT',
            'gl(Get)Texture(Parameter|LevelParameter)(i|iv|f|fv|Iiv|Iuiv)EXT',
            'gl(Get|GetCompressed)Texture(Image)()EXT',
            'gl(Copy|Compressed|)Texture(Image|SubImage)(1D|2D|3D)EXT',
            'gl()Texture(Buffer|Renderbuffer)()EXT',
            'gl(Generate)Texture(Mipmap)()EXT',
        ],
        'subst' : {
            'nondsa' : {
                '.*Renderbuffer.*' : 'glTexRenderbufferNV',
                'glGenerate.*' : 'glGenerateMipmap',
                'default' : 'gl${m1}Tex${m2}${m3}',
            },
        },
        'impl' : [
            'rCtx->dsa->DsaTexture( rCtx, ${arg1}, ${arg0} );',
            'rCtx->dsp->emuTbl.${nondsa}( ${arg1plus} );',
        ],
    },

    'UseProgram' : {
        'entries' : [ 'glUseProgram' ],
        'impl' : [
            'if( false == rCtx->dsa->ShadowGlslProgram( ${arg0} ) ) {',
            '    rCtx->dsp->emuTbl.glUseProgram( ${arg0} );',
            '}',
        ],
    },
    'SelectorProgramCommands' : {
        'entries' : [
            'glUniform(1|2|3|4)(i|f|ui|d)(v|)',
            'glUniformMatrix(2|3|4)(x2|x3|x4|)(fv|dv)',
        ],
        'prefix' : [ 'rCtx->dsa->RestoreGlslProgram( rCtx );' ],
    },
    'DsaProgramCommands' : {
        'entries' : [
            'glProgramUniform()(1|2|3|4)()(i|iv|f|fv|d|dv|ui|uiv)EXT',
            'glProgramUniform(Matrix)(2|3|4)(x2|x3|x4|)(fv|dv)EXT',
        ],
        'impl' : [
            'rCtx->dsa->DsaGlslProgram( rCtx, ${arg0});',
            'rCtx->dsp->emuTbl.glUniform${m1}${m2}${m3}${m4}( ${arg1plus} );',
        ],
    },

    'BindAsmProgram' : {
        'entries' : [ 'glBindProgramARB' ],
        'impl' : [
            'if( false == rCtx->dsa->ShadowAsmProgram( ${arg0}, ${arg1} ) ) {',
            '    rCtx->dsp->emuTbl.glBindProgramARB( ${arg0}, ${arg1} );',
            '}',
        ],
    },
    'AsmProgram' : {
        'entries' : [
            'gl(Get|)Program(Env|Local)Parameter(.*)(ARB|NV)',
            'gl(Get|)Program(String)(EXT)',
        ],
        'prefix' : [ 'rCtx->dsa->RestoreAsmProgram( rCtx, ${arg0} );' ],
    },
    'DsaAsmProgram' : {
        'entries' : [
            'gl(Get|)NamedProgram(Env|Local)Parameter(.*)(EXT)',
            'gl(Get|)NamedProgram(String|iv)()(EXT)',
        ],
        'subst' : {
            'nondsa' : {
                '.*Parameter4[df]v?EXT' : 'gl${m1}Program${m2}Parameter${m3}ARB',
                '.*Parameter[df]vEXT' : 'gl${m1}Program${m2}Parameter${m3}ARB',
                '.*Parameter(s|)I[4uiv]+EXT' : 'gl${m1}Program${m2}Parameter${m3}NV',
                '.*Program(String|iv).*' : 'gl${m1}Program${m2}ARB',
                'default' : 'gl${m1}Program${m2}Parameter${m3}EXT',
            },
        },
        'impl' : [
            'rCtx->dsa->DsaAsmProgram( rCtx, ${arg1}, ${arg0});',
            'rCtx->dsp->emuTbl.${nondsa}( ${arg1plus} );',
        ],
    },

    'BindFramebuffer' : {
        'entries' : [ 'glBindFramebuffer' ],
        'impl' : [
            'if( false == rCtx->dsa->ShadowFramebuffer( ${arg0}, ${arg1} ) ) {',
            '    rCtx->dsp->emuTbl.glBindFramebuffer( ${arg0}, ${arg1} );',
            '}',
        ],
    },
    'SelectorFramebufferCommands' : {
        'entries' : [
            'glRenderbufferStorage(Multisample|MultisampleCoverage|)(ARB|EXT|NV|)',
            'glFramebufferTexture(1D|2D|3D|Layer|Face|)(ARB|EXT|)',
            'glFramebufferRenderbuffer(ARB|EXT|)',
            'glDrawBuffer(s|)(ARB|EXT|NV|)'
            'glGet(Renderbuffer|FramebufferAttachment)Parameteriv(ARB|EXT|)',
        ],
        'prefix' : [ 'rCtx->dsa->RestoreFramebuffer( rCtx );' ],
    },
    'SelectorFramebufferCommands2' : {
        'entries' : [
            'gl()Named(RenderbufferStorage)(Multisample|MultisampleCoverage|)EXT',
            'gl()Named(FramebufferTexture)(1D|2D|3D|Layer|Face|)EXT',
            'gl()Named(FramebufferRenderbuffer)()EXT',
            'gl(Get)Named(Renderbuffer|FramebufferAttachment)(Parameteriv)EXT',
        ],
        'subst' : {
            'nondsa' : {
                '.*CoverageEXT' : 'gl${m1}${m2}${m3}NV',
                '.*MultisampleEXT' : 'gl${m1}${m2}${m3}EXT',
                'default' : 'gl${m1}${m2}${m3}',
            },
        },
        'impl' : [
            'rCtx->dsa->DsaFramebuffer( rCtx, GL_FRAMEBUFFER, ${arg0});',
            'rCtx->dsp->emuTbl.${nondsa}( GL_FRAMEBUFFER, ${arg1plus} );',
        ],
    },
    'SelectorFramebufferCommands3' : {
        'entries' : [ 'glFramebuffer(DrawBuffer|ReadBuffer)(s|)EXT' ],
        'impl' : [
            'rCtx->dsa->DsaFramebuffer( rCtx, GL_FRAMEBUFFER, ${arg0});',
            'rCtx->dsp->emuTbl.gl${m1}${m2}( ${arg1plus} );',
        ],
    },
    'SelectorFramebufferCommands4' : {
        'entries' : [ 'glCheckNamedFramebufferStatusEXT' ],
        'impl' : [
            'rCtx->dsa->DsaFramebuffer( rCtx, GL_FRAMEBUFFER, ${arg0});',
            'return rCtx->dsp->emuTbl.glCheckFramebufferStatus( ${arg1plus} );',
        ],
    },
    'ClientAttribDefault' : {
        'entries' : ['glClientAttribDefaultEXT'],
        'impl' : [ 'rCtx->dsa->ClientAttribDefault( rCtx, ${arg0} );' ],
    },
    'PushClientAttribDefault' : {
        'entries' : ['glPushClientAttribDefaultEXT'],
        'impl' : [
            'rCtx->dsp->emuTbl.glPushClientAttrib( ${arg0} );',
            'rCtx->dsa->ClientAttribDefault( rCtx, ${arg0} );',
        ],
    },
    'BindVertexArray' : {
        'entries' : [ 'glBindVertexArray' ],
        'impl' : [
            'if( false == rCtx->dsa->ShadowVao( ${arg0} ) ) {',
            '    rCtx->dsp->emuTbl.glBindVertexArray( ${arg0} );',
            '}',
        ],
    },
    # TODO - GL_ARB_base_instance ?
    'RestoreEverything' : {
        'entries' : [ 'glBegin', 'gl(Multi|)Draw(Arrays|Element|Elements)(Instanced|Indirect|BaseVertex|InstancedBaseVertex|Array|)(ARB|EXT|AMD|ATI|APPLE|)' ],
        'prefix' : [  'rCtx->dsa->Restore( rCtx );' ],
    },
    'BindBuffer' : {
        'entries' : [ 'glBindBuffer' ],
        'impl' : [
            'if( false == rCtx->dsa->ShadowBuffer( ${arg0}, ${arg1} ) ) {',
            '    rCtx->dsp->emuTbl.glBindBuffer( ${arg0}, ${arg1} );',
            '}',
        ],
    },
    'SelectorBufferCommands' : {
        'entries' : [
            'gl(Get|Copy|)Buffer(Sub|)Data',
            'gl(FlushMapped|Map|Unmap)Buffer(Range|)(ARB|EXT|)',
            'glGetBuffer(Parameteriv|Pointerv)',
            'gl(Vertex|Normal|Color|SecondaryColor)Pointer'
        ],
        'prefix' : [ 'rCtx->dsa->RestoreBuffer( rCtx );' ],
    },
    'DsaBufferCommands' : {
        'entries' : [
            'gl(Get|)Named(Copy|)Buffer(Data|SubData)EXT',
            'gl(FlushMapped)Named()Buffer(Range)EXT',
            'gl(Get)Named()Buffer(Parameteriv|Pointerv)EXT',
        ],
        'impl' : [
            'rCtx->dsa->DsaBuffer( rCtx, ${arg0});',
            'rCtx->dsp->emuTbl.gl${m1}${m2}Buffer${m3}( GL_ARRAY_BUFFER, ${arg1plus} );',
        ],
    },
    'DsaBufferCommands2' : {
        'entries' : [ 'gl(Map)NamedBuffer(Range|)EXT' ],
        'impl' : [
            'rCtx->dsa->DsaBuffer( rCtx, ${arg0});',
            'return rCtx->dsp->emuTbl.gl${m1}Buffer${m2}( GL_ARRAY_BUFFER, ${arg1plus} );',
        ],
    },
    'DsaBufferCommands3' : {
        'entries' : [ 'glUnmapNamedBufferEXT' ],
        'impl' : [
            'rCtx->dsa->DsaBuffer( rCtx, ${arg0});',
            'return rCtx->dsp->emuTbl.glUnmapBuffer( GL_ARRAY_BUFFER );',
        ],
    },
    'DsaBufferPointerCommands' : {
        'entries' : [ 'glVertexArray(Vertex|Color|EdgeFlag|Index|Normal|TexCoord|MultiTexCoord|FogCoord|SecondaryColor|VertexAttrib|VertexAttribI)OffsetEXT' ],
        'impl' : [
            'rCtx->dsa->DsaVao( rCtx, ${arg0} );'
            'rCtx->dsa->DsaBuffer( rCtx, ${arg1} );',
            'rCtx->dsp->emuTbl.gl${m1}Pointer( ${arg2plus} );',
        ],
    }
}

