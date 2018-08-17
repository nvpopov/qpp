#ifndef _QPP_RTREE_H
#define _QPP_RTREE_H

#include <ostream>
#include <typeinfo>
#include <functional>
#include <utility>
#include <set>
#include <algorithm>
#include <cmath>
#include <geom/geom.hpp>
#include <geom/ngbr.hpp>
#include <string>

//#ifdef PY_EXPORT
//#include <pybind11/pybind11.h>
//#include <pybind11/operators.h>
//#include <pybind11/stl.h>
//#include <pyqpp/py_indexed_property.hpp>
//namespace py = pybind11;
//#endif

namespace qpp{

  /// rtree multidimensional box
  template<typename REAL = float, typename DATA_OBJECT = vector3<REAL>,
           int DIM_RECT = 3>
  struct rtree_box_nd {
    std::array<REAL, DIM_RECT> rect_max;
    std::array<REAL, DIM_RECT> rect_min;

    ///
    /// \brief is_overlap
    /// \param box
    /// \return
    ///
    bool is_overlap(const rtree_box_nd<REAL,  DATA_OBJECT, DIM_RECT> *box){
      for (unsigned int i = 0; i < DIM_RECT; i++)
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
    REAL squared_dist_point(const DATA_OBJECT point){
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
    bool test_aganist_sphere(const REAL fSphRad, const DATA_OBJECT vSphCnt){
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
    void fill_guess_with_shift(const REAL _fGuessVal, const DATA_OBJECT shift){
      for (unsigned int i = 0; i < DIM_RECT; i++){
          this->rect_min[i] = (-_fGuessVal / 2) + shift[i];
          this->rect_max[i] = ( _fGuessVal / 2) + shift[i];
        }
    }

    ///
    /// \brief split
    /// \param nl
    /// \param nh
    /// \param iAxis
    ///
    void split(rtree_box_nd<REAL,  DATA_OBJECT, DIM_RECT> &nl,
               rtree_box_nd<REAL,  DATA_OBJECT, DIM_RECT> &nh,
               const int iAxis = 0){
      for (unsigned int i = 0; i < DIM_RECT; i++){
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
    bool point_inside(const DATA_OBJECT point){
      for (unsigned int i = 0; i < DIM_RECT; i++)
        if (!((point[i] > rect_min[i]) && (point[i] < rect_max[i])))
          return false;
      return true;
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

  template<typename REAL = float,
           typename DATA_OBJECT = vector3<REAL>,
           int DIM_RECT = 3>
  std::ostream& operator << (std::ostream& stream,
                             rtree_box_nd<REAL, DATA_OBJECT, DIM_RECT> &nh) {
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
  template<typename REAL, typename DATA_OBJECT,  int DIM_RECT>
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
  template<typename REAL = float,
           typename DATA_OBJECT = vector3<REAL>,
           int DIM_RECT = 3>
  struct rtree_node {
    rtree_node<REAL, DATA_OBJECT, DIM_RECT>* parent;
    rtree_box_nd<REAL, DATA_OBJECT, DIM_RECT> rect;
    std::vector<rtree_node<REAL, DATA_OBJECT, DIM_RECT>* > childs;
    std::vector<rtree_node_content<REAL>* > content;
  };


  ///
  /// aux rtree implementation
  ///
  template <class REAL,
            class CELL = periodic_cell<REAL>,
            typename DATA_OBJECT = vector3<REAL>,
            int MIN_SCIONS = 1,
            int MAX_SCIONS = 100,
            int RTREE_DIM = 3>
  class aux_rtree : public geometry_observer<REAL>{
  public:
    REAL fGuessRectSize;
    int DIM;
    geometry<REAL, CELL> *geom;
    rtree_node<REAL, DATA_OBJECT, RTREE_DIM> *root;
    bonding_table<REAL> *bt;
    std::vector<std::vector<index> > _table;

    bool bAutoBonding;
    ///
    /// \brief aux_rtree constructor
    /// \param g
    ///
    aux_rtree( geometry<REAL, CELL> & g) {
      geom = & g;
      geom->add_observer(*this);
      DIM = geom -> DIM;
      fGuessRectSize = 15.0f;
      root = nullptr;
      bAutoBonding = false;
    }

    ///
    /// \brief check_root
    ///
    void check_root(){
      if (root == nullptr){
          //std::cout << "create root" << std::endl;
          root = new rtree_node<REAL, DATA_OBJECT, RTREE_DIM>();
        }
    }

    ///
    /// \brief query_sphere
    /// \param fSphRad
    /// \param vSphCnt
    /// \param res
    ///
    void query_sphere(const REAL fSphRad,
                      const DATA_OBJECT vSphCnt,
                      std::vector<rtree_node_content<REAL>*> *res){
      traverse_query_sphere(root, fSphRad, vSphCnt, res);
    }

    ///
    /// \brief apply_visitor
    /// \param f
    ///
    void apply_visitor(
        std::function<void(rtree_node<REAL, DATA_OBJECT, RTREE_DIM>*)> f){
        traverse_apply_visitor(root, f);
    }

    ///
    /// \brief traverse_apply_visitor
    /// \param curNode
    /// \param f
    ///
    void traverse_apply_visitor(
        rtree_node<REAL, DATA_OBJECT, RTREE_DIM> *curNode,
        std::function<void(rtree_node<REAL, DATA_OBJECT, RTREE_DIM>*)> f){
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
        rtree_node<REAL, DATA_OBJECT, RTREE_DIM> *curNode,
        const REAL fSphRad,
        const DATA_OBJECT vSphCnt,
        std::vector<rtree_node_content<REAL>*> *res){


      if ((curNode->rect.test_aganist_sphere(fSphRad, vSphCnt)) ||
          (curNode == root)){

          for (int i = 0; i < curNode->childs.size(); i++)
            traverse_query_sphere(curNode->childs[i],
                                  fSphRad, vSphCnt, res);

          if (curNode != root)
            for (int i = 0; i < curNode->content.size(); i++)
              if ((vSphCnt - geom->r(curNode->content[i]->atm,
                                     curNode->content[i]->idx)).norm() < fSphRad)
                res->push_back(curNode->content[i]);
        }
    }

    ///
    /// \brief Make new node
    /// \param atm
    /// \param idx
    ///
    void make_new_node(const int atm, const index & idx){
      rtree_node<REAL, DATA_OBJECT, RTREE_DIM> *sn =
          new rtree_node<REAL, DATA_OBJECT, RTREE_DIM>();
      sn->parent = root;
      sn->rect.fill_guess_with_shift(fGuessRectSize, geom->r(atm, idx));
      rtree_node_content<REAL>* cnt = new rtree_node_content<REAL>(atm, idx);
      sn->content.push_back(cnt);
      root->childs.push_back(sn);
    }

    ///
    /// \brief Insert oject to tree
    /// \param atm
    /// \param idx
    ///
    void insert_object_to_tree(const int atm, const index & idx){

      check_root();
      if (root->childs.size() == 0){
          rtree_node<REAL, DATA_OBJECT, RTREE_DIM> *sn =
              new rtree_node<REAL, DATA_OBJECT, RTREE_DIM>();
          sn->parent = root;
          sn->rect.fill_guess(fGuessRectSize);
          root->childs.push_back(sn);
        }
      bool bPointPlaced = traverse_insert_object_to_tree(root, atm, idx);

      if (!bPointPlaced) make_new_node(atm, idx);
    }

    ///
    /// \brief split_node_and_add
    /// \param curNode
    /// \param atm
    /// \param idx
    ///
    void split_node_and_add( rtree_node<REAL, DATA_OBJECT, RTREE_DIM> *curNode,
                             const int atm,
                             const index & idx){

      rtree_node<REAL, DATA_OBJECT, RTREE_DIM> *snh =
          new rtree_node<REAL, DATA_OBJECT, RTREE_DIM>();
      rtree_node<REAL, DATA_OBJECT, RTREE_DIM> *snl =
          new rtree_node<REAL, DATA_OBJECT, RTREE_DIM>();
      curNode->rect.split(snh->rect, snl->rect);

      for (int i = 0; i < curNode->content.size(); i++){
          bool bInH = snh->rect.point_inside(
                geom->r(curNode->content[i]->atm, curNode->content[i]->idx));
          if(bInH) snh->content.push_back(curNode->content[i]);
          else snl->content.push_back(curNode->content[i]);
        }

      rtree_node_content<REAL>* cnt = new rtree_node_content<REAL>(atm, idx);

      if (snh->rect.point_inside(geom->r(atm, idx)))
        snh->content.push_back(cnt);
      else snl->content.push_back(cnt);


      curNode->childs.push_back(snh);
      curNode->childs.push_back(snl);

      curNode->content.clear();

    }

    ///
    /// \brief traverse_insert_object_to_tree
    /// \param curNode
    /// \param atm
    /// \param idx
    /// \return
    ///
    bool traverse_insert_object_to_tree(
        rtree_node<REAL, DATA_OBJECT, RTREE_DIM> *curNode,
        const int atm,
        const index & idx){

      // check self
      bool bInCurRect = curNode->rect.point_inside(geom->r(atm, idx));
      //      std::cout << curNode->rect
      //                << bInCurRect  << " " << geom->r(atm, idx)[0] << " " <<
      //                   geom->r(atm, idx)[1] << " " <<
      //                   geom->r(atm, idx)[2] << std::endl;

      if ((bInCurRect) && curNode->content.size() < MAX_SCIONS){
          rtree_node_content<REAL>* cnt = new rtree_node_content<REAL>(atm, idx);
          curNode->content.push_back(cnt);
          return true;
        }

      if ((bInCurRect) && curNode->content.size() >= MAX_SCIONS){
          split_node_and_add(curNode, atm, idx);
          return true;
        }

      for (int i = 0; i < curNode->childs.size(); i++){
          bool bTraversed =
              traverse_insert_object_to_tree(curNode->childs[i], atm, idx);
          if (bTraversed) return true;
        }

      return false;
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
    void debug_print_traverse(rtree_node<REAL, DATA_OBJECT, RTREE_DIM> *node,
                              int iDeepLevel, int &totalEntries){

      std::cout << std::string(iDeepLevel, '>')
                << "node " << node->rect << " "
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
          insert_object_to_tree(geom->nat()-1, index({0,0,0}));
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

    }

    ///
    /// \brief erased
    /// \param at
    /// \param st
    ///
    void erased(int at,
                before_after st) override {

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
