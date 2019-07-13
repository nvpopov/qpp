#ifndef QPP_BUILDERS_H
#define QPP_BUILDERS_H

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pyqpp/py_indexed_property.hpp>
//#include <pybind11/stl.h>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

#pragma GCC diagnostic ignored "-Wnarrowing"
#include <vector>
#include <cmath>
#include <functional>
#include <symm/index.hpp>
#include <symm/groups.hpp>
#include <symm/cell.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/shape.hpp>
#include <geom/ngbr.hpp>

namespace qpp {

  //!\brief the flags regulating the details of building procedures
  enum build_mode {

    //!\brief ignore the situation when two or more atoms are put too close ("crowded") - simply
    //! put them into crowd
    crowd_ignore  = 1,

    //!\brief do not put another atom too close to already existing atom
    //! - omit it
    crowd_exclude = 2,

    /*!\brief merge atoms of the same type placed in same point into one atom
      by summation of their electric charges and masses,
      i.e. atoms are considered as "fractions"
    */
    crowd_merge   = 4,

    //!\brief When filling a volume of certain geometric shape, omit all
    //!  atoms outside that volume
    fill_atoms    = 8,

    /*!\brief When filling a volume of certain geometric shape, put all atoms unit cell if
     * the centre of this cell is inside that volume (even if some atoms are outside)
    */
    fill_cells    = 16,

    // !\brief use periodic pattern for legacy uc files
    legacy_fill   = 32

  };

  template<class REAL, class CELL>
  void treat_crowd(geometry<REAL,CELL> & geom, int mode) {

    if (mode & crowd_ignore)
      return;

    bonding_table<REAL> b;
    b.default_distance = geom.tol_geom;
    neighbours_table<REAL,CELL> n(geom,b);
    n.build();
    std::vector<int> todel;
    todel.resize(geom.nat());
    for (int i = 0; i < geom.nat(); i++)
      todel[i] = -1;
    for (int i = 0; i < geom.nat(); i++)
      if ( todel[i] == -1 && n.n(i)>0)
        for (int j = 0; j < n.n(i); j++)
          if (geom.atom(i)==geom.atom(j))
            todel[n(i,j)] = i;

    xgeometry<REAL,CELL> *xgeom = dynamic_cast<xgeometry<REAL,CELL>*>(&geom);
    bool merge = (mode & crowd_merge) && xgeom != nullptr;

    if (merge)
      for (int i=geom.nat()-1; i>=0; i--)
        if (todel[i] > -1) {
            int j=todel[i];
            for (int k=0; k <xgeom->nfields(); k++)
              if (xgeom->additive(k)) {
                  if (xgeom->field_type(k) == type_int)
                    xgeom->template xfield<int>(k,j) += xgeom->template xfield<int>(k,i);
                  else if (xgeom->field_type(k) == type_real)
                    xgeom->template xfield<REAL>(k,j) += xgeom->template xfield<REAL>(k,i);
                }
          }

    for (int i=geom.nat()-1; i>=0; i--)
      if (todel[i]>-1)
        geom.erase(i);

  }


  // ----------------------------------------------------------------------------

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void copy_header(geometry<REALDST,CELLDST> & dst,
                   const geometry<REALSRC,CELLSRC> & src) {

    xgeometry<REALDST,CELLDST> *xdst = nullptr;
    xgeometry<REALSRC,CELLSRC> *xsrc = nullptr;

    std::vector<STRING_EX> fn;
    std::vector<basic_types> ft;

    if (src.is_xgeometry())
      xsrc = (xgeometry<REALSRC,CELLSRC>*)(&src);

    if (dst.is_xgeometry()){
        xdst = (xgeometry<REALDST,CELLDST>*)(&dst);
        if (src.is_xgeometry()) {
            xsrc->get_format(fn,ft);
            xdst->set_format(fn,ft);
          }
        else
          xdst->set_format({"atom","x","y","z"},
          {type_string,type_real,type_real,type_real});
      }
  }


  // ----------------------------------------------------------------------------

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void replicate(geometry<REALDST,CELLDST> & dst,
                 const geometry<REALSRC,CELLSRC> & src,
                 const CELLSRC & cell,
                 const index & begin,
                 const index & end,
                 int mode = crowd_ignore) {

    bool xcopy = dst.is_xgeometry() && src.is_xgeometry();

    copy_header(dst,src);

    xgeometry<REALSRC,CELLSRC> *xsrc = nullptr;
    if (src.is_xgeometry())
      xsrc = (xgeometry<REALSRC,CELLSRC>*)(&src);

    int ix,iy,iz;
    if (xsrc != nullptr)
      for (int i = 0; i < xsrc->nfields(); i++) {
          STRING_EX fn = xsrc -> field_name(i);
          if (fn=="x")
            ix = i;
          else if (fn=="y")
            iy = i;
          else if (fn=="z")
            iz = i;
        }
    else {
        ix = 1; iy=2; iz=3;
      }

    for (int at = 0; at < src.nat(); at++)
      if (!src.shadow(at)) {
          std::vector<datum> v;
          src.get_fields(at,v);
          const vector3<REALSRC> & r = src.coord(at);
          vector3<REALSRC> r1;
          v[ix].set(&r1(0));
          v[iy].set(&r1(1));
          v[iz].set(&r1(2));
          for (iterator I(begin,end); !I.end(); I++){
              // fixme - to be replaced with dst.add_fields(v)
              dst.add("",vector3<REALDST>::Zero());
              r1 = cell.transform(r,I);
              dst.set_fields(dst.nat()-1,v);
            }
        }

    treat_crowd(dst,mode);

  }

  // -------------------------------------------------------------------------------

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void fill( geometry<REALDST,CELLDST> & dst,
             const geometry<REALSRC,CELLSRC> & src,
             const shape<REALSRC> & shp,
             const CELLSRC & cell,
             const index & begin, const index & end,
             int mode = crowd_ignore | fill_atoms) {
    bool xcopy = dst.is_xgeometry() && src.is_xgeometry();

    copy_header(dst,src);
    xgeometry<REALSRC,CELLSRC> *xsrc = nullptr;
    if (src.is_xgeometry())
      xsrc = (xgeometry<REALSRC,CELLSRC>*)(&src);

    int ix,iy,iz;
    if (xsrc != nullptr)
      for (int i=0; i<xsrc->nfields(); i++) {
          STRING_EX fn = xsrc -> field_name(i);
          if (fn=="x")
            ix = i;
          else if (fn=="y")
            iy = i;
          else if (fn=="z")
            iz = i;
        }
    else {
        ix = 1; iy=2; iz=3;
      }

    std::cout << "fill alive 1\n";

    std::vector<std::vector<datum> > v(src.nat());
    std::vector<vector3<REALSRC> > r1(src.nat());

    for (int at=0; at<src.nat(); at++){
        src.get_fields(at,v[at]);
        v[at][ix].set(&r1[at][0]);
        v[at][iy].set(&r1[at][1]);
        v[at][iz].set(&r1[at][2]);
      }

    std::cout << "fill alive 2\n";
    std::cout << "idx begin " << begin << "\n";
    std::cout << "idx end " << end << "\n";

    bool fillcells = mode & fill_cells;

    for (iterator I(begin,end); !I.end(); I++) {

        bool allcell = false, something = false;
        bool * inside = new bool[src.nat()];
        for (int at=0; at<src.nat(); at++){
            r1[at] = cell.transform(src.pos(at),I);
            bool insd = !src.shadow(at) && shp.within(r1[at]);
            inside[at] = insd;

            if (insd) something = true;
            if (fillcells && insd) allcell = true;

            if (mode & legacy_fill) {

                int i = abs(I(0));
                int j = abs(I(1));
                int k = abs(I(2));

                bool even_catch = (k % 2 == 0) && (i % 2 == j % 2);
                bool odd_catch = (k % 2 != 0) && (i % 2 != j % 2);
                if (!(even_catch || odd_catch)) something = false;

              }
          }

        if (something)
          for (int at=0; at<src.nat(); at++)
            if (!src.shadow(at) && (allcell || inside[at])) {
                dst.add("",vector3<REALDST>::Zero());
                dst.set_fields(dst.nat()-1,v[at]);
              }
      }

    treat_crowd(dst,mode);

  }

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void fill( geometry<REALDST,CELLDST> & dst,
             const geometry<REALSRC,CELLSRC> & src,
             const shape<REALSRC> & shp,
             int mode = crowd_ignore | fill_atoms) {

    index begin, end;

    if (typeid(CELLSRC)==typeid(periodic_cell<REALSRC>)) {

        std::cout << "fillf:: alive1\n";

        // Minimal and maximal fractional coordinates of the shape
        periodic_cell<REALSRC> * cell = (periodic_cell<REALSRC>*)(&src.cell);
        vector3<REALSRC> Smin = shp.fmin(*cell),
            Smax = shp.fmax(*cell);

        std::cout << "Smin= " << Smin << " Smax= " << Smax << "\n";

        // Minimal and maximal fractional coordinates of atoms
        vector3<REALSRC> fmin,fmax;
        for (int at=0; at<src.nat(); at++) {
            vector3<REALSRC> f = src.coord(at);
            if (!src.frac) f = cell->cart2frac(f);
            if (at==0) fmin = fmax = f;
            else
              for (int i=0; i<3; i++) {
                  if (fmin[i]>f[i]) fmin[i] = f[i];
                  if (fmax[i]<f[i]) fmax[i] = f[i];
                }
          }

        std::cout << "fmin= " << fmin << " fmax= " << fmax << "\n";

        begin = {int(floor(Smin[0]-fmax[0])),
                 int(floor(Smin[1]-fmax[1])),
                 int(floor(Smin[2]-fmax[2]))};
        end   = {int(floor(Smax[0]-fmin[0])) + 1,
                 int(floor(Smax[1]-fmin[1])) + 1,
                 int(floor(Smax[2]-fmin[2])) + 1};

        std::cout << "begin= " << begin << " end= " << end << "\n";
      }
    else {
        begin = src.cell.begin();
        end   = src.cell.end();
      }

    fill(dst, src, shp, src.cell, begin, end, mode );

  }

  // -----------------------------------------------------------------------------------

  template<class REAL, class CELL>
  std::set<int> select( const geometry<REAL,CELL> & geom,
                        const shape<REAL> & shp) {
    return std::set<int>();
  }

  template<class REAL, class CELL, class REAL1, class CELL1>
  std::set<int> select( const geometry<REAL,CELL> & geom,
                        const geometry<REAL1,CELL1> & frag,
                        const bonding_table<REAL> & b) {
    return std::set<int>();
  }

  template<class REAL, class CELL, class REAL1, class CELL1>
  std::set<int> select( const geometry<REAL,CELL> & geom,
                        const geometry<REAL1,CELL1> & frag, REAL R) {
    bonding_table<REAL> b;
    b.default_distance = R;
    return select(geom,frag,b);
  }

  template<class REAL, class CELL>
  void selection_grow( std::set<int> & selection,
                       const neighbours_table<REAL,CELL> & ngbr) {

  }

  template<class REAL, class CELL>
  void selection_shrink( std::set<int> & selection,
                         const neighbours_table<REAL,CELL> & ngbr) {

  }

  /*
  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void replicate(geometry<REALDST,CELLDST> & dst,
                 const geometry<REALSRC,CELLSRC> & src,
                 const CELLSRC & cell)
  {
    replicate(dst,src,cell,cell.begin(),cell.end());
  }

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void replicate(geometry<REALDST,CELLDST> & dst,  const geometry<REALSRC,CELLSRC> & src)
  {
    replicate(dst,src,src.cell);
  }

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void replicate(geometry<REALDST,CELLDST> & dst,  const geometry<REALSRC,CELLSRC> & src,
                 const index & begin, const index& end)
  {
    replicate(dst,src,src.cell, begin, end);
  }

  */

  // -----------------------------------------------------------------------------

  template<class REAL, class UCELL, class NUCELL>
  void unique(std::vector<int> & n_images,
              geometry<REAL,UCELL> & ugeom,
              const geometry<REAL,NUCELL> & nugeom,
              const UCELL & group,
              const index & begin,
              const index & end,
              const std::function<REAL(const geometry<REAL,NUCELL> &, int)> & key,
              //[](const geometry<REAL,NUCELL> &g, int i) -> REAL
              //{ return std::sqrt(g.y[i]*g.y[i]+g.z[i]*g.z[i]); },
              REAL eps) {

    n_images.clear();
    ugeom.clear();

    std::vector<Bool> marked(nugeom.nat(), false);
    for (int i=0; i<nugeom.nat(); i++)
      if (!marked[i]){
          std::set<int> images = {i};
          marked[i] = true;

          for (iterator I(begin,end); !I.end(); I++) {
              vector3<REAL> r = group.transform(nugeom.pos(i),I);
              for (int j = 0; j<nugeom.nat(); j++)
                if (!marked[j])
                  if ( nugeom.atom(i)==nugeom.atom(j) && (r - nugeom.pos(j)).norm() < eps ) {
                      images.insert(j);
                      marked[j] = true;
                    }
            }
          int iuniq = i;
          for (int j : images)
            if ( key(nugeom,j) < key(nugeom, iuniq) )
              iuniq = j;
          ugeom.add(nugeom.atom(iuniq), nugeom.pos(iuniq));
          n_images.push_back(images.size());
        }

    std::cout << "n_images: ";
    for (int j: n_images)
      std::cout << " " << j;
    std::cout << "\n";

  }

  // -----------------------------------------------------------------------------

  template<class REAL, class UCELL, class NUCELL>
  void unique(std::vector<int> & n_images,
              geometry<REAL,UCELL> & ugeom,
              const geometry<REAL,NUCELL> & nugeom,
              const UCELL & group,
              const std::function<REAL(const geometry<REAL,NUCELL> &, int)> & key =
              [](const geometry<REAL,NUCELL> &g, int i) -> REAL
              {return std::sqrt(std::pow(g.pos(i)(1),2) + std::pow(g.pos(i)(2),2)); },
              REAL eps = geometry<REAL,NUCELL>::tol_geom_default) {
    unique(n_images, ugeom, nugeom, group, group.begin(), group.end(), key, eps);
  }

  template<class REAL, class UCELL, class NUCELL>
  void unique(std::vector<int> & n_images,
              geometry<REAL,UCELL> & ugeom,
              const geometry<REAL,NUCELL> & nugeom,
              const std::function<REAL(const geometry<REAL,NUCELL> &, int)> & key =
              [](const geometry<REAL,NUCELL> &g, int i) -> REAL
              {return std::sqrt(std::pow(g.pos(i)(1),2) + std::pow(g.pos(i)(2),2)); },
              REAL eps = geometry<REAL,NUCELL>::tol_geom_default) {
    unique(n_images, ugeom, nugeom, ugeom.cell, ugeom.cell.begin(), ugeom.cell.end(), key, eps );
  }

  template<class REAL, class UCELL, class NUCELL>
  void unique(geometry<REAL,UCELL> & ugeom,
              const geometry<REAL,NUCELL> & nugeom,
              const UCELL & group,
              const std::function<REAL(const geometry<REAL,NUCELL> &, int)> & key =
              [](const geometry<REAL,NUCELL> &g, int i) -> REAL
              { return std::sqrt(g.y[i]*g.y[i]+g.z[i]*g.z[i]); },
              REAL eps = geometry<REAL,NUCELL>::tol_geom) {
    std::vector<int> n_images;
    unique(n_images, ugeom, nugeom, group, group.begin(), group.end(), key, eps );
  }

  template<class REAL, class UCELL, class NUCELL>
  void unique(geometry<REAL,UCELL> & ugeom,
              const geometry<REAL,NUCELL> & nugeom,
              const std::function<REAL(const geometry<REAL,NUCELL> &, int)> & key =
              [](const geometry<REAL,NUCELL> &g, int i) -> REAL
              {return std::sqrt(std::pow(g.pos(i)(1),2) + std::pow(g.pos(i)(2),2)); },
              REAL eps = geometry<REAL,NUCELL>::tol_geom_default) {
    std::vector<int> n_images;
    unique(n_images, ugeom, nugeom, ugeom.cell, ugeom.cell.begin(), ugeom.cell.end(), key, eps );
  }

  // -----------------------------------------------------------------------------


#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void py_replicate1(geometry<REALDST,CELLDST> & dst,
                     const geometry<REALSRC,CELLSRC> & src,
                     const CELLSRC & cell,
                     const index & begin,
                     const index & end,
                     int mode)
  {  replicate(dst,src,cell,begin,end,mode); }

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void py_replicate2(geometry<REALDST,CELLDST> & dst,
                     const geometry<REALSRC,CELLSRC> & src,
                     const CELLSRC & cell,
                     const index & begin,
                     const index & end)
  {  replicate(dst,src,cell, begin, end, crowd_ignore); }

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void py_fill1( geometry<REALDST,CELLDST> & dst,
                 const geometry<REALSRC,CELLSRC> & src,
                 const shape<REALSRC> & shp, const CELLSRC & cell,
                 const index & begin, const index & end, int mode)
  {  fill(dst,src,shp,cell,begin,end,mode); }

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void py_fill2( geometry<REALDST,CELLDST> & dst,
                 const geometry<REALSRC,CELLSRC> & src,
                 const shape<REALSRC> & shp, int mode)
  {  fill(dst,src,shp,mode); }

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void py_fill3( geometry<REALDST,CELLDST> & dst,
                 const geometry<REALSRC,CELLSRC> & src,
                 const shape<REALSRC> & shp)
  {  fill(dst,src,shp); }

  template<class REAL, class UCELL, class NUCELL>
  void py_unique1(py::list & images,
                  geometry<REAL,UCELL> & ugeom,
                  const geometry<REAL,NUCELL> & nugeom,
                  const UCELL & group,
                  const index & begin,
                  const index & end,
                  const std::function<REAL(const geometry<REAL,NUCELL> &, int)> & key,
                  REAL eps) {
    std::vector<int>  n_images;
    unique(n_images, ugeom, nugeom, group, begin, end, key, eps);
    images.attr("clear")();
    for (const auto & n : n_images)
      images.append(n);
  }

  template<class REAL, class UCELL, class NUCELL>
  void py_unique2(py::list & images,
                  geometry<REAL,UCELL> & ugeom,
                  const geometry<REAL,NUCELL> & nugeom,
                  const UCELL & group,
                  const std::function<REAL(const geometry<REAL,NUCELL> &, int)> & key,
                  REAL eps) {
    std::vector<int>  n_images;
    unique(n_images, ugeom, nugeom, group, key, eps);
    images.attr("clear")();
    for (const auto & n : n_images)
      images.append(n);
  }

  template<class REAL, class UCELL, class NUCELL>
  void py_unique3(py::list & images,
                  geometry<REAL,UCELL> & ugeom,
                  const geometry<REAL,NUCELL> & nugeom,
                  const std::function<REAL(const geometry<REAL,NUCELL> &, int)> & key,
                  REAL eps) {
    std::vector<int>  n_images;
    unique(n_images, ugeom, nugeom, key, eps);
    images.attr("clear")();
    for (const auto & n : n_images)
      images.append(n);
  }

  template<class REAL, class UCELL, class NUCELL>
  void py_unique4(geometry<REAL,UCELL> & ugeom,
                  const geometry<REAL,NUCELL> & nugeom,
                  const UCELL & group,
                  const std::function<REAL(const geometry<REAL,NUCELL> &, int)> & key,
                  REAL eps)
  { unique(ugeom, nugeom, group, key, eps); }

  template<class REAL, class UCELL, class NUCELL>
  void py_unique5(geometry<REAL,UCELL> & ugeom,
                  const geometry<REAL,NUCELL> & nugeom,
                  const std::function<REAL(const geometry<REAL,NUCELL> &, int)> & key,
                  REAL eps)
  { unique(ugeom, nugeom, key, eps); }

  /*
  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void py_replicate3(geometry<REALDST,CELLDST> & dst,
                     const geometry<REALSRC,CELLSRC> & src,
                     const CELLSRC & cell,
                     int mode = crowd_ignore) {
    replicate(dst, src, cell, cell.begin(), cell.end(), mode);
  }

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void py_replicate3(geometry<REALDST,CELLDST> & dst,  const geometry<REALSRC,CELLSRC> & src,
                     int mode = crowd_ignore) {
    replicate(dst, src, src.cell, mode);
  }

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void py_replicate4(geometry<REALDST,CELLDST> & dst,  const geometry<REALSRC,CELLSRC> & src,
                     const index & begin, const index& end, int mode = crowd_ignore) {
    replicate(dst, src, src.cell, begin, end, mode);
  }
  */

#endif

}

#endif
