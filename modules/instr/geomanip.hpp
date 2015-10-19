#ifndef _QPP_GEOMANIP_H
#define _QPP_GEOMANIP_H

#include <geom/geom.hpp>
#include <geom/geom_extras.hpp>
#include <instr/shape.hpp>
#include <mathf/specfunc.hpp>

namespace qpp{

  enum{
    qmode_cellwise  = 0x001,
    qmode_atomwise  = 0x002,
    
    qmode_join      = 0x004,
    qmode_exclude   = 0x008,
    qmode_merge     = 0x010
  };

  // -----------------------------------------------------------------------------

  template<int DIM, int DIM2, class CREAL, class TRANSFORM, class TRANSFORM2>
  geometry<DIM,CREAL,TRANSFORM> * replicate(geometry<DIM2,CREAL,TRANSFORM2> & src,
	    TRANSFORM2 & cell, const qpp_shape<CREAL> & shape, 
	    int mode = qmode_merge | qmode_cellwise, 
	    CREAL close = 0.5e0)
  {
    bool atomwise = (mode & qmode_atomwise);
    bool exclude = (mode & qmode_exclude);
    bool join = (mode & qmode_join);
    bool sumcharge, xgeom;
    xtr_geometry<DIM2,CREAL,TRANSFORM2> * xrc = NULL;
    int ichrg;
    xgeom = src.gettype() & qtype_xgeometry;
    if (xgeom)
      {
	xrc = (xtr_geometry<DIM2,CREAL,TRANSFORM2> *)(&src);
	bool found = false;
	for (ichrg=0; ichrg < xrc->n_xreal(); ichrg++)
	  if (xrc->xreal_name(ichrg)=="charge")
	    {
	      found = true;
	      break;
	    }
	sumcharge = join && found;
      }

    std::cerr << "atomwise= " << atomwise << " exclude= " << exclude << " join= " << join 
	      << " sumcharge= " << sumcharge << " xgeom= " << xgeom << "\n";

    xtr_geometry<DIM,CREAL,TRANSFORM> * xres = NULL;
    geometry<DIM,CREAL,TRANSFORM> * res;
    if (xgeom)
      {
	res = xres = new xtr_geometry<DIM,CREAL,TRANSFORM>(xrc->n_xreal(), 
							 xrc->n_xint(), xrc->n_xbool());
	for (int j=0; j<xrc->n_xreal()+xrc->n_xint()+xrc->n_xbool(); j++)
	  xres->field_name(j) = xrc->field_name(j);
      }
    else
      res = new geometry<DIM,CREAL,TRANSFORM>;    

    TRANSFORM2 * symm = &cell;
    if (symm==NULL)
      symm = &(src.symm());
    if (symm==NULL)
      src.error("replicate: symmetry(vectors) not found",src.line(), src.file());

    // Replicate as is
    lace::simple_vector<CREAL, DIM2> f1 = shape.fmin(cell), f2 = shape.fmax(cell);
    index<DIM2> i1,i2;

    i1.atom() = 0;
    i2.atom() = src.nat()-1;

    for (int j=0; j<DIM2; j++)
      {
	i1.cell(j) = iround(f1(j))-1;
	i2.cell(j) = iround(f2(j))+1;
      }

    /*
    std::cerr << "min max frac: f1= " << f1 << " f2= " << f2 << " i1= " 
	      << i1 << " i2= " << i2 << std::endl;
    */
      
    typename geometry<DIM2,CREAL,TRANSFORM2>::iterator i(i1,i2);
    
    src.setsymm(cell);
    
    for (i=i.begin(); i!=i.end(); i++)
      {
	bool within = false;
	lace::vector3d<CREAL> r = src.position(i);
	if (atomwise && shape.within(r))
	  within = true;
	if (!atomwise && shape.within(cell.transform(lace::vector3d<CREAL>(0e0),i)))
	  within = true;

	/*
	std::cerr << " i= " << i << " r= " << r << " |r|= " 
	<< r.norm() << " within= " << within << std::endl;
	*/

	if (within)
	  {
	    res->add(src.atom(i),r);
	    if (xgeom)
	      {
		int n = res->nat()-1;
		for (int j = 0; j<xrc->n_xreal(); j++)
		  xres->xtr_real(j,n) = xrc->xtr_real(j,i);
		for (int j = 0; j<xrc->n_xint(); j++)
		  xres->xtr_int(j,n) = xrc->xtr_int(j,i);
		for (int j = 0; j<xrc->n_xbool(); j++)
		  xres->xtr_bool(j,n) = xrc->xtr_bool(j,i);
	      }
	  }
	
      }
    
    res->build_type_table();

    // Check for atom which are too close

    if (exclude || sumcharge)
      {
	
	typename geometry<DIM,CREAL,TRANSFORM>::neighbours_table crowd(*res);
	
	crowd.default_distance = close;
	crowd.set_grain_size(2.5);
	//crowd.reference_mode = true;
	crowd.build_disttable();
	crowd.build();
	//	res->add_dependent(&crowd);
	
	std::vector<bool> todel(res->nat(),false);

	for (int i=0; i<res->nat(); i++)
	  if ( !todel[i] ) 
	    {
	      std::cerr << "i= " << i << " r= " << res->atom(i)<<res->coord(i) << std::endl;
	    for (int j=0; j<crowd.n(i); j++)
	      {
		int k = crowd(i,j);
		todel[k] = true;
		if (sumcharge && res->atom(i) == res->atom(k))
		  xres->xtr_real(ichrg,i) += xres->xtr_real(ichrg,k);
		//res->erase(k);

		std::cerr << "  todel " << k << " r= " << res->atom(k)<<res->coord(k) << std::endl;
	      }
	    }

	for (int i=res->nat()-1; i>=0; i--)
	  if (todel[i])
	    {
	      res->erase(i);
	      todel.erase(todel.begin()+i);
	    }
      }

    return res;
    
  }

  // -----------------------------------------------------------------------
  
  template< int DIM, class CREAL, class TRANSFORM>
  void concat(geometry<DIM,CREAL,TRANSFORM> & g1, const geometry<DIM,CREAL,TRANSFORM> & g2)
  {
    typename geometry<DIM,CREAL,TRANSFORM>::neighbours_table crowd(g1);
  }

  // -----------------------------------------------------------------------

  template < int DIM, class CREAL, class TRANSFORM>
  void replace(geometry<DIM,CREAL,TRANSFORM> & geom, const qpp_shape<CREAL> & shape, 
	       const STRING & at1, const STRING & at2)
  // Replace one atom type with another one
  {
    for (int i = 0; i<geom.nat(); i++)
      if ( geom.atom(i) == at1 && shape.within(geom.coord(i)) )
	geom.atom(i) = at2;
  }

  // -----------------------------------------------------------------------
  
  template < int DIM, class CREAL, class TRANSFORM>
  void replace(geometry<DIM,CREAL,TRANSFORM> & g1, const geometry<DIM,CREAL,TRANSFORM> & g2)
  // Replace 
  {
    
  }

};

#endif
