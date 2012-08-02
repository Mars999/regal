#!/usr/bin/python -B

formulae = {
    'Insert' : {
        'entries' : [ 'glInsertEventMarkerEXT' ],
        'impl' : [ 'rCtx->marker->InsertEventMarker( rCtx, ${arg0plus} );',
                   'RegalAssert(rCtx->info);',
                   'if (!rCtx->info->gl_ext_debug_marker) return;' ]
    },
    'Push' : {
        'entries' : [ 'glPushGroupMarkerEXT' ],
        'impl' : [ 'rCtx->marker->PushGroupMarker( rCtx, ${arg0plus} );',
                   'RegalAssert(rCtx->info);',
                   'if (!rCtx->info->gl_ext_debug_marker) return;' ]
    },
    'Pop' : {
        'entries' : [ 'glPopGroupMarkerEXT' ],
        'impl' : [ 'rCtx->marker->PopGroupMarker( rCtx );',
                   'RegalAssert(rCtx->info);',
                   'if (!rCtx->info->gl_ext_debug_marker) return;' ]
    }
}
