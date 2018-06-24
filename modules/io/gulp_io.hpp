#ifndef _QPP_GULP_IO_NATIVE
#define _QPP_GULP_IO_NATIVE

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <io/strfun.hpp>

//#include <lace/lace3d.hpp>
//#include <lace/lace.hpp>
//#include <symm/symm.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/ngbr.hpp>
//#include <geom/geom_extras.hpp>
//#include <geom/molecule.hpp>

#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ios>
#include <algorithm>

namespace qpp{

  template<class REAL, class CELL = periodic_cell<REAL> >
  void read_gulp_simple_input(
      std::basic_istream<CHAR,TRAITS> & inp,
      geometry<REAL,CELL> & geom){
    STRING s;

    bool bParseGeometry = false;
    bool bLineChecked = false;
    bool bFinishParsing = false;

    short int iSavedARecordSize = -1;
    short int iCoordStartIdx = -1;

    while((std::getline(inp, s)) || (bFinishParsing)){
        STRING lower_s = tolower(s);
        bLineChecked = false;

        if ((lower_s.find("vectors") != std::string::npos) && (!bLineChecked)){
            for (int i = 0; i<3; i++){
                std::getline(inp, s);
                qpp::vector3d<REAL> cellv = vec_from_string<REAL>(s);
                geom.cell.v[i] = cellv;
              }
            bLineChecked = true;
          }

        if ((lower_s.find("frac") != std::string::npos) && (!bLineChecked)){
            bParseGeometry = true;
            bLineChecked = true;
            geom.frac = true;
          }

        if ((bParseGeometry) && (!bLineChecked)){
            std::vector<STRING> geom_l = split(s);
            if (iSavedARecordSize == -1) iSavedARecordSize = geom_l.size();
            if (iSavedARecordSize != -1)
              if (iSavedARecordSize == geom_l.size()) {
                  //Determine coordinate index
                  if ((geom_l[1].find("core") != std::string::npos) ||
                      (geom_l[1].find("shell") != std::string::npos))
                    iCoordStartIdx = 2;
                  else iCoordStartIdx = 1;
                  geom.add(geom_l[0], vec_from_string<REAL>(s,
                                                            iCoordStartIdx,
                                                            iCoordStartIdx+1,
                                                            iCoordStartIdx+2));
                } else bParseGeometry = false;
            bLineChecked = true;
          }
      }
  }

  template<class REAL, class CELL = periodic_cell<REAL> >
  void write_gulp_simple_input(std::basic_ostream<CHAR,TRAITS>  & out,
                               geometry<REAL, CELL> & geom){
    out << "opti prop conp relax" << std::endl;
    out << "vectors" << std::endl;
    for (int i = 0; i < 3; i++)
      out <<
             fmt::format("{:16.8f} {:16.8f} {:16.8f}",
                         geom.cell.v[i][0],
          geom.cell.v[i][1],
          geom.cell.v[i][2]) << std::endl;
    out << "frac" << std::endl;
    for (int q = 0; q < geom.nat(); q++ )
      std::cout << fmt::format("{} {} {} {} {} {}",
                               geom.atom(q),
                               "core",
                               2.0,
                               geom.pos(q)[0],
                               geom.pos(q)[1],
                               geom.pos(q)[2]) << std::endl;
  }
}

#endif
