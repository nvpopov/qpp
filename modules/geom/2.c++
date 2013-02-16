#include <iostream>

class A{
public:
  static int counter;
  int UID;
  int something;

  A(){counter++; UID=counter;}

  A(int s){counter++; UID=counter; something=s;}

  A(const A & a){counter++; UID=counter; something=a.something;}

  void info() const{std::cout << "UID= " << UID << " essence= " << something << std::endl;}

};

int A::counter = 0;

void receive(const A & a)
{
  std::cout << "receive : ";
  const A *p = &a;
  p->info();
}

int main()
{
  A a(5);
  A b(a);

  a.info();
  b.info();
  receive(a);

  receive(*new A(7));
}
