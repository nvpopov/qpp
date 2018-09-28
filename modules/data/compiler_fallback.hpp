#ifndef QPP_COMPILER_FALLBACK
#define QPP_COMPILER_FALLBACK

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#if __cplusplus >= 201500
#include <string_view>
#else
#include <experimental/string_view>
namespace std{
  using std::experimental::string_view;
}
#endif

#if __cplusplus >= 201500
#include <optional>
#else
#include <experimental/optional>
namespace std{
  using std::experimental::optional;
}
#endif

#if __cplusplus < 201402L
///Version by Stephan T. Lavavej
namespace std {
  template<class T> struct _Unique_if {
      typedef unique_ptr<T> _Single_object;
  };

  template<class T> struct _Unique_if<T[]> {
      typedef unique_ptr<T[]> _Unknown_bound;
  };

  template<class T, size_t N> struct _Unique_if<T[N]> {
      typedef void _Known_bound;
  };

  template<class T, class... Args>
  typename _Unique_if<T>::_Single_object
  make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
  }

  template<class T>
  typename _Unique_if<T>::_Unknown_bound
  make_unique(size_t n) {
    typedef typename remove_extent<T>::type U;
    return unique_ptr<T>(new U[n]());
  }

  template<class T, class... Args>
  typename _Unique_if<T>::_Known_bound
  make_unique(Args&&...) = delete;
}
#endif

#endif
