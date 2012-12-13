This is Project 2, the warping still-life created by Craig Day and Lucas Mynsberge for CS 559.  

Included Files (Important files) - in P2-Warp.zip
==============
Debug/DevIL.dll
Debug/glew32.dll
Debug/ILU.dll
Debug/ILUT.dll
Debug/Warp.exe
Warp/ADSShader.cpp
Warp/ADSShader.h
Warp/back.frag
Warp/back.vert
Warp/bowl.cpp
Warp/bowl.h
Warp/fbo.cpp
Warp/fbo.h
Warp/fireplace.jpg
Warp/globals.cpp
Warp/globals.h
Warp/Home-Theater.jpg
Warp/left-curtain.jpg
Warp/left-over.jpg
Warp/lotr-scene.jpg
Warp/main.cpp
Warp/overlay.gif
Warp/per_vertex.frag
Warp/per_vertex.vert
Warp/phong.frag
Warp/phong.vert
Warp/popcorn.jpg
Warp/right-curtain.jpg
Warp/right-over.jpg
Warp/ringg.jpg
Warp/screen_overlay.jpg
Warp/shader.cpp
Warp/shader.h
Warp/stub.frag
Warp/stub.vert
Warp.sln
Warp.suo

Overview
--------

Special Features
----------------

Slightly Implemented Features
-----------------------------
- Curtains were to slide open/shut over the screen.  They were going to be made by using normal mapping on 
a purely red surface.  Time ran out, so only the textures were drawn in the proper location.

Debugging Methods
-----------------
- By pressing "w," wireframe mode can be examined.  This will display the warp-able picture.  In this sense,
one is allowed to see how the displacement of the vertices is working.
- 