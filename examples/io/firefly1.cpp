#include <io/ccd_firefly.hpp>
#include <fstream>

using namespace qpp;

int main () {

  //geometry<float> g(0);

  //std::ifstream ifile("../examples/io/ref_data/firefly/1Ca10F20.outp");
  //std::ifstream ifile("../examples/io/ref_data/firefly/water_mp2.out");
  //std::ifstream ifile("../examples/io/ref_data/firefly/dvb_gopt_a.out");
  std::ifstream ifile("../examples/io/ref_data/firefly/dvb_ir.out");
  comp_chem_program_data_t<float> cc_o;
  read_ccd_from_firefly_output(ifile, cc_o);

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

  fmt::print(std::cout, "\nInitial geometry:\n");
  fmt::print(std::cout, "{:>15} {:>15} {:>15} {:>15}\n", "atom", "x", "y", "z");
  for (size_t i = 0; i < cc_o.init_atom_names.size(); i++)
    fmt::print(std::cout, "{:>15} {:15} {:15} {:15}\n", cc_o.init_atom_names[i],
               cc_o.init_pos[i][0], cc_o.init_pos[i][1], cc_o.init_pos[i][2]);

  for (size_t i = 0; i < cc_o.steps.size(); i++) {

      if (i == cc_o.steps.size()-1) fmt::print(std::cout, "\nFinal step:\n");
      else fmt::print(std::cout, "\nCalculation step {}:\n",i);

      //write scf info header
      fmt::print(std::cout, "Total scf-steps: {}\n", cc_o.steps[i].scf_steps.size());

      //write scf convergence info
      if (!cc_o.steps[i].scf_steps.empty()) {
          fmt::print(std::cout, "{:>15} {:>15} {:>15} {:>15} {:>15} {:>15} {:>15}\n",
                     "iter", "ex", "dem", "tot_en", "e_cnahge", "d_change", "o_grd(diis_er)");
          for (auto &scf_step : cc_o.steps[i].scf_steps){
              fmt::print(std::cout, "{:15} {:15} {:15} {:15} {:15} {:15} {:15}\n",
                         scf_step.iter, scf_step.ex, scf_step.dem,
                         scf_step.total_energy, scf_step.e_change, scf_step.d_change,
                         scf_step.orb_grad_or_diis_error);
            }
        }

      //write single particle energies
      if (!cc_o.steps[i].eigen_values.empty()) {
          fmt::print("\nEigen-values of single-particle states:\n");
          fmt::print(std::cout, "{:>15} {:>15}\n", "state_idx", "state_energy");
          for (size_t sp_i = 0; sp_i < cc_o.steps[i].eigen_values.size(); sp_i++)
            fmt::print(std::cout, "{:15} {:15}\n", sp_i, cc_o.steps[i].eigen_values[sp_i]);
        }

      //write pop analysis
      if (!cc_o.steps[i].mulliken_pop_per_atom.empty()) {
          fmt::print(std::cout, "\n{:>15} {:>15}\n", "mulliken_pop", "charge");
          for (size_t p = 0; p < cc_o.steps[i].mulliken_pop_per_atom.size(); p++)
            fmt::print(std::cout, "{:15} {:15}\n", cc_o.steps[i].mulliken_pop_per_atom[p].first,
                       cc_o.steps[i].mulliken_pop_per_atom[p].second);
        }

      if (!cc_o.steps[i].lowdin_pop_per_atom.empty()) {
          fmt::print(std::cout, "\n{:>15} {:>15}\n", "lowdin_pop", "charge");
          for (size_t p = 0; p < cc_o.steps[i].lowdin_pop_per_atom.size(); p++)
            fmt::print(std::cout, "{:15} {:15}\n", cc_o.steps[i].lowdin_pop_per_atom[p].first,
                       cc_o.steps[i].lowdin_pop_per_atom[p].second);
        }

      //write dipole moment
      if (cc_o.steps[i].dipole_moment)
        fmt::print(std::cout, "\nDipole moment = {}\n", *(cc_o.steps[i].dipole_moment));

      //write atom coordinates and gradients
      if (!cc_o.steps[i].pos.empty() && !cc_o.steps[i].grad.empty()) {
          fmt::print(std::cout, "\n{:>15} {:>15} {:>15} {:>15} {:>15} {:>15} {:>15}\n",
                     "atom", "x", "y", "z", "dx", "dy", "dz");
          for (size_t q = 0 ; q < cc_o.init_atom_names.size(); q++){
              fmt::print(std::cout, "{:>15} {:15} {:15} {:15} {:15} {:15} {:15}\n",
                         cc_o.init_atom_names[q],
                         cc_o.steps[i].pos[q][0],
                  cc_o.steps[i].pos[q][1],
                  cc_o.steps[i].pos[q][2],
                  cc_o.steps[i].grad[q][0],
                  cc_o.steps[i].grad[q][1],
                  cc_o.steps[i].grad[q][2]);
            }
        }

      fmt::print(std::cout, "Final step energy: {}\n", cc_o.steps[i].total_energy);

    }

  if (!cc_o.vibs.empty()) {
      fmt::print(std::cout, "\nVibration analysis:\n");
      for (int v = 0; v < cc_o.vibs.size(); v++)
        fmt::print(std::cout, "{:15} {:15} {:15}\n",
                   v, cc_o.vibs[v].frequency, cc_o.vibs[v].intensity);

      fmt::print(std::cout, "\nDisplacement for vibration mode {}:\n", 23);
      for (size_t i = 0; i < cc_o.vibs[29].disp.size(); i++)
        fmt::print(std::cout, "{}\n", cc_o.vibs[29].disp[i]);
    }


}
