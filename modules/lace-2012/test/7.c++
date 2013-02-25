#include <iostream>

class A{

  int a;
public:
  A(int _a):a(_a){};

  int val(){return a;}

  virtual A&  operator=(A & x) = 0;

};

int main(){


  A aa(3);


  std::cout << aa.val() << "\n";

}
