#include <basis/basis.hpp>
#include <io/gmsio.hpp>

int main()
{
  qpp::atomic_basis<qpp::qbas_gauss,double> bas;
  
  std::ifstream f("1.bas");
  qpp::read_gms_basis(f,bas);
  f.close();
  
  for (auto const & s: bas.shells)
    s.write(std::cout);
  for (auto const & s: bas.shells)
    s.write_g98(std::cout);
}
