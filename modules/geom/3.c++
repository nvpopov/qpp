#include <iostream>
#include <vector>
#include <syntax/basic.hpp>
#include <string>

int main(){

  std::string s;
  while(1)
    {
      std::getline(std::cin,s);
      std::vector<std::string> fs;
      fs = qpp::explode(" ",s);
      for (int i=0; i<fs.size(); i++)
	std::cout << i << " \"" << fs[i] << "\"\n";
    }

}
