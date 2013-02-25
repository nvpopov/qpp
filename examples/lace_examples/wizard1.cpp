#include<lace/matrix.hpp>
#include<lace/wizard_instance.hpp>
#include<boost/format.hpp>

using namespace _lace_expressions;
using namespace _lace_storage;
using _lace_main::wizard;

int main()
{
  int N = 10;
  matrix_shape shp;
  for(  int mtp = rectang; mtp < n_matrix_type; mtp++ )
    {
      shp.mtype = matrix_type(mtp);
      shp.n = shp.m = N;
      shp.ku = 3;
      shp.kl = 2;
      shp.tag = matrix_shape::upper;
      
      matrix_expression<double> *A = & wizard<double>::M(matrix_type(mtp)).create(shp);
      
      wizard<double>::M(matrix_type(mtp)).fill( *A, 2e0);
      
      for (int i=0; i<N; i++)
	for (int j=0; j<N; j++)
	  {
	    double *p = wizard<double>::M(matrix_type(mtp)).ptr( *A, i,j);
	    if ( p != NULL ) 
	      *p = i + .1*j;
	  }
      
      wizard<double>::M(matrix_type(mtp)).scale( *A, -10e0);
      
      std::cout << mtype_spelling[mtp] << "\n";
      for (int i=0; i<N; i++)
	{
	  for (int j=0; j<N; j++)
	    {
	      double *p = wizard<double>::M(matrix_type(mtp)).ptr( *A, i,j);
	      if (p!=NULL)
		std::cout << *p << " ";
	      else
		std::cout << 0e0 << " ";
	    }
	  std::cout << "\n";
	}

      delete A;
    }

  matrix_expression<double> *A = & wizard<double>::M(rectang).create(matrix_shape(rectang,12,10));
  wizard<double>::M(rectang).fill(*A,1,sub(0,10,2),sub(0,10,2));
  wizard<double>::M(rectang).fill(*A,2,sub(1,10,2),sub(1,10,2));
  for (int i=0; i<12; i++)
    {
      for (int j=0; j<10; j++)
	{
	  double *p = wizard<double>::M(matrix_type(rectang)).ptr( *A, i,j);
	  if (p!=NULL)
	    std::cout << boost::format("%8.3f")%*p << " ";
	  else
	    std::cout << boost::format("%8.3f")%0e0 << " ";
	}
      std::cout << "\n";
    }

  matrix_expression<double> *B = & wizard<double>::M(symmetric).create(matrix_shape(symmetric,5,5));
  for (int i=0; i<5; i++)
    for (int j=0; j<5; j++)
      {
	double *p = wizard<double>::M(symmetric).ptr( *B, i,j);
	if (p!=NULL) *p = i-2*j;
      }
  for (int i=0; i<5; i++)
    {
      for (int j=0; j<5; j++)
	{
	  double *p = wizard<double>::M(matrix_type(symmetric)).ptr( *B, i,j);
	  if (p!=NULL)
	    std::cout << boost::format("%8.3f")%*p << " ";
	  else
	    std::cout << boost::format("%8.3f")%0e0 << " ";
      }
      std::cout << "\n";
    }

  wizard<double>::MM(rectang,symmetric).MpM(*A,sub(4,8),sub(0,4),*B,sub(0,4),sub(0,4),-1e0/23,0);
  //wizard<double>::M(rectang).fill(*A,0);
  //wizard<double>::M(rectang).fill(*A,2,sub(4,8),sub(0,4));

  std::cout << "\n";
  for (int i=0; i<12; i++)
    {
      for (int j=0; j<10; j++)
	{
	  double *p = wizard<double>::M(matrix_type(rectang)).ptr( *A, i,j);
	  if (p!=NULL)
	    std::cout << boost::format("%8.3f")%*p << " ";
	  else
	    std::cout << boost::format("%8.3f")%0e0 << " ";
	}
      std::cout << "\n";
    }
}

