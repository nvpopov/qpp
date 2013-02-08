#include <iostream>
#include <vector>
#include <cmath>

class pc{ 

  virtual bool isc1()=0;

  virtual bool isc2()=0;

  virtual int something()=0;

};

class c : public pc{
public:

  virtual bool isc1(){return false;}

  virtual bool isc2(){return false;}

  virtual int something(){return 0;}

};


class c1 : public c{

  int var1;
public:

  c1(int i){var1=i;}

  virtual bool isc1(){return true;}

  virtual int something(){return var1;}

};

class c2 : public c{
  double var2;

public:
  
  c2(double x){var2=x;}

  virtual bool isc2(){return true;}

  virtual int something(){return int(var2);}
};

int main()
{
  std::vector<pc> cc;
  
  cc.push_back(*new c);
  cc.push_back(*new c1(5));
  cc.push_back(*new c2(std::sqrt(10.0)));

  for (int i=0; i<cc.size(); i++)
    //    std::cout << i << " " << cc[i]->isc1() << " " << cc[i]->isc2() << " " << cc[i]->something() << "\n";
    std::cout << i << " " << cc[i].isc1() << " " << cc[i].isc2() << " " << cc[i].something() << "\n";
}
