#ifndef _QPP_SPECFUNC_H
#define _QPP_SPECFUNC_H

#include <mathf/constants.hpp>
#include <lace/lace3d.hpp>

namespace qpp{

  template<class REAL>
  int iround(REAL x)
  {
    int s = x<0 ? -1 : 1;
    x *= s;
    return s*int(x+5e-1);
  }

double logfact(int n);

double atanxy(double x, double y);


/*------------------------------------------------------------
				 Orthogonal polynomials
-------------------------------------------------------------*/

/*
 Returns Legendre polynomials of variable x from 0 to l-th order
 in the vector Pl.
				   n
			  1   d     2     n
   Pl(n) = ------ --- (x  - 1)
			n       n
		   2  n!  dx
*/
void Pl_legendre(double x, int l, std::vector<double> & Pl);

/*------------------------------------------------------
 Jacobi polynomials are defined here as


				 n                n
			 (-1)        2 -a    d       2  n+a
   P_n(x) = ------ (1 - x )    --- (1 - x  )
			 n                    n
			2  n!               dx

*/
void Pn_Jacobi(double x, double alpha, int n, std::vector<double> & Pn);


/* Laguerre polynomials defined as:

			 x   -a    n
			e   x     d     -x   n+a
  P_n(x) = --------  ---  (e    x    )
					   n
			  n!     dx
*/
void Pn_laguerre(double x, double alpha, int n, std::vector<double> & Pn);

/*-------------------------------------------------------
			  Boys function & error function
-------------------------------------------------------*/

double efrc(double x);
double erf(double x);

//------------------------------------------------------
//                Modified Bessel functions
//------------------------------------------------------
void Fn_boys(double x, int n, std::vector<double> & Fn);

double I0_bessel(double x, double predexp = 0e0);
void In_bessel(int n, double x, std::vector<double> & In, double predexp = 0e0);


/*-----------------------------------------------------------
				Spherical harmonics
-----------------------------------------------------------*/
/*  Returns array Qml, where Qml(l-m) is

			   ________
   m          / (l-m)!   m
  Q (x) = _  / -------  P  (x)
   l       \/   (l+m)!   l


  Pml - associated Legendre polynomials
  Different normalization is for avoiding overflow for large l*/
void Qml_legendre(int l, int m, double x, std::vector<double> & Qml);

/*-----------------------------------------------------------*/

double Ylm_spherical(int l, int m, double theta);
/* Spherical harmonics Y_lm without the exp(i*m*phi) multiplier
 fixme - implement Ylm returning array of values!
---------------------------------------------------------------------------------*/

double djmk_wigner(int J, int M, int K, double beta);


};

#endif
