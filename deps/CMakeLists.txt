include(ExternalProject)
if(QPP_USE_STATIC_BOOST)
##    set( boost_URL
#        "http://sourceforge.net/projects/boost/files/boost/1.63.0/boost_1_63_0.tar.bz2" )
#    set( boost_SHA1 "9f1dd4fa364a3e3156a77dc17aa562ef06404ff6" )
 #   set( boost_INSTALL ${CMAKE_SOURCE_DIR}/deps/boost )
#    set( boost_INCLUDE_DIR ${boost_INSTALL}/include )
#    set( boost_LIB_DIR ${boost_INSTALL}/lib )

#    ExternalProject_Add( boost
#            PREFIX boost
#            URL ${boost_URL}
#            URL_HASH SHA1=${boost_SHA1}
#            BUILD_IN_SOURCE 1
#            CONFIGURE_COMMAND
#            ./bootstrap.sh
#            --with-libraries=python
#            --with-python=python${QPP_PYTHON_VERSION}
#            --prefix=<INSTALL_DIR>
#            BUILD_COMMAND
#            ./b2 install link=static variant=release
#            threading=multi runtime-link=static
#            INSTALL_COMMAND ""
#            INSTALL_DIR ${boost_INSTALL} )
#
    set( Boost_LIBRARIES
            ${boost_LIB_DIR}/libboost_python.a )
    message( STATUS "Boost static libs: " ${Boost_LIBRARIES} )
endif()

#fmtlib for fast c++ format routines
ExternalProject_Add(fmtlib

  SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/fmtlib"
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  #CMAKE_ARGS -DFMT_DOC:bool=off -DFMT_INSTALL:bool=off -DFMT_TEST:bool=off -DFMT_USE_CPP11:bool=on
)

if(NOT QPP_USE_SYSTEM_EIGEN3)
ExternalProject_Add(eigen3

  SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/eigen3"
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
)
endif()


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

        SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/libint"
        BUILD_IN_SOURCE 1
        CONFIGURE_COMMAND "${CMAKE_SOURCE_DIR}/deps/libint/./configure"
        "--with-cxx=${CMAKE_CXX_COMPILER}"

        INSTALL_COMMAND ""
        UPDATE_COMMAND ""
        )



endif(QPP_BUILD_QC)
