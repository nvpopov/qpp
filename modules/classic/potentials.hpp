#ifndef _QPP_POTENTIALS_H
#define  _QPP_POTENTIALS_H

#include <Eigen/Dense>
#include <geom/lace3d.hpp>
#include <data/types.hpp>
#include <geom/ngbr.hpp>

namespace qpp{
  
  template <class REAL> //, class CELL>
  class classical_potential{
  public:   


    /*
    template<class CELL>
    virtual REAL energy(const geometry<REAL,CELL> & g) const  =0;
    */

    std::vector<REAL> rmin, rmax;
    std::vector<STRING_EX> atyp;

    
    virtual REAL energy(const std::vector<vector3<REAL> > &) const  =0;

    /*
    virtual REAL energy_2b(REAL r) =0;
    virtual REAL energy_3b(const vector3<REAL> & r1,
			   const vector3<REAL> & r2,
			   const vector3<REAL> & r3)
    */

    virtual void grad(const std::vector<vector3<REAL> > &, std::vector<vector3<REAL> > &) const =0;

    virtual void d2e(const std::vector<vector3<REAL> > &, Eigen::Matrix<REAL, Eigen::Dynamic, Eigen::Dynamic> &) =0;
    
    // fixme - temporary
    virtual void load(ISTREAM &) =0;

    // debug
    virtual void debug(){}
    
  };

  // ---------------------- Pair potentials ------------------------

  template <class REAL>
  class pair_potential : public classical_potential<REAL>{
  public:
    
    using classical_potential<REAL>::rmin;
    using classical_potential<REAL>::rmax;
    
    virtual REAL e12(REAL r) const =0;
    
    virtual REAL de12(REAL r) const =0;

    virtual REAL energy( std::vector<vector3<REAL> > & r)
    {
      REAL r12 = (r[1] - r[0]).norm();
      if ( r12 >= rmin[0] && r12 <= rmax[0] )
	return e12(r12);
      else
	return 0e0;
    }

    virtual void grad( std::vector<vector3<REAL> > & r, std::vector<vector3<REAL> > & g)
    {
      REAL r12 = (r[1]-r[0]).norm();
      if ( r12 >= rmin[0] && r12 <= rmax[0] )
	g[0] = (r[1]-r[0])*de12(r12)/r12;
      else
        g[0] = vector3<REAL>(0e0);
    }
  
  };

  // ---------------------- 3-particle potentials ------------------------

  template <class REAL>
  class triple_potential : public classical_potential<REAL>{
  public:
    
    using classical_potential<REAL>::rmin;
    using classical_potential<REAL>::rmax;

    virtual REAL e123(REAL r12, REAL r13, REAL theta) const =0;
    
    virtual REAL de123(REAL r) const =0;

  };

  // --------------------- ------------------------

  template <class REAL>
  std::istream& operator>>(std::istream &is, pair_potential<REAL> &pp)
  {
    return pp.load(is);
  }  

};

#endif
