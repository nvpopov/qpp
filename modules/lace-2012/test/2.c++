#include <iostream>

// template <class A>
// class B : public A{
// public:

//   virtual void who(){std::cout << "I am B\n";}

// };

// class AA{
// public:

//   virtual void who(){std::cout << "I am AA\n";}

// };

// int main()
// {
//   AA aa;

//   aa.who();

//   B<AA> b;

//   b.who();

//   B<int> i;

//   i.who();
// }


void list(int N, double r[])
{
  for (int i=0; i<N; i++)
    std::cout << i << " " << r[i] << "\n";
}

int main()
{
//   double r[] ={1.0,2.0,3.0}; 
//   list(3,r);
  list(3,(double[]){1.0,2.0,3.0});
}
