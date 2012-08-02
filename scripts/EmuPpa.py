#!/usr/bin/python -B

ppaFormulae = {
  'PushAtrrib' : {
    'entries'  : [ 'glPushAttrib' ],
    'impl'     : [ 'rCtx->ppa->PushAttrib( rCtx, ${arg0} );', ],
  },
  'PopAttrib' : {
    'entries' : [ 'glPopAttrib' ],
    'impl'    : [ 'rCtx->ppa->PopAttrib( rCtx );', ],
  },
  'Enable'    : {
    'entries' : [ 'gl(Enable|Disable)' ],
    'prefix'  : [ 'rCtx->ppa->${m1}( ${arg0plus} );', ],
  },
  'TrackDepth' : {
    'entries'    : [ '(glClearDepth|glDepthFunc|glDepthMask)' ],
    'prefix'     : [ 'rCtx->ppa->${m1}( ${arg0plus} );', ],
  },
  'TrackStencil' : {
    'entries'    : [ '(glClearStencil|glStencilFunc|glStencilFuncSeparate|glStencilMask|glStencilMaskSeparate|glStencilOp|glStencilOpSeparate)' ],
    'prefix'     : [ 'rCtx->ppa->${m1}( ${arg0plus} );', ],
  },
  'TrackPolygon' : {
    'entries'    : [ '(glCullFace|glFrontFace|glPolygonMode|glPolygonOffset)' ],
    'prefix'     : [ 'rCtx->ppa->${m1}( ${arg0plus} );', ],
  },
}
