#ifndef QPP_IO_PARSING_EXCEPTIONS
#define QPP_IO_PARSING_EXCEPTIONS

#include <stdexcept>
#include <string>
#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>

namespace qpp {

  template<typename _CharT, typename _Traits, typename _Alloc>
  std::basic_istream<_CharT, _Traits>&
  sgetline(std::basic_istream<_CharT, _Traits>& __is,
           std::basic_string<_CharT, _Traits, _Alloc>& __str,
           uint64_t &line_number) {
    line_number++;
    return std::getline(__is, __str);
  };

  class generic_parsing_error_t : public std::exception {

    public:

      std::string m_exception_src;
      std::string m_exception_msg;
      uint64_t m_line_num{0};

      generic_parsing_error_t(uint64_t _line_num) :
        m_line_num(_line_num), m_exception_src("SRC UNDEFINED"), m_exception_msg("UNKNOWN") {};

      generic_parsing_error_t(uint64_t _line_num,
                              const std::string _e_src) :
        m_line_num(_line_num), m_exception_src(_e_src), m_exception_msg("UNKNOWN") {};

      generic_parsing_error_t(uint64_t _line_num,
                              const std::string _e_src,
                              const std::string _e_msg) :
        m_line_num(_line_num), m_exception_src(_e_src), m_exception_msg(_e_msg) {};

  };

}

#endif
