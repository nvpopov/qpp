#ifndef QPP_GEOM_EXTRAS_H
#define QPP_GEOM_EXTRAS_H

#include <data/types.hpp>
#include <data/errors.hpp>
#include <data/data.hpp>
#include <geom/geom.hpp>
#include <io/strfun.hpp>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>

#ifdef PY_EXPORT
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#endif

namespace qpp{

  template<class REAL, class CELL>
  ///
  /// \brief  Geometry with extra fields - for storing any additional data
  ///
  class xgeometry : public geometry<REAL,CELL>{

    std::vector<std::vector<REAL> >   _xreal;
    std::vector<std::vector<int> >    _xint;
    std::vector<std::vector<short> >  _xbool;
    std::vector<std::vector<STRING> > _xstring;

    std::vector<STRING>       _field_name;
    std::vector<basic_types>  _field_type;

    std::vector<int>          _field_idx;
    std::vector<char>         _field_additive;

    int _nxreal, _nxint, _nxbool, _nxstring, _nfields;
    int ix_charge, ix_x, ix_y, ix_z, ix_atom, ix_mass, ix_number;

    using geometry<REAL,CELL>::_atm;
    using geometry<REAL,CELL>::_crd;
    using geometry<REAL,CELL>::size;
    using geometry<REAL,CELL>::has_observers;
    using geometry<REAL,CELL>::observers;
    //using geometry<DIM,REAL,CELL>::error;

    void init_xdefault(){
      _nxreal = _nxstring = _nxint = _nxbool = 0;
#ifdef PY_EXPORT
      py_fields.bind(this);
      py_add.bind(this);
#endif
    }

  public:

    typedef xgeometry<REAL,CELL> SELF;

    using geometry<REAL,CELL>::DIM;
    using geometry<REAL,CELL>::name;
    using geometry<REAL,CELL>::cell;
    using geometry<REAL,CELL>::nat;
    using geometry<REAL,CELL>::type;
    using geometry<REAL,CELL>::define_type;
    using geometry<REAL,CELL>::auto_update_types;

    virtual bool is_xgeometry() const{return true;}

    inline int nfields() const{ return _nfields; }

    inline STRING field_name(int i) const{ return _field_name[i]; }

    inline basic_types field_type(int i) const{ return _field_type[i]; }

    // Constructors

    ///
    /// \brief xgeometry
    /// \param __cell
    /// \param __nxstring
    /// \param __nxreal
    /// \param __nxint
    /// \param __nxbool
    /// \param __name
    ///
    xgeometry(CELL & __cell,
              int __nxstring, int __nxreal=0, int __nxint=0, int __nxbool=0,
              const STRING & __name = "") :
      _xstring(__nxstring), _xreal(__nxreal), _xint(__nxint), _xbool(__nxbool),
      _field_name(__nxreal + __nxint + __nxbool + __nxstring),
      _field_type(__nxreal + __nxint + __nxbool + __nxstring),
      _field_idx(__nxreal + __nxint + __nxbool + __nxstring),
      _field_additive(__nxreal + __nxint + __nxbool + __nxstring),
      geometry<REAL,CELL>(__cell, __name){
      init_xdefault();
      _nxreal   = __nxreal;
      _nxint    = __nxint;
      _nxbool   = __nxbool;
      _nxstring = __nxstring;
    }

    ///
    /// \brief xgeometry
    /// \param __cell
    /// \param __name
    ///
    xgeometry(CELL & __cell,  const STRING & __name = "") :
      geometry<REAL,CELL>(__cell, __name){
      init_xdefault();
    }

    ///
    /// \brief xgeometry
    /// \param dim
    /// \param __name
    ///
    xgeometry(int dim,  const STRING & __name = "") :
      geometry<REAL,CELL>(dim, __name){
      init_xdefault();
    }

    ///
    /// \brief get_format
    /// \param fn
    /// \param ft
    ///
    void get_format(std::vector<STRING> & fn, std::vector<basic_types> & ft){
      fn = _field_name;
      ft = _field_type;
    }

    ///
    /// \brief set_format
    /// \param fn
    /// \param ft
    ///
    void set_format(const std::vector<STRING> & fn,
                    const std::vector<basic_types> & ft){
      _field_name = fn;
      _field_type = ft;
      _nxstring = std::count(ft.begin(), ft.end(), type_string);
      _nxreal = std::count(ft.begin(), ft.end(), type_real);
      _nxint = std::count(ft.begin(), ft.end(), type_int);
      _nxbool = std::count(ft.begin(), ft.end(), type_bool);

      if (fn.size() != ft.size() || fn.size()
          != _nxstring + _nxreal + _nxint + _nxbool){
          IndexError("xgeometry::format: field names or types mismatch");
        }

      _nfields = ft.size();
      _field_idx.resize(_nfields);

      int is = 0, ib = 0, ir = 0, ii = 0;

      ix_x = ix_y = ix_z = ix_atom = -1;
      ix_charge = ix_mass = ix_number = -1;

      for (int j = 0; j < _nfields; j++){
          basic_types tp = field_type(j);
          if ( tp == type_string ){
              _field_idx[j] = is++;
              if ( field_name(j) == "atom" ) ix_atom = j;
            }
          else if ( tp == type_real || tp == attributes<REAL>::type ){
              _field_type[j] = type_real;
              _field_idx[j] = ir++;
              if ( field_name(j) == "x" )      ix_x = j;
              else if ( field_name(j) == "y" ) ix_y = j;
              else if ( field_name(j) == "z" ) ix_z = j;
              else if ( field_name(j) == "charge" ) ix_charge = j;
              else if ( field_name(j) == "mass" )   ix_mass   = j;
            }
          else if ( tp == type_int ){
              _field_idx[j] = ii++;
              if ( field_name(j) == "number" ) ix_number = j;
            }
          else if ( tp == type_bool )
            _field_idx[j] = ib++;
          else{
              TypeError("xgeometry::format: invalid type");
            }
        }

      /*
      for (int i=0; i<_nfields; i++)
        std::cout << field_name(i) << " " << field_type(i) << " " << _field_idx[i] << "\n";
      std::cout << ix_atom << " " << ix_x << " " << ix_y << " " << ix_z << "\n";
      */

      if (ix_atom == -1 && ix_x == -1 && ix_y==-1 && ix_z==-1){
          ix_atom = 0;
          ix_x = 1; ix_y = 2; ix_z = 3;
          if (ix_charge >= 0) ix_charge += 4;
          if (ix_mass >= 0)   ix_mass   += 4;
          if (ix_number >= 0) ix_number += 4;

          _nfields  += 4;
          _nxstring += 1;
          _nxreal   += 3;

          std::vector<STRING> inss = {"atom","x","y","z"};
          _field_name.insert(_field_name.begin(), inss.begin(), inss.end());

          std::vector<basic_types> inst = {type_string, type_real, type_real, type_real};
          _field_type.insert(_field_type.begin(), inst.begin(), inst.end());

          std::vector<int> insi = {0,0,1,2};
          _field_idx.insert(_field_idx.begin(), insi.begin(), insi.end());

          /*
          for (int j=4; j<_nfields; j++)
            if (field_type(j)==type_string)
              _field_idx[j] += 1;
            else if (field_type(j)==type_real)
              _field_idx[j] += 3;
          */

        }

      _field_additive.resize(_nfields);
      for (int i=0; i<_nfields; i++)
        _field_additive[i] = false;
      if (ix_charge>=0)
        _field_additive[ix_charge] = true;

      if (ix_atom == -1 || ix_x == -1 || ix_y == -1 || ix_z == -1){
          KeyError("xgeometry::format: the geometry does not have either atom names, x, y, or z coordinates");
        }

      _xstring.resize(_nxstring);
      _xreal.resize(_nxreal);
      _xint.resize(_nxint);
      _xbool.resize(_nxbool);


    }

    ///
    /// \brief xgeometry
    /// \param __cell
    /// \param fn
    /// \param ft
    /// \param __name
    ///
    xgeometry(CELL & __cell,  const std::vector<STRING> & fn,
              const std::vector<basic_types> & ft,
              const STRING & __name = "") : geometry<REAL,CELL>(__cell, __name){
      init_xdefault();
      set_format(fn,ft);
    }

    int nfields_string() const{ return _nxstring; }

    int nfields_real() const{ return _nxreal; }

    int nfields_int() const{ return _nxint;}

    int nfields_bool() const{ return _nxbool;}

    bool additive(int i) const{ return (bool)_field_additive[i]; }

    bool & additive(int i){ return *((bool*)(&_field_additive[i])); }

    template<class T>
    T & xfield(int i, int j){
      basic_types ft = field_type(i);
      if (ft == type_real)
        ft = attributes<REAL>::type;
      if (attributes<T>::type != ft)
        throw std::invalid_argument("xgeometry::xfield - wrong type for the field " + t2s(i));

      if (attributes<T>::type == type_string){
          if (i==ix_atom)
            return convert<T&,STRING&>::get(_atm[j]);
          else
            return  convert<T&,STRING&>::get(_xstring[_field_idx[i]][j]);
        }
      else if (attributes<T>::type == type_bool)
        return  convert<T&,short&>::get(_xbool[_field_idx[i]][j]);
      else if (attributes<T>::type == type_int)
        return convert<T&,int&>::get(_xint[_field_idx[i]][j]);
      else if (attributes<T>::type == attributes<REAL>::type){
          if (i==ix_x)
            return convert<T&,REAL&>::get(_crd[j].x());
          else if (i==ix_y)
            return convert<T&,REAL&>::get(_crd[j].y());
          else if (i==ix_z)
            return convert<T&,REAL&>::get(_crd[j].z());
          else
            return convert<T&,REAL&>::get(_xreal[_field_idx[i]][j]);
        }
      else
        throw std::invalid_argument("Illegal type of xgeometry extra field");
    }

    template<class T>
    inline T xfield(int i, int j) const{
      basic_types ft = field_type(i);
      if (ft == type_real)
        ft = attributes<REAL>::type;
      if (attributes<T>::type != ft)
        throw std::invalid_argument(
            "xgeometry::xfield - wrong type for the field " + t2s(i));

      if (attributes<T>::type == type_string){
          if (i==ix_atom)
            return convert<T,STRING>::get(_atm[j]);
          else
            return  convert<T,STRING>::get(_xstring[_field_idx[i]][j]);
        }
      else if (attributes<T>::type == type_bool)
        return  convert<T,short>::get(_xbool[_field_idx[i]][j]);
      else if (attributes<T>::type == type_int)
        return convert<T,int>::get(_xint[_field_idx[i]][j]);
      else if (attributes<T>::type == attributes<REAL>::type){
          if (i==ix_x)
            return convert<T,REAL>::get(_crd[j].x());
          else if (i==ix_y)
            return convert<T,REAL>::get(_crd[j].y());
          else if (i==ix_z)
            return convert<T,REAL>::get(_crd[j].z());
          else
            return convert<T,REAL>::get(_xreal[_field_idx[i]][j]);
        }
      else
        throw std::invalid_argument("Illegal type of xgeometry extra field");
    }

    template<class T>
    inline T & xfield(const STRING & f, int j){
      int i = 0;
      while (_field_name[i]!=f && i<nfields()) i++;

      if (i<nfields())
        return xfield<T>(i,j);
      else{
          KeyError("Field not found in xgeometry");
        }
    }

    template<class T>
    T xfield(const STRING & f, int j) const{
      int i = 0;
      while (_field_name[i]!=f && i<nfields()) i++;

      if (i<nfields())
        return xfield<T>(i,j);
      else{
          KeyError("Field not found in xgeometry");
        }
    }

    // ----------------------------------------------------

    virtual void get_fields(int j, std::vector<datum> & v) const{
      if (j<0) j+=nat();
      if (j<0 || j>= nat()) IndexError("xgeometry::py_getitem: index out of range");

      v.resize(nfields());
      for (int i=0; i<nfields(); i++){
          if (field_type(i)==type_string)
            v[i] = xfield<STRING>(i,j);
          else if (field_type(i)==type_real)
            v[i] = xfield<REAL>(i,j);
          else if (field_type(i)==type_int)
            v[i] = xfield<int>(i,j);
          else if (field_type(i)==type_bool)
            v[i] = xfield<bool>(i,j);
        }
    }

    virtual void set_fields(int j, const std::vector<datum> & v){
      if (j<0) j+=nat();
      if (j<0 || j>= nat()) IndexError("xgeometry::set_fields: index out of range");
      if (v.size()!=nfields())
        IndexError("xgeometry::set_fields: wrong number of fields");

      STRING a1 = v[ix_atom].template get<STRING>();
      vector3<REAL> r1(v[ix_x].template get<REAL>(),
                       v[ix_y].template get<REAL>(),
                       v[ix_z].template get<REAL>());
      if (has_observers)
        for (int i=0; i<observers.size(); i++)
          observers[i]->changed(j, before, a1, r1);

      for (int i=0; i<nfields(); i++){
          if (field_type(i)==type_string)
            xfield<STRING>(i,j) = v[i].get<STRING>();
          else if (field_type(i)==type_real)
            xfield<REAL>(i,j) = v[i].get<REAL>();
          else if (field_type(i)==type_int)
            xfield<int>(i,j) = v[i].get<int>();
          else if (field_type(i)==type_bool)
            xfield<bool>(i,j) = v[i].get<bool>();
        }

      if (has_observers)
        for (int i=0; i<observers.size(); i++)
          observers[i]->changed(j, after, a1, r1);
    }

    // ----------------------------------------------------

    virtual void erase(int j){
      geometry<REAL,CELL>::erase(j);
      for (int i=0; i<_nxreal; i++)
        _xreal[i].erase(_xreal[i].begin()+j);
      for (int i=0; i<_nxint; i++)
        _xint[i].erase(_xint[i].begin()+j);
      for (int i=0; i<_nxbool; i++)
        _xbool[i].erase(_xbool[i].begin()+j);
    }

    void add(const STRING & a, const vector3<REAL> & r,
             std::initializer_list<STRING> xts,
             std::initializer_list<REAL> xtr = {},
             std::initializer_list<int> xti = {},
             std::initializer_list<bool> xtb = {}){

      int i = 0;
      for (const auto & xs : xts)
        _xstring[i++].push_back(xs);

      i = 0;
      for (const auto & xr : xtr)
        _xreal[i++].push_back(xr);

      i = 0;
      for (const auto & xi : xti)
        _xint[i++].push_back(xi);

      i = 0;
      for (const auto & xb : xtb)
        _xbool[i++].push_back(xb);

      geometry<REAL,CELL>::add(a,r);
    }

    void insert(const int j, const STRING & a, const vector3<REAL> &r,
                std::initializer_list<STRING> xts,
                std::initializer_list<REAL> xtr = {},
                std::initializer_list<int> xti = {},
                std::initializer_list<bool> xtb = {}){
      int i = 0;
      for ( const auto & xs : xts )
        _xstring[i].insert( _xstring[i++].begin() + j, xs);

      i = 0;
      for ( const auto & xr : xtr )
        _xreal[i].insert( _xreal[i++].begin() + j, xr);

      i = 0;
      for ( const auto & xi : xti )
        _xint[i].insert( _xint[i++].begin() + j, xi);

      i = 0;
      for ( const auto & xb : xtb )
        _xbool[i].insert( _xbool[i++].begin() + j, xb);

      geometry<REAL,CELL>::insert(j,a,r);
    }

    virtual void add(const STRING &a, const vector3<REAL> & r){
      for (int i=0; i<_nxstring; i++)
        _xstring[i].push_back( "" );
      for (int i=0; i<_nxreal; i++)
        _xreal[i].push_back( REAL(0) );
      for (int i=0; i<_nxint; i++)
        _xint[i].push_back(0);
      for (int i=0; i<_nxbool; i++)
        _xbool[i].push_back( false );
      geometry<REAL,CELL>::add(a,r);
    }

    virtual void insert(const int j, STRING a, const vector3<REAL> &r){
      for (int i=0; i<_nxstring; i++)
        _xstring[i].insert(_xstring[i].begin()+j, "" );
      for (int i=0; i<_nxreal; i++)
        _xreal[i].insert(_xreal[i].begin()+j, REAL(0) );
      for (int i=0; i<_nxint; i++)
        _xint[i].insert(_xint[i].begin()+j, 0);
      for (int i=0; i<_nxbool; i++)
        _xbool[i].insert(_xbool[i].begin()+j, false);
      geometry<REAL,CELL>::insert(j,a,r);
    }

    virtual void clear(){
      geometry<REAL,CELL>::clear();
      for (int i=0; i<_nxstring; i++)
        _xstring[i].clear();
      for (int i=0; i<_nxreal; i++)
        _xreal[i].clear();
      for (int i=0; i<_nxint; i++)
        _xint[i].clear();
      for (int i=0; i<_nxbool; i++)
        _xbool[i].clear();
    }


    virtual void add(STRING a, REAL _x, REAL _y, REAL _z)
    {
      add(a, {_x,_y,_z});
    }
    /*
    virtual void insert(const int j, STRING a, const REAL _x, const REAL _y, const REAL _z)
    {
      insert(j,a, {_x,_y,_z});
    }
    */
    // ---------------------------------------------------------

    template<class T>
    void parse_field(int i, int j, T t){
      basic_types f = field_type(i);
      if (f==type_string)
        xfield<STRING>(i,j) = convert<STRING,T>::get(t);
      else if (f==type_real)
        xfield<REAL>(i,j) = convert<REAL,T>::get(t);
      else if (f==type_int)
        xfield<int>(i,j) = convert<int,T>::get(t);
      else if (f==type_bool)
        xfield<bool>(i,j) = convert<bool,T>::get(t);
    }

    // ----------------------------------------

    template<class T, typename... Args>
    void parse(int i, int j, T t){
      parse_field(i,j,t);
    }

    template<class T, typename... Args>
    void parse(int i, int j, T t, Args... args){
      parse_field(i,j,t);
      parse(i+1, j, args...);
    }

    // ----------------------------------------

    template<typename... Args>
    void xfill(int j, Args... args){
      parse(0,j,args...);
      if (auto_update_types)
        type(j) = define_type(_atm[j]);
    }

    template<typename... Args>
    void xadd(Args... args){
      add("",{REAL(0),REAL(0),REAL(0)});
      xfill(size()-1, args... );
    }

    template<typename... Args>
    void xinsert(int at, Args... args){
      insert(at,"",{REAL(0),REAL(0),REAL(0)});
      xfill(at, args... );
    }

    // ----------------------------------------

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const{
      for (int k=0; k<offset; k++) os << " ";
      os << "geometry";
      if (name != "")
        os << " " << name;
      os << "(";
      cell.write(os);

      for (int i=0; i<nfields(); i++){
          std::cout << ", " << field_name(i) << " = ";
          if (field_type(i)==type_string)
            std::cout << "string";
          else if (field_type(i)==type_real)
            std::cout << "real";
          else if (field_type(i)==type_int)
            std::cout << "int";
          else if (field_type(i)==type_bool)
            std::cout << "bool";
        }
      os << ")\n";

      for (int k=0; k<offset+2; k++) os << " ";
      os << "{\n";

      for (int i=0; i<size(); i++){
          for (int k=0; k<offset+3; k++) os << " ";
          for (int j=0; j<nfields(); j++)
            if (field_type(j)==type_string)
              os << " " << xfield<STRING>(j,i);
            else if (field_type(j)==type_real)
              os << " " << xfield<REAL>(j,i);
            else if (field_type(j)==type_int)
              os << " " << xfield<int>(j,i);
            else if (field_type(j)==type_bool)
              os << " " << t2s(xfield<bool>(j,i));
          os << "\n";
        }

      for (int k=0; k<offset+2; k++) os << " ";
      os << "}\n";
    }

    // Some named fields ----------------------------------------------

    bool has_charge(){ return ix_charge >= 0; }

    REAL charge(int i) const{
      if (i<0) i+=nat();
      if (i<0 || i>= nat()) IndexError("xgeometry::py_getitem: index out of range");

      if (ix_charge >= 0)
        return _xreal[_field_idx[ix_charge]][i];
      else
        throw std::runtime_error("\"charge\" field is requested for the geometry which does not have charges");
    }

    REAL & charge(int i){
      if (i<0) i+=nat();
      if (i<0 || i>= nat()) IndexError("xgeometry::py_getitem: index out of range");

      if (ix_charge >= 0)
        return _xreal[_field_idx[ix_charge]][i];
      else
        throw std::runtime_error("\"charge\" field is requested for the geometry which does not have charges");
    }

    //-----------------------------------------------------------

    bool has_number(){ return ix_number >= 0; }

    int number(int i) const{
      if (i<0) i+=nat();
      if (i<0 || i>= nat()) IndexError("xgeometry::py_getitem: index out of range");

      if (ix_number >= 0)
        return _xint[_field_idx[ix_number]][i];
      else
        throw std::runtime_error("\"number\" field is requested for the geometry which does not have numbers");
    }

    int & number(int i){
      if (i<0) i+=nat();
      if (i<0 || i>= nat()) IndexError("xgeometry::py_getitem: index out of range");

      if (ix_number >= 0)
        return _xint[_field_idx[ix_number]][i];
      else
        throw std::runtime_error("\"number\" field is requested for the geometry which does not have numbers");
    }

    //-----------------------------------------------------------

    bool has_mass()
    { return ix_mass >= 0; }

    REAL mass(int i) const{
      if (i<0) i+=nat();
      if (i<0 || i>= nat()) IndexError("xgeometry::py_getitem: index out of range");

      if (ix_mass >= 0)
        return _xreal[_field_idx[ix_mass]][i];
      else
        throw std::runtime_error("\"mass\" field is requested for the geometry which does not have masses");
    }

    REAL & mass(int i){
      if (i<0) i+=nat();
      if (i<0 || i>= nat()) IndexError("xgeometry::py_getitem: index out of range");

      if (ix_mass >= 0)
        return _xreal[_field_idx[ix_mass]][i];
      else
        throw std::runtime_error("\"mass\" field is requested for the geometry which does not have masses");
    }

#ifdef PY_EXPORT

    xgeometry(CELL & __cell, const py::list f, const STRING & __name = "") :
      geometry<REAL,CELL>(__cell, __name){
      init_xdefault();

      std::vector<STRING> fn;
      std::vector<basic_types> ft;

      for (int i=0; i<py::len(f); i++){
          if (!py::isinstance<py::tuple>(f[i]))
            TypeError("In xgeometry constructor - bad format list");

          py::tuple t = py::cast<py::tuple>(f[i]);

          if (py::len(t)!=2 || !py::isinstance<py::str>(t[0]) ||
             !py::isinstance<py::str>(t[1]))
            TypeError("In xgeometry constructor - bad format list");

          fn.push_back(py::cast<STRING>(t[0]));
          STRING s = py::cast<STRING>(t[1]);

          if (s=="string")
            ft.push_back(type_string);
          else if (s=="real")
            ft.push_back(type_real);
          else if (s=="int")
            ft.push_back(type_int);
          else if (s=="bool")
            ft.push_back(type_bool);
          else
            KeyError("In xgeometry constructor - bad field type");
        }
      set_format(fn,ft);
    }

    virtual py::list py_getitem(int j) const{
      if (j<0) j+=nat();
      if (j<0 || j>= nat()) IndexError("xgeometry::py_getitem: index out of range");
      py::list l;
      for (int i=0; i<nfields(); i++){
          if (field_type(i)==type_string)
            l.append(xfield<STRING>(i,j));
          else if (field_type(i)==type_real)
            l.append(xfield<REAL>(i,j));
          else if (field_type(i)==type_int)
            l.append(xfield<int>(i,j));
          else if (field_type(i)==type_bool)
            l.append(xfield<bool>(i,j));
        }
      return l;
    }

    virtual void py_setitem(int j, const py::list & l){
      if (j<0) j+=nat();
      if (j<0 || j>= nat()) IndexError("xgeometry:: index out of range");
      if (py::len(l) != nfields())
        TypeError("xgeometry:: bad list of fields");

      for (int i=0; i<nfields(); i++){
          if (field_type(i)==type_string){
              if (!py::isinstance<py::str>(l[i]))
                TypeError("xgeometry:: bad list of fields");
              xfield<STRING>(i,j) = py::cast<STRING>(l[i]);
            }
          else if (field_type(i)==type_real){
              if (!py::isinstance<py::float_>(l[i]))
                TypeError("xgeometry:: bad list of fields");
              xfield<REAL>(i,j) = py::cast<REAL>(l[i]);
            }
          else if (field_type(i)==type_int){
              if (!py::isinstance<py::int_>(l[i]))
                TypeError("xgeometry:: bad list of fields");
              xfield<int>(i,j) = py::cast<int>(l[i]);
            }
          else if (field_type(i)==type_bool){
              if (!py::isinstance<py::bool_>(l[i]))
                TypeError("xgeometry:: bad list of fields");
              xfield<bool>(i,j) = py::cast<bool>(l[i]);
            }
        }
    }

    py::object py_getfield1(int i){
      KeyError("xgeometry::field accepts 2 indicies");
    }

    void py_setfield1(int i, const py::object & o){
      KeyError("xgeometry::field accepts 2 indicies");
    }

    py::object py_getfield(int i, int j){
      if (i<0) i += nfields();
      if (i<0 || i >= nfields())
        IndexError("xgeometry: field index out of range");

      if (j<0) j+= nat();
      if (j<0 || j>=nat())
        IndexError("xgeometry: atom index out of range");

      if (field_type(i)==type_string)
        return py::cast(xfield<STRING>(i,j));
      else if (field_type(i)==type_real)
        return py::cast(xfield<REAL>(i,j));
      else if (field_type(i)==type_int)
        return py::cast(xfield<int>(i,j));
      else if (field_type(i)==type_bool)
        return py::cast(xfield<bool>(i,j));

    }

    void py_setfield(int i, int j, const py::object & o){
      if (i<0) i += nfields();
      if (i<0 || i >= nfields())
        IndexError("xgeometry: field index out of range");

      if (j<0) j+= nat();
      if (j<0 || j>=nat())
        IndexError("xgeometry: atom index out of range");

      basic_types t = field_type(i);
      if (t==type_string){
          if ( !py::isinstance<py::str>(o))
            TypeError("xgeometry: string value of the field expected");
          xfield<STRING>(i,j) = py::cast<STRING>(o);
        }
      else if (t==type_real){
          if ( !py::isinstance<py::float_>(o))
            TypeError("xgeometry: real value of the field expected");
          xfield<REAL>(i,j) = py::cast<REAL>(o);
        }
      else if (t==type_int){
          if ( !py::isinstance<py::int_>(o))
            TypeError("xgeometry: int value of the field expected");
          xfield<int>(i,j) = py::cast<int>(o);
        }
      else if (t==type_bool){
          if ( !py::isinstance<py::bool_>(o))
            TypeError("xgeometry: bool value of the field expected");
          xfield<bool>(i,j) = py::cast<bool>(o);
        }
    }

    py_2indexed_property<SELF, py::object, py::object, int, &SELF::py_getfield1,
    &SELF::py_setfield1, &SELF::py_getfield, &SELF::py_setfield > py_fields;

    bool py_getadd(int i){
      if (i<0) i += nfields();
      if (i<0 || i >= nfields())
        IndexError("xgeometry: field index out of range");
      return additive(i);
    }

    void py_setadd(int i, const bool &a){
      if (i<0) i += nfields();
      if (i<0 || i >= nfields())
        IndexError("xgeometry: field index out of range");
      additive(i) = a;
    }

    py_indexed_property<SELF, bool, int, &SELF::py_getadd,
    &SELF::py_setadd > py_add;

    virtual void py_add_list(const py::list & l){
      geometry<REAL,CELL>::add("",0,0,0);
      py_setitem(nat()-1,l);
    }

    static void py_export(py::module m, const char * pyname){

      std::string sPropNameField =
           fmt::format("{0}_{1}",pyname,"idx_prop_xfield");
      py_2indexed_property<SELF, py::object, py::object, int, &SELF::py_getfield1,
          &SELF::py_setfield1, &SELF::py_getfield,
          &SELF::py_setfield >::py_2export(m, sPropNameField.c_str());

      std::string sPropNameAdd =
           fmt::format("{0}_{1}",pyname,"idx_prop_xadd");
      py_indexed_property<SELF, bool, int, &SELF::py_getadd,
          &SELF::py_setadd >::py_export(m, sPropNameAdd.c_str());

      py::class_<xgeometry<REAL,CELL>, geometry<REAL,CELL> >
          (m, pyname)
//          .def(py::init<int,   const STRING&>(),
//               py::arg("dim"), py::arg("__name") = "")
          .def(py::init<CELL&, const py::list &, const STRING&>(),
               py::arg("CELL"), py::arg("f"), py::arg("__name") = "")
          .def_readwrite("field", & SELF::py_fields)
          .def_readwrite("additive", & SELF::py_add)
          .def("nfields", & SELF::nfields)
          .def("field_name", & SELF::field_name);
    }

#endif

  };

}

#endif
