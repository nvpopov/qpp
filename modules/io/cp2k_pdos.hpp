#ifndef QPP_IO_CP2K_PDOS
#define QPP_IO_CP2K_PDOS

#include <io/pdos.hpp>
#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <io/strfun.hpp>

namespace qpp {

    template<class REAL>
    void read_cp2k_pdos(
            std::basic_istream<CHAR_EX,TRAITS> & inp,
            pdos_data_t<REAL> &data) {

    }

} // namespace qpp

#endif
