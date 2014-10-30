#include <geom/zmt.hpp>

int main()
{
  lace::vector3d<double>
    r1(2.345,-1.3,5.37),
    r2(2.3975,-4.379,-3.0347),
    r3(1,1,1);
  double b1=5, b2=6.5, b3=6.87;

  std::vector<lace::vector3d<double> > pp = qpp::triangul3b(r1,b1,r2,b2,r3,b3);

  for (int i=0; i<pp.size(); i++)
    {
      std::cout << "i= " << i << " r= " << pp[i] <<  "\n";
      std::cout << "b1= " << b1 << " " << norm(r1-pp[i]) << "\n";
      std::cout << "b2= " << b2 << " " << norm(r2-pp[i]) << "\n";
      std::cout << "b3= " << b3 << " " << norm(r3-pp[i]) << "\n";
    }
}
