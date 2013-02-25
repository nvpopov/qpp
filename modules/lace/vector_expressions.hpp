#ifndef _LACE_VECTOR_EXPRESSIONS_H
#define _LACE_VECTOR_EXPRESSIONS_H

//#include <lace/tree.hpp>
#include <lace/expressions.hpp>
//#include <lace/matrix_expressions.hpp>

namespace _lace_expressions{

  using _lace_storage::vector_shape;


  template<typename VALTYPE>
  class transpvector_expression;
  
  template<typename VALTYPE>
  class transprvector_expression;
  
  template<typename VALTYPE>
  class vector_expression : public abstract_expression
  {    
    typedef vector_expression<VALTYPE> SELF;

  public:

    typedef vector_shape shape_type;
    
    /* temp
    static void process_expr(vector_expression<VALTYPE>* &target, 
			     vector_expression<VALTYPE> *xpr);

    virtual void calculate_expr(vector_expression<VALTYPE>* &target, VALTYPE scale = VALTYPE(1e0) );
    */

    typedef expression_literal<VALTYPE,SELF>     literal;
    typedef expression_binop<VALTYPE,SELF>       binop;
    typedef equality_expression<VALTYPE,SELF>    equals;
    typedef expression_scaling<VALTYPE,SELF>     scaling;
    typedef expression_summa<VALTYPE,SELF>       summa;
    typedef summa_literal<VALTYPE,SELF>          sliteral;
    //    typedef expression_unop<VALTYPE,rawvector_expression<VALTYPE>,vector_expression<VALTYPE> >  transpop;
    typedef transpvector_expression<VALTYPE>  transpone;

    typedef expression_unop<VALTYPE,vector_expression<VALTYPE>,vector_expression<VALTYPE> >  unop;
    
    typedef mixtyped_product<VALTYPE,matrix_expression<VALTYPE>,vector_expression<VALTYPE>,vector_expression<VALTYPE> > outprod;
    typedef mixtyped_product<VALTYPE,matrix_expression<VALTYPE>,rawvector_expression<VALTYPE>,vector_expression<VALTYPE> > mulvtv;

    typedef transpvector_expression<VALTYPE> transpvector;

    vector_expression<VALTYPE>& operator+(vector_expression<VALTYPE> &v); 
    
    vector_expression<VALTYPE>& operator-(vector_expression<VALTYPE> &v); 
    
    matrix_expression<VALTYPE>& operator%(vector_expression<VALTYPE> &v); 
    
    matrix_expression<VALTYPE>& operator*(rawvector_expression<VALTYPE> &v); 
    
    vector_expression<VALTYPE>& operator*(VALTYPE s); 
    
    vector_expression<VALTYPE>& operator/(VALTYPE s); 
    
    rawvector_expression<VALTYPE>& T();
    
    rawvector_expression<VALTYPE>& H();

    matrix_expression<VALTYPE>&  D();

    virtual vector_expression<VALTYPE>& operator=(vector_expression<VALTYPE> &xpr);

    virtual vector_expression<VALTYPE>& operator()(sub I);

    virtual vector_expression<VALTYPE>& operator()(subrange_expression &I);

    virtual int basetype(){return _vector;}
    
    virtual vector_shape shape()
    { return _lace_storage::vector_shape(); }

    virtual _lace_storage::vector_type vtype(){return shape().vtype;}

    virtual void reshape( vector_shape shp )
    { assert( false && "Error: vector_expression::reshape is just an interface to vector::reshape and should never be used"); }

  };


  template<typename VALTYPE>
  class rawvector_expression : public abstract_expression
  {
    typedef rawvector_expression<VALTYPE> SELF;

  public:

    typedef vector_shape shape_type;
    
    typedef expression_binop<VALTYPE,SELF>    binop;
    typedef expression_scaling<VALTYPE,SELF>  scaling;
    //   typedef expression_unop<VALTYPE,vector_expression<VALTYPE>,rawvector_expression<VALTYPE> >  transpop;
    typedef transprvector_expression<VALTYPE> transpone;

    typedef mixtyped_product<VALTYPE,matrix_expression<VALTYPE>,rawvector_expression<VALTYPE>,vector_expression<VALTYPE> > mulvtv;
    typedef mixtyped_product<VALTYPE,rawvector_expression<VALTYPE>,rawvector_expression<VALTYPE>,matrix_expression<VALTYPE> > mulvtm;
    typedef expression_literal<VALTYPE,SELF>  literal;

    rawvector_expression<VALTYPE>& operator+(rawvector_expression<VALTYPE> &v); 
    
    rawvector_expression<VALTYPE>& operator-(rawvector_expression<VALTYPE> &v); 
    
    matrix_expression<VALTYPE>& operator*(vector_expression<VALTYPE> &v);
    
    rawvector_expression<VALTYPE>& operator*(matrix_expression<VALTYPE> &A);
    
    rawvector_expression<VALTYPE>& operator*(VALTYPE s); 

    rawvector_expression<VALTYPE>& operator/(VALTYPE s); 
    
    vector_expression<VALTYPE>& T();
    
    vector_expression<VALTYPE>& H();
    
    matrix_expression<VALTYPE>& D();

    virtual int basetype(){return _rvector;}
  };
  
  //-----------------------------------------------------------------------
  
  //  ------ Mixed products ( like matrix by vector, transpvector by matrix and two vectors outer product )


  template<typename VALTYPE,class XPR1,class XPR2,class XPR3>
  class mixtyped_product : public XPR1
  {
  protected:
    
    XPR2 *left;
    XPR3 *right;
    int op;
    
    typedef mixtyped_product<VALTYPE,XPR1,XPR2,XPR3> SELF;

    typename shape_type<XPR1>::type shp;
    bool shape_defined;

  public:
    mixtyped_product(XPR2 &l, XPR3 &r, int _op )
    {
      left  = &l;
      right = &r;
      left  -> setref();
      right -> setref();
      op = _op;
      shape_defined = false;
    }
    
    virtual int gettype(){return op;}
    
    virtual int nnext(){ return 2;}
    
    virtual tree_node* next(int i){
      switch(i){
      case 0: return left; break;
      case 1: return right; break;
      default: return NULL;
      }
    }
    
    virtual void setnext(int i, tree_node *p)
    {
      switch(i){
      case 0: left  = (XPR2*)p; break;
      case 1: right = (XPR3*)p; break;
      }
    }
    
    //debug--------
    virtual void print_tree(int shift = 0)
    { 
      if (shift == 0)
	{
	  std::cout << "(";
	  left->print_tree(); 
	  print_me();
	  right->print_tree(); 
	  std::cout << ")";
	}
      else
	{
	  left->print_tree(shift+4); 
	  print_me(shift);
	  right->print_tree(shift+4); 	
	}
    }
    
    virtual void print_me(int shift = 0)
    {
      if (shift == 0)
	std::cout << ")*(";
      else
	{
	  indent(shift);
	  std::cout << stype( ((SELF*)this) -> basetype() ) << " mixprod : UID = " << (((SELF*)this) -> getUID())
		    << " nref = " << (((SELF*)this) -> nref) << "\n";
	}
    }
    //--------------
    virtual void unroll(tree_node::nodearray &a, tree_node::nodearray &par, tree_node *parent)
    {
      if (left != NULL ) left->unroll(a,par,this);
      a.push_back(this);
      par.push_back(parent);
      if (right != NULL ) right->unroll(a,par,this);
    }
    
    virtual void free(){delete (SELF*)this;}
    
    ~mixtyped_product(){
      //       std::cout << "killing ";
      //       print_me(1);
    }
    
    virtual abstract_expression* copy(int mask = 0)
    {
      if ( (mask & op) == 0 )
	return new SELF( * (XPR2*)(left -> copy(mask)), * (XPR3*)(right -> copy(mask)), op );
      else
	return this;
    }

  };


  // ------------------------------- The types of "mixtyped" product ------------------------
  template<typename VALTYPE>
  class matrix_by_vector : public mixtyped_product<VALTYPE, vector_expression<VALTYPE>, 
						   matrix_expression<VALTYPE>, vector_expression<VALTYPE> >
  {
    typedef matrix_by_vector<VALTYPE> SELF;

  public:
    
    matrix_by_vector(matrix_expression<VALTYPE> &l, vector_expression<VALTYPE> &r ) : 
      mixtyped_product<VALTYPE, vector_expression<VALTYPE>, 
		       matrix_expression<VALTYPE>, vector_expression<VALTYPE> > (l,r,_mul_mv){}

    /* temp
    virtual void calculate_expr(vector_expression<VALTYPE>* &target, VALTYPE scale = VALTYPE(1e0) );
    */    

    virtual vector_shape shape();

    virtual abstract_expression* copy( int mask = 0 )
    {
      if ( (mask & _mul_mv ) == 0 )
	return new matrix_by_vector<VALTYPE>( *(matrix_expression<VALTYPE>*)(this -> left -> copy(mask)),
					      *(vector_expression<VALTYPE>*)(this -> right -> copy(mask)));
      else 
	return this;
    }

  };
  
  // ---------------------------------------------------------------------

  template<typename VALTYPE>
  class outer_product : public mixtyped_product<VALTYPE, matrix_expression<VALTYPE>, 
						   vector_expression<VALTYPE>, vector_expression<VALTYPE> >
  {
  public:
    outer_product(vector_expression<VALTYPE> &l, vector_expression<VALTYPE> &r) : 
      mixtyped_product<VALTYPE, matrix_expression<VALTYPE>, 
		       vector_expression<VALTYPE>, vector_expression<VALTYPE> >(l,r,_outer_prod){}

    virtual void calculate_expr(matrix_expression<VALTYPE>* &target, VALTYPE scale = VALTYPE(1e0) );
    
    virtual matrix_shape shape();

    virtual abstract_expression* copy( int mask = 0 )
    {
      if ( (mask & _outer_prod ) == 0 )
	return new outer_product<VALTYPE>( *(vector_expression<VALTYPE>*)(this -> left -> copy(mask)),
					   *(vector_expression<VALTYPE>*)(this -> right -> copy(mask)));
      else 
	return this;
    }

  };
  
  // ---------------------------------------------------------------------

  template<typename VALTYPE>
  class transpvector_expression : public expression_unop<VALTYPE, rawvector_expression<VALTYPE>,       
							 vector_expression<VALTYPE> >{
    typedef vector_expression<VALTYPE> XPR;
  public:
    transpvector_expression(vector_expression<VALTYPE> &x, int _op) : 
      expression_unop<VALTYPE, rawvector_expression<VALTYPE>, vector_expression<VALTYPE> >(x, _op)
    {
      assert( (_op & (_transp | _herm)) && "Illegal unary operation for transpvector_expression class");
    }
    
    virtual vector_shape shape()
    {
      return ( (XPR*)(this -> next(0)) ) -> shape();
    }

    virtual abstract_expression* copy( int mask = 0 )
    {
      if ( (mask & this -> op) == 0 )
	return new transpvector_expression<VALTYPE>( * (XPR*)(this -> xnext(0) -> copy(mask)), 
						     this -> op);
      else 
	return this;
    }
    
    virtual void free()
    { delete (transpvector_expression<VALTYPE>*)this;}
    
  };

  // ---------------------------------------------------------------------

  template<typename VALTYPE>
  class transprvector_expression : public expression_unop<VALTYPE, vector_expression<VALTYPE>,       
							  rawvector_expression<VALTYPE> >{
    typedef rawvector_expression<VALTYPE> XPR;
  public:
    transprvector_expression(vector_expression<VALTYPE> &x, int _op) : 
      expression_unop<VALTYPE, vector_expression<VALTYPE>, rawvector_expression<VALTYPE> >(x, _op)
    {
      assert( (_op & (_transp | _herm)) && "Illegal unary operation for transprvector_expression class");
    }
    
    virtual vector_shape shape()
    {
      return ( (XPR*)(this -> next(0)) ) -> shape();      
    }

    virtual abstract_expression* copy( int mask = 0 )
    {
      if ( (mask & this -> op) == 0 )
	return new transprvector_expression<VALTYPE>( * (XPR*)(this -> xnext(0) -> copy(mask)), 
						     this -> op);
      else 
	return this;
    }
    
    virtual void free()
    { delete (transprvector_expression<VALTYPE>*)this;}
    
  };

  // ----------------------------------------------------------------

  // Operators

  template<typename VALTYPE>
  vector_expression<VALTYPE>& matrix_expression<VALTYPE>::operator*(vector_expression<VALTYPE> &v)
  {
    return * new matrix_by_vector<VALTYPE>(*this,v);
  }

  template<typename VALTYPE>
  vector_expression<VALTYPE>& vector_expression<VALTYPE>::operator+(vector_expression<VALTYPE> &v)
  {
    return * new binop(*this,v,_plus);
  }

  template<typename VALTYPE>
  vector_expression<VALTYPE>& vector_expression<VALTYPE>::operator-(vector_expression<VALTYPE> &v)
  {
    return * new binop(*this,v,_minus);
  }

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& vector_expression<VALTYPE>::operator%(vector_expression<VALTYPE> &v)
  {
    return * new outer_product<VALTYPE>(*this, v);
  }

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& vector_expression<VALTYPE>::operator*(rawvector_expression<VALTYPE> &v)
  {
    return * new mulvtv(*this, v, _mul_vtv);
  }

  template<typename VALTYPE>
  vector_expression<VALTYPE>& vector_expression<VALTYPE>::operator*(VALTYPE s) 
  {
    return * new scaling(*this,s);
  } 

  template<typename VALTYPE>
  vector_expression<VALTYPE>& vector_expression<VALTYPE>::operator/(VALTYPE s)
  {
    return * new scaling(*this,1e0/s);
  } 

  template<typename VALTYPE>
  rawvector_expression<VALTYPE>& vector_expression<VALTYPE>::T()
  {
    return * new transpone(*this,_vector + _transp);
  }

  template<typename VALTYPE>
  rawvector_expression<VALTYPE>& vector_expression<VALTYPE>::H()
  {
    return * new transpone(*this,_vector + _herm);
  }

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& vector_expression<VALTYPE>:: D()
  {
    return *new expression_unop<VALTYPE,matrix_expression<VALTYPE>,vector_expression<VALTYPE> >(*this, _matrix + _diagonal);
  }

  template<typename VALTYPE>
  rawvector_expression<VALTYPE>& rawvector_expression<VALTYPE>::operator+(rawvector_expression<VALTYPE> &v)
  {
    return * new binop(*this,v,_plus);
  }

  template<typename VALTYPE>
  rawvector_expression<VALTYPE>& rawvector_expression<VALTYPE>::operator-(rawvector_expression<VALTYPE> &v) 
  {
    return * new binop(*this,v,_minus);
  }

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& rawvector_expression<VALTYPE>::operator*(vector_expression<VALTYPE> &v)
  {
    return * new mulvtv(*this,v, _mul_vtv);
  }
  
  template<typename VALTYPE>
  rawvector_expression<VALTYPE>& rawvector_expression<VALTYPE>::operator*(matrix_expression<VALTYPE> &A)
  {
    return * new mulvtm(*this,A, _mul_vtm);
  }
   
  template<typename VALTYPE>
  rawvector_expression<VALTYPE>& rawvector_expression<VALTYPE>::operator*(VALTYPE s)
  {
    return * new scaling(*this,s);
  } 

  template<typename VALTYPE>
  rawvector_expression<VALTYPE>& rawvector_expression<VALTYPE>::operator/(VALTYPE s)
  {
    return * new scaling(*this,1e0/s);
  } 

  template<typename VALTYPE>
  vector_expression<VALTYPE>& rawvector_expression<VALTYPE>::T()
  {
    return * new transpone(*this,_rvector + _transp);
  }

  template<typename VALTYPE>
  vector_expression<VALTYPE>& rawvector_expression<VALTYPE>::H()
  {
    return * new transpone(*this,_rvector + _herm);
  }

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& rawvector_expression<VALTYPE>::D()
  {
    return *new expression_unop<VALTYPE,matrix_expression<VALTYPE>,rawvector_expression<VALTYPE> >(*this, _matrix + _diagonal);    
  }

  template<typename VALTYPE>
  vector_expression<VALTYPE>& operator*(VALTYPE s, vector_expression<VALTYPE> &v)
  {
    return * new typename vector_expression<VALTYPE>::scaling(v,s);
  }

  template<typename VALTYPE>
  vector_expression<VALTYPE>& operator*(scalar_expression<VALTYPE> &s, vector_expression<VALTYPE> &v)
  {
    return * new typename vector_expression<VALTYPE>::scaling(v,s);
  }

  //----------------------------------------------------------
  template<typename VALTYPE>
  class subvector : public vector_expression<VALTYPE>
  {

    subrange_expression *I;
    vector_expression<VALTYPE> *vtr;

    vector_shape shp;
    bool shape_defined;

    typedef subvector<VALTYPE> SELF;
  public:

    subvector(subrange_expression &_I, vector_expression<VALTYPE> &_vtr)
    {
      I = &_I;
      vtr = &_vtr;
      
      I -> setref();
      vtr -> setref();

      shape_defined = false;
    }
    
    virtual vector_expression<VALTYPE>& operator=(vector_expression<VALTYPE> &xpr)
    {
      std::cout << "Subvector assignment called\n";
      vector_expression<VALTYPE> *trg = this;
      /* temp
      process_expr<VALTYPE,vector_expression<VALTYPE> >(trg, &xpr);
      */
      return *this;
    }

    virtual vector_expression<VALTYPE> & operator*=(VALTYPE s)
    {
      if (vtr -> gettype() & _actual)
	{
	  _lace_main::wizard<VALTYPE>::V(vtr->vtype()).scale(*vtr, s, I->rng());
	  return *this;
	}
      else
	assert(false && "Not lavalue in subvector scaling");
    }
    
    virtual vector_expression<VALTYPE> & operator=(VALTYPE s)
    {
      if (vtr -> gettype() & _actual)
	{
	  _lace_main::wizard<VALTYPE>::V(vtr->vtype()).fill(*vtr, s, I->rng());
	  return *this;
	}
      else
	assert(false && "Not lavalue in subvector assignment");
    }

    virtual int gettype(){return _subvector;}
    
    virtual int nnext(){ return 2;}
    
    virtual tree_node* next(int i){
      switch(i){
      case 0: return I; break;
      case 1: return vtr; break;
      default: return NULL;
      }
    }

    virtual void setnext(int i, tree_node *p)
    {
      switch(i){
      case 0: I  = (subrange_expression*)p; break;
      case 1: vtr = (vector_expression<VALTYPE>*)p; break;
      }
    }   

    ~subvector(){ }

    virtual abstract_expression* copy( int mask = 0 )
    {
      if ( (mask & _subvector) ^ _vector == 0 )
	return new subvector<VALTYPE>( * (subrange_expression*)(I -> copy(mask)), 
				       * (vector_expression<VALTYPE>*)(vtr -> copy(mask)) );
      else 
	return this;
    }

    virtual void print_tree(int shift = 0)
    { 
      if (shift == 0)
	{

	  std::cout << "(";	  
	  vtr -> print_tree();

	  std::cout << ")(";
	  I -> print_tree();
	  std::cout << ")";
	}
      else
	{
	  print_me(shift);
	  indent(shift+2);
	  std::cout << "index  ";
	  I -> print_tree(1);
	  
	  vtr->print_tree(shift+2);
	}
    }
    
    virtual void print_me(int shift = 0)
    {
      if (shift > 0)
	{
	  indent(shift);
	  std::cout << "subvector : UID = " << ((SELF*)this) -> getUID() << " nref = " 
		    << ((SELF*)this) -> nref << " nbound = " << ((SELF*)this) -> nbound <<"\n";
	}
    }

//     virtual bool lvalue()
//     {
//       return mtr -> lvalue();
//     }

    virtual vector_shape shape()
    {
      if ( !shape_defined)
	{
	  vector_shape base_shp = vtr -> shape();
	  shp = VI_shape( base_shp, I->rng() );
	  shape_defined = true;
	}
      return shp;
    }

  };

  template<typename VALTYPE>
  vector_expression<VALTYPE>& vector_expression<VALTYPE>::operator()(sub I)
  {
    return * new subvector<VALTYPE>( * new subrange_expression(I), *this);
  }

  template<typename VALTYPE>
  vector_expression<VALTYPE>& vector_expression<VALTYPE>::operator()(subrange_expression &I)
  {
    return * new  subvector<VALTYPE>( I, *this);
  }
  
  template<typename VALTYPE>
  vector_expression<VALTYPE>& vector_expression<VALTYPE>::operator=(vector_expression<VALTYPE> &xpr)
  {
    assert(false && "No assignment for vector expression prototype class\n");
  }


};

#endif
