#ifndef QPP_GENERAL_QC_OUTPUT_H
#define QPP_GENERAL_QC_OUTPUT_H

#include <vector>

namespace qpp {

    enum qc_prgr_run_t {
      rt_unknown,
      rt_energy,
      rt_grad,
      rt_geo_opt,
      rt_md,
      rt_vib,
      rt_tddft,
      rt_spectrum
    };

    template <class REAL>
    struct qc_prgr_scf_step_info{
            int iter{0};
            int ex{0};
            int dem{0};
            REAL total_energy{REAL(0)};
            REAL e_change{REAL(0)};
            REAL d_change{REAL(0)};
            REAL orb_grad{REAL(0)};
    };

    template <class REAL>
    struct qc_prgr_step_t {
        std::vector<qc_prgr_scf_step_info<REAL> > scf_steps;
        REAL total_energy{REAL(0)};
    };

    template <class REAL>
    struct qc_program_output {
            int tot_num_atoms{0};
            int tot_num_electrons{0};
            REAL tot_charge{0};
            int mult{0};
            bool is_unrestricted{false};
            int n_alpha{0};
            int n_beta{0};
            qc_prgr_run_t run_t{qc_prgr_run_t::rt_unknown};
            std::vector<qc_prgr_step_t<REAL> > steps;
    };


}

#endif
