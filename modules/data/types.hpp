#ifndef _TYPES_H
#define _TYPES_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

namespace qpp{

#ifdef WCHAR

#define CHAR wchar
#define STRING std::wstring

#else

#define CHAR char
#define STRING std::string

#endif

#undef assert

  typedef std::char_traits<CHAR> TRAITS;

  typedef std::basic_ostream<CHAR,TRAITS> OSTREAM;

  typedef std::basic_istream<CHAR,TRAITS> ISTREAM;

  typedef std::basic_ifstream<CHAR,TRAITS> IFSTREAM;

  typedef std::basic_ofstream<CHAR,TRAITS> OFSTREAM;

  typedef std::basic_stringstream<CHAR,TRAITS> SSTREAM;

};

#endif
