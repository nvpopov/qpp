#ifndef QPP_IO_PARSING_EXCEPTIONS
#define QPP_IO_PARSING_EXCEPTIONS

#include <stdexcept>
#include <string>
#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <geom/lace3d.hpp>
#include <io/strfun.hpp>

namespace qpp {

  template<typename _CharT, typename _Traits, typename _Alloc>
  std::basic_istream<_CharT, _Traits>&
  sgetline(std::basic_istream<_CharT, _Traits>& __is,
           std::basic_string<_CharT, _Traits, _Alloc>& __str,
           uint64_t &line_number) {
    line_number++;
    return std::getline(__is, __str);
  };

  enum pe_type : int {
    unknown,
    conv_float,
    conv_int,
    spl_min_sz,
    spl_max_sz
  };

  class parsing_error_t : public std::exception {

    public:

      std::string m_exception_src;
      std::string m_exception_msg;
      uint64_t m_line_num{0};
      pe_type m_error_type{pe_type::unknown};
      int m_error_pos{0};
      int m_sv_size{0};
      int m_sv_extr{0};

      parsing_error_t(uint64_t _line_num) :
        m_line_num(_line_num),
        m_exception_src("SRC UNDEFINED"),
        m_exception_msg("UNKNOWN") { compose_message(); };

      parsing_error_t(uint64_t _line_num,
                      const std::string _e_src) :
        m_line_num(_line_num),
        m_exception_src(_e_src),
        m_exception_msg("UNKNOWN") { compose_message(); };

      parsing_error_t(uint64_t _line_num,
                      const std::string _e_src,
                      const std::string _e_msg) :
        m_line_num(_line_num),
        m_exception_src(_e_src),
        m_exception_msg(_e_msg) { compose_message(); };

      parsing_error_t(uint64_t _line_num,
                      const std::string _e_src,
                      const pe_type _error_type,
                      const int _error_pos) :
        m_line_num(_line_num),
        m_exception_src(_e_src),
        m_error_type(_error_type),
        m_error_pos(_error_pos) { compose_message(); };

      parsing_error_t(uint64_t _line_num,
                      const std::string _e_src,
                      const pe_type _error_type,
                      const int _sv_size,
                      const int _sv_extr) :
        m_line_num(_line_num),
        m_exception_src(_e_src),
        m_error_type(_error_type),
        m_sv_size(_sv_size),
        m_sv_extr(_sv_extr) { compose_message(); };

      void compose_message() {

        switch (m_error_type) {

          case pe_type::unknown : {
              break;
            }

          case pe_type::conv_float : {
              m_exception_msg = fmt::format("Error while trying convert to float in pos {}",
                                            m_error_pos);
              break;
            }

          case pe_type::conv_int : {
              m_exception_msg = fmt::format("Error while trying convert to int in pos {}",
                                            m_error_pos);
              break;
            }

          case pe_type::spl_min_sz : {
              m_exception_msg = fmt::format("Required min el. idx = {}, sv.size() = {}",
                                            m_error_pos, m_sv_size);
              break;
            }

          case pe_type::spl_max_sz : {
              m_exception_msg = fmt::format("Required max el. idx = {}, sv.size() = {}",
                                            m_error_pos, m_sv_size);
              break;
            }

          }
      }

  };

  template<typename REAL = float, typename STR>
  REAL str2real(std::vector<std::string_view> &splt,
                const int index,
                const uint64_t &cur_line,
                const STR &s) {
    try {
      return std::stod(splt[index].data());
    } catch (const std::out_of_range& oor) {
      throw parsing_error_t(cur_line, s, pe_type::spl_min_sz, splt.size(), index);
    } catch (const std::invalid_argument& iarg) {
      throw parsing_error_t(cur_line, s, pe_type::conv_float, index);
    }

  }

  template<typename INT = int, typename STR>
  INT str2int(std::vector<std::string_view> &splt,
              const int index,
              const uint64_t &cur_line,
              const STR &s) {
    try {
      return std::stoi(splt[index].data());
    } catch (const std::out_of_range& oor) {
      throw parsing_error_t(cur_line, s, pe_type::spl_min_sz, splt.size(), index);
    } catch (const std::invalid_argument& iarg) {
      throw parsing_error_t(cur_line, s, pe_type::conv_int, index);
    }

  }

  template<typename INT = int, typename STR>
  INT str2int(
      const uint64_t &cur_line,
      const STR &s) {
    try {
      return std::stoi(s);
    } catch (const std::invalid_argument& iarg) {
      throw parsing_error_t(cur_line, s, pe_type::conv_int, 0);
    }

  }

  template<typename STR>
  void check_min_split_size(std::vector<std::string_view> &splt,
                            const int min_req,
                            const uint64_t &cur_line,
                            const STR &s) {
    if (splt.size() < min_req)
      throw parsing_error_t(cur_line, s, pe_type::spl_min_sz, splt.size(), min_req);
  }

  template<class REAL>
  qpp::vector3<REAL> vec_from_str_ex(STRING_EX &_inst,
                                     const uint64_t &cur_line,
                                     int idx = 0,
                                     int idy = 1,
                                     int idz = 2 ) {
    std::vector<std::string_view> vfs_l = split_sv(_inst);
    check_min_split_size(vfs_l, 3, cur_line, _inst);
    REAL vx, vy, vz = 0.0;
    vx = str2real(vfs_l, idx, cur_line, _inst);
    vy = str2real(vfs_l, idy, cur_line, _inst);
    vz = str2real(vfs_l, idz, cur_line, _inst);
    return qpp::vector3<REAL>(vx, vy, vz);
  }

  template<class REAL>
  qpp::vector3<REAL> vec_from_str_ex(STRING_EX &_inst,
                                     std::vector<std::string_view> &splt,
                                     const uint64_t &cur_line,
                                     int idx = 0,
                                     int idy = 1,
                                     int idz = 2 ) {
    check_min_split_size(splt, std::max(idx, std::max(idy, idz)) + 1, cur_line, _inst);
    REAL vx, vy, vz = 0.0;
    vx = str2real(splt, idx, cur_line, _inst);
    vy = str2real(splt, idy, cur_line, _inst);
    vz = str2real(splt, idz, cur_line, _inst);
    return qpp::vector3<REAL>(vx, vy, vz);
  }

}

#endif
