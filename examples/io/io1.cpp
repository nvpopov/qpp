#include <io/geomio.hpp>

int main()
{
  qpp::geometry<double> g(0);

  g.add("F",0,0,0);
  g.add("C",1,0,0);
  g.add("H",0,2,0);

  std::ofstream out("io1.xyz");
  qpp::write_xyz(out,g);
  out.close();
}
