#include<vector>
#include<iostream>

int main(){
  std::vector<int> v;
  for (int i=0; i<10; i++)
    v.push_back(10-i);

  std::vector<int>::iterator i=v.begin();
  while (i!=v.end())
    std::cout << *(i++) << " ";
  std::cout << "\n";
}
