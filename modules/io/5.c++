#include <iostream>

template<class B = double, class C=int>
class A{
  B b;
  C c;
public:

  A(B _b, C _c){b=_b; c=_c;}

  void p(){ std::cout << b << " " << c << "\n"; }

};

int main()
{
  A a(1.1,45);

  a.p();
}
