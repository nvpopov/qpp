#include <io/firefly.hpp>
#include <fstream>

using namespace qpp;

int main () {

  geometry<float> g(0);
  std::ifstream ifile("../examples/io/ref_data/firefly/dvb_gopt_a.out");
  comp_chem_program_output_t<float> cc_o;
  read_firefly_output(ifile, g, cc_o);

  fmt::print(std::cout, "Total number of atoms: {}\n", cc_o.tot_num_atoms);
  fmt::print(std::cout, "Total number of electrons: {}\n", cc_o.tot_num_electrons);
  fmt::print(std::cout, "Total charge of molecule: {}\n", cc_o.tot_charge);
  fmt::print(std::cout, "Molecule multiplicity: {}\n", cc_o.mult);

  fmt::print(std::cout, "Is calculation unrestricted? : {}\n", cc_o.is_unrestricted);
  if (cc_o.is_unrestricted) {
      fmt::print(std::cout, "Num. occup. alpha = {}\n", cc_o.n_alpha);
      fmt::print(std::cout, "Num. occup. beta = {}\n", cc_o.n_beta);
    } else {
      fmt::print(std::cout, "Num. occup. = {}\n", cc_o.n_alpha);
    }

  fmt::print(std::cout, "Calculation type = {}", cc_o.run_t);
  fmt::print(std::cout, " [unknown(0), energy(1), grad(2), geo_opt(3),"
                        "md(4), vib(5), tddft(6), spectrum(7)]\n");

  fmt::print(std::cout, "Total calculation steps: {}\n", cc_o.steps.size());
  fmt::print(std::cout, "Is calculation terminated normally? {}\n", cc_o.m_is_terminated_normally);
  for (size_t i = 0; i < cc_o.steps.size(); i++) {

      if (i == cc_o.steps.size()-1) fmt::print(std::cout, "\nFinal step:\n");
      else fmt::print(std::cout, "\nCalculation step {}:\n",i);


      //write scf info header
      fmt::print(std::cout, "Total scf-steps: {}\n", cc_o.steps[i].scf_steps.size());

      //write scf convergence info
      if (!cc_o.steps[i].scf_steps.empty()) {
          fmt::print(std::cout, "{:>15} {:>15} {:>15} {:>15} {:>15} {:>15} {:>15}\n",
                     "iter", "ex", "dem", "tot_en", "e_cnahge", "d_change", "orb_grad");
          for (auto &scf_step : cc_o.steps[i].scf_steps){
              fmt::print(std::cout, "{:15} {:15} {:15} {:15} {:15} {:15} {:15}\n",
                         scf_step.iter, scf_step.ex, scf_step.dem,
                         scf_step.total_energy, scf_step.e_change, scf_step.d_change,
                         scf_step.orb_grad);
            }
        }

      //write atom coordinates and gradients
      fmt::print(std::cout, "\n{:>15} {:>15} {:>15} {:>15} {:>15} {:>15} {:>15}\n",
                 "atom", "x", "y", "z", "dx", "dy", "dz");
      for (size_t q = 0 ; q < cc_o.init_atom_names.size(); q++){
          fmt::print(std::cout, "{:15} {:15} {:15} {:15} {:15} {:15} {:15}\n",
                     cc_o.init_atom_names[q],
                     cc_o.steps[i].pos[q][0],
              cc_o.steps[i].pos[q][1],
              cc_o.steps[i].pos[q][2],
              cc_o.steps[i].grad[q][0],
              cc_o.steps[i].grad[q][1],
              cc_o.steps[i].grad[q][2]);
        }

      fmt::print(std::cout, "Final step energy: {}\n", cc_o.steps[i].total_energy);

    }
}
