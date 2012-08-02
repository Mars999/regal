#!/usr/bin/python -B

formulae = {
    'GetString' : {
        'entries' : [ 'glGetString' ],
        'impl' : [ 'RegalAssert(rCtx->info);',
                   '// Regal interceptions',
                   'switch (name) {',
                   '  case GL_VENDOR:     return reinterpret_cast<const GLubyte *>(rCtx->info->regalVendor.c_str());',
                   '  case GL_RENDERER:   return reinterpret_cast<const GLubyte *>(rCtx->info->regalRenderer.c_str());',
                   '  case GL_VERSION:    return reinterpret_cast<const GLubyte *>(rCtx->info->regalVersion.c_str());',
                   '  case GL_EXTENSIONS: return reinterpret_cast<const GLubyte *>(rCtx->info->regalExtensions.c_str());',
                   '  default:',
                   '    break;',
                   '}' ]
    }
}
