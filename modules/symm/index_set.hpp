#ifndef QPP_INDEX_SET
#define QPP_INDEX_SET
#include <symm/index.hpp>

namespace qpp {

  struct atom_index_set_key {
      int m_atm;
      index m_idx;
      atom_index_set_key(const int atm, const index idx) {
        m_atm = atm; m_idx = idx;
      }

      atom_index_set_key(const atom_index_set_key & other) {
        m_atm = other.m_atm; m_idx = other.m_idx;
      }

      atom_index_set_key() {

      }

      bool operator==(const atom_index_set_key &other) const {
        return ( m_atm == other.m_atm && m_idx == other.m_idx);
      }
  };

  struct atom_index_set_key_compare {
      bool operator() (const atom_index_set_key &a,
                       const atom_index_set_key &b) const{
       if (a.m_atm > b.m_atm) return true;
       else if (a.m_idx > b.m_idx) return true;
       else return false;
      }
  };

  struct atom_index_set_key_hash{
    std::size_t operator()(const atom_index_set_key& k) const{
      std::size_t res = k.m_atm * int(pow(3, k.m_idx.DIM));
      for(uint8_t i = 0; i < k.m_idx.DIM; i++)
        //map -1,0,1 -> 1,2,3
        res += k.m_idx(i)*int(pow(3, k.m_idx.DIM-i-1));
      res += int(pow(3, k.m_idx.DIM)) / 2;
      return res;
    }
  };
}

#endif
