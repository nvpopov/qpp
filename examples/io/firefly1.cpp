#include <io/firefly.hpp>
#include <fstream>

using namespace qpp;

int main () {

  geometry<float> g(0);
  std::ifstream ifile("../examples/io/ref_data/firefly/dvb_gopt_a.out");
  qc_program_output<float> output;
  read_firefly_output(ifile, g, output);

  fmt::print(std::cout, "Total number of atoms: {}\n", output.tot_num_atoms);
  fmt::print(std::cout, "Total number of electrons: {}\n", output.tot_num_electrons);
  fmt::print(std::cout, "Total charge of molecule: {}\n", output.tot_charge);
  fmt::print(std::cout, "Molecule multiplicity: {}\n", output.mult);

  fmt::print(std::cout, "Is calculation unrestricted? : {}\n", output.is_unrestricted);
  if (output.is_unrestricted) {
      fmt::print(std::cout, "Num. occup. alpha = {}\n", output.n_alpha);
      fmt::print(std::cout, "Num. occup. beta = {}\n", output.n_beta);
    } else {
      fmt::print(std::cout, "Num. occup. = {}\n", output.n_alpha);
    }

  fmt::print(std::cout, "Calculation type = {}", output.run_t);
  fmt::print(std::cout, " [unknown(0), rt_energy(1), rt_grad(2), rt_geo_opt(3),"
                        "rt_md(4), rt_vib(5), rt_tddft(6), rt_spectrum(7)]\n");

  fmt::print(std::cout, "Total calculation steps: {}\n", output.steps.size());

  for (size_t i = 0; i < output.steps.size(); i++) {
      fmt::print(std::cout, "\nCalculation step {}:\n",i);
      fmt::print(std::cout, "Total scf-steps: {}\n", output.steps[i].scf_steps.size());

      if (!output.steps[i].scf_steps.empty()) {
          fmt::print(std::cout, "{:>15} {:>15} {:>15} {:>15} {:>15} {:>15} {:>15}\n",
                     "iter", "ex", "dem", "tot_en", "e_cnahge", "d_change", "orb_grad");
          for (auto &scf_step : output.steps[i].scf_steps){
              fmt::print(std::cout, "{:15} {:15} {:15} {:15} {:15} {:15} {:15}\n",
                         scf_step.iter, scf_step.ex, scf_step.dem,
                         scf_step.total_energy, scf_step.e_change, scf_step.d_change,
                         scf_step.orb_grad);
            }
        }

    }
}
