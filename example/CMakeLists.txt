function(add_CGAL_example TARGET_NAME)
    add_executable(${TARGET_NAME} CGAL/${TARGET_NAME}.cpp)

    target_link_libraries(${TARGET_NAME} CGAL::CGAL CGAL::CGAL_Core)
endfunction(add_CGAL_example)

function(add_CGAL_Qt5_example TARGET_NAME)
    add_executable(${TARGET_NAME} CGAL/Qt5/${TARGET_NAME}.cpp)

    target_link_libraries(${TARGET_NAME} PUBLIC CGAL::Data CGAL::CGAL_Basic_viewer)
endfunction(add_CGAL_Qt5_example)

add_CGAL_example(PointsAndSegments)
add_CGAL_example(VectorConvexHull2)

if(CGAL_Qt5_FOUND)
    add_CGAL_Qt5_example(DrawSurfaceMesh)
    add_CGAL_Qt5_example(DrawTriangulation3)
else()
    message("CGAL Qt5 not found")
endif()