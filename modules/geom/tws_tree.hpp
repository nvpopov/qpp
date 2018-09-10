#ifndef QPP_RTREE_H
#define QPP_RTREE_H

#include <ostream>
#include <unordered_map>
#include <functional>
#include <utility>
#include <set>
#include <algorithm>
#include <cmath>
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
        return (idx == index::D(DIM).all(0));
      }
  };

  /// rtree node forward declaration                                        ///
  template<typename REAL>
  struct tws_node_t;

  /// data to store in rtree                                                ///
  template<typename REAL = float>
  struct tws_node_content_t {
      int atm;
      index idx;
      tws_node_content_t(const int _atm, const index _idx){
        atm = _atm; idx = _idx;
      }
  };

  ///
  /// \brief The imaginary_atom struct
  ///
  template<typename REAL>
  struct imaginary_atom_t {
      uint16_t atm;
      index idx;
      bool selected;
      tws_node_t<REAL> *parent;
      vector<tws_node_content_t<REAL> > img_bonds;
      imaginary_atom_t(const int _atm, const index _idx){
        atm = _atm; idx = _idx; selected = false;
      }
      ~imaginary_atom_t() = default;
  };

  template<typename REAL = float>
  struct tws_query_data_t {
      uint16_t atm;
      index idx;
      REAL dist;
      tws_query_data_t(const int _atm, const index _idx,
                       const REAL _dist = 1000.0f){
        atm = _atm; idx = _idx; dist = _dist;
      }

      bool operator == (const tws_query_data_t<REAL> &a){
        return (idx == a.idx) && (atm == a.atm);
      }

      tws_query_data_t<REAL>& operator =(const tws_query_data_t<REAL> &a){
        idx = a.idx;
        atm = a.atm;
        dist = a.dist;
        return *this;
      }

      tws_query_data_t<REAL>(const tws_query_data_t<REAL>& a){
        idx = a.idx;
        atm = a.atm;
        dist = a.dist;
      }
  };

  template<typename REAL = float>
  bool tws_query_data_sort_by_dist(tws_query_data_t<REAL> &a, tws_query_data_t<REAL> &b){
    return a.dist <= b.dist;
  }

  ///
  /// \brief The tws_node struct
  ///
  template<typename REAL = float>
  struct tws_node_t {
      tws_node_t<REAL>* parent;
      aabb_3d_t<REAL> bb;
      vector<tws_node_content_t<REAL> > content;
      array<tws_node_t<REAL>*, 27> sub_nodes {};
      int tot_childs;
      tws_node_t(){
        tot_childs = 0;
      }

      void remove_single_content_by_id(const int atm){
        for (auto it = content.begin(); it != content.end();){
            if(it->atm == atm) it = content.erase(it);
            else ++it;
          }
      }

      void remove_single_content_by_id_with_index_store(const int atm, vector<index> &idx_vec){
        for (auto it = content.begin(); it != content.end();){
            if(it->atm == atm){
                idx_vec.push_back(it->idx);
                it = content.erase(it);
              }
            else ++it;
          }
      }

      bool operator == (const tws_node_t<REAL> &a){
        return this == a;
      }
  };


  template<typename REAL>
  struct atom_node_lookup_t {
      index idx;
      tws_node_t<REAL> *node;
      atom_node_lookup_t(const index _idx, tws_node_t<REAL> *_node){
        idx = _idx; node = _node;
      }
  };

  ///
  /// aux tws tree implementation
  ///
  template <class REAL, class CELL = periodic_cell<REAL> >
  class tws_tree_t : public geometry_observer<REAL>{
    public:
      REAL guess_rect_size;
      REAL min_tws_volume;
      int DIM;
      geometry<REAL, CELL>                       *geom;
      tws_node_t<REAL>                           *root;
      vector<tws_node_t<REAL>* >                 flat_view;
      vector<imaginary_atom_t<REAL> >            img_atoms;
      vector<vector<tws_node_content_t<REAL> > > ngb_table;
      vector<vector<atom_node_lookup_t<REAL> > >   atom_node_lookup;
      unordered_map<qpp::sym_key<int>, REAL, sym_key_hash<int> > dist_map;
      map<int, REAL> max_dist_map;

      //      std::vector<tws_node_t<REAL>* > map_atom_to_node;
      //      std::vector<tws_node_t<REAL>* > map_img_atom_to_node;
      bool make_dirty_dist_map;

      ///
      /// \brief bAutoBonding
      ///
      bool auto_bonding;

      ///
      /// \brief bAutoBuild
      ///
      bool auto_build;


      ///
      /// \brief bBuildImaginaryAtomsBonds
      ///
      bool build_imaginary_atoms_bonds;

      ///
      /// \brief aux_rtree constructor
      /// \param g
      ///
      tws_tree_t( geometry<REAL, CELL> & g) {
        geom = & g;
        geom->add_observer(*this);
        DIM = geom -> DIM;
        guess_rect_size = 6.0f;
        min_tws_volume  = 65.0;
        root = nullptr;
        auto_bonding = false;
        auto_build = true;
        make_dirty_dist_map = true;
        build_imaginary_atoms_bonds = true;
      }

      ///
      /// \brief check_root
      ///
      void check_root(){
        if (root == nullptr){
            //std::cout << "create root" << std::endl;
            root = new tws_node_t<REAL>();
            flat_view.push_back(root);
            root->bb.fill_guess(guess_rect_size);
            if (root->bb.volume() < min_tws_volume)
              root->bb.fill_guess(pow(min_tws_volume, 1/3.0));
          }

      }

      int find_imaginary_atom(const int atm, const index idx){
        for (uint16_t i = 0; i < img_atoms.size(); i++)
          if (img_atoms[i].atm == atm && img_atoms[i].idx == idx)
            return i;
        return -1;
      }

      int find_imaginary_atom_by_id(const int atm){
        for (uint16_t i = 0; i < img_atoms.size(); i++)
          if (img_atoms[i].atm == atm)
            return i;
        return -1;
      }

      ///
      /// \brief clear_bonds
      ///
      void clr_ntable(){
        for (auto &per_atom : ngb_table) per_atom.clear();
        ngb_table.clear();
      }

      void clr_bond_real_im(const int atm1, const int atm2, const index idx2){
        for(auto it = ngb_table[atm1].begin(); it != ngb_table[atm1].end(); )
          if(it->atm == atm2 && it->idx == idx2)
            ngb_table[atm1].erase(it);
          else ++it;
      }

      void clr_bond_im_real(const int img_atom_id, const int atm2, const index idx2){
        for(auto it = img_atoms[img_atom_id].begin(); it != img_atoms[img_atom_id].end(); )
          if(it->atm == atm2 && it->idx == idx2)
            img_atoms[img_atom_id].erase(it);
          else ++it;
      }

      void clr_bond_im_real(const int img_atom_id, const int atm2){
        for(auto it = img_atoms[img_atom_id].img_bonds.begin();
            it != img_atoms[img_atom_id].img_bonds.end(); )
          if(it->atm == atm2)
            img_atoms[img_atom_id].img_bonds.erase(it);
          else ++it;
      }

      ///
      /// \brief clear_atom_bonding_data
      /// \param atm
      ///
      void clr_atom_bond_data(const int atm){
        for(auto &bond : ngb_table[atm])
          if (bond.idx == index::D(geom->DIM).all(0) || geom->DIM == 0)
            clr_atom_pair_bond_data(bond.atm, atm);
          else {
              int img_id = find_imaginary_atom(bond.atm, bond.idx);
              if (img_id != -1) clr_bond_im_real(img_id, atm);
            }
        ngb_table[atm].clear();
      }

      ///
      /// \brief clear_atom_pair_bonding_data
      /// \param atm1
      /// \param atm2
      ///
      void clr_atom_pair_bond_data(const int atm1, const int atm2){
        if (ngb_table[atm1].size() > 0){
            auto new_end = std::remove_if(ngb_table[atm1].begin(), ngb_table[atm1].end(),
                                          [&atm2](tws_node_content_t<REAL> & bonds)
            { return bonds.atm == atm2; });
            ngb_table[atm1].erase(new_end);
          }
      }

      ///
      /// \brief clear_atom_from_tree
      /// \param atm
      ///
      void clr_atom_from_tree(const int atm){
        if (geom->DIM == 0 && atom_node_lookup[atm].size() > 0)
          atom_node_lookup[atm][0].node->remove_single_content_by_id(atm);

        if (geom->DIM > 0){
            vector<index> image_idx;

            //remove 0,0,0 and c1,c2,c3 atoms from tree
            for (auto& at_node : atom_node_lookup[atm])
              at_node.node->remove_single_content_by_id_with_index_store(atm, image_idx);

            //iterate over imaginary atoms, store secondary imaginary atom, erase required atom
            vector<int> pair_img_atoms;
            for (auto it = img_atoms.begin(); it != img_atoms.end();)
              if (it->atm == atm){
                  for(auto &nc : it->img_bonds)
                    if (nc.idx != index::D(geom->DIM).all(0)) pair_img_atoms.push_back(nc.atm);
                    else clr_bond_real_im(nc.atm, it->atm, it->idx);
                      it = img_atoms.erase(it);
                } else ++it;

            //delete bonds from paired imaginary atoms
            for (auto &pair : pair_img_atoms){
                int paired_img_id = find_imaginary_atom_by_id(pair);
                if (paired_img_id > -1){
                    for (auto it = img_atoms[paired_img_id].img_bonds.begin();
                         it != img_atoms[paired_img_id].img_bonds.end();){
                        if (it->atm == atm) it = img_atoms[paired_img_id].img_bonds.erase(it);
                        else ++it;
                      }
                  }
              }

          }
        //tws_node_t<REAL> *node = atom_node_lookup[]
        atom_node_lookup[atm].clear();
      }


      ///
      /// \brief clear_tree
      ///
      void clr_tree(){
        for (auto *node : flat_view){
            if (node) delete node;
            node = nullptr;
          }
        flat_view.clear();
      }

      ///
      /// \brief apply_shift
      /// \param vShift
      ///
      void apply_shift(const vector3<REAL> vec_shift){
        for (auto *node : flat_view){
            node->bb.min += vec_shift;
            node->bb.max += vec_shift;
          }
      }

      ///
      /// \brief apply_visitor
      /// \param f
      ///
      void apply_visitor(function<void(tws_node_t<REAL>*, int)> f){
        traverse_apply_visitor(root, 0, f);
      }

      ///
      /// \brief traverse_apply_visitor
      /// \param curNode
      /// \param f
      ///
      void traverse_apply_visitor(tws_node_t<REAL> *cur_node, int deep_level,
                                  function<void(tws_node_t<REAL>*, int)> f){
        f(cur_node, deep_level);
        for(auto* child : cur_node->sub_nodes)
          if (child) traverse_apply_visitor(child, deep_level+1, f);
      }

      ///
      /// \brief query_ray
      /// \param vRayStart
      /// \param vRayDir
      ///
      template<typename adding_result_policy = query_ray_add_all<REAL> >
      void query_ray(ray_t<REAL> *_ray,
                     vector<tws_query_data_t<REAL> > &res,
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
      bool traverse_query_ray(tws_node_t<REAL> *cur_node,
                              ray_t<REAL> *_ray,
                              vector<tws_query_data_t<REAL> > &res,
                              const REAL scale_factor){

        if (ray_aabb_test(_ray, &(cur_node->bb))){
            if (cur_node->tot_childs > 0){
                for (auto *ch_node : cur_node->sub_nodes)
                  if (ch_node)
                    traverse_query_ray<adding_result_policy>(ch_node, _ray, res, scale_factor);
              } else
              for (auto &nc : cur_node->content){
                  int ap_idx = ptable::number_by_symbol(geom->atom(nc.atm));

                  //TODO: move magic aRadius
                  REAL fAtRad =
                      ptable::get_inst()->arecs[ap_idx-1].aRadius * scale_factor;
                  REAL fStoredDist = 0.0;
                  vector3<REAL> vTestPos = geom->pos(nc.atm, nc.idx);
                  REAL ray_hit_dist = ray_sphere_test( _ray, vTestPos,fAtRad);
                  bool bRayHit = ray_hit_dist > -1.0f;

                  if (bRayHit) {
                      if (adding_result_policy::can_add(vTestPos, nc.idx, geom->DIM))
                        res.push_back(tws_query_data_t<REAL>(nc.atm, nc.idx, ray_hit_dist));
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
      void query_sphere(const REAL sph_r, const vector3<REAL> sph_cnt,
                        vector<tws_node_content_t<REAL> > &res){
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
          tws_node_t<REAL> *cur_node,
          const REAL &sph_r,
          const vector3<REAL> &sph_cnt,
          vector<tws_node_content_t<REAL> > &res){

        if (cur_node->bb.test_sphere(sph_r, sph_cnt)){

            for (auto *child : cur_node->sub_nodes)
              if (child) traverse_query_sphere(child, sph_r, sph_cnt, res);

            for (auto &cnt : cur_node->content)
              if ((sph_cnt - geom->pos(cnt.atm, cnt.idx)).norm() <= sph_r)
                res.push_back(tws_node_content_t<REAL>(cnt.atm, cnt.idx));
          }
      }

      //
      void insert_object_to_tree(const int atm){
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
      void insert_object_to_tree(const int atm, const index idx){
        check_root();
        int q = 0;
        if (atom_node_lookup.size() != geom->size()) atom_node_lookup.resize(geom->size());
        while (!(point_aabb_test(geom->pos(atm, idx), root->bb)) ) {
            grow_tws_root(atm, idx);
            q++;

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
      bool traverse_insert_object_to_tree(tws_node_t<REAL> *cur_node, const int atm,
                                          const index & idx){

        vector3<REAL> p = geom->pos(atm, idx);
        vector3<REAL> cn_size = cur_node->bb.max - cur_node->bb.min;
        vector3<REAL> cn_center = cur_node->bb.center();

        bool bInCurRect = point_aabb_test(p, cur_node->bb);
        if (!bInCurRect) return false;

        if (bInCurRect){
            // point in box and we reach minimum volume
            if (cur_node->bb.volume() / 27.0 <= min_tws_volume){
                push_data_to_tws_node(cur_node, atm, idx);
                return true;
              }

            //it is necessary to determine the indexes of the point
            int i_x = -1 + int((p[0]-cur_node->bb.min[0])/(cn_size[0]/3));
            int i_y = -1 + int((p[1]-cur_node->bb.min[1])/(cn_size[1]/3));
            int i_z = -1 + int((p[2]-cur_node->bb.min[2])/(cn_size[2]/3));
            int nidx = enc_tws_idx(i_x, i_y, i_z);

            if (cur_node->sub_nodes[nidx] == nullptr){

                tws_node_t<REAL> *newNode = new tws_node_t<REAL>();
                flat_view.push_back(newNode);
                //define the 0,0,0 max min
                vector3<REAL> z_min = cur_node->bb.min + cn_size / 3;
                vector3<REAL> z_max = cur_node->bb.max - cn_size / 3;

                newNode->bb.min = z_min + vector3<REAL>(
                                    i_x * cn_size[0]/ 3,
                    i_y * cn_size[1]/ 3,
                    i_z * cn_size[2]/ 3);
                newNode->bb.max = z_max + vector3<REAL>(
                                    i_x * cn_size[0]/ 3,
                    i_y * cn_size[1]/ 3,
                    i_z * cn_size[2]/ 3);

                cur_node->sub_nodes[nidx] = newNode;
                cur_node->tot_childs+=1;
              }

            traverse_insert_object_to_tree(cur_node->sub_nodes[nidx],
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
      void push_data_to_tws_node(tws_node_t<REAL> *cur_node, const int atm, const index idx){
        //pass any atom with any index to tws-tree
        cur_node->content.push_back(tws_node_content_t<REAL>(atm, idx));

        //pass any atom and store index to lookup struct
        atom_node_lookup[atm].push_back(atom_node_lookup_t<REAL>(idx, cur_node));

        if ( geom->DIM > 0 && idx != index::D(geom->DIM).all(0))
          img_atoms.push_back(imaginary_atom_t<REAL>(atm, idx));

      }


      ///
      /// \brief grow_tws_root
      /// \param atm
      /// \param idx
      ///
      void grow_tws_root( const int atm, const index & idx){

#ifdef TWS_TREE_DEBUG
        std::cout<<fmt::format(">>> pre grow vol={} {} {} {} nc = {}",
                               root->bb.volume(),
                               geom->pos(atm,idx)[0],
            geom->pos(atm,idx)[1],
            geom->pos(atm,idx)[2],
            root->tot_childs) << root->bb <<std::endl;
#endif
        tws_node_t<REAL>* old_root = root;
        root = nullptr;

        tws_node_t<REAL>* new_root = new tws_node_t<REAL>();
        flat_view.push_back(new_root);

        vector3<REAL> vSize = (old_root->bb.max - old_root->bb.max);
        new_root->bb.min = old_root->bb.min * (3.0);
        new_root->bb.max = old_root->bb.max * (3.0);
        new_root->parent = nullptr;

        new_root->sub_nodes[enc_tws_idx(0,0,0)] = old_root;
        new_root->tot_childs += 1;
        old_root->parent = new_root;

        root = new_root;

#ifdef TWS_TREE_DEBUG
        std::cout<<fmt::format(">>> post grow vol={} {} {} {} nc = {}",
                               root->bb.volume(),
                               geom->pos(atm,idx)[0],
            geom->pos(atm,idx)[1],
            geom->pos(atm,idx)[2],
            root->tot_childs) << root->bb <<std::endl;
#endif
      }

      ///
      /// \brief n
      /// \param i
      /// \return
      ///
      int n(int i) const {return ngb_table[i].size();}

      ///
      /// \brief table
      /// \param i
      /// \param j
      /// \return
      ///
      index table_idx(int i, int j) const {return ngb_table[i][j].idx;}
      int   table_atm(int i, int j) const {return ngb_table[i][j].atm;}

      void rebuild_dist_map(){
        //TODO: make it more ellegant
        dist_map.clear();
        max_dist_map.clear();
        for (int i = 0; i < geom->n_atom_types(); i++){
            REAL max_bond_rad = 0.0;
            for (int j = 0; j <  geom->n_atom_types(); j++){
                int table_idx1  = ptable::number_by_symbol(geom->atom_of_type(i));
                int table_idx2  = ptable::number_by_symbol(geom->atom_of_type(j));
                REAL bond_rad_1 = ptable::cov_rad_by_number(table_idx1);
                REAL bond_rad_2 = ptable::cov_rad_by_number(table_idx2);


                if (bond_rad_1 > 0 && bond_rad_2 > 0)
                  dist_map[sym_key<int>(i,j)] = bond_rad_1 + bond_rad_2;
                //#ifdef TWS_TREE_DEBUG
                //                std::cout << "bondrad " << "["<< i << ", " << j<< "] "<<
                //                             geom->atom_of_type(i) << " " <<
                //                             geom->atom_of_type(j) << " " <<
                //                             bond_rad_1 << " " << bond_rad_2 << " " <<
                //                             table_idx1 << " " << table_idx2 << " " <<
                //                             dist_map[sym_key<int>(i,j)] << std::endl;
                //#endif
                max_bond_rad = std::max(max_bond_rad, bond_rad_1 + bond_rad_2);
              }
            max_dist_map[i] = max_bond_rad;
          }
        make_dirty_dist_map = false;
      }

      ///
      /// \brief add_ngbr
      /// \param ha
      /// \param i
      /// \param j
      ///
      void add_ngbr(int ha, int i, const index j){
        bool found = false;
        for (int k = 0; k < ngb_table[ha].size(); k++ )
          if ((ngb_table[ha][k].atm == i ) && (ngb_table[ha][k].idx == j)){
              found = true;
              break;
            }

        if (!found) ngb_table[ha].push_back(tws_node_content_t<REAL>(i, j));
      }

      ///
      /// \brief find_all_neighbours
      ///
      void find_all_neighbours(){
        for (int i = 0; i < geom->nat(); i++) find_neighbours(i, index::D(geom->DIM).all(0));
        if (build_imaginary_atoms_bonds)
          for (int i = 0; i < img_atoms.size(); i++)
            find_neighbours(img_atoms[i].atm, img_atoms[i].idx, true);
      }

      ///
      /// \brief find_neighbours
      /// \param at_num
      ///
      void find_neighbours(int at_num){
        find_neighbours(at_num, index::D(geom->DIM).all(0));
        if (build_imaginary_atoms_bonds)
          for (int i = 0; i < img_atoms.size(); i++)
            if (img_atoms[i].atm == at_num)
              find_neighbours(img_atoms[i].atm, img_atoms[i].idx, true);
      }

      ///
      /// \brief find_neighbours
      /// \param atNum
      ///
      void find_neighbours(int at_num, index idx, bool imaginary_pass = false){
        if (!root) return;

        if (make_dirty_dist_map) {
            rebuild_dist_map();
            if (ngb_table.size() < geom->nat()) ngb_table.resize(geom->nat());
          }

        REAL sph_r = max_dist_map[geom->type_table(at_num)];
        if ( sph_r > 0.0){

            vector<tws_node_content_t<REAL> > res;
            query_sphere(sph_r, geom->pos(at_num, idx), res);

            for (auto &r_el : res){
                vector3<REAL> pos1 = geom->pos(at_num, idx);
                vector3<REAL> pos2 = geom->pos(r_el.atm, r_el.idx);

                REAL f_dr = (pos1 - pos2).norm();

                REAL bond_len = dist_map[sym_key<int>(
                                  geom->type_table(at_num),
                                  geom->type_table(r_el.atm))];

                //cache comparison data
                bool first_real      = idx == index::D(geom->DIM).all(0);
                bool second_real          = r_el.idx == index::D(geom->DIM).all(0);
                bool first_im        = !first_real;
                bool second_im       = !second_real;
                bool mixed_real_im   = (first_real && second_im) || (first_im && second_real);
                bool both_atoms_real = first_real && second_real;
                bool both_atoms_im   = first_im && second_im;

                //both atoms are real
                if (!imaginary_pass && f_dr < bond_len && both_atoms_real  &&
                    (at_num != r_el.atm || idx != r_el.idx)){
                    add_ngbr(at_num, r_el.atm, r_el.idx);
                    add_ngbr(r_el.atm, at_num , r_el.idx);
                  }

                //mixed
                if (f_dr < bond_len && mixed_real_im){
                    //determine who is who
                    int mx_at1_num = -1;
                    int mx_at2_num = -1;
                    index mx_at1_idx, mx_at2_idx;

                    if (first_real){
                        mx_at1_num = at_num;
                        mx_at1_idx = idx;
                        mx_at2_num = r_el.atm;
                        mx_at2_idx = r_el.idx;
                      } else {
                        mx_at1_num = r_el.atm;
                        mx_at1_idx = r_el.idx;
                        mx_at2_num = at_num;
                        mx_at2_idx = idx;
                      }

                    // add real bond
                    add_ngbr(mx_at1_num, mx_at2_num, mx_at2_idx);

                    // add imaginary bond
                    int iat = find_imaginary_atom(mx_at2_num, mx_at2_idx);
                    if (iat > -1)
                      img_atoms[iat].img_bonds.push_back(
                            tws_node_content_t<REAL>(mx_at1_num, mx_at1_idx));
                  }


                //two imaginary atoms
                if (imaginary_pass && build_imaginary_atoms_bonds && f_dr < bond_len &&
                    both_atoms_im){

                    int iat1 = -1, iat2 = -1;
                    iat1 = find_imaginary_atom(at_num, idx);
                    iat2 = find_imaginary_atom(r_el.atm, r_el.idx);

                    if (iat1 > -1  && iat2 > -1 ){

                        img_atoms[iat1].img_bonds.push_back(
                              tws_node_content_t<REAL>(r_el.atm, r_el.idx));

                        img_atoms[iat2].img_bonds.push_back(
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

        //        std::cout<<geom->r(0, index({0,1,1})).to_string_vec()<<std::endl;
        //        std::cout<<geom->cell.cart2frac(geom->r(0, index({0,0,0}))).to_string_vec()<<std::endl;
        //        std::cout<<geom->cell.cart2frac(geom->r(0, index({0,0,1}))).to_string_vec()<<std::endl;
        //        std::cout<<geom->cell.cart2frac(geom->r(0, index({1,1,1}))).to_string_vec()<<std::endl;

        for (int i = 0; i < geom->nat(); i++) insert_object_to_tree(i);
      }

      ///
      /// \brief debug_print
      ///
      void debug_print(){
        int totalEntries = 0;
        debug_print_traverse(root, 1, totalEntries);
        std::cout << "Total entries = " << totalEntries << std::endl;
      }

      ///
      /// \brief debug_print_traverse
      /// \param node
      /// \param iDeepLevel
      /// \param totalEntries
      ///
      void debug_print_traverse(tws_node_t<REAL> *node, int deep_level,
                                int &tot_entries){

        REAL fake_aabb_vol = 1.0;
        for (unsigned int i = 0; i < DIM_RECT; i++)
          fake_aabb_vol *= node->bb.max[i]-node->bb.min[i];
        std::cout << std::string(deep_level, '>')
                  << "node vol = "<< fake_aabb_vol <<" " << node->bb << " "
                  << node->content.size()<< std::endl;
        tot_entries += node->content.size();

        for (tws_node_t<REAL>* _node : node->sub_nodes)
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
            ngb_table.resize(geom->nat());
            if (auto_build) insert_object_to_tree(geom->nat()-1, index::D(geom->DIM).all(0));
            if (auto_bonding) {
                make_dirty_dist_map = true;
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
            //std::cout << a << " added " << r << std::endl;
            ngb_table.resize(geom->nat());
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
            ngb_table.resize(geom->nat());
            //std::cout << fmt::format("atom {} changed", at) << std::endl;
            clr_atom_bond_data(at);
            clr_atom_from_tree(at);
            insert_object_to_tree(at);
            make_dirty_dist_map = true;
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
            ngb_table.resize(geom->nat());
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
