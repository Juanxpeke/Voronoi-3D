cmake_minimum_required(VERSION 3.16.3)
project(Voronoi3D)

set(CMAKE_CXX_STANDARD 20)

# Define this repository root folder as the base path when calling CGAL::data_file_path
set(CGAL_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Core CGAL and Qt5 CGAL extension required
find_package(CGAL REQUIRED COMPONENTS Core)

set(VORONOI_3D_INCLUDE_DIRECTORY
  ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(example)
