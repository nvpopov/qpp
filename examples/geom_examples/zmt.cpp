#include <geom/zmt.hpp>
#include <io/geomio.hpp>

int main()
{
  qpp::zmatrix<double> z;
  qpp::geometry<0> g;
  /*
  z.add(qpp::zmt_record<double>("C"));
  z.add(qpp::zmt_record<double>("C", 0, 1.54));
  z.add(qpp::zmt_record<double>("H", 0, 1.00, 1, 109.47));
  z.add(qpp::zmt_record<double>("H", 1, 1.00, 0, 109.47, 2, 180));
  z.add(qpp::zmt_record<double>("H", 0, 1.00, 1, 109.47, 3,  60));
  z.add(qpp::zmt_record<double>("H", 1, 1.00, 0, 109.47, 4, -60));
  z.add(qpp::zmt_record<double>("H", 0, 1.00, 1, 109.47, 5, 180));
  z.add(qpp::zmt_record<double>("H", 1, 1.00, 0, 109.47, 6,  60));
  */
  z.add(qpp::zmt_record<double>("C1"));
  z.add(qpp::zmt_record<double>("O2", 0, 1.20 ));
  z.add(qpp::zmt_record<double>("H3", 0, 1.10, 1, 120.0 ));
  z.add(qpp::zmt_record<double>("C4", 0, 1.50, 1, 120.0, 2, 160.0));
  z.add(qpp::zmt_record<double>("H5", 3, 1.10, 0, 110.0, 1, 0.00));
  z.add(qpp::zmt_record<double>("H6", 3, 1.10, 0, 110.0, 1, 120.0));
  z.add(qpp::zmt_record<double>("H7", 3, 1.10, 0, 110.0, 1, -120.0));

  z.zmt2cart(g);
  write_xyz(std::cout,g);

  for (int i=3; i<g.size(); i++)
    std::cout << i << " " << qpp::get_dyhedral(g.coord(i), g.coord(z(i).at1), g.coord(z(i).at2), g.coord(z(i).at3)) << "\n";

}
