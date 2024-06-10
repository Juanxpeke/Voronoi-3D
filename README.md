# Voronoi 3D

Computational geometry project that produces 3D Voronoi regions from a CGAL generated 3D surface triangulation.

## Dependencies

In order to build the project, you need to install CGAL and make sure CMake can find the package configuration file of the library.

Besides CGAL, the projects uses CGAL Qt5, so make sure you have the Qt5 files installed too.

## Examples

There are some examples in the ```example``` folder showing some of the CGAL features. The following pages are related to those examples:

- DrawTriangulation3 (https://doc.cgal.org/latest/Triangulation_3/index.html)

## Building

Despite of the OS, make sure to run the commands in the system's terminal.

### Linux

In order to build the project, run the following commands in the repository root:

- ```mkdir build```
- ```cd build```
- ```cmake ../```
- ```cmake --build ./```

## Running

Despite of the OS, make sure to run the commands in the system's terminal.

### Linux

In order to run the project, run the following commands in the repository root:
 
- ```cd build/source```
- ```./Main```