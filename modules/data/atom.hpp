#ifndef _QPP_ATOM_H
#define _QPP_ATOM_H

#include <string>
#include <sstream>
#include <data/qppdata.hpp>
#include <basis/basis.hpp>

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
  // basic class for all other types of atoms
  template<class REAL>
  class qpp_atom : public qpp_declaration{

  public:

    // Atom always has a name
    // It is supposed to be unique for each type of atoms
    int *number; // Number in periodic table

    struct classical_block{
      REAL *charge; // Effective charge
      REAL *mass;   // Atomic mass
    };

    struct polarizible_block{
      REAL *alpha; // polarisibility
    };

    struct basis_block{
      STRING * bas_name;
      qpp_bastype * bas_type;
      // only one of the following arrays can be not empty
      std::vector<qpp_shell<qbas_gauss,REAL>*>  gauss_shells;
      std::vector<qpp_shell<qbas_slater,REAL>*> slater_shells;
      std::vector<qpp_shell<qbas_siesta,REAL>*> siesta_shells;
    };

    struct pseudo_block{
      STRING * pseudo_name;
    };

    struct visible_block{
      REAL *cov_rad;
      REAL *vdw_rad;
      REAL *ionic_rad;
      REAL * red, * green, * blue, *alpha;
    };

    classical_block   * classical;
    polarizible_block * polarizible;
    basis_block       * basis;
    pseudo_block      * pseudo;
    visible_block     * visible;

    qpp_atom(STRING __name, qpp_object * __owner = NULL, int __number=0) : 
      qpp_declaration("atom",__name, __owner)
    {
      qpp_parameter<int> * p = new qpp_parameter<int>("number",__number,this);
      add(*p);
      number = &p->value();
      classical   = NULL;
      polarizible = NULL;
      basis       = NULL;
      pseudo      = NULL;
      visible     = NULL;
    }

    qpp_atom(qpp_declaration * decl, qpp_object * __owner = NULL) :
      qpp_declaration("atom", decl->name(), __owner, NULL, decl->line(), decl->file())
    {
      //debug
      /*      std::cerr << "entering atom constructor\n-----------------------------\n";
      decl -> write(std::cerr);
      std::cerr << "--------------------------------------\n";
      */
      qpp_parameter<int> *pnumber;

      pnumber = decl -> parameter<int>("number");

      //debug
      //std::cerr << "atom constr: after parameter<int>(number)\n";

      if (pnumber == NULL)
	pnumber = new qpp_parameter<int>("number",0);
      add(*pnumber);
      number = &(pnumber->value());

      //debug
      //std::cerr << "atom constr alive 1\n";

      // Classical properties
      qpp_parameter<REAL> * pcharge, * pmass;
      pcharge = decl -> parameter<REAL>("charge");
      pmass   = decl -> parameter<REAL>("mass");

      if (pcharge != NULL || pmass != NULL)
	{
	  classical = new classical_block;
	  if (pcharge == NULL)
	    pcharge = new qpp_parameter<REAL>("charge",0e0);
	  if (pmass == NULL)
	    pmass = new qpp_parameter<REAL>("mass",0e0);
	  add(*pcharge);
	  add(*pmass);
	  classical = new classical_block;
	  classical -> charge = &(pcharge->value());
	  classical -> mass = &(pmass->value());
	}
      //debug
      //std::cerr << "atom constr alive 2\n";

      // Polarizible properties
      qpp_parameter<REAL> * palpha = decl -> parameter<REAL>("alpha");
      if (palpha != NULL)
	{
	  polarizible = new polarizible_block;
	  add(*palpha);
	  polarizible -> alpha = &(palpha->value());
	}
      //debug
      //std::cerr << "atom constr alive 3\n";

      // Basis data
      qpp_parameter<STRING> * pbasis = decl -> parameter<STRING>("basis");
      if (pbasis != NULL)
	{
	  basis = new basis_block;
	  add(*pbasis);
	  basis -> bas_name = &(pbasis->value());
	}
      //debug
      //std::cerr << "atom constr alive 4\n";

      // Visible properties
      qpp_parameter<REAL> *pcov_rad   = decl -> parameter<REAL>("cov_rad");
      qpp_parameter<REAL> *pvdw_rad   = decl -> parameter<REAL>("vdw_rad");
      qpp_parameter<REAL> *pionic_rad = decl -> parameter<REAL>("ionic_rad");
      qpp_parameter<REAL> *pred    = decl -> parameter<REAL>("red");
      qpp_parameter<REAL> *pgreen  = decl -> parameter<REAL>("green");
      qpp_parameter<REAL> *pblue   = decl -> parameter<REAL>("blue");
      qpp_parameter<REAL> *pvalpha = decl -> parameter<REAL>("transparancy");

      if (pcov_rad != NULL || pvdw_rad != NULL || pionic_rad != NULL || pred != NULL ||
	  pgreen   != NULL || pblue    != NULL || pvalpha    != NULL)
	{
	  visible = new visible_block;
	  if (pcov_rad == NULL)
	    pcov_rad = new qpp_parameter<REAL>("cov_rad",0e0);
	  if (pvdw_rad == NULL)
	    pvdw_rad = new qpp_parameter<REAL>("vdw_rad",0e0);
	  if (pionic_rad == NULL)
	    pionic_rad = new qpp_parameter<REAL>("ionic_rad",0e0);
	  if (pred == NULL)
	    pred = new qpp_parameter<REAL>("red",0e0);
	  if (pgreen == NULL)
	    pgreen = new qpp_parameter<REAL>("green",0e0);
	  if (pblue == NULL)
	    pblue = new qpp_parameter<REAL>("blue",0e0);
	  if (pvalpha == NULL)
	    pvalpha = new qpp_parameter<REAL>("transparency",0e0);

	  add(*pcov_rad);
	  add(*pvdw_rad);
	  add(*pionic_rad);
	  add(*pred);
	  add(*pgreen);
	  add(*pblue);
	  add(*pvalpha);
	  visible -> cov_rad   = &(pcov_rad->value());
	  visible -> vdw_rad   = &(pvdw_rad->value());
	  visible -> ionic_rad = &(pionic_rad->value());
	  visible -> red    = &(pred->value());
	  visible -> green = &(pgreen->value());
	  visible -> blue   = &(pblue->value());
	  visible -> alpha = &(pvalpha->value());
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
