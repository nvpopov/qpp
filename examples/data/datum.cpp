//#include <data/data.hpp>
#include "data/data.hpp"
#include <iostream>

int main()
{
 
  qpp::datum a(1),b;

  std::cout << a.type() << "\n";
  std::cout << a.get<int>() << "\n";  

  a="nhruhruhru";

  std::cout << a.type() << "\n";
  std::cout << a.get<STRING>() << "\n";
  

  //  a.set("nhruhruhru");
  //a.set(3);

  double dd=3.14;

  a.set(&dd);
  std::cout << a.get<double>() << "\n";

  a.ref<double>() *= 2.5;
  std::cout << a.get<double>() << " " << dd << "\n";

  std::string ss="lkajsdlkjasdljad";

  a.set(&ss);
  b = ss;

  std::cout << a.type() << "\n";
  std::cout << a.get<STRING>() << "\n";

  a.ref<STRING>()[5] = 'W';

  std::cout << ss << "|" << b.get<STRING>() << "\n";

  qpp::datum c;
  c.set(float(1.111111111111));
  std::cout << "c<double> = " << c.get<double>() << "\n";

  qpp::datum d("I am string datum");
  std::cout << d << "\n";

  qpp::datum d1(d);
  std::cout << d << "\n";

  std::vector<qpp::datum> v = {qpp::datum(1),
			       qpp::datum(456e-2),
			       qpp::datum("piggy piggy"),
			       qpp::datum(true)};
  // qpp::datum v[] = {qpp::datum(1),qpp::datum(456e-2),qpp::datum("piggy piggy"),qpp::datum(true)};
  for (int i=0; i<4; i++)
    std::cout << v[i] << " ";
  std::cout << "\n";

}

