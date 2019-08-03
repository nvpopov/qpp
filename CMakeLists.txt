cmake_minimum_required (VERSION 3.2)

project(qpp CXX C)
set (QPP_VERSION_MAJOR 0)
set (QPP_VERSION_MINOR 1)

#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_ABSOLUTE_DESTINATION_FILES)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_definitions(-DFMT_HEADER_ONLY)
if(NOT MSVC)
  add_definitions(-fPIC)
  set(CMAKE_CXX_FLAGS " -std=c++17 -fno-omit-frame-pointer -fvisibility=hidden")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Og -fno-omit-frame-pointer -g3 -ggdb")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -ffast-math")
elseif(MSVC)
   add_definitions(-D_ENABLE_EXTENDED_ALIGNED_STORAGE -DHAVE_SNPRINTF)
   add_compile_options("/std:c++latest")
endif()

include(FindOpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# option declaration
option(PYTHON_BINDINGS "build qpp python bindings" ON)
option(PYTHON_EXPOSE_EXTENDED "build python wrappers not only for real=float" ON)
option(USE_SYSTEM_EIGEN3 "use system avaiable eigen3 or download as deps" OFF)
option(BUILD_EXAMPLES "build examples" ON)
option(BUILD_TESTS "build tests executable" ON)
option(BUILD_QC "build qc stuff")
option(BUILD_DOCS "build documentation")
option(BUILD_TOOLS  "build tools" OFF)
# end option declaration

#read options from file if it exists
if(EXISTS ${PROJECT_SOURCE_DIR}/qpp.config)
    file(STRINGS ${PROJECT_SOURCE_DIR}/qpp.config ConfigContents)
    foreach(NameAndValue ${ConfigContents})
      # Strip leading spaces
      string(REGEX REPLACE "^[ ]+" "" NameAndValue ${NameAndValue})
      # Find variable name
      string(REGEX MATCH "^[^=]+" Name ${NameAndValue})
      # Find the value
      string(REPLACE "${Name}=" "" Value ${NameAndValue})
      # Set the variable
      set(${Name} "${Value}")
    endforeach()
endif()

# example framework , use def_example(<example name> <example src>)
set(EX_PR "example_")
set(EX_SF  "")

function(def_example arg_name arg_src)
    add_executable(${EX_PR}${arg_name}${EX_SF} ${arg_src})
    target_link_libraries(${EX_PR}${arg_name}${EX_SF} qpp)
endfunction(def_example)

function(def_example_custom_lib arg_name arg_src arg_lib)
    add_executable(${EX_PR}${arg_name}${EX_SF} ${arg_src})
    target_link_libraries(${EX_PR}${arg_name}${EX_SF} qpp ${arg_lib})
endfunction(def_example_custom_lib)

# end example framework

#eigen3
if(USE_SYSTEM_EIGEN3)
    find_package(Eigen3)
    if(Eigen3_FOUND)
        message("-- Use system Eigen3 from ${EIGEN3_INCLUDE_DIR}")
        include_directories(${EIGEN3_INCLUDE_DIR})
    endif()
else()
    message("-- Internal Eigen3 will be used")
    include_directories(${PROJECT_SOURCE_DIR}/deps/eigen3)
    include_directories(${PROJECT_SOURCE_DIR}/deps/eigen3/Eigen)
endif()
#end eigen3

add_subdirectory(deps)
include_directories(${PROJECT_SOURCE_DIR}/deps/pybind11/include)
include_directories(${PROJECT_SOURCE_DIR}/deps/eigen3)
include_directories(${PROJECT_SOURCE_DIR}/deps/fmtlib/include)
include_directories(${PROJECT_SOURCE_DIR}/deps/fmtlib/CppNumericalSolvers)
include_directories(${PROJECT_SOURCE_DIR}/deps/fmtlib/KMeansRex/src)
#add_subdirectory(${CMAKE_SOURCE_DIR}/deps/fmtlib)

#Python related stuff
if(PYTHON_BINDINGS)
    message("-- Python bindings are enabled")
    if(PYTHON_EXPOSE_EXTENDED)
        message("-- Python interface for REAL=double")
        add_definitions(-DPYTHON_EXP_EXT)
    endif()
endif()
#end python stuff

#Add all src and headers to qtcreator ide
file(GLOB_RECURSE ide_headers "modules/*/*.hpp")
file(GLOB_RECURSE ide_headersc "modules/*.hpp")
file(GLOB_RECURSE ide_src "modules/*/*.cpp")
file(GLOB_RECURSE ide_exm "examples/*/*.cpp")
#file(GLOB_RECURSE ide_t1 "tests/*/*.*pp")
#file(GLOB_RECURSE ide_t2 "tests/*.*pp")
add_custom_target(ideheaders SOURCES ${ide_headers} ${ide_headersc}
    ${ide_src} ${ide_exm})
#end ideheaders

#Global includes
include_directories(modules/)

add_subdirectory(modules)

if(BUILD_EXAMPLES)
    message("-- Examples are enabled")
    add_subdirectory(examples)
else()
    message("-- Examples are disabled")
endif()

#Build tests
if(BUILD_TESTS)
    message("-- Testing is enabled")
    enable_testing()

    include_directories(tests/src)
    add_subdirectory(tests)
else()
    message("-- Tests are disabled")
endif()

#qc stuff
if(BUILD_QC)
    message("-- @ Building of quantum chemistry programs enabled")
    #add_library(int-imp STATIC IMPORTED)
    #set_target_properties(int-imp PROPERTIES IMPORTED_LOCATION
    #    "${PROJECT_SOURCE_DIR}/deps/libint/lib/.libs/libint2.a")
    #include_directories(${PROJECT_SOURCE_DIR}/deps/libint/include)
    #add_subdirectory(${PROJECT_SOURCE_DIR}/examples/qc)
    #find_package(OpenMP)
    #if(OPENMP_FOUND)
    #    add_definitions(${OpenMP_CXX_FLAGS})
    #endif(OPENMP_FOUND)
endif(BUILD_QC)

#Documentation
if(BUILD_DOCS)
    message("-- HTML Documentation enabled")
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


if(BUILD_TOOLS)
    message("-- building tools enabled")
endif(BUILD_TOOLS)

add_subdirectory(${PROJECT_SOURCE_DIR}/tools)
