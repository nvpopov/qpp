#include <iostream>
#include <stdlib.h>     /* srand, rand*/
#include <time.h>       /* time */
#include <vector>
#include <boost/format.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>

int main()
{
  std::vector<int> a,b;

  for (int i=0; i<10; i++)
    a.push_back(2*i+1);

  b=a;

  for (int i=0; i<b.size(); i++)
    std::cout << b[i] << " ";
  std::cout << "\n";
}
