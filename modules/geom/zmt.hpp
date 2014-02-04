#ifndef _QPP_ZMT
#define _QPP_ZMT

#include <string>
#include <vector>
#include <algorithm>
#include <io/qppdata.hpp>
#include <geom/geom.hpp>
#include <geom/manyfold.hpp>
#include <constants.hpp>
#include <lace/lace3d.hpp>

namespace qpp{

  // ------------------------- find the dyhedral angle of four points ----------------
  template<class VALTYPE> 
  VALTYPE get_dyhedral(lace::vector3d<VALTYPE> r0, lace::vector3d<VALTYPE> r1,
		   lace::vector3d<VALTYPE> r2,lace::vector3d<VALTYPE> r3)
  {
    lace::vector3d<VALTYPE> n1 = (r0-r1)%(r2-r1),
      n2 = -(r3-r2)%(r1-r2);
    n1 /= norm(n1); 
    n2 /= norm(n2);
    
    VALTYPE theta = std::acos(scal(n1,n2));
    if ( scal(n1,(n2%(r2-r1))) < VALTYPE(0) )
      theta = -theta;
    return 180*theta/qpp::pi;
  }

  // -----------------------------------------------------------

  template<class VALTYPE> 
  VALTYPE get_angle(lace::vector3d<VALTYPE> r0, lace::vector3d<VALTYPE> r1, lace::vector3d<VALTYPE> r2)
  {
    lace::vector3d<VALTYPE> r10 = r0 - r1, r12 = r2 - r1;
    return std::acos( scal(r10,r12)/(norm(r10)*norm(r12)) );
  }

  // -------------------------------------------------------------------------
  // place the point at given bond length, angle and dihedral angle from three points
  template<class VALTYPE>
  lace::vector3d<VALTYPE> zpoint( lace::vector3d<VALTYPE> r1, lace::vector3d<VALTYPE> r2,
				  lace::vector3d<VALTYPE> r3, VALTYPE bond, VALTYPE angle, VALTYPE dyhedral)
  {

    lace::vector3d<VALTYPE> n1, n2, n3;
    
    n1 = r1 - r2;
    n1 /= norm(n1);
    
    n2 = r3 - r2;
    n2 = n2 - n1*scal(n1,n2);
    n2 /= norm(n2);
    
    n3 = n1%n2*std::sin(dyhedral) + n2*std::cos(dyhedral);
    
    return r1 - n1*bond*std::cos(angle) + n3*bond*std::sin(angle);
  }

  // --------------------------------------------------------------------------------
  // place the point at given bond length and angle from three points on parametric surface
  // the role of dyhedral is only to determine on which side of r1-r2 bond the new point must be
  template<class VALTYPE, class charT=std::string::value_type , class traits = std::char_traits<charT> >
  lace::vector2d<VALTYPE> zpoint( parametric_surface<VALTYPE,charT,traits> &mfold, lace::vector2d<VALTYPE> p1, 
				  lace::vector2d<VALTYPE> p2,lace::vector2d<VALTYPE> p3, 
				  VALTYPE bond, VALTYPE angle, VALTYPE dyhedral)
  {

    // fixme - inefficient? to much overhead?
    lace::vector3d<VALTYPE> r1,r2,r3;
    r1 = mfold.d2d3(p1);
    r2 = mfold.d2d3(p2);
    r3 = mfold.d2d3(p3);
    
    lace::vector2d<VALTYPE> p0 = mfold.protractor(p2,p1,bond,angle);
    lace::vector3d<VALTYPE> r0 = mfold.d2d3(p0);

    if ( scal((r3-r2)%(r1-r2), (r2-r1)%(r0-r1))*std::cos(dyhedral) < 0 )
      p0 = mfold.protractor(p2,p1,bond, -angle);

    return p0;
    
  }

  // ------------------- Simple Z-matrix -----------------------
  template <class VALTYPE=double, class ATLABEL = std::string, class charT = char, class traits = std::char_traits<charT> >
  struct zmt_record{
    
    ATLABEL atom;
    int at1, at2, at3;
    VALTYPE bond, angle, dyhedral;

    zmt_record(ATLABEL at, int _at1 = -1, VALTYPE _bond = 0, 
	       int _at2 = -1, VALTYPE _angle = 0, int _at3 = -1, VALTYPE _dyhedral = 0)
    {
      atom = at;
      at1 = _at1;
      bond = _bond;
      at2 = _at2;
      angle = _angle;
      at3 = _at3;
      dyhedral = _dyhedral;   
    }

    void setbond(int i, VALTYPE _bond)
    {
      at1 = i;
      bond = _bond;
    }

    void setangle(int i, VALTYPE _angle)
    {
      at2 = i;
      angle = _angle;      
    }

    void setdyhedral(int i, VALTYPE _dyhedral)
    {
      at3 = i;
      dyhedral = _dyhedral;
    }

  };



  template <class VALTYPE=double, class ATLABEL = std::string, class charT = char, class traits = std::char_traits<charT> >   
  class zmatrix : public qpp_object<charT,traits>{
    
    using typename qpp_object<charT,traits>::string;
    std::vector<zmt_record<VALTYPE,ATLABEL,charT,traits> > data;

    string _name;

  public:

    zmatrix(string __name = "")
    {
      _name = __name;
    }

    int size()
    {
      return data.size();
    }

    zmt_record<VALTYPE,ATLABEL,charT,traits> & operator()(int i)
    {
      return data[i];
    }

    void add(zmt_record<VALTYPE,ATLABEL,charT,traits> z)
    {
      data.push_back(z);
    }

    void insert(int i, zmt_record<VALTYPE,ATLABEL,charT,traits> z)
    {
      data.insert(data.begin()+i, z);
    }

    void erase(int i)
    {
      data.erase(data.begin()+i);
    }

    bool valid()
    {
      // fixme - implement
    }

    template<int DIM>
    void zmt2cart(geometry<DIM,VALTYPE,ATLABEL,charT,traits> &geom)
    {
      // fixme - check if it complies with g98

      geom.clear();
      for (int i=0; i<size(); i++)
	{
	  if (i==0)
	    geom.add(data[0].atom, 0, 0, 0);
	  else if (i==1)
	    geom.add(data[1].atom, 0, 0, data[1].bond);
	  else if (i==2)
	    {
	      VALTYPE phi = data[2].angle*qpp::pi/180;
	      VALTYPE b = data[i].bond;
	      lace::vector3d<VALTYPE> r1 = geom.coord(data[2].at1),
		r2 = geom.coord(data[2].at2);
	      lace::vector3d<VALTYPE> n1, n2;
	      n1 = r1 - r2;
	      n1 /= norm(n1);
	      n2 = lace::vector3d<VALTYPE>(-n1.z(), 0, n1.x() );
	      geom.add(data[2].atom, r1 - n1*b*std::cos(phi) + n2*b*std::sin(phi));
	    }
	  else
	    {
	      lace::vector3d<VALTYPE> r1 = geom.coord(data[i].at1),
		r2 = geom.coord(data[i].at2), r3 = geom.coord(data[i].at3);
	      VALTYPE phi = data[i].angle*qpp::pi/180, theta = data[i].dyhedral*qpp::pi/180;
	      VALTYPE b = data[i].bond;
	      geom.add(data[i].atom, zpoint(r1,r2,r3,b,phi,theta));
	    }
	}
    }

    template<int DIM>
    void zmt2surf( parametric_surface<VALTYPE,charT,traits> &mfold, 
		   lace::vector2d<VALTYPE> p0, lace::vector2d<VALTYPE> n0, int upside,
		   geometry<DIM,VALTYPE,ATLABEL,charT,traits> &geom,
		   std::vector<lace::vector2d<VALTYPE> > &parm //fixme - that's temporary kostyl
		   // put it inside the extended geometry class
		   )
    {
      // First atom
      int first = geom.size();
      parm.push_back(p0);
      geom.add( (*this)(0).atom, mfold.d2d3(p0) );
      
      // Second atom
      lace::vector2d<VALTYPE> p1 = mfold.ruler(p0,n0, (*this)(1).bond );
      parm.push_back(p1);
      geom.add( (*this)(1).atom, mfold.d2d3(p1) );

      // Third atom
      VALTYPE alpha = (*this)(2).angle*qpp::pi/180;
      if (upside<0)
	alpha *= -1;
      parm.push_back( mfold.protractor(p1,p0,(*this)(2).bond, alpha) );
      geom.add( (*this)(2).atom, mfold.d2d3( parm[first+2]) );

      // Other atoms
      for (int i=3; i<size(); i++)
	{
	  lace::vector2d<VALTYPE> p = zpoint( mfold, parm[ first+(*this)(i).at1 ], parm[ first+(*this)(i).at2 ], 
					     parm[ first+(*this)(i).at3 ], (*this)(i).bond, 
					     (*this)(i).angle*qpp::pi/180, (*this)(i).dyhedral*qpp::pi/180);
	  parm.push_back(p);
	  geom.add( (*this)(i).atom, mfold.d2d3(p) );
	  
	}
    }


    // inherited from qpp_object    
    virtual string category()
    {
      return "zmatrix";
    }

    virtual string name()
    {
      return _name;
    }

    virtual int gettype()
    {
      return qppdata_zmatrix;
    }

    virtual void write(std::basic_ostream<charT,traits> &os, int offset=0)
    {
      for (int k=0; k<offset; k++) os << " ";
      os << "zmatrix";
      if (_name != "")
	os << " " << _name;
      os << "{\n";

      for(int i=0; i<size(); i++)
	{
	  for (int k=0; k<offset+2; k++) os << " ";
	  os << data[i].atom;
	  if (data[i].at1 >= 0)
	    os << " " << data[i].at1 << " " << data[i].bond;
	  if (data[i].at2 >= 0)
	    os << " " << data[i].at2 << " " << data[i].angle;
	  if (data[i].at3 >= 0)
	    os << " " << data[i].at3 << " " << data[i].dyhedral;
	  os << "\n";
	}

      for (int k=0; k<offset; k++) os << " ";
      os << "}\n";
            
    }
        
  };

  // ------------------------------- Z-pattern definition --------------------------------
  template <class VALTYPE=double, class ATLABEL = std::string, class charT = char, class traits = std::char_traits<charT> >
  struct zpt_record{
    
    ATLABEL atom;
    int at1, at2, at3;
    VALTYPE min_bond, max_bond, min_angle, max_angle, 
      min_dyhedral, max_dyhedral;
    VALTYPE nothingelse;

    zpt_record(ATLABEL at, VALTYPE nelse = 0)
    {
      atom = at;
      nothingelse = nelse;
      at1 = at2 = at3 = -1;
    }

    zpt_record<VALTYPE,ATLABEL,charT,traits> & bond(int i, VALTYPE minb, VALTYPE maxb)
    {
      at1 = i;
      min_bond = minb;
      max_bond = maxb;
      return *this;
    }

    zpt_record<VALTYPE,ATLABEL,charT,traits> & angle(int i, VALTYPE mina, VALTYPE maxa)
    {
      at2 = i;
      min_angle = mina;
      max_angle = maxa;
      return *this;
    }

    zpt_record<VALTYPE,ATLABEL,charT,traits> & dyhedral(int i, VALTYPE mind, VALTYPE maxd)
    {
      at3 = i;
      min_dyhedral = mind;
      max_dyhedral = maxd;
      return *this;
    }

    bool comply(ATLABEL at, lace::vector3d<VALTYPE> r0=VALTYPE(0), 
		lace::vector3d<VALTYPE> r1=VALTYPE(0), 
		lace::vector3d<VALTYPE> r2=VALTYPE(0), 
		lace::vector3d<VALTYPE> r3=VALTYPE(0))
    {
      bool res = (at==atom);
      lace::vector3d<VALTYPE> n1,n2,n3;
      if (res && at1!=-1)
	// Check bond length
	{
	  VALTYPE bondl = norm(r0-r1);
	  n1 = (r0-r1)/bondl;
	  res = (bondl>=min_bond && bondl<=max_bond);
	}
      if (res && at2!=-1)
	//Check bond angle
	{
	  n2 = (r2-r1)/norm(r2-r1);
	  VALTYPE cosa = scal(n1,n2);
	  res = ( cosa <= std::cos(pi*min_angle/180) && cosa >= std::cos(pi*max_angle/180));
	}
      if (res && at3!=-1)
	// Check dyhedral angle
	{
	  VALTYPE theta = get_dyhedral(r0,r1,r2,r3);
	  res = ( theta >= min_dyhedral && theta <= max_dyhedral);
	}
      return res;
    }

  };

  class integer_lister{
  protected:

    int n1, n2;
  public:

    virtual void set(int _n1, int _n2)
    {
      n1 = _n1;
      n2 = _n2;
    }

    virtual int begin() =0;

    virtual int next() =0;

    virtual bool end() =0;

    virtual integer_lister* copy() =0;

    virtual void free(){delete this;}

  };

  class trivial_integer_lister : public integer_lister{

    int i;
  public:

    virtual int begin()
    {
      return i=n1;
    }

    virtual int next()
    {
      return ++i;
    }

    virtual bool end()
    {
      return i<=n2;
    }

    virtual integer_lister* copy()
    {
      return new trivial_integer_lister;
    }

    virtual void free(){delete this;}

  };

  class random_integer_lister : public integer_lister{

    std::vector<int> lst;
    int i;
  public:

    virtual void set(int _n1, int _n2)
    {
      n1 = _n1;
      n2 = _n2;

      lst.clear();
      for (int j = n1; j<=n2; j++)
	lst.push_back(j);

      for (int j=0; j<lst.size(); j++)
	{
	  int k = rand() % lst.size();
	  int x = lst[k];
	  lst[k] = lst[j];
	  lst[j] = x;
	}
    }

    virtual int begin()
    {
      i=0;
      return lst[0]; 
    }

    virtual int next()
    {
      return lst[++i];
    }

    virtual bool end()
    {
      return i<lst.size();
    }

    virtual integer_lister* copy()
    {
      return new random_integer_lister;
    }

    virtual void free(){delete this;}

  };

  class random_integer_selector : public integer_lister{

    bool done;

  public:

    virtual void set(int _n1, int _n2)
    {
      n1 = _n1;
      n2 = _n2;
      done = false;
    }

    virtual int begin()
    {
      done = false;
      return n1 + rand() % (n2-n1+1);
    }

    virtual int next()
    {
      done = true;
    }

    virtual bool end()
    {
      return !done;
    }

    virtual integer_lister* copy()
    {
      return new random_integer_selector;
    }

    virtual void free(){delete this;}
    
  };

  template <int DIM, class VALTYPE=double, class ATLABEL = std::string, 
	    class charT = char, class traits = std::char_traits<charT> >   
  class zpattern : public qpp_object<charT,traits>{
    
    using typename qpp_object<charT,traits>::string;
    std::vector<zpt_record<VALTYPE,ATLABEL,charT,traits> > data;
    
    string _name;

    std::vector<index<DIM> > _match;
    geometry<DIM, VALTYPE, ATLABEL, charT, traits> *geom;    

  public:
    
    zpattern(string __name = "")
    {
      _name = _name;
    }
    
    int size()
    {
      return data.size();
    }
    
    zpt_record<VALTYPE,ATLABEL,charT,traits> & operator()(int i)
    {
      return data[i];
    }

    void add(zpt_record<VALTYPE,ATLABEL,charT,traits> z)
    {
      data.push_back(z);
    }

    void insert(int i, zpt_record<VALTYPE,ATLABEL,charT,traits> z)
    {
      data.insert(data.begin()+i, z);
    }

    void erase(int i)
    {
      data.erase(data.begin()+i);
    }

    bool valid()
    {
      // fixme - implement
    }
    // inherited from qpp_object    
    virtual string category()
    {
      return "zpattern";
    }

    virtual string name()
    {
      return _name;
    }

    virtual int gettype()
    {
      return qppdata_zpattern;
    }

    virtual void write(std::basic_ostream<charT,traits> &os, int offset=0)
    {      
      for (int k=0; k<offset; k++) os << " ";
      os << "zpattern";
      if (_name != "")
	os << " " << _name;
      os << "{\n";

      for(int i=0; i<size(); i++)
	{
	  for (int k=0; k<offset+2; k++) os << " ";
	  os << data[i].atom;
	  if (data[i].at1 >= 0)
	    os << " " << data[i].at1 << " " << data[i].min_bond << " " << data[i].max_bond;
	  if (data[i].at2 >= 0)
	    os << " " << data[i].at2 << " " << data[i].min_angle << " " << data[i].max_angle;
	  if (data[i].at3 >= 0)
	    os << " " << data[i].at3 << " " << data[i].min_dyhedral << " " << data[i].max_dyhedral;
	  os << "\n";
	}
      
      for (int k=0; k<offset; k++) os << " ";
      os << "}\n";
    }

    // ----------- Matching mechanism ---------------

    inline index<DIM> bound(int i)
    {
      return _match[i];
    }

    bool check_nelse(int i)
    {
      // Check "nothingelse"
      bool res = true;
      index<DIM> at = bound(i);;
      for (int j=0; j < geom->n_ngbr(at); j++)
	{
	  index<DIM> at_neig = geom -> ngbr(at,j);
	  VALTYPE r12 = norm( geom->full_coord(at) - geom->full_coord(at_neig) );
			  
	  //debug
	  //std::cout << "neig= " << geom->atom(at_neig) << at_neig 
	  //		    << " r= " << r12 << " nelse= " <<(*this)(i).nothingelse <<  "\n"; 

	  if ( r12 < (*this)(i).nothingelse)
	    {
	      bool found = false;
	      for ( int k=0; k<size(); k++)
		if (at_neig == bound(k) )
		  {
		    found = true;
		    break;
		  }
	      if (!found)
		{
		  res = false;
		  break;
		}
	    }
	  
	}
      return res;
    }
    
    bool match_atom( int i, integer_lister *lst)
    {
      //debug
      //std::cout << "ma: " << i << "\n";

      bool matched = false;
      _match.push_back( index<DIM>(-1) );
      if (i==0)
	{
	  lst -> set(0,geom->size()-1 );
	  for (int j=lst->begin(); lst->end(); j=lst->next())
	    {
	      // debug
	      //std::cout << "level 0 j= " << j << "\n";
	      
	      if ( geom->atom(j) == (*this)(0).atom )
		{
		  _match[0] = index<DIM>(j);
		  if (match_atom(1,lst -> copy() ) )
		    {
		      //debug
		      //std::cout << "here inside\n";
		      matched = check_nelse(0);
		      
		      if (matched) break;
		    }
		}
	    }
	}
      else
	{ 
	  index<DIM> at_bond = bound((*this)(i).at1);

	  //debug
	  //	  std::cout << "at_bond "<< at_bond << " nneig =" << geom->n_ngbr(at_bond) << "\n";

	  lst -> set(0, geom->n_ngbr(at_bond)-1 );
	  for (int j=lst->begin(); lst->end(); j=lst->next())
	    { 
	      index<DIM> at_new, at_angle=-1, at_dyhedr=-1 ;
	      at_new = geom -> ngbr(at_bond,j);

	      //debug
	      //  std::cout << "j=" << j << " at_new "<< at_new << "\n";

	      _match[i] = at_new;

	      // debug
	      /*for (int j=0; j<_match.size(); j++ )
		std::cout << _match[j] << " ";
	      std::cout << "\n";
	      */
	      if (i>1)
		at_angle = bound((*this)(i).at2);
	      if (i>2)
		at_dyhedr = bound((*this)(i).at3);

	      //debug
	      //	      std::cout << " at_angle "<< at_angle << " at_dih " << at_dyhedr << "\n";

	      if (i==1)
		matched = (*this)(i).comply( geom->atom(at_new), geom -> full_coord(at_new), 
					     geom -> full_coord(at_bond) );
	      else if (i==2)
		matched = (*this)(i).comply( geom->atom(at_new), geom -> full_coord(at_new), 
					     geom -> full_coord(at_bond),
					     geom -> full_coord(at_angle));
	      else if (i>2)
		matched = (*this)(i).comply( geom->atom(at_new), geom -> full_coord(at_new), 
					     geom -> full_coord(at_bond),
					     geom -> full_coord(at_angle),
					     geom -> full_coord(at_dyhedr));
	      if ( matched && i+1 < size() )
		matched = match_atom(i+1,lst->copy());

	      // debug
	      //std::cout << "before nelse " << matched << "\n";
	      
	      if (matched)
		matched = check_nelse(i);

	      // debug
	      //std::cout << "after nelse " << matched << "\n";

	      if (matched)
		break;
	    }
	}
      if (!matched)
	_match.resize(i);
      
      if (i>0)
	lst ->free();
      //debuig
      //std::cout << "level " << i << " return value " << matched << "\n";
      return matched;
    }

    bool match( geometry<DIM, VALTYPE, ATLABEL, charT, traits> &g, integer_lister &lst)
    {
      geom = &g;
      if (_match.size()!=0)
	_match.clear();
      return match_atom(0,&lst);
    }

    // ------------- Average z-matrix ----------------

    zmatrix<VALTYPE, ATLABEL, charT, traits> & average()
    {
      zmatrix<VALTYPE, ATLABEL, charT, traits> *z = new zmatrix<VALTYPE, ATLABEL, charT, traits>(_name);
      z -> add( zmt_record<VALTYPE, ATLABEL, charT, traits>((*this)(0).atom ));
      if (size()>1)
	z -> add( zmt_record<VALTYPE, ATLABEL, charT, traits>((*this)(1).atom, (*this)(1).at1, 
	     ((*this)(1).min_bond + (*this)(1).max_bond)/2 ));
      if (size()>2)
	z -> add( zmt_record<VALTYPE, ATLABEL, charT, traits>((*this)(2).atom, 
			    (*this)(2).at1, ((*this)(2).min_bond + (*this)(2).max_bond)/2,  
			    (*this)(2).at2, ((*this)(2).min_angle + (*this)(2).max_angle)/2 ));
      for (int i=3; i<size(); i++)
	z -> add( zmt_record<VALTYPE, ATLABEL, charT, traits>((*this)(i).atom, 
			    (*this)(i).at1, ((*this)(i).min_bond + (*this)(i).max_bond)/2,  
		            (*this)(i).at2, ((*this)(i).min_angle + (*this)(i).max_angle)/2,
			    (*this)(i).at3, ((*this)(i).min_dyhedral + (*this)(i).max_dyhedral)/2 ));
      return *z;
    }

    // ------------------------ Replace part ---------------------------

  private:

    std::vector<int> delete_list;

    std::vector<zmt_record<VALTYPE,ATLABEL,charT,traits> > insert_list;

    std::vector<std::vector<VALTYPE> > bond_wt, angle_wt, dyhedral_wt;

  public:
    
    int n_delete()
    {
      return delete_list.size();
    }

    void to_delete(int at)
    {
      delete_list.push_back(at);
    }
    
    int n_insert()
    {
      return insert_list.size();
    }

    void to_insert(zmt_record<VALTYPE,ATLABEL,charT,traits> z)
    {
      insert_list.push_back(z);
      // update weigths
      
      bond_wt.push_back( std::vector<double>(size(), VALTYPE(0)) );
      angle_wt.push_back( std::vector<double>(size(), VALTYPE(0)) );
      dyhedral_wt.push_back( std::vector<double>(size(), VALTYPE(0)) );
    }

    VALTYPE & bond_weigth(int i, int j)
    {
      return bond_wt[i][j];
    }

    VALTYPE & angle_weigth(int i, int j)
    {
      return angle_wt[i][j];
    }    

    VALTYPE & dyhedral_weigth(int i, int j)
    {
      return dyhedral_wt[i][j];
    }

    void replace( geometry<DIM, VALTYPE, ATLABEL, charT, traits> &g){}

    void replace_surf( parametric_surface<VALTYPE,charT,traits> &mfold,
		       std::vector<lace::vector2d<VALTYPE> > & parm, 
		       //fixme - that's temporary kostyl
		       // put it inside the extended geometry class
		       geometry<DIM, VALTYPE, ATLABEL, charT, traits> &geom)
    {
      // Insert new atoms first

      //debug
      /*
      for (int i=0; i<size(); i++)
	std::cout << bound(i) << " ";
      std::cout << "\n";
      */
      std::vector<lace::vector3d<VALTYPE> > r(size());
      std::vector<lace::vector2d<VALTYPE> > p(size());
      for (int i=0; i<size(); i++)
	{
	  r[i] = geom.coord( bound(i) );
	  p[i] = parm[ bound(i) ];
	}

      std::vector<VALTYPE> zbonds(size(),VALTYPE(0)), zangles(size(),VALTYPE(0)),
	zdyhedrals(size(),VALTYPE(0));
      // fixme - overhead in calculating this parameters
      // they were actualy calculated earlier - during the matching procedure
      for (int i=1; i<size(); i++)
	{
	  zbonds[i] = norm( r[i] - r[ (*this)(i).at1 ] );
	  if (i>1)
	    zangles[i] = get_angle( r[i], r[ (*this)(i).at1 ], r[ (*this)(i).at2 ] );
	  if (i>2)
	    zdyhedrals[i] = get_dyhedral( r[i], r[ (*this)(i).at1 ], r[ (*this)(i).at2 ], r[ (*this)(i).at3 ] );
	}
      
      for (int i=0; i<insert_list.size(); i++)
	{
	  //debug
	  //std::cout << " insert " << i << "\n";
	  VALTYPE bond = insert_list[i].bond,
	    angle = insert_list[i].angle,
	    dyhedral = insert_list[i].dyhedral;
	  for (int j=0; j<size(); j++)
	    {
	      // Interpolation for bond, angle & dyhedral
	    }

	  //debug
	  //  std::cout << "bond= " << bond << " angle= " << angle << " dyhedral= " << dyhedral << "\n";

	  lace::vector2d<VALTYPE> p0 = zpoint(mfold, p[insert_list[i].at1], p[insert_list[i].at2], 
					      p[insert_list[i].at3], 
					      bond, qpp::pi*angle/180, qpp::pi*dyhedral/180);

	  //debug
	  //std::cout << " new point " << p0.x << " " << p0.y << "\n";
	  parm.push_back(p0);
	  geom.add(insert_list[i].atom, mfold.d2d3(p0) );	  
	}

      //debug
      //std::cout << " before delete\n ";

      // Delete what shoud be deleted
      if (delete_list.size()>0)
	{
	  std::vector<int> dlst;
	  for (int i=0; i<delete_list.size(); i++)
	    dlst.push_back(bound(delete_list[i]));
	  std::sort(dlst.begin(), dlst.end());
	  for (int i=dlst.size()-1; i<=0; i--)
	    {
	      geom.erase(dlst[i]);
	      parm.erase(parm.begin()+dlst[i]);
	    }
	}

      //debug
      //std::cout << " afetr delete\n ";

    }
    
  };
  
};

#endif
