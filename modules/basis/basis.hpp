#ifndef _QPP_BASIS_H
#define _QPP_BASIS_H

#include <io/qppdata.hpp>
#include <lace/lace3d.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace qpp{
  //fixme - this drags the whole namespace into qpp::
  //  using namespace boost::numeric::ublas;

  template <class REAL,class charT=std::string::value_type , class traits = std::char_traits<charT> >
  class basis : public qpp_object<charT,traits>{

  public:

    using qpp_object<charT,traits>::string;

    // Number of basis functions
    int nfunc;

    // Text label for i-th basis function
    virtual string label(int i) =0;

    // Calculate the values of basis functions on a grid
    virtual boost::numeric::ublas::vector<REAL> & values(const std::vector<lace::vector3d<REAL> > & grid) =0;

  };

  // -----------------------------------------------------------------

  template <class REAL>
  class gencon_shell{
    int _nprim, _nl;
    int * _l;
    REAL * _alpha, * _coeff;
    
  public:

    gencon_shell(int __nprim, int __nl)
    {
      _nprim = __nprim;
      _nl = __nl;
      _l = new int[_nl];
      _alpha = new REAL[_nprim];
      _coeff = new REAL[_nprim*_nl];
    }

    inline int nprim()
    { return _nprim; }

    inline int nshells()
    { return _nl; }

    inline REAL & alpha(int i)
    { return _alpha[i]; }

    inline REAL & coeff(int i, int j)
    { return _coeff[]; }

  };

  // -----------------------------------------------------------------

  template<class REAL, class BASIS1, class BASIS2>
  class integrator_1e{

  protected:

    bool do_overlap, do_d1_ovelap, do_dipole, do_coulomb, do_d1_coulomb;

      boost::numeric::ublas::matrix<REAL> * overlap;

  public:

    void no_overlap()
    { do_overlap = false; }

    void do_overlap(boost::numeric::ublas::matrix<REAL> & S)
    { 
      _do_overlap = true;
      overlap = & S;
    }

    // ..............................

    virtual void calculate() =0;

  };

  // ------------------------------------------------------------------

};

#endif
