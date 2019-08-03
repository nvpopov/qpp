include(ExternalProject)

add_subdirectory(${PROJECT_SOURCE_DIR}/deps/pybind11)
add_subdirectory(${PROJECT_SOURCE_DIR}/deps/fmtlib EXCLUDE_FROM_ALL)

if(NOT USE_SYSTEM_EIGEN3)
ExternalProject_Add(eigen3

  SOURCE_DIR "${PROJECT_SOURCE_DIR}/deps/eigen3"
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
)
endif()

add_library(KMeansRex ${PROJECT_SOURCE_DIR}/deps/KMeansRex/src/KMeansRexCore.cpp
                      ${PROJECT_SOURCE_DIR}/deps/KMeansRex/src/mersenneTwister2002.c)

if(BUILD_QC)
endif(BUILD_QC)
