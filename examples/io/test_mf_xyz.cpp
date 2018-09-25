#include <iostream>
#include <fstream>
#include <io/geomio.hpp>
#include <io/xyz_multiframe.hpp>
#include <string>

using namespace std::string_literals;

int main(){
  std::ifstream xyz_file("../examples/io/ref_data/23elim.xyz"s);
  if (xyz_file) std::cout << "File is good! Reading...\n";

  qpp::geometry<float> geom(3);
  std::vector<qpp::geom_anim_record_t<float> > anim;

  qpp::read_xyz_multiframe(xyz_file, geom, anim);

  std::cout << "Total animations in multiframe file = " << anim.size() << std::endl;
  for (auto i = 0 ; i < anim.size(); i++){
      std::cout << "Animations " << i << " data :" << std::endl;
      std::cout << "Anim type " << anim[i].m_anim_type << std::endl;
      std::cout << "Total frames " << anim[i].frame_data.size() << std::endl;
      for (auto q = 0; q < anim[i].frame_data.size(); q++){
          std::cout << "Total atoms in frame " << q << " = "
                    << anim[i].frame_data[q].size() << std::endl;
        }
    }
}
