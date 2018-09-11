#ifndef _QPP_SYMMETRIC_INT_H
#define _QPP_SYMMETRIC_INT_H
#include <iterator>

//TODO: rework to hash and unordered map
namespace qpp {
  template <typename TYPE>
  struct sym_key{
    TYPE a;
    TYPE b;

    bool operator==(const sym_key<TYPE>& other) const{
      return ((( a == other.a) && (b == other.b)) ||
              (( b == other.a) && (a == other.b)));
    }

    sym_key(const TYPE _a, const TYPE _b){
      a = _a;
      b = _b;
    }
  };

  template<typename TYPE>
  struct sym_key_hash{
    std::size_t operator()(const sym_key<TYPE>& k) const{
      std::size_t res = 17;
      res = res * 31 + std::hash<TYPE>()( std::min(k.a, k.b) );
      res = res * 31 + std::hash<TYPE>()( std::max(k.a, k.b) );
      return res;
    }
  };

}
#endif
