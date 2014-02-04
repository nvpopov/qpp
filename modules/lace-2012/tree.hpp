#ifndef _LACE_TREE_H
#define _LACE_TREE_H

#include <vector>
#include <lace-2012/globals.hpp>

namespace _lace_tree{
  
  class tree_node{
    
  public:
    typedef std::vector<tree_node*> nodearray;

    typedef int UIDTYPE;
    
	/**
	 *@brief Test brief
	 * 
	 * 
	 * 
	 **/
    int nref;
    // Number of other objects (tree nodes) which reference this node
    
    virtual UIDTYPE getUID() =0;
    // Unique identifier of this node. Must be different for any two different inctances of tree_node
    
    virtual int gettype() =0;
    // It's possible to define types for nodes when you produce descendants of tree_node.
    
    virtual int nnext() =0;
    // Number of branches coming from this node
    
    virtual tree_node* next(int i) =0;
    // Branch number i from this node

    virtual void setnext(int i, tree_node *p) =0;
    // Set the i-th branch pointer to object *p
    
    virtual bool equiv(tree_node *tree) =0;
    // Are this node and node *tree equvalent? That's your business how do you define
    // equivalence. But if your nodes represent, say, numbers, than it's natural
    // that nodes are equiv when their numbers are equiv
    
    //debug
    virtual void print_tree(int =0){}
    
    virtual void free(){delete this;}
    
    void setref(){nref++;}
    // Increase the reference counter

    void unsetref(){nref--;}
    // Decrease the reference counter

    // Delete the node pointed by n-th branch of this node
    // delete_node will delete the node regardless to any other objects pointing to it
    void delete_node(int n)
    {
      if ( n < nnext() && next(n) != NULL )
	{
	  next(n) -> free();
	  setnext(n, NULL);
	}
    }
    
    // Completely delete all subtree pointed by n-th branch of this node
    // regardless to any other objects pointing to the nodes of the subtree
    void delete_tree(int n)
    {
      if ( n < nnext() && next(n) != NULL )
	{
	  for (int i=0; i<next(n)->nnext(); i++)
	    next(n) -> delete_tree(i);
	  next(n) -> free();
	  setnext(n, NULL);
	}
    }

    // This is "soft" version of delete_tree
    // It will decrease the number of references to the nodes of the subtree
    // If the number of references becomes zero then subtree is deleted
    void unlink_tree(int n)
    {
      if ( n < nnext() && next(n) != NULL )
	{
	  next(n) -> nref--;
	  if ( next(n) -> nref == 0)
	    {
	      if (lace::globals::debug)
		{
		  //std::cout << "Unlinking ";
		  //next(n) -> print_tree(0);
		  //std::cout << "\n";		  
		}	      
	      for (int i = 0; i<next(n) -> nnext(); i++) 	      
		next(n) -> unlink_tree(i);
	      next(n) -> free();
	      setnext(n, NULL);
	    }
	}
    }
    
    // Depth of the subtree, i.e. maximum number of the branches each pointing to the next branch
    // until the "leafs" (i.e. nodes not pointing to any other node) are reached 
    int depth()
    {
      if ( nnext() == 0 ) 
	return 0;
      else
	{
	  int d = 0;
	  for (int i = 0; i<nnext(); i++) 
	    if ( next(i) != NULL )
	      d = std::max(d, next(i)->depth() + 1 );
	  return d;
	}
    }
   
    // Total number of nodes in the subtree
    int total_nodes()
    {
      int n = 1;
      for(int i = 0; i< nnext(); i++) 
	if ( next(i) != NULL )
	  n += next(i) -> total_nodes();
      return n;
    }
    
//     template<class NODE,bool EQUIV(NODE*,NODE*)>
//     bool compare( NODE *tree )
//     {
//       bool res = EQUIV((NODE*)this,tree);
      
//       if (res)
// 	for (int i=0; i<nnext(); i++) 
// 	  if ( next(i) == NULL && tree -> next(i) != NULL )
// 	    {
// 	      res = false; break;
// 	    }
// 	  else if ( ! next(i) -> compare<NODE,EQUIV>( (NODE*) (tree -> next(i)) ) )
// 	    {
// 	      res = false; break;
// 	    }
//       return res;
//     }
    

    // Are the two trees equivalent?
    // This will compare the shape of two trees any two matching nodes using 
    // "equiv" 
    bool compare( tree_node *tree )
    {
      bool res = equiv(tree);
      
      if (res)
	for (int i=0; i<nnext(); i++) 
	  if ( next(i) == NULL && tree -> next(i) != NULL )
	    {
	      res = false; break;
	    }
	  else if ( ! next(i) -> compare( tree -> next(i) ))
	    {
	      res = false; break;
	    }
      return res;
    }

    // "Unroll" the tree nodes into linear array a
    virtual void unroll(nodearray &a)
    {
      a.push_back(this);
      for(int i = 0; i< nnext(); i++) 
	if ( next(i) != NULL )
	  next(i)->unroll(a);
    }  
    
    // Similar, but also create linear array par
    // containing parents for each node in a
    virtual void unroll(nodearray &a, nodearray &par, tree_node *parent)
    {
      a.push_back(this);
      par.push_back(parent);
      for(int i = 0; i< nnext(); i++) 
	if ( next(i) != NULL )
	  next(i)->unroll(a,par,this);
    }

  
    template<class NODE>
    class iterator{
      // This iterator allows to iterate through the tree nodes
      // It also has other useful functions
      
      tree_node* _root;
      nodearray unr, par;
      int pos;
      
    public:
      
      typedef tree_node::iterator<NODE> _self;
      typedef NODE&           reference;
      typedef NODE*           pointer;
      
      //Constructors:

      iterator(){pos=-1;}
      
      iterator(pointer root) 
      {
	_root=root; 
	root->unroll(unr,par,NULL); 
	pos = 0;
      }
      
      void set(pointer root)
      {
	clear();
	_root=root; 
	root->unroll(unr,par,NULL); 
	pos = 0;
      }
      
      // It is possible and sometimes even necessary that some nodes of the tree
      // are referenced twice or more. I.e. several different branches of the tree
      // point to the same node. "Unrolling" such tree will create duplicate pointers
      // to such nodes.
      // "uniq" will find and remove any duplicate pointers
      void uniq()
      {
	nodearray::iterator arrow;
	
	int i=0;
	while (i<unr.size())
	  {
	    int j = i+1;
	    while (j<unr.size())
	      {
		if (unr[i]->getUID() == unr[j]->getUID())
		  // The nodes i and j are the same
		  {
		    arrow = unr.begin();
		    arrow += j;
		    unr.erase(arrow);
		    
		    arrow = par.begin();
		    arrow += j;
		    par.erase(arrow);
		  }
		else
		  j++;
	      }
	    i++;
	  }
      }
      
      inline  _self& operator++(int){if (pos < unr.size()-1 ) pos++; else pos = -1; return *this;}
      
      inline  _self& operator--(int){if (pos >= 0) pos--; return *this;}
      
      inline  _self& operator=(pointer node)
      {
	bool found = false;
	for(int i=0; i<unr.size(); i++)
	  if ( unr[i] == node )
	    {
	      pos = i; found = true; break;
	    }
	if (found) 
	  return *this;
	else
	  pos = -1;
      }
      
      inline _self& operator=(int i)
      {
	if (i<unr.size()) pos = i;
	else pos = -1;
	return *this;
      }
      
      inline int index(){
	return pos;
      }
      
      inline bool operator==(pointer node)
      {
	if (pos>=0)
	  return unr[pos] == node;
	else
	  return node == NULL;
      }
      
      inline bool operator!=(pointer node)
      {
	if (pos>=0)
	  return unr[pos] != node;
	else
	  return node != NULL;
      }
      
      inline bool operator==(const _self &x) const
      {
	return _root == x._root && pos == x.pos;
      }
      
      inline bool operator!=(const _self &x) const
      {
	return _root != x._root || pos != x.pos;
      }
      
      inline pointer operator->() 
      {
	if (pos >= 0 )
	  return (pointer)(unr[pos]);
	else
	  return NULL;
      }
      
      inline reference operator*() 
      {
	if (pos >= 0 )
	  return *((pointer)(unr[pos]));
      }
      
      inline pointer parent(){
	if (pos >= 0 )
	  return (pointer)(par[pos]);
	else
	  return NULL;
      }
      
      void clear(){
	unr.clear();
	par.clear();
	pos=-1;
      }
      
      ~iterator(){
	clear();
      }      
      
    };
    
    // Find all the branches in the tree pointing to oldnode
    // and set them to the newnode
    // "oldnode" is treated with "soft delete"
    void relink_tree(tree_node *oldnode, tree_node *newnode)
    {
      nodearray parents;
      std::vector<int> branches;
      iterator<tree_node> nd(this);
      
      while ( nd != NULL )
	{
	  for (int i=0; i < nd -> nnext(); i++)
	    if ( nd -> next(i) == oldnode )
	      {
		parents.push_back( &(*nd) );
		branches.push_back(i);
	      }
	  nd++;
	}
      for ( int i=0; i<parents.size(); i++)
	{
	  newnode -> setref();
	  parents[i] -> unlink_tree(branches[i]);
	  parents[i] -> setnext(branches[i], newnode);
	}
    }

    // For any two or more equivalent nodes or subtrees
    // remove all of them but one
    // and set all pointers to this one
    void reduce_tree()
    {
      tree_node::iterator<tree_node> i, j;
      bool not_found;
      do
	{
	  not_found = true;
	  i.set(this);
	  while ( not_found && i!= NULL  )
	    {
	      
	      j.set(this);
	      j = i.index() + 1;
	      while ( j!=NULL )
		{
		  if ( i->compare( &(*j)) && i->getUID() != j->getUID() )
		    {
		      relink_tree( &(*j), &(*i) );

		      not_found = false;
		      break;
		    }
		  j++;
		}
	      i++;
	    }
	} while ( ! not_found );
    }

  };
  
};
  
#endif
