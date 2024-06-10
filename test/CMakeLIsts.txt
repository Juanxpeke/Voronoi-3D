add_executable(TestCGAL CGAL/test.cpp)

target_link_libraries(TestCGAL CGAL::CGAL CGAL::CGAL_Core)