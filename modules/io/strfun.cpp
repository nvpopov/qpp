#include <io/strfun.hpp>

namespace qpp{

  template<>
  bool s2t<bool>(const STRING_EX & s, bool & val){
    STRING_EX s1 = tolower(s);
    if ( (s1 == "y") || (s1 == "yes") || (s1 == "true") || (s1 == "1")){
        val = true;
        return true;
      }
    else if ( (s1 == "n") || (s1 == "no") || (s1 == "false") || (s1 == "0")){
        val = false;
        return true;
      }
    else{
        return false;
      }
  }

  // -----------------------------------------------------------

  template<>
  STRING_EX t2s(const bool & val){
    return val ? "y" : "n";
  }

  // -----------------------------------------------------------
  // Make lowercase
  STRING_EX tolower(const STRING_EX & s){
    STRING_EX ss = s;
    std::transform(ss.begin(), ss.end(), ss.begin(), ::tolower);
    return ss;
  }

  // -----------------------------------------------------------
  // Case insensitive comparison of two strings
  bool icompare(const STRING_EX & s1, const STRING_EX s2){
    return tolower(s1) == tolower(s2);
  }

  // -----------------------------------------------------------

  void split(const STRING_EX &s,
             std::vector<STRING_EX> &elems,
             const STRING_EX & delims  ){
  // fixme - not efficient!

    SSTREAM ss(s);
    tokenizer tok(ss);
    tok.dump(delims);
    tok.separate("");
    elems.clear();

    // std::cerr << "split\n";

    do {
      STRING_EX item = tok.get();

      //std::cerr << "split:\"" << item << "\"";
      if (item.size()==0)
        break;
      elems.push_back(item);
    } while(true);

  }

  // -----------------------------------------------------------

  std::vector<STRING_EX> split(const STRING_EX &s, const STRING_EX & delims ){
    std::vector<STRING_EX> elems;
    split(s, elems, delims);
    return elems;
  }

  // -----------------------------------------------------------

  int strnf(const STRING_EX & s){
    std::basic_stringstream<CHAR_EX,TRAITS> ss(s);
    STRING_EX a;
    int nf = 0;
    for (nf=0; ss >> a; a!="") nf++; // TODO: inequality comparison result unused
    return nf;
  }

  // ----------------------------------------------------------

  bool is_identifier(const STRING_EX &s){
    if (s=="")
      return false;

    STRING_EX alp = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";
    STRING_EX alpnum = alp + "0123456789";
    STRING_EX s0 = s.substr(0,1);

    //std::cout << "s= " << s << " s0= " << s0 << "\n";

    if (s0.find_first_not_of(alp) !=  std::string::npos )
      return false;

    if (s.find_first_not_of(alpnum) !=  std::string::npos )
      return false;

    return true;
  }

  std::string extract_base_name(const STRING_EX &path){
    return path.substr(path.find_last_of("/\\") + 1);
  }

  const char *vec_str_to_char_ref(const STRING_EX &s){
     return s.c_str();
  }

  char *vec_str_to_char(const STRING_EX & s){
     char *pc = new char[s.size()+1];
     std::strcpy(pc, s.c_str());
     return pc;
  }

  std::vector<std::string_view> split_sv (std::string_view strv, std::string_view delims) {

      std::vector<std::string_view> output;
      size_t first = 0;

      while (first < strv.size()){
          const auto second = strv.find_first_of(delims, first);
          if (first != second) output.emplace_back(strv.substr(first, second-first));
          if (second == std::string_view::npos) break;
          first = second + 1;
      }

      return output;
  }

  void replace_string_inplace(std::string &subject, const std::string &search,
                              const std::string &replace) {
       size_t pos = 0;
       while ((pos = subject.find(search, pos)) != std::string::npos) {
            subject.replace(pos, search.length(), replace);
            pos += replace.length();
       }
   }

}
