#include<lace/blas_mtr.hpp>
#include<iostream>
#include<boost/format.hpp>

using namespace _lace_storage;
using _lace_expressions::sub;

int main()
{
  /*
  {
    std::cout << "------------------ Rectangular matricies: ---------------------\n";
    int N=6, M=4;
    matrix_storage<double,rectang> A(matrix_shape(rectang,N,M)), 
      B(matrix_shape(rectang,N, M));
    
    A.setval(0e0);
    A(0,0)=A(1,2)=A(3,4)=A(4,1)=2e0;
    A(2,1)=A(4,3)=A(6,2)=-3e0;
    
    std::cout << "A == :\n";
    for (int i=0; i<N; i++)
      {
	for (int j=0; j<M; j++)
	  std::cout << A(i,j) << " ";
	std::cout << "\n"; 
      }
    
    B.setval(0e0);
    
    B(0,0) = B(1,1) = B(2,2) = B(3,3) = 10;
    
    std::cout << "B == :\n";
    for (int i=0; i<N; i++)
      {
	for (int j=0; j<M; j++)
	  std::cout << B(i,j) << " ";
	std::cout << "\n";
      }
    
    add_mtr(A, B, -1e0, 0);
    
    std::cout << "A + B == :\n";
    for (int i=0; i<N; i++)
      {
	for (int j=0; j<M; j++)
	  std::cout << A(i,j) << " ";
	std::cout << "\n"; 
      }
    
    
  }
  {
    std::cout << "------------------ Symmetric matricies: ---------------------\n";
    int N=6;
    matrix_storage<double,symmetric> A(matrix_shape(symmetric,N,N)), 
      B(matrix_shape(symmetric,N,N));
    
    A.setval(0e0);
    A(0,0)=A(1,2)=A(3,4)=A(4,1)=2e0;
    A(2,1)=A(4,3)=A(6,2)=-3e0;
    
    std::cout << "A == :\n";
    for (int i=0; i<N; i++)
      {
	for (int j=0; j<N; j++)
	  std::cout << A(i,j) << " ";
	std::cout << "\n"; 
      }
    
    B.setval(0e0);
    
    B(0,0) = B(1,1) = B(2,2) = B(3,3) = 10;
    
    std::cout << "B == :\n";
    for (int i=0; i<N; i++)
      {
	for (int j=0; j<N; j++)
	  std::cout << B(i,j) << " ";
	std::cout << "\n";
      }
    
    add_mtr(A, B, -1e0, 0);
    
    std::cout << "A + B == :\n";
    for (int i=0; i<N; i++)
      {
	for (int j=0; j<N; j++)
	  std::cout << A(i,j) << " ";
	std::cout << "\n"; 
      }
  }
  {
    std::cout << "---------- Rectang +  Symmetric matricies: ---------------------\n";
    int N=6;
    matrix_storage<double,rectang> A(matrix_shape(rectang,N,N)); 
    matrix_storage<double,symmetric> B(matrix_shape(symmetric,N,N));
    
    A.setval(0e0);
    A(0,0)=A(1,2)=A(3,4)=A(4,1)=2e0;
    A(2,1)=A(4,3)=A(6,2)=-3e0;
    
    std::cout << "A == :\n";
    for (int i=0; i<N; i++)
      {
	for (int j=0; j<N; j++)
	  std::cout << A(i,j) << " ";
	std::cout << "\n"; 
      }
    
    B.setval(0e0);
    
    B(0,0) = B(0,1) = B(0,2) = B(2,3) = 10;
    
    std::cout << "B == :\n";
    for (int i=0; i<N; i++)
      {
	for (int j=0; j<N; j++)
	  std::cout << B(i,j) << " ";
	std::cout << "\n";
      }
    
    add_mtr(A, B, -1e0, 0);
    
    std::cout << "A + B == :\n";
    for (int i=0; i<N; i++)
      {
	for (int j=0; j<N; j++)
	  std::cout << A(i,j) << " ";
	std::cout << "\n"; 
      }
  }
  {
    std::cout << "---------- Hermitian matricies: ---------------------\n";
    int N=6;
    matrix_storage<lace::dcomplex,hermitian> A(matrix_shape(hermitian,N,N)); 
    matrix_storage<lace::dcomplex,hermitian> B(matrix_shape(hermitian,N,N));
    
    A.setval(0e0);

    lace::dcomplex I(0,1e0);

    A(1,2)=A(3,4)=A(4,1)=2e0+3*I;
    A(2,1)=A(4,3)=A(6,2)=-3e0+I;
    
    std::cout << "A == :\n";
    for (int i=0; i<N; i++)
      {
	for (int j=0; j<N; j++)
	  std::cout << A(i,j) << " ";
	std::cout << "\n"; 
      }
    
    B.setval(0e0);
    
    B(0,0) = 99;
    B(0,1) = B(0,2) = B(2,3) = 10+.5*I;
    
    std::cout << "B == :\n";
    for (int i=0; i<N; i++)
      {
	for (int j=0; j<N; j++)
	  std::cout << B(i,j) << " ";
	std::cout << "\n";
      }
    
    add_mtr(A, B, 1e0+0*I, 0);
    
    std::cout << "A + B == :\n";
    for (int i=0; i<N; i++)
      {
	for (int j=0; j<N; j++)
	  std::cout << A(i,j) << " ";
	std::cout << "\n"; 
      }

    std::cout << "Scaling A*1.5:\n";
    scale_mtr(A,1.5e0+0*I);
    for (int i=0; i<N; i++)
      {
	for (int j=0; j<N; j++)
	  std::cout << A(i,j) << " ";
	std::cout << "\n"; 
      }


  }
  */
  std::cout << "------------------ Rectangular matricies: ---------------------\n";
  int N=6, M=8;
  matrix_storage<double,rectang> A(matrix_shape(rectang,N,M)), 
    B(matrix_shape(rectang,N, M));
  matrix_storage<double,symmetric> C(matrix_shape(symmetric,N,N));

  fill_mtr(A,0e0);
  fill_mtr(A,1e0,sub(0,10,2),sub(1,10,2));
  std::cout << "-------------- A ------------ \n";
  for (int i=0; i<N; i++)
    {
      for (int j=0; j<M; j++)
	std::cout << boost::format("%8.3f")%A(i,j) << " ";
      std::cout << "\n"; 
    }

  fill_mtr(C,0e0);
  fill_mtr(C,1.5e0,sub(0,10,2),sub(1,10,2));
  std::cout << "-------------- C ------------ \n";
  for (int i=0; i<N; i++)
    {
      for (int j=0; j<N; j++)
	std::cout << boost::format("%8.3f")%C(i,j) << " ";
      std::cout << "\n"; 
    }

  add_mtr(A,sub(1,N),sub(1,N),C,sub(1,N),sub(1,N),1e0,0);
  std::cout << "-------------- A + C ------------ \n";
  for (int i=0; i<N; i++)
    {
      for (int j=0; j<M; j++)
	std::cout << boost::format("%8.3f")%A(i,j) << " ";
      std::cout << "\n"; 
    }  
}
