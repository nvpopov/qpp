#ifndef _QPPDATA_H
#define _QPPDATA_H

#include <vector>
#include <set>
#include <typeinfo>
#include <data/types.hpp>
#include <data/errors.hpp>

namespace qpp{

  // Really ugly implementation of variable data container,
  // but we don't want boost::variant neither boost::any!
  class datum{
    union{
      int    i;
      float  f;
      double d;
      bool   b;

      int    *pi;
      float  *pf;
      double *pd;
      bool   *pb;
      STRING *ps;
    };
    STRING s;
    basic_types tp;
    bool ptr;

  public:

    inline void set(int    _i) { i=_i; tp = type_int;    ptr=false;}
    inline void set(float  _f) { f=_f; tp = type_float;  ptr=false;}
    inline void set(double _d) { d=_d; tp = type_double; ptr=false;}
    inline void set(bool   _b) { b=_b; tp = type_bool;   ptr=false;}
    inline void set(const STRING &_s){ s=_s; tp = type_string; ptr=false; }
    inline void set(const char *_s)  { s=_s; tp = type_string; ptr=false; }
    	                       
    inline void set(int    *_i) { pi=_i; tp = type_int;    ptr=true;}
    inline void set(float  *_f) { pf=_f; tp = type_float;  ptr=true;}
    inline void set(double *_d) { pd=_d; tp = type_double; ptr=true;}
    inline void set(bool   *_b) { pb=_b; tp = type_bool;   ptr=true;}
    inline void set(STRING *_s) { ps=_s; tp = type_string; ptr=true;}
    
    inline basic_types type() const {return tp;}
    inline bool is_ref() const {return ptr;}
    
    template <class T>
    inline T get() const;

    template <class T>
    inline T& ref();

    inline int    & operator=(const int &v);
    inline float  & operator=(const float &v);
    inline double & operator=(const double &v);
    inline bool   & operator=(const bool &v);
    inline STRING & operator=(const STRING &v);
    inline STRING & operator=(const char * v);

    datum();

    datum( int    _i);
    datum( float  _f); 
    datum( double _d);
    datum( bool   _b) ;
    datum( const STRING & _s);
    datum( const char * _s);
	                      
    datum( int    *_i);
    datum( float  *_f);
    datum( double *_d);
    datum( bool   *_b);
    datum( STRING *_s);

    datum(const datum & v);
    /*
    template<class T>
    datum(T t)
    { set(t);}
    */

  };
  
  template<> int datum::get<int>() const;
  template<> float datum::get<float>() const;
  template<> double datum::get<double>() const;
  template<> bool datum::get<bool>() const;
  template<> STRING datum::get<STRING>() const;

  // -------------------------------------------------------------------

  template<> int& datum::ref<int>();
  template<> float& datum::ref<float>();
  template<> double& datum::ref<double>();
  template<> bool& datum::ref<bool>();
  template<> STRING& datum::ref<STRING>();

  inline int & datum::operator=(const int &v)
  {  set(v);    return ref<int>(); }
  
  inline float & datum::operator=(const float &v)
  {  set(v);    return ref<float>(); }
  
  inline double & datum::operator=(const double &v)
  {  set(v);    return ref<double>(); }
  
  inline bool & datum::operator=(const bool &v)
  {  set(v);    return ref<bool>(); }
  
  inline STRING & datum::operator=(const STRING &v)
  {  set(v);    return ref<STRING>(); }

  inline STRING & datum::operator=(const char * v)
  {  set(v);    return ref<STRING>(); }

  template<typename _CharT, class _Traits>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& __os, const datum &v)
  {
    std::basic_ostringstream<_CharT, _Traits> __s;
    __s.flags(__os.flags());
    __s.imbue(__os.getloc());
    __s.precision(__os.precision());
    
    switch (v.type()){
      case type_bool:   __s << (v.get<bool>() ? "true" : "false"); break;
      case type_int:    __s << v.get<int>(); break;
      case type_float:  __s << v.get<float>(); break;
      case type_double: __s << v.get<double>(); break;
      case type_string: __s << v.get<STRING>(); break;
      }

    return __os << __s.str();
  }

};

#endif
