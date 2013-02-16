#include <iostream>

class A{
public:
  virtual void f(){std::cout << "class A\n";}
};

class B : public A{
public:
  virtual void f(){std::cout << "class B\n";}
};

void doa(A &a)
{
  a.f();
}

int main()
{
  A a;
  B b;

  doa(a);
  doa(b);
}


