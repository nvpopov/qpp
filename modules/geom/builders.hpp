#ifndef _QPP_BUILDERS_H
#define _QPP_BUILDERS_H

#include <vector>
#include <cmath>
#include <symm/index.hpp>
#include <symm/symm.hpp>
#include <symm/cell.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/shape.hpp>
#include <geom/ngbr.hpp>
#include <mathf/math.hpp>

namespace qpp{

  enum build_mode{

    // ignore the situation when two or more atoms are put too close ("crowded") - simply put them into crowd
    crowd_ignore  = 0x00001,

    // do not put another atom too close to already existing atom - omit it
    crowd_exclude = 0x00002,

    // merge atoms of the same type placed in same point into one atom by summation of their electric charges and masses,
    // i.e. atoms are considered as "fractions" 
    crowd_merge   = 0x00004,

    // When filling a volume of certain geometric shape, omit all atoms outside that volume
    fill_atoms    = 0x00008,

    // When filling a volume of certain geometric shape, put entire unit cell if the centre of 
    // this cell is inside that volume
    fill_cells    = 0x00010
  };

  template<class REAL, class CELL>
  void treat_crowd(geometry<REAL,CELL> & geom, int mode)
  {
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
	  todel[n(i,j)] = i;
    
    xgeometry<REAL,CELL> *xgeom = dynamic_cast<xgeometry<REAL,CELL>*>(&geom); 
    bool merge = (mode & crowd_merge) && xgeom!=NULL;

    if (merge)
      for (int i=geom.nat()-1; i>=0; i--)
	if (todel[i]>-1)
	  {
	    int j=todel[i];
	    for (int k=0; k<xgeom->nfields(); k++)
	      if (xgeom->additive(k))
		{
		  if (xgeom->field_type(k) == type_int)
		    xgeom->template xfield<int>(k,j)  += xgeom->template xfield<int>(k,i);
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
  void replicate(geometry<REALDST,CELLDST> & dst, 
		 const geometry<REALSRC,CELLSRC> & src,
		 const CELLSRC & cell,
		 const index & begin,
		 const index & end,
		 int mode = crowd_ignore)
  {
    bool xcopy = dst.is_xgeometry() && src.is_xgeometry();
    xgeometry<REALDST,CELLDST> *xdst = NULL;
    xgeometry<REALSRC,CELLSRC> *xsrc = NULL;

    std::vector<STRING> fn;
    std::vector<basic_types> ft;

    if (src.is_xgeometry())
      xsrc = (xgeometry<REALSRC,CELLSRC>*)(&src);

    if (dst.is_xgeometry())
      {
	xdst = (xgeometry<REALDST,CELLDST>*)(&dst);
	if (src.is_xgeometry())
	  {
	    xsrc->get_format(fn,ft);
	    xdst->set_format(fn,ft);
	  }
	else
	  xdst->set_format({"atom","x","y","z"},{type_string,type_real,type_real,type_real});
      }

    int ix,iy,iz;
    if (xsrc!=NULL)
      for (int i=0; i<xsrc->nfields(); i++)
	{
	  if (fn[i]=="x")
	    ix = i;
	  else if (fn[i]=="y")
	    iy = i;
	  else if (fn[i]=="z")
	    iz = i;
	}
    else
      {
	ix = 1; iy=2; iz=3;
      }

    if (xcopy)
      for (int at = 0; at<src.nat(); at++)
	{
	  if (!src.shadow(at))
	    {
	      std::vector<datum> v;
	      src.get_fields(at,v);
	      const vector3d<REALSRC> & r = src.coord(at);
	      vector3d<REALSRC> r1;
	      v[ix].set(&r1(0));
	      v[iy].set(&r1(1));
	      v[iz].set(&r1(2));
	      for (iterator I(begin,end); !I.end(); I++)
		{
		  // fixme - to be replaced with dst.add_fields(v)
		  dst.add("",vector3d<REALDST>(0));
		  r1 = cell.transform(r,I);
		  dst.set_fields(dst.nat()-1,v);
		}
	    }    
	}
    else
      for (int at = 0; at<src.nat(); at++)
	if (!src.shadow(at))
	  {
	    const STRING & a = src.atom(at);
	    const vector3d<REALSRC> & r = src.coord(at);
	    for (iterator I(begin,end); !I.end(); I++)
	      {
		vector3d<REALSRC> r1 = cell.transform(r,I);
		dst.add(a,(vector3d<REALDST>)r1);
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
	     int mode = crowd_ignore | fill_atoms)
  {
    bool xcopy = dst.is_xgeometry() && src.is_xgeometry();
    xgeometry<REALDST,CELLDST> *xdst = NULL;
    xgeometry<REALSRC,CELLSRC> *xsrc = NULL;

    std::vector<STRING> fn;
    std::vector<basic_types> ft;

    if (src.is_xgeometry())
      xsrc = (xgeometry<REALSRC,CELLSRC>*)(&src);

    if (dst.is_xgeometry())
      {
	xdst = (xgeometry<REALDST,CELLDST>*)(&dst);
	if (src.is_xgeometry())
	  {
	    xsrc->get_format(fn,ft);
	    xdst->set_format(fn,ft);
	  }
	else
	  xdst->set_format({"atom","x","y","z"},{type_string,type_real,type_real,type_real});
      }

    int ix,iy,iz;
    if (xsrc!=NULL)
      for (int i=0; i<xsrc->nfields(); i++)
	{
	  if (fn[i]=="x")
	    ix = i;
	  else if (fn[i]=="y")
	    iy = i;
	  else if (fn[i]=="z")
	    iz = i;
	}
    else
      {
	ix = 1; iy=2; iz=3;
      }

    std::vector<std::vector<datum> > v(src.nat());
    std::vector<vector3d<REALSRC> > r1(src.nat());
    for (int at=0; at<src.nat(); at++)
      {
	src.get_fields(at,v[at]);
	v[at][ix].set(&r1[at][0]);
	v[at][iy].set(&r1[at][1]);
	v[at][iz].set(&r1[at][2]);
      }

    bool fillcells = mode & fill_cells;

    for (iterator I(begin,end); !I.end(); I++)
      {
	bool allcell = false, something = false;
	bool * inside = new bool[src.nat()];
	for (int at=0; at<src.nat(); at++)
	  {
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
	    if (!src.shadow(at) && (allcell || inside[at]))
	      {
		dst.add("",vector3d<REALDST>(0));
		dst.set_fields(dst.nat()-1,v[at]);		
	      }
      }    

    treat_crowd(dst,mode);
  }

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void fill( geometry<REALDST,CELLDST> & dst, const geometry<REALSRC,CELLSRC> & src,
	     const shape<REALSRC> & shp, int mode = crowd_ignore | fill_atoms)
  {
    index begin, end;
    if (typeid(CELLSRC)==typeid(periodic_cell<REALSRC>))
      {
	// Minimal and maximal fractional coordinates of the shape
	periodic_cell<REALSRC> * cell = (periodic_cell<REALSRC>*)(&src.cell);
	vector3d<REALSRC> Smin = shp.fmin(*cell),
	  Smax = shp.fmax(*cell);
	// Minimal and maximal fractional coordinates of atoms
	vector3d<REALSRC> fmin,fmax;
	for (int at=0; at<src.nat(); at++)
	  {
	    vector3d<REALSRC> f = src.coord(at);
	    if (!src.frac) f = cell->cart2frac(f);
	    if (at==0)
	      fmin = fmax = f;
	    else
	      for (int i=0; i<3; i++)
		{
		  if (fmin[i]>f[i])
		    fmin[i] = f[i];
		  if (fmax[i]<f[i])
		    fmax[i] = f[i];
		}
	  }
	begin = {floor(Smin[0]-fmax[0]),     floor(Smin[1]-fmax[1]),     floor(Smin[2]-fmax[2])};
	end   = {floor(Smax[0]-fmin[0]) + 1, floor(Smax[1]-fmin[1]) + 1, floor(Smax[2]-fmin[2]) + 1};
      }
    else
      {
	begin = src.cell.begin();
	end   = src.cell.end();
      }
    fill(dst, src, shp, src.cell, src.cell.begin(), src.cell.end() );
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
  void py_fill1( geometry<REALDST,CELLDST> & dst, const geometry<REALSRC,CELLSRC> & src,
		 const shape<REALSRC> & shp, const CELLSRC & cell,
		 const index & begin, const index & end, int mode)
  {  fill(dst,src,shp,cell,begin,end,mode); }

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void py_fill2( geometry<REALDST,CELLDST> & dst, const geometry<REALSRC,CELLSRC> & src,
		 const shape<REALSRC> & shp, int mode)
  {  fill(dst,src,shp,mode); }

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void py_fill3( geometry<REALDST,CELLDST> & dst, const geometry<REALSRC,CELLSRC> & src,
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

};

#endif
