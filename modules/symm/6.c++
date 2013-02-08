#include <lace/lace.hpp>
#include <symm/symm.hpp>
#include <symm/shenflis.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace lace;

template <class VALTYPE,matrix_type MT >
void prnmtr(matrix<VALTYPE,MT> &A)
{
  for(int i=0; i<A.size(0); i++)
    {
      for(int j=0; j<A.size(1); j++)
	std::cout << boost::format("%10.5f ") % A(i,j);
      std::cout << "\n";
    }
}

template <class VALTYPE,vector_type VT >
void prnvtr(vector<VALTYPE,VT> &A)
{
  for(int i=0; i<A.size(); i++)
    std::cout << boost::format("%10.5f ") % A(i);
  std::cout << "\n";
}

int main()
{
  qpp::shoenflis<double>::point_group G(qpp::shoenflis<double>::D_nh(4));
  //  std::cout <<"hello\n";
  G.build_all();

  matrix<double> n(G.size());
  n = 0e0;
  for (int i=0; i<n.size(0); i++)
    n(i,i) = 1e0;
  std::vector<int> dims;

  // -------------------------------------
  int M = n.size(0);
  int N = n.size(1);
  assert(N==G.size() && "only regular representaion subspaces!");

  for (int i=0; i<n.size(0); i++)
    {
      //std::cout << "regrep(" << i << ")\n";
      //prnmtr(G.regrep(i));
    }

  //  lace::globals::debug = true;

  std::vector<lace::matrix<double,lace::rectang>*> T(N);
  for (int i = 0; i<N; i++)
    {
      std::cout <<i<<"\n";
      T[i] = new lace::matrix<double,lace::rectang>(M);
      *T[i] = n*G.regrep(i)*n.T();
      prnmtr(*T[i]);
    }

  // Step 2. Form the matrix commuting the projected representation
  lace::matrix<double, lace::rectang> A(M),B(M);
  const int MXRND = 10000;
  for (int i=1; i<N; i++)
    for (int j=0; j<=i; j++)
      A(i,j) = A(j,i) = 1e0*(rand()%MXRND)/MXRND;

  //  A = 0e0;
  //  A(0,1)=A(1,0) = 1e0;

  B = A;
  for (int i=1; i<N; i++)
    B = B + (*T[i])*A*(*T[G.invert(i)]);      

  std::cout <<"B matrix\n";
  prnmtr(B);

  for (int i=0; i<N; i++)
    {
      std::cout << "Commutator " << i << "\n";
      lace::matrix<double,lace::rectang> CC(M);
      CC = B*(*T[i])-(*T[i])*B;
      prnmtr(CC);
    }

  // Step 3. Diagonalize it
  lace::matrix<double, lace::symmetric> S(M);
  for (int i=0; i<M; i++)
    for (int j=i; j<M; j++)
      S(i,j) = B(i,j);

  lace::vector<double> eig(M);
  lace::matrix<double,lace::rectang> vecs(M);
  
  lace::diagon(S,eig,vecs);
  std::cout << "Eigenvalues\n";
  prnvtr(eig);

  std::cout << "Eigenvectors\n";
  prnmtr(vecs);

  // Step 4. Count invariant subspaces
  const double invar_tol = 1e-6;
  // fixme! - check the constant, move its definition
  dims.clear();
  int d = 1;
  for (int i=1; i<M; i++)
    if ( (eig(i)-eig(i-1))*(eig(i)-eig(i-1))<invar_tol*invar_tol )
      d++;
    else
      {
	dims.push_back(d);
	d=1;
      }
  dims.push_back(d);

  // Step 5. Transform basis vectors n so that they are
  // basis vector for invariant subspaces just found
  
  lace::matrix<double,lace::rectang> nn(M,N);

  lace::globals::debug = true;
  n = vecs*n;

  std::cout << "Dimensions of invariant subspaces:\n";
  for (int i=0; i<dims.size(); i++)
    std::cout << dims[i] << " ";
  std::cout << "\n";

  std::cout << "New basis\n";

  prnmtr(n);

}
