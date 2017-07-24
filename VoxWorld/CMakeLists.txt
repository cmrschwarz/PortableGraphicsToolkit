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
include_directories(${VoxWorld_IncludeDirectories})
add_dependencies(VoxWorld pgt_slim)
target_link_libraries(VoxWorld "${PGT_BUILD_DIR}/${PGT_LIB_PREFIX}pgt${PGT_LIB_EXT}")
