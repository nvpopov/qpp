#ifndef _TYPES_H
#define _TYPES_H

#include <string>
#include <iostream>
#include <sstream>

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

  typedef std::basic_stringstream<CHAR,TRAITS> SSTREAM;

};

#endif
