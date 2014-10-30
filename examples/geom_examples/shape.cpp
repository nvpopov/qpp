#include <geom/shape.hpp>

typedef lace::vector3d<double> v3d;

int main()
{
  qpp::qpp_shape_parallel<double> p(v3d(2,0,0),v3d(1,1,0),v3d(0,0,1),"abc");
  
  p.write(std::cout);

  v3d r(0,.5,.5);
  std::cout << r << " is within= " << p.within(r) << "\n";

  std::cout << p.rmin() << p.rmax() << "\n";

  qpp::periodic_cell<3> fcc;
  fcc(0) = v3d(0,1,1);
  fcc(1) = v3d(1,0,1);
  fcc(2) = v3d(1,1,0);
  
  std::cout << p.fmin(fcc) << p.fmax(fcc) << "\n";
}
