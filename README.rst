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

Planned Features
----------------

* Debug label.
* Debug output.

Limitations
-----------

* Incomplete implementation, so far.
* Limited GLSL language support.
* GL_QUADS only works in immediate mode or with DrawArrays for ES and core profiles.

