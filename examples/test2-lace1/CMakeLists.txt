project(test2-lace1)

add_executable(test2-lace1 main.cpp)
target_link_libraries(test2-lace1 mathf lace mkl_intel_lp64 mkl_core mkl_sequential pthread m)
