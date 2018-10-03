#ifndef QPP_SYMMETRIC_INT_H
#define QPP_SYMMETRIC_INT_H
#include <iterator>

//TODO: rework to hash and unordered map
namespace qpp {

  template <typename TYPE>

  struct sym_key{

    TYPE m_a;
    TYPE m_b;

    bool operator==(const sym_key<TYPE>& other) const{
      return (( m_a == other.m_a && m_b == other.m_b) ||
              ( m_b == other.m_a && m_a == other.m_b));
    }

    sym_key(const TYPE _a, const TYPE _b){
      m_a = _a;
      m_b = _b;
    }
  };

  template<typename TYPE>

  struct sym_key_hash{

    std::size_t operator()(const sym_key<TYPE>& k) const{
      std::size_t res = 17;
      res = res * 31 + std::hash<TYPE>()( std::min(k.m_a, k.m_b) );
      res = res * 31 + std::hash<TYPE>()( std::max(k.m_a, k.m_b) );
      return res;
    }

  };

}
#endif
