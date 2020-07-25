#include "data.hpp"

namespace qpp{

template<> int datum::get<int>() const {
  if (tp != basic_types::type_int) TypeError("Type mismatch in datum conversion to int");
  if (ptr) return *pi;
  else return i;
}

template<> float datum::get<float>() const {
  if (tp == basic_types::type_float){
    if (ptr) return *pf;
    else return f;
  }
  else if (tp == basic_types::type_double) {
    if (ptr) return *pd;
    else return d;
  }
  else
    throw std::invalid_argument("Type mismatch in datum conversion to float");
}

template<> double datum::get<double>() const {
  if (tp == basic_types::type_float){
    if (ptr) return *pf;
    else return f;
  }
  else if (tp == basic_types::type_double){
    if (ptr) return *pd;
    else return d;
  }
  else
    throw std::invalid_argument("Type mismatch in datum conversion to double");
}

template<> bool datum::get<bool>() const {
  if (tp != basic_types::type_bool)
    throw std::invalid_argument("Type mismatch in datum conversion to bool");
  if (ptr) return *pb;
  else return b;
}

template<> STRING_EX datum::get<STRING_EX>() const {
  if (tp != basic_types::type_string)
    throw std::invalid_argument("Type mismatch in datum conversion to STRING");
  if (ptr) return *ps;
  else return s;
}

// -------------------------------------------------------------------

template<> int& datum::ref<int>() {
  if (tp != basic_types::type_int)
    throw std::invalid_argument("Type mismatch in datum conversion to int");
  if (ptr) return *pi;
  else return i;
}

template<> float& datum::ref<float>() {
  if (tp != basic_types::type_float)
    throw std::invalid_argument("Type mismatch in datum conversion to float");
  if (ptr) return *pf;
  else return f;
}

template<> double& datum::ref<double>() {
  if (tp != basic_types::type_double)
    throw std::invalid_argument("Type mismatch in datum conversion to double");
  if (ptr) return *pd;
  else return d;
}

template<> bool& datum::ref<bool>() {
  if (tp != basic_types::type_bool)
    throw std::invalid_argument("Type mismatch in datum conversion to bool");
  if (ptr) return *pb;
  else return b;
}

template<> STRING_EX& datum::ref<STRING_EX>() {
  if (tp != basic_types::type_string)
    throw std::invalid_argument("Type mismatch in datum conversion to STRING");
  if (ptr) return *ps;
  else return s;
}

datum::datum() {
  tp = basic_types::type_bool; ptr = false; b = false;
}

datum::datum( int    _i){set(_i);}
datum::datum( float  _f){set(_f);}
datum::datum( double _d){set(_d);}
datum::datum( bool   _b){set(_b);}
datum::datum( const STRING_EX & _s){set(_s);}
datum::datum( const char * _s){set(_s);}

datum::datum( int    *_i){set(_i);}
datum::datum( float  *_f){set(_f);}
datum::datum( double *_d){set(_d);}
datum::datum( bool   *_b){set(_b);}
datum::datum( STRING_EX *_s){set(_s);}

datum::datum(const datum & v) {
  ptr = v.ptr;
  tp = v.tp;
  if (!ptr)
    switch(tp){
     case basic_types::type_bool:   b = v.b; break;
     case basic_types::type_int:    i = v.i; break;
     case basic_types::type_float:  f = v.f; break;
     case basic_types::type_double: d = v.d; break;
     case basic_types::type_string: s = v.s; break;
     default: break;
    }
  else
    switch(tp){
     case basic_types::type_bool:   pb = v.pb; break;
     case basic_types::type_int:    pi = v.pi; break;
     case basic_types::type_float:  pf = v.pf; break;
     case basic_types::type_double: pd = v.pd; break;
     case basic_types::type_string: ps = v.ps; break;
     default: break;
    }
}

};
