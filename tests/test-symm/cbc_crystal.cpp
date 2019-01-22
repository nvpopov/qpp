#include <symm/groups.hpp>
#include <symm/cell.hpp>
#include <symm/transform.hpp>
#include <symm/group_theory.hpp>
#include <iostream>
#include <ctime>

using namespace qpp;

int main()
{
  periodic_cell<double> cl({4,0,0}, {0,4,0}, {0,0,4});
  std::cout << cl.DIM << std::endl;
  std::cout << cl << std::endl;

  rotrans<double,true>
    E(vector3<double>(0,0,0),&cl),
    T1(vector3<double>(2,0,0),&cl),
    T2(vector3<double>(0,2,0),&cl),
    T3(vector3<double>(0,0,2),&cl),
    C4x(RotMtrx({1,0,0},qpp::pi/2),&cl),
    C4y(RotMtrx({0,1,0},qpp::pi/2),&cl);

  array_group<decltype(T1)> cbc("",E);

  std::cout << clock() << " " << CLOCKS_PER_SEC << " " << 1e0*clock()/ CLOCKS_PER_SEC << std::endl;
  std::cout << T1 << std::endl;
  cbc.generate(T1);

  std::cout << clock() << " " << CLOCKS_PER_SEC << " " << 1e0*clock()/ CLOCKS_PER_SEC << std::endl;
  cbc.generate(T2);

  std::cout << clock() << " " << CLOCKS_PER_SEC << " " << 1e0*clock()/ CLOCKS_PER_SEC << std::endl;
  cbc.generate(T3);

  std::cout << clock() << " " << CLOCKS_PER_SEC << " " << 1e0*clock()/ CLOCKS_PER_SEC << std::endl;
  cbc.generate(C4x);

  std::cout << clock() << " " << CLOCKS_PER_SEC << " " << 1e0*clock()/ CLOCKS_PER_SEC << std::endl;
  cbc.generate(C4y);

  std::cout << clock() << " " << CLOCKS_PER_SEC << " " << 1e0*clock()/ CLOCKS_PER_SEC << std::endl;
  std::cout << "multab\n";

  group_analyzer<rotrans<double,true>,  array_group<rotrans<double,true> > > acbc(cbc);
  std::cout << clock() << " " << CLOCKS_PER_SEC << " " << 1e0*clock()/ CLOCKS_PER_SEC << std::endl;


  std::cout << "N classes = " << acbc.n_classes() << std::endl;
  for (int c=0; c< acbc.n_classes(); c++) {
      for (int j=0; j<acbc.class_size(c); j++) std::cout << acbc.class_element(c,j) << " ";
      std::cout << std::endl;
    }


  std::vector<int> ee = {0}, gg = acbc.find_generators(ee);

  std::cout << "generators ";
  std::cout << clock() << " " << CLOCKS_PER_SEC << " " << 1e0*clock()/ CLOCKS_PER_SEC << std::endl;

  for (int g : gg) std::cout << g << " ";

  std::cout << std::endl;


  ee.resize(8);
  for (int i=0; i<8; i++) ee[i]=i;

  gg = acbc.find_generators(ee);
  std::cout << clock() << " " << CLOCKS_PER_SEC << " " << 1e0*clock()/ CLOCKS_PER_SEC << std::endl;

  for (int g : gg) std::cout << g << " ";

  std::cout << std::endl;

  group_characters<std::complex<double>,
      rotrans<double,true>,  array_group<rotrans<double,true> > > chi(cbc,acbc);

  std::cout << clock() << " " << CLOCKS_PER_SEC << " " << 1e0*clock()/ CLOCKS_PER_SEC << std::endl;
  std::cout << "N IRREP = " << chi.nirrep << std::endl;

  std::cout << chi.chi << std::endl;
}

