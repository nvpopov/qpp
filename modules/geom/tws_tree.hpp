#ifndef QPP_RTREE_H
#define QPP_RTREE_H

#include <ostream>
#include <unordered_map>
#include <functional>
#include <utility>
#include <set>
#include <algorithm>
#include <cmath>
#include <optional>

#include <cassert>
#include <string>

#include <geom/geom.hpp>
#include <geom/ngbr.hpp>
#include <data/symmetric_key.hpp>
#include <data/ptable.hpp>
#include <geom/aabb.hpp>
#include <geom/ray.hpp>
#include <geom/primitive_intersections.hpp>
#include <data/ptable.hpp>
#include <data/make_unique.hpp>

//#ifdef PY_EXPORT
//#include <pybind11/pybind11.h>
//#include <pybind11/operators.h>
//#include <pybind11/stl.h>
//#include <pyqpp/py_indexed_property.hpp>
//namespace py = pybind11;
//#endif

#define TWS_TREE_DEBUG
using namespace std;

namespace qpp{

  template<typename INT_TYPE>
  inline INT_TYPE enc_tws_idx(const INT_TYPE a, const INT_TYPE b,
                              const INT_TYPE c){
    return a*9+b*3+c+13;
  }

  template<typename POL_REAL = float>
  struct query_ray_add_all{
      static bool can_add(vector3<POL_REAL> &pos, index &idx, const int DIM = 0){
        return true;
      }
  };

  template<typename POL_REAL = float>
  struct query_ray_add_ignore_images{
      static bool can_add(vector3<POL_REAL> &pos, index &idx, const int DIM = 0){
        return idx == index::D(DIM).all(0);
      }
  };

  /// tws tree node forward declaration                                        ///
  template<typename REAL, typename AINT>
  struct tws_node_t;

  /// data to store in rtree                                                ///
  template<typename REAL = float, typename AINT = uint32_t>
  struct tws_node_content_t {
      AINT m_atm;
      index m_idx;
      tws_node_content_t(const AINT _atm, const index _idx){m_atm = _atm; m_idx = _idx;}
  };

  ///
  /// \brief The imaginary_atom struct
  ///
  template<typename REAL, typename AINT = uint32_t>
  struct imaginary_atom_t {
      AINT m_atm;
      index m_idx;
      tws_node_t<REAL, AINT> *parent;
      vector<tws_node_content_t<REAL, AINT> > m_img_bonds;
      imaginary_atom_t(const AINT _atm, const index _idx){m_atm = _atm; m_idx = _idx;}
      ~imaginary_atom_t() = default;
  };

  template<typename REAL = float, typename AINT = uint32_t>
  struct tws_query_data_t {
      AINT m_atm;
      index m_idx;
      REAL m_dist;
      tws_query_data_t(const AINT _atm, const index _idx,
                       const REAL _dist = 1000.0f){
        m_atm = _atm; m_idx = _idx; m_dist = _dist;
      }

      bool operator == (const tws_query_data_t<REAL, AINT> &a){
        return (m_idx == a.idx) && (m_atm == a.atm);
      }

      tws_query_data_t<REAL, AINT>& operator =(const tws_query_data_t<REAL, AINT> &a){
        m_idx = a.m_idx;
        m_atm = a.m_atm;
        m_dist = a.m_dist;
        return *this;
      }

      tws_query_data_t<REAL, AINT>(const tws_query_data_t<REAL, AINT>& a){
        m_idx = a.m_idx;
        m_atm = a.m_atm;
        m_dist = a.m_dist;
      }
  };

  template<typename REAL = float>
  bool tws_query_data_sort_by_dist(tws_query_data_t<REAL> &a, tws_query_data_t<REAL> &b){
    return a.m_dist <= b.m_dist;
  }

  ///
  /// \brief The tws_node struct
  ///
  template<typename REAL = float, typename AINT = uint32_t>
  struct tws_node_t {
      tws_node_t<REAL, AINT>* parent;
      aabb_3d_t<REAL> m_bb;
      vector<tws_node_content_t<REAL, AINT> > m_content;
      array<tws_node_t<REAL, AINT>*, 27> m_sub_nodes {};
      int m_tot_childs{0};
      tws_node_t(){}

      void rm_cnt_by_id(const AINT atm){
        for (auto it = m_content.begin(); it != m_content.end();){
            if(it->m_atm == atm) it = m_content.erase(it);
            else ++it;
          }
      }

      void rm_cnt_idx_store(const AINT atm, vector<index> &idx_vec){
        for (auto it = m_content.begin(); it != m_content.end();){
            if(it->m_atm == atm){
                idx_vec.push_back(it->m_idx);
                it = m_content.erase(it);
              }
            else ++it;
          }
      }

      bool operator == (const tws_node_t<REAL, AINT> &a){
        return this == a;
      }
  };


  template<typename REAL>
  struct atom_node_lookup_t {
      index m_idx;
      tws_node_t<REAL> *node;
      atom_node_lookup_t(const index _idx, tws_node_t<REAL> *_node){
        m_idx = _idx; node = _node;
      }
  };

  template<typename REAL>
  struct dist_table_record_t {
      REAL m_bonding_dist{0.0f};
      bool m_override{false};
      bool m_enabled{false};
  };

  ///
  /// aux tws tree implementation
  ///
  template <class REAL, class CELL = periodic_cell<REAL>, typename AINT = uint32_t >
  class tws_tree_t : public geometry_observer<REAL>{
    public:
      REAL m_guess_rect_size;
      REAL m_min_tws_volume;

      geometry<REAL, CELL>                                       *geom;
      tws_node_t<REAL, AINT>                                     *root;
      vector<tws_node_t<REAL, AINT>* >                           m_flat_view;
      vector<imaginary_atom_t<REAL, AINT> >                      m_img_atoms;
      vector<vector<tws_node_content_t<REAL, AINT> > >           m_ngb_table;
      vector<vector<atom_node_lookup_t<REAL> > >                 m_atom_node_lookup;

      unordered_map<qpp::sym_key<int>, dist_table_record_t<REAL>, sym_key_hash<int> > m_dist_map;

      map<AINT, REAL> m_max_dist_map;

      bool m_make_dirty_dist_map;
      bool m_auto_bonding; /// \brief bAutoBonding
      bool m_auto_build; /// \brief bAutoBuild
      bool m_build_imaginary_atoms_bonds;/// \brief bBuildImaginaryAtomsBonds

      ///
      /// \brief aux_rtree constructor
      /// \param g
      ///
      tws_tree_t( geometry<REAL, CELL> & g) {
        geom = & g;
        geom->add_observer(*this);
        m_guess_rect_size = 6.0f;
        m_min_tws_volume  = 65.0;
        root = nullptr;
        m_auto_bonding = false;
        m_auto_build = true;
        m_make_dirty_dist_map = true;
        m_build_imaginary_atoms_bonds = true;
      }

      ///
      /// \brief check_root
      ///
      void check_root(){
        if (root == nullptr){
            //std::cout << "create root" << std::endl;
            root = new tws_node_t<REAL>();
            m_flat_view.push_back(root);
            root->m_bb.fill_guess(m_guess_rect_size);
            if (root->m_bb.volume() < m_min_tws_volume)
              root->m_bb.fill_guess(pow(m_min_tws_volume, 1/3.0));
          }
      }

      optional<AINT> find_imaginary_atom(const AINT atm, const index idx){
        for (AINT i = 0; i < m_img_atoms.size(); i++)
          if (m_img_atoms[i].m_atm == atm && m_img_atoms[i].m_idx == idx)
            return optional<AINT>(i);
        return nullopt;
      }

      optional<AINT> find_imaginary_atom_by_id(const AINT atm){
        for (AINT i = 0; i < m_img_atoms.size(); i++)
          if (m_img_atoms[i].atm == atm)
            return optional<AINT>(i);
        return nullopt;
      }

      ///
      /// \brief clear_bonds
      ///
      void clr_ntable(){
        for (auto &per_atom : m_ngb_table) per_atom.clear();
        m_ngb_table.clear();
      }

      ///
      /// \brief clr_bond_real_im
      /// \param atm1
      /// \param atm2
      /// \param idx2
      ///
      void clr_bond_real_im(const AINT atm1, const AINT atm2, const index idx2){
        for(auto it = m_ngb_table[atm1].begin(); it != m_ngb_table[atm1].end(); )
          if(it->m_atm == atm2 && it->m_idx == idx2) m_ngb_table[atm1].erase(it);
          else ++it;
      }

      ///
      /// \brief clr_bond_im_real
      /// \param img_atom_id
      /// \param atm2
      /// \param idx2
      ///
      void clr_bond_im_real(const AINT img_atom_id, const AINT atm2, const index idx2){
        for(auto it = m_img_atoms[img_atom_id].begin(); it != m_img_atoms[img_atom_id].end(); )
          if(it->m_atm == atm2 && it->m_idx == idx2) m_img_atoms[img_atom_id].erase(it);
          else ++it;
      }

      ///
      /// \brief clr_bond_im_real
      /// \param img_atom_id
      /// \param atm2
      ///
      void clr_bond_im_real(const AINT img_atom_id, const int atm2){
        for(auto it = m_img_atoms[img_atom_id].m_img_bonds.begin();
            it != m_img_atoms[img_atom_id].m_img_bonds.end(); )
          if(it->m_atm == atm2) m_img_atoms[img_atom_id].m_img_bonds.erase(it);
          else ++it;
      }

      ///
      /// \brief clear_atom_bonding_data
      /// \param atm
      ///
      void clr_atom_bond_data(const AINT atm){
        for(auto &bond : m_ngb_table[atm])
          if (bond.m_idx == index::D(geom->DIM).all(0) || geom->DIM == 0)
            clr_atom_pair_bond_data(bond.m_atm, atm);
          else {
              optional<AINT> img_id = find_imaginary_atom(bond.m_atm, bond.m_idx);
              if (img_id) clr_bond_im_real(*img_id, atm);
            }
        m_ngb_table[atm].clear();
      }

      ///
      /// \brief clear_atom_pair_bonding_data
      /// \param atm1
      /// \param atm2
      ///
      void clr_atom_pair_bond_data(const AINT atm1, const AINT atm2){
        if (m_ngb_table[atm1].size() > 0){
            auto new_end = std::remove_if(m_ngb_table[atm1].begin(), m_ngb_table[atm1].end(),
                                          [&atm2](tws_node_content_t<REAL> & bonds)
            { return bonds.m_atm == atm2; });
            m_ngb_table[atm1].erase(new_end);
          }
      }

      ///
      /// \brief clear_atom_from_tree
      /// \param atm
      ///
      void clr_atom_from_tree(const AINT atm){
        if (geom->DIM == 0 && m_atom_node_lookup[atm].size() > 0)
          m_atom_node_lookup[atm][0].node->rm_cnt_by_id(atm);

        if (geom->DIM > 0){
            vector<index> image_idx;

            //remove 0,0,0 and c1,c2,c3 atoms from tree
            for (auto& at_node : m_atom_node_lookup[atm])
              at_node.node->rm_cnt_idx_store(atm, image_idx);

            //iterate over imaginary atoms, store secondary imaginary atom, erase required atom
            vector<tuple<AINT, index> > pair_img_atoms;
            for (auto it = m_img_atoms.begin(); it != m_img_atoms.end();)
              if (it->m_atm == atm){
                  for(auto &nc : it->m_img_bonds){
                      if (nc.m_idx != index::D(geom->DIM).all(0)) {
                          pair_img_atoms.push_back(tuple<AINT, index>(nc.m_atm, nc.m_idx));
                        }
                      else clr_bond_real_im(nc.m_atm, it->m_atm, it->m_idx);
                    }
                  it = m_img_atoms.erase(it);
                } else ++it;

            //delete bonds from paired imaginary atoms
            for (auto &pair : pair_img_atoms){
                optional<AINT> paired_img_id = find_imaginary_atom(get<0>(pair), get<1>(pair));
                if (paired_img_id){
                    for (auto it = m_img_atoms[*paired_img_id].m_img_bonds.begin();
                         it != m_img_atoms[*paired_img_id].m_img_bonds.end();){
                        if (it->m_atm == atm) it = m_img_atoms[*paired_img_id].m_img_bonds.erase(it);
                        else ++it;
                      }
                  }
              }

          }
        //tws_node_t<REAL> *node = atom_node_lookup[]
        m_atom_node_lookup[atm].clear();
      }


      ///
      /// \brief clear_tree
      ///
      void clr_tree(){
        for (auto *node : m_flat_view){
            if (node) delete node;
            node = nullptr;
          }
        m_flat_view.clear();
      }

      ///
      /// \brief apply_shift
      /// \param vShift
      ///
      void apply_shift(const vector3<REAL> vec_shift){
        for (auto *node : m_flat_view){
            node->m_bb.min += vec_shift;
            node->m_bb.max += vec_shift;
          }
      }

      ///
      /// \brief apply_visitor
      /// \param f
      ///
      void apply_visitor(function<void(tws_node_t<REAL, AINT>*, int)> f){
        traverse_apply_visitor(root, 0, f);
      }

      ///
      /// \brief traverse_apply_visitor
      /// \param curNode
      /// \param f
      ///
      void traverse_apply_visitor(tws_node_t<REAL, AINT> *cur_node, int deep_level,
                                  function<void(tws_node_t<REAL, AINT>*, int)> f){
        f(cur_node, deep_level);
        for(auto* child : cur_node->m_sub_nodes)
          if (child) traverse_apply_visitor(child, deep_level+1, f);
      }

      ///
      /// \brief query_ray
      /// \param vRayStart
      /// \param vRayDir
      ///
      template<typename adding_result_policy = query_ray_add_all<REAL> >
      void query_ray(ray_t<REAL> *_ray,
                     vector<tws_query_data_t<REAL, AINT> > &res,
                     REAL scale_factor = 0.25){
        traverse_query_ray<adding_result_policy>(root, _ray, res, scale_factor);
      }

      ///
      /// \brief traverse_query_ray
      /// \param curNode
      /// \param vRayStart
      /// \param vRayDir
      ///
      template<typename adding_result_policy>
      bool traverse_query_ray(tws_node_t<REAL, AINT> *cur_node,
                              ray_t<REAL> *_ray,
                              vector<tws_query_data_t<REAL, AINT> > &res,
                              const REAL scale_factor){

        if (ray_aabb_test(_ray, &(cur_node->m_bb))){
            if (cur_node->m_tot_childs > 0){
                for (auto *ch_node : cur_node->m_sub_nodes)
                  if (ch_node)
                    traverse_query_ray<adding_result_policy>(ch_node, _ray, res, scale_factor);
              } else
              for (auto &nc : cur_node->m_content){
                  int ap_idx = ptable::number_by_symbol(geom->atom(nc.m_atm));

                  //TODO: move magic aRadius
                  REAL atom_rad = ptable::get_inst()->arecs[ap_idx-1].aRadius * scale_factor;
                  REAL stored_dist = 0.0;
                  vector3<REAL> test_pos = geom->pos(nc.m_atm, nc.m_idx);
                  REAL ray_hit_dist = ray_sphere_test( _ray, test_pos, atom_rad);
                  bool ray_hit = ray_hit_dist > -1.0f;

                  if (ray_hit) {
                      if (adding_result_policy::can_add(test_pos, nc.m_idx, geom->DIM))
                        res.push_back(tws_query_data_t<REAL, AINT>(nc.m_atm, nc.m_idx, ray_hit_dist));
                    }
                }
          }
        else return false;
      }



      ///
      /// \brief query_sphere
      /// \param fSphRad
      /// \param vSphCnt
      /// \param res
      ///
      void query_sphere(const REAL sph_r,
                        const vector3<REAL> sph_cnt,
                        vector<tws_node_content_t<REAL, AINT> > &res){
        traverse_query_sphere(root, sph_r, sph_cnt, res);
      }

      ///
      /// \brief traverse_query_sphere
      /// \param curNode
      /// \param fSphRad
      /// \param vSphCnt
      /// \param res
      ///
      void traverse_query_sphere(
          tws_node_t<REAL, AINT> *cur_node,
          const REAL &sph_r,
          const vector3<REAL> &sph_cnt,
          vector<tws_node_content_t<REAL, AINT> > &res){

        if (cur_node->m_bb.test_sphere(sph_r, sph_cnt)){

            for (auto *child : cur_node->m_sub_nodes)
              if (child) traverse_query_sphere(child, sph_r, sph_cnt, res);

            for (auto &cnt : cur_node->m_content)
              if ((sph_cnt - geom->pos(cnt.m_atm, cnt.m_idx)).norm() <= sph_r)
                res.push_back(tws_node_content_t<REAL, AINT>(cnt.m_atm, cnt.m_idx));
          }
      }

      //
      void insert_object_to_tree(const AINT atm){
        for (iterator i(index::D(geom->DIM).all(-1), index::D(geom->DIM).all(1)); !i.end(); i++ )
          if (i == index::D(geom->DIM).all(0))
            insert_object_to_tree(atm, i);
          else if (geom->cell.within_epsilon_b(geom->pos(atm, i), 0.09f))
            insert_object_to_tree(atm, i);
      }

      ///
      /// \brief Insert oject to tree
      /// \param atm
      /// \param idx
      ///
      void insert_object_to_tree(const AINT atm, const index idx){
        check_root();
        // int q = 0;
        if (m_atom_node_lookup.size() != geom->size()) m_atom_node_lookup.resize(geom->size());
        while (!(point_aabb_test(geom->pos(atm, idx), root->m_bb)) ) {
            grow_tws_root(atm, idx);
            // q++;

#ifdef TWS_TREE_DEBUG
            std::cout<<fmt::format("rootgrow p = {}, {}, {}\n",
                                   geom->pos(atm, idx)[0],
                geom->pos(atm, idx)[1],
                geom->pos(atm, idx)[2] );
            // assert(q<10);
#endif
          }
        traverse_insert_object_to_tree(root, atm, idx);
      }

      ///
      /// \brief traverse_insert_object_to_tree
      /// \param curNode
      /// \param atm
      /// \param idx
      /// \return
      ///
      bool traverse_insert_object_to_tree(tws_node_t<REAL, AINT> *cur_node, const AINT atm,
                                          const index & idx){

        vector3<REAL> p = geom->pos(atm, idx);
        vector3<REAL> cn_size = cur_node->m_bb.max - cur_node->m_bb.min;
        vector3<REAL> cn_center = cur_node->m_bb.center();

        bool in_cur_rect = point_aabb_test(p, cur_node->m_bb);
        if (!in_cur_rect) return false;

        if (in_cur_rect){
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

            if (cur_node->m_sub_nodes[nidx] == nullptr){

                tws_node_t<REAL, AINT> *newNode = new tws_node_t<REAL, AINT>();
                m_flat_view.push_back(newNode);
                //define the 0,0,0 max min
                vector3<REAL> z_min = cur_node->m_bb.min + cn_size / 3;
                vector3<REAL> z_max = cur_node->m_bb.max - cn_size / 3;

                newNode->m_bb.min = z_min +
                                    vector3<REAL>(i_x * cn_size[0]/ 3,
                    i_y * cn_size[1]/ 3,
                    i_z * cn_size[2]/ 3);

                newNode->m_bb.max = z_max +
                                    vector3<REAL>(i_x * cn_size[0]/ 3,
                    i_y * cn_size[1]/ 3,
                    i_z * cn_size[2]/ 3);

                cur_node->m_sub_nodes[nidx] = newNode;
                cur_node->m_tot_childs+=1;
              }

            traverse_insert_object_to_tree(cur_node->m_sub_nodes[nidx],
                                           atm, idx);
          }

        return false;
      }

      ///
      /// \brief push_data_to_tws_node
      /// \param curNode
      /// \param atm
      /// \param idx
      ///
      void push_data_to_tws_node(tws_node_t<REAL, AINT> *cur_node, const AINT atm, const index idx){
        //pass any atom with any index to tws-tree
        cur_node->m_content.push_back(tws_node_content_t<REAL>(atm, idx));

        //pass any atom and store index to lookup struct
        m_atom_node_lookup[atm].push_back(atom_node_lookup_t<REAL>(idx, cur_node));

        if ( geom->DIM > 0 && idx != index::D(geom->DIM).all(0))
          m_img_atoms.push_back(imaginary_atom_t<REAL>(atm, idx));

      }


      ///
      /// \brief grow_tws_root
      /// \param atm
      /// \param idx
      ///
      void grow_tws_root( const AINT atm, const index & idx){

#ifdef TWS_TREE_DEBUG
        std::cout<<fmt::format(">>> pre grow vol={} {} {} {} nc = {}",
                               root->m_bb.volume(),
                               geom->pos(atm,idx)[0],
            geom->pos(atm,idx)[1],
            geom->pos(atm,idx)[2],
            root->m_tot_childs) << root->m_bb <<std::endl;
#endif
        tws_node_t<REAL>* old_root = root;
        root = nullptr;

        tws_node_t<REAL>* new_root = new tws_node_t<REAL>();
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
        std::cout<<fmt::format(">>> post grow vol={} {} {} {} nc = {}",
                               root->m_bb.volume(),
                               geom->pos(atm,idx)[0],
            geom->pos(atm,idx)[1],
            geom->pos(atm,idx)[2],
            root->m_tot_childs) << root->m_bb <<std::endl;
#endif
      }

      ///
      /// \brief n
      /// \param i
      /// \return
      ///
      AINT n(AINT i) const {return m_ngb_table[i].size();}

      ///
      /// \brief table
      /// \param i
      /// \param j
      /// \return
      ///
      index table_idx(AINT i, AINT j) const {return m_ngb_table[i][j].m_idx;}
      AINT  table_atm(AINT i, AINT j) const {return m_ngb_table[i][j].m_atm;}

      void rebuild_dist_map(){
        //TODO: make it more ellegant

        for (int i = 0; i < geom->n_atom_types(); i++){
            REAL max_bond_rad = 0.0;
            for (int j = 0; j <  geom->n_atom_types(); j++){
                int table_idx1  = ptable::number_by_symbol(geom->atom_of_type(i));
                int table_idx2  = ptable::number_by_symbol(geom->atom_of_type(j));
                optional<REAL> bond_rad_1 = ptable::cov_rad_by_number(table_idx1);
                optional<REAL> bond_rad_2 = ptable::cov_rad_by_number(table_idx2);
                if (bond_rad_1 && bond_rad_2){
                    m_dist_map[sym_key<int>(i,j)].m_bonding_dist = *bond_rad_1 + *bond_rad_2;
                    max_bond_rad = std::max(max_bond_rad, *bond_rad_1 + *bond_rad_2);
                    m_dist_map[sym_key<int>(i,j)].m_enabled = true;
                  } else m_dist_map[sym_key<int>(i,j)].m_enabled = false;
              }
            m_max_dist_map[i] = max_bond_rad;
          }
        m_make_dirty_dist_map = false;
      }

      ///
      /// \brief add_ngbr
      /// \param ha
      /// \param i
      /// \param j
      ///
      void add_ngbr(AINT ha, AINT i, const index j){
        bool found = false;
        for (AINT k = 0; k < m_ngb_table[ha].size(); k++ )
          if (m_ngb_table[ha][k].m_atm == i  && m_ngb_table[ha][k].m_idx == j){
              found = true;
              break;
            }
        if (!found) m_ngb_table[ha].push_back(tws_node_content_t<REAL>(i, j));
      }

      ///
      /// \brief find_all_neighbours
      ///
      void find_all_neighbours(){
        for (AINT i = 0; i < geom->nat(); i++) find_neighbours(i, index::D(geom->DIM).all(0));
        if (m_build_imaginary_atoms_bonds)
          for (auto &img_atom : m_img_atoms) find_neighbours(img_atom.m_atm, img_atom.m_idx, true);
      }

      ///
      /// \brief find_neighbours
      /// \param at_num
      ///
      void find_neighbours(AINT at_num){
        find_neighbours(at_num, index::D(geom->DIM).all(0));
        if (m_build_imaginary_atoms_bonds)
          for (int i = 0; i < m_img_atoms.size(); i++)
            if (m_img_atoms[i].m_atm == at_num)
              find_neighbours(m_img_atoms[i].m_atm, m_img_atoms[i].m_idx, true);
      }

      ///
      /// \brief find_neighbours
      /// \param atNum
      ///
      void find_neighbours(AINT at_num, index idx, bool imaginary_pass = false){
        if (!root) return;

        if (m_make_dirty_dist_map) {
            rebuild_dist_map();
            if (m_ngb_table.size() < geom->nat()) m_ngb_table.resize(geom->nat());
          }

        REAL sph_r = m_max_dist_map[geom->type_table(at_num)];
        if ( sph_r > 0.0){

            vector<tws_node_content_t<REAL, AINT> > res;
            query_sphere(sph_r, geom->pos(at_num, idx), res);

            for (auto &r_el : res){
                vector3<REAL> pos1 = geom->pos(at_num, idx);
                vector3<REAL> pos2 = geom->pos(r_el.m_atm, r_el.m_idx);

                if (!m_dist_map[sym_key<int>(geom->type_table(at_num),
                                            geom->type_table(r_el.m_atm))].m_enabled) continue;

                REAL f_dr = (pos1 - pos2).norm();

                REAL bond_len = m_dist_map[sym_key<int>(
                                  geom->type_table(at_num),
                                  geom->type_table(r_el.m_atm))].m_bonding_dist;

                //cache comparison data
                bool first_real      = idx == index::D(geom->DIM).all(0);
                bool second_real          = r_el.m_idx == index::D(geom->DIM).all(0);
                bool first_im        = !first_real;
                bool second_im       = !second_real;
                bool mixed_real_im   = (first_real && second_im) || (first_im && second_real);
                bool both_atoms_real = first_real && second_real;
                bool both_atoms_im   = first_im && second_im;

                //both atoms are real
                if (!imaginary_pass && f_dr < bond_len && both_atoms_real  &&
                    (at_num != r_el.m_atm || idx != r_el.m_idx)){
                    add_ngbr(at_num, r_el.m_atm, r_el.m_idx);
                    add_ngbr(r_el.m_atm, at_num , r_el.m_idx);
                  }

                //mixed
                if (f_dr < bond_len && mixed_real_im){
                    //determine who is who
                    AINT mx_at1_num = -1;
                    AINT mx_at2_num = -1;
                    index mx_at1_idx, mx_at2_idx;

                    if (first_real){
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
                    optional<AINT> iat = find_imaginary_atom(mx_at2_num, mx_at2_idx);
                    if (iat)
                      m_img_atoms[*iat].m_img_bonds.push_back(
                            tws_node_content_t<REAL>(mx_at1_num, mx_at1_idx));
                  }


                //two imaginary atoms
                if (imaginary_pass && m_build_imaginary_atoms_bonds && f_dr < bond_len &&
                    both_atoms_im){

                    optional<AINT> iat1, iat2;

                    iat1 = find_imaginary_atom(at_num, idx);
                    iat2 = find_imaginary_atom(r_el.m_atm, r_el.m_idx);

                    if (iat1 && iat2){

                        m_img_atoms[*iat1].m_img_bonds.push_back(
                              tws_node_content_t<REAL>(r_el.m_atm, r_el.m_idx));

                        m_img_atoms[*iat2].m_img_bonds.push_back(
                              tws_node_content_t<REAL>(at_num, idx));

                      }
                  }

              }
            //TODO: strange thing happened there
            //             for (tws_node_content<REAL> *r_el : res)
            //               if (r_el) delete r_el;
            res.clear();
          }
      }

      ///
      /// \brief manual_build
      ///
      void manual_build(){
        for (AINT i = 0; i < geom->nat(); i++) insert_object_to_tree(i);
      }

      ///
      /// \brief debug_print
      ///
      void debug_print(){
        AINT totalEntries = 0;
        debug_print_traverse(root, 1, totalEntries);
        std::cout << "Total entries = " << totalEntries << std::endl;
      }

      ///
      /// \brief debug_print_traverse
      /// \param node
      /// \param iDeepLevel
      /// \param totalEntries
      ///
      void debug_print_traverse(tws_node_t<REAL, AINT> *node,
                                AINT deep_level,
                                AINT &tot_entries){

        REAL fake_aabb_vol = 1.0;
        for (AINT i = 0; i < DIM_RECT; i++)
          fake_aabb_vol *= node->m_bb.max[i]-node->m_bb.min[i];
        std::cout << std::string(deep_level, '>')
                  << "node vol = "<< fake_aabb_vol <<" " << node->m_bb << " "
                  << node->m_content.size()<< std::endl;
        tot_entries += node->m_content.size();

        for (tws_node_t<REAL>* _node : node->m_sub_nodes)
          if (_node) debug_print_traverse(_node, deep_level+1, tot_entries);

      }

      ///
      /// \brief added
      /// \param st
      /// \param a
      /// \param r
      ///
      void added( before_after st,
                  const STRING & a,
                  const vector3<REAL> & r) override {
        if (st == before_after::after){
            m_ngb_table.resize(geom->nat());
            if (m_auto_build) insert_object_to_tree(geom->nat()-1, index::D(geom->DIM).all(0));
            if (m_auto_bonding) {
                m_make_dirty_dist_map = true;
                find_neighbours(geom->nat()-1, index::D(geom->DIM).all(0));
              }
          }
      }

      ///
      /// \brief inserted
      /// \param at
      /// \param st
      /// \param a
      /// \param r
      ///
      void inserted(int at,
                    before_after st,
                    const STRING & a,
                    const vector3<REAL> & r) override {
        if (st == before_after::after){
            m_ngb_table.resize(geom->nat());
          }
      }

      ///
      /// \brief changed
      /// \param at
      /// \param st
      /// \param a
      /// \param r
      ///
      void changed(int at,
                   before_after st,
                   const STRING & a,
                   const vector3<REAL> & r) override {
        if (st == before_after::after){
            //std::cout << a << " added " << r << std::endl;
            m_ngb_table.resize(geom->nat());
            //std::cout << fmt::format("atom {} changed", at) << std::endl;
            clr_atom_bond_data(at);
            clr_atom_from_tree(at);
            insert_object_to_tree(at);
            m_make_dirty_dist_map = true;
            find_neighbours(at);
          }
      }

      ///
      /// \brief erased
      /// \param at
      /// \param st
      ///
      void erased(int at,
                  before_after st) override {
        if (st == before_after::after){
            //std::cout << a << " added " << r << std::endl;
            m_ngb_table.resize(geom->nat());
          }
      }

      ///
      /// \brief shaded
      /// \param at
      /// \param st
      /// \param sh
      ///
      void shaded(int at,
                  before_after st,
                  bool sh) override {

      }

      ///
      /// \brief reordered
      ///
      void reordered(const std::vector<int> &,
                     before_after) override {

      }

  };


}

#endif
