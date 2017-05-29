include(ExternalProject)

#fmtlib for fast c++ format routines
ExternalProject_Add(fmtlib
    GIT_REPOSITORY    https://github.com/fmtlib/fmt.git
    GIT_TAG "master"
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/fmtlib"
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
    CMAKE_ARGS -DFMT_DOC:bool=off
    -DFMT_INSTALL:bool=off
    -DFMT_TEST:bool=off
    -DFMT_USE_CPP11:bool=on
    )

#eigen3 library for linear algebra
ExternalProject_Add(eigen3
    GIT_REPOSITORY    https://github.com/RLovelett/eigen.git
    GIT_TAG "master"
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/eigen3"
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
    CMAKE_ARGS ""
    )

#spglib for crystal symmetry handling
if(QPP_USE_SPGLIB)
    ExternalProject_Add(spglib
        GIT_REPOSITORY    https://github.com/atztogo/spglib.git
        GIT_TAG "master"
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/spglib"
        INSTALL_COMMAND ""
        UPDATE_COMMAND ""
        CMAKE_ARGS ""
        )

endif(QPP_USE_SPGLIB)

if(QPP_BUILD_QC)
    #libint
    #TODO Add cxx optimization
    ExternalProject_Add(libint-m
        # DOWNLOAD_COMMAND wget "https://www.dropbox.com/s/sp6kyb7p2u0304b/libint.tgz?dl=0"
        #  DOWNLOAD_NAME libint.tgz
        #  DOWNLOAD_DIR "${CMAKE_SOURCE_DIR}/deps/"
        URL "https://www.dropbox.com/s/sp6kyb7p2u0304b/libint.tgz"
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/libint"
        CONFIGURE_COMMAND "${CMAKE_SOURCE_DIR}/deps/libint/./configure"
        "--with-cxx=${CMAKE_CXX_COMPILER}"
        BUILD_IN_SOURCE 1
        INSTALL_COMMAND ""
        UPDATE_COMMAND ""
        CMAKE_ARGS ""
        )

    ExternalProject_Add_Step(
        libint-m copyboost
        COMMAND tar -xzf ${CMAKE_SOURCE_DIR}/deps/libint/external/boost.tar.gz
        -C ${CMAKE_SOURCE_DIR}/deps/libint/include/libint2/
        DEPENDEES build
        )

endif(QPP_BUILD_QC)
