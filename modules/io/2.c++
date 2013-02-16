#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

int main()
{
  string s;
  do
    {
      getline(cin,s);
      cout <<  s.find_first_not_of(" \t") << " " << (s.find_first_not_of(" \t")==string::npos) << "\n";
    } while(1);
}
