project(lace)
include_directories(../)
include_directories(${BLAS_INCLUDE})
add_library(lace blas-mkl.cpp lapack-mkl.cpp lapack-mkl.cpp)
