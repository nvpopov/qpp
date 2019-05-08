#ifndef QPP_QM_MISC
#define QPP_QM_MISC

namespace qpp {

    /* projection of angular momentum */
    enum qm_m_l : int {
        s = 0,
        py,
        pz,
        px,
        d_2,
        d_1,
        d0,
        d1,
        d2,
        f_3,
        f_2,
        f_1,
        f0,
        f1,
        f2,
        f3,
        g_4,
        g_3,
        g_2,
        g_1,
        g0,
        g1,
        g2,
        g3,
        g4,
        MAX_SUPPORTED
    };

} // namespace qpp

#endif
