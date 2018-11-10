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


#spglib for crystal symmetry handling
#    ExternalProject_Add(spglib
#        SOURCE_DIR "${PROJECT_SOURCE_DIR}/deps/spglib"
#        INSTALL_COMMAND ""
#        UPDATE_COMMAND ""
#        CMAKE_ARGS ""
#        )

if(BUILD_QC)
    #libint
    #TODO Add cxx optimization
    ExternalProject_Add(libint-m
        # DOWNLOAD_COMMAND wget "https://www.dropbox.com/s/sp6kyb7p2u0304b/libint.tgz?dl=0"
        #  DOWNLOAD_NAME libint.tgz
        #  DOWNLOAD_DIR "${CMAKE_SOURCE_DIR}/deps/"

        SOURCE_DIR "${PROJECT_SOURCE_DIR}/deps/libint"
        BUILD_IN_SOURCE 1
        CONFIGURE_COMMAND "${PROJECT_SOURCE_DIR}/deps/libint/./configure"
        "--with-cxx=${CMAKE_CXX_COMPILER}"

        INSTALL_COMMAND ""
        UPDATE_COMMAND ""
        )



endif(BUILD_QC)
