#ifndef QPP_ECP_H
#define QPP_ECP_H

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

namespace qpp{

  template <class FREAL>
  class atomic_ecp {

    std::vector<std::vector<FREAL> > _coeff, _alpha;
    std::vector<std::vector<int> > _n;

  public:

    STRING_EX name;
    int nelec;

    void init_props(){
#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
      py_n.bind(this);
      py_nprim.bind(this);
      py_coeff.bind(this);
      py_alpha.bind(this);
#endif
    }

    atomic_ecp(){
      init_props();
    }

    atomic_ecp(int __L):
      _coeff(__L+1), _alpha(__L+1), _n(__L+1){
      init_props();
    }

    atomic_ecp(const std::vector<int> & nl){
      _n.resize(nl.size());
      _coeff.resize(nl.size());
      _alpha.resize(nl.size());
      for (int i=0; i<nl.size(); i++){
          _n[i].resize(nl[i]);
          _coeff[i].resize(nl[i]);
          _alpha[i].resize(nl[i]);
        }
      init_props();
    }

    inline int nprim(int l) const{
      return _n[l].size();
    }

    inline void setnprim(int l, int nl){
      _n[l].resize(nl);
      _coeff[l].resize(nl);
      _alpha[l].resize(nl);
    }

    inline int L() const
    { return _n.size()-1; }

    inline bool empty() const
    { return L()==-1; };

    inline int n(int l, int i) const
    { return _n[l][i]; }

    inline int & n(int l, int i)
    { return _n[l][i]; }

    inline FREAL coeff(int l, int i) const
    { return _coeff[l][i]; }

    inline FREAL & coeff(int l, int i)
    { return _coeff[l][i]; }

    inline FREAL alpha(int l, int i) const
    { return _alpha[l][i]; }

    inline FREAL & alpha(int l, int i)
    { return _alpha[l][i]; }

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

    typedef atomic_ecp<FREAL> SELF;

    atomic_ecp(const py::list & nl){
      int _L = py::len(nl);
      _n.resize(_L);
      _coeff.resize(_L);
      _alpha.resize(_L);
      for (int i=0; i<_L; i++)
        {
          int ni = py::cast<int>(nl[i]);
          _n[i].resize(ni);
          _coeff[i].resize(ni);
          _alpha[i].resize(ni);
        }
      init_props();
    }

    int  py_getnprim(int l) { return nprim(l); }
    void py_setnprim(int l, const int & np) { setnprim(l,np); }

    py_indexed_property< SELF, int, int,
                        & SELF::py_getnprim,
                        & SELF::py_setnprim> py_nprim;

    py::list py_getalln(int l){}

    void py_setalln(int l, const py::list & ln){}

    int  py_getn(int l, int i) { return n(l,i);}
    void py_setn(int l, int i, const int & nn) { n(l,i) = nn;}
    py_2indexed_property<SELF, py::list, int, int,
    &SELF::py_getalln, &SELF::py_setalln,
    &SELF::py_getn, &SELF::py_setn > py_n;



    py::list py_getallcoeff(int l){}

    void py_setallcoeff(int l, const py::list & a){}

    FREAL py_getcoeff(int l, int i) { return coeff(l,i); }
    void py_setcoeff(int l, int i, const FREAL & a) { coeff(l,i) = a; }
    py_2indexed_property<SELF, py::list, FREAL, int,
    &SELF::py_getallcoeff, &SELF::py_setallcoeff,
    &SELF::py_getcoeff, &SELF::py_setcoeff > py_coeff;


    py::list py_getallalpha(int l) {}

    void py_setallalpha(int l, const py::list & a){}

    FREAL py_getalpha(int l, int i) { return alpha(l,i); }
    void py_setalpha(int l, int i, const FREAL & a) { alpha(l,i) = a; }
    py_2indexed_property<SELF, py::list, FREAL, int,
    &SELF::py_getallalpha, &SELF::py_setallalpha,
    &SELF::py_getalpha, &SELF::py_setalpha > py_alpha;



    static void py_props(py::module m, const char * pyname){

      std::string sPropNameNPrim =
           fmt::format("{0}_{1}",pyname,"idx_prop_nprim");
      py_indexed_property< SELF, int, int, & SELF::py_getnprim,
          & SELF::py_setnprim>::py_export(m, sPropNameNPrim.c_str());

      std::string sPropNameN =
           fmt::format("{0}_{1}",pyname,"idx_prop_n");
      py_2indexed_property<SELF, py::list, int, int,
          &SELF::py_getalln, &SELF::py_setalln,
          &SELF::py_getn, &SELF::py_setn >::py_2export(m, sPropNameN.c_str());

      std::string sPropNameCoeff =
           fmt::format("{0}_{1}",pyname,"idx_prop_coeff");
      py_2indexed_property<SELF, py::list, FREAL, int,
          &SELF::py_getallcoeff, &SELF::py_setallcoeff,
          &SELF::py_getcoeff,
          &SELF::py_setcoeff >::py_2export(m, sPropNameCoeff.c_str());

      std::string sPropNameAlpha =
           fmt::format("{0}_{1}",pyname,"idx_prop_alpha");
      py_2indexed_property<SELF, py::list, FREAL, int,
          &SELF::py_getallalpha, &SELF::py_setallalpha,
          &SELF::py_getalpha, &SELF::py_setalpha >
          ::py_2export(m, sPropNameAlpha.c_str());
    }

#endif

  };

}

#endif

