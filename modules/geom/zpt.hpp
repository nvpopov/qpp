#ifndef _QPP_ZPT
#define _QPP_ZPT

#include <geom/geom.hpp>
#include <geom/zmt.hpp>
#include <io/qppdata.hpp>
#include <mathf/intlst.hpp>
#include <string>
#include <iostream>
#include <boost/format.hpp>

namespace qpp{

  std::string ptype_name [] = {"search", "avoid", "delete", "insert"};


  template <int DIM,class VALTYPE=double, class ATLABEL = std::string, 
	    class charT = char, class traits = std::char_traits<charT> >   
  class zpattern : public qpp_object<charT,traits> {

    using typename qpp_object<charT,traits>::string;
    string _name, _error;

    geometry<DIM,VALTYPE,ATLABEL,charT,traits> *geom;
    parametric_surface<VALTYPE,charT,traits> *mfold;
    std::vector<lace::vector2d<VALTYPE> > *parm;   
    
  public:

    VALTYPE geomtol;

    zpattern(const string & __name = ""){_name = __name; geomtol = default_geomtol;}

    zpattern(geometry<DIM,VALTYPE,ATLABEL,charT,traits> & g, const string & __name = "")
    {
      geom = &g;
      _name = __name;
      geomtol = default_geomtol;
    }

    // ---------------- "Points" - named points to be identified with atoms --------------

    struct zpt_point{
      string nickname;
      ATLABEL atom;
      bool is_bound;
      index<DIM> bound;

      zpt_point()
      {	is_bound = false; }

      zpt_point(string const & nick, ATLABEL const & at)
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

    inline ptype point_type(int i){ return points_types[i];}

    inline zpt_point & point(int i, int ptp) { return *(points_registry[points_idx[ptp][i]]);}

    inline int point_idx(int i, int ptp) { return points_idx[ptp][i];}

    inline int n_points(){ return points_registry.size();}

    inline int n_points(int ptp){ return points_idx[ptp].size();}

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

    class linear_dependence : public qpp_object<charT,traits>{
      using typename qpp_object<charT,traits>::string;
      zpattern<DIM,VALTYPE,ATLABEL,charT,traits> * owner;
      string _name;

      VALTYPE v0;
      std::vector<VALTYPE> coeffs;
      std::vector<string> varnames;
      std::vector<int> varidx;

    public:

      linear_dependence(VALTYPE _v0, zpattern<DIM,VALTYPE,ATLABEL,charT,traits> & _owner,
			string const &__name = "")
      { 
	v0 = _v0; 
	_name = __name;
	owner = & _owner;
      }

      linear_dependence & term(string const & vn, VALTYPE cc)
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
	  owner->error("Variable " + vn + " is not defined in zpattern realtions");
	return *this;
      }

      int n_terms()
      { return varnames.size();}

      VALTYPE value()
      {
	VALTYPE res = v0;
	for (int i=0; i<varidx.size(); i++)
	  res += coeffs[i]*owner->relation_registry[varidx[i]] -> value();
	return res;
      }

      VALTYPE is_defined()
      {
	bool res = true;
	for (int i = 0; i<varidx.size(); i++)
	  {
	    //	    std::cout << "term " << i << " rel " << varidx[i] << "\n";

	    if (!owner -> rel(varidx[i]).is_defined())
	      {
		res = false;
		break;
	      }
	  }
	return res;
      }

      virtual string category()
      { return "lindep";}

      virtual string name()
      { return _name;}

      virtual int gettype()
      {}

      virtual void error(string const &){}
      
      virtual string error(){return "";}

      virtual void write(std::basic_ostream<charT,traits> &os, int offset=0)
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

    class geometry_relation : public qpp_object<charT,traits>{      
    protected:

      using typename qpp_object<charT,traits>::string;

      zpattern<DIM,VALTYPE,ATLABEL,charT,traits> * owner;
      string _name;

      std::vector<int> _points;
      bool exact;
      linear_dependence * _formula;

      void match_points()
      {
	_points.resize(n_points());
	for (int i=0; i<n_points(); i++)
	  {
	    //debug
	    //std::cout << i << " " << point_nick(i) << "\n";

	    int k;
	    _points[i] = -1;
	    for (k=0; k<owner->n_points(); k++)
	      {
		// debug
		//std::cout << k << "\n";
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
      VALTYPE vmin,vmax;

      virtual VALTYPE value() =0;
      virtual int n_points() =0;
      virtual string point_nick(int i) =0;      

      virtual bool satisfy()
      {
	//std::cout << "psat: ";
	//write(std::cout);
	//debug();
	//std::cout << " defined= " << is_defined() << "\n";
	if (is_defined())
	  {
	    if (exact)
	      {
		//std::cout << "value= " << value() << " formula= " << _formula -> value() 
		//	  << " diff= " << boost::format("%25.20f\n")%(value() - _formula -> value());
		return _formula -> is_defined() ? std::abs(value() - _formula -> value()) <= owner -> geomtol : false;
		
	      }
	    else
	      {
		//std::cout << " " << vmin <<  " " << vmax << " " << value() << "\n";
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
      
      virtual string name()
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

      virtual void error(string const &){}

      virtual string error(){return "";}

    };

    //----------------------------------------------

    class bond_relation : public geometry_relation {
      string at1, at2;

    protected:
      //      using typename zpattern<DIM,VALTYPE,ATLABEL,charT,traits>::geometry_relation::owner;
      using geometry_relation::owner;
      using geometry_relation::vmin;
      using geometry_relation::vmax;
      using geometry_relation::_formula;
      using geometry_relation::exact;
      using geometry_relation::is_defined;
      using geometry_relation::_name;
      using geometry_relation::match_points;
      
    public:

      bond_relation(string const & _at1, string const &_at2, VALTYPE _bmin, VALTYPE _bmax, 
		    zpattern<DIM,VALTYPE,ATLABEL,charT,traits> & z, string const &__name = "")
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

      bond_relation(string const & _at1, string const &_at2, linear_dependence &__formula,
		    zpattern<DIM,VALTYPE,ATLABEL,charT,traits> & z, string const &__name = "")
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

      virtual VALTYPE value()
      {
	if (!is_defined())
	  return -1;
	else
	  {
	    index<DIM> i1 = owner->point(point(0)).bound,	      
	      i2 = owner->point(point(1)).bound;
	    return norm(owner->geom->full_coord(i1) - owner->geom->full_coord(i2));
	  }
      }

      virtual int n_points(){return 2;}

      virtual string point_nick(int i)
      {
	if (i==0)
	  return at1;
	else if (i==1)
	  return at2;
      }
      
      virtual string category()
      {
	return "bond";
      }

      
      virtual int gettype()
      { return qppdata_zpt_bond; }
      
      virtual void write(std::basic_ostream<charT,traits> &os, int offset=0)
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
      string at1, at2, at3;

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

      angle_relation(string const & _at1, string const &_at2, string const &_at3,
		    VALTYPE _amin, VALTYPE _amax, 
		     zpattern<DIM,VALTYPE,ATLABEL,charT,traits> & z, string const &__name = "")
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

      angle_relation(string const & _at1, string const &_at2, string const &_at3, linear_dependence &__formula,
		    zpattern<DIM,VALTYPE,ATLABEL,charT,traits> & z, string const &__name = "")
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

      virtual VALTYPE value()
      {
	if (!is_defined())
	  return -1;
	else
	  {
	    index<DIM> 
	      i1 = owner->point(point(0)).bound,	      
	      i2 = owner->point(point(1)).bound,
	      i3 = owner->point(point(2)).bound;
	    lace::vector3d<VALTYPE> n1, n2;
	    n1 = owner->geom->full_coord(i1) - owner->geom->full_coord(i2);
	    n2 = owner->geom->full_coord(i3) - owner->geom->full_coord(i2);
	    n1 /= norm(n1);
	    n2 /= norm(n2);

	    return std::acos(scal(n1,n2))*180/pi;
	  }
      }
      
      virtual int n_points(){return 3;}

      virtual string point_nick(int i)
      {
	if (i==0)
	  return at1;
	else if (i==1)
	  return at2;
	else if (i==2)
	  return at3;
      }
      
      virtual string category()
      {
	return "angle";
      }

      
      virtual int gettype()
      { return qppdata_zpt_angle; }
      
      virtual void write(std::basic_ostream<charT,traits> &os, int offset=0)
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
      string at1, at2, at3;

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

      surfangle_relation(string const & _at1, string const &_at2, string const &_at3,
			 VALTYPE _amin, VALTYPE _amax, 
			 zpattern<DIM,VALTYPE,ATLABEL,charT,traits> & z, string const &__name = "")
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

      surfangle_relation(string const & _at1, string const &_at2, string const &_at3, 
			 linear_dependence &__formula,
			 zpattern<DIM,VALTYPE,ATLABEL,charT,traits> & z, string const &__name = "")
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

      virtual VALTYPE value()
      {
	if (!is_defined())
	  return -1;
	else
	  {
	    index<DIM> 
	      i1 = owner->point(point(0)).bound,	      
	      i2 = owner->point(point(1)).bound,
	      i3 = owner->point(point(2)).bound;
	    /*	    lace::vector3d<VALTYPE> n1, n2, nperp;
	    n1 = owner->geom->full_coord(i1) - owner->geom->full_coord(i2);
	    n2 = owner->geom->full_coord(i3) - owner->geom->full_coord(i2);
	    nperp = owner -> mfold -> normal( (*(owner -> parm))[i2] );

	    n1 -= nperp*scal(n1,nperp);
	    n2 -= nperp*scal(n2,nperp);

	    n1 /= norm(n1);
	    n2 /= norm(n2);
	    */
	    return owner->mfold->surface_angle((*owner->parm)[i1],
					       (*owner->parm)[i2],(*owner->parm)[i3])*180/pi;
	  }
      }
      
      virtual int n_points(){return 3;}

      virtual string point_nick(int i)
      {
	if (i==0)
	  return at1;
	else if (i==1)
	  return at2;
	else if (i==2)
	  return at3;
      }
      
      virtual string category()
      {
	return "surfangle";
      }

      
      virtual int gettype()
      { return qppdata_zpt_surfangle; }
      
      virtual void write(std::basic_ostream<charT,traits> &os, int offset=0)
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
      string at1, at2, at3, at4;

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

      dyhedral_relation(string const & _at1, string const &_at2, string const &_at3, string const &_at4,
			VALTYPE _dmin, VALTYPE _dmax, 
			zpattern<DIM,VALTYPE,ATLABEL,charT,traits> & z, string const &__name = "")
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

      dyhedral_relation(string const & _at1, string const &_at2, string const &_at3, string const &_at4, 
			linear_dependence &__formula,
			zpattern<DIM,VALTYPE,ATLABEL,charT,traits> & z, string const &__name = "")
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

      virtual VALTYPE value()
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

	    return get_dyhedral(owner->geom->full_coord(i1), owner->geom->full_coord(i2),
				owner->geom->full_coord(i3), owner->geom->full_coord(i4));
	  }
      }
      
      virtual int n_points(){return 4;}

      virtual string point_nick(int i)
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
      
      virtual string category()
      {
	return "dihedral";
      }

      
      virtual int gettype()
      {	return qppdata_zpt_dihedral; }
      
      virtual void write(std::basic_ostream<charT,traits> &os, int offset=0)
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
      //std::cout << j << " ";
      //rel.write(std::cout);
      //std::cout << "\n";
      
      if ( _rel_of_point.size() != n_points() )
	{
	  _rel_of_point.resize(n_points());
	  //std::cout << "haha\n";
	}
      for (int i=0; i<rel.n_points(); i++)
	{
	  //std::cout << "adding " << j << " to " << rel.point(i) << "\n";
	  _rel_of_point[rel.point(i)].push_back(j);
	}
    }
    
    inline int n_rel()
    { return relation_registry.size();}
    
    inline geometry_relation & rel(int i)
    { return *relation_registry[i];}

    inline int n_rel_of_point(int i)
    { return _rel_of_point[i].size();}

    inline int rel_of_point(int i, int j)
    { return _rel_of_point[i][j];}

    inline int n_point_of_rel(int i)
    { return rel(i).n_points();}

    inline int point_of_rel(int i, int j)
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

    virtual string category()
    { return "zpattern"; }

    virtual string name()
    { return _name; }
      
    void setname(string __name)
    { _name = __name; }

    virtual int gettype()
    { return qppdata_zpattern;}
      
    virtual void error(string const & what)
    { 
      _error = what;
      throw new qpp_exception<charT,traits>(this);
    }
    
    virtual string error()
    {
      return _error;
    }
    
    virtual void write(std::basic_ostream<charT,traits> &os, int offset=0)
    {
      for (int k=0; k<offset; k++) os << " ";
      os << "zpattern";
      if (_name != "")
	os << " " << _name;
      os << "{\n";
      for (int ptp = zsearch; ptp <= zinsert; ptp++)
	if (n_points(ptp)>0)
	  {
	    for (int k=0; k<offset+2; k++) os << " ";
	    os << ptype_name[ptp] << "(";
	    for (int k=0; k<n_points(ptp); k++)
	      os << point(k,ptp).nickname<<"=" << point(k,ptp).atom 
		 << (k<n_points(ptp)-1 ? "," : "");	  
	    os << ");\n";
	  }

      //debug
      //for (int i=0; i<points_registry.size(); i++)
      //	std::cout << points_registry[i]->nickname << " " << i << "\n";

      for (int i=0; i<n_rel(); i++)
	{
	  relation_registry[i]->write(os,offset+2);
	  os << ";\n";
	}
      os << "}\n";
    }

    void debug()
    {     
      for (int p=zsearch; p<=zinsert; p++)
	{
	  std::cout << boost::format("%-8s") % ptype_name[p];
	  for (int i=0; i<n_points(p); i++)
	    std::cout << boost::format("%3i") % points_idx[p][i];
	  std::cout << "\n";
	}
	    

      for (int i=0; i<n_rel(); i++)
	{
	  std::cout << boost::format("%3i ") % i;
	  int t = rel(i).gettype();
	  if (t==qppdata_zpt_bond)
	    std::cout << "b";
	  else if (t==qppdata_zpt_angle)
	    std::cout << "a"; 
	  else if (t==qppdata_zpt_dihedral)
	    std::cout << "d";

	  for (int j=0; j<rel(i).n_points(); j++)
	    std::cout << boost::format("%3i")%rel(i).point(j);

	  if (rel(i).is_exact())
	    std::cout << " exact";
	  std::cout << "\n";	    
	    
	}
      for (int i=0; i<n_points(); i++)
	{
	  std::cout << boost::format("%3i %-10s %-5s %-8s") % i % point(i).nickname % point(i).atom % 
	    ptype_name[points_types[i]];
	  for (int j=0; j < n_rel_of_point(i); j++)
	    std::cout << boost::format("%4i ") % rel_of_point(i,j);
	  std::cout << "\n";
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
	  //std::cout << j << " " << k << " ";
	  //rel(k).write(std::cout);
	  //std::cout << "\n";
	  
	  if ( rel(k).is_exact() && rel(k).formula().is_defined() && rel(k).n_undefined()==1 )
	    {
	      if (rel(k).gettype() == qppdata_zpt_bond)
		ibnd.push_back(k);
	      else  if (rel(k).gettype() == qppdata_zpt_angle || rel(k).gettype() == qppdata_zpt_surfangle)
		iang.push_back(k);
	      else if (rel(k).gettype() == qppdata_zpt_dihedral)
		idhd.push_back(k);
	    }
	}
    }

    // ------------------------------------------------------------------

    void unbind_all()
    {
      occupied.clear();
      occupied.resize(geom->nat(),false);
      //      noapply.clear();
      //noapply.resize(geom->nat(),false);
      for (int i=0; i<n_points(); i++)
	unbind(i);
    }

    // ---------------------------------------------------------------------

    bool point_satisfy(int i)
    {
      bool res = true;
      for (int j=0; j<n_rel_of_point(i); j++)
	{//debug
	  //rel(rel_of_point(i,j)).write(std::cout);
	  //std::cout << " " << rel(rel_of_point(i,j)).value() << "\n";
	  
	if ( rel(rel_of_point(i,j)).is_defined() && !rel(rel_of_point(i,j)).satisfy() )
	  {
	    res = false;
	    break;
	  }
	}
      return res;
    }

    // ---------------------------------------------------------------------
    /*
    bool match_next(integer_lister &lst)
    {
    }
    
    // ------------------------------------------------------------------

    bool apply( geometry<DIM, VALTYPE, ATLABEL, charT, traits> &g, integer_lister &lst)
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
      //std::cout << "ENtering avoid\n";

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

	  //std::cout << "Avoiding: " << iavd << " " << point(iavd).nickname << "\n";

	  int jbnd = search_condition(iavd);
	  if (jbnd == -1)
	    error("Point " + point(iavd).nickname + " has no bonding condition to be searched for");

	  int k = rel_of_point(iavd,jbnd);
	  int ibnd = rel(k).point_defined(0) ? 
	    rel(k).point(0) : rel(k).point(1);
	  index<DIM> at_bnd = bound(ibnd);

	  //std::cout << "bonding to "<< ibnd << " " << point(ibnd).nickname << " = " << at_bnd << "\n";

	  for (int javd = 0; javd < geom->ngbr.n(at_bnd); javd++)
	    {
	      index<DIM> at_avd = geom -> ngbr(at_bnd,javd);

	      //std::cout << "try match to " << at_avd << " r= " 
	      //<< norm(geom->coord(at_avd)-geom->coord(at_bnd)) << "\n";

	      if ( occupied[at_avd] || point(iavd).atom != geom -> atom(at_avd) )
		continue;
	      
	      bind(iavd,at_avd);
	      
	      //std::cout << "___checking if avoided\n";

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

      
      //std::cout << "avoid result= " << res << "\n";
      return res;
      
    }

    // ------------------------------------------------------------------

    bool extract_bond(int r, VALTYPE &b, int &at)
    {
      b = rel(r).formula().value();
      if (rel(r).point_defined(0))
	at = point(rel(r).point(0)).bound;
      else
	at = point(rel(r).point(1)).bound;
      return true;
    }

    bool extract_angle(int r, VALTYPE &a, int &at1, int &at2)
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

    // ------------------------------------------------------------------

    bool insert_next( integer_lister &lst)
    {
      //std::cout << "Insert_next called\n";
      //for (int i=0; i<n_points(); i++)
      //std::cout << point(i).nickname << " " <<  point(i).bound << " " << point(i).is_bound << "\n";

      bool unfinished_insert = false, insert_found = false;
      int i;
      std::vector<int> ibnd, iang, idhd;
      for (i=0; i<n_points(zinsert); i++)
	if ( !point(i,zinsert).is_bound )
	  {
	    //std::cout << "check insert conditions for point " << point_idx(i,zinsert) << "\n";
	    unfinished_insert = true;
	    insert_condition(point_idx(i,zinsert),ibnd,iang,idhd);

	    //std::cout << "Insert conditions:\n";
	    //for (int j=0; j<ibnd.size(); j++)
	    //  rel(ibnd[j]).write(std::cout);
	    //for (int j=0; j<iang.size(); j++)
	    //  rel(iang[j]).write(std::cout);
	    //std::cout << "\n";
	      

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
	  //std::cout << "Insert found\n";

	  int insrt = point_idx(i,zinsert);
	  std::vector<lace::vector2d<VALTYPE> > new_pt;
	  if (ibnd.size()==2)
	  // Two bonds
	    {
	      VALTYPE b1,b2;
	      int at1,at2;
	      extract_bond(ibnd[0],b1,at1);
	      extract_bond(ibnd[1],b2,at2);
	      
	      //std::cout << "Two bonds: " << at1 << " " << b1 << " " << at2 << " " << b2 << "\n";

	      new_pt = mfold->triangul2b((*parm)[at1],b1,(*parm)[at2],b2);

	      //std::cout << "new points: " << new_pt.size() << "\n"; 
	    }
	  // Bond & angle
	  else if (ibnd.size()==1 && iang.size()==1)
	    {
	      VALTYPE b,a;
	      int at1,at2,at22;
	      extract_bond(ibnd[0],b,at2);
	      bool valid = extract_angle(iang[0],a,at1,at22);
	      if (valid)
		valid = (at2 == at22);
	      if (!valid)
		error("Given parameters do not allow to locate new point");

	      //std::cout << "Inserting " << at1  << " " << at2 << " bond= " 
	      //<< b << " angle= " << a << "\n";
	      if (rel(iang[0]).gettype() == qppdata_zpt_angle)
		{
		  //std::cout << "triangul generated points\n";
		  new_pt.push_back(mfold->triangul((*parm)[at1],(*parm)[at2],b,pi*a/180));
		  new_pt.push_back(mfold->triangul((*parm)[at1],(*parm)[at2],b,-pi*a/180));
		}
	      else if (rel(iang[0]).gettype() == qppdata_zpt_surfangle)
		{
		  //std::cout << "protract generated points\n";
		  new_pt.push_back(mfold->protract((*parm)[at1],(*parm)[at2],b, pi*a/180));
		  new_pt.push_back(mfold->protract((*parm)[at1],(*parm)[at2],b,-pi*a/180));
		}
	    }
	  else if (iang.size()==2)
	    // fixme - implement later
	    error("Inserting new point on the basis of two angles is not supported yet");
	  lst.set(0,new_pt.size()-1);
	  bool res = false;
	  for (int j=lst.begin(); !lst.end(); j=lst.next())
	    {
	      int inew = parm->size();
	      parm->push_back(new_pt[j]);
	      geom -> add(point(insrt).atom, mfold->map(new_pt[j]));
	      occupied.push_back(true);
	      noapply.push_back(false);

	      geom->build_type_table();
	      geom->ngbr.build_disttable();
	      geom->ngbr.build();	      
	      bind(insrt,inew);
	      
	      //std::cout << "point inserted i= " << insrt << " r= " << geom->coord(inew)<<"\n";
	      //for (int ii=0; ii<n_points(); ii++)
	      //std::cout << point(ii).nickname << " = "  << bound(ii) << " " 
	      //<< point(ii).is_bound <<  "\n";

	      if (point_satisfy(insrt))
		res = insert_next(*lst.copy());
	      //std::cout << "satisfy= " << res << "\n";
	      //res = true;
	      if (res)
		{
		  //std::cout  << "alive1\n";
		  delete &lst;
		  //std::cout << "alive2\n";
		  return true;
		}
	      else
		{
		  unbind(insrt);
		  geom -> erase(inew);
		  parm->pop_back();
		  occupied.pop_back();
		  noapply.pop_back();
		  geom->build_type_table();
		  geom->ngbr.build_disttable();
		  geom->ngbr.build();	      
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
      //std::cout << "entering match_next\n";

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
      //      std::cout << "isrch= " << isrch << "\n";

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
	  /*std::cout << " ibnd= " << ibnd << " at_bnd= " << at_bnd << "\n";
	  rel(k).write(std::cout);
	  std::cout << "\n";
	  */
	  lst.set(0,geom->ngbr.n(at_bnd)-1);

	  //std::cout << "haha1\n";

	  for (int jsrch = lst.begin(); !lst.end(); jsrch = lst.next())
	    {
	      //std::cout << "haha2\n";
	      index<DIM> at_srch = geom -> ngbr(at_bnd,jsrch);

	      //debug
	      //std::cout << "isrch= " << isrch << " jsrch= " << jsrch << " at_srch= " << at_srch 
	      //<< " r= " << norm(geom->full_coord(at_bnd)-geom->full_coord(at_srch)) << "\n";

	      if ( !occupied[at_srch] && point(isrch).atom == geom -> atom(at_srch) )
		bind(isrch,at_srch);
	      else continue;

	      //std::cout << "after continue\n";
	      
	      bool satisfy = point_satisfy(isrch);

	      //std::cout << "after point_satisfy: " << satisfy <<"\n";
	      /*
	      for (int jrel = 0; jrel < n_rel_of_point(isrch); jrel++)
		{
		  int kk = rel_of_point(isrch,jrel);
		  if ( rel(kk).is_defined() && ! rel(kk).satisfy() )
		    {
		      satisfy = false;
		      break;
		    }
		    }*/
	      if (satisfy)
		satisfy = match_next(*lst.copy());

	      //std::cout << "after match_next: " << satisfy <<"\n";

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
	  bool res = insert_next(*lst.copy());
	  //std::cout << "alive3\n";
	  delete &lst;
	  //std::cout << "alive4\n";
	  return res;
	}
    }

    // ------------------------------------------------------------------

    void setngbrdist()
    {
      geom->ngbr.default_distance = 0;
      geom->ngbr.clear_distance();

      for (int i = 0; i<n_rel(); i++)
	if (rel(i).is_bond() && !rel(i).is_exact())
	  {
	    ATLABEL at1, at2;
	    at1 = point(rel(i).point(0)).atom;
	    at2 = point(rel(i).point(1)).atom;
	    if ( geom->ngbr.distance(at1,at2) < rel(i).vmax)
	      geom->ngbr.set_distance(at1,at2,rel(i).vmax);
	  }
    }

    // ------------------------------------------------------------------

    bool apply( parametric_surface<VALTYPE,charT,traits> &m, 
		std::vector<lace::vector2d<VALTYPE> > &p, 
		geometry<DIM, VALTYPE, ATLABEL, charT, traits> &g, integer_lister &lst)
    {
      //prepare
      geom = &g;
      mfold = &m;
      parm = &p;
      unbind_all();

      setngbrdist();
      geom -> ngbr.build_disttable();
      geom -> ngbr.build();

      for (int i=0; i<geom->nat(); i++)
	std::cout << (occupied[i] ? "1" : "0");
      std::cout << "\n";
      for (int i=0; i<geom->nat(); i++)
	std::cout << (noapply[i] ? "1" : "0");
      std::cout << "\n\n";
      
      // Match first point
      bool res = false;
      lst.set(0,geom->nat()-1 );
      for (int i=lst.begin(); !lst.end(); i=lst.next())
	{
	  //std::cout << " matching 0 to " << i << "\n";
	  bind(0,i);
	  if ( match_next(*lst.copy()) )
	    {
	      res = true;
	      break;
	    }
	  unbind(0);
	}
      if (res)
	{
	  // delete marked atoms
	  for (int i=g.nat()-1; i>=0; i--)
	    if (g.shadow(i))
	      {
		g.erase(i);
		p.erase(p.begin()+i);
	      }
	}
      return res;
    }

  };

};

#endif
