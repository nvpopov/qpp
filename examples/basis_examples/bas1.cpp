#include <basis/basis.hpp>
#include <iostream>

int main()
{
  using namespace qpp;
  for (int l=0; l<4; l++)
    for (int i=0; i<nanglf[l]; i++)
      std::cout << manglf[l][i][0] << " " << manglf[l][i][1] << " " << manglf[l][i][2] << " " << anglf_label[l][i] << "\n"; 

  gencon_basis_data<double> bas;
}
