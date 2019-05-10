#ifndef QPP_IO_PDOS
#define QPP_IO_PDOS

#include <vector>
#include <array>
#include <qm/misc.hpp>
#include <Eigen/Eigen>

namespace qpp {

  template<class REAL>
  struct pdos_data_t {
      /* energy occ m_l_0 m_l_1 ... m_l_n*/
      size_t m_atom_kind{0};
      size_t m_spin_subspace{0};
      Eigen::Matrix<REAL, Eigen::Dynamic, Eigen::Dynamic> m_data;
  }; // pdos_data_t

} // namespace qpp

#endif
