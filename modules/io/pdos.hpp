#ifndef QPP_IO_PDOS
#define QPP_IO_PDOS

#include <vector>
#include <array>
#include <qm/misc.hpp>
#include <Eigen/Eigen>
#include <unsupported/Eigen/MatrixFunctions>

namespace qpp {

  template<class REAL>
  struct pdos_data_t {

      std::string m_specie_name{"X"};
      size_t m_atom_kind{0};
      size_t m_spin_subspace{0};
      bool m_spin_polarized{false};
      bool m_is_alpha{false};
      bool m_is_beta{false};
      REAL m_efermi{0};
      REAL m_scale{1};

      size_t m_occ_start{0};
      size_t m_occ_end{0};
      size_t m_unocc_start{0};
      size_t m_unocc_end{0};

      // Max angular momentum in the data
      qm_l m_max_l{qm_l::qm_l_s};

      // [0] - m.o eigenvalue, [1] - occupancy [n] - angular momentum
      std::vector<Eigen::Array<REAL, 1, Eigen::Dynamic>> m_data;
      //std::vector<qm_m_l> m_labels;

      REAL get_energy_ev(size_t mo_index) {
        if (mo_index < m_data.size() && m_data[mo_index].cols() >= 2)
          return m_data[mo_index](0);
        else return 0;
      }

      REAL get_occ(size_t mo_index) {
        if (mo_index < m_data.size() && m_data[mo_index].cols() >= 2)
          return m_data[mo_index](1);
        else return 0;
      }

  }; // pdos_data_t

} // namespace qpp

#endif
