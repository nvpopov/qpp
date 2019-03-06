include(ExternalProject)
add_subdirectory(${PROJECT_SOURCE_DIR}/deps/pybind11)

#fmtlib for fast c++ format routines
ExternalProject_Add(fmtlib

  SOURCE_DIR "${PROJECT_SOURCE_DIR}/deps/fmtlib"
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  #CMAKE_ARGS -DFMT_DOC:bool=off -DFMT_INSTALL:bool=off -DFMT_TEST:bool=off -DFMT_USE_CPP11:bool=on
)

if(NOT USE_SYSTEM_EIGEN3)
ExternalProject_Add(eigen3

  SOURCE_DIR "${PROJECT_SOURCE_DIR}/deps/eigen3"
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
)
endif()


if(BUILD_QC)
endif(BUILD_QC)
