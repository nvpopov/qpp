#ifndef _QPP_ATOM_H
#define _QPP_ATOM_H

namespace qpp{

  template <class REAL>
  class atom{
  public:

    STRING name;
    int number;

    struct classical_block{
      REAL charge; // Effective charge
      REAL mass;   // Atomic mass
    };

    struct polarizible_block{
      REAL dipole; // dipole polarisibility
      REAL quadruple; // quadruple polarisibility
    };

    struct basis_block{
      STRING bas_name;
      // fixme
    };

    struct pseudo_block{
      STRING pseudo_name;
      // fixme
    };

    struct visible_block{
      REAL cov_rad;
      REAL vdw_rad;
      REAL ionic_rad;
      REAL red, green, blue, alpha;
    };

  private:
    classical_block * pclassic;
    polarizible_block * ppolar;
    basis_block * pbasis;
    pseudo_block * ppseudo;
    visible_block * pvisible;

  public:

    bool has_classic()
    { return pclassic != NULL; }

    bool has_polar()
    { return ppolar != NULL; }

    bool has_basis()
    { return pbasis != NULL; }

    bool has_pseudo()
    { return ppseudo != NULL; }

    bool has_visible()
    { return pvisible != NULL; }

    classical_block   & classic;
    polarizible_block & polar;
    basis_block       & basis;
    pseudo_block      & pseudo;
    visible_block     & visible;

    atom(const STRING & _name, int _number, bool _classic = false, bool _polar = false, 
	 bool _basis = false, bool _pseudo = false, bool _visible = false) :
      pclassic( _classic ? new classical_block : NULL), ppolar(_polar ? new polarizible_block : NULL), 
      pbasis( _basis ? new basis_block : NULL), ppseudo( _pseudo ? new pseudo_block : NULL), 
      pvisible( _visible ? new visible_block : NULL),
      classic(*pclassic), polar(*ppolar), basis(*pbasis), pseudo(*ppseudo), visible(*pvisible)
    {
      name = _name;
      number = _number;
    }

  };

};

#endif

