import Api
from Api import Api
from Api import Function, Typedef, Enum
from Api import Return, Parameter, Input, Output, InputOutput
from Api import Enumerant

cgl = Api()
CGLContextObj = Typedef('CGLContextObj','void *')
CGLContextObj.default = '0'

CGLPixelFormatObj = Typedef('CGLPixelFormatObj','void *')
CGLPixelFormatObj.default = '0'

CGLRendererInfoObj = Typedef('CGLRendererInfoObj','void *')
CGLRendererInfoObj.default = '0'

CGLPBufferObj = Typedef('CGLPBufferObj','void *')
CGLPBufferObj.default = '0'

CGLShareGroupObj = Typedef('CGLShareGroupObj','void *')
CGLShareGroupObj.default = '0'

IOSurfaceRef = Typedef('IOSurfaceRef','void *')
IOSurfaceRef.default = '0'

CGSConnectionID = Typedef('CGSConnectionID','void *')

CGSWindowID = Typedef('CGSWindowID','void *')

CGSSurfaceID = Typedef('CGSSurfaceID','void *')

cgl.add(CGLContextObj)
cgl.add(CGLPixelFormatObj)
cgl.add(CGLRendererInfoObj)
cgl.add(CGLPBufferObj)
cgl.add(CGLShareGroupObj)
cgl.add(IOSurfaceRef)
cgl.add(CGSConnectionID)
cgl.add(CGSWindowID)
cgl.add(CGSSurfaceID)


CGLPixelFormatAttribute = Enum('CGLPixelFormatAttribute')
cgl.add(CGLPixelFormatAttribute)

kCGLPFAAllRenderers = Enumerant('kCGLPFAAllRenderers', 1, )
kCGLPFATripleBuffer = Enumerant('kCGLPFATripleBuffer', 3, )
kCGLPFADoubleBuffer = Enumerant('kCGLPFADoubleBuffer', 5, )
kCGLPFAStereo = Enumerant('kCGLPFAStereo', 6, )
kCGLPFAAuxBuffers = Enumerant('kCGLPFAAuxBuffers', 7, )
kCGLPFAColorSize = Enumerant('kCGLPFAColorSize', 8, )
kCGLPFAAlphaSize = Enumerant('kCGLPFAAlphaSize', 11, )
kCGLPFADepthSize = Enumerant('kCGLPFADepthSize', 12, )
kCGLPFAStencilSize = Enumerant('kCGLPFAStencilSize', 13, )
kCGLPFAAccumSize = Enumerant('kCGLPFAAccumSize', 14, )
kCGLPFAMinimumPolicy = Enumerant('kCGLPFAMinimumPolicy', 51, )
kCGLPFAMaximumPolicy = Enumerant('kCGLPFAMaximumPolicy', 52, )
kCGLPFAOffScreen = Enumerant('kCGLPFAOffScreen', 53, )
kCGLPFAFullScreen = Enumerant('kCGLPFAFullScreen', 54, )
kCGLPFASampleBuffers = Enumerant('kCGLPFASampleBuffers', 55, )
kCGLPFASamples = Enumerant('kCGLPFASamples', 56, )
kCGLPFAAuxDepthStencil = Enumerant('kCGLPFAAuxDepthStencil', 57, )
kCGLPFAColorFloat = Enumerant('kCGLPFAColorFloat', 58, )
kCGLPFAMultisample = Enumerant('kCGLPFAMultisample', 59, )
kCGLPFASupersample = Enumerant('kCGLPFASupersample', 60, )
kCGLPFASampleAlpha = Enumerant('kCGLPFASampleAlpha', 61, )
kCGLPFARendererID = Enumerant('kCGLPFARendererID', 70, )
kCGLPFASingleRenderer = Enumerant('kCGLPFASingleRenderer', 71, )
kCGLPFANoRecovery = Enumerant('kCGLPFANoRecovery', 72, )
kCGLPFAAccelerated = Enumerant('kCGLPFAAccelerated', 73, )
kCGLPFAClosestPolicy = Enumerant('kCGLPFAClosestPolicy', 74, )
kCGLPFABackingStore = Enumerant('kCGLPFABackingStore', 76, )
kCGLPFAWindow = Enumerant('kCGLPFAWindow', 80, )
kCGLPFACompliant = Enumerant('kCGLPFACompliant', 83, )
kCGLPFADisplayMask = Enumerant('kCGLPFADisplayMask', 84, )
kCGLPFAPBuffer = Enumerant('kCGLPFAPBuffer', 90, )
kCGLPFARemotePBuffer = Enumerant('kCGLPFARemotePBuffer', 91, )
kCGLPFAAllowOfflineRenderers = Enumerant('kCGLPFAAllowOfflineRenderers', 96, )
kCGLPFAAcceleratedCompute = Enumerant('kCGLPFAAcceleratedCompute', 97, )
kCGLPFAOpenGLProfile = Enumerant('kCGLPFAOpenGLProfile', 99, )
kCGLPFAVirtualScreenCount = Enumerant('kCGLPFAVirtualScreenCount', 128, )
CGLPixelFormatAttribute.add(kCGLPFAAllRenderers)
CGLPixelFormatAttribute.add(kCGLPFATripleBuffer)
CGLPixelFormatAttribute.add(kCGLPFADoubleBuffer)
CGLPixelFormatAttribute.add(kCGLPFAStereo)
CGLPixelFormatAttribute.add(kCGLPFAAuxBuffers)
CGLPixelFormatAttribute.add(kCGLPFAColorSize)
CGLPixelFormatAttribute.add(kCGLPFAAlphaSize)
CGLPixelFormatAttribute.add(kCGLPFADepthSize)
CGLPixelFormatAttribute.add(kCGLPFAStencilSize)
CGLPixelFormatAttribute.add(kCGLPFAAccumSize)
CGLPixelFormatAttribute.add(kCGLPFAMinimumPolicy)
CGLPixelFormatAttribute.add(kCGLPFAMaximumPolicy)
CGLPixelFormatAttribute.add(kCGLPFAOffScreen)
CGLPixelFormatAttribute.add(kCGLPFAFullScreen)
CGLPixelFormatAttribute.add(kCGLPFASampleBuffers)
CGLPixelFormatAttribute.add(kCGLPFASamples)
CGLPixelFormatAttribute.add(kCGLPFAAuxDepthStencil)
CGLPixelFormatAttribute.add(kCGLPFAColorFloat)
CGLPixelFormatAttribute.add(kCGLPFAMultisample)
CGLPixelFormatAttribute.add(kCGLPFASupersample)
CGLPixelFormatAttribute.add(kCGLPFASampleAlpha)
CGLPixelFormatAttribute.add(kCGLPFARendererID)
CGLPixelFormatAttribute.add(kCGLPFASingleRenderer)
CGLPixelFormatAttribute.add(kCGLPFANoRecovery)
CGLPixelFormatAttribute.add(kCGLPFAAccelerated)
CGLPixelFormatAttribute.add(kCGLPFAClosestPolicy)
CGLPixelFormatAttribute.add(kCGLPFABackingStore)
CGLPixelFormatAttribute.add(kCGLPFAWindow)
CGLPixelFormatAttribute.add(kCGLPFACompliant)
CGLPixelFormatAttribute.add(kCGLPFADisplayMask)
CGLPixelFormatAttribute.add(kCGLPFAPBuffer)
CGLPixelFormatAttribute.add(kCGLPFARemotePBuffer)
CGLPixelFormatAttribute.add(kCGLPFAAllowOfflineRenderers)
CGLPixelFormatAttribute.add(kCGLPFAAcceleratedCompute)
CGLPixelFormatAttribute.add(kCGLPFAOpenGLProfile)
CGLPixelFormatAttribute.add(kCGLPFAVirtualScreenCount)

CGLRendererProperty = Enum('CGLRendererProperty')
cgl.add(CGLRendererProperty)

kCGLRPOffScreen = Enumerant('kCGLRPOffScreen', 53, )
kCGLRPFullScreen = Enumerant('kCGLRPFullScreen', 54, )
kCGLRPRendererID = Enumerant('kCGLRPRendererID', 70, )
kCGLRPAccelerated = Enumerant('kCGLRPAccelerated', 73, )
kCGLRPRobust = Enumerant('kCGLRPRobust', 75, )
kCGLRPBackingStore = Enumerant('kCGLRPBackingStore', 76, )
kCGLRPMPSafe = Enumerant('kCGLRPMPSafe', 78, )
kCGLRPWindow = Enumerant('kCGLRPWindow', 80, )
kCGLRPMultiScreen = Enumerant('kCGLRPMultiScreen', 81, )
kCGLRPCompliant = Enumerant('kCGLRPCompliant', 83, )
kCGLRPDisplayMask = Enumerant('kCGLRPDisplayMask', 84, )
kCGLRPBufferModes = Enumerant('kCGLRPBufferModes', 100, )
kCGLRPColorModes = Enumerant('kCGLRPColorModes', 103, )
kCGLRPAccumModes = Enumerant('kCGLRPAccumModes', 104, )
kCGLRPDepthModes = Enumerant('kCGLRPDepthModes', 105, )
kCGLRPStencilModes = Enumerant('kCGLRPStencilModes', 106, )
kCGLRPMaxAuxBuffers = Enumerant('kCGLRPMaxAuxBuffers', 107, )
kCGLRPMaxSampleBuffers = Enumerant('kCGLRPMaxSampleBuffers', 108, )
kCGLRPMaxSamples = Enumerant('kCGLRPMaxSamples', 109, )
kCGLRPSampleModes = Enumerant('kCGLRPSampleModes', 110, )
kCGLRPSampleAlpha = Enumerant('kCGLRPSampleAlpha', 111, )
kCGLRPVideoMemory = Enumerant('kCGLRPVideoMemory', 120, )
kCGLRPTextureMemory = Enumerant('kCGLRPTextureMemory', 121, )
kCGLRPGPUVertProcCapable = Enumerant('kCGLRPGPUVertProcCapable', 122, )
kCGLRPGPUFragProcCapable = Enumerant('kCGLRPGPUFragProcCapable', 123, )
kCGLRPRendererCount = Enumerant('kCGLRPRendererCount', 128, )
kCGLRPOnline = Enumerant('kCGLRPOnline', 129, )
kCGLRPAcceleratedCompute = Enumerant('kCGLRPAcceleratedCompute', 130, )
kCGLRPVideoMemoryMegabytes = Enumerant('kCGLRPVideoMemoryMegabytes', 131, )
kCGLRPTextureMemoryMegabytes = Enumerant('kCGLRPTextureMemoryMegabytes', 132, )
CGLRendererProperty.add(kCGLRPOffScreen)
CGLRendererProperty.add(kCGLRPFullScreen)
CGLRendererProperty.add(kCGLRPRendererID)
CGLRendererProperty.add(kCGLRPAccelerated)
CGLRendererProperty.add(kCGLRPRobust)
CGLRendererProperty.add(kCGLRPBackingStore)
CGLRendererProperty.add(kCGLRPMPSafe)
CGLRendererProperty.add(kCGLRPWindow)
CGLRendererProperty.add(kCGLRPMultiScreen)
CGLRendererProperty.add(kCGLRPCompliant)
CGLRendererProperty.add(kCGLRPDisplayMask)
CGLRendererProperty.add(kCGLRPBufferModes)
CGLRendererProperty.add(kCGLRPColorModes)
CGLRendererProperty.add(kCGLRPAccumModes)
CGLRendererProperty.add(kCGLRPDepthModes)
CGLRendererProperty.add(kCGLRPStencilModes)
CGLRendererProperty.add(kCGLRPMaxAuxBuffers)
CGLRendererProperty.add(kCGLRPMaxSampleBuffers)
CGLRendererProperty.add(kCGLRPMaxSamples)
CGLRendererProperty.add(kCGLRPSampleModes)
CGLRendererProperty.add(kCGLRPSampleAlpha)
CGLRendererProperty.add(kCGLRPVideoMemory)
CGLRendererProperty.add(kCGLRPTextureMemory)
CGLRendererProperty.add(kCGLRPGPUVertProcCapable)
CGLRendererProperty.add(kCGLRPGPUFragProcCapable)
CGLRendererProperty.add(kCGLRPRendererCount)
CGLRendererProperty.add(kCGLRPOnline)
CGLRendererProperty.add(kCGLRPAcceleratedCompute)
CGLRendererProperty.add(kCGLRPVideoMemoryMegabytes)
CGLRendererProperty.add(kCGLRPTextureMemoryMegabytes)

CGLContextEnable = Enum('CGLContextEnable')
cgl.add(CGLContextEnable)

kCGLCESwapRectangle = Enumerant('kCGLCESwapRectangle', 201, )
kCGLCESwapLimit = Enumerant('kCGLCESwapLimit', 203, )
kCGLCERasterization = Enumerant('kCGLCERasterization', 221, )
kCGLCEStateValidation = Enumerant('kCGLCEStateValidation', 301, )
kCGLCESurfaceBackingSize = Enumerant('kCGLCESurfaceBackingSize', 305, )
kCGLCEDisplayListOptimization = Enumerant('kCGLCEDisplayListOptimization', 307, )
kCGLCEMPEngine = Enumerant('kCGLCEMPEngine', 313, )
kCGLCECrashOnRemovedFunctions = Enumerant('kCGLCECrashOnRemovedFunctions', 316, )
CGLContextEnable.add(kCGLCESwapRectangle)
CGLContextEnable.add(kCGLCESwapLimit)
CGLContextEnable.add(kCGLCERasterization)
CGLContextEnable.add(kCGLCEStateValidation)
CGLContextEnable.add(kCGLCESurfaceBackingSize)
CGLContextEnable.add(kCGLCEDisplayListOptimization)
CGLContextEnable.add(kCGLCEMPEngine)
CGLContextEnable.add(kCGLCECrashOnRemovedFunctions)

CGLContextParameter = Enum('CGLContextParameter')
cgl.add(CGLContextParameter)

kCGLCPSwapRectangle = Enumerant('kCGLCPSwapRectangle', 200, )
kCGLCPSwapInterval = Enumerant('kCGLCPSwapInterval', 222, )
kCGLCPDispatchTableSize = Enumerant('kCGLCPDispatchTableSize', 224, )
kCGLCPClientStorage = Enumerant('kCGLCPClientStorage', 226, )
kCGLCPSurfaceTexture = Enumerant('kCGLCPSurfaceTexture', 228, )
kCGLCPSurfaceOrder = Enumerant('kCGLCPSurfaceOrder', 235, )
kCGLCPSurfaceOpacity = Enumerant('kCGLCPSurfaceOpacity', 236, )
kCGLCPSurfaceBackingSize = Enumerant('kCGLCPSurfaceBackingSize', 304, )
kCGLCPSurfaceSurfaceVolatile = Enumerant('kCGLCPSurfaceSurfaceVolatile', 306, )
kCGLCPReclaimResources = Enumerant('kCGLCPReclaimResources', 308, )
kCGLCPCurrentRendererID = Enumerant('kCGLCPCurrentRendererID', 309, )
kCGLCPGPUVertexProcessing = Enumerant('kCGLCPGPUVertexProcessing', 310, )
kCGLCPGPUFragmentProcessing = Enumerant('kCGLCPGPUFragmentProcessing', 311, )
kCGLCPHasDrawable = Enumerant('kCGLCPHasDrawable', 314, )
kCGLCPMPSwapsInFlight = Enumerant('kCGLCPMPSwapsInFlight', 315, )
CGLContextParameter.add(kCGLCPSwapRectangle)
CGLContextParameter.add(kCGLCPSwapInterval)
CGLContextParameter.add(kCGLCPDispatchTableSize)
CGLContextParameter.add(kCGLCPClientStorage)
CGLContextParameter.add(kCGLCPSurfaceTexture)
CGLContextParameter.add(kCGLCPSurfaceOrder)
CGLContextParameter.add(kCGLCPSurfaceOpacity)
CGLContextParameter.add(kCGLCPSurfaceBackingSize)
CGLContextParameter.add(kCGLCPSurfaceSurfaceVolatile)
CGLContextParameter.add(kCGLCPReclaimResources)
CGLContextParameter.add(kCGLCPCurrentRendererID)
CGLContextParameter.add(kCGLCPGPUVertexProcessing)
CGLContextParameter.add(kCGLCPGPUFragmentProcessing)
CGLContextParameter.add(kCGLCPHasDrawable)
CGLContextParameter.add(kCGLCPMPSwapsInFlight)

CGLGlobalOption = Enum('CGLGlobalOption')
cgl.add(CGLGlobalOption)

kCGLGOFormatCacheSize = Enumerant('kCGLGOFormatCacheSize', 501, )
kCGLGOClearFormatCache = Enumerant('kCGLGOClearFormatCache', 502, )
kCGLGORetainRenderers = Enumerant('kCGLGORetainRenderers', 503, )
kCGLGOResetLibrary = Enumerant('kCGLGOResetLibrary', 504, )
kCGLGOUseErrorHandler = Enumerant('kCGLGOUseErrorHandler', 505, )
kCGLGOUseBuildCache = Enumerant('kCGLGOUseBuildCache', 506, )
CGLGlobalOption.add(kCGLGOFormatCacheSize)
CGLGlobalOption.add(kCGLGOClearFormatCache)
CGLGlobalOption.add(kCGLGORetainRenderers)
CGLGlobalOption.add(kCGLGOResetLibrary)
CGLGlobalOption.add(kCGLGOUseErrorHandler)
CGLGlobalOption.add(kCGLGOUseBuildCache)

CGLOpenGLProfile = Enum('CGLOpenGLProfile')
cgl.add(CGLOpenGLProfile)

kCGLOGLPVersion_Legacy = Enumerant('kCGLOGLPVersion_Legacy', 4096, )
kCGLOGLPVersion_3_2_Core = Enumerant('kCGLOGLPVersion_3_2_Core', 12800, )
CGLOpenGLProfile.add(kCGLOGLPVersion_Legacy)
CGLOpenGLProfile.add(kCGLOGLPVersion_3_2_Core)

CGLError = Enum('CGLError')
cgl.add(CGLError)

kCGLNoError = Enumerant('kCGLNoError', 0, )
kCGLBadAttribute = Enumerant('kCGLBadAttribute', 10000, )
kCGLBadProperty = Enumerant('kCGLBadProperty', 10001, )
kCGLBadPixelFormat = Enumerant('kCGLBadPixelFormat', 10002, )
kCGLBadRendererInfo = Enumerant('kCGLBadRendererInfo', 10003, )
kCGLBadContext = Enumerant('kCGLBadContext', 10004, )
kCGLBadDrawable = Enumerant('kCGLBadDrawable', 10005, )
kCGLBadDisplay  = Enumerant('kCGLBadDisplay ', 10006, )
kCGLBadState = Enumerant('kCGLBadState', 10007, )
kCGLBadValue = Enumerant('kCGLBadValue', 10008, )
kCGLBadMatch = Enumerant('kCGLBadMatch', 10009, )
kCGLBadEnumeration = Enumerant('kCGLBadEnumeration', 10010, )
kCGLBadOffScreen = Enumerant('kCGLBadOffScreen', 10011, )
kCGLBadFullScreen = Enumerant('kCGLBadFullScreen', 10012, )
kCGLBadWindow = Enumerant('kCGLBadWindow', 10013, )
kCGLBadAddress = Enumerant('kCGLBadAddress', 10014, )
kCGLBadCodeModule = Enumerant('kCGLBadCodeModule', 10015, )
kCGLBadAlloc = Enumerant('kCGLBadAlloc', 10016, )
kCGLBadConnection = Enumerant('kCGLBadConnection', 10017, )
CGLError.add(kCGLNoError)
CGLError.add(kCGLBadAttribute)
CGLError.add(kCGLBadProperty)
CGLError.add(kCGLBadPixelFormat)
CGLError.add(kCGLBadRendererInfo)
CGLError.add(kCGLBadContext)
CGLError.add(kCGLBadDrawable)
CGLError.add(kCGLBadDisplay )
CGLError.add(kCGLBadState)
CGLError.add(kCGLBadValue)
CGLError.add(kCGLBadMatch)
CGLError.add(kCGLBadEnumeration)
CGLError.add(kCGLBadOffScreen)
CGLError.add(kCGLBadFullScreen)
CGLError.add(kCGLBadWindow)
CGLError.add(kCGLBadAddress)
CGLError.add(kCGLBadCodeModule)
CGLError.add(kCGLBadAlloc)
CGLError.add(kCGLBadConnection)

defines = Enum('defines')
cgl.add(defines)

# 

kCGL0Bit = Enumerant('kCGL0Bit', 1, '')
kCGL10Bit = Enumerant('kCGL10Bit', 256, '')
kCGL128Bit = Enumerant('kCGL128Bit', 65536, '')
kCGL12Bit = Enumerant('kCGL12Bit', 512, '')
kCGL16Bit = Enumerant('kCGL16Bit', 1024, '')
kCGL1Bit = Enumerant('kCGL1Bit', 2, '')
kCGL24Bit = Enumerant('kCGL24Bit', 2048, '')
kCGL2Bit = Enumerant('kCGL2Bit', 4, '')
kCGL32Bit = Enumerant('kCGL32Bit', 4096, '')
kCGL3Bit = Enumerant('kCGL3Bit', 8, '')
kCGL48Bit = Enumerant('kCGL48Bit', 8192, '')
kCGL4Bit = Enumerant('kCGL4Bit', 16, '')
kCGL5Bit = Enumerant('kCGL5Bit', 32, '')
kCGL64Bit = Enumerant('kCGL64Bit', 16384, '')
kCGL6Bit = Enumerant('kCGL6Bit', 64, '')
kCGL8Bit = Enumerant('kCGL8Bit', 128, '')
kCGL96Bit = Enumerant('kCGL96Bit', 32768, '')
kCGLARGB12121212Bit = Enumerant('kCGLARGB12121212Bit', 2097152, '')
kCGLARGB1555Bit = Enumerant('kCGLARGB1555Bit', 1024, '')
kCGLARGB2101010Bit = Enumerant('kCGLARGB2101010Bit', 262144, '')
kCGLARGB4444Bit = Enumerant('kCGLARGB4444Bit', 128, '')
kCGLARGB8888Bit = Enumerant('kCGLARGB8888Bit', 32768, '')
kCGLDoubleBufferBit = Enumerant('kCGLDoubleBufferBit', 8, '')
kCGLMonoscopicBit = Enumerant('kCGLMonoscopicBit', 1, '')
kCGLMultisampleBit = Enumerant('kCGLMultisampleBit', 2, '')
kCGLRGB101010Bit = Enumerant('kCGLRGB101010Bit', 131072, '')
kCGLRGB101010_A8Bit = Enumerant('kCGLRGB101010_A8Bit', 524288, '')
kCGLRGB121212Bit = Enumerant('kCGLRGB121212Bit', 1048576, '')
kCGLRGB161616Bit = Enumerant('kCGLRGB161616Bit', 4194304, '')
kCGLRGB444A8Bit = Enumerant('kCGLRGB444A8Bit', 256, '')
kCGLRGB444Bit = Enumerant('kCGLRGB444Bit', 64, '')
kCGLRGB555A8Bit = Enumerant('kCGLRGB555A8Bit', 2048, '')
kCGLRGB555Bit = Enumerant('kCGLRGB555Bit', 512, '')
kCGLRGB565A8Bit = Enumerant('kCGLRGB565A8Bit', 8192, '')
kCGLRGB565Bit = Enumerant('kCGLRGB565Bit', 4096, '')
kCGLRGB888A8Bit = Enumerant('kCGLRGB888A8Bit', 65536, '')
kCGLRGB888Bit = Enumerant('kCGLRGB888Bit', 16384, '')
kCGLRGBA16161616Bit = Enumerant('kCGLRGBA16161616Bit', 8388608, '')
kCGLRGBAFloat128Bit = Enumerant('kCGLRGBAFloat128Bit', 134217728, '')
kCGLRGBAFloat256Bit = Enumerant('kCGLRGBAFloat256Bit', 536870912, '')
kCGLRGBAFloat64Bit = Enumerant('kCGLRGBAFloat64Bit', 33554432, '')
kCGLRGBFloat128Bit = Enumerant('kCGLRGBFloat128Bit', 67108864, '')
kCGLRGBFloat256Bit = Enumerant('kCGLRGBFloat256Bit', 268435456, '')
kCGLRGBFloat64Bit = Enumerant('kCGLRGBFloat64Bit', 16777216, '')
kCGLSingleBufferBit = Enumerant('kCGLSingleBufferBit', 4, '')
kCGLStereoscopicBit = Enumerant('kCGLStereoscopicBit', 2, '')
kCGLSupersampleBit = Enumerant('kCGLSupersampleBit', 1, '')
kCGLTripleBufferBit = Enumerant('kCGLTripleBufferBit', 16, '')

defines.add(kCGL0Bit)
defines.add(kCGL10Bit)
defines.add(kCGL128Bit)
defines.add(kCGL12Bit)
defines.add(kCGL16Bit)
defines.add(kCGL1Bit)
defines.add(kCGL24Bit)
defines.add(kCGL2Bit)
defines.add(kCGL32Bit)
defines.add(kCGL3Bit)
defines.add(kCGL48Bit)
defines.add(kCGL4Bit)
defines.add(kCGL5Bit)
defines.add(kCGL64Bit)
defines.add(kCGL6Bit)
defines.add(kCGL8Bit)
defines.add(kCGL96Bit)
defines.add(kCGLARGB12121212Bit)
defines.add(kCGLARGB1555Bit)
defines.add(kCGLARGB2101010Bit)
defines.add(kCGLARGB4444Bit)
defines.add(kCGLARGB8888Bit)
defines.add(kCGLDoubleBufferBit)
defines.add(kCGLMonoscopicBit)
defines.add(kCGLMultisampleBit)
defines.add(kCGLRGB101010Bit)
defines.add(kCGLRGB101010_A8Bit)
defines.add(kCGLRGB121212Bit)
defines.add(kCGLRGB161616Bit)
defines.add(kCGLRGB444A8Bit)
defines.add(kCGLRGB444Bit)
defines.add(kCGLRGB555A8Bit)
defines.add(kCGLRGB555Bit)
defines.add(kCGLRGB565A8Bit)
defines.add(kCGLRGB565Bit)
defines.add(kCGLRGB888A8Bit)
defines.add(kCGLRGB888Bit)
defines.add(kCGLRGBA16161616Bit)
defines.add(kCGLRGBAFloat128Bit)
defines.add(kCGLRGBAFloat256Bit)
defines.add(kCGLRGBAFloat64Bit)
defines.add(kCGLRGBFloat128Bit)
defines.add(kCGLRGBFloat256Bit)
defines.add(kCGLRGBFloat64Bit)
defines.add(kCGLSingleBufferBit)
defines.add(kCGLStereoscopicBit)
defines.add(kCGLSupersampleBit)
defines.add(kCGLTripleBufferBit)

# CGL_VERSION_1_0

CGLChoosePixelFormat = Function('CGLChoosePixelFormat')
CGLChoosePixelFormat.ret = Return('CGLError')
CGLChoosePixelFormat.add( Input( 'attribs','const CGLPixelFormatAttribute *' ))
CGLChoosePixelFormat.add( Output( 'pix','CGLPixelFormatObj *' ))
CGLChoosePixelFormat.add( Output( 'npix','GLint *' ))
CGLChoosePixelFormat.version = ''
CGLChoosePixelFormat.category = 'CGL_VERSION_1_0'
CGLChoosePixelFormat.trace = True
CGLChoosePixelFormat.play = True
cgl.add(CGLChoosePixelFormat)

CGLClearDrawable = Function('CGLClearDrawable')
CGLClearDrawable.ret = Return('CGLError')
CGLClearDrawable.add( Input( 'ctx','CGLContextObj' ))
CGLClearDrawable.version = ''
CGLClearDrawable.category = 'CGL_VERSION_1_0'
CGLClearDrawable.trace = True
CGLClearDrawable.play = True
cgl.add(CGLClearDrawable)

CGLCopyContext = Function('CGLCopyContext')
CGLCopyContext.ret = Return('CGLError')
CGLCopyContext.add( Input( 'src','CGLContextObj' ))
CGLCopyContext.add( Input( 'dst','CGLContextObj' ))
CGLCopyContext.add( Input( 'mask','GLbitfield' ))
CGLCopyContext.version = ''
CGLCopyContext.category = 'CGL_VERSION_1_0'
CGLCopyContext.trace = True
CGLCopyContext.play = True
cgl.add(CGLCopyContext)

CGLCreateContext = Function('CGLCreateContext')
CGLCreateContext.ret = Return('CGLError')
CGLCreateContext.add( Input( 'pix','CGLPixelFormatObj' ))
CGLCreateContext.add( Input( 'share','CGLContextObj' ))
CGLCreateContext.add( Output( 'ctx','CGLContextObj *' ))
CGLCreateContext.version = ''
CGLCreateContext.category = 'CGL_VERSION_1_0'
CGLCreateContext.trace = True
CGLCreateContext.play = True
cgl.add(CGLCreateContext)

CGLDescribePixelFormat = Function('CGLDescribePixelFormat')
CGLDescribePixelFormat.ret = Return('CGLError')
CGLDescribePixelFormat.add( Input( 'pix','CGLPixelFormatObj' ))
CGLDescribePixelFormat.add( Input( 'pix_num','GLint' ))
CGLDescribePixelFormat.add( Input( 'attrib','CGLPixelFormatAttribute' ))
CGLDescribePixelFormat.add( Output( 'value','GLint *' ))
CGLDescribePixelFormat.version = ''
CGLDescribePixelFormat.category = 'CGL_VERSION_1_0'
CGLDescribePixelFormat.trace = True
CGLDescribePixelFormat.play = True
cgl.add(CGLDescribePixelFormat)

CGLDescribeRenderer = Function('CGLDescribeRenderer')
CGLDescribeRenderer.ret = Return('CGLError')
CGLDescribeRenderer.add( Input( 'rend','CGLRendererInfoObj' ))
CGLDescribeRenderer.add( Input( 'rend_num','GLint' ))
CGLDescribeRenderer.add( Input( 'prop','CGLRendererProperty' ))
CGLDescribeRenderer.add( Output( 'value','GLint *' ))
CGLDescribeRenderer.version = ''
CGLDescribeRenderer.category = 'CGL_VERSION_1_0'
CGLDescribeRenderer.trace = True
CGLDescribeRenderer.play = True
cgl.add(CGLDescribeRenderer)

CGLDestroyContext = Function('CGLDestroyContext')
CGLDestroyContext.ret = Return('CGLError')
CGLDestroyContext.add( Input( 'ctx','CGLContextObj' ))
CGLDestroyContext.version = ''
CGLDestroyContext.category = 'CGL_VERSION_1_0'
CGLDestroyContext.trace = True
CGLDestroyContext.play = True
cgl.add(CGLDestroyContext)

CGLDestroyPixelFormat = Function('CGLDestroyPixelFormat')
CGLDestroyPixelFormat.ret = Return('CGLError')
CGLDestroyPixelFormat.add( Input( 'pix','CGLPixelFormatObj' ))
CGLDestroyPixelFormat.version = ''
CGLDestroyPixelFormat.category = 'CGL_VERSION_1_0'
CGLDestroyPixelFormat.trace = True
CGLDestroyPixelFormat.play = True
cgl.add(CGLDestroyPixelFormat)

CGLDestroyRendererInfo = Function('CGLDestroyRendererInfo')
CGLDestroyRendererInfo.ret = Return('CGLError')
CGLDestroyRendererInfo.add( Input( 'rend','CGLRendererInfoObj' ))
CGLDestroyRendererInfo.version = ''
CGLDestroyRendererInfo.category = 'CGL_VERSION_1_0'
CGLDestroyRendererInfo.trace = True
CGLDestroyRendererInfo.play = True
cgl.add(CGLDestroyRendererInfo)

CGLDisable = Function('CGLDisable')
CGLDisable.ret = Return('CGLError')
CGLDisable.add( Input( 'ctx','CGLContextObj' ))
CGLDisable.add( Input( 'pname','CGLContextEnable' ))
CGLDisable.version = ''
CGLDisable.category = 'CGL_VERSION_1_0'
CGLDisable.trace = True
CGLDisable.play = True
cgl.add(CGLDisable)

CGLEnable = Function('CGLEnable')
CGLEnable.ret = Return('CGLError')
CGLEnable.add( Input( 'ctx','CGLContextObj' ))
CGLEnable.add( Input( 'pname','CGLContextEnable' ))
CGLEnable.version = ''
CGLEnable.category = 'CGL_VERSION_1_0'
CGLEnable.trace = True
CGLEnable.play = True
cgl.add(CGLEnable)

CGLErrorString = Function('CGLErrorString')
CGLErrorString.ret = Return('const char *')
CGLErrorString.add( Input( 'error','CGLError' ))
CGLErrorString.version = ''
CGLErrorString.category = 'CGL_VERSION_1_0'
CGLErrorString.trace = True
CGLErrorString.play = True
cgl.add(CGLErrorString)

CGLFlushDrawable = Function('CGLFlushDrawable')
CGLFlushDrawable.ret = Return('CGLError')
CGLFlushDrawable.add( Input( 'ctx','CGLContextObj' ))
CGLFlushDrawable.version = ''
CGLFlushDrawable.category = 'CGL_VERSION_1_0'
CGLFlushDrawable.trace = True
CGLFlushDrawable.play = True
cgl.add(CGLFlushDrawable)

CGLGetOffScreen = Function('CGLGetOffScreen')
CGLGetOffScreen.ret = Return('CGLError')
CGLGetOffScreen.add( Input( 'ctx','CGLContextObj' ))
CGLGetOffScreen.add( Input( 'width','GLsizei *' ))
CGLGetOffScreen.add( Input( 'height','GLsizei *' ))
CGLGetOffScreen.add( Input( 'rowbytes','GLsizei *' ))
CGLGetOffScreen.add( Input( 'baseaddr','void **' ))
CGLGetOffScreen.version = ''
CGLGetOffScreen.category = 'CGL_VERSION_1_0'
CGLGetOffScreen.trace = True
CGLGetOffScreen.play = True
cgl.add(CGLGetOffScreen)

CGLGetOption = Function('CGLGetOption')
CGLGetOption.ret = Return('CGLError')
CGLGetOption.add( Input( 'pname','CGLGlobalOption' ))
CGLGetOption.add( Input( 'param','GLint *' ))
CGLGetOption.version = ''
CGLGetOption.category = 'CGL_VERSION_1_0'
CGLGetOption.trace = True
CGLGetOption.play = True
cgl.add(CGLGetOption)

CGLGetParameter = Function('CGLGetParameter')
CGLGetParameter.ret = Return('CGLError')
CGLGetParameter.add( Input( 'ctx','CGLContextObj' ))
CGLGetParameter.add( Input( 'pname','CGLContextEnable' ))
CGLGetParameter.add( Output( 'params','GLint *' ))
CGLGetParameter.version = ''
CGLGetParameter.category = 'CGL_VERSION_1_0'
CGLGetParameter.trace = True
CGLGetParameter.play = True
cgl.add(CGLGetParameter)

CGLGetVersion = Function('CGLGetVersion')
CGLGetVersion.ret = Return('void')
CGLGetVersion.add( Output( 'majorvers','GLint *' ))
CGLGetVersion.add( Output( 'minorvers','GLint *' ))
CGLGetVersion.version = ''
CGLGetVersion.category = 'CGL_VERSION_1_0'
CGLGetVersion.trace = True
CGLGetVersion.play = True
cgl.add(CGLGetVersion)

CGLGetVirtualScreen = Function('CGLGetVirtualScreen')
CGLGetVirtualScreen.ret = Return('CGLError')
CGLGetVirtualScreen.add( Input( 'ctx','CGLContextObj' ))
CGLGetVirtualScreen.add( Output( 'screen','GLint *' ))
CGLGetVirtualScreen.version = ''
CGLGetVirtualScreen.category = 'CGL_VERSION_1_0'
CGLGetVirtualScreen.trace = True
CGLGetVirtualScreen.play = True
cgl.add(CGLGetVirtualScreen)

CGLIsEnabled = Function('CGLIsEnabled')
CGLIsEnabled.ret = Return('CGLError')
CGLIsEnabled.add( Input( 'ctx','CGLContextObj' ))
CGLIsEnabled.add( Input( 'pname','CGLContextEnable' ))
CGLIsEnabled.add( Output( 'enable','GLint *' ))
CGLIsEnabled.version = ''
CGLIsEnabled.category = 'CGL_VERSION_1_0'
CGLIsEnabled.trace = True
CGLIsEnabled.play = True
cgl.add(CGLIsEnabled)

CGLQueryRendererInfo = Function('CGLQueryRendererInfo')
CGLQueryRendererInfo.ret = Return('CGLError')
CGLQueryRendererInfo.add( Input( 'display_mask','GLuint' ))
CGLQueryRendererInfo.add( Output( 'rend','CGLRendererInfoObj *' ))
CGLQueryRendererInfo.add( Output( 'nrend','GLint *' ))
CGLQueryRendererInfo.version = ''
CGLQueryRendererInfo.category = 'CGL_VERSION_1_0'
CGLQueryRendererInfo.trace = True
CGLQueryRendererInfo.play = True
cgl.add(CGLQueryRendererInfo)

CGLSetFullScreen = Function('CGLSetFullScreen')
CGLSetFullScreen.ret = Return('CGLError')
CGLSetFullScreen.add( Input( 'ctx','CGLContextObj' ))
CGLSetFullScreen.version = ''
CGLSetFullScreen.category = 'CGL_VERSION_1_0'
CGLSetFullScreen.trace = True
CGLSetFullScreen.play = True
cgl.add(CGLSetFullScreen)

CGLSetOffScreen = Function('CGLSetOffScreen')
CGLSetOffScreen.ret = Return('CGLError')
CGLSetOffScreen.add( Input( 'ctx','CGLContextObj' ))
CGLSetOffScreen.add( Input( 'width','GLsizei' ))
CGLSetOffScreen.add( Input( 'height','GLsizei' ))
CGLSetOffScreen.add( Input( 'rowbytes','GLsizei' ))
CGLSetOffScreen.add( Input( 'baseaddr','void *' ))
CGLSetOffScreen.version = ''
CGLSetOffScreen.category = 'CGL_VERSION_1_0'
CGLSetOffScreen.trace = True
CGLSetOffScreen.play = True
cgl.add(CGLSetOffScreen)

CGLSetOption = Function('CGLSetOption')
CGLSetOption.ret = Return('CGLError')
CGLSetOption.add( Input( 'pname','CGLGlobalOption' ))
CGLSetOption.add( Input( 'param','GLint' ))
CGLSetOption.version = ''
CGLSetOption.category = 'CGL_VERSION_1_0'
CGLSetOption.trace = True
CGLSetOption.play = True
cgl.add(CGLSetOption)

CGLSetParameter = Function('CGLSetParameter')
CGLSetParameter.ret = Return('CGLError')
CGLSetParameter.add( Input( 'ctx','CGLContextObj' ))
CGLSetParameter.add( Input( 'pname','CGLContextEnable' ))
CGLSetParameter.add( Input( 'params','const GLint *' ))
CGLSetParameter.version = ''
CGLSetParameter.category = 'CGL_VERSION_1_0'
CGLSetParameter.trace = True
CGLSetParameter.play = True
cgl.add(CGLSetParameter)

CGLSetVirtualScreen = Function('CGLSetVirtualScreen')
CGLSetVirtualScreen.ret = Return('CGLError')
CGLSetVirtualScreen.add( Input( 'ctx','CGLContextObj' ))
CGLSetVirtualScreen.add( Input( 'screen','GLint' ))
CGLSetVirtualScreen.version = ''
CGLSetVirtualScreen.category = 'CGL_VERSION_1_0'
CGLSetVirtualScreen.trace = True
CGLSetVirtualScreen.play = True
cgl.add(CGLSetVirtualScreen)

# CGL_VERSION_1_1

CGLCreatePBuffer = Function('CGLCreatePBuffer')
CGLCreatePBuffer.ret = Return('CGLError')
CGLCreatePBuffer.add( Input( 'width','GLsizei' ))
CGLCreatePBuffer.add( Input( 'height','GLsizei' ))
CGLCreatePBuffer.add( Input( 'target','GLenum' ))
CGLCreatePBuffer.add( Input( 'internalFormat','GLenum' ))
CGLCreatePBuffer.add( Input( 'max_level','GLint' ))
CGLCreatePBuffer.add( Input( 'pbuffer','CGLPBufferObj *' ))
CGLCreatePBuffer.version = ''
CGLCreatePBuffer.category = 'CGL_VERSION_1_1'
CGLCreatePBuffer.trace = True
CGLCreatePBuffer.play = True
cgl.add(CGLCreatePBuffer)

CGLDescribePBuffer = Function('CGLDescribePBuffer')
CGLDescribePBuffer.ret = Return('CGLError')
CGLDescribePBuffer.add( Input( 'pbuffer','CGLPBufferObj' ))
CGLDescribePBuffer.add( Input( 'width','GLsizei *' ))
CGLDescribePBuffer.add( Input( 'height','GLsizei *' ))
CGLDescribePBuffer.add( Input( 'target','GLenum *' ))
CGLDescribePBuffer.add( Input( 'internalFormat','GLenum *' ))
CGLDescribePBuffer.add( Input( 'mipmap','GLint *' ))
CGLDescribePBuffer.version = ''
CGLDescribePBuffer.category = 'CGL_VERSION_1_1'
CGLDescribePBuffer.trace = True
CGLDescribePBuffer.play = True
cgl.add(CGLDescribePBuffer)

CGLDestroyPBuffer = Function('CGLDestroyPBuffer')
CGLDestroyPBuffer.ret = Return('CGLError')
CGLDestroyPBuffer.add( Input( 'pbuffer','CGLPBufferObj' ))
CGLDestroyPBuffer.version = ''
CGLDestroyPBuffer.category = 'CGL_VERSION_1_1'
CGLDestroyPBuffer.trace = True
CGLDestroyPBuffer.play = True
cgl.add(CGLDestroyPBuffer)

CGLGetPBuffer = Function('CGLGetPBuffer')
CGLGetPBuffer.ret = Return('CGLError')
CGLGetPBuffer.add( Input( 'ctx','CGLContextObj' ))
CGLGetPBuffer.add( Input( 'pbuffer','CGLPBufferObj *' ))
CGLGetPBuffer.add( Input( 'face','GLenum *' ))
CGLGetPBuffer.add( Input( 'level','GLint *' ))
CGLGetPBuffer.add( Input( 'screen','GLint *' ))
CGLGetPBuffer.version = ''
CGLGetPBuffer.category = 'CGL_VERSION_1_1'
CGLGetPBuffer.trace = True
CGLGetPBuffer.play = True
cgl.add(CGLGetPBuffer)

CGLSetPBuffer = Function('CGLSetPBuffer')
CGLSetPBuffer.ret = Return('CGLError')
CGLSetPBuffer.add( Input( 'ctx','CGLContextObj' ))
CGLSetPBuffer.add( Input( 'pbuffer','CGLPBufferObj' ))
CGLSetPBuffer.add( Input( 'face','GLenum' ))
CGLSetPBuffer.add( Input( 'level','GLint' ))
CGLSetPBuffer.add( Input( 'screen','GLint' ))
CGLSetPBuffer.version = ''
CGLSetPBuffer.category = 'CGL_VERSION_1_1'
CGLSetPBuffer.trace = True
CGLSetPBuffer.play = True
cgl.add(CGLSetPBuffer)

CGLTexImagePBuffer = Function('CGLTexImagePBuffer')
CGLTexImagePBuffer.ret = Return('CGLError')
CGLTexImagePBuffer.add( Input( 'ctx','CGLContextObj' ))
CGLTexImagePBuffer.add( Input( 'pbuffer','CGLPBufferObj' ))
CGLTexImagePBuffer.add( Input( 'source','GLenum' ))
CGLTexImagePBuffer.version = ''
CGLTexImagePBuffer.category = 'CGL_VERSION_1_1'
CGLTexImagePBuffer.trace = True
CGLTexImagePBuffer.play = True
cgl.add(CGLTexImagePBuffer)

# CGL_VERSION_1_2

CGLGetContextRetainCount = Function('CGLGetContextRetainCount')
CGLGetContextRetainCount.ret = Return('GLuint')
CGLGetContextRetainCount.add( Input( 'ctx','CGLContextObj' ))
CGLGetContextRetainCount.version = ''
CGLGetContextRetainCount.category = 'CGL_VERSION_1_2'
CGLGetContextRetainCount.trace = True
CGLGetContextRetainCount.play = True
cgl.add(CGLGetContextRetainCount)

CGLGetGlobalOption = Function('CGLGetGlobalOption')
CGLGetGlobalOption.ret = Return('CGLError')
CGLGetGlobalOption.add( Input( 'pname','CGLGlobalOption' ))
CGLGetGlobalOption.add( Input( 'params','GLint *' ))
CGLGetGlobalOption.version = ''
CGLGetGlobalOption.category = 'CGL_VERSION_1_2'
CGLGetGlobalOption.trace = True
CGLGetGlobalOption.play = True
cgl.add(CGLGetGlobalOption)

CGLGetPBufferRetainCount = Function('CGLGetPBufferRetainCount')
CGLGetPBufferRetainCount.ret = Return('CGLError')
CGLGetPBufferRetainCount.add( Input( 'pbuffer','CGLPBufferObj' ))
CGLGetPBufferRetainCount.version = ''
CGLGetPBufferRetainCount.category = 'CGL_VERSION_1_2'
CGLGetPBufferRetainCount.trace = True
CGLGetPBufferRetainCount.play = True
cgl.add(CGLGetPBufferRetainCount)

CGLGetPixelFormat = Function('CGLGetPixelFormat')
CGLGetPixelFormat.ret = Return('CGLPixelFormatObj')
CGLGetPixelFormat.add( Input( 'ctx','CGLContextObj' ))
CGLGetPixelFormat.version = ''
CGLGetPixelFormat.category = 'CGL_VERSION_1_2'
CGLGetPixelFormat.trace = True
CGLGetPixelFormat.play = True
cgl.add(CGLGetPixelFormat)

CGLGetPixelFormatRetainCount = Function('CGLGetPixelFormatRetainCount')
CGLGetPixelFormatRetainCount.ret = Return('GLuint')
CGLGetPixelFormatRetainCount.add( Input( 'pix','CGLPixelFormatObj' ))
CGLGetPixelFormatRetainCount.version = ''
CGLGetPixelFormatRetainCount.category = 'CGL_VERSION_1_2'
CGLGetPixelFormatRetainCount.trace = True
CGLGetPixelFormatRetainCount.play = True
cgl.add(CGLGetPixelFormatRetainCount)

CGLLockContext = Function('CGLLockContext')
CGLLockContext.ret = Return('CGLError')
CGLLockContext.add( Input( 'ctx','CGLContextObj' ))
CGLLockContext.version = ''
CGLLockContext.category = 'CGL_VERSION_1_2'
CGLLockContext.trace = True
CGLLockContext.play = True
cgl.add(CGLLockContext)

CGLReleaseContext = Function('CGLReleaseContext')
CGLReleaseContext.ret = Return('void')
CGLReleaseContext.add( Input( 'ctx','CGLContextObj' ))
CGLReleaseContext.version = ''
CGLReleaseContext.category = 'CGL_VERSION_1_2'
CGLReleaseContext.trace = True
CGLReleaseContext.play = True
cgl.add(CGLReleaseContext)

CGLReleasePBuffer = Function('CGLReleasePBuffer')
CGLReleasePBuffer.ret = Return('CGLError')
CGLReleasePBuffer.add( Input( 'pbuffer','CGLPBufferObj' ))
CGLReleasePBuffer.version = ''
CGLReleasePBuffer.category = 'CGL_VERSION_1_2'
CGLReleasePBuffer.trace = True
CGLReleasePBuffer.play = True
cgl.add(CGLReleasePBuffer)

CGLReleasePixelFormat = Function('CGLReleasePixelFormat')
CGLReleasePixelFormat.ret = Return('void')
CGLReleasePixelFormat.add( Input( 'pix','CGLPixelFormatObj' ))
CGLReleasePixelFormat.version = ''
CGLReleasePixelFormat.category = 'CGL_VERSION_1_2'
CGLReleasePixelFormat.trace = True
CGLReleasePixelFormat.play = True
cgl.add(CGLReleasePixelFormat)

CGLRetainContext = Function('CGLRetainContext')
CGLRetainContext.ret = Return('CGLContextObj')
CGLRetainContext.add( Input( 'ctx','CGLContextObj' ))
CGLRetainContext.version = ''
CGLRetainContext.category = 'CGL_VERSION_1_2'
CGLRetainContext.trace = True
CGLRetainContext.play = True
cgl.add(CGLRetainContext)

CGLRetainPBuffer = Function('CGLRetainPBuffer')
CGLRetainPBuffer.ret = Return('CGLError')
CGLRetainPBuffer.add( Input( 'pbuffer','CGLPBufferObj' ))
CGLRetainPBuffer.version = ''
CGLRetainPBuffer.category = 'CGL_VERSION_1_2'
CGLRetainPBuffer.trace = True
CGLRetainPBuffer.play = True
cgl.add(CGLRetainPBuffer)

CGLRetainPixelFormat = Function('CGLRetainPixelFormat')
CGLRetainPixelFormat.ret = Return('CGLPixelFormatObj')
CGLRetainPixelFormat.add( Input( 'pix','CGLPixelFormatObj' ))
CGLRetainPixelFormat.version = ''
CGLRetainPixelFormat.category = 'CGL_VERSION_1_2'
CGLRetainPixelFormat.trace = True
CGLRetainPixelFormat.play = True
cgl.add(CGLRetainPixelFormat)

CGLSetGlobalOption = Function('CGLSetGlobalOption')
CGLSetGlobalOption.ret = Return('CGLError')
CGLSetGlobalOption.add( Input( 'pname','CGLGlobalOption' ))
CGLSetGlobalOption.add( Input( 'params','const GLint *' ))
CGLSetGlobalOption.version = ''
CGLSetGlobalOption.category = 'CGL_VERSION_1_2'
CGLSetGlobalOption.trace = True
CGLSetGlobalOption.play = True
cgl.add(CGLSetGlobalOption)

CGLUnlockContext = Function('CGLUnlockContext')
CGLUnlockContext.ret = Return('CGLError')
CGLUnlockContext.add( Input( 'ctx','CGLContextObj' ))
CGLUnlockContext.version = ''
CGLUnlockContext.category = 'CGL_VERSION_1_2'
CGLUnlockContext.trace = True
CGLUnlockContext.play = True
cgl.add(CGLUnlockContext)

# CGL_VERSION_1_3

CGLGetCurrentContext = Function('CGLGetCurrentContext')
CGLGetCurrentContext.ret = Return('CGLContextObj')
CGLGetCurrentContext.version = ''
CGLGetCurrentContext.category = 'CGL_VERSION_1_3'
CGLGetCurrentContext.trace = True
CGLGetCurrentContext.play = True
cgl.add(CGLGetCurrentContext)

CGLGetShareGroup = Function('CGLGetShareGroup')
CGLGetShareGroup.ret = Return('CGLShareGroupObj')
CGLGetShareGroup.add( Input( 'ctx','CGLContextObj' ))
CGLGetShareGroup.version = ''
CGLGetShareGroup.category = 'CGL_VERSION_1_3'
CGLGetShareGroup.trace = True
CGLGetShareGroup.play = True
cgl.add(CGLGetShareGroup)

CGLGetSurface = Function('CGLGetSurface')
CGLGetSurface.ret = Return('CGLError')
CGLGetSurface.add( Input( 'ctx','CGLContextObj' ))
CGLGetSurface.add( Input( 'conn','CGSConnectionID *' ))
CGLGetSurface.add( Input( 'win','CGSWindowID *' ))
CGLGetSurface.add( Input( 'srf','CGSSurfaceID *' ))
CGLGetSurface.version = ''
CGLGetSurface.category = 'CGL_VERSION_1_3'
CGLGetSurface.trace = True
CGLGetSurface.play = True
cgl.add(CGLGetSurface)

CGLSetCurrentContext = Function('CGLSetCurrentContext')
CGLSetCurrentContext.ret = Return('CGLError')
CGLSetCurrentContext.add( Input( 'ctx','CGLContextObj' ))
CGLSetCurrentContext.version = ''
CGLSetCurrentContext.category = 'CGL_VERSION_1_3'
CGLSetCurrentContext.trace = True
CGLSetCurrentContext.play = True
cgl.add(CGLSetCurrentContext)

CGLSetSurface = Function('CGLSetSurface')
CGLSetSurface.ret = Return('CGLError')
CGLSetSurface.add( Input( 'ctx','CGLContextObj' ))
CGLSetSurface.add( Input( 'conn','CGSConnectionID' ))
CGLSetSurface.add( Input( 'win','CGSWindowID' ))
CGLSetSurface.add( Input( 'srf','CGSSurfaceID' ))
CGLSetSurface.version = ''
CGLSetSurface.category = 'CGL_VERSION_1_3'
CGLSetSurface.trace = True
CGLSetSurface.play = True
cgl.add(CGLSetSurface)

CGLTexImageIOSurface2D = Function('CGLTexImageIOSurface2D')
CGLTexImageIOSurface2D.ret = Return('CGLError')
CGLTexImageIOSurface2D.add( Input( 'ctx','CGLContextObj' ))
CGLTexImageIOSurface2D.add( Input( 'target','GLenum' ))
CGLTexImageIOSurface2D.add( Input( 'internal_format','GLenum' ))
CGLTexImageIOSurface2D.add( Input( 'width','GLsizei' ))
CGLTexImageIOSurface2D.add( Input( 'height','GLsizei' ))
CGLTexImageIOSurface2D.add( Input( 'format','GLenum' ))
CGLTexImageIOSurface2D.add( Input( 'type','GLenum' ))
CGLTexImageIOSurface2D.add( Input( 'ioSurface','IOSurfaceRef' ))
CGLTexImageIOSurface2D.add( Input( 'plane','GLuint' ))
CGLTexImageIOSurface2D.version = ''
CGLTexImageIOSurface2D.category = 'CGL_VERSION_1_3'
CGLTexImageIOSurface2D.trace = True
CGLTexImageIOSurface2D.play = True
cgl.add(CGLTexImageIOSurface2D)

CGLUpdateContext = Function('CGLUpdateContext')
CGLUpdateContext.ret = Return('CGLError')
CGLUpdateContext.add( Input( 'ctx','CGLContextObj' ))
CGLUpdateContext.version = ''
CGLUpdateContext.category = 'CGL_VERSION_1_3'
CGLUpdateContext.trace = True
CGLUpdateContext.play = True
cgl.add(CGLUpdateContext)

