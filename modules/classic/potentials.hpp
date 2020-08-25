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

    template<class CELL>
    virtual void energy_and_derivs(REAL & energy,
				   std::vector<vector3<REAL> > & grad, bool do_grad,
				   Eigen::Matrix<REAL, Eigen::Dynamic, Eigen::Dynamic> & d2e, bool do_d2e,
				   const geometry<REAL,CELL> & geom) const =0;
    
    template<class CELL>
    REAL energy(const geometry<REAL,CELL> & geom) const{
      REAL E = 0e0;
      std::vector<vector3<REAL> > empty_grad;
      Eigen::Matrix<REAL, Eigen::Dynamic, Eigen::Dynamic> empty_d2e;
      energy_and_derivs(E, empty_grad, false, empty_d2e, false, geom);
      return E;
    }

    template<class CELL>
    void grad(REAL & E, std::vector<vector3<REAL> > & G, const geometry<REAL,CELL> & geom) const{
      Eigen::Matrix<REAL, Eigen::Dynamic, Eigen::Dynamic> empty_d2e;
      energy_and_derivs(E, G, true, empty_d2e, false, geom);
    }

    template<class CELL>
    virtual void d2e(REAL & E, std::vector<vector3<REAL> > & G,
		     Eigen::Matrix<REAL, Eigen::Dynamic, Eigen::Dynamic> & D2E,
		     const geometry<REAL,CELL> & geom) const{
      energy_and_derivs(E, G, true, D2E, true, geom);
    }

    virtual bonding_table<REAL> distances() const =0;
    
    // fixme - temporary
    virtual void load(ISTREAM &) =0;

    // debug
    virtual void debug(){}
    
  };

  // ---------------------- Pair potentials ------------------------

  template <class REAL>
  class pair_potential : public classical_potential<REAL>{
  public:
        
    virtual REAL e12(REAL r) const =0;
    
    virtual REAL de12(REAL r) const =0;

    virtual REAL d2e12(REAL r) const =0;

    STRING_EX atom1, atom2;
    REAL rmax;

    template<class CELL>
    virtual void energy_and_derivs(REAL & energy,
				   std::vector<vector3<REAL> > & grad, bool do_grad,
				   Eigen::Matrix<REAL, Eigen::Dynamic, Eigen::Dynamic> & d2e, bool do_d2e,
				   const geometry<REAL,CELL> & geom) const
    {
      auto dt = disatnces();
      energy = 0e0;
      // fixme - no need to rebuild ngbr table for each potential
      neighbours_table<REAL,CELL> n(geom, dt);
      n.build();
      for (int i=0; i<geom.nat(); i++)
	if (geom.atom(i) == atom1)
	  for (int j=0; j<n.n(i); j++)
	    {
	      index k = n(i,j);
	      if (geom.atom(k)!=atom2)
		continue;
	      // fixme - what about periodic cells?
	      if (atom1==atom2 && i>k)
		continue;
	      vector3d<REAL> rvec = geom.pos(k) - geom.pos(i);
	      REAL r = rvec.norm();
	      energy += e12(r);
	      if (do_grad)
		{
		  REAL de = de12(r);
		  vector3d<REAL> devec = de*rvec/r;
		  grad[i] -= devec;
		  grad[k] += devec;
		  if (do_d2e)
		    {
		      
		    }
		}
	    }
    }
    
    template<class CELL>
    virtual void grad(REAL & E, std::vector<vector3<REAL> > & G, const geometry<REAL,CELL> & geom) const =0;

    template<class CELL>
    virtual void d2e(REAL & E, std::vector<vector3<REAL> > & G,
		     Eigen::Matrix<REAL, Eigen::Dynamic, Eigen::Dynamic> & D2E,
		     const geometry<REAL,CELL> & geom) const =0;

    virtual bonding_table<REAL> distances() const
    {
      bonding_table<REAL> b;
      b.set_pairt(atom1,atom2,rmax);
      return b;
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
