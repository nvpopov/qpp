#include<io/strfun.hpp>
#include <iostream>

int main()
{
  /*
  qpp::tokenizer tok(std::cin);
  tok.dump("");
  tok.separate("\"");

  while(true)
    std::cout << "\"" << tok.get() << "\"\n";
  */

  while(true)
    {
      STRING s;
      std::cin >> s;
      std::cout << qpp::is_identifier(s) << "\n";
    }
}
