cmake_minimum_required(VERSION 3.7)
project(PortableGraphicsToolkit)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakePgtConfig" "${CMAKE_MODULE_PATH}")
include(pgt_config)

#add_subdirectory(PortableGraphicsToolkit)
#add_subdirectory(DiagramTool)
add_subdirectory(VoxWorld)
#add_subdirectory(LogicGateSandbox)
