add_executable(simple-hf simple-hf.cpp)
target_link_libraries(simple-hf qpp int-imp)
add_dependencies(simple-hf libint-m)
