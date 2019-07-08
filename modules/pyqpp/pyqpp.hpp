#ifndef PYQPP_H
#define PYQPP_H

#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
//#include <pybind11/stl.h>
#include <pybind11/iostream.h>
namespace py = pybind11;
#pragma pop_macro("slots")

void pyqpp_opaque_types_export (py::module m);
void pyqpp_linalg_export       (py::module m);
void pyqpp_math_export         (py::module m);
void pyqpp_cell_export         (py::module m);
void pyqpp_geom_export         (py::module m);
void pyqpp_xgeom_export        (py::module m);
void pyqpp_shape_export        (py::module m);
void pyqpp_neighbours_export   (py::module m);
void pyqpp_builders_export     (py::module m);
void pyqpp_autosymm_export     (py::module m);
void pyqpp_basis_ecp_export    (py::module m);
void pyqpp_molecule_export     (py::module m);
void pyqpp_io_export           (py::module m);
void pyqpp_gmsio_export        (py::module m);
void pyqpp_experimental_export (py::module m);
void pyqpp_ptable_export       (py::module m);
void pyqpp_ccd_export          (py::module m);

#endif
