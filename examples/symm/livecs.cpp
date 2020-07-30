#include <iostream>
#include <geom/lace3d.hpp>

int main(){
  qpp::matrix<double> A(4,5);
  //qpp::vector3<double> a(1,2,3), b(1,0,1), c(2,0,0);

  A <<
    0, 2, 1, 1, 0,
    1, 4, 1, 3, 2,
    2, 6, 1, 2, 1,
    3, 8, 1.0001, 5, 4;

  std::cout << "matrix was\n" << A << "\nrank is "<< qpp::matrix_rank(A, .0000001)<< "\n";

  auto L = qpp::LI_vectors(A,.000001);

  std::vector<int> I,D;
  qpp::matrix<double> ns;

  qpp::nullspace(I,D,ns,A,.000001);

  std::cout << "indep\n";
  for (int i:I)
    std::cout << i << " ";
  std::cout << "\n";

  std::cout << "dep\n";
  for (int i:D)
    std::cout << i << " ";
  std::cout << "\n";
  
  
  std::cout << "nullspace\n" << ns << "\n";

  /*  for (int i=0; i<L.size(); i++)
    std::cout << L[i] << " ";
  std::cout << "\n";

  
  
  qpp::matrix<double> B(A.rows(), L.size());
  for (int i=0; i<L.size(); i++)
    B.col(i) = A.col(L[i]);

  Eigen::Matrix<double,4,1> d;

  d << 2,3,1,1;

  std::cout << qpp::linear_combination(B,d) << "\n";
  //std::cout << Eigen::Dynamic << "\n";
  */
}
