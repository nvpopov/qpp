#ifndef QPP_BUILDERS_H
#define QPP_BUILDERS_H
#pragma GCC diagnostic ignored "-Wnarrowing"
#include <vector>
#include <cmath>
#include <symm/index.hpp>
#include <symm/groups.hpp>
#include <symm/cell.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/shape.hpp>
#include <geom/ngbr.hpp>
#ifdef PY_EXPORT
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#endif

namespace qpp{

  //!\brief the flags regulating the details of building procedures
  enum build_mode{

    //!\brief ignore the situation when two or more atoms are put too close ("crowded") - simply put them into crowd
    crowd_ignore  = 0x00001,

    //!\brief do not put another atom too close to already existing atom
    //! - omit it
    crowd_exclude = 0x00002,

    /*!\brief merge atoms of the same type placed in same point into one atom
      by summation of their electric charges and masses,
      i.e. atoms are considered as "fractions"
    */
    crowd_merge   = 0x00004,

    //!\brief When filling a volume of certain geometric shape, omit all
    //!  atoms outside that volume
    fill_atoms    = 0x00008,

    /*!\brief When filling a volume of certain geometric shape, put all atoms unit cell if the centre of
      this cell is inside that volume (even if some atoms are outside)
    */
    fill_cells    = 0x00010
  };

  template<class REAL, class CELL>
  void treat_crowd(geometry<REAL,CELL> & geom, int mode){
    if (mode & crowd_ignore)
      return;

    bonding_table<REAL> b;
    b.default_distance = geom.tol_geom;
    neighbours_table<REAL,CELL> n(geom,b);
    n.build();
    int todel[geom.nat()];
    for (int i=0; i<geom.nat(); i++)
      todel[i] = -1;
    for (int i=0; i<geom.nat(); i++)
      if ( todel[i]==-1 && n.n(i)>0)
        for (int j=0; j<n.n(i); j++)
          if (geom.atom(i)==geom.atom(j))
            todel[n(i,j)] = i;

    xgeometry<REAL,CELL> *xgeom = dynamic_cast<xgeometry<REAL,CELL>*>(&geom);
    bool merge = (mode & crowd_merge) && xgeom!=NULL;

    if (merge)
      for (int i=geom.nat()-1; i>=0; i--)
        if (todel[i]>-1){
            int j=todel[i];
            for (int k=0; k<xgeom->nfields(); k++)
              if (xgeom->additive(k)){
                  if (xgeom->field_type(k) == type_int)
                    xgeom->template xfield<int>(k,j)  +=
                        xgeom->template xfield<int>(k,i);
                  else if (xgeom->field_type(k) == type_real)
                    xgeom->template xfield<REAL>(k,j) +=
                        xgeom->template xfield<REAL>(k,i);
                }
          }

    for (int i=geom.nat()-1; i>=0; i--)
      if (todel[i]>-1)
        geom.erase(i);

  }


  // ----------------------------------------------------------------------------

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void copy_header(geometry<REALDST,CELLDST> & dst,
                   const geometry<REALSRC,CELLSRC> & src){

    xgeometry<REALDST,CELLDST> *xdst = NULL;
    xgeometry<REALSRC,CELLSRC> *xsrc = NULL;

    std::vector<STRING> fn;
    std::vector<basic_types> ft;

    if (src.is_xgeometry())
      xsrc = (xgeometry<REALSRC,CELLSRC>*)(&src);

    if (dst.is_xgeometry()){
        xdst = (xgeometry<REALDST,CELLDST>*)(&dst);
        if (src.is_xgeometry())
          {
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

    xgeometry<REALSRC,CELLSRC> *xsrc = NULL;
    if (src.is_xgeometry())
      xsrc = (xgeometry<REALSRC,CELLSRC>*)(&src);

    int ix,iy,iz;
    if (xsrc!=NULL)
      for (int i=0; i < xsrc->nfields(); i++) {
          STRING fn = xsrc -> field_name(i);
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
             int mode = crowd_ignore | fill_atoms){
    bool xcopy = dst.is_xgeometry() && src.is_xgeometry();

    copy_header(dst,src);
    xgeometry<REALSRC,CELLSRC> *xsrc = NULL;
    if (src.is_xgeometry())
      xsrc = (xgeometry<REALSRC,CELLSRC>*)(&src);

    int ix,iy,iz;
    if (xsrc!=NULL)
      for (int i=0; i<xsrc->nfields(); i++){
          STRING fn = xsrc -> field_name(i);
          if (fn=="x")
            ix = i;
          else if (fn=="y")
            iy = i;
          else if (fn=="z")
            iz = i;
        }
    else{
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

    bool fillcells = mode & fill_cells;

    for (iterator I(begin,end); !I.end(); I++){
        bool allcell = false, something = false;
        bool * inside = new bool[src.nat()];
        for (int at=0; at<src.nat(); at++){
            r1[at] = cell.transform(src.coord(at),I);
            bool insd = !src.shadow(at) && shp.within(r1[at]);
            inside[at] = insd;
            if (insd)
              something = true;
            if (fillcells && insd)
              allcell = true;
          }
        if (something)
          for (int at=0; at<src.nat(); at++)
            if (!src.shadow(at) && (allcell || inside[at])){
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
             int mode = crowd_ignore | fill_atoms){
    index begin, end;
    if (typeid(CELLSRC)==typeid(periodic_cell<REALSRC>)){

        std::cout << "fillf:: alive1\n";

        // Minimal and maximal fractional coordinates of the shape
        periodic_cell<REALSRC> * cell = (periodic_cell<REALSRC>*)(&src.cell);
        vector3<REALSRC> Smin = shp.fmin(*cell),
            Smax = shp.fmax(*cell);

        std::cout << "Smin= " << Smin << " Smax= " << Smax << "\n";

        // Minimal and maximal fractional coordinates of atoms
        vector3<REALSRC> fmin,fmax;
        for (int at=0; at<src.nat(); at++){
            vector3<REALSRC> f = src.coord(at);
            if (!src.frac) f = cell->cart2frac(f);
            if (at==0)
              fmin = fmax = f;
            else
              for (int i=0; i<3; i++){
                  if (fmin[i]>f[i])
                    fmin[i] = f[i];
                  if (fmax[i]<f[i])
                    fmax[i] = f[i];
                }
          }

        std::cout << "fmin= " << fmin << " fmax= " << fmax << "\n";

        begin = {floor(Smin[0]-fmax[0]),
                 floor(Smin[1]-fmax[1]),
                 floor(Smin[2]-fmax[2])};
        end   = {floor(Smax[0]-fmin[0]) + 1,
                 floor(Smax[1]-fmin[1]) + 1,
                 floor(Smax[2]-fmin[2]) + 1};

        std::cout << "begin= " << begin << " end= " << end << "\n";
      }
    else{
        begin = src.cell.begin();
        end   = src.cell.end();
      }
    fill(dst, src, shp, src.cell, begin, end, mode );
  }

  // -----------------------------------------------------------------------------------

  template<class REAL, class CELL>
  std::set<int> select( const geometry<REAL,CELL> & geom,
                        const shape<REAL> & shp){

  }

  template<class REAL, class CELL, class REAL1, class CELL1>
  std::set<int> select( const geometry<REAL,CELL> & geom,
                        const geometry<REAL1,CELL1> & frag,
                        const bonding_table<REAL> & b){

  }

  template<class REAL, class CELL, class REAL1, class CELL1>
  std::set<int> select( const geometry<REAL,CELL> & geom,
                        const geometry<REAL1,CELL1> & frag, REAL R){
    bonding_table<REAL> b;
    b.default_distance = R;
    select(geom,frag,b);
  }

  template<class REAL, class CELL>
  void extend( std::set<int> & selection,
               const neighbours_table<REAL,CELL> & ngbr){

  }

  template<class REAL, class CELL>
  void shrink( std::set<int> & selection,
               const neighbours_table<REAL,CELL> & ngbr){

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

#ifdef PY_EXPORT

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

  /*
  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void py_replicate3(geometry<REALDST,CELLDST> & dst,
                     const geometry<REALSRC,CELLSRC> & src,
                     const CELLSRC & cell,
                     int mode = crowd_ignore)
  {
    replicate(dst, src, cell, cell.begin(), cell.end(), mode);
  }

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void py_replicate3(geometry<REALDST,CELLDST> & dst,  const geometry<REALSRC,CELLSRC> & src,
                     int mode = crowd_ignore)
  {
    replicate(dst, src, src.cell, mode);
  }

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void py_replicate4(geometry<REALDST,CELLDST> & dst,  const geometry<REALSRC,CELLSRC> & src,
                     const index & begin, const index& end, int mode = crowd_ignore)
  {
    replicate(dst, src, src.cell, begin, end, mode);
  }
  */

#endif

}

#endif
