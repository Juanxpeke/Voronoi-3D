cmake_minimum_required(VERSION 3.16.3)
project(Voronoi3D)

set(CMAKE_CXX_STANDARD 20)

find_package(CGAL REQUIRED COMPONENTS Core)

add_subdirectory(example)
