#ifndef _QPP_BASIS_H
#define _QPP_BASIS_H

#include <data/qppdata.hpp>
#include <geom/geom.hpp>
#include <lace/lace3d.hpp>
#include <boost/format.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace qpp{
  //fixme - this drags the whole namespace into qpp::
  //  using namespace boost::numeric::ublas;

  template<class FREAL, class CREAL>
  // FREAL - real number type for wavefunctions
  // CREAL - real number type for coordinates
  class basis : public qpp_object{

  public:

    // Number of basis functions
    int nfun;

    // Text label for i-th basis function
    virtual STRING label(int i) =0;

    // Calculate the values of basis functions on a grid
    virtual boost::numeric::ublas::vector<FREAL> & values(const std::vector<lace::vector3d<CREAL> > & grid) =0;

  };

  // -----------------------------------------------------------------

  template <class FREAL>
  class gencon_shell{
    int _nprim, _nl;
    int * _l;
    FREAL * _alpha, * _coeff;
    
    const static FREAL eps;

  public:

    gencon_shell(int __nprim, int __nl)
    {
      _nprim = __nprim;
      _nl = __nl;
      _l = new int[_nl];
      _alpha = new FREAL[_nprim];
      _coeff = new FREAL[_nprim*_nl];
    }

    gencon_shell(const gencon_shell<FREAL> & sh)
    {
      _nprim = sh._nprim;
      _nl = sh._nl;
      _l = new int[_nl];
      _alpha = new FREAL[_nprim];
      _coeff = new FREAL[_nprim*_nl];
      for (int i=0; i<_nl; i++)
	_l[i] = sh._l[i];
      for (int i=0; i<_nprim; i++)
	_alpha[i] = sh._alpha[i];
      for (int i=0; i<_nprim*_nl; i++)
	_coeff[i] = sh._coeff[i];
    }

    ~gencon_shell()
    {
      delete _l;
      delete _alpha;
      delete _coeff;
    }

    inline int nprim() const
    { return _nprim; }

    inline int nshells() const
    { return _nl; }

    inline int & l(int i)
    { return _l[i]; }

    inline int l(int i) const
    { return _l[i]; }

    inline FREAL & alpha(int i)
    { return _alpha[i]; }

    inline FREAL alpha(int i) const
    { return _alpha[i]; }

    inline FREAL & coeff(int i, int j)
    { return _coeff[i*_nprim+j]; }

    inline FREAL coeff(int i, int j) const
    { return _coeff[i*_nprim+j]; }

    inline bool operator==(const gencon_shell<FREAL> & sh) const
    {
      if (_nl != sh._nl || _nprim != sh._nprim)
	return false;
      for (int i=0; i<_nl; i++)
	if (_l[i] != sh._l[i])
	  return false;
      for (int i=0; i<_nprim; i++)
	if ( std::abs(_alpha[i] - sh._alpha[i]) > eps )
	  return false;
      for (int i=0; i<_nprim*_nl; i++)
	if ( std::abs(_coeff[i] - sh._coeff[i]) > eps )
	  return false;

      return true;
    }

    bool same_alpha(const gencon_shell<FREAL> & sh) const
    {
      if (_nprim != sh._nprim)
	return false;
      for (int i=0; i<_nprim; i++)
	if ( std::abs(_alpha[i] - sh._alpha[i]) > eps )
	  return false;

      return true;
    }

    void merge(const gencon_shell<FREAL> & sh)
    {
      int * new_l = new int[nshells()+sh.nshells()];
      for (int i=0; i<nshells(); i++)
	new_l[i] = _l[i];
      for (int i=0; i<sh.nshells(); i++)
	new_l[i+nshells()] = sh._l[i];

      FREAL * new_coeff = new FREAL[nprim()*(nshells()+sh.nshells())];
      for (int p=0; p<nprim(); p++)
	{
	  for (int i=0; i<nshells(); i++)
	    new_coeff[i*nprim()+p] = _coeff[i*nprim()+p];
	  for (int i=0; i<sh.nshells(); i++)
	    new_coeff[(i+nshells())*nprim()+p] = sh._coeff[i*nprim()+p];
	}
      
      delete _coeff;
      delete _l;
      _coeff = new_coeff;
      _l = new_l;

      _nl = nshells() + sh.nshells();
    }

    virtual void write_g98(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      for (int i=0; i<nshells(); i++)
	{
	  for (int f=0; f<offset; f++) os << " ";
	  if (l(i)==0)
	    os << "S";
	  else if (l(i)==1)
	    os << "P";
	  else if (l(i)==2)
	    os << "D";
	  else if (l(i)==3)
	    os << "F";
	  else if (l(i)==4)
	    os << "G";	  
	  os << "  " << nprim() << "  1.00\n";
	  for (int p=0; p<nprim(); p++)
	    {
	      for (int f=0; f<offset; f++) os << " ";
	      os << boost::format("%15.6f %15.6f\n") % alpha(p) % coeff(i,p);
	    }
	}      
    }

  };

  template <class FREAL>
  const FREAL gencon_shell<FREAL>::eps = 1e-7;

  // ----------------------------------------------------------------------
  
  template <class FREAL=double>
  class gencon_basis_data : public qpp_object{

  public:
    struct atom_record{

      std::vector<gencon_shell<FREAL> > shells;
      std::vector<STRING> labels;
      std::vector<int> numbers;

    };

  private:
    std::vector<atom_record> _rcrd;

  public:

    gencon_basis_data(const STRING & __name = "")
    { _name = __name; }    

    inline int nrcrd() const
    { return _rcrd.size();}

    inline atom_record & rcrd(int i)
    { return _rcrd[i];}

    void new_rcrd()
    {
      _rcrd.push_back( atom_record() );
    }

    void add_number(int r, int num)
    {
      _rcrd[r].numbers.push_back(num);
    }

    void add_label(int r, const STRING & lbl)
    {
      _rcrd[r].labels.push_back(lbl);
    }

    void add_shell(int r, const gencon_shell<FREAL> & sh)
    {
      bool found = false;
      for (int i=0; i<_rcrd[r].shells.size(); i++)
	if ( _rcrd[r].shells[i].same_alpha(sh))
	  {
	    _rcrd[r].shells[i].merge(sh);
	    found = true;
	    break;
	  }
      if (!found)
	_rcrd[r].shells.push_back(sh);
    }

    void add_number(int num)
    {
      add_number(_rcrd.size()-1,num);
    }

    void add_label(const STRING & lbl)
    {
      add_label(_rcrd.size()-1,lbl);
    }

    void add_shell(const gencon_shell<FREAL> & sh)
    {
      add_shell(_rcrd.size()-1,sh);
    }

    virtual int n_nested() const
    { return 0;}

    virtual qpp_object* nested(int i) const
    { return NULL;}

    virtual STRING category() const
    { return "basis";}

    virtual qppobject_type gettype() const
    { return qtype_basis | qtype_basis_gauss | qtype_data<FREAL>::type; }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      for (int i=0; i<offset; i++)
	os << " ";
      if ( name() != "")
	os << "basis " << name();
      else
	os << "basis";
      os << "(g98)";

      for (int i=0; i<offset+2; i++)
	os << " ";
      os << "{\n";

      for (int j=0; j<nrcrd(); j++)
	{
	  for (int i=0; i<offset+4; i++) os << " ";
	  for (int k=0; k<_rcrd[j].labels.size(); k++)
	    os << _rcrd[j].labels[k] << " ";
	  for (int k=0; k<_rcrd[j].numbers.size(); k++)
	    os << _rcrd[j].numbers[k] << " ";
	  os << "0\n";
	  for (int k=0; k<_rcrd[j].shells.size(); k++)
	    {
	      //debug
	      os << "shell number " << k << "\n";
	      _rcrd[j].shells[k].write_g98(os,offset+4);
	    }
	  for (int i=0; i<offset+4; i++) os << " ";
	  os << "****\n";
	}

      for (int i=0; i<offset+2; i++)
	os << " ";
      os << "}\n";
    }
  
  };

  // ----------------------------------------------------------------------

  const int Lmax = 3;

  const int nanglf[] = {1,3,6,10};
  
  // g98 ordering of cartesian atomic orbitals
  const int 
  manglf[][10][3] = {{{0,0,0}},
		     {{1,0,0}, {0,1,0}, {0,0,1}},
		     {{2,0,0}, {0,2,0}, {0,0,2}, {1,1,0}, {1,0,1}, {0,1,1}},
		     {{3,0,0}, {0,3,0}, {0,0,3}, {1,2,0}, {2,1,0}, {1,0,2}, {2,0,1}, {0,1,2}, {0,2,1}, {1,1,1}}};
  

  const STRING 
  anglf_label[][10] = {{"S"},
		       {"PX","PY","PZ"},
		       {"DXX","DYY","DZZ","DXY","DXZ","DYZ"},
		       {"FXXX","FYYY","FZZZ","FXYY","FXXY","FXZZ","FXXZ","FYZZ","FYYZ","FXYZ"}};
  
  // ----------------------------------------------------------------------

  template <class FREAL=double, int DIM=0 , class CREAL=double, 
	    class TRANSFORM = periodic_cell<DIM,CREAL> >
  class gauss_cart_basis{

    gencon_shell<FREAL> * _shells;
    geometry<DIM,CREAL,TRANSFORM> * _geom;

  public:

    int nsh;

    // Text label for i-th basis function
    virtual STRING label(int i)
    {}

    // Calculate the values of basis functions on a grid
    virtual boost::numeric::ublas::vector<FREAL> & values(const std::vector<lace::vector3d<CREAL> > & grid){}

    /*    virtual int n_next() const
    {
      return geom == NULL ? 0 : 1;
    }

    virtual qpp_object * next(int i) 
    {
      if (i==0)
	return geom;
      else 
	return NULL;
    }

    virtual STRING category() const
    {
      return "basis";
    }

    virtual STRING name() const
    {
      
    }

    virtual qppobject_type gettype() const=0;

    virtual void error(STRING const & what) =0;

    virtual STRING error() =0;

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const =0;    
    */

  };

  // -----------------------------------------------------------------

  template<class REAL, class BASIS1, class BASIS2>
  class integrator_1e{

  protected:

    bool _do_overlap, _do_d1_ovelap, _do_dipole, _do_coulomb, _do_d1_coulomb;

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
