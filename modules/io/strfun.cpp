#include <io/strfun.hpp>

namespace qpp{

  template<>
  bool s2t<bool>(const STRING & s, bool & val){
    STRING s1 = tolower(s);
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
  STRING t2s(const bool & val){
    return val ? "y" : "n";
  }

  // -----------------------------------------------------------
  // Make lowercase
  STRING tolower(const STRING & s){
    STRING ss = s;
    std::transform(ss.begin(), ss.end(), ss.begin(), ::tolower);
    return ss;
  }

  // -----------------------------------------------------------
  // Case insensitive comparison of two strings
  bool icompare(const STRING & s1, const STRING s2){
    return tolower(s1) == tolower(s2);
  }

  // -----------------------------------------------------------

  void split(const STRING &s,
             std::vector<STRING> &elems,
             const STRING & delims  ){
  // fixme - not efficient!

    SSTREAM ss(s);
    tokenizer tok(ss);
    tok.dump(delims);
    tok.separate("");
    elems.clear();

    // std::cerr << "split\n";

    do {
      STRING item = tok.get();

      //std::cerr << "split:\"" << item << "\"";
      if (item.size()==0)
        break;
      elems.push_back(item);
    } while(true);

  }

  // -----------------------------------------------------------

  std::vector<STRING> split(const STRING &s, const STRING & delims ){
    std::vector<STRING> elems;
    split(s, elems, delims);
    return elems;
  }

  // -----------------------------------------------------------

  int strnf(const STRING & s){
    std::basic_stringstream<CHAR,TRAITS> ss(s);
    STRING a;
    int nf = 0;
    for (nf=0; ss >> a; a!="") nf++;
    return nf;
  }

  // ----------------------------------------------------------

  bool is_identifier(const STRING &s){
    if (s=="")
      return false;

    STRING alp = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";
    STRING alpnum = alp + "0123456789";
    STRING s0 = s.substr(0,1);

    //std::cout << "s= " << s << " s0= " << s0 << "\n";

    if (s0.find_first_not_of(alp) !=  std::string::npos )
      return false;

    if (s.find_first_not_of(alpnum) !=  std::string::npos )
      return false;

    return true;
  }

  std::string extract_base_name(const STRING &path){
    return path.substr(path.find_last_of("/\\") + 1);
  }

  const char *vec_str_to_char_ref(const STRING &s){
     return s.c_str();
  }

  char *vec_str_to_char(const STRING & s){
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

}
