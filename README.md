# Voronoi 3D

Computational geometry project that produces 3D Voronoi regions from a CGAL generated 3D surface triangulation.

## Dependencies

In order to build the project, you need to install CGAL in your machine.

Besides CGAL, the projects uses CGAL Qt5 for some examples, so make sure you have the Qt5 files installed too if you want to execute these examples.

## Examples

There are some examples in the ```example``` folder showing some of the CGAL features. The following pages are related to those examples:

- PointsAndSegments (https://doc.cgal.org/latest/Manual/tutorial_hello_world.html)
- VectorConvexHull2 (https://doc.cgal.org/latest/Manual/tutorial_hello_world.html)
- DrawTriangulation3 (https://doc.cgal.org/latest/Triangulation_3/index.html)

## Building

There is a Makefile used to execute CMake commands in an easier way, the following targets are supported:

- ```make```: Builds the project with default configurations
- ```make vcpkg```: Builds the project telling CMake to use the vcpkg modules to find packages
- ```make clean```: Delete all the build files