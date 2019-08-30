#ifndef QPP_IO_WRITE_COORD
#define QPP_IO_WRITE_COORD

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <io/strfun.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/geom_anim.hpp>
#include <io/parsing_exceptions.hpp>

#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ios>
#include <algorithm>
#include <array>

namespace qpp {

  template< class REAL, class CELL >
  void write_raw_coord(std::basic_ostream<CHAR_EX,TRAITS>  & out,
                       qpp::geometry<REAL,CELL> & geom) {

    for (size_t i = 0; i < geom.nat(); i++)
      fmt::print(out,
                 "{:15.8f} {:15.8f} {:15.8f}\n",
                 geom.pos(i)[0],
                 geom.pos(i)[1],
                 geom.pos(i)[2]);
  }

  template< class REAL, class CELL >
  void write_atoms_with_coord(std::basic_ostream<CHAR_EX,TRAITS>  & out,
                                   qpp::geometry<REAL,CELL> & geom) {

    for (size_t i = 0; i < geom.nat(); i++)
      fmt::print(out,
                 "{} {:15.8f} {:15.8f} {:15.8f}\n",
                 geom.atom(i),
                 geom.pos(i)[0], geom.pos(i)[1], geom.pos(i)[2]);
  }

  template< class REAL, class CELL >
  void write_atoms_with_coord_and_chg(std::basic_ostream<CHAR_EX,TRAITS>  & out,
                                      qpp::geometry<REAL,CELL> & geom) {

    xgeometry<REAL, periodic_cell<REAL> > *xg = nullptr;
    if (geom.is_xgeometry()) xg = (xgeometry<REAL, periodic_cell<REAL> > *)(&geom);

    for (size_t i = 0; i < geom.nat(); i++)
      fmt::print(out,
                 "{} {:15.8f} {:15.8f} {:15.8f} {}\n",
                 geom.atom(i), geom.pos(i)[0], geom.pos(i)[1], geom.pos(i)[2],
                 xg ? xg->charge(i) : 0
          );
  }

}

#endif
