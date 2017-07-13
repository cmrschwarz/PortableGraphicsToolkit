# PortableGraphicsToolkit
PGT provides Windows, GUIs, 2D, 3D and PseudoVoxel Renderers for Windows and GNU/Linux

## Disclaimer
This project is currently in early stage of development, please dont't expect anything to work :). 

But if that doesn't throw you off, contributions are highly appreciated and every request will be reviewed quickly.


## Plattforms
Currently supported is Windows, Linux support is coming soon
PGT uses a configuration headers which you can specify your system and build at compile time
(Endianness, Windowing Backend, Renderer, etc.)
CMake integration for this is coming soon.


## Installation
PGT uses [CMake](https://cmake.org/) as it's build system.
It can be build as a single static library, whith all its dependencies already statically linked in,
or with the bigger dependencies (currently FreeImage and SDL2) linked dynamically.
Support for full dynamic linkage is coming soon.
The available configurations can be seen in the CMakeConfigMgr/CMakeLists.txt file. 

Please note that the root CMakeLists.txt will most of the time be configured to build one of the examles(see below) instead of only the library.
But to fix this you only have to change the commented out build subdirectory.

## Examples
Three example projects are currently available, VoxWorld, LogicGateSandbox, and DiagramTool.
Each of these is in it's respectively named subdirectory and can be built by adjusting the root CMakeLists.txt.
Please note that these are rather small side projects that depend on the toolkit than real examples purely for that purpose.


## Dependencies
All dependencies are found in the folder /PortableGraphicsToolkit/deps
The subfolder LICENSES lists all their respective requirements.
- [SDL 2.0](https://www.libsdl.org/index.php)
- [GLFW](http://www.glfw.org/)
- [FreeImage](http://freeimage.sourceforge.net/)
- [freetype-gl](https://github.com/rougier/freetype-gl)
- [GLEW](http://glew.sourceforge.net/)


## License
This software is licensed under the [zlib/libpng license](https://choosealicense.com/licenses/zlib/).

