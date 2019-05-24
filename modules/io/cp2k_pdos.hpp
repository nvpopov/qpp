#ifndef QPP_IO_CP2K_PDOS
#define QPP_IO_CP2K_PDOS

#include <io/pdos.hpp>
#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <io/strfun.hpp>
#include <io/parsing_exceptions.hpp>

namespace qpp {

  template<class REAL>
  void read_cp2k_pdos(
      STRING_EX &file_name,
      std::basic_istream<CHAR_EX,TRAITS> &inp,
      pdos_data_t<REAL> &data) {

    std::locale loc1("C");
    std::string s;
    uint64_t cur_line{0};

    // analyze file name
    // looks like pdos_Ce-ALPHA_k2-1.pdos
    bool is_alpha = file_name.find("ALPHA") != std::string::npos;
    bool is_beta = file_name.find("BETA") != std::string::npos;

    data.m_is_alpha = is_alpha;
    data.m_is_beta = is_beta;

    //extract kind
    auto kind_pos_start = file_name.find("_k");
    auto kind_pos_end = file_name.find("-", kind_pos_start);
    auto kind_substr = file_name.substr(kind_pos_start + 2,
                                       kind_pos_end - (kind_pos_start + 2));

    //fmt::print("{} {} kind = {}\n", kind_pos_start, kind_pos_end, kind_substr);

    if (kind_pos_start != std::string::npos &&
        kind_pos_end != std::string::npos &&
        !kind_substr.empty()) {
          data.m_atom_kind = std::stoi(kind_substr);
      }

    // read first line
    // # Projected DOS for atomic kind <ATOM> at iteration step i = <ITER>, E(Fermi) = <EFERMI> a.u.
    // 0 1         2   3   4      5    6      7  8         9   10 11 12      13      14  15     16
    sgetline(inp, s, cur_line);
    //extract specie label
    std::vector<std::string_view> splt = split_sv(s, " ");
    data.m_specie_name = std::string(splt[6]);

    data.m_efermi = str2real(splt, 15, cur_line, s) * hartree_to_ev;

    // read second line
    //# MO Eigenvalue [a.u.] Occupation s py pz  px  d-2..2 f-3..3 g-4..4
    //0 1  2          3      4          5 6  7   8   9   ...
    sgetline(inp, s, cur_line);
    // Determine max angular momentum
    if (s.find("px") != std::string::npos) data.m_max_l = qm_l::qm_l_p;
    if (s.find("d-2") != std::string::npos) data.m_max_l = qm_l::qm_l_d;
    if (s.find("f-3") != std::string::npos) data.m_max_l = qm_l::qm_l_f;
    if (s.find("g-4") != std::string::npos) data.m_max_l = qm_l::qm_l_g;

    // process data
    int max_line_c = -1;
    while (!inp.eof()) {

        sgetline(inp, s, cur_line);
        std::vector<std::string_view> splt = split_sv(s, " ");
        max_line_c = std::max<int>(max_line_c, splt.size());

        if (max_line_c != splt.size()) continue;
        Eigen::Array<REAL, 1, Eigen::Dynamic> pdos_rec;
        pdos_rec.resize(Eigen::NoChange, splt.size()-1);

        // i = 0 is m.o. index,
        // we don't keep the m.o. index because they're already in the vector.
        for (size_t i = 1; i < splt.size(); i++) {
            REAL value = str2real(splt, i, cur_line, s);
            if (i == 1) value *= hartree_to_ev; // i-1 = 0 is energy, transform from a.u. to eV
            pdos_rec(i-1) = value;
          }

        data.m_data.push_back(std::move(pdos_rec));

      } // end of while

  }

} // namespace qpp

#endif
