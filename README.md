# SuperVoid
This is the repository for SuperVoid, and asteroids clone made from scratch with C++ and OpenGL. 

This is a side project, development started December 2018. Version 1.0 should be done around December 2019.

![](docs/Demo.gif)

# Features
* Keyboard, Mouse, and Gamepad Control
* Flexible Entity-Component system to allow manipulation of gameplay entities
* 3D Rendering with OpenGL 4.5
* Powerful framework utility classes to allow:
    * Multithreading
    * Resource Caching
    * Asynchronous File I/O
    * FNV1a String hashing for fast comparisions
    
# Todo
* Simple Physics/Collisions
* UI
* Text Rendering
* An actual asteroids clone
    

To build: 

*Note* This game requires Visual Studio 2019 to build. 

* Clone Repository
* Open SuperVoid.sln and smash F5

The GLFW binaries included in this repository were built for a windows 64bit system. To build the project on another system, replace the glfw3.lib file in Dependencies/GLFW with the apropriate binary file for your system.

See https://www.glfw.org/download.html for details and instructions on building GLFW

![This Project](http://www.poorlydrawnlines.com/wp-content/uploads/2017/07/an-idea.png)
