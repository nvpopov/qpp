#ifndef _LACE_CALCULATOR_H
#define _LACE_CALCULATOR_H

//#include <lace/engine.hpp>
#include <lace/globals.hpp>
#include <lace/wizard_instance.hpp>

namespace _lace_expressions{

  using _lace_main::wizard;
  using _lace_storage::matrix_shape;
  using _lace_storage::empty_shape;
  using _lace_storage::is_empty;

  //----------------------

   
  // --------------------- Equality implementation ----------------------

  template<typename VALTYPE>
  vector_expression<VALTYPE>* shape_type<vector_expression<VALTYPE> >::create(_lace_storage::vector_shape shp)
  {
    return &wizard<VALTYPE>::V(shp.vtype).create(shp);
  }
  
  template<typename VALTYPE>
  matrix_expression<VALTYPE>* shape_type<matrix_expression<VALTYPE> >::create(_lace_storage::matrix_shape shp)
  {
    return &wizard<VALTYPE>::M(shp.mtype).create(shp); 
  }
  
  template<typename VALTYPE, class XPR>
  void equality_expression<VALTYPE,XPR>::calculate_expr(XPR* &target, VALTYPE scale )
  {
    if (lace::globals::debug)
      std::cout << "equality_expression::calc\n";
    if (!already_calculated)
      {
	if ( this -> left -> gettype() & _proto)
	  {
	    if (lace::globals::debug)
	      {
		std::cout << "equality_expression::calc: temporary left part\n";
		this -> left -> print_tree(1);
	      }

	    this -> left -> free();
	    this -> left = shape_type<XPR>::create( this -> right -> shape() );    
	    if (lace::globals::debug)
	      {
		std::cout << "equality_expression::calc: temporary created:\n";
		this -> left -> print_tree(1);
	      }
	  }
	this -> right -> calculate_expr(this -> left, scale);
	already_calculated = true;
      }
    target = this -> left;
    if (lace::globals::debug)
      std::cout << "equality_expression::calc finished\n";
    
  }

  template<typename VALTYPE, class XPR>
  typename shape_type<XPR>::type equality_expression<VALTYPE,XPR>::shape()
  {
    if (! this -> shape_defined)
      {
	this -> shp = this -> right -> shape();
	this -> shape_defined = true;
      }
    return this -> shp;
  }

  // -------------- Matrix SUMMA specific methods -------------------
  //               i.e. SUMMA shape and calculate

  template<typename VALTYPE>
  class _summa_specific<VALTYPE,matrix_expression<VALTYPE> >{
  public:
    
    //    typedef matrix_shape                                shape_type;
    typedef typename matrix_expression<VALTYPE>::summa  SXPR;
    typedef matrix_expression<VALTYPE>                  MXPR;
    typedef transform<VALTYPE>                          trnf;   

//     static void calculate_expr(matrix_expression<VALTYPE>* &target, matrix_expression<VALTYPE> *xpr, 
// 			       bool dismiss)
//     {
//       // Check the shape of expression
//       matrix_shape res_shape = xpr -> shape();
      
//       if ( target -> gettype() & _proto )
// 	// If the target is proto-matrix, we delete it and create the
// 	// matrix of necessary shape

// 	// the procedure which called this calculate_expr must take care
// 	// about relinking the target !!!
// 	{
// 	  //matrix_expression<VALTYPE> *tokill = target; 
// 	  delete target;
// 	  target = & wizard<VALTYPE>::w_unary( res_shape.mtype ).create( res_shape );
// 	  //root -> relink_tree(tokill, target);
// 	}
//       else if ( target -> is_empty() )
// 	// It's OK to assign to empty matrix, which automatically accepts necessary shape
// 	{
// 	  // fixme: what if   target->mtype() != res_shape.mtype ?
// 	  target -> reshape( res_shape );
// 	}
//       else
// 	// We have to check is target shape conform to expression shape
// 	// fixme: think about different behaviour with global options
// 	{
// 	  std::cout <<"Target shape: \n"; 
// 	  target-> shape().debug();
// 	  assert(  
// 		 wizard<VALTYPE>::w_summator( target -> mtype(), res_shape.mtype ).
// 		 is_addable( target -> shape(), res_shape ) &&
// 		 "The result shape does not conform to expression shape in SUMMA calculation  "
// 		 );
// 	}
//       bool a_submtr = false;
//       sub sub_IA = sub::full, sub_JA = sub::full;
//       matrix_expression<VALTYPE> *trg_mtr;
//       // Check that in A = B expression A is actual matrix or submatrix of actual matrix
//       if ( !parse_target( target, trg_mtr, a_submtr, sub_IA, sub_JA) ) 
// 	assert(false && "Bad left operand in assignment");
//     }

    static void calculate_expr(matrix_expression<VALTYPE>* &target, matrix_expression<VALTYPE> *xpr)
    {
      
      // Check the shape of expression
      matrix_shape res_shape = xpr -> shape();
      
      if ( target -> gettype() & _proto )
	// If the target is proto-matrix, we create the
	// matrix of necessary shape
	// It is upper level procedures responsibility to delete old target and relink
	// new one
	{
	  target = & wizard<VALTYPE>::M( res_shape.mtype ).create( res_shape );
	}
      else if ( target -> is_empty() )
	// It's OK to assign to empty matrix, which automatically accepts necessary shape
	{
	  // fixme: what if   target->mtype() != res_shape.mtype ?
	  target -> reshape( res_shape );
	}
      else
	// We have to check is target shape conform to expression shape
	// fixme -- global options
	{
// 	  std::cout <<"Target shape: \n"; 
// 	  target-> shape().debug();
	  assert(  
		 _lace_storage::mtr_is_convertable( target -> shape(), res_shape ) &&
		 "The result shape does not conform to expression shape in SUMMA calculation  "
		 );
	}

      // Parse target, define subranges if it's submatrix
      bool a_submtr = false;
      sub sub_IA = sub::full, sub_JA = sub::full;
      matrix_expression<VALTYPE> *trg_mtr;

      // Check that in A = B expression A is actual matrix or submatrix of actual matrix
      if ( !parse_lvalue( target, trg_mtr, a_submtr, sub_IA, sub_JA) ) 
	assert(false && "Bad left operand in assignment");

      // Initialize staff needed for expression parsing
      typename matrix_expression<VALTYPE>::literal a("a"), b("b");
      typename scalar_expression<VALTYPE>::literal s("s");
      typename subrange_expression::literal IA("IA"), IB("IB"), JA("JA"), JB("JB");
      
      a.setref();      b.setref();
      IA.setref();     IB.setref();
      JA.setref();     JB.setref();
      s.setref();
      
      // debug
      if (lace::globals::debug)
	std::cout << "matrix SUMMA calc started\n\n";
      
      /* Checking for "good" and "bad" aliasing
       */
      bool bad_alias = false, good_alias = false;
      SXPR *sxpr = (SXPR*)xpr;
      
      for(int i=0; i < sxpr->terms.size(); i++)
	{
	  matrix_expression<VALTYPE> *t = sxpr -> terms[i];

	  b.match(target);
	  
	  if (  ! trnf( s*b ).match(t, trnf::ubnd_aft) )
	    {
	      abstract_expression::iterator<abstract_expression> tt(t);
	      while ( tt != NULL)
		{
		  if ( trg_mtr -> getUID() == tt -> getUID() )
		    {
		      bad_alias = true;	  

		      if (lace::globals::debug)
			std::cout << "Bad aliasing found!\n";
		      break;
		    }
		  tt++;
		}
	    }
	}
      
      b.unbind_completely();
      b.match(target);

      if ( !bad_alias )
	for (int i = 0; i < sxpr->terms.size(); i++)
	  if (trnf( s*b ).match(  sxpr -> terms[i] ))
	    // Check & treat good aliasing
	    {
	      good_alias = true;
	      
	      if (lace::globals::debug)
		{
		  std::cout << "Good aliasing found!\n";
		  s.print_tree(); std::cout << " = "; s.bound()->print_tree();std::cout << "\n";
		}
	      
	      if (!a_submtr)
		wizard<VALTYPE>::M( target -> mtype() ).scale( *trg_mtr, 
				((scalar_expression<VALTYPE>*)(s.bound()))->value() );
	      else
		wizard<VALTYPE>::M( target -> mtype() ).scale( *trg_mtr, 
				((scalar_expression<VALTYPE>*)(s.bound()))->value(), sub_IA, sub_JA );

	      sxpr->erase(i);
	      
	      if (lace::globals::debug)
		{
		  std::cout<< "SUMM = ";
		  sxpr->print_tree();std::cout << "\n";
		}

	      break;
	    }

      matrix_expression<VALTYPE> *trg_mtr_orig = trg_mtr;
      sub sub_IA_orig = sub_IA, sub_JA_orig = sub_JA;
      if (bad_alias)
	{
	  // Create temporary for result accumulating
	  trg_mtr = & wizard<VALTYPE>::M( res_shape.mtype ).create( res_shape );
	  sub_IA = sub(0,res_shape.n-1,1);
	  sub_JA = sub(0,res_shape.m-1,1);
	  if (lace::globals::debug)
	    {
	      std::cout << "Creating temporary for bad aliasing case\n";
	      trg_mtr -> print_tree(1);
	      std::cout << "Original target is\n";
	      trg_mtr_orig -> print_tree(1);
	    }
	}
      
      if ( !good_alias )
	{
	  if (!a_submtr)
	    wizard<VALTYPE>::M( target -> mtype() ).fill( *trg_mtr, (VALTYPE)0 );
	  else
	    wizard<VALTYPE>::M( target -> mtype() ).fill( *trg_mtr, (VALTYPE)0 , sub_IA, sub_JA);
	}

      // -----------------  Main loop over terms -------------------- //
      bool repeat = false;
      for (int i = 0; i < sxpr->terms.size(); i += repeat ? 0 : 1 )
	{
	  matrix_expression<VALTYPE> *t = sxpr -> terms[i];
	  repeat = false;
	  
// 	  b.print_tree(1);
// 	  s.print_tree(1);
	  
	  if ( !trnf( s*b ).match(t, trnf::ubnd_bfr ) )
	    assert(false && "Canonicalization error!!!" );
	  
	  // Getting the value of "s" or beta - the scaling factor
	  VALTYPE beta = ((scalar_expression<VALTYPE>*)( s.bound() )) -> value();
	  
	  
	  // Single additions: s*A, s*A^T, s*A^H
	  bool b_submtr = false;
	  int OP_B = 0;
	  matrix_expression<VALTYPE> *b_mtr;
	  sub sub_IB = sub::full, sub_JB = sub::full;

	  if (lace::globals::debug)
	    {
	      std::cout << "Before parse_term\n";
	      b.bound() -> print_tree(1);

	      std::cout << "TERM #" << i << "\n";
	      b.bound() -> print_tree();
	    }
	  
	  if ( parse_term( (matrix_expression<VALTYPE>*)b.bound(), b_mtr, b_submtr, sub_IB, sub_JB, OP_B, 
			   _actual | _equals ))
	    {	
	      if (lace::globals::debug)
		std::cout << "submtr: " << b_submtr << " OP_B= " << OP_B << "\n";
	      if (b_mtr -> gettype() & _equals )
// 		{
// 		  matrix_expression<VALTYPE>* equ_trg = (matrix_expression<VALTYPE>*)b_mtr -> next(0);
// 		  if ( equ_trg -> gettype() & _proto  )
// 		    {
// 		      matrix_expression<VALTYPE>* equ_xpr = (matrix_expression<VALTYPE>*)b_mtr -> next(1);
// 		      matrix_expression<VALTYPE>* equ_rslt = equ_trg;
// 		      equ_xpr -> calculate_expr(equ_rslt);
// 		      b_mtr -> relink_tree(equ_trg, equ_rslt);
// 		      equ_trg = equ_rslt;
// 		    }
// 		  b_mtr = (matrix_expression<VALTYPE>*)(b_mtr -> next(0));
// 		}
		{
		  //		  matrix_expression<VALTYPE>* tmp_term = b_mtr;
		  b_mtr -> calculate_expr(b_mtr);
		  //		  b_mtr = tmp_term;
		  //		  std::cout << "Equality calculated\n";
		  //		  b_mtr -> print_tree(1);


		  //fixme -- what if the term looks like
		  //
		  //  (A(I1,J1) = expr)(I2,J2).T()
		  //
		  // we'll need sub_of_sub
		  //		  parse_term( b_mtr, b_mtr, b_submtr, sub_IB, sub_JB, OP_B);
		}

	      if ( (a_submtr && ! bad_alias) || b_submtr )
		{
		  wizard<VALTYPE>::MM( trg_mtr->mtype(), b_mtr->mtype() ).
		    MpM(*trg_mtr, sub_IA, sub_JA, *b_mtr, sub_IB, sub_JB, beta, OP_B);
		}
	      else
		wizard<VALTYPE>::MM( trg_mtr->mtype(), b_mtr->mtype() ).
		  MpM(*trg_mtr, *b_mtr, beta, OP_B);
	    }
	  else
	    {	      
	      // Use the term's own calculate method:
	      ((MXPR*)b.bound()) -> calculate_expr(trg_mtr,beta);
	    }
	}

      if (lace::globals::debug)
	std::cout << "All terms summed\n";
      
      if (bad_alias)
	// If there is bad aliasing, copy the calculation result from temporary into the target
	// and destroy temporary
	{
	  if (lace::globals::debug)
	    {
	      std::cout << "The temporary matrix is now\n";
	      trg_mtr -> print_tree(1);
	      if (res_shape.mtype==_lace_storage::rectang)
		((matrix<VALTYPE,_lace_storage::rectang>*)trg_mtr) -> print_data();
	    }

	  if (!a_submtr)
	    wizard<VALTYPE>::M2M( trg_mtr -> mtype(), trg_mtr -> mtype() ).convert(*trg_mtr_orig, *trg_mtr);
	  else
	    wizard<VALTYPE>::M2M( trg_mtr -> mtype(), trg_mtr -> mtype() ).
	      convert( *trg_mtr_orig, sub_IA_orig, sub_JA_orig, *trg_mtr, sub_IA, sub_JA );
	  
	  trg_mtr -> free();
	}
      
    }
    

    static matrix_shape shape(matrix_expression<VALTYPE> *xpr)
    {
      if (lace::globals::debug) std::cout << "matrix SUMMA shape requested\n\n";

      SXPR *sxpr = (SXPR*)xpr;

      //     if (sxpr->terms.size() == 0) return empty_shape();

      matrix_shape shp = empty_shape();

      for (int i=0; i<sxpr->terms.size(); i++)
	{
	  matrix_shape shp1 = ((MXPR*)(sxpr->terms[i]->next(1)))->shape();

	  if (lace::globals::debug)
	    {
	      std::cout << "term " << i << " "; shp1.debug();
	      sxpr->terms[i]->print_tree(1);
	    }

	  if (i==0)
	    shp = shp1;
	  else
	    shp = _lace_storage::MpM_shape(shp,shp1);

	  assert( ! is_empty(shp) && "Shape non conformant in matrix summation");
	}

      if (lace::globals::debug)
	{
	  std::cout << "The resulting summa shape is ";
	  shp.debug();
	}
      return shp;
    }

  };

  // -------------- Matrix multiplication specific methods -------------------

  //  class _binop_specific<VALTYPE,matrix_expression<VALTYPE> >{
//   public:
//     //    typedef _lace_storage::matrix_shape   shape_type;
    
//     typedef typename matrix_expression<VALTYPE>::binop BXPR;
//     typedef matrix_expression<VALTYPE>                 MXPR;
//     typedef transform<VALTYPE> trnf;

//     static void calculate_expr(matrix_expression<VALTYPE>* &target, matrix_expression<VALTYPE> *xpr, 
// 			       bool dismiss, VALTYPE scale)
//     {
//     }


  template<typename VALTYPE>
  void mulmm_expression<VALTYPE>::calculate_expr(matrix_expression<VALTYPE>* &target, VALTYPE scale)
  {
    //       std::cout << "matrix binop calc started, scale = " << scale << " \n\n";
    //       xpr -> print_tree();std::cout << " \n";
    //       xpr -> print_tree(1);

    //       if ( xpr -> gettype() & _equals )
    // 	{
    // 	  std::cout << "Binop == equals met\n";
    // 	  MXPR *t = (MXPR*)(xpr -> next(0));
    // 	  MXPR *x = (MXPR*)(xpr -> next(1));
    // 	  //xpr -> process_expr( t, xpr, root );
    // 	  x -> calculate_expr( t );
    // 	  xpr -> setnext(0, t);
    // 	  std::cout << "before return\n";
    // 	  return;
    // 	}

    //      assert( (xpr -> gettype() & _prod) && "Error in canonicalization or calculation -- binop!=prod calculation called" );

    int OP_A = 0, OP_B = 0;
    bool a_submtr = false, b_submtr = false, c_submtr = false;
    matrix_expression<VALTYPE> *a_mtr, *b_mtr, *c_mtr;
    sub IA, JA, IB, JB, IC, JC;
 
    if (lace::globals::debug)
      {
	std::cout << "mulmm_expression::calculate_expr:\n";
	std::cout << "expression:\n";
	this -> print_tree(1);
	std::cout << "target:\n";
	target -> print_tree(1);
      }

    bool tmp_a = ! parse_term( (matrix_expression<VALTYPE>*)(this -> xnext(0)), a_mtr, a_submtr, IA, JA, OP_A  );
    bool tmp_b = ! parse_term( (matrix_expression<VALTYPE>*)(this -> xnext(1)), b_mtr, b_submtr, IB, JB, OP_B  );

    if ( tmp_a )
      {
	a_mtr = new matrix<VALTYPE,_lace_storage::nonmatrix>;
	//	  matrix_expression<VALTYPE>::process_expr( a_mtr, (matrix_expression<VALTYPE>*)xpr -> next(0), xpr );
	((matrix_expression<VALTYPE>*)(this -> next(0))) -> calculate_expr( a_mtr );
	this -> relink_tree(this->next(0), a_mtr);
	OP_A = 0;
	a_submtr= false;
	IA = JA = sub::full;
	IA.reduce( 0, a_mtr -> shape().n );
	JA.reduce( 0, a_mtr -> shape().m );
      }
    if ( tmp_b )
      {
	b_mtr = new matrix<VALTYPE,_lace_storage::nonmatrix>;
	//	  ((matrix_expression<VALTYPE>*)(xpr -> next(1))) -> process_expr( b_mtr, xpr );
	((matrix_expression<VALTYPE>*)(this -> next(1))) -> calculate_expr( b_mtr );
	this->relink_tree(this->next(1), b_mtr);
	OP_B = 0;
	b_submtr = false;
	IB = JB = sub::full;
	IB.reduce( 0, b_mtr -> shape().n );
	JB.reduce( 0, b_mtr -> shape().m );
      }
      
    if (! parse_lvalue(target, c_mtr, c_submtr, IC, JC) )
      assert(false && "Bad left assignment operand");
      
    // Do multiplication

    if ( ! ( a_submtr || b_submtr || c_submtr) )      
      wizard<VALTYPE>::MMM( c_mtr -> mtype(), a_mtr -> mtype(), b_mtr -> mtype() ).
	MxM( *c_mtr, *a_mtr, *b_mtr, VALTYPE(1e0), scale, OP_A, OP_B );
    else
      wizard<VALTYPE>::MMM( c_mtr -> mtype(), a_mtr -> mtype(), b_mtr -> mtype() ).
	MxM( *c_mtr, IC, JC, *a_mtr, IA, JA, *b_mtr, IB, JB, VALTYPE(1e0), scale, OP_A, OP_B );

    if (tmp_a)
      {
	// delete temporary
	//	a_mtr -> free();
      }
     
    if (tmp_b)
      {
	// delete temporary
	//	b_mtr -> free();
      }     
  }

  template<typename VALTYPE>
  matrix_shape mulmm_expression<VALTYPE>::shape()
  {
//       if ( xpr -> gettype() & _equals ) 
// 	return ((MXPR*)(xpr -> xnext(1) )) -> shape();
    
//       if ( xpr -> gettype() & _plus ) 
// 	return ((MXPR*)(xpr -> xnext(0) )) -> shape();

    if (! this -> shape_defined)
      {
	
	//      assert( (xpr -> gettype() & _prod ) && "Canonicalization error: binop != mult shape requested");
	if (lace::globals::debug)
	  std::cout << "matrix mult shape requested\n\n";
	typedef matrix_expression<VALTYPE> MXPR;
	MXPR *a = (MXPR*)this->next(0);
	MXPR *b = (MXPR*)this->next(1);

	if (lace::globals::debug)
	  {
	    std::cout << "multiplier 1:\n";
	    a->print_tree(1);
	    std::cout << "multiplier 2:\n";
	    b->print_tree(1);
	  }

	matrix_shape shp_a = a -> shape();
	matrix_shape shp_b = b -> shape();

	if (lace::globals::debug)
	  {
	    std::cout << "mulmm_expression<VALTYPE>::shape(): multiplier 1: ";
	    shp_a.debug();
	    std::cout << "\nmulmm_expression<VALTYPE>::shape(): multiplier 2: ";
	    //shp_b.debug();
	    std::cout << "\n";
	  }
	
	//	this -> shp = wizard<VALTYPE>::MM(shp_a.mtype,shp_b.mtype).MxM_shape(shp_a,shp_b);
	this -> shp = _lace_storage::MxM_shape(shp_a,shp_b);
	this -> shape_defined = true;
      }
    return this -> shp;
  }

  //------------------------------------------------------------------------------

//   template <typename VALTYPE>
//   class _unop_specific<VALTYPE,matrix_expression<VALTYPE>,matrix_expression<VALTYPE> >{
//   public:
//     //    typedef matrix_shape  shape_type;
//     typedef matrix_expression<VALTYPE> MXPR;
    
//     static void calculate_expr(MXPR* &target, MXPR *xpr, VALTYPE scale)
//     {
//       assert(false && "This should not happed -- unop direct calculation called");
//     }
    
//     static matrix_shape shape(MXPR *xpr)
//     {
//       if ( xpr->gettype() & (_transp | _herm) )
// 	{
// 	  //	  std::cout <<"Transp shape requested for";
// 	  matrix_shape shp = ((MXPR*)(xpr ->next(0))) -> shape();
// 	  //shp.debug();
// 	  return wizard<VALTYPE>::M(shp.mtype).T_shape(shp);
// 	}

//     }
    
//   };

  template <typename VALTYPE>
  matrix_shape transpmatrix_expression<VALTYPE>::shape() 
  {
    if ( this -> gettype() & (_transp | _herm) )
      {
	this -> shp = ((matrix_expression<VALTYPE>*)(this ->next(0))) -> shape();
	this -> shape_defined = true;
      }
    //    return wizard<VALTYPE>::M(this -> shp.mtype).T_shape( this -> shp);
    return _lace_storage::transp_shape( this -> shp);
  }

  //------------------------------------------------------------------------------

  template <typename VALTYPE>
  class _summa_specific<VALTYPE, vector_expression<VALTYPE> >{
  public:
    //    typedef vector_shape shape_type;
    typedef vector_expression<VALTYPE> VXPR;
    typedef expression_summa<VALTYPE,VXPR> SXPR;

    static void calculate_expr(VXPR* &target, VXPR *xpr)
    {
      typedef transform<VALTYPE> trnf;

      vector_shape res_shape = xpr -> shape();
      std::cout << "vector sum shape: " << _lace_storage::vtype_spelling[res_shape.vtype] 
		<< " x " << res_shape.n << "\n";
      if ( target -> gettype() & _proto )
	// If the target is proto-matrix, we create the
	// matrix of necessary shape
	// It is upper level procedures responsibility to delete old target and relink
	// new one
	{
	  target = & wizard<VALTYPE>::V( res_shape.vtype ).create( res_shape );
	}
      else if ( is_empty( target -> shape() ) )
	// It's OK to assign to empty matrix, which automatically accepts necessary shape
	{
	  // fixme: what if   target->mtype() != res_shape.mtype ?
	  target -> reshape( res_shape );
	}
      else
	// We have to check is target shape conform to expression shape
	// fixme -- global options
	{
// 	  std::cout <<"Target shape: \n"; 
// 	  target-> shape().debug();
	  assert(  
		 //		 wizard<VALTYPE>::V2V( target -> vtype(), res_shape.vtype ).
		 //		 is_convertable( target -> shape(), res_shape ) &&
		 _lace_storage::vtr_is_convertable( target -> shape(), res_shape ) &&
		 "The result shape does not conform to expression shape in SUMMA calculation  "
		 );
	}

      // Parsing target means to clear out if the left operand has the form of
      // u = or u(I)=, where u is an actual matrix and I is subrange
      vector_expression<VALTYPE> *actual_target, *tmp_target;
      bool subvtr;
      sub I_actual = sub::full, I_tmp = sub::full;
      parse_lvalue(target,actual_target,subvtr,I_actual);
      
      typename vector_expression<VALTYPE>::literal u("u"), v("v"), w("w");
      typename scalar_expression<VALTYPE>::literal s("s");

      u.setref(); v.setref(); w.setref(); s.setref();

      typename vector_expression<VALTYPE>::summa * summa_xpr = (SXPR*)xpr;

      // Check for "good" and "bad" aliasing
      bool bad_alias = false, good_alias = false;
      int i_good;
      VALTYPE beta_good;

      for (int i=0; i < summa_xpr -> terms.size(); i++)
	{	  
	  u.match(target);
	  if ( trnf(s*u).match(summa_xpr -> terms[i]) )
	    {
	      good_alias = true;
	      std::cout << "Good aliasing found!\n";
	      i_good = i;
	      beta_good = ( (scalar_expression<VALTYPE>*)s.bound() ) -> value();
	    }
	  else
	    {
	      abstract_expression::iterator<abstract_expression> term_components(summa_xpr -> terms[i]);
	      while (term_components != NULL)
		{
		  if ( actual_target -> getUID() == term_components -> getUID())
		    {
		      std::cout << "Bad aliasing found!\n";
		      bad_alias = true;
		      break;
		    }
		  term_components++;
		}
	      if (bad_alias) break;
	    }
	  u.unbind_completely();
	}

      // "Good" aliasing and no "bad" aliasing: scale the target
      if ( good_alias && !bad_alias)
	{
	  if (subvtr)
	    wizard<VALTYPE>::V(actual_target -> vtype()).scale(*actual_target, beta_good, I_actual);
	  else
	    wizard<VALTYPE>::V(actual_target -> vtype()).scale(*actual_target, beta_good);
	  summa_xpr -> erase(i_good);
	}


      // In the case of bad aliasing, create temporary vector to store the result
      if (bad_alias)
	{
	  tmp_target = & wizard<VALTYPE>::V(res_shape.vtype).create(res_shape);
	  //	  wizard<VALTYPE>::V(res_shape.vtype).setval(*tmp_target, VALTYPE(0));
	  wizard<VALTYPE>::V(res_shape.vtype).fill(*tmp_target, VALTYPE(0));
	}
      else
	tmp_target = actual_target;

      // Now the decision about target vector of calculation is made,
      // it's time to reduce subranges
      I_actual.reduce(0,actual_target -> shape().n);
      I_tmp.reduce(0,res_shape.n);

      // Loop over terms

      for (int i=0; i < summa_xpr -> terms.size(); i++)
	{
	  std::cout << "term N " << i << "\n";

	  if ( !trnf(s*u).match(summa_xpr -> terms[i], trnf::ubnd_bfr) )
	    assert(false && "Canonicalization error!");
	  // All summa terms must have a form of scalar*vector

	  s.print_tree(1);

	  VALTYPE beta = ((scalar_expression<VALTYPE>*)s.bound()) -> value();
	  vector_expression<VALTYPE> *term;
	  bool term_subvtr;
	  sub I_term;

	  std::cout << "scal_factor = " << beta << "\n";
	  std::cout << "term:\n";
	  //term -> print_tree(1);

	  if ( parse_lvalue((vector_expression<VALTYPE>*)u.bound(), 
			    term, term_subvtr, I_term, _actual | _equals) )
	    {
	    //   if ( trnf(v = w).match(term, trnf::ubnd_bfr) )
// 		// Summa term itself is an equality
// 		{
// 		  if (v.bound() -> gettype() & _proto)
// 		    // Left side of this equality is a protovector, we have replace it
// 		    // with actual vector and permform the calculation of right side
// 		    {
// 		      vector_expression<VALTYPE>* equ_result;
// 		      ((vector_expression<VALTYPE>*)w.bound()) -> calculate_expr(equ_result);
// 		      term -> relink_tree( v.bound(), equ_result );
// 		      trnf( v = w ).match(term, trnf::ubnd_bfr);
// 		    }
// 		  term = (vector_expression<VALTYPE>*)v.bound();
// 		}
	      
	      if ( term -> gettype() & _equals)
		{
		  term -> calculate_expr(term);
		  parse_lvalue(term, term, term_subvtr, I_term);
		}
	      term -> print_tree(1);

	      std::cout << "tmp_target -> vtype = " 
			<<  _lace_storage::vtype_spelling[tmp_target -> vtype()]
			<< "  term -> vtype = " 
			<< _lace_storage::vtype_spelling[term -> vtype()] << "\n";
	      std::cout << "addable" << _lace_storage::vtr_is_addable(tmp_target -> shape(), term -> shape()) << "\n";

	      // Do summation
	      if (term_subvtr)
		wizard<VALTYPE>::VV(tmp_target -> vtype(), term -> vtype()).
		  VpV(*tmp_target,I_tmp, *term, I_term, beta);
	      else
		wizard<VALTYPE>::VV(tmp_target -> vtype(), term -> vtype()).
		  VpV(*tmp_target, *term, beta);
	    }
	  else if ( u.bound() -> gettype() & _mul_mv )
	    {
	      // Maxtrix*vector
	      ((vector_expression<VALTYPE>*)u.bound()) -> calculate_expr(tmp_target,beta);
	    }
	}

      if (bad_alias)
	{
	  std::cout << "actual_target -> vtype = " <<  _lace_storage::vtype_spelling[actual_target -> vtype()]
		    << "tmp_target -> vtype = " << _lace_storage::vtype_spelling[tmp_target -> vtype()] << "\n";

	  if (subvtr)
	    wizard<VALTYPE>::V2V(actual_target -> vtype(), tmp_target -> vtype() ).
	      convert(*actual_target, I_actual, *tmp_target, I_tmp);
	  else
	    wizard<VALTYPE>::V2V(actual_target -> vtype(), tmp_target -> vtype() ).
	      convert(*actual_target, *tmp_target);
	  tmp_target -> free();
	}
      
    }

    static vector_shape shape(VXPR *xpr)
    {
      std::cout << "VECTOR SUMMA shape requested\n\n";

      SXPR *sxpr = (SXPR*)xpr;

      vector_shape shp;

      for (int i=0; i<sxpr->terms.size(); i++)
	{
	  vector_shape shp1 = ((VXPR*)(sxpr->terms[i]->next(1)))->shape();

	  if (i==0)
	    shp = shp1;
	  else
	    shp = _lace_storage::VpV_shape(shp,shp1);

	  assert( ! is_empty(shp) && "Shape non conformant is vector summation");
	}

      std::cout << "The resulting summa shape is ";
      shp.debug();
      return shp;    
    }

  };
  
  //------------------------------------------------------------------------------

//   template <typename VALTYPE>
//   class _binop_specific<VALTYPE, vector_expression<VALTYPE> >{
//   public:
//     //    typedef vector_shape shape_type;
//     typedef vector_expression<VALTYPE> VXPR;
    
//     static void calculate_expr(VXPR* &target, VXPR *xpr, VALTYPE scale)
//     {
//       vector_shape res_shape = xpr -> shape();
//       std::cout << "vector sum shape: " << _lace_storage::vtype_spelling[res_shape.vtype] 
// 		<< " x " << res_shape.n << "\n";
//     }

//     static vector_shape shape(VXPR *xpr)
//     {
//       assert(false && "This should not happed -- binop_specific prototype called");
//     }

//   };

  //------------------------------------------------------------------------------
  
//   template <typename VALTYPE>
//   class _unop_specific<VALTYPE, vector_expression<VALTYPE>, rawvector_expression<VALTYPE> >{
//   public:
//     //    typedef vector_shape                  shape_type;
//     typedef vector_expression<VALTYPE>    XPR1;
//     typedef rawvector_expression<VALTYPE> XPR2;
    
//     static void calculate_expr(XPR1* &target, XPR1 *xpr, VALTYPE scale)
//     {
//       assert(false && "This should not happed -- unop_specific prototype called");
//     }

//   template<typename VALTYPE>
//   vector_shape transpvector_expression<VALTYPE>::shape()
//   {
//     return this -> shape();
//   }

  //------------------------------------------------------------------------------
  
//   template <typename VALTYPE>
//   class _unop_specific<VALTYPE, vector_expression<VALTYPE>, vector_expression<VALTYPE> >{
//   public:
//     //    typedef vector_shape                  shape_type;
//     typedef vector_expression<VALTYPE>    XPR1;
//     typedef vector_expression<VALTYPE> XPR2;
    
//     static void calculate_expr(XPR1* &target, XPR1 *xpr, VALTYPE scale)
//     {
//       assert(false && "This should not happed -- service type _link node calculation called");
//     }

//     static vector_shape shape(XPR1 *xpr)
//     {
//       assert(false && "This should not happed -- service _link node does not have shape");
//     }

//   };
    
  //----------------------  Matrix by vector product ----------------------------

  template <typename VALTYPE>
  vector_shape matrix_by_vector<VALTYPE>::shape()
  {
    if ( ! this -> shape_defined )
      {
	matrix_shape mshp = ((matrix_expression<VALTYPE>*)(this -> left)) -> shape();
	vector_shape vshp = ((vector_expression<VALTYPE>*)(this -> right)) -> shape();
	//	this -> shp = wizard<VALTYPE>::VM(vshp.vtype, mshp.mtype).MxV_shape(mshp,vshp);
	this -> shp = _lace_storage::MxV_shape(mshp,vshp);
	this -> shape_defined = true;
      }
    return this -> shp;
  }
  
  template <typename VALTYPE>
  void matrix_by_vector<VALTYPE>::calculate_expr(vector_expression<VALTYPE>* &target, VALTYPE scale  )
  {
    
    typedef transform<VALTYPE> trnf;
    
    vector_shape res_shape = shape();
    std::cout << "MxV shape: " << _lace_storage::vtype_spelling[res_shape.vtype] 
	      << " x " << res_shape.n << "\n";

    // Parsing target means to clear out if the left operand has the form of
    // u = or u(I)=, where u is an actual matrix and I is subrange

    // The operation is u += M*v
    vector_expression<VALTYPE> *actual_u, *actual_v;
    matrix_expression<VALTYPE> *actual_M;
    bool u_sub, M_sub, v_sub;
    sub Iu = sub::full, IM = sub::full, JM = sub::full, Jv = sub::full;
    int op_M = 0;

    if ( ! parse_lvalue(target, actual_u, u_sub, Iu))
      assert(false && "Canonicalization error in MxV::calculate_expr : left operand");
    if ( ! parse_term(this -> left, actual_M, M_sub, IM, JM, op_M, _actual|_equals))
      assert(false && "Canonicalization error in MxV::calculate_expr : matrix");
    if ( ! parse_lvalue(this -> right, actual_v, v_sub, Jv, _actual|_equals))
      assert(false && "Canonicalization error in MxV::calculate_expr : vector");

    if ( actual_M -> gettype() & _equals )
      actual_M -> calculate_expr(actual_M);

    if ( actual_v -> gettype() & _equals )
      actual_v -> calculate_expr(actual_v);

    if ( u_sub || M_sub || v_sub )
      wizard<VALTYPE>::VMV(actual_u -> vtype(), actual_M -> mtype(), actual_v -> vtype() ).
	MxV( *actual_u, Iu, *actual_M, IM, JM, *actual_v, Jv, VALTYPE(1), scale, op_M );
    else
      wizard<VALTYPE>::VMV(actual_u -> vtype(), actual_M -> mtype(), actual_v -> vtype() ).
	MxV( *actual_u, *actual_M, *actual_v, VALTYPE(1), scale, op_M );
  }
    
  //------------------------------------------------------------------------------

  template<typename VALTYPE>
  matrix_shape outer_product<VALTYPE>::shape()
  {
    if ( ! this -> shape_defined )
      {
	vector_shape shp1 = ((vector_expression<VALTYPE>*)(this -> left)) -> shape();
	vector_shape shp2 = ((vector_expression<VALTYPE>*)(this -> right)) -> shape();
	//	this -> shp = wizard<VALTYPE>::VV(shp1.vtype, shp2.vtype).VxV_shape(shp1,shp2);
	this -> shp = _lace_storage::VxV_shape(shp1,shp2);
	this -> shape_defined = true;
      }
    return this -> shp;    
  }

  //------------------------------------------------------------------------------

  template<typename VALTYPE>
  void outer_product<VALTYPE>::calculate_expr(matrix_expression<VALTYPE>* &target, VALTYPE scale  )
  {
   matrix_shape res_shape = shape();
    std::cout << "V%V shape: " << _lace_storage::mtype_spelling[res_shape.mtype] 
	      << " " << res_shape.n << " x " << res_shape.m << "\n";

    // Parsing target means to clear out if the left operand has the form of
    // u = or u(I)=, where u is an actual matrix and I is subrange

    // The operation is u += M*v
    vector_expression<VALTYPE> *actual_u, *actual_v;
    matrix_expression<VALTYPE> *actual_M;
    bool u_sub, M_sub, v_sub;
    sub Iu = sub::full, IM = sub::full, JM = sub::full, Jv = sub::full;

    if ( ! parse_lvalue(target, actual_M, M_sub, IM, JM))
      assert(false && "Canonicalization error in V%V::calculate_expr : left operand");
    if ( ! parse_lvalue(this -> left,  actual_u, u_sub, Iu, _actual|_equals))
      assert(false && "Canonicalization error in V%V::calculate_expr : first vector");
    if ( ! parse_lvalue(this -> right, actual_v, v_sub, Jv, _actual|_equals))
      assert(false && "Canonicalization error in V%V::calculate_expr : second vector");

    if ( actual_u -> gettype() & _equals )
      actual_u -> calculate_expr(actual_u);

    if ( actual_v -> gettype() & _equals )
      actual_v -> calculate_expr(actual_v);

    if ( u_sub || M_sub || v_sub )
      wizard<VALTYPE>::VMV(actual_u -> vtype(), actual_M -> mtype(), actual_v -> vtype() ).
	VxV( *actual_M, IM, JM, *actual_u, Iu, *actual_v, Jv, VALTYPE(1), scale );
    else
      wizard<VALTYPE>::VMV(actual_u -> vtype(), actual_M -> mtype(), actual_v -> vtype() ).
	VxV( *actual_M, *actual_u, *actual_v, VALTYPE(1), scale );
  }

  //------------------------------------------------------------------------------

  /*
  template<typename VALTYPE>
  matrix_shape submatrix<VALTYPE>::shape()
  {
    if ( !shape_defined)
      {
	matrix_shape base_shp = mtr -> shape();
	shp = wizard<VALTYPE>::M( base_shp.mtype ).MIJ_shape( base_shp, I->rng(), J->rng() );
	shape_defined = true;
      }
    return shp;
  }
  */
  //------------------------------------------------------------------------------
  /*
  template<typename VALTYPE>
  vector_shape subvector<VALTYPE>::shape()
  {
    if ( !shape_defined)
      {
	vector_shape base_shp = vtr -> shape();
	shp = wizard<VALTYPE>::V( base_shp.vtype ).VI_shape( base_shp, I->rng() );
	shape_defined = true;
      }
    return shp;
  }
  */
  //------------------------------------------------------------------------------

  template<typename VALTYPE>
  void reduce_expr( abstract_expression * xpr )
  {
    /*	 1) reduce expression tree
         2) put temporaries for calculation of repeated subexpressions
	    this is not done for:
	       actual matricies
	       scalings
	       submatricies
	       transpone and hermitian conjugate operations, since they are taken in summas and prods
    */
    xpr -> reduce_tree();
//     std::cout << "\n --- Reduce_expr --- \n";
//     xpr -> print_tree(1);

    abstract_expression::iterator<abstract_expression> x(xpr);
    while( x != NULL )
      {
	// fixme -- think about globop
	int ops = _prod | _inverse | _outer_prod | _mul_vtv | _mul_mv | _plus | _minus;
	ops = ops ^ _basetypes;
	
	if ( (x -> nref > 1) && ( x -> gettype() & ops ))
	  {
	    if ( x -> basetype() == _matrix )
	      {
		matrix_expression<VALTYPE> *tmp = new matrix<VALTYPE,_lace_storage::nonmatrix>;
		xpr -> relink_tree( &(*x), 
		new typename matrix_expression<VALTYPE>::equals( *tmp, *(matrix_expression<VALTYPE>*)&(*x)));
	      }
	    else if ( x -> basetype() == _vector )
	      {
		vector_expression<VALTYPE> *tmp = new vector<VALTYPE,_lace_storage::nonvector>;
		xpr -> relink_tree( &(*x), 
		new typename vector_expression<VALTYPE>::equals( *tmp, *(vector_expression<VALTYPE>*)&(*x)));		
	      }
	  }
	x++;
      }

//     xpr -> print_tree(1);
  }

  // ------------------------------------------------------------------------------------------------

  template<typename VALTYPE>
  //  void matrix_expression<VALTYPE>::canonical_expr( matrix_expression<VALTYPE>* &xpr )
  void canonical_expr( abstract_expression* &xpr )
  {
    // Define literals for creating patterns

    typename matrix_expression<VALTYPE>::literal    a("a"), b("b"), c("c"), d("d");
    typename vector_expression<VALTYPE>::literal    u("u"), v("v"), w("w");
    typename rawvector_expression<VALTYPE>::literal p("p"), q("q"), r("r");
    typename scalar_expression<VALTYPE>::literal    s("s"), s1("s1"), s2("s2");
    typename matrix_expression<VALTYPE>::sliteral   M1("M1"), M2("M2"), M3("M3"), M4("M4");
    typename vector_expression<VALTYPE>::sliteral   V1("V1"), V2("V2"), V3("V3"), V4("V4");
    typename subrange_expression::literal           I("I"),J("J");
    typedef transform<VALTYPE> trnf;

    a.setref();    b.setref();     c.setref();     d.setref();
    u.setref();    v.setref();     w.setref();
    M1.setref();   M2.setref();    M3.setref();    M4.setref();
    V1.setref();   V2.setref();    V3.setref();    V4.setref();
    s.setref();    s1.setref();    s2.setref(); 
    I.setref();    J.setref();

    #define SUMM SUMMA<VALTYPE,matrix_expression<VALTYPE> >
    #define SUMV SUMMA<VALTYPE,vector_expression<VALTYPE> >

    if (lace::globals::debug)
      std::cout << "\nCanonicalization:\n";

    /* "Hang" the expression tree on special node of type "_link".
     * It does nothing. This is necessary only to be able to relink_tree
     * from the top level node
     */

    if ( xpr -> gettype() & _matrix )
      xpr = new typename matrix_expression<VALTYPE>::unop(*((matrix_expression<VALTYPE>*)xpr),_link);
    else if ( xpr -> gettype() & _vector )
      xpr = new typename vector_expression<VALTYPE>::unop(*((vector_expression<VALTYPE>*)xpr),_link);      

    // replace all '-' signs with '+(-1)*'

    trnf( a - b, a + VALTYPE(-1)*b ) . replace_all(xpr);
    trnf( u - v, u + VALTYPE(-1)*v ) . replace_all(xpr);

    /* replace a = b with a = SUMM(b) everywhere
     */
    
//     trnf( * new typename matrix_expression<VALTYPE>::binop( a, b, _equals), 
// 	  * new typename matrix_expression<VALTYPE>::binop ( a, SUMM(b), _equals) ) . replace_all(xpr);
//    std::cout << typeid(SUMM(b)).name() << "n";

    //fixme -- why a=b produces error?
    //trnf(* new typename matrix_expression<VALTYPE>::binop( a, b, _equals), a = SUMM(b) ) . replace_all(xpr);
    
    bool finished = false;
    while (!finished)
      {
	b.setmask( (~_summa) ^ _basetypes );
	trnf( a = b, a = SUMM(b) ) . replace_all(xpr);
	//	trnf( * new typename matrix_expression<VALTYPE>::equals(a,b),
	//      * new typename matrix_expression<VALTYPE>::equals(a,SUMM(b))) . replace_all(xpr);
	b.setmask( ~0x0 );
	
	v.setmask( (~_summa) ^ _basetypes );
	//    trnf( u = v, u = SUMV(v) ) . replace_all(xpr);
	trnf( * new typename vector_expression<VALTYPE>::equals(u,v),
	      * new typename vector_expression<VALTYPE>::equals(u,SUMV(v))) . replace_all(xpr);
	v.setmask(~0x0);
	
	d.setmask( (~_scaling) ^ _basetypes );
	w.setmask( (~_scaling) ^ _basetypes );
	
	while (  trnf( SUMM( M1, a + b, M2 )          , SUMM( M1, a, b, M2)             ) . replace_once(xpr) ||
		 trnf( SUMM( M1, s*(a + b), M2 )      , SUMM( M1, s*a, s*b, M2)         ) . replace_once(xpr) ||
		 trnf( SUMM( M1, s*(a + b).T(), M2 )  , SUMM( M1, s*a.T(), s*b.T(), M2) ) . replace_once(xpr) ||
		 trnf( SUMM( M1, s*(a + b).H(), M2 )  , SUMM( M1, s*a.H(), s*b.H(), M2) ) . replace_once(xpr) ||
		 trnf( SUMM( M1, s*(a + b)(I,J), M2 ) , SUMM( M1, s*a(I,J),s*b(I,J),M2) ) . replace_once(xpr) ||
		 trnf( SUMM( M1, (s*a)(I,J), M2 )     , SUMM( M1, s*a(I,J),M2)          ) . replace_once(xpr) ||
		 trnf( SUMV( V1, u + v, V2 )          , SUMV( V1, u, v, V2)             ) . replace_once(xpr) ||
		 trnf( SUMV( V1, s*(u + v), V2 )      , SUMV( V1, s*u, s*v, V2)         ) . replace_once(xpr) ||
		 trnf( s1*(s2*a)                      , (s1*s2)*a                       ) . replace_once(xpr) ||
		 trnf( s1*(s2*v)                      , (s1*s2)*v                       ) . replace_once(xpr) ||
		 trnf( (s*a).T()                      , s*a.T()                         ) . replace_once(xpr) ||
		 trnf( (a.T()).T()                    , VALTYPE(1)*a                    ) . replace_once(xpr) ||
		 trnf( (a.T())(I,J)                   , a(J,I).T()                      ) . replace_once(xpr) ||
		 trnf( (s*a).H()                      , conj(s)*a.H()                   ) . replace_once(xpr) ||
		 trnf( (a.H()).H()                    , VALTYPE(1)*a                    ) . replace_once(xpr) ||
		 trnf( (a.H())(I,J)                   , a(J,I).H()                      ) . replace_once(xpr) ||
		 trnf( (s*a)(I,J)                     , s*a(I,J)                        ) . replace_once(xpr) ||
		 trnf( SUMM( M1, s1*a, M2, s2*a, M3 ) , SUMM( M1, (s1+s2)*a,  M2, M3 )  ) . replace_once(xpr) ||
		 trnf( SUMM( M1, s*( (s1*a) * b ), M2), SUMM( M1,(s*s1)*(a*b), M2)      ) . replace_once(xpr) ||
		 trnf( SUMM( M1, s*(  a * (s1*b)), M2), SUMM( M1,(s*s1)*(a*b), M2)      ) . replace_once(xpr) ||
		 trnf( (a*b).T()                      , (b.T()*b.T())                   ) . replace_once(xpr) ||
		 trnf( (a*b).H()                      , (b.T()*b.H())                   ) . replace_once(xpr) ||
		 trnf( (a + b).T()                    , (a.T() + b.T())                 ) . replace_once(xpr) ||
		 trnf( (a + b).H()                    , (a.H() + b.H())                 ) . replace_once(xpr) ||
		 trnf( (a + b)(I,J)                   , (a(I,J) + b(I,J))               ) . replace_once(xpr) ||
		 trnf( (a*b)*v                        , a*(b*v)                         ) . replace_once(xpr) ||
		 trnf( SUMM( M1, d, M2)               , SUMM( M1, VALTYPE(1e0)*d, M2)   ) . replace_all(xpr)  ||
		 trnf( SUMV( V1, w, V2)               , SUMV( V1, VALTYPE(1e0)*w, V2)   ) . replace_all(xpr) )
	  {   
	    if (lace::globals::debug)
	      xpr->print_tree(); std::cout << "\n\n";
	  }

	finished = true;


	if (true)
	  {
	    // find all a*b products, where a or b is not simple term
	    
	    abstract_expression::iterator<abstract_expression> ixpr(xpr);
	    
	    while ( ixpr != NULL  )
	      {
		// 	    std::cout << "search: ";
		// 	    ixpr -> print_tree();
		// 	    std::cout << "\n";
		if ( trnf(a*b).match(&(*ixpr),trnf::ubnd_bfr) )
		  {
		    if ( ! is_simple((matrix_expression<VALTYPE>*)a.bound()) )
		      {
			finished = false;	      
			insert_tmp(xpr,(matrix_expression<VALTYPE>*)a.bound());
		      }
		    if ( ! is_simple((matrix_expression<VALTYPE>*)b.bound()) )
		      {
			finished = false;
			insert_tmp(xpr,(matrix_expression<VALTYPE>*)b.bound());
		      }
		  }
		if ( trnf(a*u).match(&(*ixpr),trnf::ubnd_bfr) )
		  {
		    if ( ! is_simple((matrix_expression<VALTYPE>*)a.bound()) )
		      {
			finished = false;	      
			insert_tmp(xpr,(matrix_expression<VALTYPE>*)a.bound());
		      }
		    if ( ! is_simple((vector_expression<VALTYPE>*)u.bound()) )
		      {
			finished = false;
			insert_tmp(xpr,(vector_expression<VALTYPE>*)u.bound());
		      }
		  }
		if ( trnf(u%v).match(&(*ixpr),trnf::ubnd_bfr) )
		  {
		    if ( ! is_simple((vector_expression<VALTYPE>*)u.bound()) )
		      {
			finished = false;	      
			insert_tmp(xpr,(vector_expression<VALTYPE>*)u.bound());
		      }
		    if ( ! is_simple((vector_expression<VALTYPE>*)v.bound()) )
		      {
			finished = false;
			insert_tmp(xpr,(vector_expression<VALTYPE>*)v.bound());
		      }
		  }
		ixpr++;
	      } 
	    if (lace::globals::debug)
	      {
		std::cout << "Inserting temporaries : \n";
		xpr->print_tree(1); std::cout << "\n\n";
	      }
	    
	  }
      }

    // Evaluate all scalars
    {
      std::cout << " ------------- Scalars evaluation --------------------\n";
      s.setmask( ~_actual );
      trnf scal( s*a );
      abstract_expression *scaling = NULL;
      while( scaling = scal.search(xpr,scaling) )
	xpr -> relink_tree( scaling -> xnext(0), 
		       new scalar_number<VALTYPE>( ((scalar_expression<VALTYPE>*)(scaling -> next(0)))->value() ));
    }
    if (lace::globals::debug)
      {
	std::cout << " ------------- Canonicalization finished --------------------\n";
	xpr->print_tree(); 
	std::cout << "\n\n";
      }

    #undef SUMM
    #undef SUMV

    abstract_expression *x = xpr;
    xpr = (matrix_expression<VALTYPE>*)( xpr -> xnext(0) );
    x -> free();
  }
 
  //------------------------------------------------------------------------------

  template<typename VALTYPE, class XPR>
  void process_expr(XPR * &target, XPR *xpr)
  /*  target is an object where the calculation result should be placed
      target can possibly be:
             1) actual matrix
             2) submatrix of actual matrix
             3) protomatrix that will be replaced with actual matrix during calculation
  */
  {

//     std::cout << "process_expr:: entering; root=\n";
//     xpr -> print_tree(0);

    // Create equality for the convenience of transformations, if we are not already in equality
    XPR *equ;
    bool equ_created = false;
    if (   xpr -> gettype() & _equals  )
      equ = xpr;
    else
      {
	equ = new typename XPR::equals( *target, *xpr);
// 			     SUMMA<VALTYPE,matrix_expression<VALTYPE> >(*xpr), _equals);
	equ_created = true;
      }
    reduce_expr<VALTYPE>(equ);

    // Canonicalize the top nodes
    abstract_expression *xequ = equ;
    canonical_expr<VALTYPE>(xequ);
    equ = (XPR*)xequ;

    // Perform calculation
    ((XPR*)(equ -> xnext(1))) -> calculate_expr(target,true);

    if (lace::globals::debug)
      {
	std::cout << "\nprocess_expression: calculate_expr finished\n";
	equ -> print_tree(1);
      }

    // Delete the expression
    equ -> unlink_tree(0);
    equ -> unlink_tree(1);
    if (equ_created)
      equ -> free();

  }

  // ------------------------------------------------------------------------------------------------

  template<typename VALTYPE>
  void matrix_expression<VALTYPE>::calculate_expr(matrix_expression<VALTYPE>* &target, VALTYPE scale  )
  {
    assert(false && "This should never happen -- abstract matrix expression calculate_expr called\n");
  }


  template<typename VALTYPE>
  void vector_expression<VALTYPE>::calculate_expr(vector_expression<VALTYPE>* &target, VALTYPE scale  )
  {
    assert(false && "This should never happen -- abstract vector expression calculate_expr called\n");
  }

};
    
#endif
