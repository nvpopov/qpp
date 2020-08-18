#ifndef QPP_GEOM_EXTRAS_H
#define QPP_GEOM_EXTRAS_H

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

#include <data/types.hpp>
#include <data/errors.hpp>
#include <data/data.hpp>
#include <geom/geom.hpp>
#include <io/strfun.hpp>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>

namespace qpp {

template<class REAL, class CELL>
///
/// \brief  Geometry with extra fields - for storing any additional data
///
class xgeometry : public geometry<REAL,CELL> {

private:

  std::vector<std::vector<REAL>>   p_xreal;
  std::vector<std::vector<int>>    p_xint;
  std::vector<std::vector<short>>  p_xbool;
  std::vector<std::vector<STRING_EX>> p_xstring;

  std::vector<STRING_EX>    p_field_name;
  std::vector<basic_types>  p_field_type;

  std::vector<int>          p_field_idx;
  std::vector<Bool>         p_field_additive;

  int p_nxreal, p_nxint, p_nxbool, p_nxstring, p_nfields;
  int p_ix_charge, p_ix_x, p_ix_y, p_ix_z, p_ix_atom, p_ix_mass, p_ix_number;

  using geometry<REAL, CELL>::p_atm;
  using geometry<REAL, CELL>::p_crd;
  using geometry<REAL, CELL>::p_shadow;
  using geometry<REAL, CELL>::p_sel;
  using geometry<REAL, CELL>::reorder_types;
  using geometry<REAL, CELL>::size;
  using geometry<REAL, CELL>::p_has_observers;
  using geometry<REAL, CELL>::p_observers;
  using geometry<REAL, CELL>::p_cached_obs_flags;
  using geometry<REAL, CELL>::get_geom_data_access_mode;
  using geometry<REAL, CELL>::set_geom_data_access_mode;

  //using geometry<DIM,REAL,CELL>::error;

  void init_xdefault() {

    p_nxreal = p_nxstring = p_nxint = p_nxbool = 0;
#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
    py_fields.bind(this);
    py_add.bind(this);
#endif

  }

public:

  typedef xgeometry<REAL,CELL> SELF;

  using geometry<REAL, CELL>::get_DIM;
  using geometry<REAL, CELL>::set_DIM;
  using geometry<REAL, CELL>::name;
  using geometry<REAL, CELL>::cell;
  using geometry<REAL, CELL>::nat;
  using geometry<REAL, CELL>::type;
  using geometry<REAL, CELL>::define_type;
  using geometry<REAL, CELL>::auto_update_types;
  using geometry<REAL, CELL>::add_observer;
  using geometry<REAL, CELL>::remove_observer;
  using geometry<REAL, CELL>::select;
  using geometry<REAL, CELL>::selected;
  using geometry<REAL, CELL>::iselect;
  using geometry<REAL, CELL>::iselected;
  using geometry<REAL, CELL>::toggle_selected;
  using geometry<REAL, CELL>::toggle_iselected;
  using geometry<REAL, CELL>::no_aselected;
  using geometry<REAL, CELL>::num_selected;
  using geometry<REAL, CELL>::num_aselected;
  using geometry<REAL, CELL>::num_iselected;

  virtual bool is_xgeometry() const{return true;}

  inline int nfields() const{ return p_nfields; }

  inline STRING_EX field_name(int i) const{ return p_field_name[i]; }

  inline basic_types field_type(int i) const{ return p_field_type[i]; }

  /// Constructors

  ///
  /// \brief xgeometry
  /// \param __cell
  /// \param __nxstring
  /// \param __nxreal
  /// \param __nxint
  /// \param __nxbool
  /// \param __name
  ///
  xgeometry(CELL & __cell, int __nxstring, int __nxreal=0, int __nxint=0, int __nxbool=0,
            const STRING_EX & __name = "") :
            p_xstring(__nxstring), p_xreal(__nxreal), p_xint(__nxint), p_xbool(__nxbool),
            p_field_name(__nxreal + __nxint + __nxbool + __nxstring),
            p_field_type(__nxreal + __nxint + __nxbool + __nxstring),
            p_field_idx(__nxreal + __nxint + __nxbool + __nxstring),
            p_field_additive(__nxreal + __nxint + __nxbool + __nxstring),
            geometry<REAL,CELL>(__cell, __name) {

    init_xdefault();
    p_nxreal   = __nxreal;
    p_nxint    = __nxint;
    p_nxbool   = __nxbool;
    p_nxstring = __nxstring;

  }

  ///
  /// \brief xgeometry
  /// \param __cell
  /// \param __name
  ///
  xgeometry(CELL & __cell,  const STRING_EX & __name = "") : geometry<REAL,CELL>(__cell, __name) {
    init_xdefault();
  }

  ///
  /// \brief xgeometry
  /// \param dim
  /// \param __name
  ///
  xgeometry(int dim,  const STRING_EX & __name = "") : geometry<REAL,CELL>(dim, __name) {
    init_xdefault();
  }

  ///
  /// \brief get_format
  /// \param fn
  /// \param ft
  ///
  void get_format(std::vector<STRING_EX> & fn, std::vector<basic_types> & ft){
    fn = p_field_name;
    ft = p_field_type;
  }

  ///
  /// \brief set_format
  /// \param fn
  /// \param ft
  ///
  void set_format(const std::vector<STRING_EX> & fn, const std::vector<basic_types> & ft) {

    p_field_name = fn;
    p_field_type = ft;
    p_nxstring = std::count(ft.begin(), ft.end(), basic_types::type_string);
    p_nxreal = std::count(ft.begin(), ft.end(), basic_types::type_real);
    p_nxint = std::count(ft.begin(), ft.end(), basic_types::type_int);
    p_nxbool = std::count(ft.begin(), ft.end(), basic_types::type_bool);

    if (fn.size() != ft.size() || fn.size() != p_nxstring + p_nxreal + p_nxint + p_nxbool) {
      throw std::invalid_argument("xgeometry::format: field names or types mismatch");
    }

    p_nfields = ft.size();
    p_field_idx.resize(p_nfields);

    int is = 0, ib = 0, ir = 0, ii = 0;

    p_ix_x = p_ix_y = p_ix_z = p_ix_atom = -1;
    p_ix_charge = p_ix_mass = p_ix_number = -1;

    for (int j = 0; j < p_nfields; j++) {

      basic_types tp = field_type(j);

      if ( tp == basic_types::type_string ) {
        p_field_idx[j] = is++;
        if ( field_name(j) == "atom" ) p_ix_atom = j;
      } else if ( tp == basic_types::type_real || tp == attributes<REAL>::type ){
        p_field_type[j] = basic_types::type_real;
        p_field_idx[j] = ir++;
        if ( field_name(j) == "x" )      p_ix_x = j;
        else if ( field_name(j) == "y" ) p_ix_y = j;
        else if ( field_name(j) == "z" ) p_ix_z = j;
        else if ( field_name(j) == "charge" ) p_ix_charge = j;
        else if ( field_name(j) == "mass" )   p_ix_mass   = j;
      } else if ( tp == basic_types::type_int ){
        p_field_idx[j] = ii++;
        if ( field_name(j) == "number" ) p_ix_number = j;
      } else if ( tp == basic_types::type_bool ) {
        p_field_type[j] = basic_types::type_bool;
        p_field_idx[j] = ib++;
      } else {
        throw std::invalid_argument("xgeometry::format: invalid type");
      }

    }

    /*
      for (int i=0; i<_nfields; i++)
        std::cout << field_name(i) << " " << field_type(i) << " " << _field_idx[i] << "\n";
      std::cout << ix_atom << " " << ix_x << " " << ix_y << " " << ix_z << "\n";
      */

    if (p_ix_atom == -1 && p_ix_x == -1 && p_ix_y==-1 && p_ix_z==-1) {

      p_ix_atom = 0;
      p_ix_x = 1; p_ix_y = 2; p_ix_z = 3;
      if (p_ix_charge >= 0) p_ix_charge += 4;
      if (p_ix_mass >= 0)   p_ix_mass   += 4;
      if (p_ix_number >= 0) p_ix_number += 4;

      p_nfields  += 4;
      p_nxstring += 1;
      p_nxreal   += 3;

      std::vector<STRING_EX> inss = {"atom","x","y","z"};
      p_field_name.insert(p_field_name.begin(), inss.begin(), inss.end());

      std::vector<basic_types> inst = {
          basic_types::type_string,
          basic_types::type_real,
          basic_types::type_real,
          basic_types::type_real
      };
      p_field_type.insert(p_field_type.begin(), inst.begin(), inst.end());

      std::vector<int> insi = {0,0,1,2};
      p_field_idx.insert(p_field_idx.begin(), insi.begin(), insi.end());

      /*
          for (int j=4; j<_nfields; j++)
            if (field_type(j)==type_string)
              _field_idx[j] += 1;
            else if (field_type(j)==type_real)
              _field_idx[j] += 3;
          */

    }

    p_field_additive.resize(p_nfields);

    for (int i=0; i<p_nfields; i++) p_field_additive[i] = false;

    if (p_ix_charge>=0)
      p_field_additive[p_ix_charge] = true;

    if (p_ix_atom == -1 || p_ix_x == -1 || p_ix_y == -1 || p_ix_z == -1) {
      throw std::invalid_argument("xgeometry::format: the geometry does not have either atom names,"
                                  " x, y, or z coordinates");
    }

    p_xstring.resize(p_nxstring);
    p_xreal.resize(p_nxreal);
    p_xint.resize(p_nxint);
    p_xbool.resize(p_nxbool);

  }

  ///
  /// \brief xgeometry
  /// \param __cell
  /// \param fn
  /// \param ft
  /// \param __name
  ///
  xgeometry(CELL & __cell,  const std::vector<STRING_EX> & fn,
            const std::vector<basic_types> & ft,
            const STRING_EX & __name = "") : geometry<REAL,CELL>(__cell, __name) {

    init_xdefault();
    set_format(fn,ft);

  }

  int nfields_string() const{ return p_nxstring; }

  int nfields_real() const{ return p_nxreal; }

  int nfields_int() const{ return p_nxint;}

  int nfields_bool() const{ return p_nxbool;}

  bool additive(int i) const{ return p_field_additive[i]; }

  bool & additive(int i){ return p_field_additive[i]; }

  template<class T>
  T & xfield(int i, int j) {

    assert(get_geom_data_access_mode() == geom_data_access_mode::allow_direct_access);

    basic_types ft = field_type(i);

    if (ft == basic_types::type_real) ft = attributes<REAL>::type;

    if (attributes<T>::type != ft)
      throw std::invalid_argument("xgeometry::xfield - wrong type for the field " + t2s(i));

    if (attributes<T>::type == basic_types::type_string) {

      if (i==p_ix_atom) return convert<T&,STRING_EX&>::get(p_atm[j]);
      else return convert<T&,STRING_EX&>::get(p_xstring[p_field_idx[i]][j]);

    } else if (attributes<T>::type == basic_types::type_bool) {

      //if (i==p_ix_sel) return convert<T&,short&>::get(selected(j));
      return  convert<T&,short&>::get(p_xbool[p_field_idx[i]][j]);

    } else if (attributes<T>::type == basic_types::type_int) {

      return convert<T&,int&>::get(p_xint[p_field_idx[i]][j]);

    } else if (attributes<T>::type == attributes<REAL>::type) {

      if (i==p_ix_x) return convert<T&,REAL&>::get(p_crd[j].x());
      else if (i==p_ix_y) return convert<T&,REAL&>::get(p_crd[j].y());
      else if (i==p_ix_z) return convert<T&,REAL&>::get(p_crd[j].z());
      else return convert<T&,REAL&>::get(p_xreal[p_field_idx[i]][j]);

    } else {

      throw std::invalid_argument("Illegal type of xgeometry extra field");

    }

  }

  template<class T>
  inline T xfield(int i, int j) const {

    basic_types ft = field_type(i);

    if (ft == basic_types::type_real) ft = attributes<REAL>::type;

    if (attributes<T>::type != ft)
      throw std::invalid_argument("xgeometry::xfield - wrong type for the field " + t2s(i));

    if (attributes<T>::type == basic_types::type_string) {

      if (i==p_ix_atom) return convert<T,STRING_EX>::get(p_atm[j]);
      else return  convert<T,STRING_EX>::get(p_xstring[p_field_idx[i]][j]);

    } else if (attributes<T>::type == basic_types::type_bool) {

      return  convert<T,short>::get(p_xbool[p_field_idx[i]][j]);

    } else if (attributes<T>::type == basic_types::type_int) {

      return convert<T,int>::get(p_xint[p_field_idx[i]][j]);

    } else if (attributes<T>::type == attributes<REAL>::type) {

      if (i==p_ix_x)
        return convert<T,REAL>::get(p_crd[j].x());
      else if (i==p_ix_y)
        return convert<T,REAL>::get(p_crd[j].y());
      else if (i==p_ix_z)
        return convert<T,REAL>::get(p_crd[j].z());
      else
        return convert<T,REAL>::get(p_xreal[p_field_idx[i]][j]);

    } else {

      throw std::invalid_argument("Illegal type of xgeometry extra field");

    }

  }

  template<class T>
  inline T & xfield(const STRING_EX & f, int j) {

    assert(get_geom_data_access_mode() == geom_data_access_mode::allow_direct_access);

    int i = 0;
    while (p_field_name[i]!=f && i<nfields()) i++;

    if (i<nfields()) {
      return xfield<T>(i,j);
    } else {
      throw std::invalid_argument("Field not found in xgeometry");
    }

  }

  template<class T>
  T xfield(const STRING_EX & f, int j) const {

    int i = 0;
    while (p_field_name[i]!=f && i<nfields()) i++;

    if (i<nfields()) {
      return xfield<T>(i,j);
    } else {
      throw std::invalid_argument("Field not found in xgeometry");
    }

  }

  template<class T>
  void set_xfield(int i, int j, T value, bool notify_observer = true) {

    if (notify_observer && p_has_observers)
      for (int q = 0; q < p_observers.size(); q++)
        if (p_cached_obs_flags[q] & geometry_observer_supports_xfield_change)
          p_observers[q]->xfield_changed(i, j, before_after::before);

    xfield<T>(i, j) = value;

    if (notify_observer && p_has_observers)
      for (int q = 0; q < p_observers.size(); q++)
        if (p_cached_obs_flags[q] & geometry_observer_supports_xfield_change)
          p_observers[q]->xfield_changed(i, j, before_after::after);

  }

  template<class T>
  T get_xfield(int i, int j) const {
    return xfield<T>(i, j);
  }

  // ----------------------------------------------------

  virtual void get_fields(int j, std::vector<datum> & v) const {

    if (j < 0) j += nat();
    if (j < 0 || j >= nat())
      throw std::invalid_argument("xgeometry::py_getitem: index out of range");

    v.resize(nfields());
    for (int i=0; i<nfields(); i++){
      if (field_type(i) == basic_types::type_string) v[i] = xfield<STRING_EX>(i,j);
      else if (field_type(i) == basic_types::type_real) v[i] = xfield<REAL>(i,j);
      else if (field_type(i) == basic_types::type_int) v[i] = xfield<int>(i,j);
      else if (field_type(i) == basic_types::type_bool) v[i] = xfield<bool>(i,j);
    }

  }

  virtual void set_fields(int j, const std::vector<datum> & v) {

    if (j < 0) j += nat();

    if (j < 0 || j >= nat())
      throw std::invalid_argument("xgeometry::set_fields: index out of range");

    if (v.size()!=nfields())
      throw std::invalid_argument("xgeometry::set_fields: wrong number of fields");

    STRING_EX a1 = v[p_ix_atom].template get<STRING_EX>();
    vector3<REAL> r1(v[p_ix_x].template get<REAL>(),
                     v[p_ix_y].template get<REAL>(),
                     v[p_ix_z].template get<REAL>());

    if (p_has_observers)
      for (int i=0; i<p_observers.size(); i++)
        p_observers[i]->changed(j, before_after::before, a1, r1);

    for (int i=0; i<nfields(); i++){
      if (field_type(i)==basic_types::type_string) xfield<STRING_EX>(i,j)=v[i].get<STRING_EX>();
      else if (field_type(i)==basic_types::type_real) xfield<REAL>(i,j)=v[i].get<REAL>();
      else if (field_type(i)==basic_types::type_int)  xfield<int>(i,j)=v[i].get<int>();
      else if (field_type(i)==basic_types::type_bool) xfield<bool>(i,j)=v[i].get<bool>();
    }

    if (p_has_observers)
      for (int i=0; i<p_observers.size(); i++)
        p_observers[i]->changed(j, before_after::after, a1, r1);

  }

  // ----------------------------------------------------

  virtual void erase(int j) {

    geometry<REAL,CELL>::erase(j);

    for (int i=0; i<p_nxreal; i++) p_xreal[i].erase(p_xreal[i].begin()+j);
    for (int i=0; i<p_nxint; i++) p_xint[i].erase(p_xint[i].begin()+j);
    for (int i=0; i<p_nxbool; i++) p_xbool[i].erase(p_xbool[i].begin()+j);

  }

  void add(const STRING_EX & a, const vector3<REAL> & r,
           std::initializer_list<STRING_EX> xts,
           std::initializer_list<REAL> xtr = {},
           std::initializer_list<int> xti = {},
           std::initializer_list<bool> xtb = {}) {

    int i = 0;
    for (const auto & xs : xts) p_xstring[i++].push_back(xs);

    i = 0;
    for (const auto & xr : xtr) p_xreal[i++].push_back(xr);

    i = 0;
    for (const auto & xi : xti) p_xint[i++].push_back(xi);

    i = 0;
    for (const auto & xb : xtb) p_xbool[i++].push_back(xb);

    geometry<REAL,CELL>::add(a,r);

  }

  void insert(const int j, const STRING_EX & a, const vector3<REAL> &r,
              std::initializer_list<STRING_EX> xts,
              std::initializer_list<REAL> xtr = {},
              std::initializer_list<int> xti = {},
              std::initializer_list<bool> xtb = {}) {

    int i = 0;
    for ( const auto & xs : xts ) p_xstring[i].insert( p_xstring[i++].begin() + j, xs);

    i = 0;
    for ( const auto & xr : xtr ) p_xreal[i].insert( p_xreal[i++].begin() + j, xr);

    i = 0;
    for ( const auto & xi : xti ) p_xint[i].insert( p_xint[i++].begin() + j, xi);

    i = 0;
    for ( const auto & xb : xtb ) p_xbool[i].insert( p_xbool[i++].begin() + j, xb);

    geometry<REAL,CELL>::insert(j,a,r);

  }

  virtual void add(const STRING_EX &a, const vector3<REAL> & r) {

    for (int i=0; i<p_nxstring; i++) p_xstring[i].push_back("");
    for (int i=0; i<p_nxreal; i++) p_xreal[i].push_back(REAL(0));
    for (int i=0; i<p_nxint; i++) p_xint[i].push_back(0);
    for (int i=0; i<p_nxbool; i++) p_xbool[i].push_back( false );

    geometry<REAL,CELL>::add(a, r);

  }

  virtual void insert(const int j, STRING_EX a, const vector3<REAL> &r) {

    for (int i=0; i<p_nxstring; i++) p_xstring[i].insert(p_xstring[i].begin()+j, "" );
    for (int i=0; i<p_nxreal; i++) p_xreal[i].insert(p_xreal[i].begin()+j, REAL(0) );
    for (int i=0; i<p_nxint; i++) p_xint[i].insert(p_xint[i].begin()+j, 0);
    for (int i=0; i<p_nxbool; i++) p_xbool[i].insert(p_xbool[i].begin()+j, false);

    geometry<REAL,CELL>::insert(j,a,r);

  }

  virtual void clear() {

    geometry<REAL,CELL>::clear();

    for (int i=0; i<p_nxstring; i++) p_xstring[i].clear();
    for (int i=0; i<p_nxreal; i++) p_xreal[i].clear();
    for (int i=0; i<p_nxint; i++) p_xint[i].clear();
    for (int i=0; i<p_nxbool; i++) p_xbool[i].clear();

  }

  virtual void add(STRING_EX a, REAL _x, REAL _y, REAL _z) {
    add(a, {_x,_y,_z});
  }

  virtual void reorder (const std::vector<int> & ord) {

    for (int i=0; i<p_observers.size(); i++)
      p_observers[i]->reordered(ord, before_after::before);
    // fixme - might be inefficient for large molecules

    std::vector<STRING_EX> __atm(p_atm);
    std::vector<vector3<REAL> > __crd(p_crd);
    std::vector<Bool> __shadow(p_shadow);

    for (int i=0; i<size(); i++){
      p_atm[i] = __atm[ord[i]];
      p_crd[i] = __crd[ord[i]];
      p_shadow[i] = __shadow[ord[i]];
    }

    reorder_types(ord);

    for (int i=0; i<p_nxstring; i++){
      std::vector<STRING_EX> __xstring(p_xstring[i]);
      for (int j=0; j<size(); j++) p_xstring[i][j] = __xstring[ord[j]];
    }

    for (int i=0; i<p_nxreal; i++){
      std::vector<REAL> __xreal(p_xreal[i]);
      for (int j=0; j<size(); j++) p_xreal[i][j] = __xreal[ord[j]];
    }

    for (int i=0; i<p_nxint; i++){
      std::vector<int> __xint(p_xint[i]);
      for (int j=0; j<size(); j++)  p_xint[i][j] = __xint[ord[j]];
    }

    for (int i=0; i<p_nxbool; i++){
      std::vector<short> __xbool(p_xbool[i]);
      for (int j=0; j<size(); j++) p_xbool[i][j] = __xbool[ord[j]];
    }

    for (int i=0; i<p_observers.size(); i++)
      p_observers[i]->reordered(ord, before_after::after);

  }


  /*
    virtual void insert(const int j, STRING_EX a, const REAL _x, const REAL _y, const REAL _z)
    {
      insert(j,a, {_x,_y,_z});
    }
    */
  // ---------------------------------------------------------

  void clone(xgeometry<REAL,CELL> &dst, const bool copy_data = true) {

    dst.clear();

    dst.p_DIM = get_DIM();

    //copy cell vectors
    for (size_t i = 0; i < get_DIM(); i++) dst.cell.v[i] = cell.v[i];

    //copy xgeom headers
    dst.set_format(p_field_name, p_field_type);

    //copy data
    if (copy_data) {
      for (size_t i = 0; i < nat(); i++) {
        dst.add("", vector3<float>{0});
        std::vector<datum> v;
        get_fields(i, v);
        dst.set_fields(i,v);
      }

      dst.build_types();
    }

  }

  template<class T>
  void parse_field(int i, int j, T t) {

    basic_types f = field_type(i);
    if (f == basic_types::type_string) xfield<STRING_EX>(i,j) = convert<STRING_EX,T>::get(t);
    else if (f == basic_types::type_real) xfield<REAL>(i,j) = convert<REAL,T>::get(t);
    else if (f == basic_types::type_int) xfield<int>(i,j) = convert<int,T>::get(t);
    else if (f == basic_types::type_bool) xfield<bool>(i,j) = convert<bool,T>::get(t);

  }

  // ----------------------------------------

  template<class T, typename... Args>
  void parse(int i, int j, T t) {
    parse_field(i,j,t);
  }

  template<class T, typename... Args>
  void parse(int i, int j, T t, Args... args) {
    parse_field(i,j,t);
    parse(i+1, j, args...);
  }

  // ----------------------------------------

  template<typename... Args>
  void xfill(int j, Args... args) {

    parse(0,j,args...);
    if (auto_update_types)
      type(j) = define_type(p_atm[j]);

  }

  template<typename... Args>
  void xadd(Args... args) {

    add("",{REAL(0),REAL(0),REAL(0)});
    xfill(size()-1, args... );

  }

  template<typename... Args>
  void xinsert(int at, Args... args) {

    insert(at,"",{REAL(0),REAL(0),REAL(0)});
    xfill(at, args... );

  }

  // ----------------------------------------

  virtual void write(std::basic_ostream<CHAR_EX,TRAITS> &os, int offset=0) const {

    for (int k=0; k<offset; k++) os << " ";
    os << "geometry";
    if (name != "")
      os << " " << name;
    os << "(";
    cell.write(os);

    for (int i=0; i<nfields(); i++){
      std::cout << ", " << field_name(i) << " = ";
      if (field_type(i) == basic_types::type_string) std::cout << "string";
      else if (field_type(i) == basic_types::type_real) std::cout << "real";
      else if (field_type(i) == basic_types::type_int) std::cout << "int";
      else if (field_type(i) == basic_types::type_bool) std::cout << "bool";
    }
    os << ")\n";

    for (int k=0; k<offset+2; k++) os << " ";
    os << "{\n";

    for (int i=0; i<size(); i++){
      for (int k=0; k<offset+3; k++) os << " ";
      for (int j=0; j<nfields(); j++)
        if (field_type(j) == basic_types::type_string) os << " " << xfield<STRING_EX>(j,i);
        else if (field_type(j) == basic_types::type_real) os << " " << xfield<REAL>(j,i);
        else if (field_type(j) == basic_types::type_int) os << " " << xfield<int>(j,i);
        else if (field_type(j) == basic_types::type_bool) os << " " << t2s(xfield<bool>(j,i));
      os << "\n";
    }

    for (int k=0; k<offset+2; k++) os << " ";
    os << "}\n";

  }

  // Some named fields ----------------------------------------------

  bool has_charge(){ return p_ix_charge >= 0; }

  REAL charge(int i) const {

    if (i < 0) i += nat();
    if (i < 0 || i >= nat())
      throw std::invalid_argument("xgeometry::py_getitem: index out of range");

    if (p_ix_charge >= 0)
      return p_xreal[p_field_idx[p_ix_charge]][i];
    else
      throw std::runtime_error("\"charge\" field is requested for the geometry which"
                               " does not have charges");

  }

  REAL & charge(int i) {

    if (i < 0) i+=nat();
    if (i < 0 || i>= nat())
      throw std::invalid_argument("xgeometry::py_getitem: index out of range");

    if (p_ix_charge >= 0)
      return p_xreal[p_field_idx[p_ix_charge]][i];
    else
      throw std::runtime_error("\"charge\" field is requested for the geometry "
                               "which does not have charges");

  }

  //-----------------------------------------------------------

  bool has_number(){ return p_ix_number >= 0; }

  int number(int i) const {

    if (i < 0) i += nat();
    if (i < 0 || i >= nat())
      throw std::invalid_argument("xgeometry::py_getitem: index out of range");

    if (p_ix_number >= 0)
      return p_xint[p_field_idx[p_ix_number]][i];
    else
      throw std::runtime_error("\"number\" field is requested for the geometry "
                               "which does not have numbers");

  }

  int & number(int i) {

    if (i < 0) i += nat();
    if (i < 0 || i >= nat())
      throw std::invalid_argument("xgeometry::py_getitem: index out of range");

    if (p_ix_number >= 0)
      return p_xint[p_field_idx[p_ix_number]][i];
    else
      throw std::runtime_error("\"number\" field is requested for the geometry "
                               "which does not have numbers");

  }

  //-----------------------------------------------------------

  bool has_mass()
  { return p_ix_mass >= 0; }

  REAL mass(int i) const {

    if (i < 0) i+=nat();
    if (i < 0 || i>= nat())
      throw std::invalid_argument("xgeometry::py_getitem: index out of range");

    if (p_ix_mass >= 0)
      return p_xreal[p_field_idx[p_ix_mass]][i];
    else
      throw std::runtime_error("\"mass\" field is requested for the geometry"
                               " which does not have masses");

  }

  REAL & mass(int i) {

    if (i < 0) i+=nat();
    if (i < 0 || i>= nat())
      throw std::invalid_argument("xgeometry::py_getitem: index out of range");

    if (p_ix_mass >= 0)
      return p_xreal[p_field_idx[p_ix_mass]][i];
    else
      throw std::runtime_error("\"mass\" field is requested for the geometry"
                               " which does not have masses");

  }

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

  xgeometry(CELL & __cell, const py::list f, const STRING_EX & __name = "") :
                                                                            geometry<REAL,CELL>(__cell, __name) {

    init_xdefault();

    std::vector<STRING_EX> fn;
    std::vector<basic_types> ft;

    for (int i=0; i<py::len(f); i++) {
      if (!py::isinstance<py::tuple>(f[i]))
        throw std::invalid_argument("In xgeometry constructor - bad format list");

      py::tuple t = py::cast<py::tuple>(f[i]);

      if (py::len(t)!=2 || !py::isinstance<py::str>(t[0]) ||
          !py::isinstance<py::str>(t[1]))
        throw std::invalid_argument("In xgeometry constructor - bad format list");

      fn.push_back(py::cast<STRING_EX>(t[0]));
      STRING_EX s = py::cast<STRING_EX>(t[1]);

      if (s == "string") ft.push_back(basic_types::type_string);
      else if (s == "real") ft.push_back(basic_types::type_real);
      else if (s == "int") ft.push_back(basic_types::type_int);
      else if (s == "bool") ft.push_back(basic_types::type_bool);
      else throw std::invalid_argument("In xgeometry constructor - bad field type");
    }

    set_format(fn,ft);

  }

  virtual py::list py_getitem(int j) const {

    if (j<0) j+=nat();
    if (j<0 || j>= nat())
      throw std::invalid_argument("xgeometry::py_getitem: index out of range");
    py::list l;

    for (int i=0; i<nfields(); i++){
      if (field_type(i) == basic_types::type_string) l.append(xfield<STRING_EX>(i,j));
      else if (field_type(i) == basic_types::type_real) l.append(xfield<REAL>(i,j));
      else if (field_type(i) == basic_types::type_int) l.append(xfield<int>(i,j));
      else if (field_type(i) == basic_types::type_bool) l.append(xfield<bool>(i,j));
    }

    return l;

  }

  virtual void py_setitem(int j, const py::list & l) {

    if (j<0) j+=nat();
    if (j<0 || j>= nat()) throw std::invalid_argument("xgeometry:: index out of range");
    if (py::len(l) != nfields())
      throw std::invalid_argument("xgeometry:: bad list of fields");

    for (int i=0; i<nfields(); i++){

      if (field_type(i) == basic_types::type_string) {

        if (!py::isinstance<py::str>(l[i]))
          throw std::invalid_argument("xgeometry:: bad list of fields");
        xfield<STRING_EX>(i,j) = py::cast<STRING_EX>(l[i]);

      } else if (field_type(i) == basic_types::type_real) {

        if (!py::isinstance<py::float_>(l[i]))
          throw std::invalid_argument("xgeometry:: bad list of fields");
        xfield<REAL>(i,j) = py::cast<REAL>(l[i]);

      } else if (field_type(i) == basic_types::type_int) {

        if (!py::isinstance<py::int_>(l[i]))
          throw std::invalid_argument("xgeometry:: bad list of fields");
        xfield<int>(i,j) = py::cast<int>(l[i]);

      } else if (field_type(i) == basic_types::type_bool) {

        if (!py::isinstance<py::bool_>(l[i]))
          throw std::invalid_argument("xgeometry:: bad list of fields");
        xfield<bool>(i,j) = py::cast<bool>(l[i]);

      }

    }

  }

  py::object py_getfield1(int i) {
    throw std::invalid_argument("xgeometry::field accepts 2 indicies");
    return py::none();
  }

  void py_setfield1(int i, const py::object & o) {
    throw std::invalid_argument("xgeometry::field accepts 2 indicies");
  }

  py::object py_getfield(int i, int j) {

    if (i<0) i += nfields();
    if (i<0 || i >= nfields())
      throw std::invalid_argument("xgeometry: field index out of range");

    if (j<0) j+= nat();
    if (j<0 || j>=nat())
      throw std::invalid_argument("xgeometry: atom index out of range");

    if (field_type(i) == basic_types::type_string) return py::cast(xfield<STRING_EX>(i,j));
    else if (field_type(i) == basic_types::type_real) return py::cast(xfield<REAL>(i,j));
    else if (field_type(i) == basic_types::type_int) return py::cast(xfield<int>(i,j));
    else if (field_type(i) == basic_types::type_bool) return py::cast(xfield<bool>(i,j));

    return py::none();

  }

  void py_setfield(int i, int j, const py::object & o) {

    if (i<0) i += nfields();
    if (i<0 || i >= nfields())
      throw std::invalid_argument("xgeometry: field index out of range");

    if (j<0) j+= nat();
    if (j<0 || j>=nat())
      throw std::invalid_argument("xgeometry: atom index out of range");

    basic_types t = field_type(i);
    if (t == basic_types::type_string) {

      if (!py::isinstance<py::str>(o))
        throw std::invalid_argument("xgeometry: string value of the field expected");
      xfield<STRING_EX>(i,j) = py::cast<STRING_EX>(o);

    } else if (t == basic_types::type_real) {

      if ( !py::isinstance<py::float_>(o))
        throw std::invalid_argument("xgeometry: real value of the field expected");
      xfield<REAL>(i,j) = py::cast<REAL>(o);

    } else if (t == basic_types::type_int) {

      if ( !py::isinstance<py::int_>(o))
        throw std::invalid_argument("xgeometry: int value of the field expected");
      xfield<int>(i,j) = py::cast<int>(o);

    } else if (t == basic_types::type_bool) {

      if ( !py::isinstance<py::bool_>(o))
        throw std::invalid_argument("xgeometry: bool value of the field expected");
      xfield<bool>(i,j) = py::cast<bool>(o);

    }

  }

  py_2indexed_property<SELF, py::object, py::object, int, &SELF::py_getfield1,
                       &SELF::py_setfield1, &SELF::py_getfield, &SELF::py_setfield > py_fields;

  bool py_getadd(int i) {

    if (i<0) i += nfields();
    if (i<0 || i >= nfields())
      throw std::invalid_argument("xgeometry: field index out of range");
    return additive(i);

  }

  void py_setadd(int i, const bool &a) {

    if (i<0) i += nfields();
    if (i<0 || i >= nfields())
      throw std::invalid_argument("xgeometry: field index out of range");
    additive(i) = a;

  }

  py_indexed_property<SELF, bool, int, &SELF::py_getadd, &SELF::py_setadd > py_add;

  virtual void py_add_list(const py::list & l) {
    geometry<REAL,CELL>::add("",0,0,0);
    py_setitem(nat()-1,l);
  }

  static void py_export(py::module m, const char * pyname) {

    std::string sPropNameField = fmt::format("{0}_{1}",pyname,"idx_prop_xfield");
    py_2indexed_property<SELF, py::object, py::object, int, &SELF::py_getfield1,
                         &SELF::py_setfield1, &SELF::py_getfield,
                         &SELF::py_setfield >::py_2export(m, sPropNameField.c_str());

    std::string sPropNameAdd = fmt::format("{0}_{1}",pyname,"idx_prop_xadd");
    py_indexed_property<SELF, bool, int, &SELF::py_getadd,
                        &SELF::py_setadd>::py_export(m, sPropNameAdd.c_str());

    py::class_<xgeometry<REAL,CELL>, geometry<REAL,CELL>, std::shared_ptr<xgeometry<REAL,CELL>>>
        (m, pyname, py::dynamic_attr())
            .def(py::init<int,   const STRING_EX&>(),
                 py::arg("dim"), py::arg("__name") = "")
            .def(py::init<CELL&, const py::list &, const STRING_EX&>(),
                 py::arg("CELL"), py::arg("f"), py::arg("__name") = "")
            .def_readwrite("field", & SELF::py_fields)
            .def_readwrite("additive", & SELF::py_add)
            .def("nfields", & SELF::nfields)
            .def("field_name", & SELF::field_name)
            .def("set_format", &SELF::set_format);
  }

#endif

};

} // namespace qpp

#endif
