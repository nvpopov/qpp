#include <iostream>
#include <data/qppdata.hpp>

using namespace qpp;

int main(int argc, char **argv)
{
  try{
    qpp_array *p = new qpp_parameter<STRING>("replace","");

    std::cout << "mask= " << p->allowed() << "\n";
    
    p->add(*new qpp_parameter<int>("i",3));
    p->add(*new qpp_parameter<STRING>("atom","Ca"));
    p->add(*new qpp_parameter<double>("charge",20.0));
    
    p->write(std::cout);
    std::cout << "\n";
    p->write(std::cout,1);
  }
  catch (qpp_exception & e)
    {
      std::cerr << e.what() << "\n";
    }
}
