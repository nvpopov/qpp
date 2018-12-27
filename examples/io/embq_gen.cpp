#include <io/geomio.hpp>
#include <geom/xgeom.hpp>
#include <iostream>
#include <fstream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <geom/builders.hpp>

using namespace qpp;

int main() {

  xgeometry<double, periodic_cell<double> > g(3);
  std::ifstream uc_file("../examples/io/ref_data/uc/baf2.uc");
  read_xyzq(uc_file, g);

  fmt::print(std::cout, "Total number of atoms = {}\n", g.nat());
  fmt::print(std::cout, "g.DIM = {}\n", g.DIM);

  for (int i = 0; i < g.nat(); i++)
    fmt::print(std::cout, "{} {} {} {} {}\n",
               g.atom(i), g.pos(i)[0], g.pos(i)[1], g.pos(i)[2], g.xfield<double>(4,i));

  fmt::print(std::cout, "a = {}\n", g.cell.v[0]);
  fmt::print(std::cout, "b = {}\n", g.cell.v[1]);
  fmt::print(std::cout, "c = {}\n", g.cell.v[2]);

  shape_sphere<double> sp(26, vector3<double>(0, 0, 0));
  shape_sphere<double> sp_q(11, vector3<double>(0, 0, 0));
  qpp::shape<double> & sh = sp - sp_q;

  xgeometry<double, periodic_cell<double> > gd(0);
  xgeometry<double, periodic_cell<double> > gd_cls(0);
  xgeometry<double, periodic_cell<double> > gd_chg(0);

  qpp::fill(gd, g, sp, crowd_merge | fill_atoms);
  qpp::fill(gd_cls, g, sp_q, crowd_merge | fill_atoms);
  qpp::fill(gd_chg, g, sh, crowd_merge | fill_atoms);

  std::ofstream out_xyz("all_test1.xyz");
  std::ofstream out_cls_xyz("cls_test1.xyz");
  std::ofstream out_chg_xyz("chg_test1.xyz");

  write_xyz(out_xyz, gd);
  write_xyz(out_cls_xyz, gd_cls);
  write_xyz(out_chg_xyz, gd_chg);
}
