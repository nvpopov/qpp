#ifndef _QPP_INDEX_H
#define _QPP_INDEX_H

#include <ostream>
#include <sstream>
#include <initializer_list>
#include <stdexcept>
#include <geom/lace3d.hpp>
#include <data/errors.hpp>

#ifdef PY_EXPORT
#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python.hpp>
#include <python/qppython.hpp>

namespace bp = boost::python;
namespace sn = boost::python::self_ns;

#endif

namespace qpp{
  
  // ------------------- index class ----------------------
  // Index is a general purpose complex index, having DIM
  // integer components
  // It is presumed that DIM > 0
  class index{
    int *idx;
    bool del;

  public:
    int DIM;

    inline operator int() const {return idx[0];}

    inline int operator()(int d) const {return idx[d];} 

    inline int& operator()(int d) {return idx[d];} 

    inline index& operator=(int _i)
    {
      idx[0] = _i;
      for (int d=1; d<DIM; d++)
	idx[d] = 0;
      return *this;
    }

    inline index& operator=(const index & I)
    {      
      if (DIM != I.DIM)
	{
	  if (del)
	    delete idx;
	  DIM = I.DIM;
	  idx = new int[DIM];
	  del = true;
	}

      for (int d=0; d<DIM; d++)
	idx[d] = I(d);
      return *this;
    }

    inline void set(const index & I)
    {
      *this = I;
    }

    inline index operator+(const index & I)
    {
      index res = D(DIM);
      for (int d=0; d<DIM; d++)
	res(d) = idx[d] + I(d);
      return res;
    }
    
    inline index operator-(const index & I)
    {
      index res = D(DIM);
      for (int d=0; d<DIM; d++)
	res(d) = idx[d] - I(d);
      return res;
    }
    
    inline index& operator+=(const index & I)
    {
      for (int d=0; d<DIM; d++)
	idx[d] = idx[d] + I(d);
      return *this;
    }

    inline index& operator-=(const index & I)
    {
      for (int d=0; d<DIM; d++)
	idx[d] = idx[d] - I(d);
      return *this;
    }

    inline void set(const std::initializer_list<int> &li)
    {
      if (li.size() != DIM)
	throw std::range_error("Wrong number of index components");
      int d=0;
      for (int i : li)
	idx[d++] = i;
    }

    /*
    index(int dim)
    { 
      DIM = dim;
      idx = new int[DIM];
      del = true;
    }
    */

    index()
    {
      DIM = 0;
      idx=NULL;
      del = false;
    }
    
    /*
    index(int i)
    {
      DIM=1;
      idx = new int;
      del = true;
      *idx = i;
    }
    */

    index(const index & I)
    {
      DIM = I.DIM;
      idx = new int[DIM];
      for (int d=0; d<DIM; d++)
	idx[d] = I(d);
      del = true;
    }

    index(const index & I, int d1, int d2 = -1)
    {
      if (d2==-1) 
	d2 = I.DIM-1;
      DIM = d2-d1+1;
      idx = & I.idx[d1];
      del = false;
    }

    index(const std::initializer_list<int> &li)
    {
      DIM = li.size();
      idx = new int[DIM];
      set(li);
      del = true;
    }

    ~index()
    {
      if (del)
	delete idx;
    }

    inline index sub(int d1, int d2 = -1) const
    {
      return index(*this,d1,d2);
    }

    inline bool operator==(const index &I) const
    {
      bool res = DIM == I.DIM;
      if (res)
	for (int d=0; d<DIM; d++)
	  if (idx[d]!=I(d))
	    {
	      res = false;
	      break;
	    }
      return res;
    }

    inline bool operator!=(const index &I) const
    {
      return ! ((*this)==I);
    }

    struct factory{
      int DIM;

      factory(int dim){DIM=dim;}

      index all(int a)
      {
	index t;
	t.DIM = DIM;
	t.del = true;
	t.idx = new int[DIM];

	for (int d=0; d<DIM; d++)
	  t(d) = a;
	return t;
      }

      index atom(int a)
      {
	index t = all(0);
	t(0)=a;
	return t;
      }

      operator index(){return all(0);} 

    };

    static factory D(int dim)
    {
      return factory(dim);
    }
      
#ifdef PY_EXPORT

    // --------------- PYTHON -------------------------------

    int py_getitem(int d) const
    {
      return idx[d];
    }
    
    void py_setitem(int d, int v)
    {
      idx[d] = v;
    }

    inline index sub1(int d1)
    {
      return sub(d1);
    }    

    index(const bp::list &l)
    {
      // Assuming that type checks have been performed inside python code
      DIM = bp::len(l);
      idx = new int[DIM];
      for (int d=0; d<DIM; d++)
	idx[d] = bp::extract<int>(l[d]);
      del = true;
    }

    index(const bp::tuple &l)
    {
      // Assuming that type checks have been performed inside python code
      DIM = bp::len(l);
      idx = new int[DIM];
      for (int d=0; d<DIM; d++)
	idx[d] = bp::extract<int>(l[d]);
      del = true;
    }

    static void py_export(const char * pyname)
    {
      bp::class_<index >(pyname,bp::init<>())
	.def(bp::init<bp::list&>())
	.def(bp::init<bp::tuple&>())
	.def(bp::init<index const&>())
	.def(bp::init<index const&, int, bp::optional<int> >())
	//.def(bp::init<int>())	
	.def("__getitem__",&index::py_getitem)
	.def("__setitem__",&index::py_setitem)
	.def("sub",  &index::sub)
	.def("sub",  &index::sub1)
	.def(sn::str(sn::self))
	.def(sn::repr(sn::self))
	.def(sn::self + sn::self)
	.def(sn::self - sn::self)
	.def(sn::self == sn::self)
	.def(sn::self != sn::self)
	;
    }
    
#endif

  };

  // ------------------------------------------------------

  template<typename _CharT, class _Traits>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& __os, const index &I)
  {
    std::basic_ostringstream<_CharT, _Traits> __s;
    __s.flags(__os.flags());
    __s.imbue(__os.getloc());
    __s.precision(__os.precision());
    
    if (I.DIM > 0)
      {
	__s  << "(" << I(0);
	for (int d=1; d<I.DIM; d++)
	  __s << "," << I(d);
	__s << ")";
      }
    else
      __s << "()";
    return __os << __s.str();
  }

  index atom_index(int at, const index & I);
    
  // ------------------- iterator class --------------------
  // Iterator allows you run through all (or some) atoms of this cell
  // and of surrounding cells
    
  class iterator : public index{
    
  protected:
    index a, b;
    bool _end;
    // a - from
    // b - to
    
    //using index::idx;
     
    inline void inc()
    {
      if (DIM==0)
	{
	  _end = true;
	  return;
	}

      int d = 0;

      while (++(*this)(d) > b(d))
	{
	  (*this)(d)=a(d);
	  if (++d >= DIM) 
	    {
	      _end = true;
	      break;
	    }
	}
    }
    
  public:

    iterator(const index & _a, const index & _b) :
      index(_a), a(_a), b(_b)
    {
      _end = false;   
    }
    
    inline void reset()
    {
      _end = false;
      set(a);
    }

    iterator & operator++(int)
    {
      inc();
      return *this;
    }

    inline bool end(){return _end;}
    
#ifdef PY_EXPORT

    // --------------- PYTHON -------------------------------

    index py_next()
    {
      if (end())
	StopIter();
      index res = *this;
      inc();
      return res;
    }

    static void py_export(const char * pyname)
    {
      bp::class_<iterator>(pyname,bp::init<const index&, const index&>())
	.def(bp::init<bp::list,bp::list>())
	.def(bp::init<bp::tuple,bp::tuple>())
	.def("next", & iterator::py_next)
	;
    }    

#endif

  };

#ifdef PY_EXPORT

  class index_range{

    index a,b;

  public:
    index_range(const index & _a, const index & _b) :
      a(_a), b(_b) {}

    index_range(const bp::list & l1, const bp::list & l2) :
      a(l1), b(l2){}

    index_range(const bp::tuple & l1, const bp::tuple & l2) :
      a(l1), b(l2) {}

    iterator  __iter__()
    { return iterator(a,b); }

    static void py_export(const char * pyname)
    {
      bp::class_<index_range>(pyname,bp::init<const index&, const index&>())
	.def(bp::init<const bp::list&, const bp::list&>())
	.def(bp::init<const bp::tuple&, const bp::tuple&>())
	.def("__iter__", & index_range::__iter__)
	;
    }

  };

#endif

}

#endif
