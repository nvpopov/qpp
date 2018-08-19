#ifndef _QPP_RTREE_H
#define _QPP_RTREE_H

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
#include <string>

//#ifdef PY_EXPORT
//#include <pybind11/pybind11.h>
//#include <pybind11/operators.h>
//#include <pybind11/stl.h>
//#include <pyqpp/py_indexed_property.hpp>
//namespace py = pybind11;
//#endif

namespace qpp{

  const uint DIM_RECT = 3;

  /// rtree multidimensional box
  template<typename REAL = float>
  struct rtree_box_nd {
    vector3<REAL> rect_max;
    vector3<REAL> rect_min;

    ///
    /// \brief is_overlap
    /// \param box
    /// \return
    ///
    bool is_overlap(const rtree_box_nd<REAL> *box){
      for (uint i = 0; i < DIM_RECT; i++)
        if ((this->rect_min[i] <= box->rect_max[i]) ||
            (this->rect_max[i] >= box->rect_min[i])) return false;
      return true;
    }


    ///
    /// \brief squared_dist_point_check
    /// \param pn
    /// \param bmin
    /// \param bmax
    /// \return
    ///
    REAL squared_dist_point_check(const REAL pn,
                                  const REAL bmin,
                                  const REAL bmax){
      REAL out = 0; REAL v = pn;
      if ( v < bmin ){ REAL val = (bmin - v); out += val * val; }
      if ( v > bmax ){ REAL val = (v - bmax); out += val * val; }
      return out;
    }

    ///
    /// \brief squared_dist_point
    /// \param point
    /// \return
    ///
    REAL squared_dist_point(const vector3<REAL> point){
      REAL sq = 0.0;

      for(int i = 0; i < DIM_RECT; i++)
        sq += squared_dist_point_check( point[i], rect_min[i], rect_max[i] );

      return sq;
    }

    ///
    /// \brief test_aganist_sphere
    /// \param fSphRad
    /// \param vSphCnt
    /// \return
    ///
    bool test_aganist_sphere(const REAL fSphRad,
                             const vector3<REAL> vSphCnt){
      return squared_dist_point(vSphCnt) <= (fSphRad * fSphRad);
    }

    ///
    /// \brief fill_guess
    /// \param _fGuessVal
    ///
    void fill_guess(const REAL _fGuessVal){
      for (unsigned int i = 0; i < DIM_RECT; i++){
          this->rect_min[i] = -_fGuessVal / 2;
          this->rect_max[i] =  _fGuessVal / 2;
        }
    }

    ///
    /// \brief fill_guess_with_shift
    /// \param _fGuessVal
    /// \param shift
    ///
    void fill_guess_with_shift(const REAL _fGuessVal,
                               const vector3<REAL> vShift){
      for (unsigned int i = 0; i < DIM_RECT; i++){
          this->rect_min[i] = (-_fGuessVal / 2) + vShift[i];
          this->rect_max[i] = ( _fGuessVal / 2) + vShift[i];
        }
    }

    ///
    /// \brief split
    /// \param nl
    /// \param nh
    /// \param iAxis
    ///
    void split(rtree_box_nd<REAL> &nl,
               rtree_box_nd<REAL> &nh,
               const int iAxis = 0){
      for (uint i = 0; i < DIM_RECT; i++){
          REAL fMidPoint = (rect_max[i] - rect_min[i]) /2 ;
          nl.rect_min[i] =  rect_min[i];
          if (i == iAxis){
              nl.rect_max[i] = nl.rect_min[i] + fMidPoint;
              nh.rect_min[i] = nl.rect_min[i] + fMidPoint;
              nh.rect_max[i] = nl.rect_max[i] + fMidPoint;
            }
          else {
              nl.rect_max[i] = nl.rect_min[i] + fMidPoint * 2;
              nh.rect_min[i] = nl.rect_min[i] ;
              nh.rect_max[i] = nl.rect_max[i];
            }
        }
    }

    ///
    /// \brief point_inside
    /// \param point
    /// \return
    ///
    bool point_inside(const vector3<REAL> point){
      for (uint i = 0; i < DIM_RECT; i++)
        if (!((point[i] >= rect_min[i]) && (point[i] <= rect_max[i])))
          return false;
      return true;
    }

    ///
    /// \brief volume
    /// \return
    ///
    REAL volume(){
      REAL _ret = 1.0;
      for (uint i = 0 ; i < DIM_RECT; i++) _ret *= (rect_max[i]-rect_min[i]);
      return _ret;
    }

    ///
    /// \brief rtree_box_nd
    ///
    rtree_box_nd(){
      for (unsigned int i = 0; i < DIM_RECT; i++){
          rect_max[i] = 0.0f;
          rect_min[i] = 0.0f;
        }
    }

    //void split()
  };

  template<typename REAL = float>
  std::ostream& operator << (std::ostream& stream,
                             rtree_box_nd<REAL> &nh) {
    stream << "[ rmin = {";
    for (unsigned int i = 0; i < DIM_RECT; i++)
      stream << nh.rect_min[i] << ",";
    stream << "} rmax ={";
    for (unsigned int i = 0; i < DIM_RECT; i++)
      stream << nh.rect_max[i] << ",";
    stream << "} ]";
    return stream;
  }


  /// rtree node forward declaration                                        ///
  template<typename REAL>
  struct rtree_node;

  /// data to store in rtree                                                ///
  template<typename REAL = float>
  struct rtree_node_content {
    int atm;
    index idx;
    ///
    /// \brief rtree_node_content
    /// \param _atm
    /// \param _idx
    ///
    rtree_node_content(const int _atm, const index _idx){
      atm = _atm;
      idx = _idx;
    }
  };

  /// rtree single node                                                      //
  template<typename REAL = float>
  struct rtree_node {
    rtree_node<REAL>* parent;
    rtree_box_nd<REAL> rect;
    std::vector<rtree_node<REAL>* > childs;
    std::vector<rtree_node_content<REAL>* > content;
  };


  ///
  /// aux rtree implementation
  ///
  template <class REAL, class CELL = periodic_cell<REAL> >
  class aux_rtree : public geometry_observer<REAL>{
  public:
    REAL fGuessRectSize;
    REAL fMinTWSVolume;
    int DIM;
    geometry<REAL, CELL> *geom;
    rtree_node<REAL> *root;
    std::unordered_map<qpp::sym_key<int>, REAL, qpp::sym_key_hash<int> > distMap;
    std::map<int, REAL> maxDistMap;
    std::vector<std::vector<rtree_node_content<REAL>*> > nTable;

    bool bMakeDirtyDistMap;
    bool bAutoBonding;

    ///
    /// \brief aux_rtree constructor
    /// \param g
    ///
    aux_rtree( geometry<REAL, CELL> & g) {
      geom = & g;
      geom->add_observer(*this);
      DIM = geom -> DIM;
      fGuessRectSize = 20.0f;
      fMinTWSVolume  = 100.0;
      root = nullptr;
      bAutoBonding = false;
      bMakeDirtyDistMap = true;
    }

    ///
    /// \brief check_root
    ///
    void check_root(){
      if (root == nullptr){
          //std::cout << "create root" << std::endl;
          root = new rtree_node<REAL>();
          root->rect.fill_guess(fGuessRectSize);
        }

    }

    ///
    /// \brief query_sphere
    /// \param fSphRad
    /// \param vSphCnt
    /// \param res
    ///
    void query_sphere(const REAL fSphRad,
                      const vector3<REAL> vSphCnt,
                      std::vector<rtree_node_content<REAL>*> *res){
      traverse_query_sphere(root, fSphRad, vSphCnt, res);
    }

    ///
    /// \brief apply_visitor
    /// \param f
    ///
    void apply_visitor(
        std::function<void(rtree_node<REAL>*)> f){
      traverse_apply_visitor(root, f);
    }

    ///
    /// \brief traverse_apply_visitor
    /// \param curNode
    /// \param f
    ///
    void traverse_apply_visitor(
        rtree_node<REAL> *curNode,
        std::function<void(rtree_node<REAL>*)> f){
      f(curNode);
      for(int i = 0; i < curNode->childs.size(); i++)
        traverse_apply_visitor(curNode->childs[i], f);
    }


    ///
    /// \brief traverse_query_sphere
    /// \param curNode
    /// \param fSphRad
    /// \param vSphCnt
    /// \param res
    ///
    void traverse_query_sphere(
        rtree_node<REAL> *curNode,
        const REAL fSphRad,
        const vector3<REAL> vSphCnt,
        std::vector<rtree_node_content<REAL>*> *res){


      if (curNode->rect.test_aganist_sphere(fSphRad, vSphCnt)){

          for (int i = 0; i < curNode->childs.size(); i++)
            traverse_query_sphere(curNode->childs[i],
                                  fSphRad, vSphCnt, res);

            for (int i = 0; i < curNode->content.size(); i++)
              if ((vSphCnt - geom->r(curNode->content[i]->atm,
                                     curNode->content[i]->idx)).norm() <= fSphRad)
                res->push_back(curNode->content[i]);
        }
    }

    ///
    /// \brief Insert oject to tree
    /// \param atm
    /// \param idx
    ///
    void insert_object_to_tree(const int atm, const index & idx){

      check_root();
      bool bPointInRoot = root->rect.point_inside(geom->r(atm, idx));
      int iq = 0;
      while (!(root->rect.point_inside(geom->r(atm, idx)))) {
          std::cout << "pre grow " << root->rect << std::endl;
          grow_tws_root(atm, idx);
          std::cout << "pre grow " << root->rect << std::endl;
          iq++;
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
    bool traverse_insert_object_to_tree(
        rtree_node<REAL> *curNode,
        const int atm,
        const index & idx){

//      std::cout << fmt::format("ins {} {} {} {} {} {}",
//                               curNode->rect.rect_min[0],
//          curNode->rect.rect_min[1],
//          curNode->rect.rect_min[2],
//          curNode->rect.rect_max[0],
//          curNode->rect.rect_max[1],
//          curNode->rect.rect_max[2]) <<std::endl;

      bool bInCurRect = curNode->rect.point_inside(geom->r(atm, idx));

      if (!bInCurRect) return false;

      if (bInCurRect){

          if ((curNode->childs.size() == 0) &&
            (curNode->rect.volume() / 27.0 <= fMinTWSVolume)){
              push_data_to_tws_node(curNode, atm, idx);
              return true;
            }

          if (curNode->childs.size() == 0){
              if (curNode->rect.volume() / 27.0 > fMinTWSVolume){
                  split_tws_node(curNode);
                }
            }



          for (uint i = 0; i < curNode->childs.size(); i++)
            if (traverse_insert_object_to_tree(curNode->childs[i], atm, idx))
              return true;
        }

      return false;
    }

    ///
    /// \brief push_data_to_tws_node
    /// \param curNode
    /// \param atm
    /// \param idx
    ///
    void push_data_to_tws_node(rtree_node<REAL> *curNode,
                               const int atm,
                               const index & idx){
      rtree_node_content<REAL>* cnt = new rtree_node_content<REAL>(atm, idx);
      curNode->content.push_back(cnt);
    }


    ///
    /// \brief grow_tws_root
    /// \param atm
    /// \param idx
    ///
    void grow_tws_root( const int atm,
                        const index & idx){

      vector3<REAL> vSize = (root->rect.rect_max - root->rect.rect_min)/2.0;
      rtree_node<REAL>* newRoot = new rtree_node<REAL>();

      newRoot->rect.rect_min = root->rect.rect_min * 2;
      newRoot->rect.rect_max = root->rect.rect_max * 2;
      newRoot->parent = nullptr;

      for (int ix = -1; ix < 2; ix++)
        for (int iy = -1; iy < 2; iy++)
          for (int iz = -1; iz < 2; iz++){

              if ((ix == 0) && (iy == 0) && (iz == 0))
                newRoot->childs.push_back(root);

              else {
                  rtree_node<REAL>* nNode = new rtree_node<REAL>();
                  nNode->rect.rect_min =
                      root->rect.rect_min + vector3<REAL>(ix * vSize[0],
                      iy * vSize[1],
                      iz * vSize[2]);

                  nNode->rect.rect_max =
                      root->rect.rect_max + vector3<REAL>(ix * vSize[0],
                      iy * vSize[1],
                      iz * vSize[2]);

                  newRoot->childs.push_back(nNode);
                }
            }

      root = newRoot;

    }

    ///
    /// \brief split_tws_node
    /// \param curNode
    ///
    void split_tws_node(rtree_node<REAL> *curNode){
      vector3<REAL> vSize =
          (curNode->rect.rect_max - curNode->rect.rect_min)/6.0;
      vector3<REAL> vCntr =
          (curNode->rect.rect_max+ curNode->rect.rect_min)/2.0;

      for (int ix = -1; ix < 2; ix++)
        for (int iy = -1; iy < 2; iy++)
          for (int iz = -1; iz < 2; iz++){
              rtree_node<REAL>* nNode = new rtree_node<REAL>();

              nNode->rect.rect_min =
                  vCntr - vSize + vector3<REAL>(ix * vSize[0] * 2,
                  iy * vSize[1] * 2,
                  iz * vSize[2] * 2);

              nNode->rect.rect_max =
                  vCntr + vSize + vector3<REAL>(ix * vSize[0] * 2,
                  iy * vSize[1] * 2,
                  iz * vSize[2] * 2);

              curNode->childs.push_back(nNode);
            }
    }


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
          rtree_node_content<REAL>* newTableEntry =
              new rtree_node_content<REAL>(i, j);
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
      if (bMakeDirtyDistMap) {
          rebuild_dist_map();
          if (nTable.size() < geom->nat()) nTable.resize(geom->nat());
        }

      REAL fSphRad = maxDistMap[geom->type_table(atNum)];
      if ( fSphRad > 0.0){
          std::vector<qpp::rtree_node_content<float>*> res;
          //          std::cout << "fSphRad=" << fSphRad << std::endl;
          query_sphere(fSphRad, geom->pos(atNum), &res);
          for (int i = 0; i < res.size(); i++){
              vector3<float> pos1 = geom->pos(atNum);
              vector3<float> pos2 = geom->pos(res[i]->atm, res[i]->idx);
              REAL fDr = (pos1 - pos2).norm();
              std::cout<<
                          fmt::format("a1_i={}, a2_i={}, fdr={} dtm={}",
                                      atNum, res[i]->atm, fDr,
                                      distMap[sym_key<int>(geom->type_table(atNum),
                                                           geom->type_table(res[i]->atm))])
                       << std::endl;
              //              std::cout<< "fdr " << fDr << " " <<
              //                          distMap[sym_key<int>(geom->type_table(atNum),
              //                                               geom->type_table(res[i]->atm))] <<
              //                          " tt(Atnum)=" << geom->type_table(atNum) <<
              //                          " tt(res)=" << geom->type_table(res[i]->atm) <<
              //                          " " << geom->atom(atNum) <<
              //                          " " << geom->atom(res[i]->atm) <<
              //                          " " << distMap.size() << std::endl;

              if ((fDr < distMap[sym_key<int>(geom->type_table(atNum),
                                              geom->type_table(res[i]->atm))])
                  && !(( atNum == res[i]->atm) && (res[i]->idx == index({0,0,0}))) ){
                  add_ngbr(atNum, res[i]->atm, res[i]->idx);
                  if (res[i]->idx == index({0,0,0}))
                    add_ngbr(res[i]->atm, atNum , res[i]->idx);
                }
            }
        }
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
    void debug_print_traverse(rtree_node<REAL> *node,
                              int iDeepLevel, int &totalEntries){

      REAL fAABBFakeVol = 1.0;
      for (int i = 0; i < DIM_RECT; i++)
        fAABBFakeVol *= node->rect.rect_max[i]-node->rect.rect_min[i];
      std::cout << std::string(iDeepLevel, '>')
                << "node vol = "<< fAABBFakeVol <<" " << node->rect << " "
                << node->content.size()<< std::endl;
      totalEntries += node->content.size();

      for (int i = 0; i < node->childs.size(); i++)
        debug_print_traverse(node->childs[i], iDeepLevel+1, totalEntries);

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
