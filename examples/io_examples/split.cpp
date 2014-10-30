#include<iostream>
#include<string>
#include<sstream>
#include<stdlib.h>
#include<io/qpparser.hpp>

int main()
{
  do{

    std::string line;
    getline(std::cin,line);
    std::cout << "\"" << line << "\"\n";

    _qpp_internal::tokenizer tok(line);
    tok.dump(" \t");
    tok.separate("");
    while(!tok.eof())
      std::cout << "tok:\"" << tok.get() << "\"\n";

    std::vector<std::string> fld;
    _qpp_internal::split(line,fld);
    for (int i=0; i<fld.size(); i++)
      std::cout << "\"" << fld[i] << "\"\n";

  } while(true);
}
