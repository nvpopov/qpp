set(M_SRC
    data/errors.cpp
    data/data.cpp
    data/types.cpp
    data/ptable.cpp
    symm/index.cpp
    io/strfun.cpp)

add_library(qpp ${M_SRC})

set(QPP_DEPS)
if(NOT USE_SYSTEM_EIGEN3)
    list(APPEND QPP_DEPS eigen3)
endif()

add_dependencies(qpp ${QPP_DEPS})

if(NOT MSVC)
  set(QPP_LINK_LIB m)
endif()

target_link_libraries(qpp ${QPP_LINK_LIB})

#set(IOPY io/io.py.cpp io/geomio.py.cpp io/gmsio.py.cpp)

if(PYTHON_BINDINGS)
    pybind11_add_module(pyqpp MODULE NO_EXTRAS
        pyqpp/pyqpp.cpp
        pyqpp/pyqpp_opaque_types.cpp
        pyqpp/pyqpp_linalg.cpp
        pyqpp/pyqpp_math.cpp
        pyqpp/pyqpp_cell.cpp
        pyqpp/pyqpp_geom.cpp
        pyqpp/pyqpp_xgeom.cpp
        pyqpp/pyqpp_neighbours.cpp
        pyqpp/pyqpp_builders.cpp
        pyqpp/pyqpp_shape.cpp
        pyqpp/pyqpp_autosymm.cpp
        pyqpp/pyqpp_basis_ecp.cpp
        pyqpp/pyqpp_molecule.cpp
        pyqpp/pyqpp_ptable.cpp
        pyqpp/pyqpp_io.cpp
        pyqpp/pyqpp_gmsio.cpp
        pyqpp/pyqpp_ccd.cpp
        pyqpp/pyqpp_experimental.cpp
        data/errors.cpp
        data/data.cpp
        data/types.cpp
        data/ptable.cpp
        symm/index.cpp
        io/strfun.cpp
        )
    set_target_properties(pyqpp PROPERTIES COMPILE_FLAGS "-DPY_EXPORT")
    set_target_properties(pyqpp PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
    set_target_properties(pyqpp PROPERTIES PREFIX "")
endif()
