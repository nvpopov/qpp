#ifndef _QPP_GEOM_H
#define _QPP_GEOM_H

#include <vector>
#include <cmath>
#include <symm/index.hpp>
//#include <symm/symm.hpp>
#include <symm/cell.hpp>

#ifdef PY_EXPORT
#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>
#include <python/qppython.hpp>

namespace bp = boost::python;
namespace sn = boost::python::self_ns;

#endif

namespace qpp{

  template< class REAL = double, class CELL = periodic_cell<REAL> >
  class geometry;

  //--------------------------------------------------------------//

  /*! \class geometry 
      \brief Test brief
The supercell concept generalization for the geometry class looks like:
    template< int DIM, class REAL>
    class CELL{
    public:
    index<DIM> begin();
    index<DIM> end();
    vector3d<REAL> transform(const vector3d<REAL> & r, const index<DIM> & I);
    bool within(const vector3d<REAL> & r);
    vector3d<REAL> reduce(const vector3d<REAL> & r);
    // find high symmetry point within "radius" distance from given point "r"
    // makes sence for rotational symmetries
    vector3d<REAL> symmetrize(const vector3d<REAL> & r, REAL radius);
    // fractional to cartesian and vice versa transformation
    // makes sence only for periodic translational cells
    vector3d<REAL> frac2cart(const vector3d<REAL> & r);
    vector3d<REAL> cart2frac(const vector3d<REAL> & r);
  };

	Any class having these methods - can be used as a "supercell" for some geometry

    template <int DIM> 
    struct atom_index {
    int atom;
    index<DIM> cell;

    atom_index(int _atom, const index<DIM> & _cell = index<DIM>::all(0))
    {
      atom = _atom;
      cell = _cell;
    }

    inline operator int() const {return atom;}

    inline bool operator==(const atom_index<DIM> & ai)
    {
      return atom == ai.atom && cell == ai.cell;
    }
    
    inline bool operator!=(const atom_index<DIM> & ai)
    {
      return atom != ai.atom || cell != ai.cell;
    }
    
    };
Geometry updated objects
One geometry can maintain arbitrary number of "observers", i.e.
objects which need to know about the changes made to geometry.
Geometry will inform them all when atoms are added, inserted or removed
  */

  enum before_after {before = 0, after = 1};
      
  template <class REAL>
  struct geometry_observer{

    virtual void added(before_after, const STRING &,  const vector3d<REAL> &) =0;
    virtual void inserted(int at, before_after, const STRING &, const vector3d<REAL> &) =0;
    virtual void changed( int at, before_after, const STRING &, const vector3d<REAL> &) =0;
    virtual void erased(  int at, before_after) =0;
    virtual void shaded(  int at, before_after, bool) =0;
  };

  //--------------------------------------------------------------//

  template< class REAL, class CELL>
  class geometry 
  {
  public:
    
    // Storage of atoms
    std::vector<STRING> _atm;

    // Storage of coordinates
    std::vector<vector3d<REAL> > _crd;

    //! Special logical array allows to "hide" or "shadow" some atoms
    std::vector<char> _shadow;

  protected: 
    // The dependent objects array
    std::vector<geometry_observer<REAL>*> observers;
    bool has_observers;

  public:
    
    typedef geometry_observer<REAL> DEP;
    typedef geometry<REAL,CELL> SELF;

    // fixme - is that neccessary for something?
    static REAL tol_geom_default;
    REAL tol_geom;

    int DIM;

    //! cell for periodic boundary conditions and on-the-fly transformations
    //CELL * cell;    
    CELL cell;

    //! whether to update typetable on-the-fly
    bool auto_update_types;

    //! whether fractional coordinates are used
    bool frac;

    STRING name;

    //! Number of atoms
    inline int size() const
    {return _crd.size();}

    //! Synonim
    inline int nat() const
    {return _crd.size();}

    //! The name of i-th atom
    inline STRING & atom(int at)
    {return _atm[at];}

    inline STRING atom(int at) const
    {return _atm[at];}

     /*! coord gives the coordinates of i-th atom in the cell
	@param at id of atom in cell	
	*/		
    inline vector3d<REAL> coord(int at) const{return _crd[at];}

    inline vector3d<REAL>& coord(int at){return _crd[at];}
    
    /*! real-space position of i-th atom, including i[0] as atom number and
     other i components as symmetry indicies*/
    inline vector3d<REAL> r(int at) const
    { 
      vector3d<REAL> r1 = _crd[at];
      if (frac)
	r1 = cell.frac2cart(r1);
      return cell.transform(r1, index::D(DIM).all(0)); 
    }

    inline vector3d<REAL> r(int at, const index & I) const
    { 
      vector3d<REAL> r1 = _crd[at];
      if (frac)
	r1 = cell.frac2cart(r1);
      return cell.transform(r1, I); 
    }

    //! The synonym
    inline vector3d<REAL> pos(int at) const
    { return r(at); }

    inline vector3d<REAL> pos(int at, const index & I ) const
    { return r(at,I); }

    //! Another synonym with atom_index    
    inline vector3d<REAL> r(const index & ai) const
    {
      return cell.transform(_crd[ai(0)], ai.sub(1) );
    }

    //! The synonym
    inline vector3d<REAL> pos(const index & ai) const
    {
      return cell.transform(_crd[ai(0)], ai.sub(1) );
    }
    
    inline bool shadow(int at) const
    {
      return _shadow[at];
    }

    // ------------------- Typetable for atoms ------------------------------

  private:
    std::vector<STRING> _atm_types;
    std::vector<int> _type_table;
    std::vector<REAL> _symm_rad;
    
  public:

    //! Number of atomic types in molecule
    inline int n_atom_types() const
    {
      return _atm_types.size();
    }

    inline int n_types() const
    { return n_atom_types();}

    //! Reference to atom of type number t (not the atom number t in atomic list!)
    inline STRING atom_of_type(int t) const
    {
      return _atm_types[t];
    }

    //! Number of type of certain ATOM at
    inline int type_of_atom(const STRING & at) const
    {
      int t;
      for (t=0; t < _atm_types.size(); t++)
	if ( _atm_types[t] == at )
	  break;
      if (t == _atm_types.size())
	return -1;
      else
	return t;
    }

    //! synonym
    inline int type(const STRING & at) const
    { return type_of_atom(at); }

    //! type of i-th atom in the geometry
    inline int type_table(int i) const
    {return _type_table[i];}

    //! synonym
    inline int type(int i) const
    { return type_table(i); }

    //! synonym
    inline int type_of_atom(int i) const
    { return type_table(i); }

    virtual void build_type_table()
    {
      _atm_types.clear();
      _symm_rad.clear();
      _type_table.resize(size());

      for (int i=0; i<size(); i++)
	{
	  int t = type_of_atom(atom(i));
	  if (t == -1)
	    {
	      t = _atm_types.size();
	      _atm_types.push_back(atom(i));
	      _symm_rad.push_back(default_symmetrize_radius);
	    }
	  _type_table[i] = t;
	}
      //      ngbr.resize_disttable();
    }

    void clear_type_table()
    {
      _atm_types.clear();
      _type_table.resize(size());
    }
    
    // --------------- Symmetrization radius for each atomic type ----

    // whether to be aware of high symmetry points when placing atoms
    // (if atom is placed close to high symmetry point, it would be also very close to its image)
    bool auto_symmetrize;
    REAL default_symmetrize_radius;

    REAL symmetrize_radius(int t) const
    {
      return _symm_rad[t];
    }

    void set_symmetrize_radius(int t, REAL rad)
    {
      _symm_rad[t] = rad;
    }

    REAL symmetrize_radius(const STRING & a) const
    {
      int t = type_of_atom(a);
      
      //std::cerr << "t= " << t << "\n";

      if (t==-1)
	return default_symmetrize_radius;
      else
	return _symm_rad[t];
    }

    void set_symmetrize_radius(const STRING & a, REAL rad)
    {
      int t = type_of_atom(a);

      if (t == -1)
	{
	  t = _atm_types.size();
	  _atm_types.push_back(a);
	  _symm_rad.push_back(rad);
	}
      else
	_symm_rad[t] = rad;
      
      //std::cerr << "t= " << t << "\n";

      //return _symm_rad[type_of_atom(a)];
    }

  // --------------- Constructors & destructors --------------------

  private:

    void init_default()
    {
      auto_update_types = true;
      frac = false;
      auto_symmetrize = false;
      has_observers = false;
      default_symmetrize_radius = 0e0;  
      tol_geom = tol_geom_default;

#ifdef PY_EXPORT
      py_atoms.bind(this);
      py_shadow.bind(this);
      py_x.bind(this);
      py_y.bind(this);
      py_z.bind(this);
      py_coords.bind(this);
      py_symmrad.bind(this);
#endif
    
    }
    
  public:

    geometry(const CELL & __cell, const STRING & __name = "") : cell(__cell)
    {
      init_default();
      DIM = cell.DIM;
      name = __name;
    }

    geometry(int dim, const STRING & __name = "") : cell(dim)
    {
      init_default();
      DIM = dim;
      name = __name;
    }

    geometry(const geometry<REAL, CELL> & g) : cell(g.cell)
    {
      init_default();
      //fixme
    }

    ~geometry()
    {
      //fixme
    }

    /*
    void copy(const geometry<DIM, REAL> &G)
    {
      // fixme - what is necessary to copy?
      clear();
      trnf = G.trnf;
      atm = G.atm;
      _crd = G._crd;
      _shadow = G._shadow;
      geomtol = G.geomtol;
      frac = G.frac;
    }
    */
    // ----------------------- Managing observers -----------------------

    void add_observer(DEP & d)
    {
      observers.push_back(&d);
      has_observers = true;
    }

    void remove_observer(DEP & d)
    {
      auto i = observers.begin();
      while(i != observers.end())
	{
	  if (*i == &d)
	    {
	      observers.erase(i);
	      break;
	    }
	  i++;
	}
      if (observers.size()==0)
	has_observers = false;
    }

    // ----------------------- Manipulations with atoms -----------------------

  protected:

    inline void _add(const STRING & a, const vector3d<REAL> & r1)
    {
      //std::cerr << "geometry::add entry\n";

      vector3d<REAL> r2 = r1;
      if (auto_symmetrize)
	{
	  REAL rad = symmetrize_radius(a);
	  r2 = cell.symmetrize(r1,rad);
	}

      if (has_observers)
	for (int i=0; i<observers.size(); i++)
	  observers[i]->added(before, a, r2);

      _atm.push_back(a);
      _crd.push_back(r2);
      _shadow.push_back((char)false);

      if (auto_update_types)
	{
	  int t = type_of_atom(a);
	  if (t == -1)
	    {
	      t = _atm_types.size();
	      _atm_types.push_back(a);
	      _symm_rad.push_back(default_symmetrize_radius);
	    }
	  _type_table.push_back(t);
	}

      if (has_observers)
	for (int i=0; i<observers.size(); i++)
	  observers[i]->added(after, a, r2);
    }

    inline void _erase(int at)
    {
      if (has_observers)
	for (int j=0; j<observers.size(); j++)
	  observers[j]->erased(at,before);

      _atm.erase(_atm.begin()+at);
      _crd.erase(_crd.begin()+at);
      _shadow.erase(_shadow.begin()+at);
      if (auto_update_types)
	_type_table.erase(_type_table.begin()+at);

      if (has_observers)
	for (int j=0; j<observers.size(); j++)
	  observers[j]->erased(at,after);
    }

    inline void _insert(int at, const STRING & a, const vector3d<REAL> & r1)
    {
      vector3d<REAL> r2 = r1;
      if (auto_symmetrize)
	r2 = cell.symmetrize(r1,symmetrize_radius(a));
      
      if (has_observers)
	for (int j=0; j<observers.size(); j++)
	  observers[j]->inserted(at,before, a, r2);

      _atm.insert(_atm.begin()+at,a);
      _crd.insert(_crd.begin()+at,r2);
      _shadow.insert(_shadow.begin()+at,(char)false);
      if (auto_update_types)
	{
	  int t = type_of_atom(a);
	  if (t == -1)
	    {
	      t = _atm_types.size();
	      _atm_types.push_back(a);
	      _symm_rad.push_back(default_symmetrize_radius);
	    }
	  _type_table.insert(_type_table.begin()+at,t);
	}

      if (has_observers)
	for (int j=0; j<observers.size(); j++)
	  observers[j]->inserted(at,after, a, r2);
    }

    inline void _change(int at, const STRING & a1, const vector3d<REAL> & r1)
    {
      if (has_observers)
	for (int i=0; i<observers.size(); i++)
	  observers[i]->changed(at, before, a1, r1);
      _crd[at] = r1;
      _atm[at] = a1;

      if (has_observers)
	for (int i=0; i<observers.size(); i++)
	  observers[i]->changed(at, after, a1, r1);
    }

  public:
    virtual void add(const STRING & a, const vector3d<REAL> & r1)
    { _add(a,r1); }

    void add(STRING a, const REAL _x, const REAL _y, const REAL _z)
    {  add(a,{_x,_y,_z}); }

    virtual void insert(int at, const STRING & a, const vector3d<REAL> & r1)
    { _insert(at,a,r1); }

    void insert(int at, const STRING & a, const REAL _x, const REAL _y, const REAL _z)
    { insert(at,a,{_x,_y,_z}); }

    virtual void erase(int at)
    {  _erase(at); }

    inline void shadow(int at, bool sh)
    {
      for (int i=0; i<observers.size(); i++)
	observers[i]->shaded(at, before, sh);
      _shadow[at] = sh;
      for (int i=0; i<observers.size(); i++)
	observers[i]->shaded(at, after, sh);
    }

    virtual void change(int at, const STRING & a1, const vector3d<REAL> & r1)
    { _change(at,a1,r1); }

    void clear()
    {
      _crd.clear();
      _atm.clear();
      _shadow.clear();
      clear_type_table();
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      for (int k=0; k<offset; k++) os << " ";
      os << "geometry";
      if (name != "")
	os << " " << name;
      os << "(" << DIM << "d,atom,x,y,z){\n";

      /*
      os << "(";
      for (int i=0; i<n_param(); i++)
	{
	  param(i)->write(os);
	  if (i<n_param()-1)
	    os << ",";
	}
      os << "){\n";
      */

      cell.write(os,offset+4);

      for (int i=0; i<size(); i++)
	{
	  for (int k=0; k<offset+2; k++) os << " ";
	  os << _atm[i] << boost::format(" %11.6f %11.6f %11.6f\n") % _crd[i].x() % _crd[i].y() % _crd[i].z();

	}

      for (int k=0; k<offset; k++) os << " ";
      os << "}\n";
    }

#ifdef PY_EXPORT

    /*
    inline CELL & py_getcell()
    { return *cell; }

    inline void py_setcell(CELL & cl)
    { 
      cell = & cl;  
      DIM = cell -> DIM;
    }
    */
    // --------------------------------------------------------

    inline vector3d<REAL> py_pos1(int at) const
    { return r(at); }

    inline vector3d<REAL> py_pos2(int at, const index & I ) const
    { return r(at,I); }

    inline vector3d<REAL> py_pos3(const index & AI ) const
    { return r(AI); }


    // --------------------------------------------------------------------
    // Implementing some sexual perversions to make nice&simple properties (atom, coord, x, y, z, shadow)

    STRING py_getatom(int i)
    { 
      if (i<0) i+=nat();
      if (i<0 || i>=nat()) IndexError("geometry::atom::Index out of range");
      return atom(i);
    }
    
    void py_setatom(int i, const STRING & a)
    { 
      if (i<0) i+=nat();
      if (i<0 || i>=nat()) IndexError("geometry::atom::Index out of range");
      change(i,a,coord(i)); 
    }

    py_indexed_property< SELF, STRING, int, &SELF::py_getatom, &SELF::py_setatom> py_atoms;

    bool py_getshadow(int i)
    {
      if (i<0) i+=nat();
      if (i<0 || i>=nat()) IndexError("geometry::shadow::Index out of range");
      return shadow(i);
    }

    void py_setshadow(int i, const bool & b)
    { 
      if (i<0) i+=nat();
      if (i<0 || i>=nat()) IndexError("geometry::shadow::Index out of range");
      shadow(i,b); 
    }

    py_indexed_property< SELF, bool, int, &SELF::py_getshadow, &SELF::py_setshadow> py_shadow;

    //    py_array_vector<REAL> py_coords;

    REAL py_getcoord(int i, int d)
    {
      if (i<0) i+=nat();
      if (i<0 || i>=nat() || d<0 || d>2 ) IndexError("geometry::coord::Index out of range");
      return coord(i)(d);
    }

    void py_setcoord(int i, int d, const REAL & c)
    {
      if (i<0) i+=nat();
      if (i<0 || i>=nat() || d<0 || d>2 ) IndexError("geometry::coord::Index out of range");
      vector3d<REAL> r1 = coord(i);
      r1(d) = c;
      change(i,atom(i),r1);
    }

    vector3d<REAL> py_getvec(int i)
    {
      if (i<0) i+=nat();
      if (i<0 || i>=nat()) IndexError("geometry::coord::Index out of range");
      return coord(i);
    }

    void py_setvec(int i, const vector3d<REAL> & v) 
    {
      if (i<0) i+=nat();
      if (i<0 || i>=nat()) IndexError("geometry::coord::Index out of range");
      change(i,atom(i),v);
    }

    py_2indexed_property<SELF,vector3d<REAL>,REAL, int, &SELF::py_getvec, &SELF::py_setvec, 
			 &SELF::py_getcoord, &SELF::py_setcoord > py_coords;

    template<int d>
    REAL py_getxyz(int i)
    {
      if (i<0) i+=nat();
      if (i<0 || i>=nat()) IndexError("geometry::x,y,z:: Index out of range");
      return py_getcoord(i,d);
    }

    template<int d>
    void py_setxyz(int i, const REAL & c)
    { 
      if (i<0) i+=nat();
      if (i<0 || i>=nat()) IndexError("geometry::x,y,z:: Index out of range");
      py_setcoord(i,d,c); 
    }

    py_indexed_property<SELF, REAL, int, &SELF::py_getxyz<0>, &SELF::py_setxyz<0> > py_x;
    py_indexed_property<SELF, REAL, int, &SELF::py_getxyz<1>, &SELF::py_setxyz<1> > py_y;
    py_indexed_property<SELF, REAL, int, &SELF::py_getxyz<2>, &SELF::py_setxyz<2> > py_z;

    REAL py_getsymmrad(const char * at)
    { 
      int t = type_of_atom(at);
      
      if (t==-1)
	KeyError("geometry::symmrad::get_symmrad: Atom not specified");
      else
	return _symm_rad[t];
    }
    
    void py_setsymmrad(const char *at, const REAL &r)
    { set_symmetrize_radius(at,r);  }

    py_indexed_property<SELF,REAL,const char *, &SELF::py_getsymmrad, &SELF::py_setsymmrad> py_symmrad;

    bp::dict py_symmrad2dict()
    {
      bp::dict d;
      d["default"] = default_symmetrize_radius;
      
      for (int i=0; i<n_atom_types(); i++)
	d[atom_of_type(i)] = _symm_rad[i];

      return d;
    }

    // --------------------------------------------------------------------

    inline int py_typeofatom(const STRING & at)
    {  return type_of_atom(at); }

    // --------------------------------------------------------------------

    static void py_props()
    {
      py_indexed_property< SELF, STRING, int, &SELF::py_getatom, &SELF::py_setatom>::py_export("noname");
      py_indexed_property< SELF, bool, int, &SELF::py_getshadow, &SELF::py_setshadow>::py_export("noname");

      py_2indexed_property<SELF,vector3d<REAL>,REAL, int, &SELF::py_getvec, &SELF::py_setvec, 
			   &SELF::py_getcoord, &SELF::py_setcoord >::py_2export("noname");

      py_indexed_property<SELF, REAL, int, &SELF::py_getxyz<0>, &SELF::py_setxyz<0> >::py_export("noname");
      py_indexed_property<SELF, REAL, int, &SELF::py_getxyz<1>, &SELF::py_setxyz<1> >::py_export("noname");
      py_indexed_property<SELF, REAL, int, &SELF::py_getxyz<2>, &SELF::py_setxyz<2> >::py_export("noname");
      py_indexed_property<SELF,REAL,const char *, &SELF::py_getsymmrad, &SELF::py_setsymmrad>::py_export("noname");

    }

    // --------------------------------------------------------------------

    void py_add1(const STRING & a, const vector3d<REAL> & r1)
    { add(a,r1); }

    void py_add2(STRING a, const REAL _x, const REAL _y, const REAL _z)
    { add(a,_x,_y,_z); }

    bool py_check_axyz(const bp::list & l)
    {
      return 
	bp::len(l) == 4 &&
	bp::extract<STRING>(l[0]).check() &&
	bp::extract<REAL>(l[1]).check() &&
	bp::extract<REAL>(l[2]).check() &&
	bp::extract<REAL>(l[3]).check();	
    }

    virtual void py_add_list(const bp::list & l)
    {
      if (!py_check_axyz(l))
	TypeError("geometry::Invalid list. List must be [atom,x,y,z]");
      
      add(bp::extract<STRING>(l[0]), bp::extract<REAL>(l[1]), bp::extract<REAL>(l[2]), 
	  bp::extract<REAL>(l[3]));
    }

    void py_add3(const bp::list & l)
    {
      if (bp::len(l)==0) return;
      if (bp::extract<bp::list>(l[0]).check())
	// list of lists
	for (int i=0; i<bp::len(l); i++)
	  py_add_list( bp::extract<bp::list>(l[i]) );
      else
	py_add_list(l);
    }

    void py_insert1(int i, const STRING & a, const vector3d<REAL> & r1)
    { 
      if (i<0) i+=nat();      
      if (i<0 || i>nat()) IndexError("geometry::Index out of range");

      insert(i,a,r1); 
    }

    void py_insert2(int i, const STRING & a, const REAL _x, const REAL _y, const REAL _z)
    { 
      if (i<0) i+=nat();      
      if (i<0 || i>nat()) IndexError("geometry::Index out of range");
      insert(i,a,_x,_y,_z); 
    }

    virtual void py_insert_list(int i, const bp::list & l)
    {
      if (!py_check_axyz(l))
	TypeError("geometry::Invalid list. List must be [atom,x,y,z]");
      
      insert(i, bp::extract<STRING>(l[0]), bp::extract<REAL>(l[1]), bp::extract<REAL>(l[2]), 
	     bp::extract<REAL>(l[3]));
    }

    void py_insert3(int at, const bp::list & l)
    {
      if (at<0) at+=nat();      
      if (at<0 || at>nat()) IndexError("geometry::Index out of range");

      if (bp::len(l)==0) return;
      if (bp::extract<bp::list>(l[0]).check())
	// list of lists
	for (int i=0; i<bp::len(l); i++)
	  py_insert_list(at+i, bp::extract<bp::list>(l[i]) );
      else
	py_insert_list(at, l);
    }
  
    void py_erase(int at)
    {
      if (at<0) at+=nat();      
      if (at<0 || at>=nat()) IndexError("geometry::Index out of range");

      erase(at);
    }

    virtual bp::list py_getitem(int i) const
    {      
      if (i<0)
	i+=nat();

      if (i<0 || i>=nat())
	IndexError("geometry::Index out of range");

      bp::list l;
      l.append(atom(i));
      l.append(coord(i).x());
      l.append(coord(i).y());
      l.append(coord(i).z());
      return l;
    }
    
    virtual void py_setitem(int i, const bp::list & l)
    {           
      if (i<0)
	i+=nat();
      
      if (i<0 || i>=nat())
	IndexError("geometry::Index out of range");

      if (!py_check_axyz(l))
	TypeError("geometry::Invalid list. List must be [atom,x,y,z]");

      STRING a1 = bp::extract<STRING>(l[0]);
      REAL x1 = bp::extract<REAL>(l[1]), 
	y1 = bp::extract<REAL>(l[2]), 
	z1 = bp::extract<REAL>(l[3]);
      
      change(i,a1,{x1,y1,z1});
    }    
    

#endif

  };

  template< class REAL, class CELL>
  REAL geometry<REAL,CELL>::tol_geom_default = 1e-5;

#ifdef PY_EXPORT

  template <class REAL>
  struct py_geometry_observer : geometry_observer<REAL>, bp::wrapper<geometry_observer<REAL> >
  {

    void added(before_after s, const STRING & a,  const vector3d<REAL> & v)
    { this->get_override("added")(s,a,v);}

    void inserted(int at, before_after s, const STRING & a, const vector3d<REAL> & v)
    { this->get_override("inserted")(at,s,a,v);}

    void changed( int at, before_after s, const STRING & a, const vector3d<REAL> & v)
    { this->get_override("changed")(at,s,a,v);}

    void erased(  int at, before_after s)
    { this->get_override("erased")(at,s);}

    void shaded(  int at, before_after s, bool h)
    { this->get_override("shaded")(at,s,h);}

  };

#endif

};

#endif

