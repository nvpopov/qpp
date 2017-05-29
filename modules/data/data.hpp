#ifndef _QPPDATA_H
#define _QPPDATA_H

#include <vector>
#include <typeinfo>
#include <data/types.hpp>

namespace qpp{

  class datum{
    basic_types tp;
    void *ptr;
    bool del;
  public:

    datum(const STRING & s)
    {
      del = true;
      tp = type_string;
      ptr = new STRING(s);
      //std::cout << "string datum created\n";
    }

    datum(const char * s)
    {
      del = true;
      tp = type_string;
      ptr = new STRING(s);
      //std::cout << "string datum created\n";
    }

    datum(int i)
    {
      del = true;
      tp = type_int;
      ptr = new int(i);
      //std::cout << "int datum created\n";
    }

    datum(float f)
    {
      del = true;
      tp = type_float;
      ptr = new float(f);
    }

    datum(double d)
    {
      del = true;
      tp = type_double;
      ptr = new double(d);
    }

    datum(bool b)
    {
      del = true;
      tp = type_bool;
      ptr = new bool(b);
    }

    datum(STRING *s)
    {
      del = false;
      tp = type_string;
      ptr = s;
    }

    datum(int *i)
    {
      del = false;
      tp = type_int;
      ptr = i;
    }

    datum(float *f)
    {
      del = false;
      tp = type_float;
      ptr = f;
    }

    datum(double *d)
    {
      del = false;
      tp = type_double;
      ptr = d;
    }

    datum(bool *b)
    {
      del = false;
      tp = type_bool;
      ptr = b;
    }


    template<class T>
    T substance() const
    {
      bool type_error;
      switch(tp)
	{
	case type_int:    type_error = typeid(T)!=typeid(int);    break;
	case type_float:  type_error = typeid(T)!=typeid(float);  break;
	case type_double: type_error = typeid(T)!=typeid(double); break;
	case type_bool:   type_error = typeid(T)!=typeid(bool);   break;
	case type_string: type_error = typeid(T)!=typeid(STRING); break;
	default: type_error = true;
	}
      if (type_error)
	{}//Make error

      std::cout << "extract " << typeid(T).name() << " error= " << type_error << "\n";
      return *((T*)ptr);      
    }

    template<class T>
    T & substance()
    {
      bool type_error;
      switch(tp)
	{
	case type_int:    type_error = typeid(T)!=typeid(int);    break;
	case type_float:  type_error = typeid(T)!=typeid(float);  break;
	case type_double: type_error = typeid(T)!=typeid(double); break;
	case type_bool:   type_error = typeid(T)!=typeid(bool);   break;
	case type_string: type_error = typeid(T)!=typeid(STRING); break;
	default: type_error = true;
	}
      if (type_error)
	{}//Make error
      return *((T*)ptr);      
    }

    basic_types type(){return tp;}

    ~datum()
    {
      if (del)
      switch(tp)
	{
	case type_int:    delete (int*)ptr;     break;
	case type_float:  delete (float*)ptr;   break;
	case type_double: delete (double*)ptr;  break; 
	case type_bool:   delete (bool*)ptr;    break; 
	case type_string: delete (STRING*)ptr;  break;
	}
    }

  };

};

#endif
