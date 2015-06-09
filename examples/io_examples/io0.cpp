#include <io/qpparser.hpp>
#include <geom/geom.hpp>
#include <geom/geom.hpp>
#include <iostream>
#include <fstream>
#include <io/qpparser.hpp>

using namespace qpp;

int main()
{
  do{
    std::string s,ss;
    int i;
    double d;
    float f;
    bool b;
    bool res;

    std::cin >> ss;
    res = s2t<double>(ss,d);
    std::cout << "double: " << res << " " << d << "\n";
    res = s2t<float>(ss,f);
    std::cout << "float: " << res << " " << f << "\n";
    res = s2t<int>(ss,i);
    std::cout << "int: " << res << " " << i << "\n";
    res = s2t<bool>(ss,b);
    std::cout << "bool: " << res << " " << b << "\n";
    res = s2t<std::string>(ss,s);
    std::cout << "string: " << res << " " << s << "\n";

  }while(true);
}
