include(ExternalProject)

add_subdirectory(${PROJECT_SOURCE_DIR}/deps/pybind11)
add_subdirectory(${PROJECT_SOURCE_DIR}/deps/fmtlib EXCLUDE_FROM_ALL)
add_subdirectory(${PROJECT_SOURCE_DIR}/deps/pugixml)

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
