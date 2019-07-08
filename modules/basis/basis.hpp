#ifndef QPP_BASIS_H
#define QPP_BASIS_H

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
//#include <pybind11/stl.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

//#include <data/data.hpp>
#include <geom/geom.hpp>
#include <basis/ecp.hpp>
#include <geom/lace3d.hpp>
#include <Eigen/Dense>
#include <fmt/format.h>
#include <fmt/ostream.h>

namespace qpp {
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
      virtual STRING_EX label(int i) =0;

      // Calculate the values of basis functions on a grid

      virtual Eigen::Matrix<FREAL, Eigen::Dynamic, 1> &
      values(const std::vector<vector3<CREAL> > & grid) =0;

  };

  // -----------------------------------------------------------------

  enum qpp_bastype {
    qbas_gauss,
    qbas_slater,
    qbas_siesta,
    qbas_pw,
    qbas_none
  };

  //  qppobject_type qtype_bastype(qpp_bastype t);

  // -----------------------------------------------------------------

  enum qpp_angtype {
    qang_spherical,
    qang_cartesian
  };

  // ----------------------------------------------------------------

  template <qpp_bastype BT, class FREAL>
  class qpp_shell;
  // ----------------------------------------------------------------

#define QBAS qbas_gauss
#include <basis/shell.hpp>
#undef QBAS

#define QBAS qbas_slater
#include <basis/shell.hpp>
#undef QBAS

  // ----------------------------------------------------------------

  template <qpp_bastype BT, class FREAL=double>
  class atomic_basis{
    public:

      STRING_EX atom, basis_name;
      std::vector<qpp_shell<BT, FREAL> > shells;
      atomic_ecp<FREAL> ecp;

      bool empty(){
        return shells.size() == 0 && basis_name == "";
      }

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

      static void py_export(py::module m, const char * pyname){
        //*py::class_< std::vector<qpp_shell<BT,FREAL> > >(m, pyname)
        //.def(bp::vector_indexing_suite<std::vector<qpp_shell<BT,FREAL> > >() );

        py::class_<atomic_basis<BT,FREAL> >(m, pyname)
            //TODO: Why init didnt be here in original bp bindings?
            .def(py::init<>())
            //TODO: cannot add
            .def_readwrite("shells", &atomic_basis<BT,FREAL>::shells )
            .def_readwrite("ecp",    &atomic_basis<BT,FREAL>::ecp)
            .def_readwrite("atom",   &atomic_basis<BT,FREAL>::atom )
            .def_readwrite("basis_name",   &atomic_basis<BT,FREAL>::basis_name )
            ;
      }

#endif

  };

  // ----------------------------------------------------------------------
  /*
  template <qpp_bastype ST, class FREAL=double>
  class qpp_basis_data : public qpp_declaration{

    std::vector<std::vector<STRING_EX> > labels;
    std::vector<std::vector<int> > numbers;
    std::vector<atomic_basis<ST,FREAL> > _atbasis;

  public:

    qpp_basis_data(const STRING_EX & __name = "", qpp_object * __owner = NULL,
       qpp_param_array * __parm = NULL,
       int __line=-1, const STRING_EX & __file="") :
      qpp_declaration("basis",__name,__owner,__parm,__line,__file)
    {}

    qpp_basis_data(const qpp_basis_data<ST,FREAL> & bas) :
      qpp_declaration(bas)
      // fixme - implement this
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


      new_atbasis();

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
        new_atbasis();
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

      if (_atbasis[0].empty())
        _atbasis.erase(_atbasis.begin());

    }

    inline int n_atbasis() const
    { return _atbasis.size();}

    inline atomic_basis<ST,FREAL> & atbasis(int i)
    { return _atbasis[i];}

    void new_atbasis()
    {
      _atbasis.push_back( atomic_basis<ST,FREAL>() );
      labels.push_back(std::vector<STRING>());
      numbers.push_back(std::vector<int>());
    }

    inline void add_number(int r, int num)
    {
      numbers[r].push_back(num);
    }

    void add_number(int num)
    {
      add_number(n_atbasis(),num);
    }

    void add_label(int r, const STRING_EX & lbl)
    {
      labels[r].push_back(lbl);
    }

    void add_label(const STRING_EX & lbl)
    {
      add_label(n_atbasis()-1,lbl);
    }

    void add_shell(int r, const qpp_shell<ST,FREAL> & sh)
    {
      bool found = false;
      for (int i=0; i<_atbasis[r].shells.size(); i++)
  if ( _atbasis[r].shells[i].same_alpha(sh))
    {
      _atbasis[r].shells[i].merge(sh);
      found = true;
      break;
    }
      if (!found)
  _atbasis[r].shells.push_back(sh);
    }

    void add_shell(const qpp_shell<ST,FREAL> & sh)
    {
      add_shell(n_atbasis()-1,sh);
    }

    void add_import(int r, const STRING_EX & imp)
    {
      _atbasis[r].basis_import = imp;
    }

    void add_import(const STRING_EX & imp)
    {
      _atbasis[n_atbasis()-1].basis_import = imp;
    }

    virtual STRING_EX category() const
    { return "basis";}

    virtual qppobject_type gettype() const
    //fixme
    { return qtype_basis | qtype_basis_gauss | qtype_data<FREAL>::type; }

    virtual qpp_object * copy() const
    {
      return new qpp_basis_data<ST,FREAL>(*this);
    }

    virtual void write_g98(std::basic_ostream<CHAR_EX,TRAITS> &os, int offset=0) const
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

      for (int j=0; j<n_atbasis(); j++)
  {
    for (int i=0; i<offset+4; i++) os << " ";
    for (int k=0; k<labels[j].size(); k++)
      os << labels[j][k] << " ";
    for (int k=0; k<numbers[j].size(); k++)
      os << numbers[j][k] << " ";
    os << "0\n";
    for (int k=0; k<_atbasis[j].shells.size(); k++)
      {
        //debug
        os << "shell number " << k << "\n";
        _atbasis[j].shells[k].write_g98(os,offset+4);
      }
    for (int i=0; i<offset+4; i++) os << " ";
    os << "****\n";
  }

      for (int i=0; i<offset+2; i++)
  os << " ";
      os << "}\n";
    }

    virtual void write(std::basic_ostream<CHAR_EX, TRAITS> &os, int offset=0) const
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
      for (int i=0; i<n_atbasis(); i++)
  {

    //debug
    //os << "--- record " << i << "----\n";

    if (labels[i].size()>0 || numbers[i].size()>0)
      {
        for (int k=0; k<offset+4; k++) os << " ";
        os << "center(";
        int p=0;
        for (int k=0; k<labels[i].size(); k++)
    os << (p++>0? ", " : "") << labels[i][k];
        for (int k=0; k<numbers[i].size(); k++)
    os << (p++>0? ", " : "") << numbers[i][k];
        os << ");\n";
      }
    if (_atbasis[i].basis_import!="")
      {
        for (int k=0; k<offset+4; k++) os << " ";
        os << "basis = " << _atbasis[i].basis_import << ";\n";
      }
    for (int j=0; j<_atbasis[i].shells.size(); j++)
      _atbasis[i].shells[j].write(os,offset+4);
  }
      for (int k=0; k<offset+2; k++) os << " ";
      os << "}\n";

      //debug
      //os << "nrcrd = " << _rcrd.size() << "\n";
    }

  };
          */
  // ----------------------------------------------------------------------

  const int Lmax = 3;

  const int nanglf[] = {1,3,6,10};

  // g98 ordering of cartesian atomic orbitals
  const int
  manglf[][10][3] = {{{0,0,0}},
                     {{1,0,0}, {0,1,0}, {0,0,1}},
                     {{2,0,0}, {0,2,0}, {0,0,2}, {1,1,0}, {1,0,1}, {0,1,1}},
                     {{3,0,0}, {0,3,0}, {0,0,3}, {1,2,0}, {2,1,0}, {1,0,2}, {2,0,1}, {0,1,2}, {0,2,1}, {1,1,1}}};


  const STRING_EX
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
    virtual STRING_EX label(int i)
    {}

    // Calculate the values of basis functions on a grid
    virtual boost::numeric::ublas::vector<FREAL> & values(const std::vector<vector3d<CREAL> > & grid){}

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

    virtual STRING_EX category() const
    {
      return "basis";
    }

    virtual STRING_EX name() const
    {

    }

    virtual qppobject_type gettype() const=0;

    virtual void error(STRING_EX const & what) =0;

    virtual STRING_EX error() =0;

    virtual void write(std::basic_ostream<CHAR_EX, TRAITS> &os, int offset=0) const =0;

  };
    */

  // -----------------------------------------------------------------

  template<class REAL, class BASIS1, class BASIS2>
  class integrator_1e {

    protected:

      bool _do_overlap, _do_d1_ovelap, _do_dipole, _do_coulomb, _do_d1_coulomb;


      Eigen::Matrix<REAL, Eigen::Dynamic, Eigen::Dynamic> * overlap;

    public:

      void no_overlap()
      { _do_overlap = false; }

      void do_overlap(Eigen::Matrix<REAL, Eigen::Dynamic, Eigen::Dynamic> & S) {
        _do_overlap = true;
        overlap = & S;
      }

      // ..............................

      virtual void calculate() =0;

  };

  // ------------------------------------------------------------------

};

#endif
