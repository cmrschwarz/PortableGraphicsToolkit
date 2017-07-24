cmake_minimum_required(VERSION 3.7)
#project(VoxWorld)
add_subdirectory(../PortableGraphicsToolkit "${CMAKE_BINARY_DIR}/PortableGraphicsToolkit/")

MESSAGE(STATUS "Configuring Project DiagramTool" )
set(DiagramTool_SourceFiles
	src/dt/Diagram.cpp
	src/dt/lib.cpp
	src/dt/Table.cpp 
	src/dt/Window.cpp
	src/dt/XAxis.cpp 
	src/dt/YAxis.cpp 
)
set (DiagramTool_HeaderFiles
	src/dt/Content.h
    src/dt/Diagram.h
    src/dt/DTDEFS.h
	src/dt/Table.h
    src/dt/Window.h 
    src/dt/XAxis.h
    src/dt/YAxis.h
)

set(DiagramTool_IncludeDirectories
	../PortableGraphicsToolkit/src/
	src/
)

add_executable(DiagramTool ${DiagramTool_SourceFiles} ${DiagramTool_HeaderFiles})
include_directories(${DiagramTool_IncludeDirectories})
add_dependencies(DiagramTool pgt_slim)

target_link_libraries(DiagramTool "${PGT_BUILD_DIR}/pgt${PGT_LIB_EXT}")

target_compile_definitions(DiagramTool PUBLIC 
	_CRT_SECURE_NO_WARNINGS
)

