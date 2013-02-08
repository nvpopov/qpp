#include <iostream>

template<int>
struct s;


template<>
struct s<1>
{
  enum{
    f=1
  } flag;
};

template<>
struct s<2>
{
  enum{
    f=2
  } flag;
};

int main()
{
#line 25 "Illegal value of periodicity"
  std::cout << s<1>::f << "\n";
}
