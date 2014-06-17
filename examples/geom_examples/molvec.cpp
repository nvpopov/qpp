#include <geom/geom_extras.hpp>
#include <io/geomio.hpp>
#include <lace/lace3d.hpp>

using namespace qpp;

int main()
{
  geometry<0,double> ch4;
  ch4.add("C",  .0,   .0,   .0);
  ch4.add("H",  .55,  .55,  .55);
  ch4.add("H",  .55, -.55, -.55);
  ch4.add("H", -.55,  .55, -.55);
  ch4.add("H", -.55, -.55,  .55);

  molecule_vector<0,double> v(ch4);

  for (int i=0; i<ch4.nat(); i++)
    v(i) = 0.1*ch4.position(i);

  std::ofstream f("ch4.xyz");
  lace::matrix3d<double> R = RotMtrx(lace::vector3d<double>(1,0,0), pi/30);

  for (int n = 0; n<30; n++)
    {
      write_xyz(f,ch4,v);

      v = R*v;
      for (int i=0; i<ch4.nat(); i++)
	ch4.coord(i) = R*ch4.coord(i);
    }
}

