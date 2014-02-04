#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>

struct A{
  virtual void a(){std::cout << "class A \n";}
};

template<class T>
struct B: public A{
  T b;
public:
  B(T _b){b=_b;}

  virtual void a(){std::cout << "class B " << b << " type=" << typeid(T).name() <<  "\n";}
};

struct list{
  
  std::vector<A*> x;

  A& operator[](int i){return *(x[i]);}

  void add(A & a)
  {
    x.push_back(&a);
  }

};

int main()
{

  list l;

  l.add(*new A);
  l.add(*new B<int>(42));
  l.add(*new A);
  l.add(*new B<double>(3.14));
  l.add(*new A); 
  l.add(*new B<std::string>("hahaha"));

  for (int i=0; i<l.x.size(); i++)
    l[i].a();

}
