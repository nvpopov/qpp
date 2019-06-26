#ifndef _QPP_SPECFUNC_H
#define _QPP_SPECFUNC_H

#include <consts.hpp>
#include <vector>

#ifdef PY_EXPORT
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#endif

namespace qpp {

  /**
   * @brief logfact
   * @param n
   * @return returns ln(n!)
   */
  double logfact(int n) {
    double f = 0e0;
    for (int k = 1; k<=n; k++)
      f += std::log(1e0*k);
    return f;
  }

  /**
   * @brief atanxy
   * @param x
   * @param y
   * @return returns the polar angle for the (x,y) direction
   */
  double atanxy(double x, double y) {

    const double eps=1e-8;
    double phi;

    if ( std::abs(x) <= eps ) {
        phi = pi / 2;
        if ( y < 0 )
          phi += pi;
      }
    else {
        phi = std::atan(y/x);
        if ( x  < 0 )
          phi += pi;
      }
    return phi;
  }

  // -------------------------------------------------------------
  //                 Orthogonal polynomials
  // -------------------------------------------------------------


  /**
   * @brief Pl_legendre
   * @tparam REAL
   * @param x
   * @param l
   * @param Pl
   Returns Legendre polynomials of variable x from 0 to l-th order
   in the vector Pl.
                     n
                1   d     2     n
     Pl(n) = ------ --- (x  - 1)
              n       n
             2  n!  dx
   *
   */
  template <class REAL>
  void Pl_legendre(double x, int l, std::vector<REAL> & Pl) {

    Pl.resize(l+1);
    Pl[0] = REAL(1);

    REAL pl_prev = REAL(1), pl = x;
    REAL pl_next;

    for (int k = 1; k<=l; k++)
      {
        Pl[k] = pl;

        pl_next = pl*x*(2*k + 1)/(k + 1) - pl_prev*k/(k+1);
        pl_prev = pl;
        pl = pl_next;
      }

  }


  /**
   * @brief Pn_Jacobi
   * @details
   * Jacobi polynomials are defined here as


                   n                n
               (-1)        2 -a    d       2  n+a
     P_n(x) = ------ (1 - x )    --- (1 - x  )
               n                    n
              2  n!               dx


   */
  template <class REAL>
  void Pn_Jacobi(REAL x, REAL alpha, int n, std::vector<REAL> & Pn) {
    Pn.resize(n+1);

    REAL p, p_1, p_2;
    Pn[0] = p_2 = REAL(1);

    if (n>=1)
      Pn[1] =  p_1 = (alpha + REAL(1))*(REAL(1) - 2*x);

    for (int k = 2; k <= n; k++)
      {
        p = (alpha + k -.5)*(1 - 2*x)*p_1 - .5*(alpha + k - 1)*p_2;
        p *= 2*(alpha+k)/((2*alpha+k)*k);

        Pn[k] = p;

        p_2 = p_1;
        p_1 = p;
      }
  }

  // ------------------------------------------------------
  /*
  void Pn_laguerre(double x, double alpha, int n, lace::vector<double> & Pn)
  // Laguerre polynomials defined as:

  //
  //             x   -a    n
  //            e   x     d     -x   n+a
  //  P_n(x) = --------  ---  (e    x    )
  //                       n
  //              n!     dx
  //
  {
    double p, p_1, p_2;

    Pn(0) = p_2 = 1e0;

    if (n>=1)
      Pn(1) =  p_1 = alpha + 1e0 - x;

    for (int k = 2; k <= n; k++)
      {
  p = -( (x-alpha-2*k+1)*p_1 + (alpha+k-1)*p_2 )/k;

  Pn(k) = p;

  p_2 = p_1;
  p_1 = p;
      }
  }

  // -------------------------------------------------------
  //              Boys function & error function
  // -------------------------------------------------------

  double efrc(double x)
  {
    double z = (x>0) ? x : -x;
    double t = 1e0/(1 + .5e0*z);

    double erfcc = t*std::exp( -z*z - 1.26551223 + t*( 1.00002368 + t*( .37409196 +
                    t*( .09678418 + t*( -.18628806 + t*( .27886807 + t*( -1.13520398 +
              t*( 1.48851587 + t*( -.82215223 + t*.17087277)))))))));

    if (x<0)
      return 2e0 - erfcc;
    else
      return erfcc;
  }

  //------------------------------------------------------

  double erf(double x)
  {
    return 1e0 - erfc(x);
  }

  //------------------------------------------------------

  void Fn_boys(double x, int n, lace::vector<double> & Fn)
  {
    double sx = std::sqrt(x);
    double ex = std::exp(-x);

    Fn(0) = erf(sx)/sx;
    double hspi = std::sqrt(pi)/2;
    for (int k=0; k<n; k++)
      Fn(k+1) = ( (2*k+1)*Fn(k) - ex/hspi )/(2*x);
  }

  //------------------------------------------------------
  //                Modified Bessel functions
  //------------------------------------------------------

  double I0_bessel(double x, double predexp = 0e0)
  {
    const double
      p1 = 1.0e0,
      p2 = 3.5156229e0,
      p3 = 3.0899424e0,
      p4 = 1.2067492e0,
      p5 = 0.2659732e0,
      p6 = 0.360768e-1,
      p7 = 0.45813e-2,
      q1 = 0.39894228e0,
      q2 = 0.1328592e-1,
      q3 = 0.225319e-2,
      q4 = -0.157565e-2,
      q5 = 0.916281e-2,
      q6 = -0.2057706e-1,
      q7 = 0.2635537e-1,
      q8 = -0.1647633e-1,
      q9 = 0.392377e-2;

    double absx = std::abs(x);
    if ( absx < 3.75e0 )
      {
  double xx = x/3.75e0;
  xx *= xx;

  return ( p1 + xx*(p2 + xx*(p3 + xx*(p4 + xx*(p5 + xx*(p6 + xx*p7))))) )*std::exp(predexp);
      }
    else
      {
  double xx = 3.75/absx;
  return (std::exp(predexp+absx)/std::sqrt(absx))*(q1 + xx*(q2 + xx*(q3 + xx*(q4 +
        xx*(q5 + xx*(q6 + xx*(q7 + xx*(q8 + xx*q9))))))));
      }
  }

  void In_bessel(int n, double x, lace::vector<double> & In, double predexp = 0e0)
  {
    double I0 = I0_bessel(x, predexp);
    double tx = 2e0/x;

    double big = 1e10, small = 1e-10;
    double bi = 1e0, bip=0e0, bim;

    double accrcy = 40e0;
    int nstart = 2*( ( n + (int)std::sqrt(accrcy*n) )/2 );

    for ( int j = nstart; j>0; j-- )
      {
  bim = bip + j * tx * bi;
  bip = bi;
  bi = bim;

  if (j<=n+1) In(j-1) = bi;

  if ( bi > big )
    {
      bi  *= small;
      bip *= small;

      for (int i=j-1; i<=n; i++) In(i) *= small;
    }
      }

    for (int i=0; i<=n; i++) In(i) *= I0/bi;
  }
  */
  // -------------------------------------------------------------
  //                 Spherical harmonics
  // -------------------------------------------------------------

  /**
   * @brief Qml_legendre
   * @details
    Returns array Qml, where Qml(l-m) is
                 ________
     m          / (l-m)!   m
    Q (x) = _  / -------  P  (x)
     l       \/   (l+m)!   l

    Pml - associated Legendre polynomials
    Different normalization is for avoiding overflow for large l
   */
  template <class REAL>
  void Qml_legendre(int l, int m, REAL x, std::vector<REAL> & Qml) {
    int n = l - m;
    Qml.resize(n+1);

    REAL Cmm = REAL(1);
    REAL sin2 = REAL(1) - x*x;
    for (int i=1; i<=m; i++)
      Cmm *= sin2*(1 - .5e0/i);
    Cmm = std::sqrt(Cmm);

    if ( int(m/2)*2 != m ) Cmm = -Cmm;
    
    Qml[0]=Cmm;
    
    if ( n>0 ) Qml[1] = std::sqrt(2*m+1)*x*Qml[0];
    
    for (int i=2; i<=n; i++ )
      {
	int ll = m+i;
	Qml[i] = (2*ll-1)*x*Qml[i-1] - std::sqrt( (ll-1)*(ll-REAL(1)) - m*m )*Qml[i-2];
	Qml[i] /= std::sqrt(ll*ll - m*m);
      }
  }

  //-----------------------------------------------------------

  template <class REAL>
  void Ylm_spherical( int l, int m, REAL theta, std::vector<REAL> & ylm)
  // Spherical harmonics Y_lm without the exp(i*m*phi) multiplier
  {
    ylm.resize(l-m+1);
    int sgn = 1;
    if ( m < 0 &&  m%2 != 0 ) sgn = -1; 
    if (m<0) m = -m;
    Qml_legendre(l,m,std::cos(theta), ylm);
    //REAL Cml = std::exp(logfact(2*m)/2);
    for (int ll=m; ll<=l; ll++){
      ylm[ll-m] *= sgn*std::sqrt((2*ll+1)/(4*pi));
      //Cml *= std::sqrt((1e0+ll+m)/(1+ll-m));
    }
  }

#ifdef PY_EXPORT

  template <class REAL>
  void py_pl_legendre(REAL x, int l, py::list & Pl)
  {
    std::vector<REAL> res;
    Pl_legendre(x,l,res);
    for (int i=0; i<res.size(); i++)
      Pl.append(res[i]);
  }

  template <class REAL>
  void py_ylm_spherical ( int l, int m, REAL theta, py::list & ylm)
  { 
    std::vector<REAL> Q;
    Ylm_spherical(l,m,theta,Q);
    for (int i=0; i<Q.size(); i++)
      ylm.append(Q[i]);
  }
    
#endif


  //---------------------------------------------------------------------------------//
  /*
  double djmk_wigner(int J, int M, int K, double beta)
  {
    // fixme - inefficient implementation
    // It's better to use recurrence relations
    int sgn = 1;
    double pi=std::atan(1.)*4;

    if ((beta<=pi/2))//||(beta>=pi))
      {
  beta=pi-beta;
  if((J+M)%2==1){sgn*=(-1);};
  K = -K;
      };
    if (M+K<0)
      {
  int tmp = M;
  M = -K;
  K = -tmp;
      };
    if (K>M)
      {
  sgn *= ((K-M)%2 == 1)? -1 : 1;
  int tmp = K;
  K = M;
  M = tmp;
      };

    /// Calculating prefactor

    int f1 = 1;
    if ( (J-K)%2 == 1 ) {f1 = -1;};

    double f2 = 0e0;
    ///-
      for(int i = J-M+1;i<=J+M; i++)
  {
    f2 += std::log( (double)i );
  };
      f2 *= 0.5e0;

      double f3=0e0;
      for(int i = J-abs(K)+1; i<=J+abs(K); i++)
  {
    f3 += std::log( (double)i );
  };

      f3 *= 0.5e0;

      if(K<0) f3 = -f3;

      double fmk=0e0;
      for(int i = 1; i<=M+K; i++)
  {
    fmk += std::log( (double)i );
  };

      double beta2=beta/2;
      double Sin = std::sin(beta2);
      double Sin2J = std::pow(Sin, 2*J );
      double CTan = std::cos(beta2)/Sin;
      double CTan2 = CTan*CTan;
      double CTanMK = std::pow(CTan, M+K );

      double Prefac = sgn*Sin2J*CTanMK*f1*std::exp(f2+f3-fmk);

      double sum = 1e0, g = 1e0;


      for(int i = 0; i < J-M; i++)
  {

    g *= -CTan2*(J-M-i)*(J-K-i)/((i+1)*(M+K+i+1));


    sum += g;
  };


      return Prefac*sum;
  }
  */
};

#endif
