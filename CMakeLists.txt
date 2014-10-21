cmake_minimum_required (VERSION 2.6)

project(qpp)
set (qpp_VERSION_MAJOR 0)
set (qpp_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "-std=\"c++11\" -pg")
set(CMAKE_BUILD_TYPE "Debug")
#Detect system bitness
set(bitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(bitness 64)  
endif()

set(BLAS_INCLUDE "-" CACHE STRING "Blas include dir")
set(BLAS_LIB "-" CACHE STRING "Blas library dir")
set(LAPACK_INCLUDE "-" CACHE STRING "Lapack include dir")
set(LAPACK_LIB "-" CACHE STRING "Lapack lib dir")
set(LA_TYPE "MKL" CACHE STRING "Type of linear algebra library, (MKL,ACML)")

#IF ((${LA_TYPE} EQUAL "MKL") or (${LA_TYPE} EQUAL "ACML"))
#
##ENDIF()

if (LA_TYPE EQUAL "MKL")
	set(BLAS_LIBS_COM
	-L${BLAS_LIB}
	-l mkl_core
	)
	include_directories(${BLAS_INCLUDE})
	message(STATUS "MKL!")
endif()

find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    add_definitions( "-DHAS_BOOST" )
endif()
 
 
include_directories(modules/)

add_subdirectory(modules)

option(QPP_BUILD_TOOLS "Build third-part tools")
if (QPP_BUILD_TOOLS)
	add_subdirectory(tools)
endif(QPP_BUILD_TOOLS)

#option(QPP_BUILD_SAMPLES "Build or not to build samples")
#if (QPP_BUILD_TOOLS)
add_subdirectory(examples)

option(QPP_BUILD_TESTS "build tests executable")
if (QPP_BUILD_TESTS)
        add_subdirectory(tests)
endif(QPP_BUILD_TESTS)
