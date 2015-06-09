#ifndef _QPP_GEOM_H
#define _QPP_GEOM_H

#include <vector>
#include <cmath>
#include <lace/lace3d.hpp>
//#include <lace/lace.hpp>
//#include <symm/symm.hpp>
#include <data/qppdata.hpp>
#include <mathf/constants.hpp>

namespace qpp{

// ------------------- index class ----------------------
// Index is a handy tool to reference atoms in this geometry
// as well as atoms in neighbouring cells
// For that purpose it is a complex index - it contains, besides
// the number of atom it is currently pointning at, also the
// indicies of the cell.
template <int DIM>
class index{
protected:
	int at;
	int cll[DIM];

public:
	inline index& operator=(int _at)
	{
		at=_at;
		for (int d=0; d<DIM; d++)
			cll[d] = 0;
		return *this;
	}

	inline operator int() const {return at;}

	inline int atom() const {return at;}

	inline int & atom() {return at;}

	inline int cell(int d) const {return cll[d];}

	inline int & cell(int d) {return cll[d];}

	inline void set(int _at, int i1=0, int i2=0, int i3=0, int i4=0, int i5=0)
	{
		at=_at;
		if (DIM>0)
			cll[0]=i1;
		if (DIM>1)
			cll[1]=i2;
		if (DIM>2)
			cll[2]=i3;
		if (DIM>3)
			cll[3]=i4;
		if (DIM>4)
			cll[4]=i5;
	}

	inline void setatom(int _at){at=_at;}

	inline void setcell(int d, int i){cll[d]=i;}

	index()
	{ set(0); }

	index(int _at, int i1=0, int i2=0, int i3=0, int i4=0, int i5=0)
	{ set(_at,i1,i2,i3,i4,i5); }

	index(const index<DIM> & I)
	{
		at = I.at;
		for (int d =0; d<DIM; d++)
			cll[d] = I.cll[d];
	}

	inline bool operator==(const index<DIM> & I) const
	{
		bool res = (at == I.at);
		for (int d=0; d<DIM; d++)
			res = res && (cll[d] == I.cll[d]);
		return res;
	}

	inline bool operator!=(const index<DIM> &I) const
	{
		return ! ((*this)==I);
	}

};

template<int DIM>
std::basic_ostream<CHAR,TRAITS>&
operator<<(std::basic_ostream<CHAR,TRAITS>& __os, index<DIM> i)
{
	std::basic_ostringstream<CHAR,TRAITS> __s;
	__s.flags(__os.flags());
	__s.imbue(__os.getloc());
	__s.precision(__os.precision());

	__s << i.atom();
	if (DIM>0)
	{
		__s << "("  << i.cell(0);
		for (int d=1; d<DIM; d++)
			__s << "," << i.cell(d);
		__s << ")";
	}
	return __os << __s.str();
}

/* -----------------------------------------------------------
	 The class TRANSFORM is not being defined, though it will be
	 used as a template parameter.
	 Any class having transform method can be substituted for TRANSFORM

	 template <int DIM, class CREAL, ...>
	 class A {

	 public:
	 lace::vector3d<CREAL> transform(const lace::vector3d<CREAL> &r, index<DIM> i) const;
	 };
  */
//--------------------------------------------------------------//

// The struct to store 1, 2 or 3 translation vectors
template<int DIM,class CREAL=double>
struct periodic_cell :  public qpp_object{
	lace::vector3d<CREAL> v[DIM];

	periodic_cell(const STRING & __name = "", qpp_object * __owner = NULL) : qpp_object(__name,_owner)
	{}

	periodic_cell(const periodic_cell<DIM,CREAL> & cl) : qpp_object(cl.name(), cl.owner())
	{
		for(int i=0; i<DIM; i++)
			v[i] = cl.v[i];
	}

	periodic_cell(CREAL a, CREAL b, CREAL c,
				  CREAL alpha, CREAL beta, CREAL gamma,
				  const STRING & __name = "", qpp_object * __owner = NULL) : qpp_object(__name,_owner)
	  // for DIM==3
	{
		v[0] = lace::vector3d<CREAL>(a,CREAL(0),CREAL(0));
		v[1] = lace::vector3d<CREAL>(b*std::cos(gamma), b*std::sin(gamma),
									 CREAL(0));
		CREAL nx = std::cos(beta);
		CREAL ny = (std::cos(alpha) - nx*std::cos(gamma))/std::sin(gamma);
		CREAL nz = std::sqrt(1-nx*nx-ny*ny);
		v[2] = lace::vector3d<CREAL>(nx,ny,nz)*c;

		_name = __name;
	}

	periodic_cell(lace::vector3d<CREAL > a, lace::vector3d<CREAL > b=0, lace::vector3d<CREAL > c=0,
				  const STRING & __name = "", qpp_object * __owner = NULL) : qpp_object(__name,_owner)
	{
		if (DIM>0)
			v[0] = a;
		if (DIM>1)
			v[1] = b;
		if (DIM>2)
			v[2] = c;
	}

	lace::vector3d<CREAL> transform(const lace::vector3d<CREAL> &r, index<DIM> i) const
	{
		if (DIM==0)
			return r;
		if (DIM==1)
			return r + v[0]*i.cell(0);
		if (DIM==2)
			return r + v[0]*i.cell(0)  + v[1]*i.cell(1);
		if (DIM==3)
			return r + v[0]*i.cell(0)  + v[1]*i.cell(1) + v[2]*i.cell(2);

	}

	inline lace::vector3d<CREAL> & operator()(int i)
	// fixme - not obvious convention
	{ return v[i]; }

	inline lace::vector3d<CREAL> operator()(int i) const
	{ return v[i]; }

	inline CREAL & operator()(int i, int j)
	{ return v[i](j); }

	inline CREAL operator()(int i, int j) const
	{ return v[i](j); }

	inline periodic_cell<DIM,CREAL> & operator=(const periodic_cell<DIM,CREAL> & cl)
	{
		_name = cl._name;
		for(int i=0; i<DIM; i++)
			v[i] = cl.v[i];
		return *this;
	}

	inline lace::vector3d<CREAL> frac2cart(lace::vector3d<CREAL> frac) const
	// transforms fractional coordinates to cartesian
	// Works for any DIM, but the vector frac still should be 3d
	// if DIM<3, frac(i) components with i>=DIM are not used
	{
		lace::vector3d<CREAL> res=CREAL(0);
		for (int i=0; i<DIM; i++)
			res+=frac(i)*v[i];
		return res;
	}

	//   inline lace::vector3d<CREAL> frac2cart(simple_vector<CREAL,DIM> frac)
	// fractional to cartesian coordinates
	// works for DIM=1,2,3
	// here we use simple_vector to pass fractional coords
	//{
	//  lace::vector3d<CREAL> res=CREAL(0);
	//  for (int i=0; i<DIM; i++)
	//	res+=frac(i)*v[i];
	// return res;
	//}

	inline lace::vector3d<CREAL> cart2frac(lace::vector3d<CREAL> r) const
	// cartesian to fractional
	// works for DIM==3 only
	{
		lace::matrix3d<CREAL> A(v[0],v[1],v[2]);
		return lace::solve3d(A, r);
	}

	inline lace::vector3d<CREAL> reduce(lace::vector3d<CREAL> r)  const
	// Brings the point r into the volume of unit cell
	// by translations
	// unit cell is defined as parallelepiped with one vertex in
	// the coordinate origin
	// the others are pointed by v[0],v[1],v[2] vectors
	{
		lace::vector3d<CREAL> f = cart2frac(r);
		f(0) -= floor(f(0));
		f(1) -= floor(f(1));
		f(2) -= floor(f(2));
		return frac2cart(f);
	}

	inline lace::vector3d<CREAL> reduce_cntr(lace::vector3d<CREAL> r) const
	// Brings the point r into the volume of unit cell
	// by translations
	// unit cell is defined as parallelepiped CENTRED in the
	// coordinate origin
	{
		lace::vector3d<CREAL> f = cart2frac(r);
		for (int i=0; i<3; i++)
		{
			f(i) -= int(f(i));
			if ( f(i) > CREAL(1)/2 ) f(i)-=1;
		}
		return frac2cart(f);
	}

	inline lace::vector3d<CREAL> reduce_wz(lace::vector3d<CREAL> r) const
	// Brings r into Wigner-Zeitz unit cell
	// fixme - implement this!
	{}

	inline bool in_cell(lace::vector3d<CREAL> r) const
	// Answers the question whether r belongs to the unit cell
	{
		lace::vector3d<CREAL> f = cart2frac(r);
		return
				CREAL(0)<=f(0) && f(0) < CREAL(1) &&
				CREAL(0)<=f(1) && f(1) < CREAL(1) &&
				CREAL(0)<=f(2) && f(2) < CREAL(1);
	}


	inline bool in_cell_cntr(lace::vector3d<CREAL> r) const
	// does r belong to unit cell centred at the coords origin?
	{
		lace::vector3d<CREAL> f = cart2frac(r);
		return
				-CREAL(1)/2 <= f(0) && f(0) < CREAL(1)/2 &&
				-CREAL(1)/2 <= f(1) && f(1) < CREAL(1)/2 &&
				-CREAL(1)/2 <= f(2) && f(2) < CREAL(1)/2;
	}

	inline bool in_cell_wz(lace::vector3d<CREAL> r) const
	// does r belong to Wigner-Zeitz unit cell
	// fixme - implement this!
	{}

	virtual STRING category() const
	{
		return "vectors";
	}

	virtual qppobject_type gettype() const
	{
		int d;
		if (DIM==0)
			d = qtype_dim0;
		else if (DIM==1)
			d = qtype_dim1;
		else if (DIM==2)
			d = qtype_dim2;
		else if (DIM==3)
			d = qtype_dim3;
		return qtype_vectors | d | qtype_data<CREAL>::type;
	}

	virtual int n_nested() const
	{ return 0; }

	virtual qpp_object* nested(int i) const
	{ return NULL; }

        virtual qpp_object * copy() const
        {
	  return new periodic_cell<DIM,CREAL>(*this);
	}

	virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
	{
		for (int k=0; k<offset; k++) os << " ";
		os << "vectors";
		if (_name != "")
			os << " " << _name;
		os << "(" << DIM << "d){\n";

		for (int i=0; i<DIM; i++)
		{
			for (int k=0; k<offset+2; k++) os << " ";
			os << boost::format(" %11.6f %11.6f %11.6f\n") % v[i](0) % v[i](1) % v[i](2);
		}

		for (int k=0; k<offset; k++) os << " ";
		os << "}\n";
	}

	void symmtrap(lace::vector3d<CREAL> & r, CREAL symmtrap_radius)
	{}

};

//--------------------------------------------------------------//
/* Geometry dependent objects
	 One geometry can maintain arbitrary number of "dependants", i.e.
	 objects which need to know about the changes made to geometry.
	 Geometry will inform them all when atoms are added, inserted or removed
  */

class geometry_dependent{
public:

	virtual void added(bool done) =0;
	virtual void inserted(int i, bool done) =0;
	virtual void erased(int i, bool done) =0;
};


//--------------------------------------------------------------//

// The geometry class stores atoms together with their
// coordinates.

template< int DIM, class CREAL=double, class TRANSFORM = periodic_cell<DIM,CREAL> >
class geometry : public qpp_array{

protected:

	//int nat;
	// Number of atoms/points

	std::vector<STRING> atm;
	// Storage of atoms

	std::vector<lace::vector3d<CREAL> > crd;
	// Their coordinates

	std::vector<char> _shadow;

	TRANSFORM * trnf;

	std::vector<geometry_dependent*> dependents;

	int _nparm;

public:

	using qpp_array::add;
	//    periodic_cell<DIM,CREAL,charT,traits> cell;
	//    bool update_types, update_neighbours;
	bool update_types;

	CREAL geomtol;

	TRANSFORM & symm(){return *trnf;}

	// Just a synonim

	TRANSFORM & cell;

	// Unit cell vectors for 1,2,3d periodicity

	// ------------------- iterator class --------------------
	// Iterator allows you run through all (or some) atoms of this cell
	// and of surrounding cells

	class iterator : public index<DIM>{

		index<DIM> a, b;
		// a - from
		// b - to

		geometry<DIM, CREAL, TRANSFORM> * geom;

		using index<DIM>::at;
		using index<DIM>::cll;

		void inc()
		{
			if (*this == b)
				*this = end();

			if ( *this == end())
				return;

			at++;
			if (at > b.atom() && DIM>0)
			{
				at=a.atom();
				int d=0;
				while(d < DIM)
				{
					cll[d]++;
					if (cll[d] > b.cell(d))
					{
						for(int dd=0; dd<=d; dd++)
							cll[d] = a.cell(dd);
						d++;
					}
					else
						break;
				}
			}

		}

	public:

		iterator(geometry<DIM, CREAL, TRANSFORM> &g)
		// default iterator goes through neighbouring cells only
		{
			a.setatom(0);
			for (int d=0; d < DIM; d++)
				a.setcell(d,-1);
			b.setatom(g.nat() - 1);
			for (int d=0; d < DIM; d++)
				b.setcell(d,1);
			geom = &g;
		}

		iterator(index<DIM> _a, index<DIM> _b)
		{
			a = _a;
			b = _b;
			geom = NULL;
		}

		iterator(index<DIM> _a, index<DIM> _b, geometry<DIM, CREAL, TRANSFORM> &g)
		{
			a = _a;
			b = _b;
			geom = &g;
		}

		inline index<DIM> begin()
		{
			iterator tmp(a,b,*geom);
			tmp = a;
			while ( geom != NULL && tmp != end() ? geom -> shadow(tmp) : false)
				tmp.inc();
			return tmp;
		}

		//      inline index end(){return b;}

		inline index<DIM> end(){return index<DIM>(-1,0,0,0);}

		inline iterator& operator=(const index<DIM> &i)
		{
			at = i.atom();
			for (int d = 0; d<DIM; d++)
				cll[d] = i.cell(d);
		}

		/*
	  inline bool operator==(const index<DIM> & i) const
	  {
	bool res = (at == i.atom());
	if (res)
	  for (int d = 0; d<DIM; d++)
		if ( cll[d] != i.cell(d) )
		  {
		res = false;
		break;
		  }
	return res;
	  }

	  inline bool operator!=(index<DIM> i)
	  {
	if (DIM==0)
	  return at != i.atom();
	else if (DIM==1)
	  return at != i.atom() || cll[0] != i.cell(0);
	else if (DIM==2)
	  return at != i.atom() || cll[0] != i.cell(0) || cll[1] != i.cell(1);
	else if (DIM==3)
	  return at != i.atom() || cll[0] != i.cell(0) || cll[1] != i.cell(1) || cll[2] != i.cell(2);
	  }
	  */
		iterator& operator++(int)
		{
			do
			{ inc();}
			while ( geom != NULL && *this != end() ? geom -> shadow(*this) : false);
		}

	};

	// ---------------------------------------------------------
public:

	virtual STRING category() const
	{
		return "geometry";
	}

	virtual qppobject_type gettype() const
	{
		int d;
		if (DIM==0)
			d = qtype_dim0;
		else if (DIM==1)
			d = qtype_dim1;
		else if (DIM==2)
			d = qtype_dim2;
		else if (DIM==3)
			d = qtype_dim3;
		return qtype_geometry | d | qtype_data<CREAL>::type;
	}

	int n_param() const
	{
		return _nparm;
	}

	qpp_object * param(int i) const
	{
		return nested(i);
	}
	inline int size() const
	{return crd.size();}

	inline int nat() const
	{return crd.size();}

	inline STRING & atom(index<DIM> i)
	{return atm[i.atom()];}

	inline STRING atom(index<DIM> i) const
	{return atm[i.atom()];}

	// coord gives the coordinates of i-th atom in the cell
	inline lace::vector3d<CREAL> coord(int i) const{return crd[i];}

	inline lace::vector3d<CREAL>& coord(int i){return crd[i];}

	// Unlike coord(i), position(i) gives the coordinates of either
	// this atom in this unit cell or the coordinates of its image
	// in neighbouring cells
	// In other words
	// coord(i) = cell_coord(i) + atom_coord(i)
	inline lace::vector3d<CREAL> position(const index<DIM> & i) const
	{
		return trnf -> transform(crd[i.atom()],i);
	}

	virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
	{
		for (int k=0; k<offset; k++) os << " ";
		os << "geometry";
		if (_name != "")
			os << " " << _name;
		//      os << "(" << DIM << "d,atom,x,y,z){\n";
		os << "(";
		for (int i=0; i<n_param(); i++)
		{
			param(i)->write(os);
			if (i<n_param()-1)
				os << ",";
		}
		os << "){\n";

		for (int i=0; i<size(); i++)
		{
			for (int k=0; k<offset+2; k++) os << " ";
			os << atm[i] << boost::format(" %11.6f %11.6f %11.6f\n") % crd[i].x() % crd[i].y() %crd[i].z();

		}

		for (int k=0; k<offset; k++) os << " ";
		os << "}\n";
	}

  virtual qpp_object * copy() const
  {
    return new geometry<DIM,CREAL,TRANSFORM>(*this);
  }

	//------------------- Type table operations -------------------------

private:
	std::vector<STRING> _atm_types;
	std::vector<int> _type_table;

public:

	class neighbours_table;
	neighbours_table ngbr;

	// Number of atomic types in molecule
	inline int n_atom_types() const
	{
		return _atm_types.size();
	}

	// Reference to atom of type number t (not the atom number t in atomic list!)
	inline STRING atom_of_type(int t) const
	{
		return _atm_types[t];
	}

	// Number of type of certain ATOM at
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

	//
	inline int type_table(int i) const
	{return _type_table[i];}

	// synonims
	inline int type(int i) const
	{
		return type_table(i);
	}

	inline int type_of_atom(int i) const
	{
		return type_table(i);
	}

	inline int type(const STRING & at) const
	{
		return type_of_atom(at);
	}

	virtual void build_type_table()
	{
		_atm_types.clear();
		_type_table.resize(size());

		for (int i=0; i<size(); i++)
		{
			int t = type_of_atom(atom(i));
			if (t == -1)
			{
				t = _atm_types.size();
				_atm_types.push_back(atom(i));
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

	// ------------------- Neighbours table -----------------------
	class neighbours_table : public geometry_dependent{
		std::vector<std::vector<index<DIM> > > _table;

		struct _ngbr_record{
			STRING at1, at2;
			CREAL d;

			_ngbr_record(STRING _at1, STRING _at2, CREAL _d)
			{
				at1 = _at1;
				at2 = _at2;
				d = _d;
			}
		};

		std::vector<_ngbr_record> _records;
		CREAL *_disttable;

		lace::vector3d<CREAL> Rmin, Rmax;
		CREAL grainsize;
		int grain_nx, grain_ny, grain_nz;
		std::vector<std::vector<index<DIM> > > _grains;

		inline int _record_match(STRING at1, STRING at2, int i)
		{
			return ( at1 == _records[i].at1 && at2 == _records[i].at2 ) ||
					( at2 == _records[i].at1 && at1 == _records[i].at2 );
		}

		void _grain_setup()
		{
			// find largest neighbourung distance
			grainsize = CREAL(0);
			int ntp = geom->n_atom_types();
			for (int i=0; i<ntp*ntp; i++)
				if (_disttable[i] > grainsize )
					grainsize = _disttable[i];
			Rmin = Rmax = geom->position(0);
			for (int i=1; i<geom->size(); i++)
			{
				if ( Rmin.x() > geom->position(i).x() )
					Rmin.x() = geom->position(i).x();
				if ( Rmax.x() < geom->position(i).x() )
					Rmax.x() = geom->position(i).x();
				if ( Rmin.y() > geom->position(i).y() )
					Rmin.y() = geom->position(i).y();
				if ( Rmax.y() < geom->position(i).y() )
					Rmax.y() = geom->position(i).y();
				if ( Rmin.z() > geom->position(i).z() )
					Rmin.z() = geom->position(i).z();
				if ( Rmax.z() < geom->position(i).z() )
					Rmax.z() = geom->position(i).z();
			}
			if (DIM==0)
			{
				//fixme
				grain_nx = int( (Rmax.x()-Rmin.x())/grainsize ) + 3;
				grain_ny = int( (Rmax.y()-Rmin.y())/grainsize ) + 3;
				grain_nz = int( (Rmax.z()-Rmin.z())/grainsize ) + 3;
			}
			else
			{
				grain_nx = int( (Rmax.x()-Rmin.x())/grainsize ) + 3;
				grain_ny = int( (Rmax.y()-Rmin.y())/grainsize ) + 3;
				grain_nz = int( (Rmax.z()-Rmin.z())/grainsize ) + 3;
			}

			//debug
			//std::cout << "Grain setup:\n" << grain_nx<<"x"<<grain_ny<<"x"<<grain_nz<<"\n";
			//std::cout << "grain size= " << grainsize << " corners= " << Rmin << Rmax << "\n";
		}

		inline std::vector<index<DIM> > & grains(int i, int j, int k)
		{
			return _grains[i*grain_ny*grain_nz + j*grain_nz + k];
		}

		inline void ijk_grain(const index<DIM> & at, int &i, int &j, int &k)
		{
			lace::vector3d<CREAL> r = geom->position(at);
			i = floor( (r.x()-Rmin.x())/grainsize ) + 1;
			j = floor( (r.y()-Rmin.y())/grainsize ) + 1;
			k = floor( (r.z()-Rmin.z())/grainsize ) + 1;
		}

		inline void to_grain(const index<DIM> & at)
		{
		  //lace::vector3d<CREAL> r = geom->position(at);
			int i,j,k;
			ijk_grain(at,i,j,k);
			if ( i>=0 && i<grain_nx && j>=0 && j<grain_ny && k>=0 && k<grain_nz)
			{
				//lace::vector3d<CREAL> r = geom->position(at);
				/*
		bool found = false;
		for (int l=0; l<grains(i,j,k).size(); l++)
		  if ( norm( r - geom->position(grains(i,j,k)[l])) < geom->geomtol &&
		   at.atom() == grains(i,j,k)[l].atom() )
		{
		  found = true;
		  break;
		}

		if (!found)
		*/
				grains(i,j,k).push_back(at);
			}
		}


		void _graining()
		{
			for (int i=0; i<_grains.size(); i++)
				_grains[i].clear();
			_grains.clear();
			_grains.resize(grain_nx*grain_ny*grain_nz);

			for (int i=0; i<geom->nat(); i++)
				if (! geom->shadow(i) )
					to_grain(i);
			geometry<DIM, CREAL, TRANSFORM>::iterator at(*geom);
			for ( at = at.begin(); at != at.end(); at++)
				if ( at != index<DIM>(at.atom()) )
					to_grain(at);

			//      debug
			/*
	std::cerr << "graining finished\n";
	for (int i=0; i<grain_nx; i++)
	  for (int j=0; j<grain_ny; j++)
		for (int k=0; k<grain_nz; k++)
		  {
		std::cerr << i << " " << j << " " << k;
		for (int l=0; l<grains(i,j,k).size(); l++)
		  std::cerr << " " << grains(i,j,k)[l];
		std::cerr << "\n";
		  }
	*/

		}

		// -------------------------------------------------------------------

		inline void _add_ngbr(int i, const index<DIM> & j)
		{
			bool found = false;
			for (int k = 0; k < _table[i].size(); k++ )
				if (_table[i][k]==j)
				{
					found = true;
					break;
				}
			if (!found)
				_table[i].push_back(j);
		}

	public:

		geometry<DIM, CREAL, TRANSFORM> * geom;

		CREAL default_distance;
		bool autoupdate;
		bool reference_mode;

		neighbours_table( geometry<DIM, CREAL, TRANSFORM> & g)
		{
			_disttable = NULL;
			default_distance = CREAL(0);
			geom = & g;
			reference_mode = geom->nat() < 100;
		}

		// Number of neighbours of i-th atom
		inline int n(int i)
		{
			return _table[i].size();
		}

		// j-th neighbour of i-th atom
		inline index<DIM> table(int i, int j) const
		{
			return _table[i][j];
		}

		inline index<DIM> operator()(index<DIM> i, int j) const
		{
			index<DIM> res = table(i,j);
			for (int a=0; a<DIM; a++)
				res.setcell( a, res.cell(a)+i.cell(a) );
			return res;
		}

		CREAL distance(STRING at1, STRING at2)
		{
			bool found = false;
			int i;
			for (i=0; i<_records.size(); i++)
				if (_record_match(at1,at2,i))
				{
					found = true;
					break;
				}
			return found? _records[i].d : default_distance;
		}

		void set_distance(STRING at1, STRING at2, CREAL d)
		{
			bool found = false;
			int i;
			for (i=0; i<_records.size(); i++)
				if (_record_match(at1,at2,i))
				{
					found = true;
					break;
				}
			if (found)
				_records[i].d = d;
			else
				_records.push_back(_ngbr_record(at1,at2,d));
		}

		void clear_distance()
		{
			_records.clear();
		}

		inline void resize_disttable()
		{
			if (_disttable!=NULL)
				delete _disttable;
			int N = geom->n_atom_types();
			_disttable = new CREAL[N*N];
		}

		CREAL distance(int i, int j)
		{
			if (_disttable!=NULL)
				return _disttable[i*geom->n_atom_types()+j];
			else
				return default_distance;
		}

		inline void build_disttable()
		{
			resize_disttable();
			int n = geom->n_atom_types();
			for (int i=0; i<n; i++)
				for (int j=0; j<=i; j++)
					_disttable[n*i+j] = _disttable[n*j+i] =
							distance(geom->atom_of_type(i),geom->atom_of_type(j));
		}

		// -------------------------------------------------------------------

		void build()
		{
			if (reference_mode)
			{
				reference_build();
				return;
			}

			_grain_setup();
			_graining();
			for (int i=0; i<_table.size(); i++)
				_table[i].clear();

			_table.resize(geom->size());

			for (int i = 1; i < grain_nx; i++)
				for (int j = 1; j < grain_ny; j++)
					for (int k = 1; k < grain_nz; k++)
					{
						int g1 = i*grain_ny*grain_nz + j*grain_nz + k;
						if (_grains[g1].size()>0)
							for (int di=-1; di<=0; di++)
								for (int dj=-1; dj<=-di; dj++)
									for (int dk=-1; dk<=-di || dk<=-dj; dk++)
									{
										int g2 = (i+di)*grain_ny*grain_nz + (j+dj)*grain_nz + k+dk;
										for (int c2 = 0; c2 < _grains[g2].size(); c2++)
											for (int c1 = 0; c1 < ( g1==g2? c2 : _grains[g1].size()); c1++)
											{
												index<DIM> at1 = _grains[g1][c1];
												index<DIM> at2 = _grains[g2][c2];
												CREAL r = norm(geom->position(at1) - geom->position(at2));

												if ( r <= distance(geom->type_table(at1), geom->type_table(at2)))
												{
													//debug
													/*
					std::cerr << "pair " << i << " " << j << " " << k << " "
						  << i+di << " " << j+dj << " " << k+dk << " "
						  << at1 << geom->position(at1) << " "
						  << at2 << geom->position(at2) << " " << r << "\n";
					*/

													if ( at1 == index<DIM>(at1.atom()) )
													{
														_add_ngbr(at1,at2);
														//_table[at1].push_back(at2);
														//debug
														/*
					std::cerr << i << " " << j << " " << k << " "
						  << i+di << " " << j+dj << " " << k+dk << " "
						  << at1 << geom->position(at1) << " "
						  << at2 << geom->position(at2) << " " << r << "\n";
					*/

														index<DIM> at(at1);
														for (int dd=0; dd<DIM; dd++)
															at.setcell(dd,-at2.cell(dd));
														_add_ngbr(at2,at);
														//_table[at2].push_back(at);
														//debug
														/*
					std::cerr << "case2 " << i << " " << j << " " << k << " "
						  << i+di << " " << j+dj << " " << k+dk << " "
						  << at2 << geom->position(at2) << " "
						  << at1 << geom->position(at1) << " " << r << "\n";
					*/
													}

													if ( at2 == index<DIM>(at2.atom()) )
													{
														//debug
														//std::cout << "hehe\n";

														_add_ngbr(at2,at1);
														//debug
														/*
					std::cerr << "case3 " << i << " " << j << " " << k << " "
						  << i+di << " " << j+dj << " " << k+dk << " "
						  << at2 << " " << at1 << " " << r << "\n";
					*/
														/*
					if ( at1 != index<DIM>(at1.atom()) )
					  {
						for (int dd=0; dd<DIM; dd++)
						  at2.setcell(dd,-at1.cell(dd));
						_table[at1].push_back(at2);
					  }
					*/
													}


												}
											}
									}
					}
		}

		void reference_build()
		{
			for (int i=0; i<_table.size(); i++)
				_table[i].clear();

			_table.resize(geom->size());

			for (int i=0; i<geom->nat(); i++)
				if (!geom->shadow(i))
				{
					geometry<DIM, CREAL, TRANSFORM>::iterator j(*geom);
					for (j=j.begin(); j!=j.end(); j++)
						if ( norm(geom->position(i) - geom->position(j)) <
							 distance(geom->type_table(i), geom->type_table(j))
							 && j!=index<DIM>(i) && ! geom->shadow(j) )
							_table[i].push_back(j);
				}
		}

		void ref_inserted(int at, bool done)
		{
			if (done)
			{
				_table.insert(_table.begin()+at, std::vector<index<DIM> >());
				geometry<DIM, CREAL, TRANSFORM>::iterator j(*geom);
				for (j=j.begin(); j!=j.end(); j++)
					if ( ! geom->shadow(j) && j!=index<DIM>(at) && norm(geom->position(at) - geom->position(j)) <
						 distance(geom->type_table(at), geom->type_table(j)) )
					{
						_table[at].push_back(j);
						index<DIM> iat(at);
						for (int d=0; d<DIM; d++)
							iat.setcell(d,-j.cell(d));
						_table[j].push_back(iat);
					}
			}
		}

		virtual void ref_erased(int at, bool done)
		{
			if (!done)
			{
				_table.erase(_table.begin()+at);

				for (int i=geom->nat()-2; i>=0; i--)
					for (int j=n(i)-1; j>=0; j--)
						if (_table[i][j].atom()==at)
						{
							//std::cerr << "erase " << i << " " << _table[i][j] << "\n";
							_table[i].erase(_table[i].begin()+j);
						}
						else if (_table[i][j].atom()>at)
						{
							//std::cerr << _table[i][j] << "->";
							_table[i][j].atom()--;
							//std::cerr << _table[i][j] << "\n";
						}
			}
		}

		/*
	  void build()
	  {
	_grain_setup();
	_graining();
	for (int i=0; i<_table.size(); i++)
	  _table[i].clear();

	_table.resize(geom->size());

	for (int i = 0; i < grain_nx; i++)
	  for (int j = 0; j < grain_ny; j++)
		for (int k = 0; k < grain_nz; k++)
		  {
		int g1 = i*grain_ny*grain_nz + j*grain_nz + k;
		if (_grains[g1].size()>0)
		  for (int di=-1; di<=1; di++)
			for (int dj=-1; dj<=1; dj++)
			  for (int dk=-1; dk<=1; dk++)
			if ( 0 <= i+di && i+di < grain_nx &&  0 <= j+dj && j+dj < grain_ny  &&
				 0 <= k+dk && k+dk < grain_nz)
			  {
				int g2 = (i+di)*grain_ny*grain_nz + (j+dj)*grain_nz + k+dk;
				for (int c1 = 0; c1 < _grains[g1].size(); c1++)
				  {
				index<DIM> at1 = _grains[g1][c1];
				if (at1 != index<DIM>(at1.atom()))
				  break;

				for (int c2 = 0; c2 < _grains[g2].size(); c2++)
				  {
					index<DIM> at2 = _grains[g2][c2];
					CREAL r = norm(geom->position(at1) - geom->position(at2));

					if ( at1.atom() == at2.atom() && r < geom->geomtol)
					  continue;

					if ( at1 != at2 && r <= distance(geom->type_table(at1), geom->type_table(at2)))
					  _table[at1].push_back(at2);

				  }

				  }
			  }
		  }
	  }
	  */

		virtual void inserted(int at, bool done)
		{
			if (reference_mode)
			{
				ref_inserted(at,done);
				return;
			}
			if (done)
			{
				lace::vector3d<CREAL> r = geom->position(at);
				if ( r.x()<Rmin.x()-geom->geomtol || r.x()>Rmax.x()+geom->geomtol ||
					 r.y()<Rmin.y()-geom->geomtol || r.y()>Rmax.y()+geom->geomtol ||
					 r.z()<Rmin.z()-geom->geomtol || r.z()>Rmax.z()+geom->geomtol )
				{
					//debug
					//std::cerr << "Complete rebuild after " << geom->atom(at) << r << "\n";
					//std::cerr << Rmin << Rmax << "\n";
					build();
					return;
				}
				_table.insert(_table.begin()+at, std::vector<index<DIM> >());

				for (int i=0; i<_grains.size(); i++)
					for (int j=0; j<_grains[i].size(); j++)
						if (_grains[i][j].atom()>=at)
							_grains[i][j].atom()++;

				for (int i=0; i<geom->nat(); i++)
					for (int j=0; j<n(i); j++)
						if (_table[i][j].atom()>=at)
							_table[i][j].atom()++;

				index<DIM> im1(at,-1,-1,-1), im2(at,1,1,1);
				geometry<DIM, CREAL, TRANSFORM>::iterator aat(im1,im2);
				for (aat=aat.begin(); aat!=aat.end(); aat++)
					to_grain(aat);

				int i,j,k;
				ijk_grain(at,i,j,k);

				for (int i1=i-1; i1<=i+1; i1++)
					if (i1>=0 && i1<=grain_nx)
						for (int j1=j-1; j1<=j+1; j1++)
							if (j1>=0 && j1<=grain_ny)
								for (int k1=k-1; k1<=k+1; k1++)
									if (k1>=0 && k1<=grain_nz)
									{
										int g = i1*grain_ny*grain_nz + j1*grain_nz + k1;
										for (int l=0; l<_grains[g].size(); l++)
										{
											index<DIM> at1 = _grains[g][l];
											lace::vector3d<CREAL> r1 = geom -> position(at1);

											if ( at != at1 && norm(r-r1)
												 <= distance(geom->type_table(at), geom->type_table(at1)))
											{
												_table[at].push_back(at1);
												index<DIM> at2=at;
												for (int d=0; d<DIM; d++)
													at2.cell(d) = -at1.cell(d);
												_table[at1].push_back(at2);
											}
										}
									}


			}
		}

		virtual void added(bool done)
		{
			inserted(geom->nat()-1,done);
		}

		virtual void erased(int at, bool done)
		{
			if (reference_mode)
			{
				ref_erased(at,done);
				return;
			}
			if (!done)
			{
				for (int i=0; i<_grains.size(); i++)
					for (int j=_grains[i].size()-1; j>=0; j--)
						if (_grains[i][j].atom() == at)
							_grains[i].erase(_grains[i].begin()+j);
						else if (_grains[i][j].atom()>at)
							_grains[i][j].atom()--;

				_table.erase(_table.begin()+at);

				for (int i=geom->nat()-2; i>=0; i--)
					for (int j=n(i)-1; j>=0; j--)
						if (_table[i][j].atom()==at)
						{
							//std::cerr << "erase " << i << " " << _table[i][j] << "\n";
							_table[i].erase(_table[i].begin()+j);
						}
						else if (_table[i][j].atom()>at)
						{
							//std::cerr << _table[i][j] << "->";
							_table[i][j].atom()--;
							//std::cerr << _table[i][j] << "\n";
						}
			}
		}

		//------------------------------------------------------------
		bool operator==(const neighbours_table & t)
		{
			if (_table.size() != t._table.size())
				return false;
			for (int i=0; i<_table.size(); i++)
			{
				if (_table[i].size() != t._table[i].size())
					return false;
				for (int j=0; j<_table[i].size(); j++)
				{
					bool found = false;
					for (int k=0; k<_table[i].size(); k++)
						if (_table[i][j]==t._table[i][k])
						{
							found=true;
							break;
						}
					if (!found)
						return false;
				}
			}
			return true;
		}

	};

protected:
	qpp_param_array * _makeparam()
	{
		qpp_param_array * _parm = new qpp_param_array("parameters",this);
		_parm->add(*new qpp_parameter<int>("dim",DIM,_parm));

		return _parm;
	}

	void _addparam(qpp_param_array * __parm)
	{
		if (__parm == NULL)
			__parm = _makeparam();

		for (int i=0; i<__parm->n_nested(); i++)
			add(*__parm->nested(i));
		_nparm =__parm->n_nested();
	}

public:
	// --------------- Constructors & destructors --------------------

	geometry(TRANSFORM & _trnf, const STRING & __name = "",
			 qpp_object * __owner = NULL, qpp_param_array * __parm = NULL) :
		qpp_array(__name,__owner), trnf(&_trnf), cell(_trnf), ngbr(*this)
	{
		//      trnf = & _trnf;
		update_types = false;
		geomtol = default_geomtol;
		_addparam(__parm);
		//update_neighbours = false;
	}

	geometry(const STRING & __name = "",
			 qpp_object * __owner = NULL, qpp_param_array * __parm = NULL) :
		qpp_array(__name,__owner), trnf(new TRANSFORM), cell(*trnf), ngbr(*this)
	{
		update_types = false;
		geomtol = default_geomtol;
		//update_neighbours = false;
		_addparam(__parm);
	}

	~geometry()
	{
		//if (_ngbr_disttable!=NULL)
		//delete _ngbr_disttable;
	}

	void copy(const geometry<DIM, CREAL, TRANSFORM> &G)
	{
		// fixme - what is necessary to copy?
		clear();
		atm = G.atm;
		crd = G.crd;
		_shadow = G._shadow;
		geomtol = G.geomtol;
	}

	// ----------------------- Managing dependents -----------------------

	void add_dependent(geometry_dependent * d)
	{
		dependents.push_back(d);
	}

	void remove_dependent(geometry_dependent * d)
	{
		std::vector<geometry_dependent*>::iterator i = dependents.begin();
		while(i != dependents.end())
		{
			if (*i == d)
			{
				dependents.erase(i);
				break;
			}
			i++;
		}
	}

	// ----------------------- Manipulations with atoms -----------------------

	virtual void add(const STRING & a, const lace::vector3d<CREAL> & r)
	{
		//std::cerr << "geometry::add entry\n";
		for (int i=0; i<dependents.size(); i++)
			dependents[i]->added(false);

		atm.push_back(a);
		crd.push_back(r);
		_shadow.push_back((char)false);
		if (update_types)
		{
			int t = type_of_atom(a);
			if (t == -1)
			{
				t = _atm_types.size();
				_atm_types.push_back(a);
				/*if (update_neighbours)
		{
		ngbr.resize_disttable();
		ngbr.build_disttable();
		}
		  */
			}
			_type_table.push_back(t);
		}
		for (int i=0; i<dependents.size(); i++)
			dependents[i]->added(true);
	}

	virtual void add(STRING a, const CREAL _x, const CREAL _y, const CREAL _z)
	{
		add(a,lace::vector3d<CREAL>(_x,_y,_z));
	}

	virtual void erase(const int i)
	{
		for (int j=0; j<dependents.size(); j++)
			dependents[j]->erased(i,false);

		atm.erase(atm.begin()+i);
		crd.erase(crd.begin()+i);
		_shadow.erase(_shadow.begin()+i);
		if (update_types)
			_type_table.erase(_type_table.begin()+i);

		for (int j=0; j<dependents.size(); j++)
			dependents[j]->erased(i,true);
	}

	virtual void insert(int i, STRING a, const lace::vector3d<CREAL> &r)
	{
		for (int j=0; j<dependents.size(); j++)
			dependents[j]->inserted(i,false);

		atm.insert(atm.begin()+i,a);
		crd.insert(crd.begin()+i,r);
		_shadow.insert(_shadow.begin()+i,(char)false);
		if (update_types)
		{
			int t = type_of_atom(a);
			if (t == -1)
			{
				t = _atm_types.size();
				_atm_types.push_back(a);
				/*if (update_neighbours)
		{
		ngbr.resize_disttable();
		ngbr.build_disttable();
		}
		  */
			}
			_type_table.insert(_type_table.begin()+i,t);
		}
		for (int j=0; j<dependents.size(); j++)
			dependents[j]->inserted(i,true);
	}

	virtual void insert(int i, STRING a, const CREAL _x, const CREAL _y, const CREAL _z)
	{
		insert(i,a,lace::vector3d<CREAL>(_x,_y,_z));
	}

	void clear()
	{
		crd.clear();
		atm.clear();
		_shadow.clear();
		clear_type_table();
	}

	inline bool & shadow(int i)
	{
		return *((bool*)&_shadow[i]);
	}

};

/*
  template< int DIM, class CREAL=double >
  class geometry : public gen_geometry<DIM,CREAL,periodic_cell<DIM,CREAL> >{

  protected:
	using gen_geometry<DIM,CREAL,periodic_cell<DIM,CREAL> >::trnf;
	using gen_geometry<DIM,CREAL,periodic_cell<DIM,CREAL> >::crd;
	using gen_geometry<DIM,CREAL,periodic_cell<DIM,CREAL> >::_name;
	using gen_geometry<DIM,CREAL,periodic_cell<DIM,CREAL> >::atm;
	using gen_geometry<DIM,CREAL,periodic_cell<DIM,CREAL> >::_shadow;
	using gen_geometry<DIM,CREAL,periodic_cell<DIM,CREAL> >::geomtol;

  public:
	using gen_geometry<DIM,CREAL,periodic_cell<DIM,CREAL> >::nat;

	periodic_cell<DIM,CREAL> cell;

	geometry(const STRING & __name = "") : cell(),
					   gen_geometry<DIM,CREAL,periodic_cell<DIM,CREAL> >(cell, __name)
	{ trnf = & cell;}

	geometry(lace::vector3d<CREAL> v1, lace::vector3d<CREAL> v2=0e0,
		 lace::vector3d<CREAL> v3=0e0, const STRING &__name = "") : cell(v1,v2,v3),
									gen_geometry<DIM,CREAL,periodic_cell<DIM,CREAL> >(cell, __name)
	{
	  trnf = & cell;
	}

	geometry(const geometry<DIM,CREAL> & g) : cell(g.cell),
						  gen_geometry<DIM,CREAL,periodic_cell<DIM,CREAL> >(cell, g.name())
	{
	  atm = g.atm;
	  crd = g.crd;
	  _shadow = g._shadow;
	  geomtol = g.geomtol;
	}

	inline lace::vector3d<CREAL> cell_coord(int i1=0, int i2=0, int i3=0) const
	{
	  lace::vector3d<CREAL> r=0e0;
	  if (DIM>0)
	r += i1*cell(0);
	  if (DIM>1)
	r += i2*cell(1);
	  if (DIM>2)
	r += i3*cell(2);
	  return r;
	}

	void scale(CREAL s)
	{
	  for (int i=0; i<DIM; i++)
	cell(i) *= s;
	  for (int i=0; i<nat(); i++)
	crd[i] *= s;
	}

  };
  */

};

#endif
