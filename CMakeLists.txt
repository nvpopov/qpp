cmake_minimum_required (VERSION 2.7)

project(qpp CXX)
set (qpp_VERSION_MAJOR 0)
set (qpp_VERSION_MINOR 1)
add_definitions(-std=c++11)
#set(CMAKE_CXX_FLAGS "-pg -ggdb")
#set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 11)

#options


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

#Use system boost
find_package(Boost COMPONENTS python REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    add_definitions( "-DHAS_BOOST" )
endif()

#Use system python
find_package(PythonLibs 2.7 REQUIRED)
if(PYTHONLIBS_FOUND)
    include_directories(${PYTHON_INCLUDE_DIRS})
endif(PYTHONLIBS_FOUND)
 
#Add all src and headers to qtcreator ide
file(GLOB_RECURSE ide_headers "modules/*/*.hpp")
file(GLOB_RECURSE ide_src "modules/*/*.cpp")
file(GLOB_RECURSE ide_exm "examples/*/*.cpp")
add_custom_target(ideheaders SOURCES ${ide_headers})
add_custom_target(idesrc SOURCES ${ide_src})
add_custom_target(ideexm SOURCES ${ide_exm})

#Global includes
include_directories(modules/)
include_directories(${CMAKE_SOURCE_DIR}/deps/eigen3)
include_directories(${CMAKE_SOURCE_DIR}/deps/fmtlib)

add_library(fmtlib-imp STATIC IMPORTED)
set_target_properties(fmtlib-imp PROPERTIES IMPORTED_LOCATION
    "${PROJECT_BINARY_DIR}/deps/fmtlib-prefix/src/fmtlib-build/fmt/libfmt.a")

option(QPP_USE_SPGLIB "use spglib")
if(QPP_USE_SPGLIB)
    include_directories(${CMAKE_SOURCE_DIR}/deps/spglib/src)
    add_library(spglib-imp STATIC IMPORTED)
    set_target_properties(spglib-imp PROPERTIES IMPORTED_LOCATION
        "${PROJECT_BINARY_DIR}/deps/spglib-prefix/src/spglib-build/libsymspg.a")
endif()

#Only data fetching here
add_subdirectory(deps)
add_subdirectory(modules)
add_subdirectory(examples)
add_subdirectory(utils)

#Build tests
option(QPP_BUILD_TESTS "build tests executable")
if(QPP_BUILD_TESTS)
    add_subdirectory(tests)
endif(QPP_BUILD_TESTS)

#qc stuff
option(QPP_BUILD_QC "build qc stuff")
if(QPP_BUILD_QC)
    add_subdirectory(${CMAKE_SOURCE_DIR}/examples/qc)
    #find_package(OpenMP)
    #if(OPENMP_FOUND)
    #    add_definitions(${OpenMP_CXX_FLAGS})
    #endif(OPENMP_FOUND)
endif(QPP_BUILD_QC)

#Documentation
option(QPP_BUILD_DOCS "build documentation")
if(QPP_BUILD_DOCS)
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
          COMMAND ${CMAKE_COMMAND} -E echo "Done."
          WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif(DOXYGEN_FOUND)
endif(QPP_BUILD_DOCS)


