#ifndef QPP_TWS_TREE_H
#define QPP_TWS_TREE_H

#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <utility>
#include <set>
#include <algorithm>
#include <cmath>
#include <array>
#include <type_traits>

#include <cassert>
#include <string>

#include <iostream>
#include <ostream>
#include <fmt/ostream.h>

#include <geom/xgeom.hpp>
#include <geom/ngbr.hpp>
#include <data/symmetric_key.hpp>
#include <data/ptable.hpp>
#include <geom/aabb.hpp>
#include <geom/ray.hpp>
#include <geom/primitive_intersections.hpp>
#include <data/ptable.hpp>

#define TWS_TREE_DEBUG

namespace qpp{

template<typename INT_TYPE>
inline INT_TYPE enc_tws_idx(const INT_TYPE a, const INT_TYPE b, const INT_TYPE c) {
  return (a * 9)+ (b * 3) + c + 13;
}

template<typename POL_REAL>
struct query_ray_add_all {
  static bool can_add(vector3<POL_REAL> &pos, index &idx, const int DIM = 0) {
    return true;
  }
};

template<typename POL_REAL>
struct query_ray_add_ignore_img {
  static bool can_add(vector3<POL_REAL> &pos, index &idx, const int DIM = 0) {
    return idx.is_zero();
  }
};

/// tws tree node forward declaration
template<typename REAL, typename AINT>
struct tws_node_t;

/// data to store in twstree
template<typename REAL, typename AINT = size_t>
struct tws_node_cnt_t {
  AINT m_atm;
  index m_idx;
  tws_node_cnt_t(const AINT atm, const index idx) noexcept {
    m_atm = atm;
    m_idx = idx;
  }
};

/// data to store in rtree
template<typename REAL, typename AINT>
struct tws_node_content_bonds_t {
  AINT m_atm;
  index m_idx;
  matrix4<REAL> m_mat_model;
  tws_node_content_bonds_t(const AINT atm, const index idx) noexcept {
    m_atm = atm; m_idx = idx;
  }
};

/// \brief The imaginary_atom struct
template<typename REAL, typename AINT>
struct img_atom_t {
  AINT m_atm;
  index m_idx;
  std::vector<tws_node_cnt_t<REAL, AINT>> m_img_bonds;
  img_atom_t(const AINT atm, const index idx) noexcept {
    m_atm = atm;
    m_idx = idx;
  }
};

template<typename REAL, typename AINT>
struct tws_query_data_t {
  AINT m_atm;
  index m_idx;
  REAL m_dist;
  tws_query_data_t(const AINT atm, const index idx, const REAL dist = 1000.0f) noexcept {
    m_atm = atm; m_idx = idx; m_dist = dist;
  }
  bool operator == (const tws_query_data_t<REAL, AINT> &a){
    return (m_idx == a.idx) && (m_atm == a.atm);
  }
};

template<typename REAL, typename AINT>
bool tws_query_data_sort_by_dist(const tws_query_data_t<REAL, AINT> &a,
                                 const tws_query_data_t<REAL, AINT> &b) {
  return a.m_dist < b.m_dist;
}

/// \brief The tws_node struct
template<typename REAL, typename AINT>
struct tws_node_t {

  tws_node_t<REAL, AINT>* parent;
  aabb_3d_t<REAL> m_bb;
  std::vector<tws_node_cnt_t<REAL, AINT>> m_content;
  std::array<tws_node_t<REAL, AINT>*, 27> m_sub_nodes {{nullptr}};
  int m_tot_childs{0};

  tws_node_t() noexcept {}

  void rm_cnt_by_id(const AINT atm) {
    for (auto it = m_content.begin(); it != m_content.end();){
      if(it->m_atm == atm)
        it = m_content.erase(it);
      else
        ++it;
    }
  }

  void rm_cnt_idx_store(const AINT atm, std::vector<index> &idx_vec) {
    for (auto it = m_content.begin(); it != m_content.end();){
      if(it->m_atm == atm) {
        idx_vec.push_back(it->m_idx);
        it = m_content.erase(it);
      } else {
        ++it;
      }
    }
  }

};

template<typename REAL, typename AINT>
struct atom_node_lookup_t {
  index m_idx;
  tws_node_t<REAL, AINT> *m_node;
  atom_node_lookup_t(const index idx, tws_node_t<REAL, AINT> *node) {
    if (!node)
      throw std::runtime_error("invalid node");
    m_idx = idx; m_node = node;
  }
};

template<typename REAL>
struct bonding_table_record_t {
  REAL m_bonding_dist{0.0f};
  bool m_override{false};
  bool m_enabled{false};
};

template<typename REAL, typename AINT>
struct bonding_table_t {

  std::unordered_map<qpp::sym_key<AINT>, bonding_table_record_t<REAL>, sym_key_hash<AINT>> m_dist;
  std::map<AINT, REAL> m_max_dist;
  std::set<AINT> m_has_types;

  template<typename CELL>
  void init_for_type_pair(geometry<REAL, CELL> *geom, const int atype1, const int atype2,
                          bool overwrite_existing = false) {
    if (!geom)
      throw std::runtime_error("invalid geom");
    if (atype1 >= geom->n_types() || atype2 >= geom->n_types())
      return;
    sym_key<AINT> sk{atype1, atype2};
    auto dist_iter = m_dist.find(sk);
    if (dist_iter != end(m_dist) && !overwrite_existing) //record exists - do nothing
      return;
    auto table_idx1  = ptable::number_by_symbol(geom->atom_of_type(atype1));
    auto table_idx2  = ptable::number_by_symbol(geom->atom_of_type(atype2));
    if (table_idx1 && table_idx2) {
      auto bond_rad_1 = ptable::cov_rad_by_number(*table_idx1);
      auto bond_rad_2 = ptable::cov_rad_by_number(*table_idx2);
      if (bond_rad_1 && bond_rad_2) {
        m_dist[sk].m_bonding_dist = *bond_rad_1 + *bond_rad_2;
        m_dist[sk].m_enabled = true;
        m_max_dist[atype1] = std::max(m_max_dist[atype1], m_dist[sk].m_bonding_dist);
        m_max_dist[atype2] = std::max(m_max_dist[atype2], m_dist[sk].m_bonding_dist);
        m_has_types.insert(atype1);
        m_has_types.insert(atype2);
      } else {
        m_dist[sk].m_enabled = false;
      }
    }
  }

  template<typename CELL>
  void init_for_single_type(geometry<REAL, CELL> *geom, const int atype) {
    if (!geom)
      throw std::runtime_error("invalid geom");
    if (atype >= geom->n_types())
      return;
    auto hastype_iter = m_has_types.find(atype);
    if (hastype_iter != end(m_has_types))
      return;
    for (AINT i = 0; i < geom->n_atom_types(); i++)
      init_for_type_pair(geom, i, atype, true);
  }

  template<typename CELL>
  void init_default(geometry<REAL, CELL> *geom) {
    if (!geom)
      throw std::runtime_error("invalid geom");
    for (AINT i = 0; i < geom->n_atom_types(); i++)
      for (AINT j = i; j <  geom->n_atom_types(); j++)
        init_for_type_pair(geom, i, j, true);
  }

  void update_dist_for_pair(const AINT i, const AINT j, const REAL new_dist) {
    auto it = m_dist.find(sym_key<AINT>{i,j});
    if (it != m_dist.end()) {
      it->second.m_bonding_dist = new_dist;
      it->second.m_override = true;
      if (i < m_max_dist.size() && j < m_max_dist.size()) {
        m_max_dist[i] = std::max(m_max_dist[i], new_dist);
        m_max_dist[j] = std::max(m_max_dist[j], new_dist);
      }
    }
  }

  void update_pair_max_dist(const AINT i, const AINT j) {
    auto it = m_dist.find(sym_key<AINT>(i,j));
    if (it != m_dist.end()) {
      REAL dist = it->second.m_bonding_dist;
      m_max_dist[i] = std::max(m_max_dist[i], dist);
      m_max_dist[j] = std::max(m_max_dist[j], dist);
    }
  }

  void update_pair_max_dist_all() {
    for (auto& record : m_dist)
      update_pair_max_dist(record.first.m_a, record.first.m_b);
  }

};

/// \brief action bitmask for use in do_action
const uint32_t act_clear_tree        = 1 << 0;
const uint32_t act_clear_ntable      = 1 << 1;
const uint32_t act_clear_img_ntable  = 1 << 2;
const uint32_t act_clear_img         = 1 << 3;
const uint32_t act_clear_all         = 1 << 4;
const uint32_t act_rebuild_tree      = 1 << 5;
const uint32_t act_rebuild_ntable    = 1 << 6;
const uint32_t act_build_tree        = 1 << 7;
const uint32_t act_build_ntable      = 1 << 8;
const uint32_t act_rebuild_all       = 1 << 9;
const uint32_t act_build_all         = 1 << 10;
const uint32_t act_check_consistency = 1 << 11;
const uint32_t act_check_root        = 1 << 12;
const uint32_t act_lock              = 1 << 13;
const uint32_t act_unlock            = 1 << 14;
const uint32_t act_lock_img          = 1 << 15;
const uint32_t act_unlock_img        = 1 << 16;

/// aux tws tree implementation
template <class REAL, class CELL = periodic_cell<REAL>, typename AINT = size_t >
class tws_tree_t : public geometry_observer<REAL> {

public:

  REAL m_guess_rect_size{8.0};
  REAL m_min_tws_volume{150.0};
  REAL m_cell_within_eps{0.09};

  xgeometry<REAL, CELL>                                     *geom{nullptr};
  tws_node_t<REAL, AINT>                                    *root{nullptr};
  std::vector<tws_node_t<REAL, AINT>*>                      m_flat_view;
  std::vector<std::vector<atom_node_lookup_t<REAL, AINT>>>  m_atom_node_lookup;

  bool m_make_dirty_dist_map{true};
  bool m_auto_bonding{false};
  bool m_auto_build{true};
  bool m_build_img_atoms_bonds{true};
  bool m_keep_img_atoms{false};
  bool m_tree_is_dirty{false};
  bool m_atoms_existence_is_broken{false};
  bool m_rebuild_all_on_erase{true};
  bool m_rebuild_all_on_insert{true};

  std::vector<img_atom_t<REAL, AINT>>                       m_img_atoms;
  std::vector<std::vector<tws_node_cnt_t<REAL, AINT>>>      m_ngb_table;
  bonding_table_t<REAL, AINT>                               m_bonding_table;

  explicit tws_tree_t(xgeometry<REAL, CELL> &g) {
    geom = &g;
    geom->add_observer(*this);
  }

  ~tws_tree_t() {
    if (geom)
      geom->remove_observer(*this);
  }

  std::optional<AINT> find_img_atom(const AINT atm, const index idx) {
    auto find_lambda = [&atm, &idx](const auto &el){return el.m_atm == atm && el.m_idx == idx;};
    auto iter = std::find_if(begin(m_img_atoms), end(m_img_atoms), find_lambda);
    return iter != end(m_img_atoms) ?
           std::optional<AINT>(std::distance(begin(m_img_atoms), iter)) :
           std::nullopt;
  }

  /**
   * @brief find_img_atom_by_id
   * @param atm
   * @return
   */
  std::optional<AINT> find_img_atom_by_id(const AINT atm) {
    auto find_lambda = [&atm](const auto &el){return el.m_atm == atm;};
    auto iter = std::find_if(begin(m_img_atoms), end(m_img_atoms), find_lambda);
    return iter != end(m_img_atoms) ?
           std::optional<AINT>(std::distance(begin(m_img_atoms), iter)) :
           std::nullopt;
  }

  std::vector<AINT> find_all_occurences_of_atom_by_id(const AINT atm) {
    std::vector<AINT> result;
    AINT i{0};
    auto fe_lambda = [&result, &atm, &i] (auto &el) {
      if (el.m_atm == atm)
        result.push_back(i);
      i++;
    };
    std::for_each(begin(m_img_atoms), end(m_img_atoms), fe_lambda);
    return result;
  }

  void rebuild_after_erase(const AINT changed_atom) {
    // Before erase we have : 0 1 2 3 4 5 6 7 8 num=9
    // After erase we have  : 0 1 2 3 4 6 7 8 num=8
    // We need to change all data for 6 7 8 to 5 6 7
    // All data means m_img_atoms and ngbs and atoms inside tree

    if (changed_atom >= m_atom_node_lookup.size())
      throw std::runtime_error("Ill formed atom-node lookup table...");

    //update tree
    auto nd_cnt_erase_lambda = [changed_atom](auto &el){ return el.m_atm == changed_atom;};
    auto nd_cnt_update_anum = [changed_atom](auto &el){
      if (el.m_atm > changed_atom)
        el.m_atm -= 1;
    };
    for (int i = changed_atom + 1; i < geom->nat(); i++) {
      auto &ndlkp = m_atom_node_lookup[i];
      for (atom_node_lookup_t<REAL, AINT>& ndlkp_inst : ndlkp) {
        if (auto nd = ndlkp_inst.m_node; nd) {
          auto &nd_cnt = nd->m_content;
          //erase first
          nd_cnt.erase(std::remove_if(begin(nd_cnt), end(nd_cnt), nd_cnt_erase_lambda),end(nd_cnt));
          //update indicies next
          std::for_each(begin(nd_cnt), end(nd_cnt), nd_cnt_update_anum);
        }
      }
    }
    //we dont need lookup for <changed_atom>
    m_atom_node_lookup.erase(changed_atom);

    //update ngb table

    //update img atoms
  }

  void rebuild_after_insert(const AINT changed_atom) {
    //
  }

  void check_img_eps() {
    auto const max_cell_v_l_boundary = 25.0;
    if (!geom)
      return;
    if (geom->get_DIM() == 0)
      return;
    REAL max_cell_v_l{0};
    for (size_t i = 0; i < geom->get_DIM(); i++)
      max_cell_v_l = std::max(max_cell_v_l, geom->cell.v[i].norm());
    if (max_cell_v_l > max_cell_v_l_boundary)
      m_cell_within_eps = 0.001;
  }

  /// \brief do_action
  /// \param action bitmask for action
  void do_action(const uint32_t action) {
    if (action & act_lock) {
      m_auto_bonding = false;
      m_auto_build = false;
    }

    if (action & act_unlock) {
      m_auto_bonding = true;
      m_auto_build = true;
    }

    if (action & act_lock_img) {
      m_keep_img_atoms = true;
    }

    if (action & act_unlock_img) {
      m_keep_img_atoms = false;
    }

    if (action & act_check_root) {
      if (!root) {
        root = new tws_node_t<REAL, AINT>();
        m_flat_view.push_back(root);
        root->m_bb.fill_guess(m_guess_rect_size);
        if (root->m_bb.volume() < m_min_tws_volume)
          root->m_bb.fill_guess(pow(m_min_tws_volume, 1/3.0));
      }
    }

    if (action & act_check_consistency) {
      if (m_ngb_table.size() != geom->nat())
        m_ngb_table.resize(geom->nat());
      if (m_atom_node_lookup.size() != geom->nat())
        m_atom_node_lookup.resize(geom->nat());
    }

    if (action & act_clear_ntable) {
      for (auto &per_atom : m_ngb_table)
        per_atom.clear();
      m_ngb_table.clear();
    }

    if (action & act_clear_img_ntable)
      for (auto &per_img_atom : m_img_atoms)
        per_img_atom.m_img_bonds.clear();

    if (action & act_clear_img)
      m_img_atoms.clear();

    if (action & act_clear_tree) {
      for (auto *node : m_flat_view) {
        delete node;
      }
      root = nullptr;
      m_flat_view.clear();
      m_atom_node_lookup.clear();
    }

    if (action & act_clear_all) {
      do_action(act_clear_img);
      do_action(act_clear_ntable);
      do_action(act_clear_tree);
    }

    if (action & act_rebuild_tree) {
      do_action(act_clear_img);
      do_action(act_clear_tree);
      do_action(act_build_tree);
    }

    if (action & act_rebuild_ntable) {
      do_action(act_clear_img_ntable);
      do_action(act_clear_ntable);
      do_action(act_build_ntable);
    }

    if (action & act_build_tree) {
      check_img_eps();
      manual_build();
    }

    if (action & act_build_ntable) {
      check_img_eps();
      find_all_neighbours();
    }

    if (action & act_rebuild_all) {
      do_action(act_rebuild_tree);
      do_action(act_rebuild_ntable);
    }

    if (action & act_build_all) {
      do_action(act_build_tree);
      do_action(act_build_ntable);
    }
  }

  void clr_bond_real_img(const AINT atm1, const AINT atm2, const index idx2) {
    for (auto it = m_ngb_table[atm1].begin(); it != m_ngb_table[atm1].end(); )
      if (it->m_atm == atm2 && it->m_idx == idx2)
        m_ngb_table[atm1].erase(it);
      else
        ++it;
  }

  void clr_bond_img_real(const AINT img_atom_id, const AINT atm2, const index idx2) {
    for (auto it = m_img_atoms[img_atom_id].begin(); it != m_img_atoms[img_atom_id].end();)
      if (it->m_atm == atm2 && it->m_idx == idx2)
        m_img_atoms[img_atom_id].erase(it);
      else
        ++it;
  }

  void clr_bond_img_real(const AINT img_atom_id, const int atm2) {
    for (auto it = m_img_atoms[img_atom_id].m_img_bonds.begin();
         it != m_img_atoms[img_atom_id].m_img_bonds.end(); )
      if (it->m_atm == atm2)
        m_img_atoms[img_atom_id].m_img_bonds.erase(it);
      else
        ++it;
  }

  void clr_atom_bond_data(const AINT atm) {
    for(auto &bond : m_ngb_table[atm])
      if (bond.m_idx.is_zero() || geom->get_DIM() == 0) {
        clr_atom_pair_bond_data(bond.m_atm, atm);
      } else {
        std::optional<AINT> img_id = find_img_atom(bond.m_atm, bond.m_idx);
        if (img_id)
          clr_bond_img_real(*img_id, atm);
      }
    m_ngb_table[atm].clear();
  }

  void clr_atom_pair_bond_data(const AINT atm1, const AINT atm2) {
    if (m_ngb_table[atm1].size() > 0) {
      auto new_end = std::remove_if(m_ngb_table[atm1].begin(), m_ngb_table[atm1].end(),
                                    [&atm2](tws_node_cnt_t<REAL, AINT> & bonds) {
                                      return bonds.m_atm == atm2;
                                    });
      m_ngb_table[atm1].erase(new_end);
    }
  }

  std::vector<index> clr_atom_from_tree(const AINT atm) {

    std::vector<index> image_idx;

    if (geom->get_DIM() == 0 && m_atom_node_lookup[atm].size() > 0)
      m_atom_node_lookup[atm][0].m_node->rm_cnt_by_id(atm);

    if (geom->get_DIM() > 0) {

      //remove 0,0,0 and c1,c2,c3 atoms from tree
      for (auto& at_node : m_atom_node_lookup[atm])
        at_node.m_node->rm_cnt_idx_store(atm, image_idx);

      //iterate over imaginary atoms, store secondary imaginary atom, erase required atom
      std::vector<std::tuple<AINT, index> > pair_img_atoms;
      for (auto it = m_img_atoms.begin(); it != m_img_atoms.end();)
        if (it->m_atm == atm) {
          for(auto &nc : it->m_img_bonds) {
            if (!nc.m_idx.is_zero()) {
              pair_img_atoms.push_back(std::tuple<AINT, index>(nc.m_atm, nc.m_idx));
            } else {
              clr_bond_real_img(nc.m_atm, it->m_atm, it->m_idx);
            }
          }
          it = m_img_atoms.erase(it);
        } else {
          ++it;
        }

      //delete bonds from paired imaginary atoms
      for (auto &pair : pair_img_atoms) {
        std::optional<AINT> paired_img_id = find_img_atom(std::get<0>(pair), std::get<1>(pair));
        if (paired_img_id){
          for (auto it = m_img_atoms[*paired_img_id].m_img_bonds.begin();
               it != m_img_atoms[*paired_img_id].m_img_bonds.end();) {
            if (it->m_atm == atm)
              it = m_img_atoms[*paired_img_id].m_img_bonds.erase(it);
            else
              ++it;
          }
        }
      }

    }
    //tws_node_t<REAL> *node = atom_node_lookup[]
    m_atom_node_lookup[atm].clear();

    return image_idx;
  }

  void apply_shift(const vector3<REAL> vec_shift) {
    for (auto *node : m_flat_view) {
      node->m_bb.min += vec_shift;
      node->m_bb.max += vec_shift;
    }
  }

  void apply_visitor(std::function<void(tws_node_t<REAL, AINT>*, int)> f) {
    traverse_apply_visitor(root, 0, f);
  }

  void traverse_apply_visitor(tws_node_t<REAL, AINT> *cur_node, int deep_level,
                              std::function<void(tws_node_t<REAL, AINT>*, int)> f) {
    if (!root)
      return;
    f(cur_node, deep_level);
    for (auto* child : cur_node->m_sub_nodes)
      if (child)
        traverse_apply_visitor(child, deep_level + 1, f);
  }

  template<typename adding_result_policy = query_ray_add_all<REAL> >
  void query_ray(ray_t<REAL> &_ray,
                 std::vector<tws_query_data_t<REAL, AINT> > &res,
                 const std::unordered_set<size_t> &hidden_types,
                 REAL scale_factor = 0.25,
                 bool hide_by_field = false,
                 int xgeom_hide_field_id = 6) {
    if (!root)
      return;
    traverse_query_ray<adding_result_policy>(root,
                                             _ray,
                                             res,
                                             hidden_types,
                                             scale_factor,
                                             hide_by_field,
                                             xgeom_hide_field_id);
  }

  template<typename adding_result_policy>
  void traverse_query_ray(tws_node_t<REAL, AINT> *cur_node,
                          ray_t<REAL> &_ray,
                          std::vector<tws_query_data_t<REAL, AINT> > &res,
                          const std::unordered_set<size_t> &hidden_types,
                          const REAL scale_factor,
                          bool hide_by_field,
                          int xgeom_hide_field_id) {

    if (!cur_node)
      return;

    if (ray_aabb_test(_ray, cur_node->m_bb)) {

      if (cur_node->m_tot_childs > 0) {
        for (auto ch_node : cur_node->m_sub_nodes)
          if (ch_node)
            traverse_query_ray<adding_result_policy>(ch_node,
                                                     _ray,
                                                     res,
                                                     hidden_types,
                                                     scale_factor,
                                                     hide_by_field,
                                                     xgeom_hide_field_id);
      } else {
        for (auto &nc : cur_node->m_content) {
          auto ap_idx = ptable::number_by_symbol(geom->atom(nc.m_atm));

          //TODO: move magic aRadius
          REAL atom_rad = 1.0f;
          if (ap_idx)
            atom_rad = ptable::get_inst()->arecs[*ap_idx-1].m_radius * scale_factor;
          REAL stored_dist = 0.0;
          vector3<REAL> test_pos = geom->pos(nc.m_atm, nc.m_idx);
          REAL ray_hit_dist = ray_sphere_test(&_ray, test_pos, atom_rad);
          bool ray_hit = ray_hit_dist > -1.0f;

          bool atom_hidden = false;
          if (!hidden_types.empty()) {
            auto it = hidden_types.find(geom->type_of_atom(nc.m_atm));
            if (it != hidden_types.end())
              atom_hidden = true;
          }

          if (ray_hit
              && adding_result_policy::can_add(test_pos, nc.m_idx, geom->get_DIM())
              && !atom_hidden
              && (!hide_by_field
                  || !geom->template xfield<bool>(xgeom_hide_field_id, nc.m_atm)
                  || !xgeom_hide_field_id))
            res.push_back(tws_query_data_t<REAL, AINT>(nc.m_atm, nc.m_idx, ray_hit_dist));

        }
      }
    }

    else return ;

  }

  void query_sphere(const REAL sph_r, const vector3<REAL> sph_cnt,
                    std::vector<tws_node_cnt_t<REAL, AINT>> &res) {
    if (!root)
      return;
    traverse_query_sphere(root, sph_r, sph_cnt, res);
  }

  void traverse_query_sphere(tws_node_t<REAL, AINT> *cur_node,
                             const REAL &sph_r, const vector3<REAL> &sph_cnt,
                             std::vector<tws_node_cnt_t<REAL, AINT>> &res) {
    if (cur_node->m_bb.test_sphere(sph_r, sph_cnt)) {
      for (auto child : cur_node->m_sub_nodes)
        if (child)
          traverse_query_sphere(child, sph_r, sph_cnt, res);
      for (auto &cnt : cur_node->m_content)
        if ((sph_cnt - geom->pos(cnt.m_atm, cnt.m_idx)).norm() <= sph_r)
          res.push_back(tws_node_cnt_t<REAL, AINT>(cnt.m_atm, cnt.m_idx));
    }
  }

  //
  void insert_object_to_tree(const AINT atm) {
    for (iterator i(index::D(geom->get_DIM()).all(-1), index::D(geom->get_DIM()).all(1));
         !i.end(); i++)
      if (i.is_zero())
        insert_object_to_tree(atm, i);
      else if ((geom->nat() < 500 && geom->cell.within_eps_b(geom->pos(atm, i), m_cell_within_eps))
               || m_keep_img_atoms)
        insert_object_to_tree(atm, i);
  }

  void insert_object_to_tree(const AINT atm, const index idx) {
    do_action(act_check_root);
    if (m_atom_node_lookup.size() != geom->nat())
      m_atom_node_lookup.resize(geom->nat());
    while (!(point_aabb_test(geom->pos(atm, idx), root->m_bb))) {
      grow_tws_root(atm, idx);
#ifdef TWS_TREE_DEBUG
      fmt::print("rootgrow p = {}, {}, {}\n", geom->pos(atm, idx)[0],
                                              geom->pos(atm, idx)[1],
                                              geom->pos(atm, idx)[2]);
#endif
    }
    traverse_insert_object_to_tree(root, atm, idx);
  }

  bool traverse_insert_object_to_tree(tws_node_t<REAL, AINT> *cur_node,
                                      const AINT atm, const index & idx) {

    vector3<REAL> p = geom->pos(atm, idx);
    vector3<REAL> cn_size = cur_node->m_bb.max - cur_node->m_bb.min;
    vector3<REAL> cn_center = cur_node->m_bb.center();

    bool in_cur_rect = point_aabb_test(p, cur_node->m_bb);
    if (!in_cur_rect)
      return false;

    if (in_cur_rect) {
      // point in box and we reach minimum volume
      if (cur_node->m_bb.volume() / 27.0 <= m_min_tws_volume){
        push_data_to_tws_node(cur_node, atm, idx);
        return true;
      }
      //it is necessary to determine the indexes of the point
      int i_x = -1 + int((p[0]-cur_node->m_bb.min[0])/(cn_size[0]/3));
      int i_y = -1 + int((p[1]-cur_node->m_bb.min[1])/(cn_size[1]/3));
      int i_z = -1 + int((p[2]-cur_node->m_bb.min[2])/(cn_size[2]/3));
      int nidx = enc_tws_idx(i_x, i_y, i_z);
      if (cur_node->m_sub_nodes[nidx] == nullptr) {
        tws_node_t<REAL, AINT> *new_node = new tws_node_t<REAL, AINT>();
        m_flat_view.push_back(new_node);
        //define the 0,0,0 max min
        vector3<REAL> z_min = cur_node->m_bb.min + cn_size / 3;
        vector3<REAL> z_max = cur_node->m_bb.max - cn_size / 3;
        new_node->m_bb.min = z_min + vector3<REAL>(i_x * cn_size[0]/ 3,
                                                   i_y * cn_size[1]/ 3,
                                                   i_z * cn_size[2]/ 3);
        new_node->m_bb.max = z_max + vector3<REAL>(i_x * cn_size[0]/ 3,
                                                   i_y * cn_size[1]/ 3,
                                                   i_z * cn_size[2]/ 3);
        cur_node->m_sub_nodes[nidx] = new_node;
        cur_node->m_tot_childs+=1;
      }
      traverse_insert_object_to_tree(cur_node->m_sub_nodes[nidx], atm, idx);
    }

    return false;

  }

  void push_data_to_tws_node(tws_node_t<REAL, AINT> *cur_node, const AINT atm, const index idx) {
    //pass any atom with any index to tws-tree
    cur_node->m_content.push_back(tws_node_cnt_t<REAL, AINT>(atm, idx));
    //pass any atom and store index to lookup struct
    m_atom_node_lookup[atm].push_back(atom_node_lookup_t<REAL, AINT>(idx, cur_node));
    if (geom->get_DIM() > 0 && !idx.is_zero())
      m_img_atoms.push_back(img_atom_t<REAL, AINT>(atm, idx));
  }

  void grow_tws_root(const AINT atm, const index & idx) {
#ifdef TWS_TREE_DEBUG
    fmt::print(">>> pre grow vol={0} {1} {2} {3} nc = {4}, root_bb : min={5}, max={6}\n",
               root->m_bb.volume(),
               geom->pos(atm,idx)[0],
               geom->pos(atm,idx)[1],
               geom->pos(atm,idx)[2],
               root->m_tot_childs,
               root->m_bb.min,
               root->m_bb.max);
#endif
    tws_node_t<REAL, AINT>* old_root = root;
    root = nullptr;

    tws_node_t<REAL, AINT>* new_root = new tws_node_t<REAL, AINT>();
    m_flat_view.push_back(new_root);

    vector3<REAL> vSize = (old_root->m_bb.max - old_root->m_bb.max);
    new_root->m_bb.min = old_root->m_bb.min * (3.0);
    new_root->m_bb.max = old_root->m_bb.max * (3.0);
    new_root->parent = nullptr;

    new_root->m_sub_nodes[enc_tws_idx(0,0,0)] = old_root;
    new_root->m_tot_childs += 1;
    old_root->parent = new_root;

    root = new_root;

#ifdef TWS_TREE_DEBUG
    fmt::print(">>> post grow vol={0} {1} {2} {3} nc = {4}, root_bb : min={5}, max={6}\n",
               root->m_bb.volume(),
               geom->pos(atm,idx)[0],
               geom->pos(atm,idx)[1],
               geom->pos(atm,idx)[2],
               root->m_tot_childs,
               root->m_bb.min,
               root->m_bb.max);
#endif
  }

  AINT n(AINT i) const {
    return m_ngb_table[i].size();
  }

  index table_idx(AINT i, AINT j) const {
    return m_ngb_table[i][j].m_idx;
  }

  AINT  table_atm(AINT i, AINT j) const {
    return m_ngb_table[i][j].m_atm;
  }

  void add_ngbr(AINT ha, AINT i, const index j) {
    bool found = false;
    for (AINT k = 0; k < m_ngb_table[ha].size(); k++ )
      if (m_ngb_table[ha][k].m_atm == i  && m_ngb_table[ha][k].m_idx == j){
        found = true;
        break;
      }
    if (!found)
      m_ngb_table[ha].push_back(tws_node_cnt_t<REAL, AINT>(i, j));
  }

  void find_all_neighbours() {
    for (AINT i = 0; i < geom->nat(); i++)
      find_neighbours(i, index::D(geom->get_DIM()).all(0));
    if (m_build_img_atoms_bonds)
      for (auto &img_atom : m_img_atoms)
        find_neighbours(img_atom.m_atm, img_atom.m_idx);
  }

  void find_neighbours(AINT at_num) {
    find_neighbours(at_num, index::D(geom->get_DIM()).all(0));
    if (m_build_img_atoms_bonds)
      for (AINT i = 0; i < m_img_atoms.size(); i++)
        if (m_img_atoms[i].m_atm == at_num)
          find_neighbours(m_img_atoms[i].m_atm, m_img_atoms[i].m_idx);
  }

  void find_neighbours(AINT at_num, index idx) {
    if (!root)
      return;

    if (m_bonding_table.m_dist.size() == 0)
      m_bonding_table.init_default(geom);

    if (m_ngb_table.size() < geom->nat())
      m_ngb_table.resize(geom->nat());

    bool img_pass = !idx.is_zero();

    REAL sph_r = m_bonding_table.m_max_dist[geom->type_table(at_num)];
    if ( sph_r > 0.0) {

      std::vector<tws_node_cnt_t<REAL, AINT> > res;
      query_sphere(sph_r, geom->pos(at_num, idx), res);

      for (auto &r_el : res) {
        vector3<REAL> pos1 = geom->pos(at_num, idx);
        vector3<REAL> pos2 = geom->pos(r_el.m_atm, r_el.m_idx);

        auto bonding_record = m_bonding_table.m_dist.find(sym_key<AINT>(
            geom->type_table(at_num),
            geom->type_table(r_el.m_atm)));

        if (bonding_record == m_bonding_table.m_dist.end())
          continue;

        if (!bonding_record->second.m_enabled)
          continue;

        REAL f_dr = (pos1 - pos2).norm();

        REAL bond_len = bonding_record->second.m_bonding_dist;

        //cache comparison data
        bool first_real      = idx.is_zero();
        bool second_real     = r_el.m_idx.is_zero();
        bool first_im        = !first_real;
        bool second_im       = !second_real;
        bool mixed_real_im   = (first_real && second_im) || (first_im && second_real);
        bool both_atoms_real = first_real && second_real;
        bool both_atoms_im   = first_im && second_im;

        //both atoms are real
        if (!img_pass && f_dr < bond_len && both_atoms_real
            && (at_num != r_el.m_atm || idx != r_el.m_idx)) {
          add_ngbr(at_num, r_el.m_atm, r_el.m_idx);
          add_ngbr(r_el.m_atm, at_num , r_el.m_idx);
        }

        //mixed
        if (f_dr < bond_len && mixed_real_im) {
          //determine who is who
          AINT mx_at1_num = -1;
          AINT mx_at2_num = -1;
          index mx_at1_idx, mx_at2_idx;
          if (first_real) {
            mx_at1_num = at_num;
            mx_at1_idx = idx;
            mx_at2_num = r_el.m_atm;
            mx_at2_idx = r_el.m_idx;
          } else {
            mx_at1_num = r_el.m_atm;
            mx_at1_idx = r_el.m_idx;
            mx_at2_num = at_num;
            mx_at2_idx = idx;
          }
          // add real bond
          add_ngbr(mx_at1_num, mx_at2_num, mx_at2_idx);
          // add imaginary bond
          std::optional<AINT> iat = find_img_atom(mx_at2_num, mx_at2_idx);
          if (iat)
            m_img_atoms[*iat].m_img_bonds.push_back(tws_node_cnt_t<REAL, AINT>(mx_at1_num, mx_at1_idx));
        }

        //two imaginary atoms
        if (img_pass
            && m_build_img_atoms_bonds
            && f_dr < bond_len
            && both_atoms_im) {
          std::optional<AINT> iat1, iat2;
          iat1 = find_img_atom(at_num, idx);
          iat2 = find_img_atom(r_el.m_atm, r_el.m_idx);
          if (iat1 && iat2) {
            m_img_atoms[*iat1].m_img_bonds.push_back(tws_node_cnt_t<REAL, AINT>(r_el.m_atm, r_el.m_idx));
            m_img_atoms[*iat2].m_img_bonds.push_back(tws_node_cnt_t<REAL, AINT>(at_num, idx));
          }
        }

      }

      res.clear();

    }
  }

  void manual_build() {
    for (AINT i = 0; i < geom->nat(); i++) insert_object_to_tree(i);
#ifdef TWS_TREE_DEBUG
    fmt::print("Total img.atoms for tree {}\n", m_img_atoms.size());
#endif
  }

  void debug_print() {
    AINT totalEntries = 0;
    debug_print_traverse(root, 1, totalEntries);
    fmt::print("Total entries = {}\n ", totalEntries);
  }

  void debug_print_traverse(tws_node_t<REAL, AINT> *node, AINT deep_level, AINT &tot_entries) {
    REAL fake_aabb_vol = 1.0;
    for (AINT i = 0; i < DIM_RECT; i++)
      fake_aabb_vol *= node->m_bb.max[i]-node->m_bb.min[i];
    std::cout << std::string(deep_level, '>')
              << "node vol = "<< fake_aabb_vol <<" " << node->m_bb << " "
              << node->m_content.size()<< std::endl;
    tot_entries += node->m_content.size();
    for (tws_node_t<REAL, AINT>* node_inst : node->m_sub_nodes)
      if (node_inst)
        debug_print_traverse(node_inst, deep_level+1, tot_entries);
  }


  uint32_t get_flags() override {
    return geometry_observer_supports_default
           | geometry_observer_supports_add
           | geometry_observer_supports_insert
           | geometry_observer_supports_change
           | geometry_observer_supports_erase
           | geometry_observer_supports_shadow
           | geometry_observer_supports_reorder;
  };


  void added(before_after st, const STRING_EX & a, const vector3<REAL> & r) override {
    if (st == before_after::after) {
      do_action(act_check_consistency);
      if (m_auto_build)
        insert_object_to_tree(geom->nat()-1);
      if (m_auto_bonding)
        find_neighbours(geom->nat()-1);
    }
    m_tree_is_dirty = true;
    m_atoms_existence_is_broken = true;
  }

  void inserted(int at, before_after st, const STRING_EX & a, const vector3<REAL> & r) override {
    if (m_auto_bonding && m_auto_build) {
      if (st == before_after::before) {
        if (m_rebuild_all_on_insert)
          do_action(act_clear_all);
      } else { /* after */
        if (m_auto_build)
          insert_object_to_tree(at);
        if (m_auto_bonding) {
          m_bonding_table.init_for_single_type(geom, geom->type_of_atom(at));
          find_neighbours(at);
        }
        if (m_rebuild_all_on_insert)
          do_action(act_check_consistency | act_rebuild_all);
      }
    }
    m_tree_is_dirty = true;
    m_atoms_existence_is_broken = true;
  }

  void changed(int at, before_after st, const STRING_EX & a, const vector3<REAL> & r) override {
    if (st == before_after::after) {
      if (m_auto_bonding && m_auto_build) {
        do_action(act_check_consistency);
        clr_atom_bond_data(at);
        std::vector<index> imgs = clr_atom_from_tree(at);
        if (m_keep_img_atoms) {
          for (auto &idx : imgs) {
            insert_object_to_tree(at, idx);
            find_neighbours(at, idx);
          }
        } else {
          insert_object_to_tree(at);
          find_neighbours(at);
        }
      }
    }
    m_tree_is_dirty = true;
  }

  void erased(int at, before_after st) override {
    if (m_auto_bonding && m_auto_build) {
      if (st == before_after::before) {
        if (m_rebuild_all_on_erase)
          do_action(act_clear_all);
      } else { /* after */
        if (m_rebuild_all_on_erase)
          do_action(act_check_consistency | act_rebuild_all);
      }
    }
    m_tree_is_dirty = true;
    m_atoms_existence_is_broken = true;
  }

  void shaded(int at, before_after st, bool sh) override {
    m_tree_is_dirty = true;
  }

  /// \brief reordered
  void reordered(const std::vector<int> &, before_after ord) override {
    m_tree_is_dirty = true;
  }

  void selected(atom_index_set_key &sel_at, before_after, bool state) override {}
  void dim_changed(before_after ord) override {}
  void cell_changed(before_after ord) override {}
  void xfield_changed(int xid, int at, before_after ord) override {}

}; // class tws_tree


} // namespace qpp

#endif
