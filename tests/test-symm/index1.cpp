#include <symm/index.hpp>
#include <iostream>

int main()
{
  qpp::index I = qpp::index::D(5);
  qpp::index J = qpp::index::D(5).atom(4);

  std::cout << I << J << "\n";

  I.sub(2) = {3,4,5};

  std::cout << I << atom_index(16,I) << "\n";

  int DIM=0;

  for (qpp::iterator X(qpp::index::D(DIM).all(-1), qpp::index::D(DIM).all(1)); !X.end(); X++ )
    std::cout << X << "\n";
}

