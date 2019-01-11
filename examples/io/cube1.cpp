#include <io/geomio.hpp>
#include <io/cube.hpp>

int main(){
  std::ifstream cube1("/home/nvpopov/delme/babri/c1.cube");

  qpp::periodic_cell<float> cell(3);
  qpp::geometry<float,decltype(cell)> g1(cell);

  qpp::cube_header_t<float> cube_header;
  std::vector<float> field;

  qpp::read_cube(cube1, g1, cube_header, field);
  std::cout << fmt::format("tot atoms = {}\n", cube_header.tot_atoms);

  std::cout<<"Atoms from cube file:\n";
  for (auto i = 0; i < g1.nat(); i++)
    std::cout << fmt::format("{} {} {} {}\n", g1.atom(i), g1.pos(i)[0], g1.pos(i)[1], g1.pos(i)[2]);

  float cube_val_0_0_0  = qpp::get_field_value_at(0,0,0, cube_header, field);
  float cube_val_0_0_6  = qpp::get_field_value_at(0,0,6, cube_header, field);
  float cube_val_0_0_11 = qpp::get_field_value_at(0,0,11, cube_header, field);
  std::cout<<fmt::format("field value at {} {} {} = {}\n", 0,0,0, cube_val_0_0_0);
  std::cout<<fmt::format("field value at {} {} {} = {}\n", 0,0,6, cube_val_0_0_6);
  std::cout<<fmt::format("field value at {} {} {} = {}\n", 0,0,11, cube_val_0_0_11);
}
