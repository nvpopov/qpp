#ifndef QPP_IO_ADME_EWALD
#define QPP_IO_ADME_EWALD
#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <io/strfun.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/ngbr.hpp>
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
    void write_adme_ewald_uc(std::basic_ostream<CHAR_EX,TRAITS>  & out,
                             qpp::geometry<REAL,CELL> & geom) {

        xgeometry<REAL, periodic_cell<REAL> > *xg = nullptr;
        if (geom.is_xgeometry()) xg = (xgeometry<REAL, periodic_cell<REAL> > *)(&geom);

        for (size_t i = 0; i < 3; i++)
            fmt::print(out, "{:15.8f} {:15.8f} {:15.8f} 6 \n",
                       geom.cell.v[i][0], geom.cell.v[i][1], geom.cell.v[i][2]);

        for (size_t i = 0; i < geom.nat(); i++) {

                vector3<REAL> frac_c = geom.cell.cart2frac(geom.pos(i));

                fmt::print(out,
                           "{:15.8f} {:15.8f} {:15.8f} {:15.8f} {}\n",
                           frac_c[0], frac_c[1], frac_c[2],
                           xg ? xg->charge(i) : 0,
                           geom.atom(i)
                        );

            }
    }

}

#endif
