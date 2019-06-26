#ifndef QPP_CP2K_IO_NATIVE
#define QPP_CP2K_IO_NATIVE

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <io/strfun.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/ngbr.hpp>

#include <vector>
#include <array>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ios>
#include <algorithm>

namespace qpp {

  template<class REAL, class CELL = periodic_cell<REAL> >
  void write_cp2k_coord_section (std::basic_ostream<CHAR_EX,TRAITS> &out, geometry<REAL, CELL> &geom) {

//  Reference:
//    &CELL
//     A AX AY AZ
//     B BX BY BZ
//     C CX CY CZ
//     PERIODIC XYZ
//    &END CELL
//    &COORD
//    X    1.8946037594202060E+01    1.6099953511998024E+01    1.9360306949254490E+01
//     &END COORD

    out << "&CELL\n";
    std::array<const char*, 3> cell_descr{"A", "B", "C"};

    for (auto i = 0; i < 3; i++)
    out << fmt::format("{} {:16.8f} {:16.8f} {:16.8f}", cell_descr[i], geom.cell.v[i][0],
        geom.cell.v[i][1], geom.cell.v[i][2]) << "\n";

    out << "PERIODIC XYZ\n";
    out << "&END CELL\n";
    out << "&COORD\n";

    for (auto i = 0; i < geom.nat(); i++)
      out << fmt::format("{:5} {:16.8f} {:16.8f} {:16.8f}", geom.atom(i),
                         geom.pos(i)[0], geom.pos(i)[1], geom.pos(i)[2]) << "\n";
    out << "&END COORD\n";

  }

}

#endif
