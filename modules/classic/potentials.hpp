#ifndef _QPP_POTENTIALS_H
#define  _QPP_POTENTIALS_H

#include <Eigen/Dense>
#include <geom/lace3d.hpp>
#include <data/types.hpp>
#include <geom/ngbr.hpp>

namespace qpp{
  
  template <class REAL>
  class classical_potential{
  public:
    // number of particles
    int N;

    std::vector<REAL> rmin, rmax;
    std::vector<STRING> atyp;
    
    virtual REAL energy(const std::vector<vector3d<REAL> > &) const  =0;

    virtual void grad(const std::vector<vector3d<REAL> > &, std::vector<vector3d<REAL> > &) const =0;

    virtual void d2e(const std::vector<vector3d<REAL> > &, Eigen::Matrix<REAL, Eigen::Dynamic, Eigen::Dynamic> &) =0;
    
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

    virtual REAL energy( std::vector<vector3d<REAL> > & r)
    {
      REAL r12 = norm(r[1] - r[0]);
      if ( r12 >= rmin[0] && r12 <= rmax[0] )
	return e12(r12);
      else
	return 0e0;
    }

    virtual void grad( std::vector<vector3d<REAL> > & r, std::vector<vector3d<REAL> > & g)
    {
      REAL r12 = norm(r[1]-r[0]);
      if ( r12 >= rmin[0] && r12 <= rmax[0] )
	g[0] = (r[1]-r[0])*de12(r12)/r12;
      else
	g[0] = vector3d<REAL>(0e0);
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
