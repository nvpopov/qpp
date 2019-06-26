#ifndef QPP_QM_MISC
#define QPP_QM_MISC

namespace qpp {

  enum qm_l : int {
    qm_l_s = 0,
    qm_l_p,
    qm_l_d,
    qm_l_f,
    qm_l_g,
    qm_l_h
  };

  /* projection of angular momentum */
  enum qm_m_l : int {
    qm_m_l_s = 0,
    qm_m_l_py,
    qm_m_l_pz,
    qm_m_l_px,
    qm_m_l_d_2,
    qm_m_l_d_1,
    qm_m_l_d0,
    qm_m_l_d1,
    qm_m_l_d2,
    qm_m_l_f_3,
    qm_m_l_f_2,
    qm_m_l_f_1,
    qm_m_l_f0,
    qm_m_l_f1,
    qm_m_l_f2,
    qm_m_l_f3,
    qm_m_l_g_4,
    qm_m_l_g_3,
    qm_m_l_g_2,
    qm_m_l_g_1,
    qm_m_l_g0,
    qm_m_l_g1,
    qm_m_l_g2,
    qm_m_l_g3,
    qm_m_l_g4,
    MAX_SUPPORTED
  };

} // namespace qpp

#endif
