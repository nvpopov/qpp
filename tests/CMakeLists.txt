add_executable(run_tests
               run_tests.cpp
               test_lace3d.cpp
               test_ccd.cpp
	       test_symmetry.cpp
               test_compute.cpp
               test_geom.cpp)

target_link_libraries(run_tests qpp)

add_test(NAME run_tests
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/run_tests -o report.xml -r junit
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
