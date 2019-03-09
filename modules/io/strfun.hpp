#ifndef QPP_STRFUN
#define QPP_STRFUN

#include <data/types.hpp>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <geom/lace3d.hpp>

namespace qpp{

  // -------------------- Simple tokenizer -----------------------------------

  class tokenizer{
    std::basic_istream<CHAR,TRAITS> * _input;
    STRING _buff, _dump, _sepr;
    int _line_number;
    STRING _filename;
    bool _created_here;

  public:

    tokenizer(ISTREAM & input, const STRING & __filename=""){
      _input = & input;
      _dump = " \t";
      _line_number = 0;
      _filename = __filename;
      _created_here = false;
    }
    /*
        tokenizer(const STRING & str)
        {
          _input = new std::basic_stringstream<CHAR,TRAITS>(str);
          _dump = " \t";
          _line_number = 0;
          _filename = "";
          _created_here = true;
        }
        */
    tokenizer(const STRING & __filename){
      _input = new
          std::basic_ifstream<CHAR,TRAITS>(__filename.c_str());
      _dump = " \t";
      _line_number = 0;
      _filename = __filename;
      _created_here = true;
    }

    ~tokenizer(){
      if (_created_here)
        delete _input;
    }

    void dump(const STRING & smb){
      _dump = smb;
    }

    void separate(const STRING & smb){
      _sepr = smb;
    }

    STRING get(){
      int i;
      if (_buff == "" ){
          std::getline(*_input, _buff);

          _line_number++;
        }

      do{
          i = _buff.find_first_not_of(_dump);

          //debug
          //std::cout << "i = " << i << "\""  << _buff << "\"\n";
          if (i != std::string::npos){
              _buff = _buff.substr(i);
              break;
            }
          else if ( !_input -> eof() ){
              std::getline(*_input, _buff);
              _line_number++;
            }
          else{
              _buff = "";
              break;
            }
        } while ( true );

      if ( _input -> eof() && _buff.size()==0 )
        return "";

      //debug
      //std::cout << "\"" << _buff << "\"\n";

      STRING rez;
      i = _buff.find_first_of(_sepr + _dump);
      if (i==0){
          //debug
          //std::cout << "here1\n";

          rez = _buff.substr(0,1);
          _buff = _buff.substr(1);

        }
      else if (i != std::string::npos){
          //debug
          //std::cout << "here2\n";

          rez =  _buff.substr(0,i);
          _buff = _buff.substr(i);
        }
      else{
          //debug
          //std::cout << "here3\n";

          rez =  _buff;
          _buff = "";
        }
      return rez;
    }

    void back(STRING s){
      _buff = s + " " + _buff;
    }

    bool eof() const{
      return _input -> eof() && _buff == "";
    }

    int line() const{
      return _line_number;
    }

    STRING file() const{
      return _filename;
    }

  };

  // -----------------------------------------------------------

  STRING tolower(const STRING & s);
  // Make lowercase

  // -----------------------------------------------------------

  bool icompare(const STRING & s1, const STRING s2);
  // Case insensitive comparison of two strings
  // -----------------------------------------------------------

  void split(const STRING &s,
             std::vector<STRING> &elems,
             const STRING & delims = " \t");
  // fixme - not efficient!

  std::vector<STRING> split(const STRING &s, const STRING & delims=" \t");

  bool is_identifier(const STRING &s);

  // --------------------------------------------------------------------//

  int strnf(const STRING & s);

  // -------------------------------- string to type T convertor ----------------------------

  template<typename T>
  bool s2t(const STRING & s, T & val){
    std::basic_stringstream<CHAR,TRAITS> ss(s);
    ss >> val;

    //std::cout << "ss eof= " << ss.eof() << "\n";
    return (!ss.fail()) && ss.eof();
  }

  template<>
  bool s2t<bool>(const STRING & s, bool & val);

  // -------------------------------------------------------------

  template<typename T>
  STRING t2s(const T & val){
    std::basic_stringstream<CHAR,TRAITS> ss;
    ss << val;
    return ss.str();
  }

  template<>
  STRING t2s<bool>(const bool & val);

  // -------------------------------------------------------------


  std::string extract_base_name(std::string const & path);

  template<class REAL>
  qpp::vector3<REAL> vec_from_string(STRING &_inst,
                                      int idx = 0,
                                      int idy = 1,
                                      int idz = 2 ){
    std::vector<STRING> vfs_l = split(_inst);
    REAL vx, vy, vz = 0.0;
    s2t(vfs_l[idx], vx);
    s2t(vfs_l[idy], vy);
    s2t(vfs_l[idz], vz);
    return qpp::vector3<REAL>(vx, vy, vz);
  }

  void replace_string_inplace(std::string& subject, const std::string& search,
                            const std::string& replace);

  //https://www.bfilipek.com/2018/07/string-view-perf-followup.html
  std::vector<std::string_view> split_sv (std::string_view strv, std::string_view delims = " ");

  char *vec_str_to_char(const STRING & s);
  const char *vec_str_to_char_ref(const STRING & s);

  template<typename charT>
  struct ci_equal {
      ci_equal( const std::locale& loc ) : loc_(loc) {}
      bool operator() (charT ch1, charT ch2) {
          return std::tolower(ch1, loc_) == std::tolower(ch2, loc_);
      }
  private:
      const std::locale& loc_;
  };

  template<typename T>
  bool find_string_ci( const T& str1, const T& str2, const std::locale& loc = std::locale()) {
      typename T::const_iterator it = std::search( str1.begin(), str1.end(),
          str2.begin(), str2.end(), ci_equal<typename T::value_type>(loc) );
      if ( it != str1.end() ) return true/*it - str1.begin()*/;
      else return false/*-1*/; // not found
      return false;
  }
}

#endif
