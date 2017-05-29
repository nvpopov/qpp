#ifndef _QPP_SYMM_H
#define _QPP_SYMM_H

#include <symm/index.hpp>
#include <vector>

#ifdef PY_EXPORT
#include <boost/python.hpp>
namespace bp = boost::python;
#endif

namespace qpp{
  
  template <class TRANSFORM>
  class generators_pack{
  public:
    
    std::vector<TRANSFORM> generators;
    index begin, end;
    int DIM;
    
    generators_pack(int dim=0)
    {
      DIM=dim;
    }

    generators_pack(const std::vector<TRANSFORM> & g, 
		     const index & __begin, const index & __end)
    {
      DIM = g.size();
      generators.resize(DIM);
      int d=0;
      for (const TRANSFORM & t : g)
	generators[d++]=t; 
      begin = __begin;
      end   = __end;
    }

    generators_pack(const std::vector<TRANSFORM> & g)
    {
      DIM = g.size();
      generators.resize(DIM);

      int d=0;
      for (const TRANSFORM & t : g)
	generators[d++]=t; 

      begin = index::D(DIM);
      end   = index::D(DIM);
    }
    
    generators_pack(const generators_pack<TRANSFORM> & G) :
      DIM(G.DIM), generators(G.generators), begin(G.begin), end(G.end)
    {}

    int get_dim(){return DIM;}

    void set_dim(int D)
    {
      DIM = D;
      generators.resize(DIM);
      
      begin = index::D(DIM);
      end   = index::D(DIM);
    }

    TRANSFORM operator()(const index & n) const
    {
      if (DIM==0)
	return TRANSFORM::unity;

      TRANSFORM A = pow(generators[0],n(0));
      for (int d = 1; d<DIM; d++)
	A = A*pow(generators[d],n(d));
      return A;
    }

    template <class ARRAY>
    void generate(ARRAY & group)
    {
      for (iterator n(begin, end); !n.end(); n++)
	group.push_back((*this)(n));
    }

    void auto_order(int d)
    {
      begin(d) = 0;
      const TRANSFORM & g = generators[d];
      TRANSFORM a = g;
      int n=1;
      while (a != TRANSFORM::unity)
	{
	  a = a*g;
	  n++;
	}
      end(d) = n-1;
    }

    void auto_orders()
    {      
      for (int d=0; d<DIM; d++)
	auto_order(d);
    }
    
  };

  // ------------------------------------------------------------------------
  /*
#ifdef PY_EXPORT

  template<class TRANSFORM> class generated_group;

  template <class TRANSFORM>
  int py_group_len(const generated_group<TRANSFORM> & G)
  {
    return G.size();
  }

#endif
  */
  // ------------------------------------------------------------------------

  template<class TRANSFORM>
  class generated_group{
  public:
    
    std::vector<TRANSFORM> group;

    int index(const TRANSFORM & g)
    {
      int i;
      bool result=false;
      for (i=0; i<group.size(); i++)
	if ( group[i] == g )
	  {
	    result = true;
	    break;
	  }
      return result? i : -1;
    }

    generated_group(TRANSFORM E = TRANSFORM::unity)
    {
      group.push_back(E);
    }

    generated_group(const generated_group<TRANSFORM> & G):
      group(G.group)
    {}

    inline TRANSFORM & operator[](int i)
    { return group[i]; }

    inline TRANSFORM operator[](int i) const
    { return group[i]; }

    inline int size() const
    { return group.size(); }

    void add(const TRANSFORM & g)
    {
      if ( index(g) >= 0 )
	return;
      int inew = size();
      group.push_back(g);

      while (inew < size())
	{
	  //std::cout << size() << "\n";

	  int inewest = size();
	  for (int ig1 = 0; ig1 < inewest; ig1++)
	    for (int ig2 = inew; ig2 < inewest; ig2++)
	      {
		//std::cout << "ig1= " << ig1 << " ig2= " << ig2 << "\n";

		TRANSFORM h1 = group[ig1]*group[ig2];
		
		//std::cout << "h1= " << h1 << "\n";

		if (index(h1)==-1)
		  group.push_back(h1);
		TRANSFORM h2 = group[ig2]*group[ig1];

		//std::cout << "h2= " << h2 << "\n";

		if (h2 != h1 && index(h2)==-1)
		  group.push_back(h2);
	      } 
	  //std::cout << inew << " " << inewest << "\n";

	  inew = inewest;
	}
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      // fixme
    }

#ifdef PY_EXPORT

    inline TRANSFORM py_getitem(int i)
    {
      if (i<0) 
	i += size();
      if (i<0 || i>=size())
	IndexError("cell: index out of range");
      return group[i]; 
    }

    inline void py_setitem(int i, const TRANSFORM & t)
    {
      if (i<0) 
	i += size();
      if (i<0 || i>=size())
	IndexError("cell: index out of range"); 
      group[i] = t;
    }

    static void py_export(const char * pyname)
    {
      bp::class_<generated_group<TRANSFORM> >(pyname,bp::init< bp::optional<TRANSFORM> >())
	.def(bp::init<const generated_group<TRANSFORM> &>())
	.def("index", & generated_group<TRANSFORM>::index )
	.def("add",   & generated_group<TRANSFORM>::add )
	.def("__getitem__",  & generated_group<TRANSFORM>::py_getitem)
	.def("__setitem__",  & generated_group<TRANSFORM>::py_setitem)
	.def("__len__", & generated_group<TRANSFORM>::size)
	;
      // bp::def("len", py_group_len<TRANSFORM>);
    }

#endif
    
  };
  
};

#endif
