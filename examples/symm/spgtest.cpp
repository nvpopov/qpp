#include <fmt/format.h>
#include <iostream>
#include <symm/index.hpp>

#include <ctime>
#include <cmath>
#include <symm/spgw.hpp>
#include <geom/geom.hpp>


int main()
{
    qpp::periodic_cell<double> cell({4,0,0},{0,4,0},{0,0,4});
    qpp::geometry<double,qpp::periodic_cell<double>> g(cell);
    g.add("Fe", 0.0, 0.0, 0.0);
    g.add("Fe", 0.5, 0.5, 0.5);
    g.build_type_table();

    qpp::periodic_cell<double> cell2({4,2,0},{0,4,0},{0,0,4});
    qpp::geometry<double,qpp::periodic_cell<double>> g2(cell2);

    int numpa = spgw_standartize_cell(g,g2);
    /*
    std::cout<<fmt::format("num_primitive_atoms = {}\n",numpa);

    for(int i=0; i<3; i++)
        std::cout<<fmt::format("{} {} {}\n",
                               g2.cell->v[i].x(),
                               g2.cell->v[i].y(),
                               g2.cell->v[i].z());
    for(int i=0; i<g2.nat(); i++)
        std::cout<<fmt::format("{} {} {} {}\n",
                               g2.type_table(i),
                               g2.coord(i).x(),
                               g2.coord(i).y(),
                               g2.coord(i).z());
    std::cout<<spgw_get_international(g)<<std::endl;*/


    //Test CaF2 symmetry
    qpp::periodic_cell<double> CaF2_cell({2.689,-2.689,0},
                                         {-2.689,0.0,-2.689},
                                         {2.689,2.689,0});
    qpp::geometry<double,qpp::periodic_cell<double>> CaF2_g(CaF2_cell);
    CaF2_g.add("Ca", 0.0, 0.0, 0.0);
    CaF2_g.add("F", 0.75, 0.5, 0.25);
    CaF2_g.add("F", 0.25, 0.5, 0.75);
    CaF2_g.build_type_table();

    std::cout<<fmt::format("CaF2 international symmetry = {}\n" \
                           "CaF2 schoenflies symmetry = {} \n",
                           spgw_get_international(CaF2_g),
                           spgw_get_schoenflies(CaF2_g));

    //Test NaCl symmetry
    qpp::periodic_cell<double> NaCl_cell({0.00000000,2.82028000,2.82028000},
                                         {2.82028000,0.00000000,2.82028000},
                                         {2.82028000,2.82028000,0.00000000});
    qpp::geometry<double,qpp::periodic_cell<double>> NaCl_g(NaCl_cell);
    NaCl_g.add("Na", 0.0, 0.0, 0.0);
    NaCl_g.add("Cl", 0.5, 0.5, 0.5);
    NaCl_g.build_type_table();

    std::cout<<fmt::format("NaCl international symmetry = {}\n" \
                           "NaCl schoenflies symmetry = {} \n",
                           spgw_get_international(NaCl_g),
                           spgw_get_schoenflies(NaCl_g));


}
