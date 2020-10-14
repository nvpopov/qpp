#ifndef QPP_BASIC_GEOM_H
#define QPP_BASIC_GEOM_H

#include <algorithm>
#include <cmath>
#include <symm/index.hpp>
#include <symm/index_set.hpp>
#include <cassert>
#include <vector>
#include <numeric>
#include <functional>
#include <data/data.hpp>
#include <geom/lace3d.hpp>

namespace qpp {

enum class before_after {
  before = 0,
  after = 1
};

enum class geom_data_access_mode {
  allow_direct_access,
  disallow_direct_access
};

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
const uint32_t geometry_observer_supports_select            = 1 << 11;

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
  virtual void selected(atom_index_set_key &sel_at, before_after, bool state) = 0;
  virtual void dim_changed(before_after) = 0;
  virtual void cell_changed(before_after) = 0;
  virtual void xfield_changed(int at, int xid, before_after) = 0;
  virtual ~geometry_observer(){};
};

template <class REAL>
class basic_geometry {

protected:

  /// The dependent objects array
  std::vector<geometry_observer<REAL> *> p_observers;
  std::vector<uint32_t> p_cached_obs_flags;
  bool p_has_observers;

  geom_data_access_mode p_access_mode{geom_data_access_mode::allow_direct_access};

public:

  void set_geom_data_access_mode(geom_data_access_mode mode) {
    p_access_mode = mode;
  }

  geom_data_access_mode get_geom_data_access_mode() {
    return p_access_mode;
  }

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
    if (p_observers.size() == 0)
      p_has_observers = false;
  }

};

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

template <class REAL>
struct py_geometry_observer : geometry_observer<REAL> {

  using geometry_observer<REAL>::geometry_observer;

  uint32_t get_flags() override {
    PYBIND11_OVERLOAD_PURE(uint32_t, geometry_observer<REAL>, get_flags);
  };

  void added(before_after s, const STRING_EX &a, const vector3<REAL> &v) override {
    PYBIND11_OVERLOAD_PURE(void, geometry_observer<REAL>, added, s, a, v);
  }

  void inserted(int at, before_after s, const STRING_EX &a, const vector3<REAL> &v) override {
    PYBIND11_OVERLOAD_PURE(void, geometry_observer<REAL>, inserted, at, s, a, v);
  }

  void changed(int at, before_after s, const STRING_EX &a, const vector3<REAL> &v) override {
    PYBIND11_OVERLOAD_PURE(void, geometry_observer<REAL>, changed, at, s, a, v);
  }

  void erased(int at, before_after s) override {
    PYBIND11_OVERLOAD_PURE(void, geometry_observer<REAL>, erased, at, s);
  }

  void shaded(int at, before_after s, bool h) override {
    PYBIND11_OVERLOAD_PURE(void, geometry_observer<REAL>, shaded, at, s, h);
  }

  void reordered(const std::vector<int> &ord, before_after s) override {
    PYBIND11_OVERLOAD_PURE(void, geometry_observer<REAL>, reordered, ord, s);
  }

  void selected(atom_index_set_key &sel_at, before_after s, bool state) override {
    PYBIND11_OVERLOAD_PURE(void, geometry_observer<REAL>, selected, sel_at, s, state);
  }

  void dim_changed(before_after s) override {
    PYBIND11_OVERLOAD_PURE(void, geometry_observer<REAL>, dim_changed, s);
  }

  void cell_changed(before_after s) override {
    PYBIND11_OVERLOAD_PURE(void, geometry_observer<REAL>, cell_changed, s);
  }

  void xfield_changed(int xid, int at, before_after s) override {
    PYBIND11_OVERLOAD_PURE(void, geometry_observer<REAL>, xfield_changed, xid, at, s);
  }

};
#endif

}

#endif
