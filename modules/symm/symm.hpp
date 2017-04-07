#ifndef _QPP_SYMM_H
#define _QPP_SYMM_H

#include <symm/index.hpp>
#include <vector>

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
      TRANSFORM A = TRANSFORM::unity;
      for (int d = 0; d<DIM; d++)
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

  template<class TRANSFORM>
  class generated_group{
  public:
    
    std::vector<TRANSFORM> group;

    int idx(const TRANSFORM & g)
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

    generated_group()
    {
      group.push_back(TRANSFORM::unity);
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
      if ( idx(g) == -1 )
	{
	  group.push_back(g);
	  bool contin = true;
	  while (contin)
	    {
	      contin = false;
	      for (int i=0; i<group.size(); i++)
		for (int j=0; j<group.size(); j++)
		  {
		    TRANSFORM h = group[i]*group[j];
		    if (idx(h)==-1)
		      {
			contin = true;
			group.push_back(h);
		      }
		  }
	    }
	}
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      // fixme
    }
    
  };
  
};

#endif
