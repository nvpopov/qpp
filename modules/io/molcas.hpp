#ifndef QPP_MOLCAS_IO
#define QPP_MOLCAS_IO

#include <iostream>
#include <vector>
#include <fstream>
#include <io/cube.hpp>

namespace qpp {

  template<class REAL, class CELL>
  void load_grid_ascii(std::basic_istream<CHAR_EX,TRAITS> & inp,
                       geometry<REAL, CELL> &geom,
                       std::vector<scalar_volume_t<REAL>> &volumes) {
    std::locale loc1("C");
    std::string s;
    std::vector<std::string_view> splt;

    std::getline(inp, s); // read 0
    std::getline(inp, s); //read empty line

    int natom = -1;
    bool first_section_ended = false;
    //read params and geometry

    std::getline(inp, s); //read Natom= X
    splt = split_sv(s, " ");
    natom = std::stoi(splt[1].data());

    //read atoms
    for (size_t i = 0; i < natom; i++) {
        std::getline(inp, s);
        splt = split_sv(s, " ");
        std::string an = std::string(splt[0]);
        an.erase(remove_if(an.begin(), an.end(),[](char c){return !isalpha(c);}), an.end());
        REAL x = std::stod(splt[1].data());
        REAL y = std::stod(splt[2].data());
        REAL z = std::stod(splt[3].data());
        geom.add(an, x, y, z);
        fmt::print(std::cout, "DEBUG MGRID ATOM {} {} {} {}\n", an, x, y, z);
      }

    //    Typical control block for gv
    //    VERSION=     1.01
    //    N_of_MO=            104
    //    N_of_Grids=          18
    //    N_of_Points=     226981
    //    Block_Size=       18432
    //    N_Blocks=            13
    //    Is_cutoff=            0
    //    CutOff=          2.5000
    //    N_P=             226981
    //    N_INDEX=         0   27    0    3    0   74    0
    //    Net=            60   60   60
    //    Origin=      -15.000     -15.000     -15.000
    //    Axis_1=       30.000       0.000       0.000
    //    Axis_2=        0.000      30.000       0.000
    //    Axis_3=        0.000       0.000      30.000

    //read version
    std::getline(inp, s); splt = split_sv(s, " ");
    std::string version = std::string(splt[1]);

    //read N_of_MO=
    std::getline(inp, s); splt = split_sv(s, " ");
    int n_of_mo = std::stoi(splt[1].data());

    //read N_of_grids
    std::getline(inp, s); splt = split_sv(s, " ");
    int n_of_grids = std::stoi(splt[1].data());

    //read N_of_points
    std::getline(inp, s); splt = split_sv(s, " ");
    int n_of_points = std::stoi(splt[1].data());

    //read Block_Size
    std::getline(inp, s); splt = split_sv(s, " ");
    int block_size = std::stoi(splt[1].data());

    //read n_Blocks
    std::getline(inp, s); splt = split_sv(s, " ");
    int n_blocks = std::stoi(splt[1].data());

    //read Is_cutoff
    std::getline(inp, s); splt = split_sv(s, " ");
    int is_cutoff = std::stoi(splt[1].data());

    //read CutOff
    std::getline(inp, s); splt = split_sv(s, " ");
    REAL cutoff = std::stod(splt[1].data());

    //read N_P
    std::getline(inp, s); splt = split_sv(s, " ");
    int n_p = std::stoi(splt[1].data());

    //read N_INDEX
    std::getline(inp, s); splt = split_sv(s, " ");

    //read net
    std::getline(inp, s); splt = split_sv(s, " ");
    REAL net_0 = std::stoi(splt[1].data());
    REAL net_1 = std::stoi(splt[2].data());
    REAL net_2 = std::stoi(splt[3].data());

    //read origin
    std::getline(inp, s); splt = split_sv(s, " ");
    REAL org_x = std::stod(splt[1].data());
    REAL org_y = std::stod(splt[2].data());
    REAL org_z = std::stod(splt[3].data());

    //read axis 0
    std::getline(inp, s); splt = split_sv(s, " ");
    REAL ax0_x = std::stod(splt[1].data());
    REAL ax0_y = std::stod(splt[2].data());
    REAL ax0_z = std::stod(splt[3].data());

    //read axis 1
    std::getline(inp, s); splt = split_sv(s, " ");
    REAL ax1_x = std::stod(splt[1].data());
    REAL ax1_y = std::stod(splt[2].data());
    REAL ax1_z = std::stod(splt[3].data());

    //read axis 2
    std::getline(inp, s); splt = split_sv(s, " ");
    REAL ax2_x = std::stod(splt[1].data());
    REAL ax2_y = std::stod(splt[2].data());
    REAL ax2_z = std::stod(splt[3].data());

    std::vector<std::string> grid_names;
    grid_names.resize(n_of_grids);
    volumes.resize(n_of_grids);

    for (size_t i = 0; i < n_of_grids; i++) {
        std::getline(inp, s); splt = split_sv(s, "=");
        volumes[i].m_name = std::string(splt[1]);
      }

    //prepare volume data
    for (auto &volume : volumes) {

        volume.m_field.resize(n_of_points);
        volume.m_offset = vector3<REAL>{org_x, org_y, org_z};
        volume.m_axis[0] = (vector3<REAL>{ax0_x, ax0_y, ax0_z} / net_0);
        volume.m_axis[1] = (vector3<REAL>{ax1_x, ax1_y, ax1_z} / net_1);
        volume.m_axis[2] = (vector3<REAL>{ax2_x, ax2_y, ax2_z} / net_2);
        volume.m_steps[0] = net_0;
        volume.m_steps[1] = net_1;
        volume.m_steps[2] = net_2;
        volume.m_addr_mode = 0;
      }

    size_t current_grid = -1;
    REAL v0;

    std::vector<size_t> ix;
    ix.resize(volumes.size());

    std::vector<size_t> iy;
    iy.resize(volumes.size());

    std::vector<size_t> iz;
    iz.resize(volumes.size());

    while(std::getline(inp, s)) {

        splt = split_sv(s, " ");

        if (splt.size() >= 2) { //change grid

            if (s.find("Title=") == std::string::npos)
              break;

            current_grid += 1;

            if (current_grid >= n_of_grids)
              current_grid = 0;

          } else {

            // emit point
            v0 = std::stod(s); //read value

            volumes[current_grid].m_field[iz[current_grid]*net_2*net_1 +
                iy[current_grid]*net_2 + ix[current_grid]] = v0;

            ix[current_grid]++;

            if (ix[current_grid] == net_0) {
                ix[current_grid] = 0;
                iy[current_grid]++;
              }

            if (iy[current_grid] == net_1) {
                iy[current_grid] = 0;
                iz[current_grid]++;
              }

            if (v0 < -0.01) volumes[current_grid].m_has_negative_values = true;

          }

      }

    fmt::print(std::cout, "DEBUG MGRID Natom={}\n", natom);
    fmt::print(std::cout, "DEBUG MGRID Version={}\n", version);
    fmt::print(std::cout, "DEBUG MGRID N_of_MO={}\n", n_of_mo);
    fmt::print(std::cout, "DEBUG MGRID N_of_Grids={}\n", n_of_grids);
    fmt::print(std::cout, "DEBUG MGRID N_of_Points={}\n", n_of_points);
    fmt::print(std::cout, "DEBUG MGRID Blocks={}\n", n_blocks);
    fmt::print(std::cout, "DEBUG MGRID Blocks_size={}\n", block_size);
    fmt::print(std::cout, "DEBUG MGRID Net={} {} {}\n", net_0, net_1, net_2);
    fmt::print(std::cout, "DEBUG MGRID Origin={} {} {}\n", org_x, org_y, org_z);
    fmt::print(std::cout, "DEBUG MGRID ax0={} {} {}\n", ax0_x, ax0_y, ax0_z);
    fmt::print(std::cout, "DEBUG MGRID ax1={} {} {}\n", ax1_x, ax1_y, ax1_z);
    fmt::print(std::cout, "DEBUG MGRID ax2={} {} {}\n", ax2_x, ax2_y, ax2_z);

    for (size_t i = 0 ; i < n_of_grids; i++)
      fmt::print(std::cout, "DEBUG MGRID GRID NAME[{}] {}\n", i, grid_names[i]);

  } // load_grid_ascii

} // namespace qpp

#endif
