#ifndef _QPP_QPPYTHON_H
#define _QPP_QPPYTHON_H

#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <vector>
#include <geom/lace3d.hpp>

using namespace boost::python;
namespace sn = boost::python::self_ns;

namespace qpp{

  void IndexError(const char *);
  void TypeError(const char *);
  void KeyError(const char *);
  void StopIter();

  // ----------------------------------------------

  template<class OWNER, class ELEM, class IDX,
	   ELEM (OWNER::*GET)(IDX), void (OWNER::*SET)(IDX, const ELEM &)>
  struct py_indexed_property{

    typedef py_indexed_property<OWNER,ELEM,IDX,GET,SET> SELF;

    OWNER * owner;

    py_indexed_property(){  owner = NULL;}
    py_indexed_property(OWNER * _owner){ owner = _owner;}
    void bind(OWNER * _owner){owner = _owner;}

    inline ELEM getitem(IDX i)
    { return ((*owner).*GET)(i); }

    inline void setitem(IDX i, const ELEM & e)
    { ((*owner).*SET)(i,e); }

    static void py_export(const char * pyname)
    {
      class_<SELF>(pyname)
	.def(init<>())
	.def(init<OWNER*>())
	.def("__getitem__", & SELF::getitem)
	.def("__setitem__", & SELF::setitem)
	;
    }

  }; 

  // ---------------------------------------------

  template<class OWNER, class ELEM, class ELEM2, class IDX,
	   ELEM (OWNER::*GET)(IDX), void (OWNER::*SET)(IDX, const ELEM &),
	   ELEM2 (OWNER::*GET2)(IDX,IDX), void (OWNER::*SET2)(IDX,IDX,const ELEM2 &)>
  struct py_2indexed_property : public py_indexed_property<OWNER,ELEM,IDX,GET,SET>
  {
    using  py_indexed_property<OWNER,ELEM,IDX,GET,SET>::owner;
    typedef py_2indexed_property<OWNER,ELEM,ELEM2,IDX,GET,SET,GET2,SET2> SELF2;

    inline ELEM2 getitem2(tuple I)
    {
      IDX i=extract<IDX>(I[0]), j=extract<IDX>(I[1]);
      return ((*owner).*GET2)(i,j);
    }

    inline void setitem2(tuple I, const ELEM2 & e)
    {
      IDX i=extract<IDX>(I[0]), j=extract<IDX>(I[1]);
      ((*owner).*SET2)(i,j,e);
    }

    static void py_2export(const char * pyname, bool only2 = false)
    {
      if (only2)
	class_<SELF2>(pyname)
	  .def(init<>())
	  .def(init<OWNER*>())
	  .def("__getitem__", & SELF2::getitem2)
	  .def("__setitem__", & SELF2::setitem2)
	  ;
      else
	class_<SELF2>(pyname)
	  .def(init<>())
	  .def(init<OWNER*>())
	  .def("__getitem__", & SELF2::getitem)
	  .def("__setitem__", & SELF2::setitem)
	  .def("__getitem__", & SELF2::getitem2)
	  .def("__setitem__", & SELF2::setitem2)
	  ;
    }

    py_2indexed_property(){ owner = NULL;}
    py_2indexed_property(OWNER * _owner, const char * pyname = "noname", bool only2 = false)
    { 
      py_2export(pyname,only2);
      owner = _owner;
    }

  };

  // ---------------------------------------------
  /*
  template <class T>
  struct py_array{

    std::vector<T> * vec;

    py_array(){ vec = NULL;}

    py_array(std::vector<T> & _vec){ vec = & _vec; }

    void set(std::vector<T> & _vec){ vec = & _vec; }

    inline T getitem(int i) const 
    {
      if (i<0)
	i+=vec->size();
      if (i<0 || i>=vec->size())
	IndexError("");

      return (*vec)[i];
    }

    inline void setitem(int i, const T & elem)
    { 
      if (i<0)
	i+=vec->size();
      if (i<0 || i>=vec->size())
	IndexError();

      (*vec)[i] = elem; 
    }

  };
  */
  //---------------------------------------
  /*
  template <class T>
  struct py_array_vector
  {
    std::vector<vector3d<T> > * vec;
        
    py_array_vector(){vec = NULL;}

    py_array_vector(std::vector<qpp::vector3d<T> > & _vec){vec = & _vec;}

    void set(std::vector<qpp::vector3d<T> > & _vec){ vec = & _vec; }

    inline qpp::vector3d<T> getitem(int i) const 
    {
      if (i<0)
	i+=vec->size();
      if (i<0 || i>=vec->size())
	IndexError();

      return (*vec)[i];
    }

    inline void setitem(int i, const qpp::vector3d<T> & elem)
    { 
      if (i<0)
	i+=vec->size();
      if (i<0 || i>=vec->size())
	IndexError();

      (*vec)[i] = elem; 
    }

    inline T getitem2(tuple I) const 
    { 
      int i=extract<int>(I[0]), j=extract<int>(I[1]);
      if (i<0)
	i+=vec->size();
      if (i<0 || i>=vec->size() || j<0 || j>=3)
	IndexError();

      return (*vec)[i](j);
    }
    
    inline void setitem2(tuple I, const T & a)
    {    
      int i=extract<int>(I[0]), j=extract<int>(I[1]);
      if (i<0)
	i+=vec->size();
      if (i<0 || i>=vec->size() || j<0 || j>=3)
	IndexError();

      (*vec)[i](j) = a;
    }

    inline void setitem3(int i, list & l)
    { 
      if (i<0)
	i+=vec->size();
      if (i<0 || i>=vec->size())
	IndexError();

      (*vec)[i] = qpp::vector3d<T>(l);
    }

    inline void setitem4(int i, tuple & l)
    { 
      if (i<0)
	i+=vec->size();
      if (i<0 || i>=vec->size())
	IndexError();

      (*vec)[i] = qpp::vector3d<T>(l);
    }

  };
  */
}

#endif
