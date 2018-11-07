#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <geom/lace3d.hpp>
#include <io/firefly.hpp>
#include <fstream>

using namespace qpp;
using v3f = vector3<float>;
using v3d = vector3<double>;
using m3f = matrix3<float>;
using m3d = matrix3<double>;
using pd  = std::pair<double, double>;

TEST_CASE( "Computational chemistry data parsing : PC Gamess Firefly" ) {

  SECTION ("Parsing results of single-point calculations[PC Gamess Firefly]") {

    std::ifstream isec("../examples/io/ref_data/firefly/dvb_sp.out");
    comp_chem_program_data_t<double> cc_o;
    read_ccd_from_firefly_output(isec, cc_o);
    REQUIRE( cc_o.tot_num_electrons == 70) ;
    REQUIRE( cc_o.tot_charge == Approx(0)) ;
    REQUIRE( cc_o.DIM == 0 );
    REQUIRE( cc_o.mult == 1 );
    REQUIRE( cc_o.n_alpha == 35 );
    REQUIRE( cc_o.n_beta == 35 );
    REQUIRE( cc_o.tot_num_atoms == 20);
    REQUIRE( cc_o.run_t == comp_chem_program_run_t::energy);
    REQUIRE( cc_o.steps.back().scf_steps.size() == 9);
    REQUIRE( cc_o.steps.back().scf_steps.front().total_energy == Approx(-379.453243734));
    REQUIRE( cc_o.steps.back().scf_steps.back().total_energy == Approx(-379.777955008));
    REQUIRE( cc_o.steps.back().eigen_values.front() == Approx(-11.0409) );
    REQUIRE( cc_o.steps.back().eigen_values.back() == Approx(1.1646) );
    REQUIRE( cc_o.init_pos.size() == 20);
    REQUIRE( cc_o.init_atom_names.size() == 20);
    REQUIRE( cc_o.init_pos[0] == v3d(2.6342558126*bohr_to_angs, -0.4183391645*bohr_to_angs, 0.000) );
    REQUIRE( cc_o.steps.back().mulliken_pop_per_atom.front().first == Approx(5.997223) );
    REQUIRE( cc_o.steps.back().mulliken_pop_per_atom.front().second == Approx(0.002777) );
    REQUIRE( cc_o.steps.back().mulliken_pop_per_atom.back().first == Approx(0.935496) );
    REQUIRE( cc_o.steps.back().mulliken_pop_per_atom.back().second == Approx(0.064504) );
    REQUIRE( cc_o.steps.back().lowdin_pop_per_atom.front().first == Approx(5.989834) );
    REQUIRE( cc_o.steps.back().lowdin_pop_per_atom.front().second == Approx(0.010166) );
    REQUIRE( cc_o.steps.back().lowdin_pop_per_atom.back().first == Approx(0.966150) );
    REQUIRE( cc_o.steps.back().lowdin_pop_per_atom.back().second == Approx(0.033850) );
    REQUIRE( *(cc_o.steps.back().dipole_moment) == v3d(v3d::Zero()) );

  }

  SECTION ("Parsing results of geometry optimization[PC Gamess Firefly]") {

    std::ifstream isec("../examples/io/ref_data/firefly/dvb_gopt_a.out");
    comp_chem_program_data_t<double> cc_o;
    read_ccd_from_firefly_output(isec, cc_o);
    REQUIRE( cc_o.tot_num_electrons == 70) ;
    REQUIRE( cc_o.tot_charge == Approx(0)) ;
    REQUIRE( cc_o.DIM == 0 );
    REQUIRE( cc_o.mult == 1 );
    REQUIRE( cc_o.n_alpha == 35 );
    REQUIRE( cc_o.n_beta == 35 );
    REQUIRE( cc_o.tot_num_atoms == 20);
    REQUIRE( cc_o.run_t == comp_chem_program_run_t::geo_opt);
    REQUIRE( cc_o.init_pos.size() == 20);
    REQUIRE( cc_o.init_atom_names.size() == 20);
    REQUIRE( cc_o.steps.size() == 24);
    REQUIRE( cc_o.m_is_terminated_normally == true );
    REQUIRE( cc_o.steps.front().pos.size() == cc_o.init_pos.size());
    REQUIRE( cc_o.steps.back().pos.size() == cc_o.init_pos.size());
    REQUIRE( cc_o.steps.back().pos[0] == v3d(0.2292900177, 1.3927230046, 0.0) );
    REQUIRE( cc_o.steps.back().pos.back() == v3d(-0.0328883188, 4.8736185925, 0.0) );
    REQUIRE( cc_o.steps.back().grad.front() == v3d(-0.0000150, -0.0000011, 0.0000000) );
    REQUIRE( cc_o.steps.back().grad.back() == v3d(-0.0000191, 0.0000149, 0.0000000) );

  }

  SECTION ("Parsing results of hessian calculation[PC Gamess Firefly]") {

    std::ifstream isec("../examples/io/ref_data/firefly/dvb_ir.out");
    comp_chem_program_data_t<double> cc_o;
    read_ccd_from_firefly_output(isec, cc_o);
    REQUIRE( cc_o.tot_num_electrons == 70) ;
    REQUIRE( cc_o.tot_charge == Approx(0)) ;
    REQUIRE( cc_o.DIM == 0 );
    REQUIRE( cc_o.mult == 1 );
    REQUIRE( cc_o.n_alpha == 35 );
    REQUIRE( cc_o.n_beta == 35 );
    REQUIRE( cc_o.tot_num_atoms == 20);
    REQUIRE( cc_o.run_t == comp_chem_program_run_t::vib);
    REQUIRE( cc_o.init_pos.size() == 20);
    REQUIRE( cc_o.init_atom_names.size() == 20);
    REQUIRE( cc_o.vibs.size() == 60 );
    REQUIRE( cc_o.vibs[0].frequency == Approx(5.89) );
    REQUIRE( cc_o.vibs[0].intensity == Approx(0.00000) );
    REQUIRE( cc_o.vibs[6].frequency == Approx(38.65) );
    REQUIRE( cc_o.vibs[6].intensity == Approx(0.00004) );
    REQUIRE( cc_o.vibs[15].frequency == Approx(528.44) );
    REQUIRE( cc_o.vibs[15].intensity == Approx(0.05468) );
    REQUIRE( cc_o.vibs[59].frequency == Approx(3816.56) );
    REQUIRE( cc_o.vibs[59].intensity == Approx(0.00000) );
    REQUIRE( cc_o.vibs[25].disp[0] == v3d(0, 0, 0.00328228));
    REQUIRE( cc_o.vibs[25].disp[1] == v3d(0, 0, -0.00328228));
    REQUIRE( cc_o.vibs[25].disp[18] == v3d(0, 0, -0.39977811));
    REQUIRE( cc_o.vibs[25].disp[19] == v3d(0, 0, 0.39977811));

  }

}

TEST_CASE( "Compilation of ccd model" ) {

  SECTION( " Compile 0d models") {
    std::ifstream isec("../examples/io/ref_data/firefly/dvb_sp.out");
    comp_chem_program_data_t<double> cc_o;
    read_ccd_from_firefly_output(isec, cc_o);
    geometry<double, periodic_cell<double> > g(0);
    bool succes = compile_geometry(cc_o, g);
    REQUIRE( succes == true);
    REQUIRE( g.nat() == cc_o.tot_num_atoms);
  }

}
