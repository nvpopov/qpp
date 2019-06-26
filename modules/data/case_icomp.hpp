#ifndef QPP_CASE_INSENSITIVE_COMP
#define QPP_CASE_INSENSITIVE_COMP

#ifndef _WIN32
#include <strings.h>
#endif

#ifdef _MSC_VER
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif

#include <map>
#include <string>

namespace qpp {

  template<typename T>
  struct case_icomp {
      bool operator()(const T& a, const T& b) const noexcept {
        return ::strcasecmp(a.c_str(), b.c_str()) < 0;
      }
  };

}

#endif
