// Example for permutations group

#include <geom/lace3d.hpp>
#include <symm/symm.hpp>
#include <symm/group_theory.hpp>
#include <iostream>
//#include <boost/format.hpp>
#include <iomanip> 
#include <Eigen/Dense>
#include <initializer_list>

using namespace qpp;

typedef Eigen::Matrix<double,Eigen::Dynamic, 1> vec;

class permutation
{
  std::vector<int> p;

public:
  
  static const int N;
  
  static permutation unity;

  permutation()
  {
    for (int i=0; i<N; i++)
      p.push_back(i);
  }


  permutation(const permutation & b) 
  {
    //std::cout << "copy constructor\n";
    for (int i : b.p)
      p.push_back(i);
  }

  permutation(const std::initializer_list<int> & li)
  {
    //std::cout << "list constructor\n";
    if (li.size()!=N)
      throw std::range_error("wrong permutation size");
    for (int j : li)
      p.push_back(j);
    
    /*
    for (int j=0; j<N; j++)
      std::cout << p[j] << " ";
    std::cout << std::endl;
    */
  }

  inline int operator[](int i) const
  { return p[i];}

  inline int & operator[](int i)
  { return p[i];}

  inline int size() const
  {return p.size();}

  static inline permutation Identity(){
    return permutation::unity;
  }

  inline permutation  operator*(const permutation & b)
  {
    /*
    print();
    std::cout << "*";
    b.print();
    std::cout << "\n";
    */
    permutation res;
    for (int i=0; i<N; i++)
      res[i] = p[b[i]];
    return res;
  }

  inline bool operator==(const permutation & b)
  {
    bool res=true;
    for (int i=0; i<N; i++)
      if (p[i] != b[i])
	{
	  res = false;
	  break;
	}
    return res;
  }

  inline bool operator!=(const permutation & b)
  {
    return ! ((*this)==b);
  }

  void print() const
  {
    std::cout << "(";
    for (int i:p)
      std::cout << i << " ";
    std::cout <<")";
  }

};

const int permutation::N = 6;
permutation permutation::unity;

int main()
{

  generated_group<permutation> P;
  /*  
  P.generator({1,0,2,3,4});
  P.generator({2,0,1,3,4});
  P.generator({3,1,2,0,4});
  P.generator({4,1,2,3,0});
  */
  P.add({1,0,2,3,4,5});
  P.add({2,0,1,3,4,5});
  P.add({3,1,2,0,4,5});
  P.add({4,1,2,3,0,5});
  P.add({5,1,2,3,4,0});

  for (int i=0; i<P.size(); i++)
    {
      for (int j=0; j<permutation::N; j++)
	std::cout << P[i][j] << " ";
      std::cout << std::endl;
    }

  group_analyzer<permutation, decltype(P)> A(P);

  std::cout << "N classes = " << A.n_classes() << "\n";
  for (int c=0; c< A.n_classes(); c++)
    {
      for (int j=0; j<A.class_size(c); j++)
	std::cout << A.class_element(c,j) << " ";
      std::cout << std::endl;
    }


  //group_characters<std::complex<double>,permutation, decltype(P)> chi(P,A);
  group_characters<double,permutation, decltype(P)> chi(P,A);
  std::cout << "N IRREP = " << chi.nirrep << std::endl;
  std::cout << chi.chi << std::endl;
}
