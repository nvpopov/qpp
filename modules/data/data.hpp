#ifndef QPPDATA_H
#define QPPDATA_H

#include <vector>
#include <set>
#include <typeinfo>
#include <data/types.hpp>
#include <data/errors.hpp>

namespace qpp {

  // simple and dirty table
  template <class ITEM>
  class static_table {

      int N,M;
      ITEM * tbl;
      //std::vector<std::vector<ITEM> > tbl;

      inline int idx(int i, int j) const {
        return i*N+j;
      }

    public:

      void resize(int _N, int _M) {

        N = _N;
        M = _M;

        //        if (tbl != nullptr)
        //
        delete [] tbl;

        if (N*M>0)
          tbl = new ITEM[N*M];
        else
          tbl = nullptr;
      }

      static_table(int _N, int _M) {
        N = _N;
        M = _M;
        if (N*M>0)
          tbl = new ITEM[N*M];
        else
          tbl = nullptr;
      }

      static_table(){
        N = M = 0;
        tbl = nullptr;
      }

      static_table(const static_table<ITEM> & T) {
        N = T.N;
        M = T.M;
        if (T.tbl == nullptr)
          tbl = nullptr;
        else {
            tbl = new ITEM[N*M];
            for (int i=0; i<N*M; i++)
              tbl[i] = T.tbl[i];
          }
      }

      inline int size(int d) const{
        if (d==0) return N;
        else if (d==1) return M;
        else throw std::range_error("Illegal dimension in static_table");
      }

      inline ITEM operator()(int i, int j) const{
        if (i<0) i+=N;
        if (i<0 || i>=N) throw std::range_error("Index 0 out of range in static_table");
        if (j<0) j+=M;
        if (j<0 || j>=M) throw std::range_error("Index 1 out of range in static_table");
        return tbl[idx(i,j)];
      }

      inline ITEM & operator()(int i, int j) {
        if (i<0) i+=N;
        if (i<0 || i>=N) throw std::range_error("Index 0 out of range in static_table");
        if (j<0) j+=M;
        if (j<0 || j>=M) throw std::range_error("Index 1 out of range in static_table");
        return tbl[idx(i,j)];
      }

      ~static_table(){
        //        if (tbl != nullptr)
        //          delete [] tbl;
        delete [] tbl;
      }

  };

  /*
   */
  template<class T, class INT>
  void reorder(std::vector<T> & data, std::vector<INT> & idx) {
    std::vector<INT> ridx(idx.size());
    for (INT i=0; i<idx.size(); i++)
      ridx[idx[i]] = i;
    bool done;
    do {
        done = true;
        for (INT i=0; i<idx.size(); i++)
          if (ridx[i]!=i){
              INT j = ridx[i];
              std::swap(data[i],data[j]);
              std::swap(ridx[i],ridx[j]);
              done = false;
            }
      } while (!done);
  }

  // ----------------------------------------------------------------------------------------
  // Class Bool to use std::vector<Bool> instead of std::vector<bool>

  class Bool{
    private:
      bool m_value;
    public:

      Bool(): m_value(){}
      Bool( bool value ) : m_value(value){}
      inline operator bool() const { return m_value;}
      inline operator bool&() { return m_value;}

  };

  // Really ugly implementation of variable data container,
  // but we don't want boost::variant neither boost::any!
  class datum {

      union {
          int    i;
          float  f;
          double d;
          bool   b;

          int    *pi;
          float  *pf;
          double *pd;
          bool   *pb;
          STRING_EX *ps;
      };

      STRING_EX s;
      basic_types tp;
      bool ptr;

    public:

      inline void set(int    _i) { i=_i; tp = type_int;    ptr=false;}
      inline void set(float  _f) { f=_f; tp = type_float;  ptr=false;}
      inline void set(double _d) { d=_d; tp = type_double; ptr=false;}
      inline void set(bool   _b) { b=_b; tp = type_bool;   ptr=false;}
      inline void set(const STRING_EX &_s){ s=_s; tp = type_string; ptr=false; }
      inline void set(const char *_s)  { s=_s; tp = type_string; ptr=false; }

      inline void set(int    *_i) { pi=_i; tp = type_int;    ptr=true;}
      inline void set(float  *_f) { pf=_f; tp = type_float;  ptr=true;}
      inline void set(double *_d) { pd=_d; tp = type_double; ptr=true;}
      inline void set(bool   *_b) { pb=_b; tp = type_bool;   ptr=true;}
      inline void set(STRING_EX *_s) { ps=_s; tp = type_string; ptr=true;}

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
      inline STRING_EX & operator=(const STRING_EX &v);
      inline STRING_EX & operator=(const char * v);

      datum();

      datum( int    _i);
      datum( float  _f);
      datum( double _d);
      datum( bool   _b) ;
      datum( const STRING_EX & _s);
      datum( const char * _s);

      datum( int    *_i);
      datum( float  *_f);
      datum( double *_d);
      datum( bool   *_b);
      datum( STRING_EX *_s);

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
  template<> STRING_EX datum::get<STRING_EX>() const;

  // -------------------------------------------------------------------

  template<> int& datum::ref<int>();
  template<> float& datum::ref<float>();
  template<> double& datum::ref<double>();
  template<> bool& datum::ref<bool>();
  template<> STRING_EX& datum::ref<STRING_EX>();

  inline int & datum::operator=(const int &v)
  {  set(v);    return ref<int>(); }

  inline float & datum::operator=(const float &v)
  {  set(v);    return ref<float>(); }

  inline double & datum::operator=(const double &v)
  {  set(v);    return ref<double>(); }

  inline bool & datum::operator=(const bool &v)
  {  set(v);    return ref<bool>(); }

  inline STRING_EX & datum::operator=(const STRING_EX &v)
  {  set(v);    return ref<STRING_EX>(); }

  inline STRING_EX & datum::operator=(const char * v)
  {  set(v);    return ref<STRING_EX>(); }

  template<typename _CharT, class _Traits>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& __os, const datum &v) {
    std::basic_ostringstream<_CharT, _Traits> __s;
    __s.flags(__os.flags());
    __s.imbue(__os.getloc());
    __s.precision(__os.precision());

    switch (v.type()) {
      case type_bool:   __s << (v.get<bool>() ? "true" : "false"); break;
      case type_int:    __s << v.get<int>(); break;
      case type_float:  __s << v.get<float>(); break;
      case type_double: __s << v.get<double>(); break;
      case type_string: __s << v.get<STRING_EX>(); break;
      default: break;
      }

    return __os << __s.str();
  }

};

#endif
