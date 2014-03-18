#ifndef _QPP_INTLST
#define _QPP_INTLST

// fixme - this file contains auxillary simple data structures and should be placed properly


#include <stdlib.h>
#include <time.h>

namespace qpp{

  // --------------------------- Listers ----------------------------

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
      return i>n2;
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
      return lst.size()>0 ? lst[0] : n1; 
    }

    virtual int next()
    {
      return lst[++i];
    }

    virtual bool end()
    {
      return i>=lst.size();
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
      return done;
    }

    virtual integer_lister* copy()
    {
      return new random_integer_selector;
    }

    virtual void free(){delete this;}
    
  };
  
  void init_rand()
  {
    srand(time(NULL));
  }

  //  ------------------------------------------------------------------------
  //                           Simple array of references
  //  ------------------------------------------------------------------------

  template<class T>
  class refarray{
    
    std::vector<T*> p;
    
  public:
    
    inline void add_ref(T &x)
    { p.push_back(&x); }
    
    inline void add(const T &x)
    {
      T *y = new T;
      *y = x;
      p.push_back(y); 
    }
    
    inline void put_ref(int i, T &x)
    { p[i] = &x;}
    
    inline void erase_ref(int i)
    { p.erase(p.begin()+i);}
    
    inline void erase(int i)
    { 
      delete p[i];
      p.erase(p.begin()+i);
    }
    
    inline void insert_ref(int i, T &x)
    { p.insert(p.begin()+i,&x);}
    
    inline void insert(int i, const T &x)
    {
      T *y = new T;
      *y = x;
      p.insert(p.begin()+i,y);
    }
    
    inline T& operator()(int i)
    { return *p[i];}
    
    inline int size()
    {return p.size();}
    
    inline void resize(int n)
    { p.resize(n);}

    std::vector<T*> & data()
    { return p;}
    
  };

};

#endif
