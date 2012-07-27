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
    Consistent OpenGL API that runs on all major platforms:
    Windows, Linux, Mac, iOS, and Android

* Compatible
    Immediate mode, fixed function, GL_QUADS work everywhere, emulated as necessary.

* Modern OpenGL API
    Direct State Access (DSA) and Vertex Array Object (VAO), emulated as necessary.

* Open Source
    There is nothing behind the curtain.
    You can see what Regal is doing and change it if needed.

* Ease of Use
    Set breakpoints on OpenGL functions.
    Step into the code.
    Inspect state.
    
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

  - Fixed function and DSA emulation enabled by default.

  - Build-time configuration: 
  
    - **REGAL_NO_EMULATION**      -- Disable the use of emulation
    - **REGAL_FORCE_EMULATION**   -- Force the use of emulation, even for compatibility contexts with DSA

  - Environment variable configuration:

    - **REGAL_NO_EMULATION**      -- Disable the use of emulation
    - **REGAL_FORCE_EMULATION**   -- Force the use of emulation, even for compatibility contexts with DSA

* OpenGL error checking

  - Disabled by default.

  - Build-time configuration: **REGAL_ERROR** 
  
  - Environment variable configuration: **REGAL_ERROR**

* Browser-based interface

  - Enabled by default.

  - **REGAL_NO_HTTP**         --- Build-time and environment variable enable/disable.
  - **REGAL_HTTP_PORT**       --- Port for HTTP connections (8080 by default)
  - **REGAL_HTTP_LOG_LIMIT**  --- Number of lines of logging buffered

  - `http://127.0.0.1:8080/log`_                          --- View log
  - `http://127.0.0.1:8080/glEnable?GL_LOG_APP_REGAL`_    --- Enable/disable application logging
  - `http://127.0.0.1:8080/glEnable?GL_LOG_DRIVER_REGAL`_ --- Enable/disable driver logging
  - `http://127.0.0.1:8080`_                              --- State information

.. _http://127.0.0.1:8080/log:                          http://127.0.0.1:8080/log
.. _http://127.0.0.1:8080/glEnable?GL_LOG_APP_REGAL:    http://127.0.0.1:8080/glEnable?GL_LOG_APP_REGAL
.. _http://127.0.0.1:8080/glEnable?GL_LOG_DRIVER_REGAL: http://127.0.0.1:8080/glEnable?GL_LOG_DRIVER_REGAL
.. _http://127.0.0.1:8080:                              http://127.0.0.1:8080

* Logging

  Regal supports detailed logging for development purposes.

  - **Error**       -- Fatal and non-fatal Regal runtime errors.
  - **Warning**     -- Non-fatal Regal warnings.
  - **Info**        -- Informational messages.
  - **App**         -- Application calls into Regal.
  - **Driver**      -- Regal calls into OpenGL.
  - **Internal**    -- Internal Regal calls.
  - **Http**        -- HTTP traffic logging.

  Build-time configuration:

  - **REGAL_LOG_ERROR** 
  - **REGAL_LOG_WARNING**
  - **REGAL_LOG_INFO**
  - **REGAL_LOG_APP**
  - **REGAL_LOG_DRIVER**
  - **REGAL_LOG_INTERNAL**
  - **REGAL_LOG_HTTP**
  
  * Debug mode: All logging supported with error, warning, info and http logging enabled.
  * Release mode: Support for application, driver and internal logging disabled by default.

  Environment variable configuration:

  - **REGAL_LOG_ERROR**
  - **REGAL_LOG_WARNING**
  - **REGAL_LOG_INFO**
  - **REGAL_LOG_APP**
  - **REGAL_LOG_DRIVER**
  - **REGAL_LOG_INTERNAL**
  - **REGAL_LOG_HTTP**
  - **REGAL_LOG_API**       --- Application + Driver OpenGL logging
  - **REGAL_LOG_NONE**      --- enable or disable all logging
  
  Environment variable lookup is globally disabled by defining **REGAL_NO_GETENV**
  at compile-time.

  Runtime configuration via **GL_REGAL_log** extension: (**glEnable/glDisable/glIsEnabled**)

  - **GL_LOG_ERROR_REGAL**
  - **GL_LOG_WARNING_REGAL**
  - **GL_LOG_INFO_REGAL**
  - **GL_LOG_APP_REGAL**
  - **GL_LOG_DRIVER_REGAL**
  - **GL_LOG_INTERNAL_REGAL**
  - **GL_LOG_HTTP_REGAL**

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

* Regal OpenGL extensions

  - **GL_REGAL_error_string** for GLU-style GLenum to error string conversion.
  - **GL_REGAL_extension_query** for GLEW-style extension checking.
  - **GL_REGAL_log** for Regal logging configuration.

Planned Features
----------------

* Debug label.
* Debug output.
* Web browser-based debugging tools.
* Display list emulation.

Limitations
-----------

* Incomplete implementation, so far.
* Limited GLSL language support.
* GL_QUADS only works in immediate mode or with DrawArrays for ES and core profiles.

