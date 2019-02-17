#include <io/molcas.hpp>
#include <iostream>
#include <vector>

using namespace qpp;

int main () {

  std::ifstream mgrid("/home/nvpopov/work/inp.grid");

  periodic_cell<float> cell(3);
  geometry<float,decltype(cell)> g1(cell);

  std::vector<scalar_volume_t<float> > volumes;

  load_grid_ascii(mgrid, g1, volumes);

}
