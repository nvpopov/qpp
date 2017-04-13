#ifndef _QPP_GEOM_EXTRAS_H
#define _QPP_GEOM_EXTRAS_H

#include <data/types.hpp>
#include <geom/geom.hpp>
#include <initializer_list>
#include <stdexcept>

namespace qpp{

  // ---------------- Geometry with extra fields - for storing any additional data -------------------

  template<class REAL, class CELL>
  class xgeometry : public geometry<REAL,CELL>{
  
    std::vector<std::vector<REAL> >   _xreal;
    std::vector<std::vector<int> >    _xint;
    std::vector<std::vector<short> >  _xbool;
    std::vector<std::vector<STRING> > _xstring;

    std::vector<STRING>       _field_name;
    std::vector<basic_types>  _field_type;
    std::vector<int>          _field_idx;
    std::vector<bool>         _field_additive;

    int _nxreal, _nxint, _nxbool, _nxstring;
    bool xchrg;
    int ichrg;

    using geometry<REAL,CELL>::_atm;
    using geometry<REAL,CELL>::_crd;
    using geometry<REAL,CELL>::size;
    //using geometry<DIM,REAL,CELL>::error;

  public:

    using geometry<REAL,CELL>::DIM;
    using geometry<REAL,CELL>::name;
    using geometry<REAL,CELL>::cell;

    xgeometry(CELL & __cell,
	      int __nxstring=0, int __nxreal=0, int __nxint=0, int __nxbool=0, 
	      const STRING & __name = "") :
      _xstring(__nxstring), _xreal(__nxreal), _xint(__nxint), _xbool(__nxbool), 
      _field_name(__nxreal + __nxint + __nxbool + __nxstring),
      _field_type(__nxreal + __nxint + __nxbool + __nxstring),
      _field_idx(__nxreal + __nxint + __nxbool + __nxstring),
      _field_additive(__nxreal + __nxint + __nxbool + __nxstring),
      geometry<REAL,CELL>(__cell, __name)
    {
      //xchrg = charge;
      _nxreal   = __nxreal;
      _nxint    = __nxint; 
      _nxbool   = __nxbool;      
      _nxstring = __nxstring;
    }

    xgeometry(CELL & __cell,  const STRING & __name = "") : geometry<REAL,CELL>(__cell, __name)
    {
      _nxreal = _nxstring = _nxint = _nxbool = 0;
    }

    xgeometry(int dim,  const STRING & __name = "") : geometry<REAL,CELL>(dim, __name)
    {
      _nxreal = _nxstring = _nxint = _nxbool = 0;
    }

    void set_fields(const std::vector<STRING> & fn, const std::vector<basic_types> & ft)
    {
      
    }

    int nxreal() const
    { return _nxreal; }

    int nxint() const
    { return _nxint;}

    int nxbool() const
    { return _nxbool;}

    STRING & field_name(int i)
    { return _field_name[i]; }

    STRING field_name(int i) const
    { return _field_name[i]; }

    STRING & xreal_name(int i)
    { return _field_name[i]; }

    STRING xreal_name(int i) const
    { return _field_name[i]; }

    STRING & xint_name(int i)
    { return _field_name[_nxreal+i]; }

    STRING xint_name(int i) const
    { return _field_name[_nxreal+i]; }

    STRING & xbool_name(int i)
    { return _field_name[_nxreal+_nxint+i]; }

    STRING xbool_name(int i) const
    { return _field_name[_nxreal+_nxint+i]; }

    REAL xreal(int i, int j) const
    { return _xreal[i][j]; }

    REAL & xreal(int i, int j)
    { return _xreal[i][j]; }

    int xint(int i, int j) const
    { return _xint[i][j]; }

    int & xint(int i, int j)
    { return _xint[i][j]; }

    bool xbool(int i, int j) const
    { return * ((bool*) & _xbool[i][j]); }

    bool & xbool(int i, int j)
    { return * ((bool*) & _xbool[i][j]); }

    template<class T>
    T xfield(int i, int j) const
    {
      if (attributes<T>::name == "bool")
	return * ((bool*) & _xbool[i][j]);
      else if (attributes<T>::name == "int")
	return _xint[i][j];
      else if (attributes<T>::name == attributes<REAL>::name)
	return _xreal[i][j];
      else 
	throw std::invalid_argument("Illegal type of xgeometry extra field");
    }

    template<class T>
    T & xfield(int i, int j)
    {
      if (attributes<T>::name == "bool")
	return * ((T*) & _xbool[i][j]);
      else if (attributes<T>::name == "int")
	return * ((T*)& _xint[i][j]);
      else if (attributes<T>::name == attributes<REAL>::name)
	return * ((T*) & _xreal[i][j]);
      else 
	throw std::invalid_argument("Illegal type of xgeometry extra field");
    }

   
    template<class T>
    T & xfield(const STRING & f)
    {}

    bool has_charges()
    {
      xchrg = false;
      ichrg = 0;
      for (ichrg = 0; ichrg<nxreal; ichrg++)
	if (_field_name[ichrg]=="charge")
	  {
	    xchrg = true;
	    break;
	  }
      return xchrg;
    }

    REAL charge(int i) const
    {
      if (xchrg)
	return _xreal[ichrg][i]; 
      else
	throw std::runtime_error("\"charge\" field is requested for the geometry which does not have charges");
    }

    REAL & charge(int i)
    {
      if (xchrg)
	return _xreal[ichrg][i]; 
      else
	throw std::runtime_error("\"charge\" field is requested for the geometry which does not have charges");
    }
    /*
    REAL charge(int i) const
    { return chrg[i]; }

    REAL & charge(int i)
    { return chrg[i]; }
    */
    virtual void erase(const int j)
    {
      //debug
      /*
      std::cerr << "erase of xtr_geometry:enter\n";
      std::cerr << j << " " << size(); 
      for (int i=0; i<nxreal; i++) std::cerr << " " << _xreal[i].size();
      for (int i=0; i<nxint; i++) std::cerr << " " << _xint[i].size();
      for (int i=0; i<nxbool; i++) std::cerr << " " << _xbool[i].size();
      std::cerr << "\n";
      */

      geometry<REAL>::erase(j);
      for (int i=0; i<_nxreal; i++)
	_xreal[i].erase(_xreal[i].begin()+j);
      for (int i=0; i<_nxint; i++)
	_xint[i].erase(_xint[i].begin()+j);
      for (int i=0; i<_nxbool; i++)
	_xbool[i].erase(_xbool[i].begin()+j);
      //     if (xchrg)
      //	chrg.erase(chrg.begin()+j);  
      //std::cerr << "erase of xtr_geometry:exit\n";
    }

    void add(const STRING & a, const vector3d<REAL> & r,
	     std::initializer_list<REAL> xtr, 
	     std::initializer_list<int> xti = {}, 
	     std::initializer_list<bool> xtb = {})
    {
      //std::cerr << "xtr_geometry::add entry\n";

      //      if (xchrg)
      //	chrg.push_back( q );

      typename std::initializer_list<REAL>::iterator ir = xtr.begin();
      for (int i=0; i<_nxreal; i++)
	{
	  _xreal[i].push_back( ir == xtr.end() ? REAL(0) : *ir );
	  if (ir != xtr.end() ) 
	    ir++;
	}

      typename std::initializer_list<int>::iterator ii = xti.begin();
      for (int i=0; i<_nxint; i++)
	{
	  _xint[i].push_back( ii == xti.end() ? 0 : *ii );
	  if (ii != xti.end() ) 
	    ii++;
	}

      typename std::initializer_list<bool>::iterator ib = xtb.begin();
      for (int i=0; i<_nxbool; i++)
	{
	  _xbool[i].push_back( ib == xtb.end() ? false : *ib );
	  if (ib != xtb.end() ) 
	    ib++;
	}
      geometry<REAL>::add(a,r);
    }

    void insert(const int j, const STRING & a, const vector3d<REAL> &r,
		std::initializer_list<REAL> xtr, 
		std::initializer_list<int> xti = {}, 
		std::initializer_list<bool> xtb = {})
    {
      //if (xchrg)
      //	chrg.insert( chrg.begin()+j, q );

      typename std::initializer_list<REAL>::iterator ir = xtr.begin();
      for (int i=0; i<_nxreal; i++)
	{
	  _xreal[i].insert( _xreal[i].begin()+j, ir == xtr.end() ? REAL(0) : *ir );
	  ir++;
	}

      typename std::initializer_list<int>::iterator ii = xti.begin();
      for (int i=0; i<_nxint; i++)
	{
	  _xint[i].insert( _xint[i].begin()+j, ii == xti.end() ? 0 : *ii );
	  ii++;
	}

      typename std::initializer_list<bool>::iterator ib = xtb.begin();
      for (int i=0; i<_nxbool; i++)
	{
	  _xbool[i].insert( _xbool[i].begin()+j, ib == xtb.end() ? false : *ib );
	  ib++;
	}
      geometry<REAL>::insert(j,a,r);
    }

    virtual void add(const STRING &a, const vector3d<REAL> & r)
    {

      //std::cerr << "xtr_geometry::add entry\n";
      //if (xchrg)
      //	chrg.push_back( REAL(0) );   
      for (int i=0; i<_nxreal; i++)
	_xreal[i].push_back( REAL(0) );
      for (int i=0; i<_nxint; i++)
	_xint[i].push_back(0);
      for (int i=0; i<_nxbool; i++)
	_xbool[i].push_back( false );
      geometry<REAL>::add(a,r);
    }

    virtual void insert(const int j, STRING a, const vector3d<REAL> &r)
    {

      //if (xchrg)
      //	chrg.insert(chrg.begin()+j, REAL(0) );  
      for (int i=0; i<_nxreal; i++)
	_xreal[i].insert(_xreal[i].begin()+j, REAL(0) );
      for (int i=0; i<_nxint; i++)
	_xint[i].insert(_xint[i].begin()+j, 0);
      for (int i=0; i<_nxbool; i++)
	_xbool[i].insert(_xbool[i].begin()+j, false);
      geometry<REAL>::insert(j,a,r);
    }

    virtual void add(STRING a, REAL _x, REAL _y, REAL _z)
    {
      add(a, {_x,_y,_z});
    }

    virtual void insert(const int j, STRING a, const REAL _x, const REAL _y, const REAL _z)
    {
      insert(j,a, {_x,_y,_z});
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      for (int k=0; k<offset; k++) os << " ";
      os << "geometry";
      if (name != "")
	os << " " << name;
      os << "(" << DIM << "d,atom,x,y,z";
      for (int i=0; i<_nxreal; i++)
	{
	  os << ",";
	  if ( xreal_name(i) != "")
	    os << xreal_name(i) << "=";
	  os << "real";
	}
      for (int i=0; i<_nxint; i++)
	{
	  os << ",";
	  if ( xint_name(i) != "")
	    os << xint_name(i) << "=";
	  os << "int";
	}
      for (int i=0; i<_nxbool; i++)
	{
	  os << ",";
	  if ( xbool_name(i) != "")
	    os << xbool_name(i) << "=";
	  os << "bool";
	}
      os << ")\n";
      for (int k=0; k<offset+2; k++) os << " ";
      os << "{\n";

      cell->write(os,offset+4);

      for (int i=0; i<size(); i++)
	{
	  for (int k=0; k<offset+4; k++) os << " ";
	  os << boost::format("%-5s %11.6f %11.6f %11.6f") % _atm[i] % _crd[i].x() % _crd[i].y() % _crd[i].z();

	  //if (xchrg)
	  //  os << boost::format(" %11.6f") % charge(i);
	  for (int j=0; j<_nxreal; j++)
	    os <<  boost::format(" %11.6f") % xreal(j,i);
	  for (int j=0; j<_nxint; j++)
	    os << boost::format(" %5i") % xint(j,i);
	  for (int j=0; j<_nxbool; j++)
	    os << boost::format(" %s") % (xbool(j,i) ? "true" : "false");
	  os << "\n";
	}

      for (int k=0; k<offset+2; k++) os << " ";
      os << "}\n";
    }

  };

};

#endif
