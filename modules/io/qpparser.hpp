#ifndef _QPP_QPPARSER_H
#define _QPP_QPPARSER_H


#include <string>
#include <ios>
#include <iostream>

namespace _qpp_internal{

  
  //  template<typename _CharT = std::string::value_type, class _Traits = std::char_traits<_CharT> >
  template<typename _CharT, class _Traits>
  bool parse_brace(std::string & firststr, std::basic_istream<_CharT, _Traits>  & input, _CharT closer)
  {
    std::string line = firststr;
    bool finished = false, error = false;
      {
	unsigned i = line.find_first_of("{}()");
	if ( i == std::string::npos )
	  {
	    //process line
	    std::cout << line << "\n";
	    if ( ! (error = input.eof()) )
	      std::getline(input,line);
	  }
	else if ( line[i] == closer )
	  {
	    // block finished
	    finished = true;
	    firststr = line.substr(i+1);
	  }
	else if ( line[i] == '{' )
	  {
	    // block{ begin	   
	    std::cout << line.substr(0,i) << "\n";
	    std::cout << "block{ begin:\n";
	    parse_brace(line,input,'}');
	    std::cout << "block{ end\n";
	  }
	else if ( line[i] == '(' )
	  {
 	    // block{ begin	   
	    std::cout << line.substr(0,i) << "\n";
	    std::cout << "block( begin:\n";
	    parse_brace(line,input,')');
	    std::cout << "block( end\n";
	  }
	  	
      } while(! ( finished || error) );
      return !error;
  }


};

#endif
