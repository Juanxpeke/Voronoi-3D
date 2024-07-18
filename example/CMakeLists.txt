function(add_CGAL_example FOLDER_NAME TARGET_NAME)
    add_executable(${TARGET_NAME} CGAL/${FOLDER_NAME}/${TARGET_NAME}.cpp)

	set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 20)
	set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER Examples/${FOLDER_NAME})

    target_link_libraries(${TARGET_NAME} CGAL::CGAL CGAL::CGAL_Core CGAL::Data)
endfunction(add_CGAL_example)

function(add_CGAL_Qt5_example TARGET_NAME)
    add_executable(${TARGET_NAME} CGAL/Qt5/${TARGET_NAME}.cpp)

	set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 20)
	set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER Examples/Qt5)

    target_link_libraries(${TARGET_NAME} PUBLIC CGAL::Data CGAL::CGAL_Basic_viewer)
endfunction(add_CGAL_Qt5_example)

add_CGAL_example(Basic PointsAndSegments)
add_CGAL_example(Basic VectorConvexHull2)

add_CGAL_example(LCC Voronoi3)

if(CGAL_Qt5_FOUND)
    add_CGAL_Qt5_example(DrawSurfaceMesh)
    add_CGAL_Qt5_example(DrawTriangulation3)
    add_CGAL_Qt5_example(DrawLCC)
else()
    message("-- CGAL Qt5 not found")
endif()