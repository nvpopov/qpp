#ifndef QPP_BASIC_GEOM_H
#define QPP_BASIC_GEOM_H

#include <algorithm>
#include <cmath>
#include <data/data.hpp>
#include <functional>
#include <geom/lace3d.hpp>
#include <numeric>
#include <symm/index.hpp>
#include <vector>

namespace qpp {

enum before_after { before = 0, after = 1 };

///cell type traits
template <typename T, typename = int>
struct cell_has_only_tsym : std::false_type { };

template <typename T>
struct cell_has_only_tsym <T, decltype((void) T::v, 0)> : std::true_type { };

template <typename T, typename = int>
struct cell_has_tsym_DIM : std::false_type { };

template <typename T>
struct cell_has_tsym_DIM <T, decltype((void) T::DIM, 0)> : std::true_type { };

///geometry_observer capabilities
const uint32_t geometry_observer_supports_default           = 0;
const uint32_t geometry_observer_supports_add               = 1 << 1;
const uint32_t geometry_observer_supports_insert            = 1 << 2;
const uint32_t geometry_observer_supports_change            = 1 << 3;
const uint32_t geometry_observer_supports_erase             = 1 << 4;
const uint32_t geometry_observer_supports_shadow            = 1 << 5;
const uint32_t geometry_observer_supports_reorder           = 1 << 6;
const uint32_t geometry_observer_supports_geom_destroy      = 1 << 7;
const uint32_t geometry_observer_supports_dim_change        = 1 << 8;
const uint32_t geometry_observer_supports_cell_change       = 1 << 9;
const uint32_t geometry_observer_supports_xfield_change     = 1 << 10;

/*!
 * \class geometry_observer
 * \brief Geometry updated objects
 * One geometry can maintain arbitrary number of "observers", i.e.
 * objects which need to know about the changes made to geometry.
 * Geometry will inform them all when atoms are added, inserted or removed
*/
template <class REAL>
struct geometry_observer {

  virtual uint32_t get_flags() = 0;
  virtual void added(before_after, const STRING_EX &,const vector3<REAL> &) = 0;
  virtual void inserted(int at, before_after, const STRING_EX &, const vector3<REAL> &) = 0;
  virtual void changed(int at, before_after, const STRING_EX &, const vector3<REAL> &) = 0;
  virtual void erased(int at, before_after) = 0;
  virtual void shaded(int at, before_after, bool) = 0;
  virtual void reordered(const std::vector<int> &, before_after) = 0;
  virtual void geometry_destroyed() = 0;
  virtual void dim_changed(before_after) = 0;
  virtual void cell_changed(before_after) = 0;
  virtual void xfield_changed(int at, int xid, before_after) = 0;

};

template <class REAL>
class basic_geometry {

protected:

  /// The dependent objects array
  std::vector<geometry_observer<REAL> *> p_observers;
  std::vector<uint32_t> p_cached_obs_flags;
  bool p_has_observers;

public:

  // ----------------------- Managing observers -----------------------

  void add_observer(geometry_observer<REAL> &d) {

    auto it = std::find(p_observers.begin(), p_observers.end(), &d);

    if (it != p_observers.end()) {
      p_has_observers = true;
      return;
    }

    p_observers.push_back(&d);
    p_cached_obs_flags.push_back(d.get_flags());
    p_has_observers = true;

  }

  void remove_observer(geometry_observer<REAL> &d) {
    auto i = p_observers.begin();

    while (i != p_observers.end()) {
      if (*i == &d) {
        p_observers.erase(i);
        auto obs_shift = std::distance(begin(p_observers), i);
        p_cached_obs_flags.erase(begin(p_cached_obs_flags) + obs_shift);
        break;
      }
      i++;
    }

    if (p_observers.size() == 0) p_has_observers = false;
  }

};

}

#endif
