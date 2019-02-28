#include <iostream>
#include <variant>
#include <functional>
#include <map>
#include <tuple>
#include <geom/lace3d.hpp>
#include <symm/cell.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>

using namespace qpp;

template<class REAL>
class cls_pot_param_t {
  public:
    std::string name;
    REAL value;
};

template<class REAL>
using param_pack_t = std::vector<cls_pot_param_t<REAL>>;

/*
 * func proto
 */

template<class REAL>
using fn_2body_en_t =
typename std::function<REAL(REAL,
                            param_pack_t<REAL>&)>;

template<class REAL>
using fn_2body_gr_t =
typename std::function<vector3<REAL>(REAL,
                                     param_pack_t<REAL>&)>;

template<class REAL>
using fn_3body_en_t =
typename std::function<REAL(vector3<REAL>&,
                            vector3<REAL>&,
                            vector3<REAL>&,
                            param_pack_t<REAL>&)>;

template<class REAL>
using fn_3body_gr_t =
typename std::function<vector3<REAL>(vector3<REAL>&,
                                     vector3<REAL>&,
                                     vector3<REAL>&,
                                     param_pack_t<REAL>&)>;

/*
 *func collections proto
 */

template<class REAL>
using fn_en_t = std::variant<fn_2body_en_t<REAL>, fn_3body_en_t<REAL>>;

template<class REAL>
using fn_gr_t = std::variant<fn_2body_gr_t<REAL>, fn_3body_gr_t<REAL>>;

enum classic_potential_nbody : int {
  p2body = 0,
  p3body = 1
};

template<class REAL>
class clas_pot_t {
  public:
    clas_pot_t() {};
    classic_potential_nbody pot_type{classic_potential_nbody::p2body};
    param_pack_t<REAL> param_pack;
    std::vector<std::string> types;
    fn_en_t<REAL> fn_en;
    fn_gr_t<REAL> fn_gr;
    std::string pot_name;
    ~clas_pot_t() {
      fmt::print(std::cout, "Destructor called for {}\n", pot_name);
    }
};

template<class REAL>
using clas_pots = std::vector<clas_pot_t<REAL>>;

template<class REAL>
clas_pot_t<REAL> construct_fake_2body() {
  clas_pot_t<REAL> fake_2b;
  fake_2b.pot_type = classic_potential_nbody::p2body;
  fake_2b.fn_en = [](REAL r, param_pack_t<REAL>&){return 1 / r;};
  fake_2b.fn_gr = [](REAL r, param_pack_t<REAL>&){return 3 / r;};
  fake_2b.param_pack = {{"a", 2.0}, {"b", 3.0}, {"c", 4.0}};
  fake_2b.types = {"C", "C"};
  fake_2b.pot_name = "fake2dCC";
  return fake_2b;
}

template<class REAL>
clas_pot_t<REAL> construct_fake_2bodyCC2() {
  clas_pot_t<REAL> fake_2b;
  fake_2b.pot_type = classic_potential_nbody::p2body;
  fake_2b.fn_en = [](REAL r, param_pack_t<REAL>&){return 1 / r;};
  fake_2b.fn_gr = [](REAL r, param_pack_t<REAL>&){return 3 / r;};
  fake_2b.param_pack = {{"a", 2.0}, {"b", 1.0}, {"c", 1.0}};
  fake_2b.types = {"C", "C"};
  fake_2b.pot_name = "fake2dCC2";
  return fake_2b;
}

template<class REAL>
clas_pot_t<REAL> construct_fake_2bodyCH() {
  clas_pot_t<REAL> fake_2b;
  fake_2b.pot_type = classic_potential_nbody::p2body;
  fake_2b.fn_en = [](REAL r, param_pack_t<REAL>&){return 1 / r;};
  fake_2b.fn_gr = [](REAL r, param_pack_t<REAL>&){return 3 / r;};
  fake_2b.param_pack = {{"a", 4.0}, {"b", 2.0}, {"c", 4.0}};
  fake_2b.types = {"C", "H"};
  fake_2b.pot_name = "fake2dCH";
  return fake_2b;
}


template<class REAL, class CELL>
class calculator_t {

  public:

    geometry<REAL, CELL> *geom{nullptr};

    std::map<std::tuple<int, int>, clas_pots<REAL>> cache_pot_2body;
    std::map<std::tuple<int, int, int>, clas_pots<REAL>> cache_pot_3body;

    REAL energy{0.0};
    std::vector<vector3<REAL>> gradient;

    void compute_2body_terms() {

      std::cout << "Compute two body terms \n";

      for (size_t i = 0; i < geom->nat(); i++)
        for (size_t j = i; j < geom->nat(); j++)
          if (i != j) {

              int type1 = geom->type_table(i);
              int type2 = geom->type_table(j);

              int type_1 = std::min(type1, type2);
              int type_2 = std::max(type1, type2);

              int _i = i;
              int _j = j;

              if (type1 != type_1) {
                  _i = j;
                  _j = i;
                }

              auto it = cache_pot_2body.find(std::make_tuple(type_1, type_2));
              if (it != cache_pot_2body.end())
                for (auto &pot : it->second) {
                    fmt::print(std::cout,
                               "COMPUTE t1b = {}, t2b = {}, t1a = {}, t2a = {},"
                               " ib = {}, jb = {}, ia = {}, ja = {}, pot = {}, val={}\n",
                               type1,
                               type2,
                               type_1,
                               type_2,
                               i,
                               j,
                               _i,
                               _j,
                               pot.pot_name,
                               std::get<0>(pot.fn_en)((geom->pos(_i) - geom->pos(_j)).norm(),
                                                      pot.param_pack));
                  }

            }

    };

    void compute_3body_terms() {

      std::cout << "Compute three body terms \n";

    };

    void assign_geometry(geometry<REAL, CELL> *_geom) {
      geom = _geom;
    }

    void gather_potential(clas_pot_t<REAL> &&pot) {

      //build cache

      if (pot.pot_type == classic_potential_nbody::p2body && pot.types.size() == 2) {

          int type1 = geom->type(pot.types[0]);
          int type2 = geom->type(pot.types[1]);

          int type_1 = std::min(type1, type2);
          int type_2 = std::max(type1, type2);

          if (type1 == -1 || type2 == -1) return;

          std::cout << "gather pot, type_1 = " << type_1 << ", type_2 = " << type_2 << std::endl;

          auto &pots = cache_pot_2body[std::make_tuple(type_1, type_2)];
          pots.emplace_back(pot);

        }

    }

};


int main () {

  std::cout << "Alive\n";
  geometry<double, periodic_cell<double>> g(0);

  calculator_t<double, periodic_cell<double>> calc;
  calc.geom = &g;

  g.add("C", {0, 0, 0});
  g.add("C", {0, 1, 0});
  g.add("H", {0, 0, 3});
  g.add("C", {4, 4, 0});
  g.add("H", {0, 5, 5});

  calc.gather_potential(construct_fake_2body<double>());
  calc.gather_potential(construct_fake_2bodyCH<double>());
  calc.gather_potential(construct_fake_2bodyCC2<double>());

  std::cout<<"Total types = " << g.n_atom_types() << "\n";

  calc.compute_2body_terms();
  calc.compute_3body_terms();
  return 0;

}
