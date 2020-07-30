add_executable(test_lace3d test_lace3d.cpp)
add_executable(test_ccd test_ccd.cpp)
add_executable(test_compute test_compute.cpp)
add_executable(test_geom test_geom.cpp)
target_link_libraries(test_ccd qpp)
target_link_libraries(test_compute qpp)
target_link_libraries(test_geom qpp)

add_test(NAME test_lace3d
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_lace3d -o report.xml -r junit
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_test(NAME test_ccd
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_ccd -o report.xml -r junit
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_test(NAME test_compute
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_compute -o report.xml -r junit
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_test(NAME test_geom
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_geom -o report.xml -r junit
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(test-symm)

#add_subdirectory(test-geom)

