#ifndef _LACE_EXPRESSIONS_H
#define _LACE_EXPRESSIONS_H

#include <lace/tree.hpp>
#include <lace/complex.hpp>

namespace _lace_expressions{

  using _lace_tree::tree_node;

  // --- Just for debug ---
  void indent(int shift);
  
  /**
   * @brief The base of all expression classes
   **/
  class abstract_expression : public tree_node{
    
    //    typedef abstract_expression<VALTYPE> XPR;
    //typedef abstract_expression self;

    static int xpr_counter;
    int UID;    
    
    abstract_expression* bound_to;
    
  public:
    int nbound;

    //    typedef char shape_type;

    typedef abstract_expression SELF;
    
    //for debug
    static int xpr_total_number;

    abstract_expression(){UID = xpr_counter++; bound_to=NULL; nref=0; nbound=0; xpr_total_number++;}
    
    virtual UIDTYPE getUID(){return UID;}

    virtual int nnext(){return 0;}
    
    virtual tree_node* next(int i){return NULL;}

    inline SELF* xnext(int i){ return (SELF*)next(i); }
    
    virtual void setnext(int i, tree_node *p){}
    
    virtual bool equiv(tree_node *tree)
    {
      bool res = tree == NULL ? false : tree -> gettype() == gettype() &&
	nnext() == tree -> nnext();
      return res;
    }
    
    virtual void print_tree(int shift = 0){}
    
    virtual void print_me(int shift = 0){}
    
    // --- pattern matching mechanism ---
    
    virtual void bind(abstract_expression *xpr)
    { 
      if (nbound==0) bound_to = xpr; 
      nbound++;

//       std::cout << " --bind-- ";
//       print_tree();
//       std::cout << "\n";
    }
    
    virtual void unbind()
    { 
      if (nbound>0) nbound--; 
      if (nbound==0) bound_to = NULL; 
    }  
    
    virtual void unbind_tree()
    {
      unbind();
      for(int i=0; i<nnext(); i++) xnext(i) -> unbind_tree();
    }

    void unbind_completely()
    {
      nbound=0;
      bound_to = NULL; 
      for(int i=0; i<nnext(); i++) xnext(i) -> unbind_completely();
    }

    virtual abstract_expression* bound(){return bound_to;}

//     virtual bool match(XPR *xpr)
//     {
//       bind(xpr);
//       bool res = equiv(xpr);
//       if (res)
// 	{
// 	  for (int i=0; i<nnext(); i++) 
// 	    if ( ! xnext(i) -> match( xpr -> xnext(i) )  )
// 	      {
// 		res = false; 
// 		break;
// 	      }
// 	  if (!res)
// 	    unbind_completely();
// 	}

//       if (!res) unbind();
//       return res;
//     }

    virtual bool match(SELF *xpr)
    {
      bind(xpr);
      bool res = equiv(xpr);
      if (res)
	{
	  int ifail;
	  for (int i=0; i<nnext(); i++) 
	    if ( ! xnext(i) -> match( xpr -> xnext(i) )  )
	      {
		res = false; 
		ifail = i;
		break;
	      }
 	  if (!res)
 	    for (int j=0; j<ifail; j++) xnext(j) -> unbind_tree();
	}

       if (!res) unbind();
      return res;
    }

    // Virtual methods which work only for SUMMA:
    virtual void insert(int i, SELF *xpr){}

    virtual void erase(int i){}

    virtual int nterms(){}

    virtual SELF* bound(int i){}
        
//     template<typename VALTYPE>
//     virtual VALTYPE value(){assert(false && "Attempt to get scalar value of non-scalar expression");}

    virtual SELF* copy(int mask = 0) =0;

    virtual int basetype(){return 0;}

    //    virtual bool lvalue() = 0;

    ~abstract_expression(){
      xpr_total_number--;
      //      std::cout << "expression destructor called\n";
    }

    //    virtual void calculate(abstract_expression* target){}

  };
  
  // fixme
  // to be replace with UID == this
  //  template<typename VALTYPE>

  enum{
    _scalar  = 0,
    _vector  = 0x100000,
    _rvector = 0x200000,
    _matrix  = 0x400000,
    _range   = 0x800000,
    _basetypes = (_vector | _rvector | _matrix | _range)
  };


  //debug
  std::string stype(int t);

  // ------------------------------------------------------------------------------------------------
  // Type table for expressions
  enum{ 
    // Common for all 4 types of expressions:
    _actual   = 0x0001,
    _literal  = 0x0002,
    _sliteral = 0x0004,
    // Binops:
    _plus     = 0x0008,
    _minus    = 0x0010,
    _prod     = 0x0020,
    _equals   = 0x0040,
    // Scaling:
    _scaling  = 0x0080,
    // Unops:
    _transp   = 0x0100,
    _herm     = 0x0200,
    _conj     = 0x0200,
    _diagonal = 0x0400,
    // Protomatrix or protovector
    _proto    = 0x0800,
    // Summa:
    _summa    = 0x1000,
    // Specific for matrix or vector expressions:
    //    _mul_mm       =  _matrix + 0x02000,
    _inverse      =  _matrix + 0x02000,  _mul_mv       =  _vector + 0x02000,     _mul_vtm    = _rvector + 0x02000,
    _outer_prod   =  _matrix + 0x04000,
    _mul_vtv      =  _matrix + 0x08000,
    // Submatricies & subvectors:
    _submtr       =  _matrix + 0x20000,  _subcolmn     =  _vector + 0x20000,     _subrow     = _rvector + 0x20000,
                                         _subvector    =  _vector + 0x40000,     _subrvector = _rvector + 0x40000,
    // Special service expression types
    _link  =  0x80000,
    // Combinations
    _binop = (_plus | _minus | _prod),
    _unop  = (_transp | _herm | _diagonal)
  };

  bool is_literal(abstract_expression *x);

  bool is_sliteral(abstract_expression *x);

  bool is_summa(abstract_expression *x);

  int expr_type(abstract_expression *x);

  // Forward declarations of "modificators"

  template<typename VALTYPE,class XPR>
  class expression_binop;

  template<typename VALTYPE,class XPR>
  class equality_expression;

  template<typename VALTYPE,class XPR>
  class expression_literal;

  template<typename VALTYPE,class XPR>
  class expression_scaling;

  // --------------------------------------------------------------

  template<typename VALTYPE>
  class matrix_expression;

  template<typename VALTYPE>
  class vector_expression;

  template<typename VALTYPE>
  class rawvector_expression;

  template<typename VALTYPE,class XPR1,class XPR2,class XPR3>
  class mixtyped_product;

  // --------------------------------------------------------------

  template<class XPR>
  struct shape_type
  {
    typedef int type;

    static XPR* create(type shp)
    { assert(false && "this should never be called!");}
  };

  template<typename VALTYPE>
  struct shape_type<vector_expression<VALTYPE> >
  {
    typedef _lace_storage::vector_shape type;

    static vector_expression<VALTYPE>* create(_lace_storage::vector_shape shp);
  };

  template<typename VALTYPE>
  struct shape_type<rawvector_expression<VALTYPE> >
  {
    typedef _lace_storage::vector_shape type;

    static rawvector_expression<VALTYPE>* create(_lace_storage::vector_shape shp)
    { assert(false && "this should never be called!");}
  };

  template<typename VALTYPE>
  struct shape_type<matrix_expression<VALTYPE> >
  {
    typedef _lace_storage::matrix_shape type;

    static matrix_expression<VALTYPE>* create(_lace_storage::matrix_shape shp);
  };

  // ---------------------------------------------------------------------------------------------------------------
  // Scalar expressions
  
  template<typename VALTYPE>
  class scalar_expression : public abstract_expression
  {
  public:
    typedef scalar_expression<VALTYPE> SELF;
    typedef expression_binop<VALTYPE, SELF>   binop;
    typedef expression_literal<VALTYPE, SELF> literal;
    typedef expression_scaling<VALTYPE, SELF> scaling;

    scalar_expression& operator+(scalar_expression<VALTYPE> &s);
    scalar_expression& operator+(VALTYPE s);

    scalar_expression& operator-(scalar_expression<VALTYPE> &s);
    scalar_expression& operator-(VALTYPE s);
    
    scalar_expression& operator*(scalar_expression<VALTYPE> &s);
    scalar_expression& operator*(VALTYPE s);
       
    virtual VALTYPE value(){};

    inline VALTYPE value_cast(){ return value(); }

    virtual int basetype(){return _scalar;}
    
  };

  template<typename VALTYPE>
  scalar_expression<VALTYPE>& operator+(VALTYPE s1, scalar_expression<VALTYPE> &s2);  

  template<typename VALTYPE>
  scalar_expression<VALTYPE>& operator*(VALTYPE s1, scalar_expression<VALTYPE> &s2);

  // -------------------------------------------------------------------------------------  
  template<typename VALTYPE>
  class scalar_number : public scalar_expression<VALTYPE>{
    VALTYPE val;
    typedef scalar_number<VALTYPE> SELF;
    
  public:
    
    scalar_number(VALTYPE _val){val = _val;}
    
    virtual int gettype(){return _scalar + _actual;}
    
    virtual bool equiv(tree_node *tree)
    {
      bool res = tree == NULL ? false : tree -> gettype() == gettype() &&
	((SELF*)(this)) -> nnext() == tree -> nnext();
      if (res)
	res = val == ((scalar_number<VALTYPE>*)tree) -> val;
      return res;
    }
    
    //debug--------
    virtual void print_tree(int shift = 0){ print_me(shift);}
    
    virtual void print_me(int shift = 0)
    {
      if (shift==0)
	std::cout << " " << val << " ";
      else
	{
	  indent(shift);
	  std::cout << val << " scalar number : UID = " << ((SELF*)(this)) -> getUID() 
		    << " nref = " << ((SELF*)(this)) -> nref << " nbound = " << ((SELF*)(this)) -> nbound << "\n";
	}
    }
    //--------------
    
    virtual void free(){delete (SELF*)this;}
    
    ~scalar_number(){
//       std::cout << "killing ";
//       print_me(1);
    }
    
    //--------------
    
    //    virtual bool match(abstract_expression<VALTYPE> *xpr)
    virtual bool match(abstract_expression *xpr)
    {
      if (equiv(xpr))
	{
	  ((scalar_expression<VALTYPE>*)this) -> bind(xpr);
	  return true;
	}
      else 
	{
	  return false;
	}
    }
    
    virtual VALTYPE value()
    {
      return val;
    }
    
    virtual abstract_expression* copy(int mask = 0)
    {
      if ( (mask & _actual) == 0 )
	return new scalar_number<VALTYPE>(val);
      else
	return this;
    }

  };


  //-----------------------------------------------------------------------



  template<typename VALTYPE>
  class scalar_conjugate : public scalar_expression<VALTYPE>{

    scalar_expression<VALTYPE> *s;
    typedef scalar_conjugate<VALTYPE> SELF;
    
  public:
    
    scalar_conjugate(scalar_expression<VALTYPE> &_s){s = &_s; s -> setref(); }
    
    virtual int gettype(){return _scalar + _conj;}
     
    virtual int nnext(){ return 1;}
    
    virtual tree_node* next(int i){
      if (i==0)
	return s;
      else
	return NULL;
    }
    
    virtual void setnext(int i, tree_node *p)
    {
      if (i==0)
	s = (scalar_expression<VALTYPE>*)p;
    }

   //debug--------
    virtual void print_tree(int shift = 0)
    { 
      if (shift == 0)
	{
	  std::cout << "(";
	  s->print_tree();
	  std::cout << ")";
	  print_me();
	}
      else
	{
	  print_me(shift);
	  s -> print_tree(shift+4);
	}
    }
    
    virtual void print_me(int shift = 0)
    {
      if (shift == 0)
	std::cout << "^*";
      else
	{
	  indent(shift);
	  std::cout << " scalar conjugate : UID = " << ((SELF*)this) -> getUID() 
		    << " nref = " << ((SELF*)this) -> nref << "\n";
	}
    }
    
    //--------------
    
    virtual void free(){delete (SELF*)this;}
    
    ~scalar_conjugate(){
//       std::cout << "killing ";
//       print_me(1);
    }
    
    //--------------
    
    
    virtual VALTYPE value()
    {
      return lace::conj( s->value());
    }
    
    virtual abstract_expression* copy(int mask = 0)
    {
      if ( (mask & _conj) == 0 )
	return new SELF( * ((scalar_expression<VALTYPE>*)(s -> copy(mask))) );
      else
	return this;
    }

  };

  //-----------------------------------------------------------------------
  
  template<typename VALTYPE,class XPR>
  class expression_literal : public XPR{

    std::string name;
    int match_mask;
    
  public:
    typedef expression_literal<VALTYPE,XPR> SELF;
    
    expression_literal(std::string _name, int _mask = ~0x0)
    { name = _name; match_mask = _mask; }
    
    virtual int gettype(){return ((SELF*)this) -> basetype() + _literal;}
    
    virtual bool equiv(tree_node *tree)
    {
      bool res = tree == NULL ? false : tree -> gettype() == gettype() &&
	((XPR*)this) -> nnext() == tree -> nnext();
      if (res)
	res = name == ((SELF*)tree) -> name;
      return res;
    }
    
    //debug--------
    virtual void print_tree(int shift = 0){ print_me(shift);}
    
    virtual void print_me(int shift = 0)
    {
      if (shift==0)
	std::cout << " " << name << " ";
      else
	{	  
	  indent(shift);
	  std::cout << name << " " << stype(((SELF*)this)->basetype()) << " literal : UID = " << ((SELF*)this) -> getUID() 
		    << " nref = " << ((SELF*)this) -> nref  << " mask = " << match_mask << " nbound = " << ((SELF*)this) -> nbound<< "\n";
	}
    }
    //--------------
    
    virtual void free(){delete (SELF*)this;}
    
    ~expression_literal(){
//       std::cout << "killing ";
//       print_me(1);
    }
    
    //--------------

    void setmask(int _mask)
    { match_mask = _mask; }
    
    virtual bool match(abstract_expression *xpr)
    {
      bool res = true;
      if ( ((SELF*)this) -> bound() == NULL )
	{
	  if ( ( ((SELF*)this)->basetype() == xpr -> basetype() ) && (match_mask & xpr -> gettype()) )
	    ((SELF*)this) -> bind(xpr);
	  else
	    res = false;
	}
      else if ( ((XPR*)this) -> bound() -> getUID() == xpr -> getUID() )
	((SELF*)this) -> bind(xpr);
      else 
	{
	  res = false;
	}
      return res;
    }
    
    virtual VALTYPE value()
    {
      assert( ((SELF*)this) -> basetype() == _scalar && "Illegal attempt to get scalar value of non-scalar expression" );
      assert( ((SELF*)this) -> bound() != NULL && "Illegal attempt to get numerical value of undefined variable" );
      return ((scalar_expression<VALTYPE>*) (((SELF*)this) -> bound())) -> value_cast();
    }
    
    virtual abstract_expression* copy(int mask = 0)
    {
      if ( (mask & _literal) == 0 )
	return new expression_literal<VALTYPE,XPR>(name);
      else
	return this;
    }

    //    virtual bool lvalue(){ return true; }

//     expression_literal(const SELF &A)
//     {
//     }

//     virtual XPR& operator=(XPR &A)
//     {  
// //       std::cout << "\n\n" << typeid(*this).name() << "\n";
// //       std::cout << "argument: " << typeid(A).name() << "\n";
// //       std::cout << "literal::assignament\n";
//       return * new equality_expression<VALTYPE,XPR>(*this,A);
//     }

     virtual XPR& operator=(XPR &A)
     {
       return * new equality_expression<VALTYPE,XPR>(*this,A);
     }

  };
    

  template<typename VALTYPE,class XPR>
  class expression_binop : public XPR{
  protected:
    int op;
    XPR *left, *right;

    //    typename _binop_specific<VALTYPE,XPR>::shape_type shp;
    //    typename XPR::shape_type shp;
    typename shape_type<XPR>::type shp;
    bool shape_defined;
        
  public:
    typedef expression_binop<VALTYPE,XPR> SELF;

    expression_binop(XPR &l, XPR &r, int _op )
    {
      left  = &l;
      right = &r;
      left  -> setref();
      right -> setref();
      op = _op;
      shape_defined = false;
    }
    
    virtual int gettype(){return ((SELF*)this)->basetype() + op;}
    
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
      case 0: left  = (XPR*)p; break;
      case 1: right = (XPR*)p; break;
      }
    }
    
    //debug--------
    virtual void print_tree(int shift = 0)
    { 
      if (shift == 0)
	{
	  std::cout << "(";
	  if (left != NULL) left->print_tree(); 
	  print_me();
	  if (right != NULL) right->print_tree(); 
	  std::cout << ")";
	}
      else
	{
	  if (left != NULL) left->print_tree(shift+4); 
	  print_me(shift);
	  if (right != NULL) right->print_tree(shift+4); 	
	}
    }
    
    virtual void print_me(int shift = 0)
    {
      std::string sgn;

      switch (op){
      case _plus:   sgn = "+"; break;
      case _minus:  sgn = "-"; break;
      case _prod:   sgn = "*"; break;
      case _equals: sgn = "="; break;
      };

      if (shift == 0)
	std::cout << ") "<< sgn <<" (";
      else
	{
	  indent(shift);
	  std::cout << sgn << " " << stype(((SELF*)this)->basetype()) << "  op : UID = " << ((SELF*)this) -> getUID() 
		    << " nref = " << ((SELF*)this) -> nref << " nbound = " << ((SELF*)this) -> nbound <<"\n";
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
    
    ~expression_binop(){
//       std::cout << "killing ";
//       print_me(1);
    }
    
    virtual VALTYPE value()
    {
      assert( ((SELF*)this)->basetype() == _scalar && "Attempt to get scalar value of non-scalar expression" );
      VALTYPE res, vl, vr;
      vl = ((scalar_expression<VALTYPE>*) left) -> value_cast();
      vr = ((scalar_expression<VALTYPE>*) right) -> value_cast();
      switch (op){
      case _plus:     res = vl + vr;
	break;
      case _minus:    res = vl - vr;
	break;
      case _prod:     res = vl * vr;
	break;
      }    
      return res;
    }    

    virtual abstract_expression* copy( int mask = 0 )
    {
      if ( (mask & _binop) == 0 )
	return new expression_binop<VALTYPE,XPR>( * (XPR*)(left -> copy(mask)), * (XPR*)(right -> copy(mask)), op);
      else 
	return this;
    }

    virtual void calculate_expr(XPR* &target, VALTYPE scale = VALTYPE(1e0) )
    {
      //      _binop_specific<VALTYPE,XPR>::calculate_expr(target,this,scale);
      assert(false && "expression_binop::calc should not be called");
    }

    virtual typename shape_type<XPR>::type shape()
    {
//       if ( ! shape_defined)
// 	{
// 	  shp = _binop_specific<VALTYPE,XPR>::shape(this);
// 	  shape_defined = true;
// 	}
//       return shp;
      print_tree(1);
      assert(false && "expression_binop::shape should not be called");
    }

    virtual XPR& operator=(XPR &A)
    {
      assert(false && "It's illegal to assign anything to binary operation");
    }

  };

  //-----------------------------------------------------------------
  template <typename VALTYPE, class XPR>
  class equality_expression : public expression_binop<VALTYPE,XPR>{

    bool already_calculated;

  public:
    equality_expression(XPR &l, XPR &r) : 
      expression_binop<VALTYPE,XPR>(l,r,_equals)
    { already_calculated = false; }

    virtual void calculate_expr(XPR* &target, VALTYPE scale = VALTYPE(1e0) );

    virtual typename shape_type<XPR>::type shape();

    /*   virtual void print_tree(int shift=0)
    {
      if (shift>0)
	{
	  indent(shift);
	  std::cout << "Special equality type\n";
	}
      expression_binop<VALTYPE,XPR>::print_tree(shift);
    }
    */
    virtual abstract_expression* copy( int mask = 0 )
    {
      if ( (mask & _equals) == 0 )
	return new equality_expression<VALTYPE,XPR>( * (XPR*)(this -> left -> copy(mask)), 
						     * (XPR*)(this -> right -> copy(mask)));
      else 
	return this;
    }

  };

//   template<typename VALTYPE, class XPR>
//   VALTYPE expression_binop<VALTYPE,XPR>::value()
//   {
//     assert(false && "Scalar value of non-scalar object requested");
//     op = 1;
//   }

//   template<typename VALTYPE>
//   VALTYPE expression_binop<VALTYPE,abstract_expression::SELF>::value()
//   {
//     assert(false && "Scalar value of non-scalar object requested");
//     op = 1;
//   }

//   template<typename VALTYPE>
//   VALTYPE expression_binop<VALTYPE,typename scalar_expression<VALTYPE>::SELF>::value()
//   {
//     //    assert( ((SELF*)this)->basetype() == _scalar && "Attempt to get scalar value of non-scalar expression" );
//     VALTYPE res;
//     switch (op){
//     case _plus:     res = left -> value() + right -> value();
//       break;
//     case _minus:    res = left -> value() - right -> value();
//       break;
//     case _prod:     res = (left -> value()) * (right -> value());
//       break;
//     }    
//     return res;
//   }

  //------- Unary operations ( like transp and herm )

//   template <typename VALTYPE,class XPR1, class XPR2>
//   class _unop_specific{
//   public:
//     //    typedef char   shape_type;
    
//     static void calculate_expr(XPR1* &target, XPR1 *xpr, VALTYPE scale)
//     {
//       assert(false && "This should not happed -- unop_specific prototype called");
//     }

//     static typename shape_type<XPR1>::type shape(XPR1 *xpr)
//     {
//       assert(false && "This should not happed -- unop_specific prototype called");
//     }

//   };


  template<typename VALTYPE, class XPR1, class XPR2>
  class expression_unop : public XPR1{
    
    XPR2 *a;

  protected:

    int op;
    typename shape_type<XPR1>::type shp;
    bool shape_defined;
    
    typedef expression_unop<VALTYPE,XPR1,XPR2> SELF;
  public:
    expression_unop(XPR2 &_a, int _op)
    {
      a = &_a;
      a -> setref();
      op = _op;
      shape_defined = false;
    }
    
    virtual int gettype(){return ((SELF*)this) -> basetype() + op;}
    
    virtual int nnext(){ return 1;}
    
    virtual tree_node* next(int i){
      if (i==0)
	return a;
      else
	return NULL;
    }
    
    virtual void setnext(int i, tree_node *p)
    {
      if (i==0)
	a = (XPR2*)p;
    }
    
    //debug--------
    virtual void print_tree(int shift = 0)
    { 
      if (shift == 0)
	{
	  std::cout << "(";
	  a->print_tree();
	  std::cout << ")";
	  print_me();
	}
      else
	{
	  print_me(shift);
	  a -> print_tree(shift+4);
	}
    }
    
    virtual void print_me(int shift = 0)
    {
      if (shift == 0)
	switch( op  )
	  {
	  case _transp: std::cout << "^T  ";  break;
	  case _herm:   std::cout << "^H  ";  break;
	  case _inverse:    std::cout << "^Inv  "; break;
	  }
      else
	{
	  indent(shift);
	  switch( op  )
	    {
	    case _transp: std::cout << " Transp ";  break;
	    case _herm:   std::cout << " Herm ";    break;
	    case _inverse:    std::cout << " Inverse "; break;
	    }
	  std::cout << stype(((SELF*)this) -> basetype()) << " : UID = " << ((SELF*)this) -> getUID() 
		    << " nref = " << ((SELF*)this) -> nref << "\n";
	}
    }
    //--------------
    
    virtual abstract_expression* copy( int mask = 0)
    {
      if ( (mask & op) == 0 )
	return new SELF( * ((XPR2*)(a -> copy(mask))), op);
      else
	{
	  //	  std::cout << "SELF returned instead of copy\n";
	  return this;
	}
    }

    virtual void free(){delete (SELF*)this;}
    
    ~expression_unop(){
//       std::cout << "killing ";
//       print_me(1);
    }


    virtual void calculate_expr(XPR1* &target, VALTYPE scale = VALTYPE(1e0) )
    {
      assert(false && "expression_unop::calc should not be called");
      // _unop_specific<VALTYPE,XPR1,XPR2>::calculate_expr(target,this,scale);
    }

    virtual typename shape_type<XPR1>::type shape()
    { 
      assert(false && "expression_unop::shape should not be called");
//       if ( ! shape_defined)
// 	{
// 	  shp = _unop_specific<VALTYPE,XPR1,XPR2>::shape(this);
// 	  shape_defined = true;
// 	}
//       return shp;
    }

    virtual XPR1& operator=(XPR1 &A)
    {
      assert(false && "It's illegal to assign anything to unary operation");
    }

  };

  // ---------------------------------------------------------------------
  template <typename VALTYPE,class XPR>
  class expression_scaling : public XPR{
    
    XPR *a;
    scalar_expression<VALTYPE> *s;
    
    typedef expression_scaling<VALTYPE,XPR> SELF;
  public:

    expression_scaling(XPR &_a, VALTYPE _s)
    {
      a = &_a;
      a -> setref();
      s = new scalar_number<VALTYPE>(_s);
      s -> setref();
    }
    
    expression_scaling(XPR &_a, scalar_expression<VALTYPE> &_s)
    {
      a = &_a;
      a -> setref();
      s = &_s;
      s -> setref();
    }
    
    virtual int gettype(){return ((SELF*)this) -> basetype() + _scaling;}
    
    virtual int nnext(){ return 2;}
    
    virtual tree_node* next(int i){
      if (i==0)
	return s;
      else if (i==1)
	return a;
      else
	return NULL;
    }
    
    virtual void setnext(int i, tree_node *p)
    {
      if (i==0)
	s = (scalar_expression<VALTYPE>*)p;
      else if (i==1)
	a = (XPR*)p;
    }
        
    //debug--------
    virtual void print_tree(int shift = 0)
    { 
      if (shift == 0)
	{
	  std::cout << "(";
	  s->print_tree();
	  print_me();
	  a->print_tree();
	  std::cout << ")";
	}
      else
	{
	  print_me(shift);
	  s -> print_tree(shift+4);
	  a -> print_tree(shift+4);
	}
    }
    
    virtual void print_me(int shift = 0)
    {
      if (shift == 0)
	std::cout << ") * (";
      else
	{
	  indent(shift);
	  std::cout << " " << stype(((SELF*)this)->basetype()) << " scaling  : UID = " << ((XPR*)this) -> getUID() 
		    << " nref = " << ((XPR*)this) -> nref << " nbound = " << ((XPR*)this) -> nbound << "\n";
	}
    }
    //--------------
    
    virtual void free(){delete (SELF*)this;}
    
    virtual abstract_expression* copy( int mask = 0 )
    {
      if ( (mask & _scaling) == 0)
	return new expression_scaling<VALTYPE,XPR>( * (XPR*)( a -> copy(mask)), 
						    * (scalar_expression<VALTYPE>*)(s -> copy(mask)));
      else
	return this;
    }

    virtual XPR& operator=(XPR &A)
    {
      assert(false && "It's illegal to assign anything to scaling operation");
    }

    ~expression_scaling(){
//       std::cout << "killing ";
//       print_me(1);
    }
  };

//   template<typename VALTYPE>
//   typedef expression_binop<VALTYPE,scalar_expression<> > scalar_binop<VALTYPE>;
//   typedef expression_literal<scalar_expression> scalar_literal;


  

  // ------------------------------------------------------------------------------
  template<typename VALTYPE>
  scalar_expression<VALTYPE>& scalar_expression<VALTYPE>::operator+(scalar_expression<VALTYPE> &s)
  {
    return * new binop(*this,s,_plus);
  }
  
  template<typename VALTYPE>
  scalar_expression<VALTYPE>& scalar_expression<VALTYPE>::operator+(VALTYPE s)
  {
    return * new binop(*this, * new scalar_number<VALTYPE>(s),_plus);
  }
 
  template<typename VALTYPE>
  scalar_expression<VALTYPE>& scalar_expression<VALTYPE>::operator-(scalar_expression<VALTYPE> &s)
  {
    return * new binop(*this,s,_minus);
  }
   
  template<typename VALTYPE>
  scalar_expression<VALTYPE>& scalar_expression<VALTYPE>::operator-(VALTYPE s)
  {
    return * new binop(*this, * new scalar_number<VALTYPE>(s),_minus);
  }
   
  template<typename VALTYPE>
  scalar_expression<VALTYPE>& scalar_expression<VALTYPE>::operator*(scalar_expression &s)
  {
    return * new binop(*this,s,_prod);
  }
  
  template<typename VALTYPE>
  scalar_expression<VALTYPE>& scalar_expression<VALTYPE>::operator*(VALTYPE s)
  {
    return * new binop(*this, * new scalar_number<VALTYPE>(s),_prod);
  }
  
  template<typename VALTYPE>
  scalar_expression<VALTYPE>& operator+(VALTYPE s1, scalar_expression<VALTYPE> &s2)
  {
    return * new typename scalar_expression<VALTYPE>::binop(* new scalar_number<VALTYPE>(s1), s2, _plus);
  }

  template<typename VALTYPE>
  scalar_expression<VALTYPE>& operator-(VALTYPE s1, scalar_expression<VALTYPE> &s2)
  {
    return * new typename scalar_expression<VALTYPE>::binop(* new scalar_number<VALTYPE>(s1), s2, _minus);
  }
  
  template<typename VALTYPE>
  scalar_expression<VALTYPE>& operator*(VALTYPE s1, scalar_expression<VALTYPE> &s2)
  {
    return * new typename scalar_expression<VALTYPE>::binop(* new scalar_number<VALTYPE>(s1), s2, _prod);
  }

  template<typename VALTYPE>
  scalar_expression<VALTYPE>& conj(scalar_expression<VALTYPE> &s)
  {
    return * new scalar_conjugate<VALTYPE>(s);
  }

  // ------------- SUMMA --------------------------------------------------------------

  template <typename VALTYPE,class XPR>
  class _summa_specific{
  public:
    static void calculate_expr(XPR* &target, XPR *xpr)
    {
      assert(false && "This should not happen!! -- _summa_specific prototype called");
    }

  };

  template <typename VALTYPE,class XPR>
  class expression_summa : public XPR{
  protected:

    std::vector<XPR*> terms;

    typedef expression_summa<VALTYPE,XPR> SELF;

    friend class _summa_specific<VALTYPE,XPR>;

    typename shape_type<XPR>::type shp;
    bool shape_defined;

  public:

    expression_summa(){shape_defined=false;}

    expression_summa(XPR *_terms[], int n)
    {
      for(int i=0; i<n; i++)
	{
	  terms.push_back(_terms[i]);
	  terms[i] -> setref();
	}
      shape_defined = false;
    }

    virtual int gettype(){return ((SELF*)this) -> basetype() + _summa; }

    virtual tree_node* next(int i){ return terms[i]; }

    virtual int nnext(){ return terms.size(); }

    virtual void setnext(int i, tree_node* p){ terms[i] = (XPR*)p; }

    void add(XPR *xpr){ terms.push_back(xpr); }
    
    virtual void erase(int i)
    { 
      // fixme -- how to unlink term properly?
      //      ((SELF*)this) -> unlink_tree(i);
      terms.erase(terms.begin()+i); 
    }

    virtual void insert(int i, abstract_expression *xpr){ terms.insert(terms.begin()+i,(XPR*)xpr); }

    void clear(){ terms.clear(); }

    virtual void print_me(int shift = 0)
    {
      if (shift == 0)
	std::cout << " SUM { ";
      else
	{
	  indent(shift);
	  std::cout << " " << stype(((SELF*)this) -> basetype()) << " SUMMA of size " << terms.size() 
		    << " : UID = " << ((XPR*)this) -> getUID() 
		    << " nref = " << ((XPR*)this) -> nref << " nbound = " << ((XPR*)this) -> nbound<< "\n";
	}
    }

    virtual void print_tree(int shift = 0)
    {
      if (shift == 0)
	{
	  print_me();
	  for(int i = 0; i<terms.size(); i++)
	    {	 
	      terms[i] -> print_tree();
	      if ( i < terms.size() - 1 ) std::cout << " ,+ ";
	    }
	  std::cout << " }";
	}
      else
	{
	  print_me(shift);	  
	  for (int i = 0; i<terms.size(); i++)
	    {
	      indent(shift+4);
	      std::cout << "term " << i << "\n";
	      terms[i] -> print_tree(shift+4);
	    }
	}
    }

    bool match_term(int term, abstract_expression *xpr, int first);

    virtual bool match(abstract_expression *xpr);

    virtual void free(){delete (expression_summa<VALTYPE,XPR>*)this;}
    
    ~expression_summa(){
//       std::cout << "killing ";
//       print_me(1);
    }

    virtual abstract_expression* copy(int mask = 0)
    {
      if ( (mask & _summa) == 0)
	{
	  expression_summa<VALTYPE,XPR> * tmp = new expression_summa<VALTYPE,XPR>;
	  for (int i = 0; i < terms.size(); i++)
	    {
	      tmp -> add( (XPR*)(terms[i] -> copy(mask)) );
	      tmp -> xnext(i) -> setref();
	    }
	  return tmp;
	}
      else
	return this;
    }

    virtual void calculate_expr(XPR* &target, VALTYPE scale = VALTYPE(1e0) )
    {
      _summa_specific<VALTYPE,XPR>::calculate_expr(target,this);
    }

    
    virtual typename shape_type<XPR>::type shape()
    {
      if ( ! shape_defined )
	{
	  // shp = _summa_specific<VALTYPE,XPR>::shape(this);
	  shape_defined = true;
	}
      return shp;
    }
    

    virtual XPR& operator=(XPR &A)
    {
      assert(false && "It's illegal to assign anything to SUMMA");
    }

  };


  // -------------------------------------------

  template <typename VALTYPE,class XPR>
  class summa_literal : public expression_summa<VALTYPE,XPR>{
    
    std::string name;

    friend class expression_summa<VALTYPE,XPR>;

    typedef summa_literal<VALTYPE,XPR> SELF;
  public:

    summa_literal(std::string _name){ name = _name; }
    
    virtual int gettype(){return ((SELF*)this) -> basetype() + _sliteral;}
    
    virtual bool equiv(tree_node *tree)
    {
      bool res = tree == NULL ? false : tree -> gettype() == gettype() &&
	((summa_literal<VALTYPE,XPR>*)this) -> nnext() == tree -> nnext();
      if (res)
	res = name == ((summa_literal<VALTYPE,XPR>*)tree) -> name;
      return res;
    }
    
    //debug--------
    virtual void print_tree(int shift = 0){ print_me(shift);}
    
    virtual void print_me(int shift = 0)
    {
      if (shift==0)
	std::cout << " " << name << " ";
      else
	{	  
	  indent(shift);
	  std::cout << name << " " << stype(((SELF*)this) -> basetype()) << " SUMMA literal : UID = " << ((XPR*)this) -> getUID() 
		    << " nref = " << ((XPR*)this) -> nref  << " nbound = " << ((XPR*)this) -> nbound  
		    << "terms bound = " << ((SELF*)this) -> terms.size() << "\n";
	}
    }
    //--------------
    
    virtual void free(){delete (SELF*)this;}
    
    ~summa_literal(){
//       std::cout << "killing ";
//       print_me(1);
    }
    
    //--------------
    
//     virtual VALTYPE value()
//     {
//       assert( false && "Illegal attempt to get scalar value of non-scalar expression" );
//     }
    
    virtual int nnext(){return 0;}

    virtual void bind(abstract_expression *xpr)
    {
      assert( false && "Attempt to bind summa_literal directly to abstract_expression");
    }

    void bind(abstract_expression *xpr, int i1, int i2)
    {
      if ( ((expression_summa<VALTYPE,XPR>*)this) -> nbound++ == 0) 
	for(int i = i1; i<=i2; i++) this-> add( (XPR*)(xpr -> xnext(i)) );
    }
    
    virtual int nterms(){return ((summa_literal<VALTYPE,XPR>*)this) -> terms.size();}

    virtual void unbind()
    { 
      SELF* xhis = (SELF*)this;
      if (xhis -> nbound > 0) xhis -> nbound--; 
      if (xhis -> nbound == 0) xhis -> clear(); 
    }

    virtual void unbind_completely()
    {
      SELF* xhis = (SELF*)this;
      xhis -> nbound = 0;
      xhis -> clear();
    }

    virtual abstract_expression* bound(int i)
    {
      return ((expression_summa<VALTYPE,XPR>*)this) -> xnext(i);
    }    

    virtual abstract_expression* bound()
    {
      return ((expression_summa<VALTYPE,XPR>*)this) -> nnext() == 0 ? NULL : 
	((expression_summa<VALTYPE,XPR>*)this) -> xnext(0);
    }

    virtual bool match(abstract_expression *xpr)
    {
      assert( false && "Attempt to match summa_literal directly, not from summa pattern");
    }
  
    bool match(abstract_expression *xpr, int i1, int i2)
    {
      summa_literal<VALTYPE,XPR> * xhis = (summa_literal<VALTYPE,XPR>*)this;
      if ( xhis -> nnext() == 0 )
	{
	  bind(xpr,i1,i2);
	  return true;
	}
      else
	{
	  bool res = ( i2 - i1 + 1 ) == xhis -> nnext();
	  if (res)
	    for (int i = 0; i < xhis -> nnext(); i++)
	      if ( ! xhis -> xnext(i) -> match( xpr -> xnext(i1 + i) ) )
		{
		  res = false;
		  break;
		}
	  if (res) xhis -> nbound++;
	  return res;
	}
    }
    
    virtual abstract_expression* copy(int mask = 0)
    {
      if ( (mask & _sliteral) == 0)
	return new summa_literal<VALTYPE,XPR>(name);
      else
	return this;
    }

  };

  // ---------------------------------------

  template<typename VALTYPE,class XPR>
  bool expression_summa<VALTYPE,XPR>::match_term(int term, abstract_expression *xpr, int first)
  {

    //std::cout << "Matching term pattern " << term << " to summa term " << first << "\n";
    expression_summa<VALTYPE,XPR> *sxpr = (expression_summa<VALTYPE,XPR>*) xpr;
    bool res;

    // All terms are already exhausted
    if ( term  == terms.size() )
      {
	res = first == sxpr -> terms.size();
	//std::cout << "It's term after the last and res = " << res << "\n";
 	return res;
      }

    //terms[term] -> print_tree(5);
    //std::cout << "\n";
    //sxpr -> print_tree(5);

    if ( is_sliteral(terms[term]) )
      {
	//std::cout << "Number of terms = " << sxpr -> terms.size() << " \n";
	summa_literal<VALTYPE,XPR> * lterm = (summa_literal<VALTYPE,XPR>*) terms[term];
	for (int pos = first; pos <= (sxpr -> terms.size()); pos++ )
	  {
	    
	    //std::cout << "   trying range " << first << " to " << pos << "\n";
 	    res = lterm -> match(xpr,first,pos-1);
	    if (res) 
	      {
		//lterm -> print_tree(3);
		//std::cout << "   matched to "<<lterm->nterms() << " terms\n";
		//for(int i=0; i<lterm->nterms(); i++) lterm->bound(i)->print_tree(3);
		res = match_term(term+1,xpr,pos);	      
	      }
	    if (res) break;
	    lterm -> unbind();
	    //for (int i = term; i<terms.size(); i++ ) terms[i] -> unbind_tree();
	  }
      }
    else
      {
	res = first < xpr -> nnext();
	if (res)
	  res = terms[term] -> match( xpr -> xnext(first) );
	if (res) 
	  {
	    //std::cout << "Matched to\n";
	    //xpr -> xnext(first) -> print_tree(7);
	    res = match_term(term+1,xpr,first+1);
	    if (!res)
	      terms[term] -> unbind_tree();
	  }
      }
    // if (!res) terms[term] -> unbind();
    return res;
  }
  
  template<typename VALTYPE,class XPR>
  bool expression_summa<VALTYPE,XPR>::match(abstract_expression *xpr)
  {
    expression_summa<VALTYPE,XPR> *xhis = (expression_summa<VALTYPE,XPR>*)this;
    xhis -> bind(xpr);

    bool res = xpr -> gettype() == xhis -> basetype() + _summa;        

//     std::cout << "Step 1 : res = " << res << "\n";

    if (res)
      res = match_term(0,xpr,0);

    if ( !res ) xhis -> unbind();
    return res;
  }


  // Not a very elegant way, but it's just for internal use
  //- --- ----------------------------------------------------------
  template<typename VALTYPE,class XPR>
  expression_summa<VALTYPE,XPR>&  SUMMA()
  {
    XPR **t;
    return * new expression_summa<VALTYPE,XPR>(t,0);
  }

  template<typename VALTYPE,class XPR>
  expression_summa<VALTYPE,XPR>&  SUMMA(XPR &t1)
  {
    XPR *t[1];
    t[0] = &t1;
    return * new expression_summa<VALTYPE,XPR>(t,1);
  }

  template<typename VALTYPE,class XPR>
  expression_summa<VALTYPE,XPR>&  SUMMA(XPR &t1, XPR &t2)
  {
    XPR *t[2];
    t[0] = &t1;
    t[1] = &t2;
    return * new expression_summa<VALTYPE,XPR>(t,2);
  }

  template<typename VALTYPE,class XPR>
  expression_summa<VALTYPE,XPR>&  SUMMA(XPR &t1, XPR &t2 , XPR &t3)
  {
    XPR *t[3];
    t[0] = &t1;
    t[1] = &t2;
    t[2] = &t3;
    return * new expression_summa<VALTYPE,XPR>(t,3);
  }

  template<typename VALTYPE,class XPR>
  expression_summa<VALTYPE,XPR>&  SUMMA(XPR &t1, XPR &t2 , XPR &t3, XPR &t4)
  {
    XPR *t[4];
    t[0] = &t1;
    t[1] = &t2;
    t[2] = &t3;
    t[3] = &t4;
    return * new expression_summa<VALTYPE,XPR>(t,4);
  }

  template<typename VALTYPE,class XPR>
  expression_summa<VALTYPE,XPR>&  SUMMA(XPR &t1, XPR &t2 , XPR &t3, XPR &t4, XPR &t5)
  {
    XPR *t[5];
    t[0] = &t1;
    t[1] = &t2;
    t[2] = &t3;
    t[3] = &t4;
    t[4] = &t5;
    return * new expression_summa<VALTYPE,XPR>(t,5);
  }

  template<typename VALTYPE,class XPR>
  expression_summa<VALTYPE,XPR>&  SUMMA(XPR &t1, XPR &t2 , XPR &t3, XPR &t4, XPR &t5, XPR &t6)
  {
    XPR *t[6];
    t[0] = &t1;
    t[1] = &t2;
    t[2] = &t3;
    t[3] = &t4;
    t[4] = &t5;
    t[5] = &t6;
    return * new expression_summa<VALTYPE,XPR>(t,6);
  }

  //#define SUM SUMMA<matrix_expression>
  //#define SUV SUMMA<vector_expression>


  // --------------------------------------------------------------

  template<typename VALTYPE>
  class transform{
    bool bound;

    typedef abstract_expression expression;
    typedef tree_node::iterator<expression> iterator;
    typedef expression_binop<VALTYPE,abstract_expression> linktyp;
    typedef expression_unop<VALTYPE,abstract_expression,abstract_expression> linktyp1;
    
  public:
    enum{
      ubnd_bfr = 0x01,
      ubnd_aft = 0x02
    };

    abstract_expression *srch,*rplc;

    //  public:

    transform(abstract_expression &_srch, abstract_expression &_rplc)
    {      
      assert(  _srch.basetype() == _rplc.basetype()  
	       && "Attempt to make pattern with inconsistent expression types" );

      linktyp *link = new linktyp(_srch,_rplc,_link);

      link -> reduce_tree();
      srch = link -> xnext(0);
      rplc = link -> xnext(1);
      link -> free();
      bound = false;
    }

    transform(abstract_expression &_srch)
    {
      linktyp1 *link = new linktyp1(_srch,_link);
      link -> reduce_tree();
      srch = link -> xnext(0);
      rplc = NULL;
      link -> free();
      bound = false;
    }

    ~transform()
    {
      if ( rplc == NULL )
	{
	  linktyp1 *link = new linktyp1(*srch,_link);
	  srch -> unsetref();
	  link -> unlink_tree(0);
	  link -> free();
	}
      else
	{
	  linktyp *link = new linktyp(*srch,*rplc,_link);
	  srch -> unsetref();
	  rplc -> unsetref();
	  
	  link -> unlink_tree(0);
	  link -> unlink_tree(1);
	  link -> free();
	}
    }

    void debug()
    {
      std::cout << "------- Pattern ------\n";
      srch -> print_tree();
      std::cout << " = ";
      rplc -> print_tree();
      std::cout << "\n Details: Pattern\n";
      srch -> print_tree(1);
      std::cout << "\n Transform:\n";
      rplc -> print_tree(1);
    }

    // replaces the pattern srch in the expression xpr with the
    // transformation rplc. It is presumed that the pattern has
    // been already matched to some piece of expression, and all
    // nodes of srch are bound

    abstract_expression* replace(abstract_expression *xpr)
    {
      abstract_expression *old_piece = srch -> bound();
      abstract_expression *new_piece = rplc -> copy( _literal | _sliteral );

      std::vector<abstract_expression*> liter,summ;
      std::vector<int> idx;

      iterator elem(new_piece);
      while (elem != NULL)
	{
	  if ( is_summa( &(*elem)) )
	    summ.push_back( &(*elem) );
	  for (int i = 0; i < elem -> nnext(); i++ )
	    if ( is_literal( elem -> xnext(i) ) )
	      {
		liter.push_back( &(*elem) );
		idx.push_back(i);
	      }
	  elem++;
	}     
      
      for (int k = 0; k<liter.size(); k++ )
	{		  
	  liter[k] -> xnext(idx[k]) -> nref--;
	  liter[k] -> setnext(idx[k], liter[k] -> xnext(idx[k]) -> bound() );
	  liter[k] -> next(idx[k]) -> setref();	  
	}
      for (int k = 0; k<summ.size(); k++ )
	{
	  int i = 0;
	  while ( i < summ[k] -> nnext() )
	    if ( is_sliteral(summ[k]->xnext(i)) )
	      {
		abstract_expression *sl = summ[k] -> xnext(i);		

		summ[k] -> erase(i);
		sl -> unsetref();

		for (int j = 0; j < sl -> nterms(); j++)
		  {
		    summ[k] -> insert(i+j, sl->bound(j));
		    summ[k] -> next(i+j) -> setref();		    
		  }
	      }
	    else
	      i++;
	}
      xpr -> relink_tree( old_piece, new_piece );
      return new_piece;
    }


    void unbind()
    {
      if (bound)
	{
	  srch -> unbind_tree();
	  bound = false;
	}
    }

    bool match(abstract_expression *xpr, int details = 0)
    {
      if ( details & ubnd_bfr )
	srch -> unbind_completely();

      if ( srch -> match(xpr) )
	{
	  bound = true;

	  if ( details & ubnd_aft )
	    {
	      srch -> unbind_completely();
	      bound = false;
	    }

	  return true;
	}
      else
	return false;
    }

    abstract_expression* search(abstract_expression* root, abstract_expression* from = NULL)
    {
      if ( bound ) from = srch -> bound();
      unbind();
      iterator iroot(root);

      // Skip all nodes up to "from" (including it)
      if ( from != NULL )
	{
	  while( iroot != from ) iroot++;
	  iroot++;
	}
      
      while ( iroot != NULL)
	{
	  if ( srch -> match( &(*iroot) ) )
	    {
	      bound = true;
	      return &(*iroot);
	    }
	  else
	    srch -> unbind_completely();
	  iroot++;
	}
      return NULL;
    }

    abstract_expression* replace_once(abstract_expression *root, abstract_expression *from = NULL)
    {
      if ( search(root,from) != NULL )
	{

// 	  std::cout << "Replace_once: ";
// 	  srch->print_tree(1);
// 	  std::cout << " == ";
// 	  rplc->print_tree(1);


	  abstract_expression *res = replace(root);
	  unbind();

// 	  std::cout << "\nResult: ";
// 	  root -> print_tree(1);
// 	  std::cout << "\n\n";

	  return res;
	}
      else
	return NULL;
    }
    
    bool replace_all(abstract_expression *root)
    {
      bool res = false;
      while (replace_once(root)) res = true;
      return res;
    }
        
  };

  template<typename VALTYPE>
  transform<VALTYPE>& operator==(abstract_expression &l, abstract_expression &r)
  {
    return * new transform<VALTYPE>(l,r);
  }

  template<typename VALTYPE>
  transform<VALTYPE>& operator==(matrix_expression<VALTYPE> &l, matrix_expression<VALTYPE> &r)
  {
    return * new transform<VALTYPE>(l,r);
  }

  //----------------------------------------------

  template<typename VALTYPE, class XPR>
  void process_expr(XPR * &target, XPR *xpr);


   
};

namespace _lace_main
{

  template<typename VALTYPE>
  class wizard;
  /*
  template<typename VALTYPE> class m_unary_engine;
  template<typename VALTYPE> class v_unary_engine;
  template<typename VALTYPE> class m_convertor_engine;
  template<typename VALTYPE> class v_convertor_engine;
  template<typename VALTYPE> class mm_binary_engine;
  template<typename VALTYPE> class vv_binary_engine;
  template<typename VALTYPE> class vm_binary_engine;
  template<typename VALTYPE> class mmm_ternary_engine;
  template<typename VALTYPE> class vmv_ternary_engine;

  template<typename VALTYPE, _lace_storage::matrix_type> class m_unary;
  template<typename VALTYPE, _lace_storage::vector_type> class v_unary;
  template<typename VALTYPE, _lace_storage::matrix_type, _lace_storage::matrix_type> class m_convertor;
  template<typename VALTYPE, _lace_storage::vector_type, _lace_storage::vector_type> class v_convertor;
  template<typename VALTYPE, _lace_storage::matrix_type, _lace_storage::matrix_type> class mm_binary;
  
  template<typename VALTYPE> class vv_binary;
  template<typename VALTYPE> class vm_binary;
  template<typename VALTYPE> class mmm_ternary;
  template<typename VALTYPE> class vmv_ternary;*/

};

#endif
