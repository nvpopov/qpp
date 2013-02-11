cmake_minimum_required (VERSION 2.6)

project(qpp)
set (qpp_VERSION_MAJOR 0)
set (qpp_VERSION_MINOR 1)

#Detect system bitness
set(bitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(bitness 64)  
endif()

set(BLAS_INCLUDE "-" CACHE STRING "Blas include dir")
set(BLAS_LIB "-" CACHE STRING "Blas library dir")
set(LAPACK_INCLUDE "-" CACHE STRING "Lapack include dir")
set(LAPACK_LIB "-" CACHE STRING "Lapack lib dir")

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()
 
include_directories(${LAPACK_INCLUDE})
include_directories(${BLAS_INCLUDE})
include_directories(modules/)

#Create system-depend build directories
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_NAME}${bitness}/bin)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_NAME}${bitness}/lib)

#Set output directories
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_NAME}${bitness}/bin)
set( LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_NAME}${bitness}/lib)

add_subdirectory(modules)

option(QPP_BUILD_TOOLS "Build third-part tools")
if (QPP_BUILD_TOOLS)
	add_subdirectory(tools)
endif(QPP_BUILD_TOOLS)

option(QPP_BUILD_SAMPLES "Build or not to build samples")
if (QPP_BUILD_TOOLS)
	add_subdirectory(examples)
endif(QPP_BUILD_TOOLS)
