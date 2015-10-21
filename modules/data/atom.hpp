#ifndef _QPP_ATOM_H
#define _QPP_ATOM_H

#include <string>
#include <sstream>
#include <data/qppdata.hpp>
#include <basis/basis.hpp>
#include <io/compile.hpp>

namespace qpp{

  /*
  enum basis_set_types{
    gaussian,
    slater,
    tabulated,
    plane_waves,
    nobasis
  };
  */

  //-------------- Atomic types ----------------------
  enum{
    aprop_mendeleev_number    = 0x0001,
    aprop_atomic_mass         = 0x0002,
    aprop_effective_charge    = 0x0004,
    aprop_pair_potential      = 0x0008,
    aprop_3body_potential     = 0x0010,
    aprop_4body_potential     = 0x0020,
    aprop_many_body_potential = 0x0040,

    aprop_classical_potentials  = aprop_pair_potential  | aprop_3body_potential | 
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
  template<class REAL, qpp_bastype BT>
  void _list_shells(qpp_object * bas, std::vector<qpp_shell<BT,REAL>*>  & shells)
  {
    qpp_basis_data<BT,REAL> * basis = (qpp_basis_data<BT,REAL> *)bas;
    // Check there is no "center" declarations in basis
    bool OK = true;
    if (basis -> n_rcrd() != 1)
      OK = false;
    if (OK)
      if (basis->rcrd(0).labels.size()!=0 || basis->rcrd(0).numbers.size()!=0)
	OK = false;

    if (!OK)
      bas -> error("Basis declaration inside atom declaration cannot contain \"center\" specification",
		   bas ->line(), bas->file());
    for (int i=0; i<basis->rcrd(0).shells.size(); i++)
      shells.push_back( &(basis->rcrd(0).shells[i]) );
  }

  // --------------------------------------------------
  // basic class for all other types of atoms
  template<class REAL>
  class qpp_atom : public qpp_declaration{

  public:

    // Atom always has a name
    // It is supposed to be unique for each type of atoms
    int number; // Number in periodic table
    bool freeze; // If the atom is just frozen point charge

    struct classical_block{
      REAL charge; // Effective charge
      REAL mass;   // Atomic mass
    };

    struct polarizible_block{
      REAL alpha; // polarisibility
    };

    struct basis_block{
      STRING bas_name;
      qpp_object * basis;
      qpp_bastype bastype;
      // only one of the following arrays can be not empty
      std::vector<qpp_shell<qbas_gauss,REAL>*>  gauss_shells;
      std::vector<qpp_shell<qbas_slater,REAL>*> slater_shells;
      std::vector<qpp_shell<qbas_siesta,REAL>*> siesta_shells;
      std::vector<qpp_shell<qbas_pw,REAL>*>     pw_shells;
    };

    struct pseudo_block{
      STRING pseudo_name;
    };

    struct visible_block{
      REAL cov_rad;
      REAL vdw_rad;
      REAL ionic_rad;
      REAL red, green, blue, alpha;
    };

    classical_block   * classical;
    polarizible_block * polarizible;
    basis_block       * basis;
    pseudo_block      * pseudo;
    visible_block     * visible;

    qpp_atom(STRING __name, qpp_object * __owner = NULL, int __number=0) : 
      qpp_declaration("atom",__name, __owner)
    {
      number = __number;      
      add( * new qpp_parameter<int>("number",&number,this) );

      classical   = NULL;
      polarizible = NULL;
      basis       = NULL;
      pseudo      = NULL;
      visible     = NULL;
    }

    qpp_atom(qpp_declaration * d) :
      qpp_declaration("atom", d->name(), d->owner(), NULL, d->line(), d->file())
    {
      //debug
      std::cerr << "entering atom constructor\n-----------------------------\n";
      d -> write(std::cerr);
      std::cerr << "--------------------------------------\n";
      
      qpp_parameter<int> *pnumber;
      pnumber = d -> parameter<int>("number");
      if (pnumber != NULL)
	number = pnumber -> value();
      else 
	number = 0;

      add( * new qpp_parameter<int>("number",&number,this) );

      qpp_parameter<bool> * pfreeze = d -> parameter<bool>("freeze");
      if (pfreeze != NULL)
	freeze = pfreeze -> value();
      else
	freeze = false;

      // fixme - freeze is mutually exclusive with the most of other properties

      //debug
      //std::cerr << "atom constr: after parameter<int>(number)\n";

      //debug
      //std::cerr << "atom constr alive 1\n";

      // Classical properties
      qpp_parameter<double> * pcharge, * pmass;
      pcharge = d -> parameter<double>("charge");
      pmass   = d -> parameter<double>("mass");

      if (pcharge != NULL || pmass != NULL)
	{
	  classical = new classical_block;

	  std::cout << "cl found &&&&&&&&\n";

	  if (pcharge != NULL)
	    classical -> charge = pcharge -> value();
	  else
	    classical -> charge = 0e0;

	  if (pmass != NULL)
	    classical -> mass = pmass -> value();
	  else
	    classical -> mass = 0e0;

	  add(* new qpp_parameter<REAL>("charge", &(classical->charge), this));
	  add(* new qpp_parameter<REAL>("mass", &(classical->mass), this));
	}
      //debug
      //std::cerr << "atom constr alive 2\n";

      // Polarizible properties
      qpp_parameter<double> * palpha = d -> parameter<double>("alpha");
      if (palpha != NULL)
	{
	  polarizible = new polarizible_block;
	  polarizible -> alpha = palpha -> value();
	  add(* new qpp_parameter<REAL>("alpha", &(polarizible->alpha), this));
	}
      //debug
      //std::cerr << "atom constr alive 3\n";

      // Basis data
      qpp_object * pbasis = d -> find1("basis", qtype_all, qscope_local);
      // fixme - compilation sequence and possible types here
      bool bas_name_found = false, basis_found = false;

      if (pbasis != NULL)
	{
	  //pbasis = qpp_compile(pbasis);

	  //debug
	  std::cerr << "--- atom: basis found ------\n";
	  pbasis ->write(std::cerr);	  

	  bas_name_found = pbasis -> gettype() == ( qtype_parameter | qtype_data_string );
	  basis_found = pbasis -> gettype() & ( qtype_basis | qtype_data<REAL>::type);

	  std::cerr << "basname= " << bas_name_found << " basis found= " << basis_found << "\n";
	  std::cerr << std::hex << pbasis -> gettype() << std::dec << "\n";
	}

      if (bas_name_found)
	{
	  basis = new basis_block;
	  basis -> bas_name = ((qpp_parameter<STRING>*)pbasis) -> value();
	  add(* new qpp_parameter<STRING>("basis", &(basis->bas_name), this));
	  basis -> basis = NULL;
	}
      else if (basis_found)
	{
	  basis = new basis_block;
	  basis -> basis = pbasis -> copy();
	  add(*basis->basis);
	  if ( pbasis-> gettype() & qtype_basis_gauss)
	    {
	      basis -> bastype = qbas_gauss;
	      _list_shells<REAL,qbas_gauss>(basis->basis, basis->gauss_shells);
	    }
	  else if (pbasis->gettype() & qtype_basis_slater)
	    {
	      basis -> bastype = qbas_slater;
	      _list_shells<REAL,qbas_slater>(basis->basis, basis->slater_shells);
	    }
	  else if (pbasis->gettype() & qtype_basis_siesta)
	    {
	      basis -> bastype = qbas_siesta;
	      //_list_shells<REAL,qbas_siesta>(basis->basis, basis->siesta_shells);
	    }
	  else if (pbasis->gettype() & qtype_basis_pw)
	    {
	      basis -> bastype = qbas_pw;
	      //_list_shells<REAL,qbas_pw>(basis->basis, basis->pw_shells);
	    }
	}
      //debug
      //std::cerr << "atom constr alive 4\n";

      // Visible properties
      qpp_parameter<double> *pcov_rad   = d -> parameter<double>("cov_rad");
      qpp_parameter<double> *pvdw_rad   = d -> parameter<double>("vdw_rad");
      qpp_parameter<double> *pionic_rad = d -> parameter<double>("ionic_rad");
      qpp_parameter<double> *pred       = d -> parameter<double>("red");
      qpp_parameter<double> *pgreen     = d -> parameter<double>("green");
      qpp_parameter<double> *pblue      = d -> parameter<double>("blue");
      qpp_parameter<double> *pvalpha    = d -> parameter<double>("transparancy");

      if (pcov_rad != NULL || pvdw_rad != NULL || pionic_rad != NULL || pred != NULL ||
	  pgreen   != NULL || pblue    != NULL || pvalpha    != NULL)
	{
	  visible = new visible_block;

	  if (pcov_rad != NULL)
	    visible -> cov_rad = pcov_rad ->value();
	  else
	    visible -> cov_rad = 0e0;

	  if (pvdw_rad != NULL)
	    visible -> vdw_rad = pvdw_rad -> value();
	  else
	    visible -> vdw_rad = 0e0;

	  if (pionic_rad != NULL)
	    visible -> ionic_rad = pionic_rad -> value();
	  else
	    visible -> ionic_rad = 0e0;
	    
	  if (pred != NULL)
	    visible -> red = pred ->value();
	  else
	    visible -> red = 0e0;

	  if (pgreen != NULL)
	    visible -> green = pgreen ->value();
	  else
	    visible -> green = 0e0;

	  if (pblue != NULL)
	    visible -> blue = pblue ->value();
	  else
	    visible -> blue = 0e0;

	  if (pvalpha != NULL)
	    visible -> alpha = pvalpha ->value();
	  else
	    visible -> alpha = 0e0;

	  add(* new qpp_parameter<REAL>("cov_rad", & (visible -> cov_rad), this));
	  add(* new qpp_parameter<REAL>("vdw_rad", &(visible -> vdw_rad), this));
	  add(* new qpp_parameter<REAL>("ionic_rad", &(visible -> ionic_rad), this));
	  add(* new qpp_parameter<REAL>("red", &(visible -> red), this));
	  add(* new qpp_parameter<REAL>("green", &(visible -> green), this));
	  add(* new qpp_parameter<REAL>("blue", &(visible -> blue), this));
	  add(* new qpp_parameter<REAL>("transparency", &(visible -> alpha), this));
	}
      
  }

    qpp_atom(const qpp_atom & a) :
      qpp_declaration("atom",a.name(),a.owner(),NULL,a.line(),a.file())
    {
      //fixme - implement this
    }


    virtual STRING category() const
    { return "atom";}

    virtual qppobject_type gettype() const
    { return qtype_atom + qtype_data<REAL>::type; }

    virtual int atype() const
    {
    }

    virtual bool operator==(const qpp_atom &a) const
    {
    }

    virtual qpp_atom* copy() const
    {
      return new qpp_atom<REAL>(*this);
    }

  };

  // -------------------------------------------------

};

#endif
