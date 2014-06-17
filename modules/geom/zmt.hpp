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
  template<class VALTYPE>
  lace::vector2d<VALTYPE> zpoint( parametric_surface<VALTYPE> &mfold, lace::vector2d<VALTYPE> p1, 
				  lace::vector2d<VALTYPE> p2,lace::vector2d<VALTYPE> p3, 
				  VALTYPE bond, VALTYPE angle, VALTYPE dyhedral)
  {

    // fixme - inefficient? to much overhead?
    lace::vector3d<VALTYPE> r1,r2,r3;
    r1 = mfold.map(p1);
    r2 = mfold.map(p2);
    r3 = mfold.map(p3);
    
    // lace::vector2d<VALTYPE> p0 = mfold.protract(p2,p1,bond,angle);
    lace::vector2d<VALTYPE> p0 = mfold.triangul(p2,p1,bond,angle);
    lace::vector3d<VALTYPE> r0 = mfold.map(p0);

    if ( scal((r3-r2)%(r1-r2), (r2-r1)%(r0-r1))*std::cos(dyhedral) < 0 )
      //      p0 = mfold.protract(p2,p1,bond, -angle);
      p0 = mfold.triangul(p2,p1,bond, -angle);

    return p0;
    
  }

  // ------------------- Simple Z-matrix -----------------------
  template <class VALTYPE=double>
  struct zmt_record{
    
    STRING atom;
    int at1, at2, at3;
    VALTYPE bond, angle, dyhedral;

    zmt_record(STRING at, int _at1 = -1, VALTYPE _bond = 0, 
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

  //------------------------------------------------------------------------------------


  template <class VALTYPE=double>   
  class zmatrix : public qpp_object{
    
    std::vector<zmt_record<VALTYPE> > data;

    STRING _name, _error;

  public:

    zmatrix(STRING __name = "")
    {
      _name = __name;
    }

    int size()
    {
      return data.size();
    }

    zmt_record<VALTYPE> & operator()(int i)
    {
      return data[i];
    }

    void add(const zmt_record<VALTYPE> & z)
    {
      data.push_back(z);
    }

    void insert(int i, zmt_record<VALTYPE> z)
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
    void zmt2cart(geometry<DIM,VALTYPE> &geom)
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
    void zmt2surf( parametric_surface<VALTYPE> &mfold, 
		   lace::vector2d<VALTYPE> p0, lace::vector2d<VALTYPE> n0, int upside,
		   geometry<DIM,VALTYPE> &geom,
		   std::vector<lace::vector2d<VALTYPE> > &parm //fixme - that's temporary kostyl
		   // put it inside the extended geometry class
		   )
    {
      // First atom
      int first = geom.size();
      parm.push_back(p0);
      geom.add( (*this)(0).atom, mfold.map(p0) );
      
      // Second atom
      lace::vector2d<VALTYPE> p1 = mfold.ruler(p0,n0, (*this)(1).bond );
      parm.push_back(p1);
      geom.add( (*this)(1).atom, mfold.map(p1) );

      // Third atom
      VALTYPE alpha = (*this)(2).angle*qpp::pi/180;
      if (upside<0)
	alpha *= -1;
      parm.push_back( mfold.protract(p1,p0,(*this)(2).bond, alpha) );
      geom.add( (*this)(2).atom, mfold.map( parm[first+2]) );

      // Other atoms
      for (int i=3; i<size(); i++)
	{
	  lace::vector2d<VALTYPE> p = zpoint( mfold, parm[ first+(*this)(i).at1 ], parm[ first+(*this)(i).at2 ], 
					     parm[ first+(*this)(i).at3 ], (*this)(i).bond, 
					     (*this)(i).angle*qpp::pi/180, (*this)(i).dyhedral*qpp::pi/180);
	  parm.push_back(p);
	  geom.add( (*this)(i).atom, mfold.map(p) );
	  
	}
    }


    // inherited from qpp_object    
    virtual STRING category() const
    {
      return "zmatrix";
    }

    virtual STRING name() const
    {
      return _name;
    }

    virtual qppobject_type gettype() const
    {
      return data_zmatrix;
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

    virtual int n_next() const
    { return 0;}

    virtual qpp_object* next(int i)
    { return NULL;}

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
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

};

#endif
