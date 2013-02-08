#include <iostream>

struct cmplx
{
  double x,y;

  cmplx(double _x, double _y)
  { x=_x; y=_y;}
};

template <int I>
struct slct
{
  typedef double type;

  static inline type & newelem(double &x, double &y)
  {
    return x;
  }
};

template <>
struct slct<0>
{
  typedef cmplx type;  

  static inline type & newelem(double &x, double &y)
  {
    return * new cmplx(x,y);
  }
};

// template <>
// struct slct<1>
// {
//   typedef int type;
// };

template <int I, int J>
struct slct1{
  typedef double type;

  static inline type & newelem(double &x, double &y)
  {
    return x;
  }
};

template <int J>
struct slct1<0,J>{
  typedef typename slct<J>::type type;

  static inline type & newelem(double &x, double &y)
  { return slct<J>::newelem(x,y);}
};

int main(){

  double x=3,y=2;

  slct1<0,0>::type *a=slct1<0,0>::newelem(x,y);
  slct1<0,1>::type *b=(3,2);
  slct1<0,2>::type *c=(3,2);
  slct1<1,0>::type *d=(3,2);
  slct1<2,4>::type *e=(3,2);

  std::cout << typeid(a).name() << "\n";
  std::cout << typeid(b).name() << "\n";
  std::cout << typeid(c).name() << "\n";
  std::cout << typeid(d).name() << "\n";
  std::cout << typeid(e).name() << "\n";
}
