#ifndef QPP_RTREE_H
#define QPP_RTREE_H

#include <ostream>
#include <unordered_map>
#include <functional>
#include <utility>
#include <set>
#include <algorithm>
#include <cmath>
#include <geom/geom.hpp>
#include <geom/ngbr.hpp>
#include <data/symmetric_key.hpp>
#include <data/ptable.hpp>
#include <geom/aabb.hpp>
#include <geom/ray.hpp>
#include <geom/primitive_intersections.hpp>
#include <data/ptable.hpp>
#include <string>


//#ifdef PY_EXPORT
//#include <pybind11/pybind11.h>
//#include <pybind11/operators.h>
//#include <pybind11/stl.h>
//#include <pyqpp/py_indexed_property.hpp>
//namespace py = pybind11;
//#endif

#define TWS_TREE_DEBUG

namespace qpp{

  template<typename INT_TYPE>
  inline INT_TYPE enc_tws_idx(const INT_TYPE a, const INT_TYPE b,
                              const INT_TYPE c){
    return a*9+b*3+c+13;
  }


  /// rtree node forward declaration                                        ///
  template<typename REAL>
  struct tws_node;

  /// data to store in rtree                                                ///
  template<typename REAL = float>
  struct tws_node_content {
      int atm;
      index idx;

      tws_node_content(const int _atm, const index _idx){
        atm = _atm; idx = _idx;
      }
  };

  template<typename REAL = float>
  struct tws_query_data {
      int atm;
      index idx;
      REAL dist;
      tws_query_data(const int _atm, const index _idx,
                     const REAL _dist = 1000.0f){
        atm = _atm; idx = _idx; dist = _dist;
      }
  };

  template<typename REAL = float>
  bool tws_query_data_sort_by_dist(tws_query_data<REAL> *a,
                                   tws_query_data<REAL> *b){
    return a->dist <= b->dist;
  }

  ///
  /// \brief The tws_node struct
  ///
  template<typename REAL = float>
  struct tws_node {
      tws_node<REAL>* parent;
      aabb_3d<REAL> bb;
      //std::vector<tws_node<REAL>* > childs;
      std::vector<tws_node_content<REAL>* > content;
      std::array<tws_node<REAL>*, 27> sub_nodes {};
      int tot_childs;
      tws_node(){
        tot_childs = 0;
      }
  };


  ///
  /// aux tws tree implementation
  ///
  template <class REAL, class CELL = periodic_cell<REAL> >
  class tws_tree : public geometry_observer<REAL>{
    public:
      REAL fGuessRectSize;
      REAL fMinTWSVolume;
      int DIM;
      geometry<REAL, CELL> *geom;
      tws_node<REAL> *root;
      std::vector<tws_node<REAL>* > flat_view;

      std::unordered_map<qpp::sym_key<int>,
      REAL, qpp::sym_key_hash<int> > distMap;
      std::map<int, REAL> maxDistMap;
      std::vector<std::vector<tws_node_content<REAL>*> > nTable;


      bool bMakeDirtyDistMap;

      ///
      /// \brief bAutoBonding
      ///
      bool bAutoBonding;

      ///
      /// \brief bAutoBuild
      ///
      bool bAutoBuild;

      ///
      /// \brief aux_rtree constructor
      /// \param g
      ///
      tws_tree( geometry<REAL, CELL> & g) {
        geom = & g;
        geom->add_observer(*this);
        DIM = geom -> DIM;
        fGuessRectSize = 6.0f;
        fMinTWSVolume  = 65.0;
        root = nullptr;
        bAutoBonding = false;
        bAutoBuild = true;
        bMakeDirtyDistMap = true;
      }

      ///
      /// \brief check_root
      ///
      void check_root(){
        if (root == nullptr){
            //std::cout << "create root" << std::endl;
            root = new tws_node<REAL>();
            flat_view.push_back(root);
            root->bb.fill_guess(fGuessRectSize);
            if (root->bb.volume() < fMinTWSVolume)
              root->bb.fill_guess(pow(fMinTWSVolume, 1/3.0));
          }

      }

      ///
      /// \brief clear_bonds
      ///
      void clear_ntable(){
        //std::vector<std::vector<tws_node_content<REAL>*> > nTable;
        for (std::vector<tws_node_content<REAL>*> &vPerAtom : nTable){
            for (tws_node_content<REAL> *nc : vPerAtom){
                delete nc;
              }
            vPerAtom.clear();
          }
        nTable.clear();
      }

      ///
      /// \brief clear_tree
      ///
      void clear_tree(){
        for (tws_node<REAL> *node : flat_view)
          delete node;
        flat_view.clear();
      }

      ///
      /// \brief apply_shift
      /// \param vShift
      ///
      void apply_shift(const vector3<REAL> vShift){
        for (tws_node<REAL> *node : flat_view){
            node->bb.min += vShift;
            node->bb.max += vShift;
          }
      }

      ///
      /// \brief apply_visitor
      /// \param f
      ///
      void apply_visitor(std::function<void(tws_node<REAL>*, int)> f){
        traverse_apply_visitor(root, 0, f);
      }

      ///
      /// \brief traverse_apply_visitor
      /// \param curNode
      /// \param f
      ///
      void traverse_apply_visitor(tws_node<REAL> *curNode, int deepLevel,
                                  std::function<void(tws_node<REAL>*, int)> f){
        f(curNode, deepLevel);
        for(tws_node<REAL>* child : curNode->sub_nodes)
          if (child) traverse_apply_visitor(child, deepLevel+1, f);
      }

      ///
      /// \brief query_ray
      /// \param vRayStart
      /// \param vRayDir
      ///
      void query_ray(ray<REAL> *_ray,
                     std::vector<tws_query_data<REAL>*> *res,
                     REAL fScaleFactor = 0.25){
        traverse_query_ray(root, _ray, res, fScaleFactor);
      }

      ///
      /// \brief traverse_query_ray
      /// \param curNode
      /// \param vRayStart
      /// \param vRayDir
      ///
      bool traverse_query_ray(tws_node<REAL> *curNode,
                              ray<REAL> *_ray,
                              std::vector<tws_query_data<REAL>*> *res,
                              const REAL fScaleFactor){

        if (ray_aabb_test(_ray, &(curNode->bb))){
            if (curNode->tot_childs > 0){
                for (tws_node<REAL> *chNode : curNode->sub_nodes)
                  if (chNode) traverse_query_ray(chNode, _ray, res, fScaleFactor);
              }
            else
              for (tws_node_content<REAL> *nc : curNode->content){
                  int ap_idx = ptable::number_by_symbol(geom->atom(nc->atm));

                  //TODO: move magic aRadius
                  REAL fAtRad =
                      ptable::get_inst()->arecs[ap_idx-1].aRadius * fScaleFactor;
                  REAL fStoredDist = 0.0;
                  REAL fRayHitDist = ray_sphere_test( _ray,
                                                      geom->pos(nc->atm, nc->idx),
                                                      fAtRad);
                  bool bRayHit = fRayHitDist > -1.0f;

                  if(bRayHit){
                      tws_query_data<REAL>* newd = new tws_query_data<REAL>(
                                                     nc->atm, nc->idx,
                                                     fRayHitDist);
                      res->push_back(newd);
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
      void query_sphere(const REAL fSphRad,
                        const vector3<REAL> vSphCnt,
                        std::vector<tws_node_content<REAL>*> *res){
        traverse_query_sphere(root, fSphRad, vSphCnt, res);
      }

      ///
      /// \brief traverse_query_sphere
      /// \param curNode
      /// \param fSphRad
      /// \param vSphCnt
      /// \param res
      ///
      void traverse_query_sphere(
          tws_node<REAL> *curNode,
          const REAL fSphRad,
          const vector3<REAL> vSphCnt,
          std::vector<tws_node_content<REAL>*> *res){


        if (curNode->bb.test_sphere(fSphRad, vSphCnt)){

            for (tws_node<REAL> *child : curNode->sub_nodes)
              if (child) traverse_query_sphere(child, fSphRad, vSphCnt, res);

            for (tws_node_content<REAL>* cnt : curNode->content)
              if ((vSphCnt - geom->r(cnt->atm, cnt->idx)).norm() <= fSphRad)
                res->push_back(cnt);
          }
      }

      ///
      /// \brief Insert oject to tree
      /// \param atm
      /// \param idx
      ///
      void insert_object_to_tree(const int atm, const index & idx){
        check_root();
        while (!(point_aabb_test(geom->r(atm, idx), root->bb)) ) {
            grow_tws_root(atm, idx);
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
      bool traverse_insert_object_to_tree( tws_node<REAL> *curNode,
                                           const int atm, const index & idx){

        vector3<REAL> p = geom->r(atm, idx);
        vector3<REAL> cn_size = curNode->bb.max - curNode->bb.min;
        vector3<REAL> cn_center = curNode->bb.center();

        bool bInCurRect = point_aabb_test(p, curNode->bb);
        if (!bInCurRect) return false;

        if (bInCurRect){
            // point in box and we reach minimum volume
            if (curNode->bb.volume() / 27.0 <= fMinTWSVolume){
                push_data_to_tws_node(curNode, atm, idx);
                return true;
              }
                //it is necessary to determine the indexes of the point
                int i_x = -1 + int((p[0]-curNode->bb.min[0])/(cn_size[0]/3));
                int i_y = -1 + int((p[1]-curNode->bb.min[1])/(cn_size[1]/3));
                int i_z = -1 + int((p[2]-curNode->bb.min[2])/(cn_size[2]/3));
                int nidx = enc_tws_idx(i_x, i_y, i_z);

                if (curNode->sub_nodes[nidx] == nullptr){

                    tws_node<REAL> *newNode = new tws_node<REAL>();
                    flat_view.push_back(newNode);
                    //define the 0,0,0 max min
                    vector3<REAL> z_min = curNode->bb.min + cn_size / 3;
                    vector3<REAL> z_max = curNode->bb.max - cn_size / 3;

                    newNode->bb.min = z_min + vector3<REAL>
                                      (i_x * cn_size[0]/ 3, i_y * cn_size[1]/ 3, i_z * cn_size[2]/ 3);
                    newNode->bb.max = z_max + vector3<REAL>
                                      (i_x * cn_size[0]/ 3, i_y * cn_size[1]/ 3, i_z * cn_size[2]/ 3);

                    curNode->sub_nodes[nidx] = newNode;
                    curNode->tot_childs+=1;
                  }

                traverse_insert_object_to_tree(curNode->sub_nodes[nidx],
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
      void push_data_to_tws_node(tws_node<REAL> *curNode, const int atm,
                                 const index & idx){
        tws_node_content<REAL>* cnt = new tws_node_content<REAL>(atm, idx);
        curNode->content.push_back(cnt);
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
        tws_node<REAL>* oldRoot = root;
        root = nullptr;

        tws_node<REAL>* newRoot = new tws_node<REAL>();
        flat_view.push_back(newRoot);

        vector3<REAL> vSize = (oldRoot->bb.max - oldRoot->bb.max);
        newRoot->bb.min = oldRoot->bb.min * (3.0);
        newRoot->bb.max = oldRoot->bb.max * (3.0);
        newRoot->parent = nullptr;

        newRoot->sub_nodes[enc_tws_idx(0,0,0)] = oldRoot;
        newRoot->tot_childs += 1;
        oldRoot->parent = newRoot;

        root = newRoot;

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
      /// \brief split_tws_node
      /// \param curNode
      ///
      //      void split_tws_node(tws_node<REAL> *curNode){
      //        vector3<REAL> vSize = (curNode->bb.max - curNode->bb.min)/6.0;
      //        vector3<REAL> vCntr = (curNode->bb.max+ curNode->bb.min)/2.0;

      //        for (int ix = -1; ix < 2; ix++)
      //          for (int iy = -1; iy < 2; iy++)
      //            for (int iz = -1; iz < 2; iz++){
      //                tws_node<REAL>* nNode = new tws_node<REAL>();

      //                nNode->bb.min =
      //                    vCntr - vSize + vector3<REAL>(ix * vSize[0] * 2,
      //                    iy * vSize[1] * 2,
      //                    iz * vSize[2] * 2);

      //                nNode->bb.max =
      //                    vCntr + vSize + vector3<REAL>(ix * vSize[0] * 2,
      //                    iy * vSize[1] * 2,
      //                    iz * vSize[2] * 2);

      //                curNode->childs.push_back(nNode);
      //              }
      //      }


      ///
      /// \brief n
      /// \param i
      /// \return
      ///
      int n(int i) const {return nTable[i].size();}

      ///
      /// \brief table
      /// \param i
      /// \param j
      /// \return
      ///
      index table_idx(int i, int j) const {return nTable[i][j]->idx;}
      int   table_atm(int i, int j) const {return nTable[i][j]->atm;}

      void rebuild_dist_map(){
        //TODO: make it more ellegant
        distMap.clear();
        maxDistMap.clear();
        for (int i = 0; i < geom->n_atom_types(); i++){
            REAL fMaxBondRad = 0.0;
            for (int j = 0; j <  geom->n_atom_types(); j++){
                int pTableIdx1 = ptable::number_by_symbol(geom->atom_of_type(i));
                int pTableIdx2 = ptable::number_by_symbol(geom->atom_of_type(j));
                REAL fBondRad1 = ptable::cov_rad_by_number(pTableIdx1);
                REAL fBondRad2 = ptable::cov_rad_by_number(pTableIdx2);


                if ((fBondRad1 >0) && (fBondRad2 > 0))
                  distMap[sym_key<int>(i,j)] = fBondRad1 + fBondRad2;

                std::cout << "bondrad " << "["<< i << ", " << j<< "] "<<
                             geom->atom_of_type(i) << " " <<
                             geom->atom_of_type(j) << " " <<
                             fBondRad1 << " " << fBondRad2 << " " <<
                             pTableIdx1 << " " << pTableIdx2 << " " <<
                             distMap[sym_key<int>(i,j)] << std::endl;

                fMaxBondRad = std::max(fMaxBondRad, fBondRad1 + fBondRad2);
              }
            maxDistMap[i] = fMaxBondRad;
          }
        bMakeDirtyDistMap = false;
      }

      ///
      /// \brief add_ngbr
      /// \param ha
      /// \param i
      /// \param j
      ///
      void add_ngbr(int ha, int i, const index & j){
        bool found = false;
        for (int k = 0; k < nTable[ha].size(); k++ )
          if ((nTable[ha][k]->atm == i ) && (nTable[ha][k]->idx == j)){
              found = true;
              break;
            }

        if (!found){
            tws_node_content<REAL>* newTableEntry =
                new tws_node_content<REAL>(i, j);
            nTable[ha].push_back(newTableEntry);
          }
      }

      ///
      /// \brief find_all_neighbours
      ///
      void find_all_neighbours(){
        for (int i = 0; i < geom->nat(); i++)
          find_neighbours(i);
      }

      ///
      /// \brief find_neighbours
      /// \param atNum
      ///
      void find_neighbours(int atNum){
        if (!root) return;

        if (bMakeDirtyDistMap) {
            rebuild_dist_map();
            if (nTable.size() < geom->nat()) nTable.resize(geom->nat());
          }

        REAL fSphRad = maxDistMap[geom->type_table(atNum)];
        if ( fSphRad > 0.0){

            std::vector<tws_node_content<REAL>*> res;
            query_sphere(fSphRad, geom->pos(atNum), &res);

            for (tws_node_content<REAL> *r_el : res){
                vector3<REAL> pos1 = geom->pos(atNum);
                vector3<REAL> pos2 = geom->pos(r_el->atm, r_el->idx);
                REAL fDr = (pos1 - pos2).norm();

                REAL fBondLength = distMap[sym_key<int>(
                                     geom->type_table(atNum),
                                     geom->type_table(r_el->atm))];
                if ((fDr < fBondLength) &&
                    !(( atNum == r_el->atm) && (r_el->idx == index({0,0,0})))){
                    add_ngbr(atNum, r_el->atm, r_el->idx);
                    if (r_el->idx == index({0,0,0}))
                      add_ngbr(r_el->atm, atNum , r_el->idx);
                  }
              }
          }
      }

      ///
      /// \brief manual_build
      ///
      void manual_build(){
        for (int i = 0; i < geom->nat(); i++)
          insert_object_to_tree(i, index({0,0,0}));
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
      void debug_print_traverse(tws_node<REAL> *node, int iDeepLevel,
                                int &totalEntries){

        REAL fAABBFakeVol = 1.0;
        for (unsigned int i = 0; i < DIM_RECT; i++)
          fAABBFakeVol *= node->bb.max[i]-node->bb.min[i];
        std::cout << std::string(iDeepLevel, '>')
                  << "node vol = "<< fAABBFakeVol <<" " << node->bb << " "
                  << node->content.size()<< std::endl;
        totalEntries += node->content.size();

        for (tws_node<REAL>* _node : node->sub_nodes)
          if (_node)
            debug_print_traverse(_node, iDeepLevel+1, totalEntries);

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
            //std::cout << a << " added " << r << std::endl;


            nTable.resize(geom->nat());
            if (bAutoBuild)
              insert_object_to_tree(geom->nat()-1, index({0,0,0}));

            if(bAutoBonding) {
                //std::cout << "autobond " << geom->n_types() << std::endl;
                bMakeDirtyDistMap = true;
                find_neighbours(geom->nat()-1);
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
            nTable.resize(geom->nat());
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
            nTable.resize(geom->nat());
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
            nTable.resize(geom->nat());
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
