set(M_IO_SRC  io/strfun.cpp)
set(M_DATA_SRC data/types.cpp data/errors.cpp data/data.cpp)
set(M_SYMM_SRC symm/index.cpp)
set(M_SRC ${M_IO_SRC} ${M_DATA_SRC} ${M_SYMM_SRC})
add_library(qpp ${M_SRC})

set(QPP_DEPS fmtlib spglib-imp)
if(NOT USE_SYSTEM_EIGEN3)
    list(APPEND QPP_DEPS eigen3)
endif()

add_dependencies(qpp ${QPP_DEPS})

set(QPP_LINK_LIB m)

if(USE_SPGLIB)
    list(APPEND QPP_LINK_LIB spglib-imp)
endif(USE_SPGLIB)
target_link_libraries(qpp ${QPP_LINK_LIB} )

#set(IOPY io/io.py.cpp io/geomio.py.cpp io/gmsio.py.cpp)

if(PYTHON_BINDINGS)
    pybind11_add_module(pyqpp SHARED NO_EXTRAS
        pyqpp/pyqpp.cpp
        pyqpp/pyqpp_linalg.cpp
        pyqpp/pyqpp_cell.cpp
        pyqpp/pyqpp_geom.cpp
        pyqpp/pyqpp_xgeom.cpp
        pyqpp/pyqpp_neighbours.cpp
        pyqpp/pyqpp_builders.cpp
        data/errors.cpp
        data/data.cpp
        data/types.cpp
        symm/index.cpp
        io/strfun.cpp
        )
    set_target_properties(pyqpp PROPERTIES COMPILE_FLAGS "-DPY_EXPORT")
    set_target_properties(pyqpp PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
    set_target_properties(pyqpp PROPERTIES PREFIX "")
    add_dependencies(pyqpp spglib-imp)
   #add_library(qpp_cpp SHARED
  #  python/qppython.cpp data/errors.cpp data/types.cpp data/data.cpp
   # io/strfun.cpp symm/index.cpp python/qppcpp1.cpp python/qppcpp2.cpp
   # python/qppcpp3.cpp python/qppcpp4.cpp python/qppcpp5.cpp
  #  python/qppcpp6.cpp python/qppcpp7.cpp python/qppcpp8.cpp
   # python/qppcpp9.cpp python/qppcpp10.cpp ${IOPY})
#   target_link_libraries(qpp_cpp boost_python  spglib-imp)
   #   target_compile_options(qpp_cpp "-DPY_EXPORT")
 #
   #set_target_properties(qpp_cpp PROPERTIES COMPILE_FLAGS "-DPY_EXPORT")

 #   target_link_libraries(qpp_cpp
  #      ${Boost_LIBRARIES}
 #       ${PYTHON_LIBRARIES}
  #  )
  #
  #  set_target_properties(qpp_cpp PROPERTIES PREFIX "")
endif()
