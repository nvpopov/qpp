cmake_minimum_required (VERSION 3.2)

project(qpp CXX)
set (QPP_VERSION_MAJOR 0)
set (QPP_VERSION_MINOR 1)
add_definitions(-O3 -std=c++11 -fPIC -DFMT_HEADER_ONLY)
set(CMAKE_CXX_FLAGS "-pg -ggdb")
#set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 11)

include(FindOpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
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



add_subdirectory(deps)
include_directories(${CMAKE_SOURCE_DIR}/deps/fmtlib)
#add_subdirectory(${CMAKE_SOURCE_DIR}/deps/fmtlib)



#Python related stuff
option(PYTHON_BINDINGS "build qpp python bindings" ON)

if(PYTHON_BINDINGS)
endif()

#eigen3
option(USE_SYSTEM_EIGEN3
	"use system avaiable eigen3 or download as deps" OFF)
if(USE_SYSTEM_EIGEN3)
    find_package(Eigen3)
    if(Eigen3_FOUND)
        message("-- Use system Eigen3 from ${EIGEN3_INCLUDE_DIR}")
        include_directories(${EIGEN3_INCLUDE_DIR})
    endif()
else()
    message("-- Internal Eigen3 will be used")
    include_directories(${CMAKE_SOURCE_DIR}/deps/eigen3)
endif()
 
#Add all src and headers to qtcreator ide
file(GLOB_RECURSE ide_headers "modules/*/*.hpp")
file(GLOB_RECURSE ide_headersc "modules/*.hpp")
file(GLOB_RECURSE ide_src "modules/*/*.cpp")
file(GLOB_RECURSE ide_exm "examples/*/*.cpp")
file(GLOB_RECURSE ide_t1 "tests/*/*.*pp")
file(GLOB_RECURSE ide_t2 "tests/*.*pp")
#add_custom_target(ideheaders SOURCES ${ide_headers} ${ide_headersc}
#    ${ide_src} ${ide_exm} ${ide_t1} ${ide_t2})


#Global includes
include_directories(modules/)

option(USE_SPGLIB "use spglib" ON)
if(USE_SPGLIB)
    message("-- spglib bindings is enabled")
    include_directories(${CMAKE_SOURCE_DIR}/deps/spglib/src)
    add_library(spglib-imp STATIC IMPORTED)
    set_target_properties(spglib-imp PROPERTIES IMPORTED_LOCATION
        "${PROJECT_BINARY_DIR}/deps/spglib-prefix/src/spglib-build/libsymspg.a")
endif()

#Only data fetching here
add_subdirectory(modules)
#add_subdirectory(utils)

option(BUILD_EXAMPLES "build examples" OFF)
if(BUILD_EXAMPLES)
    message("-- Building examples is enabled")
    add_subdirectory(examples)
else()
    message("-- Building examples is disabled")
endif()

#Build tests
option(BUILD_TESTS "build tests executable" OFF)
if(BUILD_TESTS)
    message("-- Testing are enabled")
    enable_testing()

    include_directories(tests/src)
    add_subdirectory(tests)
else()
    message("-- Tests are disabled")
endif()

#qc stuff
option(BUILD_QC "build qc stuff")
if(BUILD_QC)
    message("-- @ Building of quantum chemistry programs enabled")
    add_library(int-imp STATIC IMPORTED)
    set_target_properties(int-imp PROPERTIES IMPORTED_LOCATION
      "${CMAKE_SOURCE_DIR}/deps/libint/lib/.libs/libint2.a")
    include_directories(${CMAKE_SOURCE_DIR}/deps/libint/include)
    add_subdirectory(${CMAKE_SOURCE_DIR}/examples/qc)
    #find_package(OpenMP)
    #if(OPENMP_FOUND)
    #    add_definitions(${OpenMP_CXX_FLAGS})
    #endif(OPENMP_FOUND)
endif(BUILD_QC)

#Documentation
option(BUILD_DOCS "build documentation")
if(BUILD_DOCS)
    message("-- HTML Documentation is enabled")
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        set(DOXYGEN_INPUT docs/doxyfile_qpp)
        set(DOXYGEN_OUTPUT docs/render)
        add_custom_command(
          OUTPUT ${DOXYGEN_OUTPUT}
          COMMAND ${CMAKE_COMMAND}
          -E echo_append "Building API Documentation..."
          COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
          COMMAND ${CMAKE_COMMAND} -E echo "Done."
          WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
          DEPENDS ${DOXYGEN_INPUT})
        add_custom_target(apidoc ALL DEPENDS ${DOXYGEN_OUTPUT})
        add_custom_target(apidoc_forced
          COMMAND ${CMAKE_COMMAND}
          -E echo_append "Building API Documentation..."
          COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
          COMMAND ${CMAKE_COMMAND}
          -E echo "Done."
          WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif(DOXYGEN_FOUND)
else()
    message("-- HTML Documentation is disabled")
endif()

