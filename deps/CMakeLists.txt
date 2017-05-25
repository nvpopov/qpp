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
    #gmplib for libint
    ExternalProject_Add(gmp
      URL "https://gmplib.org/download/gmp/gmp-6.1.2.tar.xz"
      SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/gmplib"
      CONFIGURE_COMMAND "${CMAKE_SOURCE_DIR}/deps/gmplib/configure"
      --enable-static
      --enable-cxx
      --enable-silent-rules
      INSTALL_COMMAND ""
      UPDATE_COMMAND ""
      CMAKE_ARGS ""
    )

    set(GMP_LIB_DIR "${CMAKE_SOURCE_DIR}/build/deps/gmp-prefix/src/gmp-build/.libs")

    set(ENV{CXX} ${CMAKE_CXX_COMPILER})
    #libint
    ExternalProject_Add(libint
      GIT_REPOSITORY https://github.com/evaleev/libint.git
      CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/libint/autogen.sh
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/libint/./configure
            LDFLAGS="-L${GMP_LIB_DIR}"
      BINARY_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/libint"
      INSTALL_COMMAND ""
      UPDATE_COMMAND ""
      CMAKE_ARGS ""
    )
endif(QPP_BUILD_QC)
