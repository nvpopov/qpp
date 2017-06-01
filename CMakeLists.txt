cmake_minimum_required (VERSION 3.2)

project(qpp CXX)
set (QPP_VERSION_MAJOR 0)
set (QPP_VERSION_MINOR 1)
add_definitions(-std=c++11 -fPIC -DFMT_HEADER_ONLY)
#set(CMAKE_CXX_FLAGS "-pg -ggdb")
#set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 11)

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

#boost related stuff
option(QPP_USE_STATIC_BOOST "use static boost library for python bindings" OFF)

#Python related stuff
option(QPP_PYTHON_BINDINGS "build qpp python bindings" ON)

set(QPP_PYTHON_VERSION "2.7" CACHE STRING "Python version")

if(QPP_PYTHON_BINDINGS)
    message("-- Compilation of python bindings is enabled")
    message("-- Use Python ${QPP_PYTHON_VERSION} for bindings")
    if(QPP_USE_STATIC_BOOST)
        message("-- Using static boost python libs for linking")
        add_definitions(-DBOOST_PYTHON_STATIC_LIB)
    else()
        message("-- Use dynamic boost python libs for linking")
    endif()

    find_package(PythonLibs ${QPP_PYTHON_VERSION} REQUIRED)
    if(PYTHONLIBS_FOUND)
        include_directories(${PYTHON_INCLUDE_DIRS})
        if(NOT QPP_USE_STATIC_BOOST)
            set(QPP_PYTHON_VERSION_ ${QPP_PYTHON_VERSION})
            string(REPLACE "." "" QPP_PYTHON_VERSION_ ${QPP_PYTHON_VERSION})
            if(${QPP_PYTHON_VERSION_} GREATER 30)
                find_package(Boost COMPONENTS
                    python-py${QPP_PYTHON_VERSION_} REQUIRED)
            else()
                find_package(Boost COMPONENTS python REQUIRED)
            endif()
            include_directories(${Boost_INCLUDE_DIRS})
        endif()
    endif()

endif()

#eigen3
option(QPP_USE_SYSTEM_EIGEN3
    "use system avaiable eigen3 or download as deps" ON)
if(QPP_USE_SYSTEM_EIGEN3)
    find_package(Eigen3)
    if(Eigen3_FOUND)
        message("-- Use system Eigen3 from ${EIGEN3_INCLUDE_DIR}")
        include_directories(${EIGEN3_INCLUDE_DIR})
    endif()
else()
    message("-- Eigen3 will be downloaded as dependency")
    include_directories(${CMAKE_SOURCE_DIR}/deps/eigen3)
endif()
 
#Add all src and headers to qtcreator ide
file(GLOB_RECURSE ide_headers "modules/*/*.hpp")
file(GLOB_RECURSE ide_src "modules/*/*.cpp")
file(GLOB_RECURSE ide_exm "examples/*/*.cpp")
add_custom_target(ideheaders SOURCES ${ide_headers})
add_custom_target(idesrc SOURCES ${ide_src})
add_custom_target(ideexm SOURCES ${ide_exm})

#Global includes
include_directories(modules/)

option(QPP_USE_SPGLIB "use spglib")
if(QPP_USE_SPGLIB)
    message("-- spglib bindings is enabled")
    include_directories(${CMAKE_SOURCE_DIR}/deps/spglib/src)
    add_library(spglib-imp STATIC IMPORTED)
    set_target_properties(spglib-imp PROPERTIES IMPORTED_LOCATION
        "${PROJECT_BINARY_DIR}/deps/spglib-prefix/src/spglib-build/libsymspg.a")
endif()

#Only data fetching here
add_subdirectory(modules)
add_subdirectory(utils)

option(QPP_BUILD_EXAMPLES "build examples" ON)
if(QPP_BUILD_EXAMPLES)
    message("-- Building examples is enabled")
    add_subdirectory(examples)
else()
    message("-- Building examples is disabled")
endif()

#Build tests
option(QPP_BUILD_TESTS "build tests executable")
if(QPP_BUILD_TESTS)
    message("-- Testing are enabled")
    add_subdirectory(tests)
else()
    message("-- Tests are disabled")
endif()

#qc stuff
option(QPP_BUILD_QC "build qc stuff")
if(QPP_BUILD_QC)
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
endif(QPP_BUILD_QC)

#Documentation
option(QPP_BUILD_DOCS "build documentation")
if(QPP_BUILD_DOCS)
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


