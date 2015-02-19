cmake_minimum_required (VERSION 2.6)

project(qpp CXX)
set (qpp_VERSION_MAJOR 0)
set (qpp_VERSION_MINOR 1)
include(CheckCXXCompilerFlag)

set(CMAKE_CXX_FLAGS "-pg")
set(CMAKE_BUILD_TYPE "Debug")

set(bitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(bitness 64)  
endif()

set(BLAS_INCLUDE "-" CACHE STRING "Blas include dir")
set(BLAS_LIB "-" CACHE STRING "Blas library dir")
set(LAPACK_INCLUDE "-" CACHE STRING "Lapack include dir")
set(LAPACK_LIB "-" CACHE STRING "Lapack lib dir")
set(LA_TYPE "MKL" CACHE STRING "Type of linear algebra library, (MKL,ACML)")

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

if (DEFINED QPP_MOLCAD)
     message("Configuring molcad...")
     add_subdirectory(tools/molcad)
else()
     message("Configuring molcad not enabled..")
endif()

if (DEFINED QPP_NVP_TOOLS)
     message("Configuring additional nvpopov tools...")
     add_subdirectory(tools/mparser)
else()
     message("Configuring additional nvpopov tools not enabled..")
endif()



if (DEFINED QPP_C11)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
    message("Forcing c++11...")
endif()

add_subdirectory(examples)
add_subdirectory(utils)

option(QPP_BUILD_TESTS "build tests executable")
if (QPP_BUILD_TESTS)
        add_subdirectory(tests)
endif(QPP_BUILD_TESTS)
