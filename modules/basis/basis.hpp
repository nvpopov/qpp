#ifndef _QPP_BASIS_H
#define _QPP_BASIS_H

#include <data/qppdata.hpp>
#include <geom/geom.hpp>
#include <lace/lace3d.hpp>
#include <boost/format.hpp>
#include <boost/numeric/ublas/vector.hpp>
//debug
#include <iomanip>

namespace qpp{
  //fixme - this drags the whole namespace into qpp::
  //  using namespace boost::numeric::ublas;

  template<class FREAL, class CREAL>
  // FREAL - real number type for wavefunctions
  // CREAL - real number type for coordinates
  class basis //: public qpp_object{
  {

  public:

    // Number of basis functions
    int nfun;

    // Text label for i-th basis function
    virtual STRING label(int i) =0;

    // Calculate the values of basis functions on a grid
    virtual boost::numeric::ublas::vector<FREAL> & values(const std::vector<lace::vector3d<CREAL> > & grid) =0;

  };

  // -----------------------------------------------------------------

  enum qpp_bastype{
    qbas_gauss,
    qbas_slater,
    qbas_siesta,
    qbas_pw,
    qbas_none
  };

  qppobject_type qtype_bastype(qpp_bastype t);

  // -----------------------------------------------------------------

  enum qpp_angtype{
    qang_spherical,
    qang_cartesian
  };

  // ----------------------------------------------------------------

  template <qpp_bastype ST, class FREAL>
  class qpp_shell;
  // ----------------------------------------------------------------

#define QBAS qbas_gauss
#include <basis/shell.hpp>
#undef QBAS

#define QBAS qbas_slater
#include <basis/shell.hpp>
#undef QBAS


  // ----------------------------------------------------------------------
  
  template <qpp_bastype ST, class FREAL=double>
  class qpp_basis_data : public qpp_declaration{
    
    struct basis_record{

    public:

      std::vector<qpp_shell<ST,FREAL> > shells;
      std::vector<STRING> labels;
      std::vector<int> numbers;
      STRING import;
    
      bool empty()
      {
	return shells.size() == 0 && labels.size() == 0 &&
	  numbers.size() == 0 && import == "";
      }

    };

    std::vector<basis_record> _rcrd;

  public:

    qpp_basis_data(const STRING & __name = "", qpp_object * __owner = NULL,
		   qpp_param_array * __parm = NULL, 
		   int __line=-1, const STRING & __file="") : 
      qpp_declaration("basis",__name,__owner,__parm,__line,__file)
    {}    

    qpp_basis_data(const qpp_basis_data<ST,FREAL> & bas) :
      qpp_declaration(bas), _rcrd(bas._rcrd)
    {}

    qpp_basis_data(qpp_declaration * q) :
      qpp_declaration(*q)
    { 
      // debug
      //std::cerr << "Basis constructor from declaration called\n";

      for (int i=0; i<n_decl(); i++)
	if (decl(i)->category()=="center" && (decl(i)->gettype() & qtype_declaration ))
	  {
	    qpp_declaration * center = (qpp_declaration*)decl(i);
	    for (int j=0; j<center->n_decl(); j++)
	      insert_decl(i+j+1,*center->decl(j));
	    while (center->n_decl()>0)
	      center->erase_decl(0);
	  }
      /*
      for (int i=0; i<n_decl(); i++)
	if (decl(i)->category()=="center" && (decl(i)->gettype() & qtype_parameter ) )
	  {
	    if (decl(i)->gettype & qtype_data_int)
	      qpp_declaration * dcl = new qpp_declaration("center","",this,);
	      }*/
      //debug
      /*
      std::cerr << "After moving up alive\n=====================================\n";
      qpp_declaration::write(std::cerr);

      for (int i=0; i<n_decl(); i++)
	{
	  std::cerr << "=== type = " << std::hex << decl(i)->gettype() << " ===\n";
	  decl(i)->write(std::cerr);
	  std::cerr << "\n\n";
	}
      std::cerr << "=====================================\n";
      */

      new_rcrd();

      //debug
      //std::cerr << "alive0.1\n";

      for (int i=0; i<n_decl(); i++)
	{
	  //debug
	  //std::cerr << "alive1\n";
	  
	  if (decl(i)->category()=="shell")
	    {
	      //debug
	      //std::cerr << "alive2\n";

	      if (decl(i)->gettype() == qtype_shell + 
		  qtype_data<FREAL>::type + qtype_bastype(ST))
		add_shell(*((qpp_shell<ST,FREAL>*)decl(i)) );
	      else 
		owner()->error("Wrong basis shell type", decl(i)->line(), decl(i)->file());
	    }
	  else if (decl(i)->category()=="center")
	    {
	      //debug
	      //std::cerr << "alive4\n";

	      qpp_declaration * dcl = (qpp_declaration*)decl(i);
	      new_rcrd();
	      for (int j=0; j<dcl->n_param(); j++)
		if (dcl->param(j)->gettype()==qtype_parameter+qtype_data_int)
		  add_number( ((qpp_parameter<int>*)(dcl->param(j))) -> value());
		else if (dcl->param(j)->gettype()==qtype_parameter+qtype_data_string)
		  add_label( ((qpp_parameter<STRING>*)(dcl->param(j))) -> value());
	    }
	  else if (decl(i)->category()=="parameter")
	    {
	      //debug
	      //std::cerr << "alive3\n";

	      if (decl(i)->name() == "basis" && 
		  decl(i)->gettype() == qtype_parameter + qtype_data_string)
		add_import( ((qpp_parameter<STRING>*)decl(i))->value() );
	      else
		owner()->error("Wrong external basis request", decl(i)->line(), decl(i)->file());
	    }
	  else
	    owner()->error("Only declaration of shell, external basis and \"center\" are allowed inside basis definition", 
		  decl(i)->line(), decl(i)->file());
	
	  //debug
	  // std::cerr << "alive5\n";

	}

      if (rcrd(0).empty())
      	_rcrd.erase(_rcrd.begin());
	
    }

    inline int n_rcrd() const
    { return _rcrd.size();}

    inline basis_record & rcrd(int i)
    { return _rcrd[i];}

    void new_rcrd()
    {
      _rcrd.push_back( basis_record() );
    }

    void add_number(int r, int num)
    {
      _rcrd[r].numbers.push_back(num);
    }

    void add_label(int r, const STRING & lbl)
    {
      _rcrd[r].labels.push_back(lbl);
    }

    void add_shell(int r, const qpp_shell<ST,FREAL> & sh)
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

    void add_import(int r, const STRING & imp)
    {
      _rcrd[r].import = imp;
    }

    void add_number(int num)
    {
      add_number(_rcrd.size()-1,num);
    }

    void add_label(const STRING & lbl)
    {
      add_label(_rcrd.size()-1,lbl);
    }

    void add_shell(const qpp_shell<ST,FREAL> & sh)
    {
      add_shell(_rcrd.size()-1,sh);
    }

    void add_import(const STRING & imp)
    {
      _rcrd[_rcrd.size()-1].import = imp;
    }

    virtual STRING category() const
    { return "basis";}

    virtual qppobject_type gettype() const
    //fixme
    { return qtype_basis | qtype_basis_gauss | qtype_data<FREAL>::type; }

    virtual qpp_object * copy() const
    {
      return new qpp_basis_data<ST,FREAL>(*this);
    }

    virtual void write_g98(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
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

      for (int j=0; j<n_rcrd(); j++)
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

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      //debug
      for (int k=0; k<offset; k++) os << " ";
      os << "type= " << std::hex << gettype() << std::dec << std::endl;


      for (int k=0; k<offset; k++) os << " ";
      os << "basis";
      if (name()!="")
	os << " " << name() << "(";
      os << "( real=";
      if (qtype_data<FREAL>::type == qtype_data_double)
	os << "double";
      else
	os << "float";
      os << ", bastype=";
      if (ST==qbas_gauss)
	os << "gaussian";
      else if (ST==qbas_slater)
	os << "slater";
      else if (ST==qbas_siesta)
	os << "siesta";
      else if (ST==qbas_pw)
	os << "plane_waves";
      os << ")\n";
      for (int k=0; k<offset+2; k++) os << " ";
      os << "{\n";
      for (int i=0; i<n_rcrd(); i++)
	{

	  //debug
	  //os << "--- record " << i << "----\n";

	  if (_rcrd[i].labels.size()>0 || _rcrd[i].numbers.size()>0)
	    {
	      for (int k=0; k<offset+4; k++) os << " ";
	      os << "center(";
	      int p=0;
	      for (int k=0; k<_rcrd[i].labels.size(); k++)
		os << (p++>0? ", " : "") << _rcrd[i].labels[k];
	      for (int k=0; k<_rcrd[i].numbers.size(); k++)
		os << (p++>0? ", " : "") << _rcrd[i].numbers[k];
	      os << ");\n";
	    }
	  if (_rcrd[i].import!="")
	    {
	      for (int k=0; k<offset+4; k++) os << " ";
	      os << "basis = " << _rcrd[i].import << ";\n";
	    }
	  for (int j=0; j<_rcrd[i].shells.size(); j++)
	    _rcrd[i].shells[j].write(os,offset+4);
	}
      for (int k=0; k<offset+2; k++) os << " ";
      os << "}\n";

      //debug
      //os << "nrcrd = " << _rcrd.size() << "\n";
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
  /*
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

  };
    */

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
