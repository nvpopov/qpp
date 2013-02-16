#ifndef _QPP_ATOM_H
#define _QPP_ATOM_H

#include <string>
#include <sstream>

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
    aprop_mendeleev_number = 0x0001,
    aprop_effective_charge = 0x0002,
    aprop_pair_potential   = 0x0004,
    aprop_3body_potential  = 0x0008,
    aprop_4body_potential =  0x0010,
    aprop_many_body_potential = 0x0020,

    aprop_classic_potentials = aprop_pair_potential | aprop_3body_potential | 
                              aprop_4body_potential | aprop_many_body_potential,   
    aprop_dipole_polarisible = 0x0040,
    aprop_gaussian_basis  = 0x0100,
    aprop_slater_basis    = 0x0200,
    aprop_tabulated_basis = 0x0400,
    aprop_ecp             = 0x1000,
    aprop_mcp             = 0x2000
  };

  // --------------------------------------------------
  // basic class for all other types of atoms
  class qpp_atom{
  public:

    // Atom always has a name
    // It is supposed to be unique for each type of atoms
    std::string name;
    int number; // Number in periodic table

    qpp_atom(std::string _name, int _number=0)
    {
      name=_name;
      number=_number;
    }

    qpp_atom(const qpp_atom & a)
    {
      name = a.name;
      number = a.number;
    }

    virtual int gettype() const
    {return aprop_mendeleev_number;}

    virtual bool operator==(const qpp_atom &a) const
    {
      return (gettype() == a.gettype()) && (name == a.name) && (number == a.number);
    }

    virtual std::string info() const
    {
      std::stringstream ss;
      ss << name << "{ number = " << number << "}";
      return ss.str();
    }

    virtual qpp_atom* copy() const
    {
      return new qpp_atom(*this);
    }

  };

  // -------------------------------------------------
  // Classical atoms
  class classical_atom : public qpp_atom{
  public:
    //fixme - should it be float?
    float charge; // Effective charge
    float mass;

    classical_atom(std::string _name, int _number=0, float _charge = 0e0, float _mass = 0e0) : 
      qpp_atom(_name,_number)
    {
      charge = _charge;
      mass   = _mass;
    }

    classical_atom(const classical_atom & a) :
      qpp_atom(a.name,a.number)
    {
      charge = a.charge;
      mass   = a.mass;
    }

    virtual int gettype() const
    {return aprop_mendeleev_number | aprop_effective_charge;}

    virtual bool operator==(const qpp_atom &a) const
    {
      bool res = (gettype() == a.gettype());
      if (res)
	{ const classical_atom *aa = (const classical_atom*)(&a);
	  res = name == aa->name && number == aa->number && 
	    charge == aa->charge && mass == aa->mass;
	}
      return res;
    }

    virtual std::string info() const
    {
      std::stringstream ss;
      ss << name << "{ number = " << number << "; charge = " << charge << "; mass = " << mass << "}";
      return ss.str();
    }

    virtual qpp_atom* copy() const
    {
      return new classical_atom(*this);
    }


  };

  class polarisible_atom : public classical_atom{
  public:
    float alpha; // polarisibility

    polarisible_atom(std::string _name, int _number=0, float _charge = 0e0, float _mass = 0e0, 
		     float _alpha=0e0) :
      classical_atom(_name,_number,_charge,_mass)
    {
      alpha  = _alpha;
    }

    polarisible_atom(const polarisible_atom & a) :
      classical_atom(a.name,a.number,a.charge,a.mass)
    {
      alpha  = a.alpha;
    }

    virtual int gettype() const
    {return aprop_mendeleev_number | aprop_effective_charge | aprop_dipole_polarisible;}

    virtual bool operator==(const qpp_atom &a) const
    {
      bool res = gettype() == a.gettype();
      if (res)
	{
	  const polarisible_atom * aa = (const polarisible_atom *)(&a);
	  res = name == aa->name && number == aa->number && charge == aa->charge && 
	    mass == aa->mass && alpha == aa->alpha;
	}
      return res;
    }

    virtual std::string info() const
    {
      std::stringstream ss;
      ss << name << "{ number = " << number << "; charge = " << charge << "; mass = " << mass 
	 << "; alpha= " << alpha << "}";
      return ss.str();
    }

    virtual qpp_atom* copy() const
    {
      return new polarisible_atom(*this);
    }    

  };

};

#endif
