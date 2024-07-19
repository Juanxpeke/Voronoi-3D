function(add_example TARGET_NAME)
    add_executable(${TARGET_NAME} ${TARGET_NAME}.cpp)

	set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 20)
	set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER Examples)

    target_include_directories(${TARGET_NAME} PRIVATE ${VORONOI_3D_INCLUDE_DIRECTORY})
    target_link_libraries(${TARGET_NAME} CGAL::CGAL CGAL::CGAL_Core CGAL::Data)
endfunction(add_example)

function(add_CGAL_example FOLDER_NAME TARGET_NAME)
    add_executable(${TARGET_NAME} CGAL/${FOLDER_NAME}/${TARGET_NAME}.cpp)

	set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 20)
	set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER Examples/CGAL/${FOLDER_NAME})

    target_link_libraries(${TARGET_NAME} CGAL::CGAL CGAL::CGAL_Core CGAL::Data)
endfunction(add_CGAL_example)

# Examples

add_example(BasicOFF)
add_example(BasicDelaunayVoronoi)
add_example(BasicDelaunayToOFF)
add_example(BasicVoronoiToOFF)
add_example(Complex)

# CGAL Examples

add_CGAL_example(Basic PointsAndSegments)
add_CGAL_example(Basic VectorConvexHull2)

add_CGAL_example(LCC Voronoi3)