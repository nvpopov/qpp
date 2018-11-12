#ifndef QPP_CASE_INSENSITIVE_COMP
#define QPP_CASE_INSENSITIVE_COMP

#include <strings.h>
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
