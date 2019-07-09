#include <io/ccd_molden.hpp>
#include <fstream>

using namespace qpp;

int main() {

  fmt::print("molden1 exec...\n");
  std::ifstream ifile("../examples/io/ref_data/molden/srf2_vib.mol");
  comp_chem_program_data_t<float> cc_o;
  read_ccd_from_molden(ifile, cc_o);

  fmt::print("Total vibs = {}\n", cc_o.m_vibs.size());
  fmt::print("Total atom names in init = {}\n", cc_o.m_init_anames.size());
  fmt::print("Total atom pos in init = {}\n", cc_o.m_init_apos.size());

}
