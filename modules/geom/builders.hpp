#ifndef _QPP_BUILDERS_H
#define _QPP_BUILDERS_H

#include <vector>
#include <cmath>
#include <symm/index.hpp>
#include <symm/symm.hpp>
#include <symm/cell.hpp>
#include <geom/geom.hpp>

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

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void replicate(geometry<REALDST,CELLDST> & dst, 
		 const geometry<REALSRC,CELLSRC> & src,
		 const CELLSRC & cell,
		 const index & begin,
		 const index & end)
  {
    for (int at = 0; at<src.nat(); at++)
      if (!src.shadow(at))
	{
	  std::vector<vector3d<REALSRC> > pt;
	  const STRING & a = src.atom(at);
	  const vector3d<REALSRC> & r = src.coord(at);

	  pt.push_back(r);

	  for (iterator I(begin,end); !I.end(); I++)
	    {
	      vector3d<REALSRC> r1 = cell.transform(r,I);
	      bool already = false;
	      for (const auto & p : pt)
		if (norm(p-r1) <= dst.tol_geom)
		  {
		    already = true;
		    break;
		  }

	      //std::cout << "r= " << r << " r1= " << r1 << " already= " << already << " tol=  " <<  dst.tol_geom << "\n";

	      if (!already)
		pt.push_back(r1);
	    }
	  for (const auto & p : pt)
	    dst.add(a,p.x(),p.y(),p.z());
	}
  }
	   

  template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
  void replicate(geometry<REALDST,CELLDST> & dst, 
		 const geometry<REALSRC,CELLSRC> & src,
		 const CELLSRC & cell)
  {
    replicate(dst,src,cell,cell.begin,cell.end);
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

};

#endif
