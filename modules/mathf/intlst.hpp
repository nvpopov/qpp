#ifndef _QPP_INTLST
#define _QPP_INTLST

#include <vector>

// fixme - this file contains auxillary simple data structures and should be placed properly

namespace qpp{

  // --------------------------- Listers ----------------------------

  class integer_lister{
  protected:

    int n1, n2;
  public:

    virtual void set(int _n1, int _n2);

    virtual int begin() =0;

    virtual int next() =0;

    virtual bool end() =0;

    virtual integer_lister* copy() =0;

    virtual void free(){delete this;}

  };

  // ----------------------- Sequential lister -----------------------------------

  class trivial_integer_lister : public integer_lister{

    int i;
  public:

    virtual int begin();

    virtual int next();

    virtual bool end();

    virtual integer_lister* copy();

    virtual void free();

  };

  // ------------------------ Lister producing integers in random order -------------------

  class random_integer_lister : public integer_lister{

    std::vector<int> lst;
    int i;
  public:

    virtual void set(int _n1, int _n2);

    virtual int begin();

    virtual int next();

    virtual bool end();

    virtual integer_lister* copy();

    virtual void free();

  };

  // --------------------- This lister produces only one random integer from a given range -------------------

  class random_integer_selector : public integer_lister{

    bool done;

  public:

    virtual void set(int _n1, int _n2);

    virtual int begin();

    virtual int next();

    virtual bool end();

    virtual integer_lister* copy();

    virtual void free();
    
  };


  // Simple way to initialize random generator  
  void init_rand();

  //  ------------------------------------------------------------------------
  //                           Simple array of references
  //  ------------------------------------------------------------------------
  /*
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
  */
};

#endif
