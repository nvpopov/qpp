#include <pyqpp/pyqpp.hpp>
#include <data/ptable.hpp>

void pyqpp_ptable_export(pybind11::module m){
  py::module ptablem = m.def_submodule("ptable");

  ptablem.def(
        "get_atom_symbol_by_number",
        &qpp::ptable::symbol_by_number);

  ptablem.def(
        "get_atom_name_by_number",
        &qpp::ptable::name_by_number);

  ptablem.def(
        "get_atom_number_by_name",
        &qpp::ptable::number_by_name);

  ptablem.def(
        "get_atom_number_by_symbol",
        &qpp::ptable::number_by_symbol);

  ptablem.def(
        "get_atom_mass_by_number",
        &qpp::ptable::mass_by_number);

  ptablem.def(
        "get_ionic_rad_by_number",
        &qpp::ptable::ionic_rad_by_number);

  ptablem.def(
        "get_cov_rad_by_number",
        &qpp::ptable::cov_rad_by_number);

  ptablem.def(
        "get_vdw_rad_by_number",
        &qpp::ptable::vdw_rad_by_number);

  ptablem.def(
        "get_nval_elec_by_number",
        &qpp::ptable::nval_elec_by_number);
}
