cmake_minimum_required(VERSION 3.7)
project(PortableGraphicsToolkit)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(CMakeConfigMgr "${CMAKE_CURRENT_BINARY_DIR}/config" EXCLUDE_FROM_ALL)

#add_subdirectory(PortableGraphicsToolkit)
#add_subdirectory(DiagramTool)
add_subdirectory(VoxWorld)
#add_subdirectory(LogicGateSandbox)
