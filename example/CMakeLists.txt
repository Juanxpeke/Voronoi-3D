function(add_CGAL_example TARGET_NAME)
    add_executable(${TARGET_NAME} CGAL/${TARGET_NAME}.cpp)

    target_link_libraries(${TARGET_NAME} CGAL::CGAL CGAL::CGAL_Core)
endfunction(add_CGAL_example)

add_CGAL_example(PointsAndSegments)
add_CGAL_example(VectorConvexHull2)