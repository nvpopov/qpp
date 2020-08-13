#ifndef QPP_NGBR_H
#define QPP_NGBR_H

#include <typeinfo>
#include <utility>
#include <set>
#include <algorithm>
#include <cmath>
#include <geom/geom.hpp>
#include <string>

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

namespace qpp {

// ------------------------------------------------------------


template <class REAL>
class bonding_table {

  struct covrad_record_t {
    STRING_EX at;
    REAL d;

    covrad_record_t(const STRING_EX & _at, REAL _d) {
      at = _at;
      d = _d;
    }

  };

  std::vector<covrad_record_t> p_covrads;

  inline bool covrad_match(const STRING_EX & at, int i) const {
    return at == p_covrads[i].at;
  }

  inline int find_covrad(const STRING_EX & at) const {
    for (int i=0; i<p_covrads.size(); i++)
      if (covrad_match(at,i))
        return i;
    return -1;
  }

  // -------------------------------------------------

  struct ngbr_record_t {
    STRING_EX at1, at2;
    REAL d;

    ngbr_record_t(const STRING_EX & _at1, const STRING_EX & _at2, REAL _d) {
      at1 = _at1;
      at2 = _at2;
      d = _d;
    }
  };

  std::vector<ngbr_record_t> p_records;

  inline bool record_match(const STRING_EX & at1,
                            const STRING_EX & at2, int i) const {
    return ( at1 == p_records[i].at1 && at2 == p_records[i].at2 )
           || ( at2 == p_records[i].at1 && at1 == p_records[i].at2 );
  }

  inline int find_record(const STRING_EX & at1, const STRING_EX & at2) const {
    for (int i=0; i<p_records.size(); i++)
      if (record_match(at1,at2,i))
        return i;
    return -1;
  }

public:

  typedef bonding_table<REAL> SELF;

  STRING_EX name;

  REAL default_distance;

  REAL covrad(const STRING_EX &at) {
    int i = find_covrad(at);
    return i>-1 ? p_covrads[i].d : 0e0;
  }

  void set_covrad(const STRING_EX &at, const REAL & d) {
    int i = find_covrad(at);
    if (i>-1)
      p_covrads[i].d = d;
    else
      p_covrads.push_back(covrad_record_t(at,d));
  }

  REAL pair(const STRING_EX at1, const STRING_EX at2) {
    int i = find_record(at1,at2);
    return i>-1 ? p_records[i].d : 0e0;
  }

  void set_pair(const STRING_EX   at1, const STRING_EX at2, const REAL &d) {
    int i = find_record(at1,at2);
    if (i>-1)
      p_records[i].d = d;
    else
      p_records.push_back(ngbr_record_t(at1,at2,d));
  }

  REAL distance(const STRING_EX &at1, const STRING_EX at2) {
    int i = find_record(at1,at2);
    if (i>-1)
      return p_records[i].d;

    i = find_covrad(at1);
    int j = find_covrad(at2);

    if ( i>-1 && j>-1 )
      return p_covrads[i].d + p_covrads[j].d;

    return default_distance;
  }


  void clear() {
    p_records.clear();
    p_covrads.clear();
    default_distance = 0e0;
  }

  virtual void write(std::basic_ostream<CHAR_EX,TRAITS> &os, int offset=0) const {
    for (int k=0; k<offset; k++) os << " ";
    os << "bonding_table";
    if (name != "")
      os << " " << name;
    os << "{\n";

    for (int k=0; k<offset+2; k++) os << " ";
    os << "default = " << default_distance << ";\n";

    for (const auto & c : p_covrads) {
      for (int k=0; k<offset+2; k++) os << " ";
      os << "covrad(" << c.at << ") = " << c.d << ";\n";
    }

    for (const auto & p : p_records) {
      for (int k=0; k<offset+2; k++) os << " ";
      os << "pair(" << p.at1 << "," << p.at2 << ") = " << p.d << ";\n";
    }

    for (int k=0; k<offset; k++) os << " ";
    os << "}\n";
  }

  void merge(const bonding_table<REAL> & bt) {
    default_distance = std::max(default_distance, bt.default_distance);
    for (int i=0; i<bt.p_records.size(); i++) {
      int j = find_record( bt.p_records[i].at1, bt.p_records[i].at2);
      if (j==-1)
        p_records.push_back(bt.p_records[i]);
      else
        p_records[j].d = std::max( p_records[j].d, bt.p_records[i].d);
    }

    for (int i=0; i<bt.p_covrads.size(); i++) {
      int j = find_covrad( bt.p_covrads[i].at );
      if (j==-1)
        p_covrads.push_back(bt.p_covrads[i]);
      else
        p_covrads[j].d = std::max( p_covrads[j].d, bt.p_covrads[i].d);
    }
  }


#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

  // --------------- PYTHON -------------------------------

  py_indexed_property<SELF, REAL, const STRING_EX &,
                      &SELF::covrad, &SELF::set_covrad> py_covrad;

  REAL py_getpair(const STRING_EX) { return -1;}
  void py_setpair(const STRING_EX, const REAL &) {}

  REAL py_getpair2(const STRING_EX at1, const STRING_EX  at2) {
    return pair(at1,at2);
  }

  void py_setpair2(const STRING_EX at1, const STRING_EX  at2, const REAL & d) {
    set_pair(at1,at2,d);
  }

  py_2indexed_property<SELF, REAL, REAL, const STRING_EX,
                       &SELF::py_getpair, &SELF::py_setpair,
                       &SELF::py_getpair2, &SELF::py_setpair2 > py_pair;

  py::dict to_dict() {
    py::dict d;
    d["default"] = default_distance;

    for (auto i = p_covrads.begin(); i != p_covrads.end(); i++)
      d[i->at.c_str()] = i->d;

    for (auto i = p_records.begin(); i != p_records.end(); i++)
      d[py::make_tuple(i->at1, i->at2)] = i->d;

    return d;
  }

  void from_dict( py::dict & d) {

    for(auto p : d) {
      //std::vector p = py::cast<std::vector>(pnc);
      REAL val = this->default_distance;
      if (!py::isinstance<py::float_>(p.second))
        TypeError("bonding_table::from_dict: "
                  "Invalid dictionary, values must be of real type");
      else val = py::cast<REAL>(p.second);

      //bp::extract<STRING> ks(p[0]);
      if (py::isinstance<py::str>(p.first)) {
        STRING_EX s = py::cast<STRING_EX>(p.first);
        if (s=="default")
          default_distance = val;
        else
          set_covrad(s,val);
      }

      else if (py::cast<py::tuple>(p.first)) {
        py::tuple t = py::cast<py::tuple>(p.first);
        if (py::len(t)!=2)
          TypeError("bonding_table::from_dict: Invalid dictionary, "
                    "tuple key can contain a pair of atoms only");

        if (py::isinstance<py::str>(t[0]) &&
            py::isinstance<py::str>(t[1]))
          set_pair(py::cast<STRING_EX>(t[0]),
                   py::cast<STRING_EX>(t[1]), val);
        else
          TypeError("bonding_table::from_dict: Invalid dictionary,"
                    " tuple key can contain a pair of atoms only");
      }
      else
        TypeError("bonding_table::from_dict: Invalid dictionary, "
                  "key can be \'default\', an atom, or a pair of atoms");
    }
  }

  static void py_export(py::module m, const char * pyname) {
    std::string sPropNameCovRad =
        fmt::format("{0}_{1}",pyname,"idx_prop_covrad");
    py_indexed_property<SELF, REAL, const STRING_EX & , &SELF::covrad,
                        &SELF::set_covrad>::py_export(m, sPropNameCovRad.c_str());

    std::string sPropNamePair =
        fmt::format("{0}_{1}",pyname,"idx_prop_pair");
    py_2indexed_property<SELF,REAL,REAL, const STRING_EX , &SELF::py_getpair,
                         &SELF::py_setpair,&SELF::py_getpair2, &SELF::py_setpair2 >
        ::py_2export(m, sPropNamePair.c_str(),true);

    py::class_<bonding_table<REAL> >(m, pyname)
        .def( py::init<>())
        .def_readwrite("default", &SELF::default_distance,
                       "The default bonding distance between any atoms (r/w)" )
        .def_readwrite("covrad",  &SELF::py_covrad,
                       "Covalent radius for atom. "
                       "Usage: covrad[at] with string at(r/w)")
        .def_readwrite("pair",    &SELF::py_pair,
                       "Pair specific bonding distance. "
                       "Usage: pair[at1,at2] "
                       "with string at1,at2 (r/w)")
        .def("distance", &SELF::distance,
             "Bonding distance between two atoms. "
             "Usage: distance(at1,at2)"
             " with string at1,at2")
        .def("to_dict", & SELF::to_dict,
             "Output the content of bonding"
             " table as dictionary. Usage: to_dict()")
        .def("from_dict", & SELF::from_dict,
             "Fill the bonding table from dictionary. "
             "Usage: from_dict(dict)")
        .def("clear", & SELF::clear, "Erase all data records")
        .def("merge",  & SELF::merge, "Merge another bonding table"
                                    " to this one");

  }

#endif

  bonding_table(const STRING_EX & __name = "") {
    name = __name;
    default_distance = 0e0;
#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
    py_covrad.bind(this);
    py_pair.bind(this);
#endif
  }


};

// ------------------- Neighbours table -----------------------

template <class REAL, class CELL = periodic_cell<REAL> >
class neighbours_table : public geometry_observer<REAL> {

  typedef neighbours_table<REAL,CELL> SELF;

  // The periodicity the geometry
  int DIM;

  // The geometry for which neighbours table is
  geometry<REAL, CELL> *geom{};

  // The bonding distances data
  bonding_table<REAL> *btbl{};

  // Internal bonding distances table
  REAL* p_disttable{};

  // Number of atomic types
  int p_ntp;

  // Bonding distance between i-th and j-th atomic types
  inline REAL distance(int i, int j) const {return p_disttable[i*p_ntp+j];}

  inline REAL & distance(int i, int j) {return p_disttable[i*p_ntp+j];}

  inline void resize_disttable() {
    if (p_disttable != nullptr)
      delete []p_disttable;
    p_ntp = geom->n_types();
    if (p_ntp < 1)
      IndexError("Number of atomic types is zero. Maybe, you should initialize typetable?");
    p_disttable = new REAL[p_ntp*p_ntp];
  }

  void build_disttable() {
    resize_disttable();
    for (int i=0; i<p_ntp; i++)
      for (int j=0; j<=i; j++) {
        distance(i,j) = btbl->distance(geom->atom_of_type(i),geom->atom_of_type(j));
        distance(j,i) = btbl->distance(geom->atom_of_type(i),geom->atom_of_type(j));

      }
  }
  // ------------------------------------------

  std::vector<std::vector<index> > p_table;

public:
  // Number of neighbours of i-th atom
  inline int n(int i) const {return p_table[i].size();}

  // j-th neighbour of i-th atom
  inline index table(int i, int j) const {return p_table[i][j];}

  // Synonym
  inline index operator()(int i, int j) const{
    return table(i,j);
  }

  // The same but more general - i-th atom specified with full index
  inline index operator()(const index & i, int j) const{
    index res = table(i,j);
    for (int d=0; d<DIM; d++)
      res(d+1) += i(d+1);
    return res;
  }

private:

  inline void add_ngbr_impl(int i, const index & j) {
    bool found = false;
    for (int k = 0; k < p_table[i].size(); k++ )
      if (p_table[i][k]==j) {
        found = true;
        break;
      }
    if (!found)
      p_table[i].push_back(j);
  }

  // ------------------------------------------

  bool auto_update;

public:
  bool auto_grainsize;

  void set_auto_update(bool au) {
    if (au && !auto_update) {
      geom->add_observer(*this);
      auto_update = true;
    }
    else if (!au && auto_update) {
      geom->remove_observer(*this);
      auto_update = false;
    }
  }

  bool get_auto_update() const {return auto_update;}

private:
  REAL grainsize;

  vector3<REAL> Rmin, Rmax;
  index ngrain;
  std::vector<std::vector<index> > grains;

  void translational_grain_setup() {
    // find largest neighbourung distance
    //std::cout << "trnsl grain setup\n";

    bool ndef = true;

    for (int i=0; i<geom->size(); i++) {
      vector3<REAL> r = geom->pos(i);
      if (ndef) {
        Rmin = Rmax = r;
        ndef = false;
      }
      for (int j=0; j<3; j++) {
        if ( Rmin(j) > r(j) )
          Rmin(j) = r(j);
        if ( Rmax(j) < r(j) )
          Rmax(j) = r(j);
      }
    }
    //std::cout <<  "Rmin = " << Rmin << " Rmax= " << Rmax << "\n";

    if (DIM!=0) {
      //std::cout << "Extension of Rmin, Rmax\n";
      Rmin -= vector3<REAL>(1,1,1)*(grainsize+1e-5);
      Rmax += vector3<REAL>(1,1,1)*(grainsize+1e-5);
    }

    ngrain = index::D(3);
    for (int i=0; i<3; i++)
      ngrain(i) = int( (Rmax(i)-Rmin(i))/grainsize ) + 1;

    //std::cout << "grain setup finished\n" << "Rmin = " << Rmin
    //<< " Rmax= " << Rmax << " gs= " << grainsize <<
    //" ngrain = " << ngrain << "\n";
  }

  REAL optimal_grainsize() {
    const REAL alpha = 1, beta = 0;
    REAL Vol = (Rmax(0)-Rmin(0))*(Rmax(1)-Rmin(1))*(Rmax(2)-Rmin(2));
    return std::pow(Vol,1./3)*std::pow(alpha/geom->nat(), 1./(3*(beta+1)));

  }

  void grain_setup() {

    if (auto_grainsize) {
      grainsize = REAL(0);
      int ntp = geom->n_atom_types();
      for (int i=0; i<ntp*ntp; i++)
        if (p_disttable[i] > grainsize )
          grainsize = p_disttable[i];
    }

    translational_grain_setup();

    REAL opt_gs = optimal_grainsize();

    //std::cout << "gs= " << grainsize << " opt_gs= " << opt_gs << "\n";

    if (auto_grainsize && grainsize < opt_gs ) {
      grainsize = opt_gs;
      for (int i=0; i<3; i++)
        ngrain(i) = int( (Rmax(i)-Rmin(i))/grainsize ) + 1;
    }

  }

  inline int gidx(int i, int j, int k) {
    return i + ngrain(0)*j + ngrain(0)*ngrain(1)*k;
  }

  inline int gidx(const index & I) {
    return I(0) + ngrain(0)*I(1) + ngrain(0)*ngrain(1)*I(2);
  }

  inline std::vector<index> & grain(int i, int j, int k) {
    return grains[gidx(i,j,k)];
  }

  inline std::vector<index> & grain(const index & I) {return grains[gidx(I)];}

  inline index igrain(const index & at) {
    vector3<REAL> r = geom->r(at);
    index I = index::D(3);
    for (int j=0; j<3; j++)
      I(j) = std::floor( (r(j)-Rmin(j))/grainsize );
    return I;
  }

  inline void to_grain(const index & at) {
    index I=igrain(at);
    if ( I(0)>=0 && I(0)<ngrain(0) && I(1)>=0 &&
        I(1)<ngrain(1) && I(2)>=0 && I(2)<ngrain(2) )
      grain(I).push_back(at);
  }

  void graining() {
    for (int i=0; i<grains.size(); i++)
      grains[i].clear();
    grains.clear();
    grains.resize(ngrain(0)*ngrain(1)*ngrain(2));


    for (int at=0; at<geom->nat(); at++)
      if (! geom->shadow(at) )
        for ( iterator I(geom->cell.begin(),geom->cell.end()); !I.end(); I++)
          to_grain(atom_index(at,I));

    //      debug
    /*
      std::cout << "graining finished\n";

    for (iterator I({0,0,0}, ngrain-index({1,1,1})); !I.end(); I++)
    {
      std::cout << "grain" <<  I << " " << gidx(I) << "\n";

      for (int l=0; l<grain(I).size(); l++)
        std::cout << " " << grain(I)[l] << " ";
      std::cout << "\n";

    }
    */

  }

  // -------------------------------------------------------------------


public:

  bool reference_mode;
  bool transl_mode;

  neighbours_table( geometry<REAL, CELL> & g, bonding_table<REAL> & t) :
                    ngrain(index::D(3)), p_disttable(nullptr) {
    btbl = &t;
    geom = & g;
    DIM = geom -> get_DIM();
    build_disttable();
    reference_mode = false;
    transl_mode = true;
    auto_grainsize = true;
    auto_update = false;
  }

  ~neighbours_table() {
    //          delete [] _disttable;
    if (p_disttable != nullptr)
      delete [] p_disttable;
  }

  REAL get_grain_size() {return grainsize;}

  void set_grain_size(REAL gs) {auto_grainsize = false;grainsize = gs;}

  // -------------------------------------------------------------------

  void reference_build() {

    //std::cout << "reference build\n";

    for (int i=0; i<geom->nat(); i++)
      if (!geom->shadow(i))
        for (int k=0; k<geom->nat(); k++)
          if (!geom->shadow(k))
            for (iterator I(geom->cell.begin(), geom->cell.end()); !I.end(); I++)
              if ( (geom->pos(i) - geom->pos(k,I)).norm() <
                      distance(geom->type_table(i), geom->type_table(k))
                  && !( i==k && I==index::D(DIM).all(0)) )
                p_table[i].push_back(atom_index(k,I));
  }

  void translational_build() {
    //std::cout << "translational build\n";

    index dirray[14];
    int n=0;
    for (int i=-1; i<=0; i++)
      for (int j=-1; j<=-i; j++)
        for (int k=-1; k<=-i || k<=-j; k++)
          dirray[n++] = {i,j,k};


    // debug
    /*
      std::cout << "after dirray alive\n";
      for (const index & DI : dirray)
        std::cout << DI;
      std::cout << "\n";
      */


    //index shift1 = {1,1,1}, shift2={2,2,2};
    //index shift1 = {1,1,1}, shift2={1,1,1};
    index shift1 = {0,0,0}, shift2={1,1,1};
    /*
      if (geom->DIM==0)
        {
          //shift1 = {0,0,0};
          //shift2 = {1,1,1};
          shift1 = {1,1,1};
          shift2 = {1,1,1};
        }
      */
    int Nprint=200;
    int nprint=0;

    for (iterator I(shift1, ngrain-shift2); !I.end(); I++) {
      int g1 = gidx(I);
      if (grains[g1].size()>0)
        for (const index & DI : dirray) {
          index J = I + DI;
          if ( J(0)<0 || J(0)>=ngrain(0) || J(1)<0 || J(1)>=ngrain(1) ||
              J(2)<0 || J(2)>=ngrain(2))
            continue;
          int g2 = gidx(J);

          if (++nprint == Nprint) {
            nprint =0;
            //std::cout << I << " = " << g1 << " + " <<
            //DI << " = " << J << " = " << g2 << " grains.size= "
            //<< grains.size() << "\n";
          }

          for (int c2 = 0; c2 < grains[g2].size(); c2++)
            for (int c1 = 0; c1 < ( g1==g2? c2 : grains[g1].size()); c1++) {

              index at1 = grains[g1][c1];
              index at2 = grains[g2][c2];
              REAL r = (geom->pos(at1) - geom->pos(at2)).norm();

              /*
                      if (at1==31|| at2==31)
                        {
                          std::cout << "at1 = " << at1 << " grain " << I <<
 " at2= "<< at2 << " grain " << J <<  " DI =" << DI <<"\n";
                          std::cout << "type1= " << geom->type(at1) <<
  " type2= " << geom->type(at2) << " d= "
<< distance(geom->type(at1), geom->type(at2)) << " r= " << r << "\n";
                        }
                      */

              if ( r <= distance(geom->type(at1), geom->type(at2))) {
                if ( at1.sub(1) == index::D(DIM).all(0) ) {
                  add_ngbr_impl(at1,at2);
                  index at= at1;
                  at.sub(1) -= at2.sub(1);
                  /*
                              for (int dd=0; dd<DIM; dd++)
                                at.setcell(dd,-at2.cell(dd));
                              */
                  add_ngbr_impl(at2,at);

                  /*
                              if (at1==31 || at1==41)
                                std:: cout << "added:" << int(at1) <<
                                at2 << " added " << int(at2) << at << "\n";
                              */

                }
                else if ( at2.sub(1) == index::D(DIM).all(0) ) {
                  add_ngbr_impl(at2,at1);
                  index at= at2;
                  at.sub(1) -= at1.sub(1);
                  add_ngbr_impl(at1,at);

                }

              }
            }
        }
    }
  }

  void build() {
    for (int i=0; i<p_table.size(); i++)
      p_table[i].clear();
    p_table.resize(geom->nat());

    if (reference_mode) {
      reference_build();
      return;
    }

    grain_setup();
    graining();

    /*
      std::cout << typeid(CELL).name() << "\n";
      std::cout <<typeid(periodic_cell<DIM,REAL>).name() << "\n";
      std::cout << typeid(CELL).hash_code() << "\n";
      std::cout <<typeid(periodic_cell<DIM,REAL>).hash_code() << "\n";
      */

    if (transl_mode && typeid(CELL) == typeid(periodic_cell<REAL>)) {
      translational_build();
      return;
    }

    std::set<std::pair<int,int> > gpairs;
    std::vector<char> marked(ngrain(0)*ngrain(1)*ngrain(2), false);

    /*
      std::cout << "alive1 " << marked.size()<< "\n";
      std::cout << "ngrain= " << ngrain << " Rmin= " <<
      Rmin << " Rmax= " << Rmax << " gs= " << grainsize << "\n";
      */

    for (int at=0; at<geom->nat(); at++)
      if (!geom->shadow(at)) {
        index I = igrain(index::D(DIM+1).atom(at));
        int g1 = gidx(I);

        if (marked[g1])
          continue;
        else
          marked[g1] = true;

        //std::cout << "g1= " << g1 << " I= " << I << "\n";

        for (iterator DI({-1,-1,-1},{1,1,1}); !DI.end(); DI++) {
          auto J = I + DI;
          if (J(0)>=0 && J(0)<ngrain(0) && J(1)>=0 &&
              J(1)<ngrain(1) && J(2)>=0 && J(2)<ngrain(2) ) {
            int g2 = gidx(J);

            //std::cout << g1 << I << g2 << J << "\n";

            if (g1>=g2)
              gpairs.insert(std::pair<int,int>(g1,g2));
            else
              gpairs.insert(std::pair<int,int>(g2,g1));
          }
        }
      }
    /*
      std::sort(gpairs.begin(),gpairs.end());
      auto last = std::unique(gpairs.begin(),gpairs.end());
      gpairs.resize( std::distance(gpairs.begin(),last) );
      */

    for (const auto & gp : gpairs) {
      int g1 = gp.first, g2 = gp.second;
      for (int c1 = 0; c1 < grains[g1].size(); c1++)
        for (int c2 = 0; c2 < (g1==g2 ? c1 : grains[g2].size()); c2++) {
          index at1 = grains[g1][c1];
          index at2 = grains[g2][c2];

          bool skip = geom->shadow(at1) || geom->shadow(at2);
          if (!skip)
            skip = at1.sub(1) != index::D(DIM).all(0) && at2.sub(1)
                                                             != index::D(DIM).all(0);
          if (skip)
            continue;

          REAL r = (geom->pos(at1) - geom->pos(at2)).norm();

          //std::cout << "at1 = " << at1.atom << at1.cell
          //<< " grain " << I << " at2= "<< at2.atom <<
          //at2.cell << " grain " << I+DI <<  " DI =" << DI <<"\n";

          if ( r <= distance(geom->type_table(at1),
                            geom->type_table(at2))) {
            if ( at1.sub(1) == index::D(DIM).all(0) )
              add_ngbr_impl(at1, at2);
            if ( at2.sub(1) == index::D(DIM).all(0) )
              add_ngbr_impl(at2, at1);
          }

        }
    }

    //      for (auto gp:gpairs)
    //	std::cout << gp.first << " " << gp.second << "\n";
  }

  typedef  geometry_observer<REAL> DEP;

  void ref_inserted(int at,
                    before_after st,
                    const STRING_EX & a,
                    const vector3<REAL> & r) {
    if (st == DEP::after) {
      p_table.insert(p_table.begin()+at, std::vector<index>());
      for (int i=0; i<geom->nat(); i++)
        if (! geom->shadow(i))
          for (iterator j(geom->cell.begin(),
                          geom->cell.end()); j.end(); j++)
            if ( !(i==at && j==index::D(DIM).all(0)) &&
                norm(geom->r(at) - geom->r(i, j)) <
                    distance(geom->type_table(at), geom->type_table(i))
                ) {
              p_table[at].push_back(index({i,j}));
              index iat = {at};
              iat.sub(1) -= j;
              p_table[i].push_back(iat);
            }
    }
  }

  void ref_added(before_after st,
                 const STRING_EX & a,
                 const vector3<REAL> & r) {
    ref_inserted(geom->nat()-1,st,a,r);
  }

  void ref_moved(int at,
                 before_after st,
                 const vector3<REAL> & r) {

  }

  void ref_erased(int at,
                  before_after st) {

    if (st==DEP::before) {
      p_table.erase(p_table.begin()+at);

      for (int i=geom->nat()-2; i>=0; i--)
        for (int j=n(i)-1; j>=0; j--)
          if (p_table[i][j](0)==at) {
            //std::cerr << "erase " << i << " " << _table[i][j] << "\n";
            p_table[i].erase(p_table[i].begin()+j);
          }
          else if (p_table[i][j](0)>at) {
            //std::cerr << _table[i][j] << "->";
            p_table[i][j](0)--;
            //std::cerr << _table[i][j] << "\n";
          }
    }
  }

  void ref_shaded(int at, before_after st, bool sh) {}

  uint32_t get_flags() override {
    return geometry_observer_supports_default
           | geometry_observer_supports_add
           | geometry_observer_supports_insert
           | geometry_observer_supports_change
           | geometry_observer_supports_erase
           | geometry_observer_supports_shadow
           | geometry_observer_supports_reorder;
  };

  void added(before_after st, const STRING_EX & a, const vector3<REAL> & r) override {}
  void inserted(int at, before_after st, const STRING_EX & a,const vector3<REAL> & r) override {}
  void changed(int at, before_after st, const STRING_EX & a,const vector3<REAL> & r) override {}
  void erased(int at, before_after st) override {}
  void shaded(int at, before_after st, bool sh) override {}
  void reordered(const std::vector<int> &, before_after) override {}
  void selected(int at, before_after ord) override {}

  void geometry_destroyed() override {}
  void dim_changed(before_after ord) override {}
  void cell_changed(before_after ord) override {}
  void xfield_changed(int xid, int at, before_after ord) override {}

  //------------------------------------------------------------
  bool operator==(const neighbours_table & t) const{
    if (p_table.size() != t.p_table.size())
      return false;
    for (int i=0; i<p_table.size(); i++) {
      if (p_table[i].size() != t.p_table[i].size())
        return false;
      for (int j=0; j<p_table[i].size(); j++) {
        bool found = false;
        for (int k=0; k<p_table[i].size(); k++)
          if (p_table[i][j]==t.p_table[i][k]) {
            found=true;
            break;
          }
        if (!found)
          return false;
      }
    }
    return true;
  }

  bool operator!=(const neighbours_table & t) const {
    return ! (*this == t);
  }

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

  py::list py_getitem(int i) const{
    if (i<0)
      i += geom -> nat();
    if (i<0 || i>= geom->nat())
      IndexError("Index out of range in ngbr_table::getitem");
    py::list l;
    for(int j=0; j<n(i); j++)
      l.append(table(i, j));
    return l;
  }

  index py_getitem2(py::tuple I) const{
    if (py::len(I)!=2)
      TypeError("neigbour_table::getitem. Expected 2 integers");
    if ( ! py::isinstance<py::int_>(I[0]) || ! py::isinstance<py::int_>(I[1]))
      TypeError("neigbour_table::getitem. Expected 2 integers");

    int i = py::cast<int>(I[0]);
    int j = py::cast<int>(I[1]);

    if (i<0)
      i += geom -> nat();
    if (i<0 || i>= geom->nat())
      IndexError("Index out of range in ngbr_table::getitem");

    if (j<0)
      j += n(i);
    if (j<0 || j>= n(i))
      IndexError("Index out of range in ngbr_table::getitem");

    return table(i,j);
  }

  static void py_export(py::module m, const char * pyname) {
    py::class_<neighbours_table<REAL,CELL> >(m, pyname)
        .def(py::init< geometry<REAL, CELL> &, bonding_table<REAL> & >())
        .def_property("auto_update",
                      &SELF::get_auto_update,
                      &SELF::set_auto_update,
                      "bool auto_update (default: False). If auto_update==True, "
                      "any modifications made to atoms are\nautomatically "
                      "reflected by neighbours_table")

        .def_readwrite("reference_mode",
                       &SELF::reference_mode,
                       "bool reference_mode (default: False). "
                       "If reference_mode==True, simple but very inefficient\n"
                       "algorythm is used for building neighbours_table. For "
                       "small molecules (less then 100 atoms) and for"
                       " debugging purpose")

        .def_property("grain_size",
                      &SELF::get_grain_size,
                      &SELF::set_grain_size,
                      "real grain_size (default: auto). Building and updating"
                      " neighbour_table is done by dividing the\nmolecule "
                      "space into cubic grains of grain_size. The value of "
                      "grain_size\nis normally selected automatically, "
                      "however, you can set it manually")

        .def_readwrite("auto_grainsize",
                       &SELF::auto_grainsize,
                       "bool auto_grainsize (default: True). Whether to "
                       "choose grain_size value automatically")

        .def_readwrite("transl_mode",
                       &SELF::transl_mode)
        .def("build", &SELF::build, "Build the neighbours_table")
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("len", &SELF::n,
             "Usage: len(int i) - number of neighbours of i-th atom")
        .def("__getitem__", &SELF::py_getitem)
        .def("__getitem__", &SELF::py_getitem2)
        ;
  }

#endif

};

}

#endif
