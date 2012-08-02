import Api
from Api import Api
from Api import Function, Typedef, Enum
from Api import Return, Parameter, Input, Output, InputOutput
from Api import Enumerant

egl = Api()
EGLNativeWindowType = Typedef('EGLNativeWindowType','struct ANativeWindow*')
EGLNativeWindowType.default = '0'

EGLNativePixmapType = Typedef('EGLNativePixmapType','struct egl_native_pixmap_t*')
EGLNativePixmapType.default = '0'

EGLNativeDisplayType = Typedef('EGLNativeDisplayType','void*')
EGLNativeDisplayType.default = '0'

NativeDisplayType = Typedef('NativeDisplayType','EGLNativeDisplayType')
NativeDisplayType.default = '0'

NativePixmapType = Typedef('NativePixmapType','EGLNativePixmapType ')
NativePixmapType.default = '0'

NativeWindowType = Typedef('NativeWindowType','EGLNativeWindowType ')
NativeWindowType.default = '0'

EGLint = Typedef('EGLint','int')
EGLint.default = '0'

EGLBoolean = Typedef('EGLBoolean','unsigned int')
EGLBoolean.default = '0'

EGLenum = Typedef('EGLenum','unsigned int')
EGLenum.default = '0'

EGLConfig = Typedef('EGLConfig','void *')
EGLConfig.default = '0'

EGLContext = Typedef('EGLContext','void *')
EGLContext.default = '0'

EGLDisplay = Typedef('EGLDisplay','void *')
EGLDisplay.default = '0'

EGLSurface = Typedef('EGLSurface','void *')
EGLSurface.default = '0'

EGLClientBuffer = Typedef('EGLClientBuffer','void *')
EGLClientBuffer.default = '0'

__eglMustCastToProperFunctionPointerType = Typedef('__eglMustCastToProperFunctionPointerType','void  (*)(void)')
__eglMustCastToProperFunctionPointerType.default = '0'

egl.add(EGLNativeWindowType)
egl.add(EGLNativePixmapType)
egl.add(EGLNativeDisplayType)
egl.add(NativeDisplayType)
egl.add(NativePixmapType)
egl.add(NativeWindowType)
egl.add(EGLint)
egl.add(EGLBoolean)
egl.add(EGLenum)
egl.add(EGLConfig)
egl.add(EGLContext)
egl.add(EGLDisplay)
egl.add(EGLSurface)
egl.add(EGLClientBuffer)
egl.add(__eglMustCastToProperFunctionPointerType)


defines = Enum('defines')
egl.add(defines)

# 

EGLAPI = Enumerant('EGLAPI', 'KHRONOS_APICALL', '')
EGLAPIENTRY = Enumerant('EGLAPIENTRY', 'KHRONOS_APIENTRY', '')
EGLAPIENTRYP = Enumerant('EGLAPIENTRYP', 'EGLAPIENTRY *', '')
EGL_ALPHA_FORMAT = Enumerant('EGL_ALPHA_FORMAT', 'EGL_VG_ALPHA_FORMAT', '')
EGL_ALPHA_FORMAT_NONPRE = Enumerant('EGL_ALPHA_FORMAT_NONPRE', 'EGL_VG_ALPHA_FORMAT_NONPRE', '')
EGL_ALPHA_FORMAT_PRE = Enumerant('EGL_ALPHA_FORMAT_PRE', 'EGL_VG_ALPHA_FORMAT_PRE', '')
EGL_ALPHA_MASK_SIZE = Enumerant('EGL_ALPHA_MASK_SIZE', 12350, '')
EGL_ALPHA_SIZE = Enumerant('EGL_ALPHA_SIZE', 12321, '')
EGL_BACK_BUFFER = Enumerant('EGL_BACK_BUFFER', 12420, '')
EGL_BAD_ACCESS = Enumerant('EGL_BAD_ACCESS', 12290, '')
EGL_BAD_ALLOC = Enumerant('EGL_BAD_ALLOC', 12291, '')
EGL_BAD_ATTRIBUTE = Enumerant('EGL_BAD_ATTRIBUTE', 12292, '')
EGL_BAD_CONFIG = Enumerant('EGL_BAD_CONFIG', 12293, '')
EGL_BAD_CONTEXT = Enumerant('EGL_BAD_CONTEXT', 12294, '')
EGL_BAD_CURRENT_SURFACE = Enumerant('EGL_BAD_CURRENT_SURFACE', 12295, '')
EGL_BAD_DISPLAY = Enumerant('EGL_BAD_DISPLAY', 12296, '')
EGL_BAD_MATCH = Enumerant('EGL_BAD_MATCH', 12297, '')
EGL_BAD_NATIVE_PIXMAP = Enumerant('EGL_BAD_NATIVE_PIXMAP', 12298, '')
EGL_BAD_NATIVE_WINDOW = Enumerant('EGL_BAD_NATIVE_WINDOW', 12299, '')
EGL_BAD_PARAMETER = Enumerant('EGL_BAD_PARAMETER', 12300, '')
EGL_BAD_SURFACE = Enumerant('EGL_BAD_SURFACE', 12301, '')
EGL_BIND_TO_TEXTURE_RGB = Enumerant('EGL_BIND_TO_TEXTURE_RGB', 12345, '')
EGL_BIND_TO_TEXTURE_RGBA = Enumerant('EGL_BIND_TO_TEXTURE_RGBA', 12346, '')
EGL_BLUE_SIZE = Enumerant('EGL_BLUE_SIZE', 12322, '')
EGL_BUFFER_DESTROYED = Enumerant('EGL_BUFFER_DESTROYED', 12437, '')
EGL_BUFFER_PRESERVED = Enumerant('EGL_BUFFER_PRESERVED', 12436, '')
EGL_BUFFER_SIZE = Enumerant('EGL_BUFFER_SIZE', 12320, '')
EGL_CLIENT_APIS = Enumerant('EGL_CLIENT_APIS', 12429, '')
EGL_COLORSPACE = Enumerant('EGL_COLORSPACE', 'EGL_VG_COLORSPACE', '')
EGL_COLORSPACE_LINEAR = Enumerant('EGL_COLORSPACE_LINEAR', 'EGL_VG_COLORSPACE_LINEAR', '')
EGL_COLORSPACE_sRGB = Enumerant('EGL_COLORSPACE_sRGB', 'EGL_VG_COLORSPACE_sRGB', '')
EGL_COLOR_BUFFER_TYPE = Enumerant('EGL_COLOR_BUFFER_TYPE', 12351, '')
EGL_CONFIG_CAVEAT = Enumerant('EGL_CONFIG_CAVEAT', 12327, '')
EGL_CONFIG_ID = Enumerant('EGL_CONFIG_ID', 12328, '')
EGL_CONFORMANT = Enumerant('EGL_CONFORMANT', 12354, '')
EGL_CONTEXT_CLIENT_TYPE = Enumerant('EGL_CONTEXT_CLIENT_TYPE', 12439, '')
EGL_CONTEXT_CLIENT_VERSION = Enumerant('EGL_CONTEXT_CLIENT_VERSION', 12440, '')
EGL_CONTEXT_LOST = Enumerant('EGL_CONTEXT_LOST', 12302, '')
EGL_CORE_NATIVE_ENGINE = Enumerant('EGL_CORE_NATIVE_ENGINE', 12379, '')
EGL_DEFAULT_DISPLAY = Enumerant('EGL_DEFAULT_DISPLAY', '((EGLNativeDisplayType)0)', '')
EGL_DEPTH_SIZE = Enumerant('EGL_DEPTH_SIZE', 12325, '')
EGL_DISPLAY_SCALING = Enumerant('EGL_DISPLAY_SCALING', 10000, '')
EGL_DONT_CARE = Enumerant('EGL_DONT_CARE', '((EGLint)-1)', '')
EGL_DRAW = Enumerant('EGL_DRAW', 12377, '')
EGL_EXTENSIONS = Enumerant('EGL_EXTENSIONS', 12373, '')
EGL_FALSE = Enumerant('EGL_FALSE', 0, '')
EGL_GREEN_SIZE = Enumerant('EGL_GREEN_SIZE', 12323, '')
EGL_HEIGHT = Enumerant('EGL_HEIGHT', 12374, '')
EGL_HORIZONTAL_RESOLUTION = Enumerant('EGL_HORIZONTAL_RESOLUTION', 12432, '')
EGL_LARGEST_PBUFFER = Enumerant('EGL_LARGEST_PBUFFER', 12376, '')
EGL_LEVEL = Enumerant('EGL_LEVEL', 12329, '')
EGL_LUMINANCE_BUFFER = Enumerant('EGL_LUMINANCE_BUFFER', 12431, '')
EGL_LUMINANCE_SIZE = Enumerant('EGL_LUMINANCE_SIZE', 12349, '')
EGL_MATCH_NATIVE_PIXMAP = Enumerant('EGL_MATCH_NATIVE_PIXMAP', 12353, '')
EGL_MAX_PBUFFER_HEIGHT = Enumerant('EGL_MAX_PBUFFER_HEIGHT', 12330, '')
EGL_MAX_PBUFFER_PIXELS = Enumerant('EGL_MAX_PBUFFER_PIXELS', 12331, '')
EGL_MAX_PBUFFER_WIDTH = Enumerant('EGL_MAX_PBUFFER_WIDTH', 12332, '')
EGL_MAX_SWAP_INTERVAL = Enumerant('EGL_MAX_SWAP_INTERVAL', 12348, '')
EGL_MIN_SWAP_INTERVAL = Enumerant('EGL_MIN_SWAP_INTERVAL', 12347, '')
EGL_MIPMAP_LEVEL = Enumerant('EGL_MIPMAP_LEVEL', 12419, '')
EGL_MIPMAP_TEXTURE = Enumerant('EGL_MIPMAP_TEXTURE', 12418, '')
EGL_MULTISAMPLE_RESOLVE = Enumerant('EGL_MULTISAMPLE_RESOLVE', 12441, '')
EGL_MULTISAMPLE_RESOLVE_BOX = Enumerant('EGL_MULTISAMPLE_RESOLVE_BOX', 12443, '')
EGL_MULTISAMPLE_RESOLVE_BOX_BIT = Enumerant('EGL_MULTISAMPLE_RESOLVE_BOX_BIT', 512, '')
EGL_MULTISAMPLE_RESOLVE_DEFAULT = Enumerant('EGL_MULTISAMPLE_RESOLVE_DEFAULT', 12442, '')
EGL_NATIVE_RENDERABLE = Enumerant('EGL_NATIVE_RENDERABLE', 12333, '')
EGL_NATIVE_VISUAL_ID = Enumerant('EGL_NATIVE_VISUAL_ID', 12334, '')
EGL_NATIVE_VISUAL_TYPE = Enumerant('EGL_NATIVE_VISUAL_TYPE', 12335, '')
EGL_NONE = Enumerant('EGL_NONE', 12344, '')
EGL_NON_CONFORMANT_CONFIG = Enumerant('EGL_NON_CONFORMANT_CONFIG', 12369, '')
EGL_NOT_INITIALIZED = Enumerant('EGL_NOT_INITIALIZED', 12289, '')
EGL_NO_CONTEXT = Enumerant('EGL_NO_CONTEXT', '((EGLContext)0)', '')
EGL_NO_DISPLAY = Enumerant('EGL_NO_DISPLAY', '((EGLDisplay)0)', '')
EGL_NO_SURFACE = Enumerant('EGL_NO_SURFACE', '((EGLSurface)0)', '')
EGL_NO_TEXTURE = Enumerant('EGL_NO_TEXTURE', 12380, '')
EGL_OPENGL_API = Enumerant('EGL_OPENGL_API', 12450, '')
EGL_OPENGL_BIT = Enumerant('EGL_OPENGL_BIT', 8, '')
EGL_OPENGL_ES2_BIT = Enumerant('EGL_OPENGL_ES2_BIT', 4, '')
EGL_OPENGL_ES_API = Enumerant('EGL_OPENGL_ES_API', 12448, '')
EGL_OPENGL_ES_BIT = Enumerant('EGL_OPENGL_ES_BIT', 1, '')
EGL_OPENVG_API = Enumerant('EGL_OPENVG_API', 12449, '')
EGL_OPENVG_BIT = Enumerant('EGL_OPENVG_BIT', 2, '')
EGL_OPENVG_IMAGE = Enumerant('EGL_OPENVG_IMAGE', 12438, '')
EGL_PBUFFER_BIT = Enumerant('EGL_PBUFFER_BIT', 1, '')
EGL_PIXEL_ASPECT_RATIO = Enumerant('EGL_PIXEL_ASPECT_RATIO', 12434, '')
EGL_PIXMAP_BIT = Enumerant('EGL_PIXMAP_BIT', 2, '')
EGL_READ = Enumerant('EGL_READ', 12378, '')
EGL_RED_SIZE = Enumerant('EGL_RED_SIZE', 12324, '')
EGL_RENDERABLE_TYPE = Enumerant('EGL_RENDERABLE_TYPE', 12352, '')
EGL_RENDER_BUFFER = Enumerant('EGL_RENDER_BUFFER', 12422, '')
EGL_RGB_BUFFER = Enumerant('EGL_RGB_BUFFER', 12430, '')
EGL_SAMPLES = Enumerant('EGL_SAMPLES', 12337, '')
EGL_SAMPLE_BUFFERS = Enumerant('EGL_SAMPLE_BUFFERS', 12338, '')
EGL_SINGLE_BUFFER = Enumerant('EGL_SINGLE_BUFFER', 12421, '')
EGL_SLOW_CONFIG = Enumerant('EGL_SLOW_CONFIG', 12368, '')
EGL_STENCIL_SIZE = Enumerant('EGL_STENCIL_SIZE', 12326, '')
EGL_SUCCESS = Enumerant('EGL_SUCCESS', 12288, '')
EGL_SURFACE_TYPE = Enumerant('EGL_SURFACE_TYPE', 12339, '')
EGL_SWAP_BEHAVIOR = Enumerant('EGL_SWAP_BEHAVIOR', 12435, '')
EGL_SWAP_BEHAVIOR_PRESERVED_BIT = Enumerant('EGL_SWAP_BEHAVIOR_PRESERVED_BIT', 1024, '')
EGL_TEXTURE_2D = Enumerant('EGL_TEXTURE_2D', 12383, '')
EGL_TEXTURE_FORMAT = Enumerant('EGL_TEXTURE_FORMAT', 12416, '')
EGL_TEXTURE_RGB = Enumerant('EGL_TEXTURE_RGB', 12381, '')
EGL_TEXTURE_RGBA = Enumerant('EGL_TEXTURE_RGBA', 12382, '')
EGL_TEXTURE_TARGET = Enumerant('EGL_TEXTURE_TARGET', 12417, '')
EGL_TRANSPARENT_BLUE_VALUE = Enumerant('EGL_TRANSPARENT_BLUE_VALUE', 12341, '')
EGL_TRANSPARENT_GREEN_VALUE = Enumerant('EGL_TRANSPARENT_GREEN_VALUE', 12342, '')
EGL_TRANSPARENT_RED_VALUE = Enumerant('EGL_TRANSPARENT_RED_VALUE', 12343, '')
EGL_TRANSPARENT_RGB = Enumerant('EGL_TRANSPARENT_RGB', 12370, '')
EGL_TRANSPARENT_TYPE = Enumerant('EGL_TRANSPARENT_TYPE', 12340, '')
EGL_TRUE = Enumerant('EGL_TRUE', 1, '')
EGL_UNKNOWN = Enumerant('EGL_UNKNOWN', '((EGLint)-1)', '')
EGL_VENDOR = Enumerant('EGL_VENDOR', 12371, '')
EGL_VERSION = Enumerant('EGL_VERSION', 12372, '')
EGL_VERSION_1_3 = Enumerant('EGL_VERSION_1_3', 1, '')
EGL_VERSION_1_4 = Enumerant('EGL_VERSION_1_4', 1, '')
EGL_VERTICAL_RESOLUTION = Enumerant('EGL_VERTICAL_RESOLUTION', 12433, '')
EGL_VG_ALPHA_FORMAT = Enumerant('EGL_VG_ALPHA_FORMAT', 12424, '')
EGL_VG_ALPHA_FORMAT_NONPRE = Enumerant('EGL_VG_ALPHA_FORMAT_NONPRE', 12427, '')
EGL_VG_ALPHA_FORMAT_PRE = Enumerant('EGL_VG_ALPHA_FORMAT_PRE', 12428, '')
EGL_VG_ALPHA_FORMAT_PRE_BIT = Enumerant('EGL_VG_ALPHA_FORMAT_PRE_BIT', 64, '')
EGL_VG_COLORSPACE = Enumerant('EGL_VG_COLORSPACE', 12423, '')
EGL_VG_COLORSPACE_LINEAR = Enumerant('EGL_VG_COLORSPACE_LINEAR', 12426, '')
EGL_VG_COLORSPACE_LINEAR_BIT = Enumerant('EGL_VG_COLORSPACE_LINEAR_BIT', 32, '')
EGL_VG_COLORSPACE_sRGB = Enumerant('EGL_VG_COLORSPACE_sRGB', 12425, '')
EGL_WIDTH = Enumerant('EGL_WIDTH', 12375, '')
EGL_WINDOW_BIT = Enumerant('EGL_WINDOW_BIT', 4, '')

defines.add(EGLAPI)
defines.add(EGLAPIENTRY)
defines.add(EGLAPIENTRYP)
defines.add(EGL_ALPHA_FORMAT)
defines.add(EGL_ALPHA_FORMAT_NONPRE)
defines.add(EGL_ALPHA_FORMAT_PRE)
defines.add(EGL_ALPHA_MASK_SIZE)
defines.add(EGL_ALPHA_SIZE)
defines.add(EGL_BACK_BUFFER)
defines.add(EGL_BAD_ACCESS)
defines.add(EGL_BAD_ALLOC)
defines.add(EGL_BAD_ATTRIBUTE)
defines.add(EGL_BAD_CONFIG)
defines.add(EGL_BAD_CONTEXT)
defines.add(EGL_BAD_CURRENT_SURFACE)
defines.add(EGL_BAD_DISPLAY)
defines.add(EGL_BAD_MATCH)
defines.add(EGL_BAD_NATIVE_PIXMAP)
defines.add(EGL_BAD_NATIVE_WINDOW)
defines.add(EGL_BAD_PARAMETER)
defines.add(EGL_BAD_SURFACE)
defines.add(EGL_BIND_TO_TEXTURE_RGB)
defines.add(EGL_BIND_TO_TEXTURE_RGBA)
defines.add(EGL_BLUE_SIZE)
defines.add(EGL_BUFFER_DESTROYED)
defines.add(EGL_BUFFER_PRESERVED)
defines.add(EGL_BUFFER_SIZE)
defines.add(EGL_CLIENT_APIS)
defines.add(EGL_COLORSPACE)
defines.add(EGL_COLORSPACE_LINEAR)
defines.add(EGL_COLORSPACE_sRGB)
defines.add(EGL_COLOR_BUFFER_TYPE)
defines.add(EGL_CONFIG_CAVEAT)
defines.add(EGL_CONFIG_ID)
defines.add(EGL_CONFORMANT)
defines.add(EGL_CONTEXT_CLIENT_TYPE)
defines.add(EGL_CONTEXT_CLIENT_VERSION)
defines.add(EGL_CONTEXT_LOST)
defines.add(EGL_CORE_NATIVE_ENGINE)
defines.add(EGL_DEFAULT_DISPLAY)
defines.add(EGL_DEPTH_SIZE)
defines.add(EGL_DISPLAY_SCALING)
defines.add(EGL_DONT_CARE)
defines.add(EGL_DRAW)
defines.add(EGL_EXTENSIONS)
defines.add(EGL_FALSE)
defines.add(EGL_GREEN_SIZE)
defines.add(EGL_HEIGHT)
defines.add(EGL_HORIZONTAL_RESOLUTION)
defines.add(EGL_LARGEST_PBUFFER)
defines.add(EGL_LEVEL)
defines.add(EGL_LUMINANCE_BUFFER)
defines.add(EGL_LUMINANCE_SIZE)
defines.add(EGL_MATCH_NATIVE_PIXMAP)
defines.add(EGL_MAX_PBUFFER_HEIGHT)
defines.add(EGL_MAX_PBUFFER_PIXELS)
defines.add(EGL_MAX_PBUFFER_WIDTH)
defines.add(EGL_MAX_SWAP_INTERVAL)
defines.add(EGL_MIN_SWAP_INTERVAL)
defines.add(EGL_MIPMAP_LEVEL)
defines.add(EGL_MIPMAP_TEXTURE)
defines.add(EGL_MULTISAMPLE_RESOLVE)
defines.add(EGL_MULTISAMPLE_RESOLVE_BOX)
defines.add(EGL_MULTISAMPLE_RESOLVE_BOX_BIT)
defines.add(EGL_MULTISAMPLE_RESOLVE_DEFAULT)
defines.add(EGL_NATIVE_RENDERABLE)
defines.add(EGL_NATIVE_VISUAL_ID)
defines.add(EGL_NATIVE_VISUAL_TYPE)
defines.add(EGL_NONE)
defines.add(EGL_NON_CONFORMANT_CONFIG)
defines.add(EGL_NOT_INITIALIZED)
defines.add(EGL_NO_CONTEXT)
defines.add(EGL_NO_DISPLAY)
defines.add(EGL_NO_SURFACE)
defines.add(EGL_NO_TEXTURE)
defines.add(EGL_OPENGL_API)
defines.add(EGL_OPENGL_BIT)
defines.add(EGL_OPENGL_ES2_BIT)
defines.add(EGL_OPENGL_ES_API)
defines.add(EGL_OPENGL_ES_BIT)
defines.add(EGL_OPENVG_API)
defines.add(EGL_OPENVG_BIT)
defines.add(EGL_OPENVG_IMAGE)
defines.add(EGL_PBUFFER_BIT)
defines.add(EGL_PIXEL_ASPECT_RATIO)
defines.add(EGL_PIXMAP_BIT)
defines.add(EGL_READ)
defines.add(EGL_RED_SIZE)
defines.add(EGL_RENDERABLE_TYPE)
defines.add(EGL_RENDER_BUFFER)
defines.add(EGL_RGB_BUFFER)
defines.add(EGL_SAMPLES)
defines.add(EGL_SAMPLE_BUFFERS)
defines.add(EGL_SINGLE_BUFFER)
defines.add(EGL_SLOW_CONFIG)
defines.add(EGL_STENCIL_SIZE)
defines.add(EGL_SUCCESS)
defines.add(EGL_SURFACE_TYPE)
defines.add(EGL_SWAP_BEHAVIOR)
defines.add(EGL_SWAP_BEHAVIOR_PRESERVED_BIT)
defines.add(EGL_TEXTURE_2D)
defines.add(EGL_TEXTURE_FORMAT)
defines.add(EGL_TEXTURE_RGB)
defines.add(EGL_TEXTURE_RGBA)
defines.add(EGL_TEXTURE_TARGET)
defines.add(EGL_TRANSPARENT_BLUE_VALUE)
defines.add(EGL_TRANSPARENT_GREEN_VALUE)
defines.add(EGL_TRANSPARENT_RED_VALUE)
defines.add(EGL_TRANSPARENT_RGB)
defines.add(EGL_TRANSPARENT_TYPE)
defines.add(EGL_TRUE)
defines.add(EGL_UNKNOWN)
defines.add(EGL_VENDOR)
defines.add(EGL_VERSION)
defines.add(EGL_VERSION_1_3)
defines.add(EGL_VERSION_1_4)
defines.add(EGL_VERTICAL_RESOLUTION)
defines.add(EGL_VG_ALPHA_FORMAT)
defines.add(EGL_VG_ALPHA_FORMAT_NONPRE)
defines.add(EGL_VG_ALPHA_FORMAT_PRE)
defines.add(EGL_VG_ALPHA_FORMAT_PRE_BIT)
defines.add(EGL_VG_COLORSPACE)
defines.add(EGL_VG_COLORSPACE_LINEAR)
defines.add(EGL_VG_COLORSPACE_LINEAR_BIT)
defines.add(EGL_VG_COLORSPACE_sRGB)
defines.add(EGL_WIDTH)
defines.add(EGL_WINDOW_BIT)

# EGL_VERSION_1_0

eglChooseConfig = Function('eglChooseConfig')
eglChooseConfig.ret = Return('EGLBoolean')
eglChooseConfig.add( Input( 'dpy','EGLDisplay' ))
eglChooseConfig.add( Input( 'attrib_list','const EGLint *' ))
eglChooseConfig.add( Input( 'configs','EGLConfig *' ))
eglChooseConfig.add( Input( 'config_size','EGLint' ))
eglChooseConfig.add( Input( 'num_config','EGLint *' ))
eglChooseConfig.version = ''
eglChooseConfig.category = 'EGL_VERSION_1_0'
eglChooseConfig.trace = True
eglChooseConfig.play = True
egl.add(eglChooseConfig)

eglCopyBuffers = Function('eglCopyBuffers')
eglCopyBuffers.ret = Return('EGLBoolean')
eglCopyBuffers.add( Input( 'dpy','EGLDisplay' ))
eglCopyBuffers.add( Input( 'surface','EGLSurface' ))
eglCopyBuffers.add( Input( 'target','EGLNativePixmapType' ))
eglCopyBuffers.version = ''
eglCopyBuffers.category = 'EGL_VERSION_1_0'
eglCopyBuffers.trace = True
eglCopyBuffers.play = True
egl.add(eglCopyBuffers)

eglCreateContext = Function('eglCreateContext')
eglCreateContext.ret = Return('EGLContext')
eglCreateContext.add( Input( 'dpy','EGLDisplay' ))
eglCreateContext.add( Input( 'config','EGLConfig' ))
eglCreateContext.add( Input( 'share_context','EGLContext' ))
eglCreateContext.add( Input( 'attrib_list','const EGLint *' ))
eglCreateContext.version = ''
eglCreateContext.category = 'EGL_VERSION_1_0'
eglCreateContext.trace = True
eglCreateContext.play = True
egl.add(eglCreateContext)

eglCreatePbufferSurface = Function('eglCreatePbufferSurface')
eglCreatePbufferSurface.ret = Return('EGLSurface')
eglCreatePbufferSurface.add( Input( 'dpy','EGLDisplay' ))
eglCreatePbufferSurface.add( Input( 'config','EGLConfig' ))
eglCreatePbufferSurface.add( Input( 'attrib_list','const EGLint *' ))
eglCreatePbufferSurface.version = ''
eglCreatePbufferSurface.category = 'EGL_VERSION_1_0'
eglCreatePbufferSurface.trace = True
eglCreatePbufferSurface.play = True
egl.add(eglCreatePbufferSurface)

eglCreatePixmapSurface = Function('eglCreatePixmapSurface')
eglCreatePixmapSurface.ret = Return('EGLSurface')
eglCreatePixmapSurface.add( Input( 'dpy','EGLDisplay' ))
eglCreatePixmapSurface.add( Input( 'config','EGLConfig' ))
eglCreatePixmapSurface.add( Input( 'pixmap','EGLNativePixmapType' ))
eglCreatePixmapSurface.add( Input( 'attrib_list','const EGLint *' ))
eglCreatePixmapSurface.version = ''
eglCreatePixmapSurface.category = 'EGL_VERSION_1_0'
eglCreatePixmapSurface.trace = True
eglCreatePixmapSurface.play = True
egl.add(eglCreatePixmapSurface)

eglCreateWindowSurface = Function('eglCreateWindowSurface')
eglCreateWindowSurface.ret = Return('EGLSurface')
eglCreateWindowSurface.add( Input( 'dpy','EGLDisplay' ))
eglCreateWindowSurface.add( Input( 'config','EGLConfig' ))
eglCreateWindowSurface.add( Input( 'win','EGLNativeWindowType' ))
eglCreateWindowSurface.add( Input( 'attrib_list','const EGLint *' ))
eglCreateWindowSurface.version = ''
eglCreateWindowSurface.category = 'EGL_VERSION_1_0'
eglCreateWindowSurface.trace = True
eglCreateWindowSurface.play = True
egl.add(eglCreateWindowSurface)

eglDestroyContext = Function('eglDestroyContext')
eglDestroyContext.ret = Return('EGLBoolean')
eglDestroyContext.add( Input( 'dpy','EGLDisplay' ))
eglDestroyContext.add( Input( 'ctx','EGLContext' ))
eglDestroyContext.version = ''
eglDestroyContext.category = 'EGL_VERSION_1_0'
eglDestroyContext.trace = True
eglDestroyContext.play = True
egl.add(eglDestroyContext)

eglDestroySurface = Function('eglDestroySurface')
eglDestroySurface.ret = Return('EGLBoolean')
eglDestroySurface.add( Input( 'dpy','EGLDisplay' ))
eglDestroySurface.add( Input( 'surface','EGLSurface' ))
eglDestroySurface.version = ''
eglDestroySurface.category = 'EGL_VERSION_1_0'
eglDestroySurface.trace = True
eglDestroySurface.play = True
egl.add(eglDestroySurface)

eglGetConfigAttrib = Function('eglGetConfigAttrib')
eglGetConfigAttrib.ret = Return('EGLBoolean')
eglGetConfigAttrib.add( Input( 'dpy','EGLDisplay' ))
eglGetConfigAttrib.add( Input( 'config','EGLConfig' ))
eglGetConfigAttrib.add( Input( 'attribute','EGLint' ))
eglGetConfigAttrib.add( Input( 'value','EGLint *' ))
eglGetConfigAttrib.version = ''
eglGetConfigAttrib.category = 'EGL_VERSION_1_0'
eglGetConfigAttrib.trace = True
eglGetConfigAttrib.play = True
egl.add(eglGetConfigAttrib)

eglGetConfigs = Function('eglGetConfigs')
eglGetConfigs.ret = Return('EGLBoolean')
eglGetConfigs.add( Input( 'dpy','EGLDisplay' ))
eglGetConfigs.add( Input( 'configs','EGLConfig *' ))
eglGetConfigs.add( Input( 'config_size','EGLint' ))
eglGetConfigs.add( Input( 'num_config','EGLint *' ))
eglGetConfigs.version = ''
eglGetConfigs.category = 'EGL_VERSION_1_0'
eglGetConfigs.trace = True
eglGetConfigs.play = True
egl.add(eglGetConfigs)

eglGetCurrentContext = Function('eglGetCurrentContext')
eglGetCurrentContext.ret = Return('EGLContext')
eglGetCurrentContext.version = ''
eglGetCurrentContext.category = 'EGL_VERSION_1_0'
eglGetCurrentContext.trace = True
eglGetCurrentContext.play = True
egl.add(eglGetCurrentContext)

eglGetCurrentDisplay = Function('eglGetCurrentDisplay')
eglGetCurrentDisplay.ret = Return('EGLDisplay')
eglGetCurrentDisplay.version = ''
eglGetCurrentDisplay.category = 'EGL_VERSION_1_0'
eglGetCurrentDisplay.trace = True
eglGetCurrentDisplay.play = True
egl.add(eglGetCurrentDisplay)

eglGetCurrentSurface = Function('eglGetCurrentSurface')
eglGetCurrentSurface.ret = Return('EGLSurface')
eglGetCurrentSurface.add( Input( 'readdraw','EGLint' ))
eglGetCurrentSurface.version = ''
eglGetCurrentSurface.category = 'EGL_VERSION_1_0'
eglGetCurrentSurface.trace = True
eglGetCurrentSurface.play = True
egl.add(eglGetCurrentSurface)

eglGetDisplay = Function('eglGetDisplay')
eglGetDisplay.ret = Return('EGLDisplay')
eglGetDisplay.add( Input( 'display_id','EGLNativeDisplayType' ))
eglGetDisplay.version = ''
eglGetDisplay.category = 'EGL_VERSION_1_0'
eglGetDisplay.trace = True
eglGetDisplay.play = True
egl.add(eglGetDisplay)

eglGetError = Function('eglGetError')
eglGetError.ret = Return('EGLint')
eglGetError.version = ''
eglGetError.category = 'EGL_VERSION_1_0'
eglGetError.trace = True
eglGetError.play = True
egl.add(eglGetError)

eglGetProcAddress = Function('eglGetProcAddress')
eglGetProcAddress.ret = Return('__eglMustCastToProperFunctionPointerType')
eglGetProcAddress.add( Input( 'procname','const char *' ))
eglGetProcAddress.version = ''
eglGetProcAddress.category = 'EGL_VERSION_1_0'
eglGetProcAddress.trace = True
eglGetProcAddress.play = True
egl.add(eglGetProcAddress)

eglInitialize = Function('eglInitialize')
eglInitialize.ret = Return('EGLBoolean')
eglInitialize.add( Input( 'dpy','EGLDisplay' ))
eglInitialize.add( Input( 'major','EGLint *' ))
eglInitialize.add( Input( 'minor','EGLint *' ))
eglInitialize.version = ''
eglInitialize.category = 'EGL_VERSION_1_0'
eglInitialize.trace = True
eglInitialize.play = True
egl.add(eglInitialize)

eglMakeCurrent = Function('eglMakeCurrent')
eglMakeCurrent.ret = Return('EGLBoolean')
eglMakeCurrent.add( Input( 'dpy','EGLDisplay' ))
eglMakeCurrent.add( Input( 'draw','EGLSurface' ))
eglMakeCurrent.add( Input( 'read','EGLSurface' ))
eglMakeCurrent.add( Input( 'ctx','EGLContext' ))
eglMakeCurrent.version = ''
eglMakeCurrent.category = 'EGL_VERSION_1_0'
eglMakeCurrent.trace = True
eglMakeCurrent.play = True
egl.add(eglMakeCurrent)

eglQueryContext = Function('eglQueryContext')
eglQueryContext.ret = Return('EGLBoolean')
eglQueryContext.add( Input( 'dpy','EGLDisplay' ))
eglQueryContext.add( Input( 'ctx','EGLContext' ))
eglQueryContext.add( Input( 'attribute','EGLint' ))
eglQueryContext.add( Input( 'value','EGLint *' ))
eglQueryContext.version = ''
eglQueryContext.category = 'EGL_VERSION_1_0'
eglQueryContext.trace = True
eglQueryContext.play = True
egl.add(eglQueryContext)

eglQueryString = Function('eglQueryString')
eglQueryString.ret = Return('const char *')
eglQueryString.add( Input( 'dpy','EGLDisplay' ))
eglQueryString.add( Input( 'name','EGLint' ))
eglQueryString.version = ''
eglQueryString.category = 'EGL_VERSION_1_0'
eglQueryString.trace = True
eglQueryString.play = True
egl.add(eglQueryString)

eglQuerySurface = Function('eglQuerySurface')
eglQuerySurface.ret = Return('EGLBoolean')
eglQuerySurface.add( Input( 'dpy','EGLDisplay' ))
eglQuerySurface.add( Input( 'surface','EGLSurface' ))
eglQuerySurface.add( Input( 'attribute','EGLint' ))
eglQuerySurface.add( Input( 'value','EGLint *' ))
eglQuerySurface.version = ''
eglQuerySurface.category = 'EGL_VERSION_1_0'
eglQuerySurface.trace = True
eglQuerySurface.play = True
egl.add(eglQuerySurface)

eglSwapBuffers = Function('eglSwapBuffers')
eglSwapBuffers.ret = Return('EGLBoolean')
eglSwapBuffers.add( Input( 'dpy','EGLDisplay' ))
eglSwapBuffers.add( Input( 'surface','EGLSurface' ))
eglSwapBuffers.version = ''
eglSwapBuffers.category = 'EGL_VERSION_1_0'
eglSwapBuffers.trace = True
eglSwapBuffers.play = True
egl.add(eglSwapBuffers)

eglTerminate = Function('eglTerminate')
eglTerminate.ret = Return('EGLBoolean')
eglTerminate.add( Input( 'dpy','EGLDisplay' ))
eglTerminate.version = ''
eglTerminate.category = 'EGL_VERSION_1_0'
eglTerminate.trace = True
eglTerminate.play = True
egl.add(eglTerminate)

eglWaitGL = Function('eglWaitGL')
eglWaitGL.ret = Return('EGLBoolean')
eglWaitGL.version = ''
eglWaitGL.category = 'EGL_VERSION_1_0'
eglWaitGL.trace = True
eglWaitGL.play = True
egl.add(eglWaitGL)

eglWaitNative = Function('eglWaitNative')
eglWaitNative.ret = Return('EGLBoolean')
eglWaitNative.add( Input( 'engine','EGLint' ))
eglWaitNative.version = ''
eglWaitNative.category = 'EGL_VERSION_1_0'
eglWaitNative.trace = True
eglWaitNative.play = True
egl.add(eglWaitNative)

# EGL_VERSION_1_1

eglBindTexImage = Function('eglBindTexImage')
eglBindTexImage.ret = Return('EGLBoolean')
eglBindTexImage.add( Input( 'dpy','EGLDisplay' ))
eglBindTexImage.add( Input( 'surface','EGLSurface' ))
eglBindTexImage.add( Input( 'buffer','EGLint' ))
eglBindTexImage.version = ''
eglBindTexImage.category = 'EGL_VERSION_1_1'
eglBindTexImage.trace = True
eglBindTexImage.play = True
egl.add(eglBindTexImage)

eglReleaseTexImage = Function('eglReleaseTexImage')
eglReleaseTexImage.ret = Return('EGLBoolean')
eglReleaseTexImage.add( Input( 'dpy','EGLDisplay' ))
eglReleaseTexImage.add( Input( 'surface','EGLSurface' ))
eglReleaseTexImage.add( Input( 'buffer','EGLint' ))
eglReleaseTexImage.version = ''
eglReleaseTexImage.category = 'EGL_VERSION_1_1'
eglReleaseTexImage.trace = True
eglReleaseTexImage.play = True
egl.add(eglReleaseTexImage)

# EGL_VERSION_1_2

eglBindAPI = Function('eglBindAPI')
eglBindAPI.ret = Return('EGLBoolean')
eglBindAPI.add( Input( 'api','EGLenum' ))
eglBindAPI.version = ''
eglBindAPI.category = 'EGL_VERSION_1_2'
eglBindAPI.trace = True
eglBindAPI.play = True
egl.add(eglBindAPI)

eglCreatePbufferFromClientBuffer = Function('eglCreatePbufferFromClientBuffer')
eglCreatePbufferFromClientBuffer.ret = Return('EGLSurface')
eglCreatePbufferFromClientBuffer.add( Input( 'dpy',' EGLDisplay' ))
eglCreatePbufferFromClientBuffer.add( Input( 'buftype','EGLenum' ))
eglCreatePbufferFromClientBuffer.add( Input( 'buffer','EGLClientBuffer' ))
eglCreatePbufferFromClientBuffer.add( Input( 'config','EGLConfig' ))
eglCreatePbufferFromClientBuffer.add( Input( 'attrib_list','const EGLint *' ))
eglCreatePbufferFromClientBuffer.version = ''
eglCreatePbufferFromClientBuffer.category = 'EGL_VERSION_1_2'
eglCreatePbufferFromClientBuffer.trace = True
eglCreatePbufferFromClientBuffer.play = True
egl.add(eglCreatePbufferFromClientBuffer)

eglQueryAPI = Function('eglQueryAPI')
eglQueryAPI.ret = Return('EGLenum')
eglQueryAPI.version = ''
eglQueryAPI.category = 'EGL_VERSION_1_2'
eglQueryAPI.trace = True
eglQueryAPI.play = True
egl.add(eglQueryAPI)

eglReleaseThread = Function('eglReleaseThread')
eglReleaseThread.ret = Return('EGLBoolean')
eglReleaseThread.version = ''
eglReleaseThread.category = 'EGL_VERSION_1_2'
eglReleaseThread.trace = True
eglReleaseThread.play = True
egl.add(eglReleaseThread)

eglSurfaceAttrib = Function('eglSurfaceAttrib')
eglSurfaceAttrib.ret = Return('EGLBoolean')
eglSurfaceAttrib.add( Input( 'dpy','EGLDisplay' ))
eglSurfaceAttrib.add( Input( 'surface','EGLSurface' ))
eglSurfaceAttrib.add( Input( 'attribute','EGLint' ))
eglSurfaceAttrib.add( Input( 'value','EGLint' ))
eglSurfaceAttrib.version = ''
eglSurfaceAttrib.category = 'EGL_VERSION_1_2'
eglSurfaceAttrib.trace = True
eglSurfaceAttrib.play = True
egl.add(eglSurfaceAttrib)

eglSwapInterval = Function('eglSwapInterval')
eglSwapInterval.ret = Return('EGLBoolean')
eglSwapInterval.add( Input( 'dpy','EGLDisplay' ))
eglSwapInterval.add( Input( 'interval','EGLint' ))
eglSwapInterval.version = ''
eglSwapInterval.category = 'EGL_VERSION_1_2'
eglSwapInterval.trace = True
eglSwapInterval.play = True
egl.add(eglSwapInterval)

eglWaitClient = Function('eglWaitClient')
eglWaitClient.ret = Return('EGLBoolean')
eglWaitClient.version = ''
eglWaitClient.category = 'EGL_VERSION_1_2'
eglWaitClient.trace = True
eglWaitClient.play = True
egl.add(eglWaitClient)

