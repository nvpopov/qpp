project(lace)
include_directories(../)
add_library(lace blas-mkl.cpp lapack-mkl.cpp lapack-mkl.cpp)
