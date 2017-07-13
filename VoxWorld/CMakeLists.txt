cmake_minimum_required(VERSION 3.7)

#project(VoxWorld)
add_subdirectory(../PortableGraphicsToolkit "${CMAKE_BINARY_DIR}/PortableGraphicsToolkit/")


MESSAGE(STATUS "Configuring Project VoxWorld" )
set(VoxWorld_SourceFiles
	src/main.cpp
	src/game/VoxelTest.cpp
	src/game/world/Chunk.cpp
	src/game/world/World.cpp
	src/gui/GuiTestWindow.cpp
)
set (VoxWorld_HeaderFiles
	src/game/VoxelTest.h
	src/game/world/Chunk.h
	src/game/world/World.h
	src/gui/GuiTestWindow.h
)

set(VoxWorld_IncludeDirectories
	../PortableGraphicsToolkit/src/
	src/
)

add_executable(VoxWorld ${VoxWorld_SourceFiles} ${VoxWorld_HeaderFiles})
add_dependencies(VoxWorld PGT)
include_directories(${VoxWorld_IncludeDirectories})

#find_library(pgtengine_core_lib_path NAMES "PGTngine_combined" PATHS "${CMAKE_BINARY_DIR}/PGTngine_core/Debug/" NO_DEFAULT_PATH )


target_link_libraries(VoxWorld PGTngine_core)#${pgtengine_core_lib_path}

target_compile_definitions(VoxWorld PUBLIC 
_CRT_SECURE_NO_WARNINGS
GLEW_STATIC
NOT_USING_FT_GL_NAMESPACE
)

