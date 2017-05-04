include(ExternalProject)

ExternalProject_Add(fmtlib
  GIT_REPOSITORY    https://github.com/fmtlib/fmt.git
  GIT_TAG "master"
  SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/fmtlib"
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
  CMAKE_ARGS -DFMT_DOC:bool=off -DFMT_INSTALL:bool=off -DFMT_TEST:bool=off -DFMT_USE_CPP11:bool=on
)

ExternalProject_Add(eigen3
  GIT_REPOSITORY    https://github.com/RLovelett/eigen.git
  GIT_TAG "master"
  SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/eigen3"
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
  CMAKE_ARGS ""
)

if(QPP_USE_SPGLIB)
    ExternalProject_Add(spglib
      GIT_REPOSITORY    https://github.com/atztogo/spglib.git
      GIT_TAG "master"
      SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/spglib"
      INSTALL_COMMAND true
      CMAKE_ARGS true
    )
endif(QPP_USE_SPGLIB)

