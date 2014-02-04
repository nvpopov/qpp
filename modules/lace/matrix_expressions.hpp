#ifndef _LACE_MATRIX_EXPRESSIONS_H
#define _LACE_MATRIX_EXPRESSIONS_H

//#include <lace/tree.hpp>
//#include <lace/shape.hpp>
#include <lace/expressions.hpp>
#include <lace/range.hpp>
#include <lace/globals.hpp>

//#include <bits/cpp_type_traits.h>

namespace _lace_expressions{

  using _lace_storage::matrix_shape;

  template<typename VALTYPE>
  class mulmm_expression;

  template<typename VALTYPE>
  class transpmatrix_expression;

  template<typename VALTYPE>
  class matrix_expression : public abstract_expression
  {

  public:    

    virtual void calculate_expr(matrix_expression<VALTYPE>* &target, VALTYPE scale = VALTYPE(1e0) );

    typedef expression_literal<VALTYPE,matrix_expression<VALTYPE> >  literal;
    typedef expression_scaling<VALTYPE,matrix_expression<VALTYPE> >  scaling;
    typedef expression_summa<VALTYPE,matrix_expression<VALTYPE> >    summa;
    typedef summa_literal<VALTYPE,matrix_expression<VALTYPE> >       sliteral;
    typedef expression_unop<VALTYPE,matrix_expression<VALTYPE>,matrix_expression<VALTYPE> > unop;
    typedef mixtyped_product<VALTYPE,vector_expression<VALTYPE>,matrix_expression<VALTYPE>,
			     vector_expression<VALTYPE> > mulmv;
    typedef expression_binop<VALTYPE,matrix_expression<VALTYPE> >    binop;

    typedef equality_expression<VALTYPE,matrix_expression<VALTYPE> > equals;
    typedef mulmm_expression<VALTYPE>   mulmm;
    typedef transpmatrix_expression<VALTYPE> transpone;


    // Binary operators

    matrix_expression<VALTYPE>& operator+(matrix_expression<VALTYPE> &A); 
    
    matrix_expression<VALTYPE>& operator-(matrix_expression<VALTYPE> &A); 
    
    matrix_expression<VALTYPE>& operator*(scalar_expression<VALTYPE> &s); 
    
    matrix_expression<VALTYPE>& operator*(VALTYPE s); 
    
    matrix_expression<VALTYPE>& operator/(VALTYPE s); 
    
    matrix_expression<VALTYPE>& operator*(matrix_expression<VALTYPE> &A); 

    vector_expression<VALTYPE>& operator*(vector_expression<VALTYPE> &v);

     // Unary operators
    
    matrix_expression<VALTYPE>& T();
    
    matrix_expression<VALTYPE>& H();
    
    //    matrix_expression<VALTYPE>& I();
    
    vector_expression<VALTYPE>& D();

    // Submatrix & subvector

    virtual matrix_expression<VALTYPE>& operator()(sub I, sub J);

    virtual matrix_expression<VALTYPE>& operator()(subrange_expression &I, subrange_expression &J);

    virtual int basetype(){return _matrix;}
    
    virtual bool equiv(tree_node *tree)
    {
      bool res = tree == NULL ? false : tree -> gettype() == gettype() &&
	nnext() == tree -> nnext();
      return res;
    }

    static _lace_storage::matrix_shape shape() 
    { return _lace_storage::empty_shape(); }
    
    //    virtual _lace_storage::matrix_type mtype(){return shape().mtype;}

    virtual _lace_storage::matrix_type type(){}

    virtual int gettype() = 0;
    //{return _matrix + _proto;}

    virtual abstract_expression* copy(int mask = 0)
    {
//       if ( (mask & _proto) == 0 )
// 	return new matrix<VALTYPE,_lace_storage::nonmatrix>;
//       else
      return this;	
    }

    virtual void print_tree(int shift = 0)=0;
//     {
//       if (shift==0)
// 	std::cout << "TMP" << getUID();
//       else
// 	{
// 	  indent(shift);
// 	  std::cout << "Protomatrix with UID = " << getUID() << " nref = " << nref << "\n";
// 	}
//     }

    virtual void reshape( matrix_shape shp )
    { assert( false && "Error: matrix_expression::reshape is just an interface to matrix::reshape and should never be used"); }

    virtual bool is_empty(){ return _lace_storage::is_empty(shape()); }

    virtual matrix_expression<VALTYPE>& operator=(matrix_expression<VALTYPE> &xpr)
    {
      std::cout << typeid(*this).name() << "\n";
      std::cout << "argument bad: " << typeid(xpr).name() << "\n";
      assert(false && "Bad assignment");
    }

    matrix_expression(){}

    matrix_expression(const matrix_expression<VALTYPE> &xpr)
    {
      assert(false && "Bad assignment in initialization");
    }

  };

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& operator*(VALTYPE s,matrix_expression<VALTYPE> &A);

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& operator*(scalar_expression<VALTYPE> &s,matrix_expression<VALTYPE> &A);
  
  //-----------------------------------------------------------------------


  template<typename VALTYPE>
  class mulmm_expression : public expression_binop<VALTYPE, matrix_expression<VALTYPE> >
  {
    typedef matrix_expression<VALTYPE> XPR;
  public:
    mulmm_expression(matrix_expression<VALTYPE> &l, matrix_expression<VALTYPE> &r) : 
      expression_binop<VALTYPE, matrix_expression<VALTYPE> >(l, r, _prod)
    {}

    virtual abstract_expression* copy( int mask = 0 )
    {
      if ( (mask & _prod) == 0 )
	return new mulmm_expression<VALTYPE>( * (XPR*)(this -> left -> copy(mask)), 
					      * (XPR*)(this -> right -> copy(mask)));
      else 
	return this;
    }
    
    virtual void calculate_expr(XPR* &target, VALTYPE scale = VALTYPE(1e0) );    

    virtual matrix_shape shape();

    virtual void free()
    { delete (mulmm_expression<VALTYPE>*)this;}

    
  };

  //-------------------------------------------------------------------

  template<typename VALTYPE>
  class transpmatrix_expression : public expression_unop<VALTYPE, matrix_expression<VALTYPE>,       
						      matrix_expression<VALTYPE> >{
    typedef matrix_expression<VALTYPE> XPR;
  public:
    transpmatrix_expression(matrix_expression<VALTYPE> &x, int _op) : 
      expression_unop<VALTYPE, matrix_expression<VALTYPE>, matrix_expression<VALTYPE> >(x, _op)
    {
      assert( (_op & (_transp | _herm)) && "Illegal unary operation for transpmatrix_expression class");
    }
    
    virtual matrix_shape shape();

    virtual abstract_expression* copy( int mask = 0 )
    {
      if ( (mask & this -> op) == 0 )
	return new transpmatrix_expression<VALTYPE>( * (XPR*)(this -> xnext(0) -> copy(mask)), 
						  this -> op);
      else 
	return this;
    }

    virtual void free()
    { delete (transpmatrix_expression<VALTYPE>*)this;}
    
  };
  
//   matrix_literal & m(std::string name)
//   {
//     return * new matrix_literal(name);
//   }

//   summa_literal<matrix_expression> & M(std::string name)
//   {
//     return * new summa_literal<matrix_expression>(name);
//   }
    
  
  // Operators

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& matrix_expression<VALTYPE>::operator+(matrix_expression<VALTYPE> &A)
  {
    return * new binop(*this,A,_plus);
  }

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& matrix_expression<VALTYPE>::operator-(matrix_expression<VALTYPE> &A)
  {
    return * new binop(*this,A,_minus);
  }

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& matrix_expression<VALTYPE>::operator*(VALTYPE s)
  {
    return * new scaling(*this,s);
  } 

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& matrix_expression<VALTYPE>::operator/(VALTYPE s)
  {
    return * new scaling(*this,1e0/s);
  } 

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& matrix_expression<VALTYPE>::operator*(matrix_expression<VALTYPE> &A) 
  {
    return * new mulmm(*this,A);
  }

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& matrix_expression<VALTYPE>::T()
  {
    return * new transpone(*this,_transp);
  }

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& matrix_expression<VALTYPE>::H()
  {
    return * new transpone(*this,_herm);
  }

//   template<typename VALTYPE>
//   matrix_expression<VALTYPE>& matrix_expression<VALTYPE>::I()
//   {
//     return * new unop(*this,_inverse);
//   }

  template<typename VALTYPE>
  vector_expression<VALTYPE>& matrix_expression<VALTYPE>::D()
  {
    return * new expression_unop<VALTYPE,vector_expression<VALTYPE>,matrix_expression<VALTYPE> >(*this, _diagonal);
  }

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& operator*(VALTYPE s,matrix_expression<VALTYPE> &A)
  {
    return * new typename matrix_expression<VALTYPE>::scaling(A,s);
  } 

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& operator*(scalar_expression<VALTYPE> &s,matrix_expression<VALTYPE> &A)
  {
    return * new typename matrix_expression<VALTYPE>::scaling(A,s);
  } 

//   matrix_expression& matrix_expression::operator=(matrix_expression &A) 
//   {
//     assert( lvalue() && "Attempt to assign something to an expression which is not lvalue");
//     return * new matrix_binop(*this,A,_equals);
//   }

// ------------------------------------------------------------------------------------------------

  template<typename VALTYPE>
  class submatrix : public matrix_expression<VALTYPE>{

    subrange_expression *I, *J;
    matrix_expression<VALTYPE> *mtr;

    matrix_shape shp;
    bool shape_defined;

    typedef submatrix<VALTYPE> SELF;
  public:
    
    submatrix(subrange_expression &_I, subrange_expression &_J, matrix_expression<VALTYPE> &_mtr)
    {
      I = &_I;
      J = &_J;
      mtr = &_mtr;
      
      I -> setref();
      J -> setref();
      mtr -> setref();

      shape_defined = false;
    }
    
    virtual int gettype(){return _submtr;}
    
    virtual int nnext(){ return 3;}
    
    virtual tree_node* next(int i){
      switch(i){
      case 0: return I; break;
      case 1: return J; break;
      case 2: return mtr; break;
      default: return NULL;
      }
    }
    
    virtual void setnext(int i, tree_node *p)
    {
      switch(i){
      case 0: I  = (subrange_expression*)p; break;
      case 1: J  = (subrange_expression*)p; break;
      case 2: mtr = (matrix_expression<VALTYPE>*)p; break;
      }
    }   

    //debug--------
    virtual void print_tree(int shift = 0)
    { 
      if (shift == 0)
	{

	  std::cout << "(";	  
	  mtr -> print_tree();

	  std::cout << ")(";
	  I -> print_tree();
	  std::cout << ",";
	  J -> print_tree(); 
	  std::cout << ")";
	}
      else
	{
	  print_me(shift);
	  indent(shift+2);
	  std::cout << "index 1 ";
	  I -> print_tree(1);
	  indent(shift+2);
	  std::cout << "index 2 ";
	  J -> print_tree(1);
	  
	  mtr->print_tree(shift+2);
	}
    }
    
    virtual void print_me(int shift = 0)
    {
      if (shift > 0)
	{
	  indent(shift);
	  std::cout << "submatrix : UID = " << ((SELF*)this) -> getUID() << " nref = " 
		    << ((SELF*)this) -> nref << " nbound = " << ((SELF*)this) -> nbound <<"\n";
	}
    }

    virtual void free(){delete (SELF*)this;}
    
    ~submatrix(){ }

    virtual abstract_expression* copy( int mask = 0 )
    {
      if ( (mask & _submtr) ^ _matrix == 0 )
	return new submatrix<VALTYPE>( * (subrange_expression*)(I -> copy(mask)), 
				       * (subrange_expression*)(J -> copy(mask)),
				       * (matrix_expression<VALTYPE>*)(mtr -> copy(mask)) );
      else 
	return this;
    }
    
    virtual matrix_shape shape()
    {
      if ( !shape_defined)
	{
	  matrix_shape base_shp = mtr -> shape();
	  shp = MIJ_shape( base_shp, I->rng(), J->rng() );
	  shape_defined = true;
	}
      return shp;
    }

    virtual submatrix<VALTYPE>& operator=(matrix_expression<VALTYPE> &xpr)
    {
      //      std::cout << "Submatrix assignment called\n";
      matrix_expression<VALTYPE> *trg = this;
      process_expr<VALTYPE,matrix_expression<VALTYPE> >(trg,&xpr);
      return *this;
    }
    
  };

// ------------------------------------------------------------------------------------------------

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& matrix_expression<VALTYPE>::operator()(sub I, sub J)
  {
    return * new submatrix<VALTYPE>( * new subrange_expression(I), * new subrange_expression(J), *this);
  }

  template<typename VALTYPE>
  matrix_expression<VALTYPE>& matrix_expression<VALTYPE>::operator()(subrange_expression &I, subrange_expression &J)
  {
    return * new submatrix<VALTYPE>( I, J, *this);
  }


};

#endif
