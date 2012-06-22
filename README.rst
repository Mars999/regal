Regal
=====

https://github.com/p3/regal

OpenGL portability layer for OpenGL 2.x, 3.x, 4.x, Core contexts and ES 2.0

+---------------+----------------------------------------------------------------------+
|  **Warning**  |  Regal is pre-alpha software, it is available here for evaluation    |
|               |  and to play with the examples.  Don't use it in your projects yet.  |
|               |  You have been warned.                                               |
+---------------+----------------------------------------------------------------------+

Goals
-----

Regal is a portable OpenGL layer on top of existing OpenGL implementations.
Compile and link an app against Regal and deploy on various OpenGL implementations
including compatibility, core and ES 2.0 OpenGL contexts.

* Portability
    Consistent API that runs on all major platforms: Windows, Linux, Mac, iOS, and Android

* Compatible
    Immediate mode, fixed function, GL_QUADS work everywhere, emulated as necessary.

* Modern OpenGL API
    Direct State Access (DSA) and Vertex Array Object (VAO), emulated as necessary.

* Open Source
    There is nothing behind the curtain.
    You can see what Regal is doing and change it if you need to.

* Ease of Use
    Set breakpoints on OpenGL functions.  Step into the code.  Inspect state.
    
* Efficiency
    If it cannot be implemented efficiently in Regal, it is not universally supported.
    For example, tessellation support requires tessellation hardware.

Deployment
----------

* Most code remains unchanged.
* Optionally **#include <GL/Regal.h>**
* Link with **regal32.dll**, **libRegal.so** or **libRegal.dylib**

From an application developer's perspective, Regal just looks like an OpenGL implementation.
You link with it instead of your platform's OpenGL library or framework, and that's really
all you have to do to use Regal.  The rest of your code can remain unchanged.

Features
--------

* Emulation

  - Fixed function texturing, lighting and fog.
  - Direct State Access extension 

    http://www.opengl.org/registry/specs/EXT/direct_state_access.txt

  - GL_EXT_debug_marker extension

    http://www.khronos.org/registry/gles/extensions/EXT/EXT_debug_marker.txt

* OpenGL error checking

* Logging

  Regal supports detailed logging for development purposes.

  - **Error**       -- Fatal and non-fatal Regal runtime errors.
  - **Warning**     -- Non-fatal Regal warnings.
  - **Info**        -- Informational messages.
  - **Regal**       -- Regal API calls.
  - **OpenGL**      -- OpenGL API calls.
  - **Internal**    -- Internal Regal calls.

  Build-time configuration:

  - **REGAL_LOG_ERROR** 
  - **REGAL_LOG_WARNING**
  - **REGAL_LOG_INFO**
  - **REGAL_LOG_REGAL**
  - **REGAL_LOG_OPENGL**
  - **REGAL_LOG_INTERNAL**
  
  * Debug mode: All logging supported with error, warning and info enabled.
  * Release mode: Support for Regal, OpenGL and internal logging disabled by default.

  Environment variable configuration:

  - **REGAL_LOG_ERROR**
  - **REGAL_LOG_WARNING**
  - **REGAL_LOG_INFO**
  - **REGAL_LOG_REGAL**
  - **REGAL_LOG_OPENGL**
  - **REGAL_LOG_INTERNAL**
  - **REGAL_LOG_API**       --- Regal + OpenGL
  - **REGAL_LOG_NONE**      --- disable all logging
  
  Environment variable lookup is globally disabled by defining **REGAL_NO_GETENV**
  at compile-time.

  Runtime configuration via **GL_REGAL_log** extension: (**glEnable/glDisable/glIsEnabled**)

  - **GL_LOG_ERROR_REGAL**
  - **GL_LOG_WARNING_REGAL**
  - **GL_LOG_INFO_REGAL**
  - **GL_LOG_REGAL_REGAL**
  - **GL_LOG_OPENGL_REGAL**
  - **GL_LOG_INTERNAL_REGAL**
  
* Spoofing OpenGL vendor, renderer, version and extension strings

  Build-time configuration

  - **REGAL_GL_VENDOR**
  - **REGAL_GL_RENDERER**
  - **REGAL_GL_VERSION**
  - **REGAL_GL_EXTENSION**
  
  Environment variable configuration:

  - **REGAL_GL_VENDOR**
  - **REGAL_GL_RENDERER**
  - **REGAL_GL_VERSION**
  - **REGAL_GL_EXTENSION**

  Environment variable lookup is globally disabled by defining **REGAL_NO_GETENV**
  at compile-time.

Planned Features
----------------

* Debug label.
* Debug output.
* Display list emulation.

Limitations
-----------

* Incomplete implementation, so far.
* Limited GLSL language support.
* GL_QUADS only works in immediate mode or with DrawArrays for ES and core profiles.

