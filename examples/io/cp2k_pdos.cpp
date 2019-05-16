#include <iostream>
#include <io/cp2k_pdos.hpp>
#include <fstream>

using namespace qpp;

int main() {

  std::string file_name = "../examples/io/ref_data/cp2k/pdos_Ce-ALPHA_k2-1.pdos";
  std::ifstream ifile(file_name);
  pdos_data_t<float> data;

  read_cp2k_pdos(file_name, ifile, data);

}
