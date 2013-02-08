#include <iostream>

class empty{

public:

  inline bool operator==(empty b)
  {
    return true;
  }

};

int main()
{
  empty a,b;

  std::cout << (a==a)  << "\n";
}
