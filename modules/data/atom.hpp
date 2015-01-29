#ifndef _QPP_ATOM_H
#define _QPP_ATOM_H

#include <string>
#include <sstream>
#include <data/qppdata.hpp>

namespace qpp{

  enum basis_set_types{
    gaussian,
    slater,
    tabulated,
    plane_waves,
    nobasis
  };

  //-------------- Atomic types ----------------------
  enum{
    aprop_mendeleev_number    = 0x0001,
    aprop_atomic_mass         = 0x0002,
    aprop_effective_charge    = 0x0004,
    aprop_pair_potential      = 0x0008,
    aprop_3body_potential     = 0x0010,
    aprop_4body_potential     = 0x0020,
    aprop_many_body_potential = 0x0040,

    aprop_classic_potentials  = aprop_pair_potential  | aprop_3body_potential | 
                                aprop_4body_potential | aprop_many_body_potential,   
    aprop_dipole_polarizible = 0x0100,
    aprop_gaussian_basis     = 0x0200,
    aprop_slater_basis       = 0x0400,
    aprop_tabulated_basis    = 0x1000,
    aprop_ecp                = 0x2000,
    aprop_mcp                = 0x4000,
    aprop_visible            = 0x8000
  };

  // --------------------------------------------------
  // basic class for all other types of atoms
  class qpp_atom : public qpp_object{

    // Atom always has a name
    // It is supposed to be unique for each type of atoms
    int _number; // Number in periodic table

  public:

    qpp_atom(STRING __name, qpp_object * __owner = NULL, int __number=0) : 
      qpp_object(__name, __owner)
    {
      _number=__number;
    }

    qpp_atom(const qpp_atom & a) :
      qpp_object(a.name(),a.owner())
    {
      _number=a._number;
    } 

    virtual int n_nested() const
    { return 0;}

    virtual qpp_object* nested(int i) const
    { return NULL;}

    virtual STRING category() const
    { return "atom";}

    int number() const
    { return _number;}

    virtual qppobject_type gettype() const
    { return qtype_atom; }

    virtual int atype() const
    {return aprop_mendeleev_number;}

    virtual void write(OSTREAM &os, int offset=0) const 
    {
      for (int i=0; i<offset; i++)
	os << " ";
      os << "atom " << _name << "{ number = " << _number << ";}";
    }

    virtual bool operator==(const qpp_atom &a) const
    {
      return (atype() == a.atype()) && (name() == a.name()) && (number() == a.number());
    }

    virtual qpp_atom* copy() const
    {
      return new qpp_atom(*this);
    }

  };

  // -------------------------------------------------
  /*
  std::string nameofatom(std::string at)
  {
    return at;
  }

  std::string nameofatom(qpp_atom * at)
  {
    return at -> name;
  }
  */
  // -------------------------------------------------
  // Classical atoms
  template<class REAL>
  class classical_atom : public qpp_atom{
    //fixme - should it be float?
    REAL _charge; // Effective charge
    REAL _mass;   // Atomic mass
  public:

    classical_atom(STRING __name, qpp_object * __owner = NULL, 
		   int __number=0, float __charge = 0e0, float __mass = 0e0) : 
      qpp_atom(__name,__owner,__number)
    {
      _charge = __charge;
      _mass   = __mass;
    }

    classical_atom(const classical_atom & a) :
      qpp_atom(a.name(),a.owner(),a.number())
    {
      _charge = a._charge;
      _mass   = a._mass;
    }

    REAL charge() const
    { return _charge;}

    REAL mass() const
    { return _mass;}

    virtual qppobject_type gettype() const
    { return qtype_atom | qtype_data<REAL>::type; }

    virtual int atype() const
    {return aprop_mendeleev_number | aprop_effective_charge | aprop_atomic_mass;}

    virtual bool operator==(const qpp_atom &a) const
    {
      bool res = (gettype() == a.gettype()) && (atype() == a.atype());
      if (res)
	{ const classical_atom *aa = (const classical_atom*)(&a);
	  res = name() == aa->name() && number() == aa->number() && 
	    charge() == aa->charge() && mass() == aa->mass();
	}
      return res;
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const 
    {
      for (int i=0; i<offset; i++)
	os << " ";
      os << "atom " << _name << "{\n";
      for (int i=0; i<offset+2; i++) os << " ";
      os << "number = " << number() << ";\n";
      for (int i=0; i<offset+2; i++) os << " ";
      os << "charge = " << charge() << ";\n";
      for (int i=0; i<offset+2; i++) os << " ";
      os << "mass = " << mass() << ";\n";
      for (int i=0; i<offset; i++) os << " ";
      os << "}\n";
    }

    virtual qpp_atom* copy() const
    {
      return new classical_atom(*this);
    }

  };

  // ---------------------------------------------------------------------

  template <class REAL>
  class polarizible_atom : public classical_atom<REAL>{
    REAL _alpha; // polarisibility
  public:

    using classical_atom<REAL>::gettype;
    using classical_atom<REAL>::name;
    using classical_atom<REAL>::number;
    using classical_atom<REAL>::mass;
    using classical_atom<REAL>::charge;

    polarizible_atom(STRING __name, qpp_object * __owner = NULL, 
		     int __number=0, float __charge = 0e0, float __mass = 0e0, 
		     REAL __alpha=0e0) :
      classical_atom<REAL>(__name,__owner,__number,__charge,__mass)
    {
      _alpha  = __alpha;
    }

    polarizible_atom(const polarizible_atom<REAL> & a) :
      classical_atom<REAL>(a.name(),a.owner(),a.number(),a.charge(),a.mass())
    {
      _alpha  = a.alpha();
    }

    virtual int atype() const
    {return aprop_mendeleev_number | aprop_effective_charge | 
	aprop_atomic_mass | aprop_dipole_polarizible;
    }

    REAL alpha() const
    { return _alpha;}

    virtual bool operator==(const qpp_atom &a) const
    {
      bool res = gettype() == a.gettype();
      if (res)
	{
	  const polarizible_atom<REAL> * aa = (const polarizible_atom<REAL> *)(&a);
	  res = name() == aa->name() && number() == aa->number() && charge() == aa->charge() && 
	    mass() == aa->mass() && alpha() == aa->alpha();
	}
      return res;
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const 
    {
      for (int i=0; i<offset; i++)
	os << " ";
      os << "atom " << name() << "{\n";
      for (int i=0; i<offset+2; i++) os << " ";
      os << "number = " << number() << ";\n";
      for (int i=0; i<offset+2; i++) os << " ";
      os << "charge = " << charge() << ";\n";
      for (int i=0; i<offset+2; i++) os << " ";
      os << "mass = " << mass() << ";\n";
      for (int i=0; i<offset+2; i++) os << " ";
      os << "alpha = " << alpha() << ";\n";
      for (int i=0; i<offset; i++) os << " ";
      os << "}\n";
    }

    virtual qpp_atom* copy() const
    {
      return new polarizible_atom(*this);
    }    

  };

  // -------------------------------------------------
  // Classical atoms
  class visible_atom : public qpp_atom{

  public:

    float cov_rad;
    float vdw_rad;
    float ionic_rad;
    float color[3];

    /*
    polarizible_atom(STRING __name, qpp_object * __owner = NULL, 
		     int __number=0, float __charge = 0e0, float __mass = 0e0, 
		     REAL __alpha=0e0) :
      classical_atom<REAL>(__name,__owner,__number,__charge,__mass)
    */
    visible_atom(STRING __name, qpp_object * __owner = NULL, 
		 int __number=0, float _cov_rad=0, float _vdw_rad=0, 
		 float _ionic_rad=0) : 
      qpp_atom(__name,__owner,__number)
    {
      cov_rad	= _cov_rad;	
      vdw_rad   = _vdw_rad;	
      ionic_rad = _ionic_rad; 
    }
    
    visible_atom(const visible_atom & a) :
      qpp_atom( a.name(), a.owner(),a.number() )
    {
      cov_rad	= a.cov_rad;	
      vdw_rad   = a.vdw_rad;	
      ionic_rad = a.ionic_rad; 
    }

    virtual qppobject_type gettype() const
    { return qtype_atom; }

    virtual int atype() const
    {return aprop_mendeleev_number | aprop_visible;}

    virtual bool operator==(const qpp_atom &a) const
    {
      bool res = (gettype() == a.gettype()) && (atype() == a.atype());
      if (res)
	{ const visible_atom *aa = (const visible_atom*)(&a);
	  res = name() == aa->name() && number() == aa->number() && 
	    cov_rad == aa->cov_rad && 
	    vdw_rad == aa->vdw_rad && 
	    ionic_rad == aa->ionic_rad;
	  // compare colors
	}
      return res;
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const 
    {
      for (int i=0; i<offset; i++)
	os << " ";
      os << "atom " << name() << "{\n";
      for (int i=0; i<offset+2; i++) os << " ";
      os << "number = " << number() << ";\n";
      for (int i=0; i<offset+2; i++) os << " ";
      os << "cov_rad = " << cov_rad << ";\n";
      for (int i=0; i<offset+2; i++) os << " ";
      os << "vdw_rad = " << vdw_rad << ";\n";
      for (int i=0; i<offset+2; i++) os << " ";
      os << "ionic_rad = " << ionic_rad << ";\n";
      //      for (int i=0; i<offset+2; i++) os << " ";
      //      os << "color = " << cov_rad << ";\n";
      for (int i=0; i<offset; i++) os << " ";
      os << "}\n";
    }

    virtual qpp_atom* copy() const
    {
      return new visible_atom(*this);
    }

  };

};

#endif
