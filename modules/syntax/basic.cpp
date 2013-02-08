#include "basic.hpp"

namespace qpp{

  int strnf(std::string s)
  {
    std::stringstream ss(s);
    std::string a;
    int nf = 0;
    for (nf=0; ss >> a; a!="") nf++;
    return nf;
  }

};
