cmake_minimum_required(VERSION 3.7)
#project(VoxWorld)
add_subdirectory(../PGTEngine_core "${CMAKE_BINARY_DIR}/PGTEngine_core/")

MESSAGE(STATUS "Configuring Project LogicGateSandbox" )
set(LGS_SOURCE_FILES
	src/circuit_logic_components/Circuit.cpp
	src/circuit_logic_components/Node.cpp
	src/Connection.cpp
	src/main.cpp
	src/Port.cpp src/Scene.cpp
)
set (LGS_HEADER_FILES
	src/Button.h
	src/circuit_logic_components/Circuit.h
	src/circuit_logic_components/NAND.h
	src/circuit_logic_components/Node.h
	src/circuit_logic_components/node_update_request.h
	src/circuit_logic_components/PowerSource.h
	src/Connection.h
	src/GateListViewItem.h
	src/LED.h
	src/NAND.h
	src/Node_legacy.h
	src/NOT.h
	src/Port.h
	src/Scene.h
)

set(LGS_INCLUDE_DIRS
	../PGTEngine_core/src/
	src/
)

add_executable(LogicGateSandbox ${LGS_SOURCE_FILES} ${LGS_HEADER_FILES})
add_dependencies(LogicGateSandbox PGTEngine_core)
include_directories(${LGS_INCLUDE_DIRS})
#find_library(pgtengine_core_lib_path NAMES "PGTEngine_combined" PATHS "${CMAKE_BINARY_DIR}/PGTEngine_core/Debug/" NO_DEFAULT_PATH )


target_link_libraries(LogicGateSandbox PGTEngine_core)#${pgtengine_core_lib_path}

target_compile_definitions(LogicGateSandbox PUBLIC 
_CRT_SECURE_NO_WARNINGS
)

