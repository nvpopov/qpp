#include "mathf/intlst.hpp"
#include <stdlib.h>
#include <time.h>
#include <vector>

namespace qpp{

  void integer_lister::set(int _n1, int _n2)
  {
    n1 = _n1;
    n2 = _n2;
  }

  // ----------------------------------------------------------

  int trivial_integer_lister::begin()
  {
    return i=n1;
  }

  int trivial_integer_lister::next()
  {
    return ++i;
  }

  bool trivial_integer_lister::end()
  {
    return i>n2;
  }

  integer_lister* trivial_integer_lister::copy()
  {
    return new trivial_integer_lister;
  }

  void trivial_integer_lister::free(){delete this;}

  // ------------------------ Lister producing integers in random order -------------------

 
  void random_integer_lister::set(int _n1, int _n2)
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

  int random_integer_lister::begin()
  {
    i=0;
    return lst.size()>0 ? lst[0] : n1; 
  }

  int random_integer_lister::next()
  {
    return lst[++i];
  }

  bool random_integer_lister::end()
  {
    return i>=lst.size();
  }

  integer_lister* random_integer_lister::copy()
  {
    return new random_integer_lister;
  }

  void random_integer_lister::free(){delete this;}

  // --------------------- This lister produces only one random integer from a given range -------------------

  void random_integer_selector::set(int _n1, int _n2)
  {
    n1 = _n1;
    n2 = _n2;
    done = false;
  }

  int random_integer_selector::begin()
  {
    done = false;
    return n1 + rand() % (n2-n1+1);
  }

  int random_integer_selector::next()
  {
    done = true;
  }

  bool random_integer_selector::end()
  {
    return done;
  }

  integer_lister* random_integer_selector::copy()
  {
    return new random_integer_selector;
  }

  void random_integer_selector::free(){delete this;}

  // Simple way to initialize random generator  
  void init_rand()
  {
    srand(time(NULL));
  }

};

