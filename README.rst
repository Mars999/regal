Regal
=====

Regal for OpenGL

https://github.com/p3/regal

From an application developer's perspective, Regal just looks like an OpenGL implementation.
You link with it instead of your platform's OpenGL library or framework, and that's really
all you have to do to use Regal.  The rest of your code can remain unchanged.

+---------------+----------------------------------------------------------------------+
|  **Warning**  |  Regal is pre-alpha software, it is provided here to look at         |
|               |  and to play with the examples.  Don't use it in your projects yet.  |
|               |  You have been warned.                                               |
+---------------+----------------------------------------------------------------------+

Why use Regal? (Once it's ready, I mean.)

  * It is portable.
      A single, consistent API that runs on all major platforms: Windows, Linux, Mac, iOS, and Android

  * It is compatible.
      Feel free to use immediate mode, fixed function, GL_QUADS.  Old code still works even on ES and core profiles.

  * It is open source.
      There is nothing behind the curtain.  You can see what Regal is doing and change it if you need to.

  * It is modern.
      You can use Direct State Access and Vertex Array Object unconditionally with Regal because it is supported on all platforms.
      Other similar extensions like debug label and debug output are planned.

  * It is efficient.
      If it cannot be implemented efficiently in Regal, it is not supported universally.  No tessellation
      support without tessellation hardware, for example.

  * It makes development easier.
      Set a breakpoint on a GL entry point.  Step into the code.  Look at state.  Register an error callback.
      Regal makes all this possible today.  In addition to debug label and debug output support going in soon,
      there will be support for trace dumps and state dumps to quickly see what your app is doing.



