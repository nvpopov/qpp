#include <io/geomio.hpp>
namespace qpp{
int strnf(const STRING & s)
{
  std::basic_stringstream<CHAR,TRAITS> ss(s);
  STRING a;
  int nf = 0;
  for (nf=0; ss >> a; a!="") nf++;
  return nf;
}
}
