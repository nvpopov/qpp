#ifndef QPP_PDF_NAME_REDUCER
#define QPP_PDF_NAME_REDUCER

#include <string>
#include <array>
#include <string_view>
#include <map>

struct pbd_name_reducer {
    static void eval_change(std::string &sv){
      const std::map<std::string, std::string> reducer_lookup = {
        {"CA"   , "C"},
        {"CB"   , "C"},
        {"CG"   , "C"},
        {"CG1"  , "C"},
        {"CG2"  , "C"},
        {"CH2"  , "C"},
        {"CZ"   , "C"},
        {"CZ2"  , "C"},
        {"CZ3"  , "C"},
        {"C1'"  , "C"},
        {"C2'"  , "C"},
        {"C3'"  , "C"},
        {"C4'"  , "C"},
        {"C5'"  , "C"},
        {"C6'"  , "C"},
        {"C7'"  , "C"},
        {"C1*"  , "C"},
        {"C2*"  , "C"},
        {"C3*"  , "C"},
        {"C4*"  , "C"},

        {"C2"   , "C"},
        {"C4"   , "C"},
        {"C4A"  , "C"},
        {"C5A"  , "C"},
        {"C6"   , "C"},
        {"C7"   , "C"},
        {"C7M"  , "C"},
        {"C8M"  , "C"},
        {"C8"   , "C"},
        {"C9"   , "C"},
        {"C9A"  , "C"},
        {"C10"  , "C"},

        {"NZ"   , "N"},
        {"N1"   , "N"},
        {"N3"   , "N"},
        {"NH1"  , "N"},
        {"NH2"  , "N"},
        {"N5"   , "N"},
        {"N10"   , "N"},

        {"OE1"  , "O"},
        {"OG1"  , "O"},
        {"OG"   , "O"},
        {"O2"   , "O"},
        {"O4"   , "O"},
        {"OH"   , "O"},
        {"OD1"  , "O"},
        {"OP"   , "O"},
        {"OD"   , "O"},
        {"O1'"  , "O"},
        {"O2'"  , "O"},
        {"O4'"  , "O"},
        {"O2*"  , "O"},
        {"O3*"  , "O"},

        {"HE"   , "H"},
        {"HE1"  , "H"},
        {"HN"   , "H"},
        {"HZ"   , "H"},
        {"HZ1"  , "H"},
        {"HZ2"  , "H"},
        {"HZ3"  , "H"},
        {"HH12" , "H"},
        {"HH11" , "H"},
        {"HH22" , "H"},
        {"HH21" , "H"},
        {"H1"   , "H"},
        {"H2"   , "H"},
        {"H3"   , "H"},
        {"H6"   , "H"},
        {"H7"   , "H"},
        {"H71"  , "H"},
        {"H72"  , "H"},
        {"H73"  , "H"},
        {"H2'"  , "H"},
        {"H3'"  , "H"},
        {"H5'"  , "H"},
        {"H6'"  , "H"},
        {"H81"  , "H"},
        {"H82"  , "H"},
        {"H83"  , "H"},
        {"H9"   , "H"},
        {"H11"  , "H"},
        {"H12"  , "H"},
        {"HH"   , "H"},
        {"HN5"  , "H"},
        {"HD21" , "H"},
        {"HD22" , "H"},
      };

      std::map<std::string, std::string>::const_iterator it = reducer_lookup.find(sv);
      if (it != reducer_lookup.cend()) sv = it->second;
    }
};




#endif
