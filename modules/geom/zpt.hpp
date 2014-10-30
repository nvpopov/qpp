#ifndef _QPP_ZPT
#define _QPP_ZPT

#include <geom/geom.hpp>
#include <geom/zmt.hpp>
#include <io/qppdata.hpp>
#include <io/qpparser.hpp>
#include <mathf/intlst.hpp>
#include <string>
#include <iostream>
#include <boost/format.hpp>
//debug
#include <stdlib.h>  
#include <io/geomio.hpp>

namespace qpp{

  STRING ptype_name [] = {"search", "avoid", "delete", "insert"};


  template <int DIM,class CREAL=double, class TRANSFORM = periodic_cell<DIM,CREAL> >   
  class zpattern : public qpp_object, public geometry_dependent {

    STRING _name, _error;

    geometry<DIM,CREAL,TRANSFORM> *geom;
    typename geometry<DIM,CREAL,TRANSFORM>::neighbours_table * ngbr;
    parametric_surface<CREAL> *mfold;
    //std::vector<lace::vector2d<CREAL> > *parm;   
    
  public:

    CREAL geomtol, symmtrap_radius;
    int priority;

    zpattern(const STRING & __name = "")
    {
      _name = __name; 
      geomtol = default_geomtol;      
      priority = 0;
    }

    zpattern(geometry<DIM,CREAL,TRANSFORM> & g, const STRING & __name = "")
    {
      geom = &g;
      _name = __name;
      geomtol = geom->geomtol;
      priority = 0;
    }

    // kostyl for commented "parm"
    lace::vector2d<CREAL> parm(int i)
    {
      return lace::vector2d<CREAL>(geom->coord(i).x(), geom->coord(i).y());
    }

    // ---------------- "Points" - named points to be identified with atoms --------------

    struct zpt_point{
      STRING nickname;
      STRING atom;
      bool is_bound;
      index<DIM> bound;

      zpt_point()
      {	is_bound = false; }

      zpt_point(STRING const & nick, STRING const & at)
      {
	nickname = nick;
	atom = at;
	is_bound = false;
      }

      zpt_point(zpt_point const &zp)
      {
	nickname = zp.nickname;
	atom = zp.atom;
	is_bound = zp.is_bound;
	bound = zp.bound;
      }

    };
    
    enum ptype {zsearch = 0, zavoid = 1, zdelete = 2, zinsert = 3};

  private:
    std::vector<zpt_point*> points_registry;
    std::vector<ptype> points_types;
    std::vector<int> points_idx[4];
  public:

    inline zpt_point & point(int i) { return *points_registry[i];}

    inline ptype point_type(int i) const{ return points_types[i];}

    inline zpt_point & point(int i, int ptp) { return *(points_registry[points_idx[ptp][i]]);}

    inline int point_idx(int i, int ptp) const{ return points_idx[ptp][i];}

    inline int n_points() const{ return points_registry.size();}

    inline int n_points(int ptp) const{ return points_idx[ptp].size();}

    /*
    bool point_already(zpt_point * cp, ptype ptp)
    {
      bool found = false;
      for (int i=0; i<points[ptp].size(); i++)
	if (cp->nickname == points[ptp][i]->nickname)
	  {
	    found = true;
	    break;
	  }
      return found;
      }*/

    void add_point(zpt_point const & zp, ptype ptp)
    {
      bool found = false;
      int i;
      for (i=0; i<points_registry.size(); i++)
	if (zp.nickname == point(i).nickname)
	  {
	    found = true;
	    break;
	  }
      if ( found )
	{
	  if (ptp == zdelete && point_type(i) == zsearch)
	    // this is OK, just mark this point to delete
	    {
	      points_types[i] = zdelete;
	      int j;
	      for (j=0; j<n_points(zsearch); j++)
		if ( points_idx[zsearch][j] == i)
		  points_idx[zsearch].erase(points_idx[zsearch].begin()+j);
	      points_idx[zdelete].push_back(i);
	    }
	  else if ( ! (ptp == zsearch && point_type(i) == zdelete) )
	    // this condition would be also OK and would not require any action
	    error("point with such name (" + zp.nickname + ") is already present");
	}
      else
	{
	  points_registry.push_back(new zpt_point(zp));
	  points_types.push_back(ptp);
	  points_idx[ptp].push_back(points_registry.size()-1);
	}
    }
    
      /*      if (found)
	cp = points_registry[i];
      else
	{
	  cp = new zpt_point(zp);
	  points_registry.push_back(cp);
	}
	  
      if (!point_already(cp,ptp))
	points[ptp].push_back(cp);

      if (ptp==zdelete && ! point_already(cp,zsearch))
	points[zsearch].push_back(cp);
      */

    // -------------- Relations - bonds, angles & dihedrals ---------------
    
    class geometry_relation;

  private:
    std::vector<geometry_relation*> relation_registry;
    std::vector< std::vector<int> > _rel_of_point;
    // instead of vector<bool>
    std::vector<char> occupied, noapply;
  public:

    class linear_dependence : public qpp_object{
      zpattern<DIM,CREAL,TRANSFORM> * owner;
      STRING _name;

      CREAL v0;
      std::vector<CREAL> coeffs;
      std::vector<STRING> varnames;
      std::vector<int> varidx;

    public:

      linear_dependence(CREAL _v0, zpattern<DIM,CREAL,TRANSFORM> & _owner,
			STRING const &__name = "")
      { 
	v0 = _v0; 
	_name = __name;
	owner = & _owner;
      }

      linear_dependence & term(STRING const & vn, CREAL cc)
      {
	varnames.push_back(vn);
	coeffs.push_back(cc);
	bool vnfound = false;
	for (int i=0; i < owner->relation_registry.size(); i++)
	  {
	    if (vn == owner->relation_registry[i]->name())
	      {
		varidx.push_back(i);
		vnfound = true;
		break;
	      }
	  }
	if (!vnfound)
	  owner->error("Variable " + vn + " is not defined in relations of zpattern " 
		       + owner->name());
	return *this;
      }

      int n_terms()
      { return varnames.size();}

      CREAL value()
      {
	CREAL res = v0;
	for (int i=0; i<varidx.size(); i++)
	  res += coeffs[i]*owner->relation_registry[varidx[i]] -> value();
	return res;
      }

      CREAL is_defined()
      {
	bool res = true;
	for (int i = 0; i<varidx.size(); i++)
	  {
	    //	    std::cerr << "term " << i << " rel " << varidx[i] << "\n";

	    if (!owner -> rel(varidx[i]).is_defined())
	      {
		res = false;
		break;
	      }
	  }
	return res;
      }

      virtual STRING category() const
      { return "lindep";}

      virtual STRING name() const
      { return _name;}

      virtual qppobject_type gettype() const
      {
	return qtype_zpt_lindep | qtype_data<CREAL>::type;
      }

      virtual int n_next() const
      { return 0;}

      virtual qpp_object* next(int i)
      {
	return NULL;
      }

      virtual void error(STRING const &){}
      
      virtual STRING error(){return "";}

      virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
      {
	for (int k=0; k<offset; k++) os << " ";
	os << "lindep";
	if (_name != "")
	  os << " " << _name;

	os << "(" << v0;
	for (int i=0; i<varnames.size(); i++)
	  os << ", " << varnames[i] << ", " << coeffs[i];
	os << ")";
      }

    };

    class geometry_relation : public qpp_object{      
    protected:

      zpattern<DIM,CREAL,TRANSFORM> * owner;
      STRING _name;

      std::vector<int> _points;
      bool exact;
      linear_dependence * _formula;

      void match_points()
      {
	_points.resize(n_points());
	for (int i=0; i<n_points(); i++)
	  {
	    //debug
	    //std::cerr << i << " " << point_nick(i) << "\n";

	    int k;
	    _points[i] = -1;
	    for (k=0; k<owner->n_points(); k++)
	      {
		// debug
		//std::cerr << k << "\n";
		//std:: cout << "=" << owner->point(k).nickname << "\n";

	      if (point_nick(i)==owner->point(k).nickname)
		{
		  _points[i] = k;
		  break;
		}	      
	      }
	    if (_points[i] == -1)
	      owner->error("Point with nickname " + point_nick(i) + 
			  " is not defined among zpattern points");
	  }
      }

    public:      
      CREAL vmin,vmax;

      virtual CREAL value() =0;
      virtual int n_points() =0;
      virtual STRING point_nick(int i) =0;      

      virtual bool satisfy()
      {
	//std::cerr << "psat: ";
	//write(std::cerr);
	//debug();
	//std::cerr << " defined= " << is_defined() << "\n";
	if (is_defined())
	  {
	    if (exact)
	      {
		//std::cerr << "value= " << value() << " formula= " << _formula -> value() 
		//	  << " diff= " << boost::format("%25.20f\n")%(value() - _formula -> value());
		return _formula -> is_defined() ? std::abs(value() - _formula -> value()) <= owner -> geomtol : false;
		
	      }
	    else
	      {
		//std::cerr << " " << vmin <<  " " << vmax << " " << value() << "\n";
		return ( vmin <= value() && vmax >=value() );
	      }
	  }
	else
	  return false;
      }

      linear_dependence & formula(){return *_formula;}

      virtual bool is_bond(){return false;}

      bool is_exact(){return exact;}

      bool is_dependence(){return exact && (_formula -> n_terms() > 0) ;}

      bool is_range()
      { return !is_exact();}
      
      virtual STRING name() const
      { return _name; }

      int point(int i)
      { return _points[i];}

      bool point_defined(int i)
      {
	return owner->point(point(i)).is_bound;
      }

      int n_undefined()
      {
	int res = 0;
	for (int i=0; i<n_points(); i++)
	  if ( !point_defined(i) )
	    res += 1;
	return res;
      }
      
      bool is_defined()
      {
	return n_undefined() == 0;
      }

      virtual void error(STRING const &){}

      virtual STRING error(){return "";}

    };

    //----------------------------------------------

    class bond_relation : public geometry_relation {
      STRING at1, at2;

    protected:
      //      using typename zpattern<DIM,CREAL,ATLABEL,charT,traits>::geometry_relation::owner;
      using geometry_relation::owner;
      using geometry_relation::vmin;
      using geometry_relation::vmax;
      using geometry_relation::_formula;
      using geometry_relation::exact;
      using geometry_relation::is_defined;
      using geometry_relation::_name;
      using geometry_relation::match_points;
      
    public:

      bond_relation(STRING const & _at1, STRING const &_at2, CREAL _bmin, CREAL _bmax, 
		    zpattern<DIM,CREAL,TRANSFORM> & z, STRING const &__name = "")
      {
	at1 = _at1;
	at2 = _at2;
	vmin = _bmin;
	vmax = _bmax;
	exact = false;
	_formula = NULL;
	owner = &z;
	_name = __name;
	match_points();
      }

      bond_relation(STRING const & _at1, STRING const &_at2, linear_dependence &__formula,
		    zpattern<DIM,CREAL,TRANSFORM> & z, STRING const &__name = "")
      {
	at1 = _at1;
	at2 = _at2;
	exact = true;
	_formula = &__formula;
	owner = &z;
	_name = __name;
	match_points();
      }

      virtual bool is_bond()
      { return true;} 

      virtual CREAL value()
      {
	if (!is_defined())
	  return -1;
	else
	  {
	    index<DIM> i1 = owner->point(point(0)).bound,	      
	      i2 = owner->point(point(1)).bound;
	    return norm(owner->geom->position(i1) - owner->geom->position(i2));
	  }
      }

      virtual int n_points(){return 2;}

      virtual STRING point_nick(int i)
      {
	if (i==0)
	  return at1;
	else if (i==1)
	  return at2;
      }
      
      virtual STRING category() const
      {
	return "bond";
      }

      
      virtual qppobject_type gettype() const
      { 
	return qtype_zpt_bond | qtype_data<CREAL>::type; 
      }
      
      virtual int n_next() const
      { return 0;}

      virtual qpp_object* next(int i)
      {
	return NULL;
      }

      virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
      {
	for (int k=0; k<offset; k++) os << " ";
	os << "bond";
	if (_name != "")
	  os << " " << _name;
	if (!exact)
	  os << "(" << at1 << "," << at2 << "," << vmin << "," << vmax << ")";
	else
	  {
	    os << "(" << at1 << "," << at2 << ",";
	    _formula -> write(os);
	    os << ")";
	  }
      }
      
    };

    //-------------------------------------------------

    class angle_relation : public geometry_relation {
      STRING at1, at2, at3;

    protected:
      using geometry_relation::owner;
      using geometry_relation::vmin;
      using geometry_relation::vmax;
      using geometry_relation::_formula;
      using geometry_relation::exact;
      using geometry_relation::is_defined;
      using geometry_relation::_name;
      using geometry_relation::match_points;
      
    public:

      angle_relation(STRING const & _at1, STRING const &_at2, STRING const &_at3,
		    CREAL _amin, CREAL _amax, 
		     zpattern<DIM,CREAL,TRANSFORM> & z, STRING const &__name = "")
      {
	at1 = _at1;
	at2 = _at2;
	at3 = _at3;
	vmin = _amin;
	vmax = _amax;
	exact = false;
	_formula = NULL;
	owner = &z;
	_name = __name;
	match_points();
      }

      angle_relation(STRING const & _at1, STRING const &_at2, STRING const &_at3, linear_dependence &__formula,
		    zpattern<DIM,CREAL,TRANSFORM> & z, STRING const &__name = "")
      {
	at1 = _at1;
	at2 = _at2;
	at3 = _at3;
	exact = true;
	_formula = &__formula;
	owner = &z;
	_name = __name;
	match_points();
      }

      virtual CREAL value()
      {
	if (!is_defined())
	  return -1;
	else
	  {
	    index<DIM> 
	      i1 = owner->point(point(0)).bound,	      
	      i2 = owner->point(point(1)).bound,
	      i3 = owner->point(point(2)).bound;
	    lace::vector3d<CREAL> n1, n2;
	    n1 = owner->geom->position(i1) - owner->geom->position(i2);
	    n2 = owner->geom->position(i3) - owner->geom->position(i2);
	    n1 /= norm(n1);
	    n2 /= norm(n2);

	    return std::acos(scal(n1,n2))*180/pi;
	  }
      }
      
      virtual int n_points(){return 3;}

      virtual STRING point_nick(int i)
      {
	if (i==0)
	  return at1;
	else if (i==1)
	  return at2;
	else if (i==2)
	  return at3;
      }
      
      virtual STRING category() const
      {
	return "angle";
      }
      
      virtual qppobject_type gettype() const
      { 
	return qtype_zpt_angle | qtype_data<CREAL>::type; 
      }

      virtual int n_next() const
      { return 0;}

      virtual qpp_object* next(int i)
      {
	return NULL;
      }
      
      virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
      {
	for (int k=0; k<offset; k++) os << " ";
	os << "angle";
	if (_name != "")
	  os << " " << _name;
	if (!exact)
	  os << "(" << at1 << "," << at2 << "," << at3 << "," << vmin << "," << vmax << ")";
	else
	  {
	    os << "(" << at1 << "," << at2 << "," << at3 << ",";
	    _formula -> write(os);
	    os << ")";
	  }
      }
      
    };

    //-------------------------------------------------

    class surfangle_relation : public geometry_relation {
      STRING at1, at2, at3;

    protected:
      using geometry_relation::owner;
      using geometry_relation::vmin;
      using geometry_relation::vmax;
      using geometry_relation::_formula;
      using geometry_relation::exact;
      using geometry_relation::is_defined;
      using geometry_relation::_name;
      using geometry_relation::match_points;
      
    public:

      surfangle_relation(STRING const & _at1, STRING const &_at2, STRING const &_at3,
			 CREAL _amin, CREAL _amax, 
			 zpattern<DIM,CREAL,TRANSFORM> & z, STRING const &__name = "")
      {
	at1 = _at1;
	at2 = _at2;
	at3 = _at3;
	vmin = _amin;
	vmax = _amax;
	exact = false;
	_formula = NULL;
	owner = &z;
	_name = __name;
	match_points();
      }

      surfangle_relation(STRING const & _at1, STRING const &_at2, STRING const &_at3, 
			 linear_dependence &__formula,
			 zpattern<DIM,CREAL,TRANSFORM> & z, STRING const &__name = "")
      {
	at1 = _at1;
	at2 = _at2;
	at3 = _at3;
	exact = true;
	_formula = &__formula;
	owner = &z;
	_name = __name;
	match_points();
      }

      virtual CREAL value()
      {
	if (!is_defined())
	  return -1;
	else
	  {
	    index<DIM> 
	      i1 = owner->point(point(0)).bound,	      
	      i2 = owner->point(point(1)).bound,
	      i3 = owner->point(point(2)).bound;
	    /*	    lace::vector3d<CREAL> n1, n2, nperp;
	    n1 = owner->geom->full_coord(i1) - owner->geom->full_coord(i2);
	    n2 = owner->geom->full_coord(i3) - owner->geom->full_coord(i2);
	    nperp = owner -> mfold -> normal( (*(owner -> parm))[i2] );

	    n1 -= nperp*scal(n1,nperp);
	    n2 -= nperp*scal(n2,nperp);

	    n1 /= norm(n1);
	    n2 /= norm(n2);
	    */
	    return owner->mfold->surface_angle(owner->parm(i1),
					       owner->parm(i2),owner->parm(i3))*180/pi;
	  }
      }
      
      virtual int n_points(){return 3;}

      virtual STRING point_nick(int i)
      {
	if (i==0)
	  return at1;
	else if (i==1)
	  return at2;
	else if (i==2)
	  return at3;
      }
      
      virtual STRING category() const
      {
	return "surfangle";
      }

      
      virtual qppobject_type gettype() const
      { 
	return qtype_zpt_surfangle | qtype_data<CREAL>::type; 
      }
      
      virtual int n_next() const
      { return 0;}

      virtual qpp_object* next(int i)
      {
	return NULL;
      }

      virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
      {
	for (int k=0; k<offset; k++) os << " ";
	os << "surfangle";
	if (_name != "")
	  os << " " << _name;
	if (!exact)
	  os << "(" << at1 << "," << at2 << "," << at3 << "," << vmin << "," << vmax << ")";
	else
	  {
	    os << "(" << at1 << "," << at2 << "," << at3 << ",";
	    _formula -> write(os);
	    os << ")";
	  }
      }
      
    };

    //-------------------------------------------------

    class dyhedral_relation : public geometry_relation {
      STRING at1, at2, at3, at4;

    protected:
      using geometry_relation::owner;
      using geometry_relation::vmin;
      using geometry_relation::vmax;
      using geometry_relation::_formula;
      using geometry_relation::exact;
      using geometry_relation::is_defined;
      using geometry_relation::_name;
      using geometry_relation::match_points;
      
    public:

      dyhedral_relation(STRING const & _at1, STRING const &_at2, STRING const &_at3, STRING const &_at4,
			CREAL _dmin, CREAL _dmax, 
			zpattern<DIM,CREAL,TRANSFORM> & z, STRING const &__name = "")
      {
	at1 = _at1;
	at2 = _at2;
	at3 = _at3;
	at4 = _at4;
	vmin = _dmin;
	vmax = _dmax;
	exact = false;
	_formula = NULL;
	owner = &z;
	_name = __name;
	match_points();
      }

      dyhedral_relation(STRING const & _at1, STRING const &_at2, STRING const &_at3, STRING const &_at4, 
			linear_dependence &__formula,
			zpattern<DIM,CREAL,TRANSFORM> & z, STRING const &__name = "")
      {
	at1 = _at1;
	at2 = _at2;
	at3 = _at3;
	at4 = _at4;
	exact = true;
	_formula = &__formula;
	owner = &z;
	_name = __name;
	match_points();
      }

      virtual CREAL value()
      {
	if (!is_defined())
	  return -9000;
	else
	  {
	    index<DIM> 
	      i1 = owner->point(point(0)).bound,	      
	      i2 = owner->point(point(1)).bound,
	      i3 = owner->point(point(2)).bound,
	      i4 = owner->point(point(3)).bound;

	    return get_dyhedral(owner->geom->position(i1), owner->geom->position(i2),
				owner->geom->position(i3), owner->geom->position(i4));
	  }
      }
      
      virtual int n_points(){return 4;}

      virtual STRING point_nick(int i)
      {
	if (i==0)
	  return at1;
	else if (i==1)
	  return at2;
	else if (i==2)
	  return at3;
	else if (i==3)
	  return at4;
      }
      
      virtual STRING category() const
      {
	return "dihedral";
      }

      
      virtual qppobject_type gettype() const
      {
	return qtype_zpt_dihedral | qtype_data<CREAL>::type; 
      }
      
      virtual int n_next() const
      { return 0;}

      virtual qpp_object* next(int i)
      {
	return NULL;
      }

      virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
      {
	for (int k=0; k<offset; k++) os << " ";
	os << "dihedral";
	if (_name != "")
	  os << " " << _name;
	if (!exact)
	  os << "(" << at1 << "," << at2 << "," << at3 << "," << at4 << "," << vmin << "," << vmax << ")";
	else
	  {
	    os << "(" << at1 << "," << at2 << "," << at3 << "," << at4 << ",";
	    _formula -> write(os);
	    os << ")";
	  }
      }
      
    };

    //-------------------------------    
  
    void add_relation(geometry_relation & rel)
    { 
      relation_registry.push_back(&rel); 
      int j = relation_registry.size()-1;
      
      //debug
      //std::cerr << j << " ";
      //rel.write(std::cerr);
      //std::cerr << "\n";
      
      if ( _rel_of_point.size() != n_points() )
	{
	  _rel_of_point.resize(n_points());
	  //std::cerr << "haha\n";
	}
      for (int i=0; i<rel.n_points(); i++)
	{
	  //std::cerr << "adding " << j << " to " << rel.point(i) << "\n";
	  _rel_of_point[rel.point(i)].push_back(j);
	}
    }
    
    inline int n_rel() const
    { return relation_registry.size();}
    
    inline geometry_relation & rel(int i)
    { return *relation_registry[i];}

    inline int n_rel_of_point(int i) const
    { return _rel_of_point[i].size();}

    inline int rel_of_point(int i, int j) const
    { return _rel_of_point[i][j];}

    inline int n_point_of_rel(int i) //const
    { return rel(i).n_points();}

    inline int point_of_rel(int i, int j) const
    { return rel(i).point(j);}

    inline void bind(int i, index<DIM> j)
    {
      point(i).is_bound = true;
      point(i).bound = j;
      // fixme - potential bug here, since j is index<DIM> and not int
      // however, if z-pattern is smaller then unit cell size, it should not cause any problems
      occupied[j] = true;
    }

    inline void unbind(int i)
    {
      if (point(i).is_bound)
	occupied[point(i).bound] = false;
      point(i).is_bound = false;
    }

    inline index<DIM> bound(int i)
    {
      return point(i).bound;
    }

    inline bool is_bound(int i)
    {
      return point(i).is_bound;
    }

    // ----------------------------------------------------------------------

    virtual STRING category() const
    { return "zpattern"; }

    virtual STRING name() const
    { return _name; }
      
    void setname(STRING __name)
    { _name = __name; }

    virtual qppobject_type gettype() const
    { 
      return qtype_zpattern | qtype_data<CREAL>::type;
    }
      
    virtual int n_next() const
    { 
      //fixme
    }
    
    virtual qpp_object* next(int i)
    {
      //fixme
    }

    virtual void error(STRING const & what)
    { 
      _error = what;
      throw qpp_exception(this);
    }
    
    virtual STRING error()
    {
      return _error;
    }
    
    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      for (int k=0; k<offset; k++) os << " ";
      os << "zpattern";
      if (_name != "")
	os << " " << _name;

      //if (priority!=0)
	{
	  os << "(priority=" << priority << ")\n";
	  for (int k=0; k<offset; k++) os << " ";
	}

      os << "{\n";
      for (int ptp = zsearch; ptp <= zinsert; ptp++)
	if (n_points(ptp)>0)
	  {
	    for (int k=0; k<offset+2; k++) os << " ";
	    os << ptype_name[ptp] << "(";
	    for (int k=0; k<n_points(ptp); k++)
	      os << points_registry[points_idx[ptp][k]] -> nickname  << "=" 
		 << points_registry[points_idx[ptp][k]] -> atom 
		 << (k<n_points(ptp)-1 ? "," : "");	  
	    os << ");\n";
	  }

      //debug
      //for (int i=0; i<points_registry.size(); i++)
      //	std::cerr << points_registry[i]->nickname << " " << i << "\n";

      for (int i=0; i<n_rel(); i++)
	{
	  relation_registry[i] -> write(os,offset+2);
	  os << ";\n";
	}
      os << "}\n";
    }

    void debug()
    {     
      for (int p=zsearch; p<=zinsert; p++)
	{
	  std::cerr << boost::format("%-8s") % ptype_name[p];
	  for (int i=0; i<n_points(p); i++)
	    std::cerr << boost::format("%3i") % points_idx[p][i];
	  std::cerr << "\n";
	}
	    

      for (int i=0; i<n_rel(); i++)
	{
	  std::cerr << boost::format("%3i ") % i;
	  int t = rel(i).gettype();
	  if (t & qtype_zpt_bond)
	    std::cerr << "b";
	  else if (t & qtype_zpt_angle)
	    std::cerr << "a"; 
	  else if (t & qtype_zpt_dihedral)
	    std::cerr << "d";

	  for (int j=0; j<rel(i).n_points(); j++)
	    std::cerr << boost::format("%3i")%rel(i).point(j);

	  if (rel(i).is_exact())
	    std::cerr << " exact";
	  std::cerr << "\n";	    
	    
	}
      for (int i=0; i<n_points(); i++)
	{
	  std::cerr << boost::format("%3i %-10s %-5s %-8s") % i % point(i).nickname % point(i).atom % 
	    ptype_name[points_types[i]];
	  for (int j=0; j < n_rel_of_point(i); j++)
	    std::cerr << boost::format("%4i ") % rel_of_point(i,j);
	  std::cerr << "\n";
	}
    }

    // ------------------------------------------------------------------
    //                       Pattern "depth"
    int depth(int *mask=NULL)
    {
      //debug
      // std::cerr << "depth\n";

      if (mask==NULL)
	{
	  mask = new int[n_points()];
	  mask[0] = 1;
	  for (int i=1; i<n_points(); i++)
	    if (point_type(i)==zsearch || point_type(i)==zdelete)
	      mask[i] = 0;
	    else
	      mask[i] = -1;
	  return depth(mask);
	}
      else
	{
	  //debug
	  /*
	  for (int i=0; i<n_points(); i++)
	    std::cerr << i << " " << point(i).nickname << " " << mask[i] << "\n";
	  std::cerr << "\n";
	  */

	  bool found=false;
	  for (int i=0; i<n_points(); i++)
	    if (mask[i]==1)
	      for (int j=0; j<n_rel_of_point(i); j++)
		{
		  int k = rel_of_point(i,j);
		  if (rel(k).is_bond())
		    {
		      int other_pt = rel(k).point(0);
		      if (other_pt==i)
			other_pt = rel(k).point(1);
		      if (mask[other_pt]==0)
			{
			  found = true;
			  mask[other_pt]=2;
			}
		    }
		}
	  for (int i=0; i<n_points(); i++)
	    if (mask[i]==2) 
	      mask[i] = 1;
	  if (!found)
	    return 0;
	  else
	    return depth(mask)+1;
	}
    }


    // ------------------------------------------------------------------
    //                Matching and applying the pattern
    // ------------------------------------------------------------------

    int search_condition(int i)
    // find the bond connecting i-th point to already defined point
    {
      int res = -1;
      for (int j=0; j<n_rel_of_point(i); j++)
	{
	  int k = rel_of_point(i,j);
	  if ( rel(k).is_bond() && rel(k).n_undefined()==1 )
	    {
	      res = j;
	      break;
	    }
	}
      return res;
    }

    // ---------------------------------------------------------------------

    void insert_condition(int i, std::vector<int> & ibnd, std::vector<int> & iang, 
			  std::vector<int> & idhd)
    {
      /* The point can be inserted in the following cases:
	 1) A bond, angle & dihedral are known
	 2) 
      */
      ibnd.clear();
      iang.clear();
      idhd.clear();
      for (int j=0; j<n_rel_of_point(i); j++)
	{
	  int k =  rel_of_point(i,j);
	  // debug
	  /*
	  std::cerr << j << " " << k << " ";
	  rel(k).write(std::cerr);	  
	  std::cerr << " type: " << rel(k).gettype() << " exact: " << rel(k).is_exact() 
		    << " val_defined: " 
		    << rel(k).formula().is_defined() << " pt_undef: " 
		    << rel(k).n_undefined() << "\n";
	  */
	  
	  if ( rel(k).is_exact() && rel(k).formula().is_defined() && rel(k).n_undefined()==1 )
	    {
	      if (rel(k).gettype() & qtype_zpt_bond)
		ibnd.push_back(k);
	      else  if (rel(k).gettype() & (qtype_zpt_angle | qtype_zpt_surfangle))
		iang.push_back(k);
	      else if (rel(k).gettype() & qtype_zpt_dihedral)
		idhd.push_back(k);
	    }
	}
    }

    // ------------------------------------------------------------------

    void unbind_all()
    {
      occupied.clear();
      occupied.resize(geom->nat(),false);
      
      // noapply.clear();
      // noapply.resize(geom->nat(),false);
      // if (geom->gettype() & qtype_xgeometry)
      // 	{
      // 	  qpp::xtr_geometry<DIM,CREAL> * xgeom = 
      // 	    (qpp::xtr_geometry<DIM,CREAL> *)geom;
      // 	  if ()
      // 	}
      
      for (int i=0; i<n_points(); i++)
	unbind(i);
    }

    // ---------------------------------------------------------------------

    bool point_satisfy(int i)
    {
      bool res = true;
      for (int j=0; j<n_rel_of_point(i); j++)
	{//debug
	  //rel(rel_of_point(i,j)).write(std::cerr);
	  //std::cerr << " " << rel(rel_of_point(i,j)).value() << "\n";
	  
	if ( rel(rel_of_point(i,j)).is_defined() && !rel(rel_of_point(i,j)).satisfy() )
	  {
	    res = false;
	    break;
	  }
	}
      return res;
    }

    // ---------------------------------------------------------------------

    void symmtrap(lace::vector2d<CREAL> & p)
    {
      lace::vector3d<CREAL> r(p.x,p.y,0e0);
      geom -> symm().symmtrap(r,symmtrap_radius);
      p.x = r.x();
      p.y = r.y();
    }

    // ---------------------------------------------------------------------
    /*
    bool match_next(integer_lister &lst)
    {
    }
    
    // ------------------------------------------------------------------

    bool apply( geometry<DIM, CREAL, ATLABEL, charT, traits> &g, integer_lister &lst)
    {
      //prepare
      geom = &g;
      occupied.resize(geom.size());
      for (int i=0; i<geom.size(); i++)
	occupied[i] = false;
      for (int i=0; i<n_points(); i++)
	unbind(i);
      
      // Match first point
      bool res = false;
      lst.set(0,geom->size()-1 );
      for (int i=lst.begin(); !lst.end(); i=lst.next())
	{
	  bind(0,i);
	  if ( match_next(*lst.copy()) )
	    {
	      res = true;
	      break;
	    }
	}
      return res;
    }
    */
    // ------------------------------------------------------------------
    //             Pattern application on parametric surface
    // ------------------------------------------------------------------

    bool avoid()
    {
      // Check that all matched points safisfy all conditions
      //std::cerr << "ENtering avoid\n";

      bool res = true;
      for (int i=0; i<n_rel(); i++)
	if (rel(i).is_defined() && !rel(i).satisfy())
	  {
	    res = false;
	    break;
	  }
      // Check that points to avoid cannot be matched

      for (int i=0; i<n_points(zavoid); i++)
	{
	  int iavd = point_idx(i,zavoid);

	  //std::cerr << "Avoiding: " << iavd << " " << point(iavd).nickname << "\n";

	  int jbnd = search_condition(iavd);
	  if (jbnd == -1)
	    error("Point " + point(iavd).nickname + 
		  " has no bonding condition to be searched for in zpattern " + name());

	  int k = rel_of_point(iavd,jbnd);
	  int ibnd = rel(k).point_defined(0) ? 
	    rel(k).point(0) : rel(k).point(1);
	  index<DIM> at_bnd = bound(ibnd);

	  //std::cerr << "bonding to "<< ibnd << " " << point(ibnd).nickname << " = " << at_bnd << "\n";

	  for (int javd = 0; javd < ngbr->n(at_bnd); javd++)
	    {
	      index<DIM> at_avd = (*ngbr)(at_bnd,javd);

	      //std::cerr << "try match to " << at_avd << " r= " 
	      //<< norm(geom->coord(at_avd)-geom->coord(at_bnd)) << "\n";

	      if ( occupied[at_avd] || !(point(iavd).atom == "*" || 
					 point(iavd).atom == geom -> atom(at_avd) ))
		continue;
	      
	      bind(iavd,at_avd);
	      
	      //std::cerr << "___checking if avoided\n";

	      if (point_satisfy(iavd))
		{
		  unbind(iavd);
		  res = false;
		  break;
		}
	      else
		unbind(iavd);
	    }
	  if (!res) break;
	}

      //debug
      //      std::cerr << "avoid result= " << res << "\n";
      return res;
      
    }

    // ------------------------------------------------------------------

    bool extract_bond(int r, CREAL &b, int &at)
    {
      b = rel(r).formula().value();
      if (rel(r).point_defined(0))
	at = point(rel(r).point(0)).bound;
      else
	at = point(rel(r).point(1)).bound;
      return true;
    }

    bool extract_angle(int r, CREAL &a, int &at1, int &at2)
    {
      bool res = true;
      a = rel(r).formula().value();
      if ( !rel(r).point_defined(0))
	{
	  at1 = point(rel(r).point(2)).bound;
	  at2 = point(rel(r).point(1)).bound;
	}
      else if ( !rel(r).point_defined(2))
	{
	  at1 = point(rel(r).point(0)).bound;
	  at2 = point(rel(r).point(1)).bound;
	}
      else res = false;
      return res;
    }

    bool extract_dihedral(int r, CREAL & d, int & at1, int & at2, int & at3)
    {
      bool res = true;
      d = rel(r).formula().value();
      if ( !rel(r).point_defined(0))
	{
	  at1 = point(rel(r).point(3)).bound;
	  at2 = point(rel(r).point(2)).bound;
	  at3 = point(rel(r).point(1)).bound;	  
	}
      else if ( !rel(r).point_defined(3))
	{
	  at1 = point(rel(r).point(0)).bound;
	  at2 = point(rel(r).point(1)).bound;
	  at3 = point(rel(r).point(2)).bound;	  
	}
      else
	res = false;
      return res;
    }

    // ------------------------------------------------------------------

    // New point insertion on parametric surface
    bool insert_next_surf( integer_lister &lst)
    {
      //std::cerr << "Insert_next called\n";
      //for (int i=0; i<n_points(); i++)
      //std::cerr << point(i).nickname << " " <<  point(i).bound << " " << point(i).is_bound << "\n";

      bool unfinished_insert = false, insert_found = false;
      int i;
      std::vector<int> ibnd, iang, idhd;
      for (i=0; i<n_points(zinsert); i++)
	if ( !point(i,zinsert).is_bound )
	  {
	    //std::cerr << "check insert conditions for point " << point_idx(i,zinsert) << "\n";
	    unfinished_insert = true;
	    insert_condition(point_idx(i,zinsert),ibnd,iang,idhd);

	    //std::cerr << "Insert conditions:\n";
	    //for (int j=0; j<ibnd.size(); j++)
	    //  rel(ibnd[j]).write(std::cerr);
	    //for (int j=0; j<iang.size(); j++)
	    //  rel(iang[j]).write(std::cerr);
	    //std::cerr << "\n";
	      

	    if ( ibnd.size() + iang.size() >= 2)
	      {
		insert_found = true;
		break;
	      }
	  }
      if (unfinished_insert && !insert_found)
	error("Not all new points are inserted, but no other insertion can be done");
      
      if (insert_found)
	{
	  //std::cerr << "Insert found\n";

	  int insrt = point_idx(i,zinsert);
	  std::vector<lace::vector2d<CREAL> > new_pt;
	  if (ibnd.size()==2)
	  // Two bonds
	    {
	      CREAL b1,b2;
	      int at1,at2;
	      extract_bond(ibnd[0],b1,at1);
	      extract_bond(ibnd[1],b2,at2);
	      
	      //std::cerr << "Two bonds: " << at1 << " " << b1 << " " << at2 << " " << b2 << "\n";

	      new_pt = mfold->triangul2b(parm(at1),b1,parm(at2),b2);

	      //std::cerr << "new points: " << new_pt.size() << "\n"; 
	    }
	  // Bond & angle
	  else if (ibnd.size()==1 && iang.size()==1)
	    {
	      CREAL b,a;
	      int at1,at2,at22;
	      extract_bond(ibnd[0],b,at2);
	      bool valid = extract_angle(iang[0],a,at1,at22);
	      if (valid)
		valid = (at2 == at22);
	      if (!valid)
		error("Given parameters do not allow to locate new point");

	      //std::cerr << "Inserting " << at1  << " " << at2 << " bond= " 
	      //<< b << " angle= " << a << "\n";
	      if (rel(iang[0]).gettype() & qtype_zpt_angle)
		{
		  //std::cerr << "triangul generated points\n";
		  new_pt.push_back(mfold->triangul(parm(at1),parm(at2),b,pi*a/180));
		  new_pt.push_back(mfold->triangul(parm(at1),parm(at2),b,-pi*a/180));
		}
	      else if (rel(iang[0]).gettype() & qtype_zpt_surfangle)
		{
		  //std::cerr << "protract generated points\n";
		  new_pt.push_back(mfold->protract(parm(at1),parm(at2),b, pi*a/180));
		  new_pt.push_back(mfold->protract(parm(at1),parm(at2),b,-pi*a/180));
		}
	    }
	  else if (iang.size()==2)
	    // fixme - implement later
	    error("Inserting new point on the basis of two angles is not supported yet");

	  for (int j=0; j<new_pt.size(); j++)
	    symmtrap(new_pt[j]);

	  lst.set(0,new_pt.size()-1);
	  bool res = false;
	  for (int j=lst.begin(); !lst.end(); j=lst.next())
	    {
	      int inew = geom->nat();
	      //	      parm->push_back(new_pt[j]);
	      geom -> add(point(insrt).atom, new_pt[j].x, new_pt[j].y, 0e0);
	      //geom -> add(point(insrt).atom, mfold->map(new_pt[j]));
	      occupied.push_back(true);
	      //noapply.push_back(false);

	      //geom->build_type_table();
	      //ngbr->build_disttable();
	      //ngbr->build();	      
	      bind(insrt,inew);
	      
	      //std::cerr << "point inserted i= " << insrt << " r= " << geom->coord(inew)<<"\n";
	      //for (int ii=0; ii<n_points(); ii++)
	      //std::cerr << point(ii).nickname << " = "  << bound(ii) << " " 
	      //<< point(ii).is_bound <<  "\n";

	      if (point_satisfy(insrt))
		res = insert_next_surf(*lst.copy());
	      //std::cerr << "satisfy= " << res << "\n";
	      //res = true;
	      if (res)
		{
		  //std::cerr  << "alive1\n";
		  delete &lst;
		  //std::cerr << "alive2\n";
		  return true;
		}
	      else
		{
		  unbind(insrt);
		  geom -> erase(inew);
		  //parm->pop_back();
		  occupied.pop_back();
		  //noapply.pop_back();
		  //geom->build_type_table();
		  //ngbr->build_disttable();
		  //ngbr->build();	      
		}
	    }
	  delete &lst;
	  return false;
	}
      else
	return avoid();
    }

    // ------------------------------------------------------------------

    // New point insertion in volume
    bool insert_next( integer_lister &lst)
    {
      //debug
      /*
      std::cerr << "Insert_next called\n";
      for (int i=0; i<n_points(); i++)
	{
	  std::cerr << point(i).nickname << " " <<  point(i).bound << " "; 
	  if (point(i).is_bound)
	    std::cerr << geom -> atom(point(i).bound) << geom -> position(point(i).bound);
	  std::cerr << "\n";
	}
      */

      bool unfinished_insert = false, insert_found = false;
      int i;
      std::vector<int> ibnd, iang, idhd;
      for (i=0; i<n_points(zinsert); i++)
	if ( !point(i,zinsert).is_bound )
	  {
	    //std::cerr << "check insert conditions for point " << point_idx(i,zinsert) << "\n";
	    unfinished_insert = true;
	    insert_condition(point_idx(i,zinsert),ibnd,iang,idhd);

	    //debug
	    /*
	    std::cerr << "Insert conditions:\n";
	    for (int j=0; j<ibnd.size(); j++)
	      rel(ibnd[j]).write(std::cerr);
	    for (int j=0; j<iang.size(); j++)
	      rel(iang[j]).write(std::cerr);
	    for (int j=0; j<idhd.size(); j++)
	      rel(idhd[j]).write(std::cerr);
	    std::cerr << "\n";
	    */
	    if ( ibnd.size() + iang.size() + idhd.size() >= 3)
	      {
		insert_found = true;
		break;
	      }

	    // Special case 180 degree
	    CREAL alp;
	    int a1,a2;
	    if (ibnd.size()==1 && iang.size()==1)
	      if (extract_angle(iang[0],alp,a1,a2))
		if ( std::abs(alp-180e0)<1e-5 )
		  {
		    //debug
		    //std::cerr << "linear case\n";
		    insert_found = true;
		    break;
		  }
	    
	  }
      if (unfinished_insert && !insert_found)
	error("Not all new points are inserted, but no other insertion can be done");
      
      if (insert_found)
	{
	  //debug
	  //std::cerr << "Insert found\n";

	  int insrt = point_idx(i,zinsert);
	  std::vector<lace::vector3d<CREAL> > new_pt;
	  
	  // Three bonds
	  if (ibnd.size()==3)
	    {
	      CREAL b1,b2,b3;
	      int at1,at2,at3;
	      extract_bond(ibnd[0],b1,at1);
	      extract_bond(ibnd[1],b2,at2);
	      extract_bond(ibnd[2],b3,at3);
	      

	      new_pt = triangul3b(geom->coord(at1),b1,geom->coord(at2),b2,
				  geom->coord(at3),b3);

	      //debug
	      /*
		std::cerr << "Three bonds: " << at1 << " " << b1 << " " << at2 << " " << b2 
			<<  at3 << " " << b3 << "\n";
	      std::cerr << "new points: " << new_pt.size() << "\n"; 
	      */
	    }
	  // Bond, angle & dihedral
	  else if (ibnd.size()==1 && iang.size()==1 && idhd.size()==1 )
	    {
	      CREAL b,alpha,gamma;
	      int at1,at2,at3, at22, at33;
	      extract_bond(ibnd[0],b,at3);
	      bool valid = extract_angle(iang[0],alpha,at2,at33);
	      
	      //debug
	      //std::cerr << at3 << " = " << at33 << "\n";

	      if (valid)
		valid = (at3 == at33);
	      if (valid)
		valid = extract_dihedral(idhd[0],gamma,at1,at22,at33);
	      if (valid)
		valid = (at3==at33) && (at2==at22);

	      //debug
	      //std::cerr << "Inserting " << at1  << " " << at2 << " " << at3 << " bond= " 
	      //<< b << " angle= " << alpha << " dhd= " << gamma << "\n";

	      if (!valid)
		error("Given parameters do not allow to locate new point");
	      
	      new_pt.push_back( zpoint( geom->coord(at3), geom->coord(at2), geom->coord(at1),
					b, alpha*pi/180, gamma*pi/180) );
	    }
	  else if (ibnd.size()==1 && iang.size()==1)
	    {
	      CREAL b,alpha;
	      int at1, at2, at22;
	      extract_bond(ibnd[0],b,at2);
	      bool valid = extract_angle(iang[0],alpha,at1,at22);
	      if (valid)
		valid = (at2==at22 && std::abs(alpha-180e0)<1e-5 );
	      if (!valid)
		error("Given parameters do not allow to locate new point");

	      lace::vector3d<CREAL> ndir = geom->coord(at2) - geom->coord(at1);
	      ndir /= norm(ndir);
	      new_pt.push_back( geom->coord(at2) + b*ndir);

	      // debug
	      //std::cerr << at1 << geom->coord(at1) << " " << at2 << geom->coord(at2) 
	      //		<< new_pt[0] << "\n";
	    }
	  else 
	    // fixme - implement later
	    error("Inserting new point implemented only if 1)bond, angle, dihedral; 2) three bonds are given; 3) bond and angle=180 deg;");
	  
	  //for (int j=0; j<new_pt.size(); j++)
	  //  symmtrap(new_pt[j]);

	  lst.set(0,new_pt.size()-1);
	  bool res = false;
	  for (int j=lst.begin(); !lst.end(); j=lst.next())
	    {
	      int inew = geom->nat();
	      //	      parm->push_back(new_pt[j]);
	      geom -> add(point(insrt).atom, new_pt[j]);
	      //geom -> add(point(insrt).atom, mfold->map(new_pt[j]));
	      occupied.push_back(true);
	      //noapply.push_back(false);

	      //geom->build_type_table();
	      //ngbr->build_disttable();
	      //ngbr->build();	      
	      bind(insrt,inew);

	      //debug	      
	      /*
	      std::cerr << "point inserted i= " << insrt << " r= " << geom->coord(inew)<<"\n";
	      for (int ii=0; ii<n_points(); ii++)
		std::cerr << point(ii).nickname << " = "  << bound(ii) << " " 
			  << point(ii).is_bound <<  "\n";
	      */
	      
	      if (point_satisfy(insrt))
		res = insert_next(*lst.copy());

	      //debug
	      //std::cerr << "satisfy= " << res << "\n";
	      //res = true;
	      if (res)
		{
		  //std::cerr  << "alive1\n";
		  delete &lst;
		  //std::cerr << "alive2\n";
		  return true;
		}
	      else
		{
		  //std::cerr << " after not satisfy 0\n";

		  unbind(insrt);
		  //		  std::cerr << " after not satisfy 1\n";
		  geom -> erase(inew);
		  //std::cerr << " after not satisfy 2\n";
		  //parm->pop_back();
		  occupied.pop_back();

		  //std::cerr << " after not satisfy 5\n";
		  //noapply.pop_back();
		  //geom->build_type_table();
		  //ngbr->build_disttable();
		  //ngbr->build();	      

		  //debug
		  //std::cerr << " after not satisfy 10\n";
		}
	    }
	  delete &lst;
	  return false;
	}
      else
	return avoid();
    }

    // -----------------------------------------------------------------

    bool match_next( integer_lister &lst)
    {
      //debug
      //std::cerr << "entering match_next\n";

      // Check if we have remainig search | delete points
      // If so, find the next point to search
      bool unfinished_search = false;
      int isrch=-1, jbnd=-1;
      for (int i=0; i<n_points(); i++)
	if ( !is_bound(i) && ( point_type(i)==zsearch || point_type(i)==zdelete ))
	  {
	    unfinished_search = true;
	    jbnd = search_condition(i);
	    if (jbnd != -1)
	      {
		isrch = i;
		break;
	      }
	  } 

      //debug
      //std::cerr << "isrch= " << isrch << "\n";

      if ( unfinished_search && isrch == -1 )
	error("Search is not complete, but no other point can be matched");
      // Perform the search
      if (unfinished_search)
	{
	  int k = rel_of_point(isrch,jbnd);
	  int ibnd = rel(k).point_defined(0) ? 
	    rel(k).point(0) : rel(k).point(1);
	  index<DIM> at_bnd = bound(ibnd);

	  //debug
	  //std::cerr << " ibnd= " << ibnd << " at_bnd= " << at_bnd << "\n";
	  //rel(k).write(std::cerr);
	  //std::cerr << "\n";
	  
	  lst.set(0,ngbr->n(at_bnd)-1);

	  //std::cerr << "haha1\n";

	  for (int jsrch = lst.begin(); !lst.end(); jsrch = lst.next())
	    {
	      //std::cerr << "haha2\n";
	      index<DIM> at_srch = (*ngbr)(at_bnd,jsrch);

	      //debug
	      //std::cerr << "isrch= " << isrch << " jsrch= " << jsrch << " at_srch= " << at_srch 
	      //<< " r= " << norm(geom->coord(at_bnd)-geom->coord(at_srch)) << "\n";

	      if ( !occupied[at_srch] && 
		   ( point(isrch).atom == "*" || point(isrch).atom == geom -> atom(at_srch) ))
		bind(isrch,at_srch);
	      else continue;

	      //std::cerr << "after continue\n";
	      
	      bool satisfy = point_satisfy(isrch);

	      //debug
	      //std::cerr << "after point_satisfy: " << satisfy <<"\n";	      
	      for (int jrel = 0; jrel < n_rel_of_point(isrch); jrel++)
		{
		  int kk = rel_of_point(isrch,jrel);
		  if ( rel(kk).is_defined() && ! rel(kk).satisfy() )
		    {
		      satisfy = false;
		      break;
		    }
		}

	      if (satisfy)
		satisfy = match_next(*lst.copy());

	      //std::cerr << "after match_next: " << satisfy <<"\n";

	      if (satisfy)
		{
		  delete &lst;
		  return true;
		}
	      else
		unbind(isrch);
	    }
	  delete &lst;
	  return false;
	}
      else
	{
	  // mark atoms to delete
	  for (int i=0; i<n_points(zdelete); i++)
	    geom->shadow(point(i,zdelete).bound) = true;

	  // insert atoms to be inserted
	  bool res;
	  if ( mfold == NULL)
	    res = insert_next(*lst.copy());
	  else
	    res = insert_next_surf(*lst.copy());	    
	  //std::cerr << "alive3\n";
	  delete &lst;
	  //std::cerr << "alive4\n";
	  return res;
	}
    }

    // ------------------------------------------------------------------

    void setngbrdist()
    {
      ngbr->default_distance = 0;
      ngbr->clear_distance();

      for (int i = 0; i<n_rel(); i++)
	if (rel(i).is_bond() && !rel(i).is_exact())
	  {
	    STRING at1, at2;
	    at1 = point(rel(i).point(0)).atom;
	    at2 = point(rel(i).point(1)).atom;

	    if (at2=="*")
	      {
		STRING at = at2; 
		at2 = at1;
		at1 = at;
	      }

	    if (at1 == "*" && at2 == "*")
	      {
		for (int i=0; i<geom->n_atom_types(); i++)
		  for (int j=0; j<=i; j++)
		    ngbr->set_distance(geom->atom_of_type(i),geom->atom_of_type(j),rel(i).vmax);
	      }
	    else if (at1 == "*")
	      {
		for (int i=0; i<geom->n_atom_types(); i++)
		  ngbr->set_distance(geom->atom_of_type(i),at2,rel(i).vmax);
	      }
	    else if ( ngbr->distance(at1,at2) < rel(i).vmax)
	      ngbr->set_distance(at1,at2,rel(i).vmax);
	  }
    }

    // -----------------------------------------------------------------

    void search_next(std::vector<std::vector<int> > & matches,
		     std::vector<std::vector<CREAL> > & vals,
		     std::vector<CREAL> & cost)
    {
      //debug
      //std::cerr << "entering match_next\n";

      // Check if we have remainig search | delete points
      // If so, find the next point to search
      bool unfinished_search = false;
      int isrch=-1, jbnd=-1;
      for (int i=0; i<n_points(); i++)
	//	if ( !is_bound(i) && ( point_type(i)==zsearch || point_type(i)==zdelete ))
	// Here all points are considered as search points
	if ( !is_bound(i) )
	  {
	    unfinished_search = true;
	    jbnd = search_condition(i);
	    if (jbnd != -1)
	      {
		isrch = i;
		break;
	      }
	  } 

      //debug
      //std::cerr << "isrch= " << isrch << "\n";

      if ( unfinished_search && isrch == -1 )
	error("Search is not complete, but no other point can be matched");
      // Perform the search
      if (unfinished_search)
	{
	  int k = rel_of_point(isrch,jbnd);
	  int ibnd = rel(k).point_defined(0) ? 
	    rel(k).point(0) : rel(k).point(1);
	  index<DIM> at_bnd = bound(ibnd);

	  //debug
	  //std::cerr << " ibnd= " << ibnd << " at_bnd= " << at_bnd << "\n";
	  //rel(k).write(std::cerr);
	  //std::cerr << "\n";
	  
	  for (int jsrch = 0; jsrch < ngbr->n(at_bnd); jsrch++)
	    {
	      //std::cerr << "haha2\n";
	      index<DIM> at_srch = (*ngbr)(at_bnd,jsrch);

	      //debug
	      //std::cerr << "isrch= " << isrch << " jsrch= " << jsrch << " at_srch= " << at_srch 
	      //<< " r= " << norm(geom->coord(at_bnd)-geom->coord(at_srch)) << "\n";

	      if ( !occupied[at_srch] && 
		   ( point(isrch).atom == "*" || point(isrch).atom == geom -> atom(at_srch) ))
		bind(isrch,at_srch);
	      else continue;

	      //std::cerr << "after continue\n";
	      
	      bool satisfy = point_satisfy(isrch);

	      //debug
	      //std::cerr << "after point_satisfy: " << satisfy <<"\n";	      
	      for (int jrel = 0; jrel < n_rel_of_point(isrch); jrel++)
		{
		  int kk = rel_of_point(isrch,jrel);
		  if ( rel(kk).is_defined() && ! rel(kk).satisfy() )
		    {
		      satisfy = false;
		      break;
		    }
		}

	      if (satisfy)
		search_next(matches,vals,cost);

	      //std::cerr << "after match_next: " << satisfy <<"\n";
	      
	      unbind(isrch);

	    }
	}
      else
	{
	  // Everything is found
	  
	  matches.push_back(std::vector<int>());
	  for (int i=0; i<n_points(); i++)
	    matches[matches.size()-1].push_back(point(i).bound);

	  vals.push_back(std::vector<CREAL>());
	  for (int i=0; i<n_rel(); i++)
	    vals[vals.size()-1].push_back(rel(i).value());

	  //Calculate cost
	  CREAL S=0e0;
	  if (geom->gettype() & qtype_xgeometry)
	    {
	      xtr_geometry<DIM,CREAL> * xgeom = (xtr_geometry<DIM,CREAL> *)geom;
	      if ( xgeom -> n_xreal()>0 )
		for (int i=0; i<n_points(); i++)
		  if ( point_type(i)==zsearch || point_type(i)==zinsert)
		    S += xgeom -> xtr_real(0,point(i).bound);
	    }
	  cost.push_back(S);
	    
	}
    }

    // ------------------------------------------------------------------

    void search(std::vector<std::vector<int> > & matches,
		std::vector<std::vector<CREAL> > & vals,
		std::vector<CREAL> & cost)
    {
      unbind_all();

      for (int i=0; i<geom->nat(); i++)
	if ( point(0).atom == "*" || point(0).atom == geom -> atom(i) )
	  {
	    bind(0,i);
	    search_next(matches,vals,cost);
	    unbind(0);
	  }
    }

    bool apply(integer_lister &lst)
    {
      //prepare
      unbind_all();

      //ngbr->build_disttable();
      //ngbr->build();

      /*
      for (int i=0; i<geom->nat(); i++)
	std::cerr << (occupied[i] ? "1" : "0");
      std::cerr << "\n";
      */
      
      std::cerr << " pri= " << priority << "\n";
      for (int i=0; i<noapply.size(); i++)
	std::cerr << (noapply[i] ? "1" : "0");
      std::cerr << "\n\n";
      
      bool res = false;
            
      // Match first point

      lst.set(0,geom->nat()-1 );
      for (int i=lst.begin(); !lst.end(); i=lst.next())
	// fixme - temporary commented
	//if (!noapply[i])
	  {
	    //std::cerr << " matching 0 to " << i << "\n";
	    bind(0,i);
	    if ( match_next(*lst.copy()) )
	      {
		res = true;
		break;
	      }
	    else
	      noapply[i] = true;
	    unbind(0);
	  }
      if (res)
	{
	  // delete marked atoms
	  for (int i=geom->nat()-1; i>=0; i--)
	    if (geom->shadow(i))
	      {
		geom->erase(i);
		//parm->erase(parm->begin()+i);
	      }
	}
      return res;
    }

    /*
    bool init( parametric_surface<CREAL,charT,traits> &m, 
	       std::vector<lace::vector2d<CREAL> > &p, 
	       geometry<DIM, CREAL, ATLABEL, charT, traits> &g)
    {
      //prepare
      geom = &g;
      mfold = &m;
      parm = &p;
    }
    */
    
    void init_noapply()
    {
      noapply.resize(geom->nat());
      for (int i=0; i<geom->nat(); i++)
	noapply[i] = false;

      //debug
      /*
      std::cout << geom->gettype() << " " << qtype_xgeometry << " " 
		<< qtype_geometry << " " << qtype_data<double>::type << " "
		<< qtype_dim3 << "\n";
      */

      if (geom->gettype() & qtype_xgeometry)
	{
	  //std::cout << "xgeom\n";
	  xtr_geometry<DIM,CREAL> * xgeom = (xtr_geometry<DIM,CREAL> *)geom;

	  // fixme - implement proper field handling!
	  if ( xgeom->n_xbool()>0)
	    for (int i=0; i<geom->nat(); i++)
	      noapply[i] = xgeom->xtr_bool(0,i);
	}
    }

    //debug
    typename geometry<DIM, CREAL,TRANSFORM>::neighbours_table *ngbr1;

    void init_surf( geometry<DIM, CREAL,TRANSFORM> &g, CREAL st_rad = 0e0)
    {
      //prepare
      geom = &g;
      geom -> add_dependent(this);
      ngbr = new typename geometry<DIM, CREAL,TRANSFORM>::neighbours_table(g);
      mfold = & g.symm().mfold();
      //      parm = &p;
      symmtrap_radius = st_rad;

      geom -> build_type_table();
      geom -> update_types = true;
      
      setngbrdist();
      ngbr->build_disttable();
      ngbr->build();
      init_noapply();

    }

    // ----------------------------------------------------------

    void init( geometry<DIM, CREAL,TRANSFORM> &g, CREAL st_rad = 0e0)
    {
      //prepare
      geom = &g;
      geom -> add_dependent(this);

      ngbr = new typename geometry<DIM, CREAL,TRANSFORM>::neighbours_table(g);
     
      //std::cerr << "ngbr created\n";

      mfold = NULL;
      symmtrap_radius = st_rad;

      geom -> build_type_table();
      geom -> update_types = true;

      //std::cerr << "alive1\n";
      setngbrdist();
      ngbr->build_disttable();
      ngbr->build();

      init_noapply();

      //std::cerr << "init done\n";
      //debug
      // ngbr1 = new typename geometry<DIM, CREAL,TRANSFORM>::neighbours_table(g);
      // typename geometry<DIM, CREAL,TRANSFORM>::neighbours_table *ngbr2=ngbr;
      // ngbr=ngbr1;
      // setngbrdist();
      // ngbr = ngbr2;
      // ngbr1->build_disttable();
      // 	  //debug
      // ngbr1 -> reference_build();
      // std::ofstream f1("ngbr1"),f2("ngbr2");
      // f1 << name() << "\n";
      // f2 << name() << "\n";
      // write_ngbr<DIM, CREAL,TRANSFORM>(f1,*ngbr);
      // write_ngbr<DIM, CREAL,TRANSFORM>(f2,*ngbr1);
      // f1.close();
      // f2.close();
      // std::cout << name() << " init\n";
      // system("diff ngbr1 ngbr2");
      // if (! (*ngbr==*ngbr1))
      // 	exit(1);
      //end debug

    }
    
    // ----------------------------------------
    
    void unmark(std::vector<int> & touched, int d)
    {
      if (d==0)
	{
	  for (int i=0; i<touched.size(); i++)
	    noapply[touched[i]]=false;
	  return;
	}

      for (int i=0; i<touched.size(); i++)
	for (int j=0; j<ngbr->n(i); j++)
	  {
	    int k = (*ngbr)(i,j);
	    bool already=false;
	    for (int l=0; l<touched.size(); l++)
	      if (touched[l]==k)
		{
		  already=true;
		  break;
		}
	    if (!already)
	      touched.push_back(k);
	  }
      unmark(touched,d-1);
    }

    // ----------------------------------------

    virtual void added(bool done)
    {
      //std::cerr << "added\n";
      if (done)
	{
	  ngbr -> added(true);

	  // //debug
	  // ngbr1 -> reference_build();
	  // std::ofstream f1("ngbr1"),f2("ngbr2"),f3("geom");
	  // write_ngbr<DIM, CREAL,TRANSFORM>(f1,*ngbr);
	  // write_ngbr<DIM, CREAL,TRANSFORM>(f2,*ngbr1);
	  // write_xyz(f3,*geom);
	  // f1.close();
	  // f2.close();
	  // f3.close();
	  // std::cout << name() << " added " << geom->nat()-1 << "\n";
	  // system("diff ngbr1 ngbr2");
	  // if (! (*ngbr==*ngbr1))
	  //   exit(1);
	  // //end debug

	  noapply.push_back(false);
	  std::vector<int> touched;
	  touched.push_back( geom->nat()-1 );
	  unmark(touched,depth());
	}
    }

    virtual void inserted(int i, bool done)
    {
      //std::cerr << "ins\n";
      if (done)
	{
	  ngbr -> inserted(i,true);

	  // //debug
	  // ngbr1 -> reference_build();
	  // std::ofstream f1("ngbr1"),f2("ngbr2");
	  // write_ngbr<DIM, CREAL,TRANSFORM>(f1,*ngbr);
	  // write_ngbr<DIM, CREAL,TRANSFORM>(f2,*ngbr1);
	  // f1.close();
	  // f2.close();
	  // std::cout << name() << " inserted " << i << "\n";
	  // system("diff ngbr1 ngbr2");
	  // if (! (*ngbr==*ngbr1))
	  //   exit(1);
	  // //end debug

	  noapply.insert(noapply.begin()+i,false);
	  std::vector<int> touched;
	  touched.push_back( i );
	  unmark(touched,depth());
	}
    }

    virtual void erased(int i, bool done)
    {
      if (!done)
	{
	  std::vector<int> touched;
	  touched.push_back( i );
	  unmark(touched,depth());
	  noapply.erase(noapply.begin()+i);
	  ngbr -> erased(i,false);
	}
      else
	{
	  //debug
	  // ngbr1 -> reference_build();
	  // std::ofstream f1("ngbr1"),f2("ngbr2"),f3("geom");
	  // write_ngbr<DIM, CREAL,TRANSFORM>(f1,*ngbr);
	  // write_ngbr<DIM, CREAL,TRANSFORM>(f2,*ngbr1);
	  // write_xyz(f3,*geom);
	  // f1.close();
	  // f2.close();
	  // f3.close();
	  // std::cout << name() << " deleted " << i << "\n";
	  // system("diff ngbr1 ngbr2");
	  // if (! (*ngbr==*ngbr1))
	  //   exit(1);
	  //end debug
	}
      //std::cerr << "del\n";
    }

  };

  template <int DIM,class CREAL=double, class TRANSFORM = periodic_cell<DIM,CREAL> >   
  zpattern<DIM,CREAL,TRANSFORM> * decl2zpt(qpp_declaration * decl)
  {
    if (decl -> category() != "zpattern")
      decl -> error("This declaration does not define z-pattern");
    zpattern<DIM,CREAL,TRANSFORM> * res = new zpattern<DIM,CREAL,TRANSFORM>(decl -> name());

    for (int i=0; i<decl->n_parm(); i++)
      {
	STRING pname = decl->nested_parm(i).name();
	STRING pval  = ((qpp::qpp_parameter<STRING>*)(&decl->nested_parm(i))) -> value();
	if (pname=="priority")
	  s2t<int>(pval,res -> priority);
      }

    for (int i=0; i<decl->n_decl(); i++)
      if (decl->nested_decl(i).gettype() & qtype_declaration)
	{
	  STRING cat = decl->nested_decl(i).category();

	  //debug
	  //std::cerr << "cat: " << cat << "\n";

	  qpp_declaration * d1 = (qpp_declaration *)(&decl->nested_decl(i));
	  if (cat=="search" || cat=="insert" || cat=="delete" || cat=="avoid")
	    {
	      typename zpattern<DIM,CREAL,TRANSFORM>::ptype zop;
	      if (cat=="search") 
		zop = zpattern<DIM,CREAL,TRANSFORM>::zsearch;
	      else if (cat=="insert") 
		zop = zpattern<DIM,CREAL,TRANSFORM>::zinsert;
	      else if (cat=="delete") 
		zop = zpattern<DIM,CREAL,TRANSFORM>::zdelete;
	      else if (cat=="avoid")
		zop = zpattern<DIM,CREAL,TRANSFORM>::zavoid;

	      for (int j=0; j<d1->n_parm(); j++)
		{
		  qpp_parameter<STRING> * pt = (qpp_parameter<STRING> *)(&d1->nested_parm(j));
		  res -> add_point(
		    typename zpattern<DIM,CREAL,TRANSFORM>::zpt_point(pt->name(),pt->value()),zop);
		}
	    }
	  if (cat=="bond" || cat=="angle" || cat=="dihedral" || cat=="surfangle")
	    {
	      STRING newvar = decl->nested_decl(i).name();

	      int npt;
	      if (cat=="bond")
		npt=2;
	      else if ( cat=="angle"|| cat=="surfangle")
		npt=3;
	      else if ( cat=="dihedral" )
		npt=4;

	      //debug
	      //std::cerr << "pt def " << " cat= " << cat << " npt= " << npt << "\n";
	      
	      STRING at[4], sval1, sval2;
	      bool exact = (d1 -> n_parm() == npt+1);
	      if (!exact && (d1 -> n_parm() != npt+2))
		d1 -> error("Bond declaration in z-pattern must have 3 or 4 parameters");

	      if (exact && newvar!="")
		d1 -> error("Only range relations can be used to define new variable");

	      CREAL val1, val2;
	      typename zpattern<DIM,CREAL,TRANSFORM>::linear_dependence * ld = NULL;

	      for (int pt=0; pt<npt; pt++)
		at[pt] = ((qpp_parameter<STRING>*)&(d1->nested_parm(pt)))->value();
	      
	      qpp::qpp_parameter<STRING> * pval1 = (qpp_parameter<STRING>*)&(d1->nested_parm(npt));
	      if (pval1->n_parm() > 0)
		{
		  // compile lindep instruction
		  if (pval1->name()!="lindep" && pval1->name()!="linear")
		    d1->error("lindep statement expected");

		  CREAL val0, coeff;
		  STRING var, sval0, scoeff;

		  sval0 = ((qpp_parameter<STRING>*)&(pval1->nested_parm(0)))->value();
		  if (!s2t<CREAL>(sval0, val0))
		    if (!s2t<CREAL>(decl->env(sval0,i),val0) )
		      d1->error("Real number or previously defined constant expected");

		  ld = new typename zpattern<DIM,CREAL,TRANSFORM>::linear_dependence(val0,*res);
		  int nf=1;
		  while( nf < pval1->n_parm() )
		    {
		      if (nf+1==pval1->n_parm())
			d1->error("Wrong number of parameters in lindep");
		      var    = ((qpp_parameter<STRING>*)&(pval1->nested_parm(nf)))->value();
		      scoeff = ((qpp_parameter<STRING>*)&(pval1->nested_parm(nf+1)))->value();

		      if (!s2t<CREAL>(scoeff, coeff))
			if (!s2t<CREAL>(decl->env(scoeff,i),coeff) )
			  d1->error("Real number or previously defined constant expected");
		      
		      ld = & ld->term(var,coeff);

		      nf += 2;
		    }
		}
	      else
		{
		  sval1 = ((qpp_parameter<STRING>*)&(d1->nested_parm(npt)))->value();
		  if (!s2t<CREAL>(sval1, val1))
		    if (!s2t<CREAL>(decl->env(sval1,i),val1) )
		      //fixme
		      d1->error("3th parameter of bond declaration must be real number or previously defined constanct");

		  if (exact)
		    ld = new typename zpattern<DIM,CREAL,TRANSFORM>::linear_dependence(val1,*res);
		}

	      if (!exact)
		{
		  sval2 = ((qpp_parameter<STRING>*)&(d1->nested_parm(npt+1)))->value();
		  if (!s2t<CREAL>(sval2,val2))
		    if (!s2t<CREAL>(decl->env(sval2,i),val2) )
		      d1->error("4th parameter of bond declaration must be real number or previously defined constanct");
		}

	      typename zpattern<DIM,CREAL,TRANSFORM>::geometry_relation * rel;

	      if (cat=="bond")
		{
		  if (exact)
		    rel = new typename zpattern<DIM,CREAL,TRANSFORM>::
		      bond_relation(at[0],at[1],*ld,*res);
		  else
		    rel = new typename zpattern<DIM,CREAL,TRANSFORM>::
		      bond_relation(at[0],at[1],val1,val2,*res,newvar);
		}
	      else if (cat=="angle")
		{
		  if (exact)
		    rel = new typename zpattern<DIM,CREAL,TRANSFORM>::
		      angle_relation(at[0],at[1],at[2],*ld,*res);
		  else
		    rel = new typename zpattern<DIM,CREAL,TRANSFORM>::
		      angle_relation(at[0],at[1],at[2],val1,val2,*res,newvar);
		}
	      else if (cat=="surfangle")
		{
		  //debug
		  //std::cerr << "surfangle\n";

		  if (exact)
		    rel = new typename zpattern<DIM,CREAL,TRANSFORM>::
		      surfangle_relation(at[0],at[1],at[2],*ld,*res);
		  else
		    rel = new typename zpattern<DIM,CREAL,TRANSFORM>::
		      surfangle_relation(at[0],at[1],at[2],val1,val2,*res,newvar);
		}
	      else if (cat=="dihedral")
		{
		  if (exact)
		    rel = new typename zpattern<DIM,CREAL,TRANSFORM>::
		      dyhedral_relation(at[0],at[1],at[2],at[3],*ld,*res);
		  else
		    rel = new typename zpattern<DIM,CREAL,TRANSFORM>::
		      dyhedral_relation(at[0],at[1],at[2],at[3],val1,val2,*res,newvar);
		}

	      res -> add_relation(*rel);

	    }
	}

    return res;
  }
  

};

#endif
