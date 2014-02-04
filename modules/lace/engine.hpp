#ifndef _LACE_ENGINE_H
#define _LACE_ENGINE_H

#include <lace/globals.hpp>
#include <lace/wizard_instance.hpp>
#include <lace/calcul.hpp>

namespace _lace_expressions{

  using _lace_main::wizard;
  using _lace_storage::matrix_shape;
  using _lace_storage::empty_shape;
  using _lace_storage::is_empty;

  // ------------------------------------------------------------------------------------------------
  //                        Temporary dummy

  template <typename VALTYPE, class XPR>
  void equality_expression<VALTYPE,XPR>::calculate_expr(XPR* &target, VALTYPE scale )
  {}

  template <typename VALTYPE, class XPR>
  typename shape_type<XPR>::type equality_expression<VALTYPE,XPR>::shape()
  {}

  template<typename VALTYPE>
  void  matrix_expression<VALTYPE>::calculate_expr(matrix_expression<VALTYPE>* &target, VALTYPE scale)
  {}

  template<typename VALTYPE>
  void  vector_expression<VALTYPE>::calculate_expr(vector_expression<VALTYPE>* &target, VALTYPE scale)
  {}

  template<typename VALTYPE>
  void outer_product<VALTYPE>::calculate_expr(matrix_expression<VALTYPE>* &target, VALTYPE scale)
  {}
  
  template<typename VALTYPE>
  matrix_shape outer_product<VALTYPE>::shape()
  {}

  template<typename VALTYPE>
  matrix_shape transpmatrix_expression<VALTYPE>::shape()
  {}

  template<typename VALTYPE> 
  void matrix_by_vector<VALTYPE>::calculate_expr(vector_expression<VALTYPE>* &target, VALTYPE scale  )
  {}

  template<typename VALTYPE> 
  vector_shape matrix_by_vector<VALTYPE>::shape()
  {}

  template<typename VALTYPE>
  void mulmm_expression<VALTYPE>::calculate_expr(XPR* &target, VALTYPE scale)
  {}  
 
  template<typename VALTYPE>
  matrix_shape mulmm_expression<VALTYPE>::shape()
  {}

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

  template<typename VALTYPE>
  bool parse_lvalue( matrix_expression<VALTYPE> *trg, matrix_expression<VALTYPE>* &mtr, bool &submtr, sub &I, sub &J, int mask = _actual)
  {
    I = J = sub::full;
    submtr = false;
    mtr = trg;

    if ( (trg -> gettype() & (_submtr ^ _matrix) ) )
      {
	submtr = true;
	I = ((subrange_expression*)(trg -> next(0))) -> rng();
	J = ((subrange_expression*)(trg -> next(1))) -> rng();
	mtr = (matrix_expression<VALTYPE>*)(trg -> next(2)); 
      }

    if (mtr -> gettype() & mask)
      {
	matrix_shape shp = mtr -> shape(); 
	I.reduce(0, shp.n );
	J.reduce(0, shp.m );
	return true;
      }
    else
      return false;
  }

  //----------------------

  template<typename VALTYPE>
  bool parse_lvalue( vector_expression<VALTYPE> *xpr, vector_expression<VALTYPE>* &trg, 
		     bool &subvtr, sub &I, int mask = _actual)
  {
    typedef transform<VALTYPE> trnf;   
    typename vector_expression<VALTYPE>::literal u("u");
    typename subrange_expression::literal II("I");
    u.setref(); u.setmask(mask);
    II.setref();

    if ( trnf(u).match(xpr,trnf::ubnd_bfr) )
      {
	trg = (vector_expression<VALTYPE>*)u.bound();
	subvtr = false;
	return true;
      }
    else if ( trnf(u(II)).match(xpr,trnf::ubnd_bfr) )
      {
	trg = (vector_expression<VALTYPE>*)u.bound();
	I = ((subrange_expression*)II.bound()) -> rng();
	subvtr = true;
	return true;	
      }
    else 
      return false;
  }

  //----------------------

  template<typename VALTYPE>
  bool parse_term( matrix_expression<VALTYPE> *term, matrix_expression<VALTYPE>* &mtr, 
		   bool &submtr, sub &I, sub &J, int &OP, int mask = _actual)
  {
    bool res = true;

//     std::cout << "Parse term:\n";
//     term -> print_tree(1);

    OP = 0;
    if ( term -> gettype() & _transp )
      {
	OP = _transp;
	term = (matrix_expression<VALTYPE>*)(term -> xnext(0));
      }
    else if ( term -> gettype() & _herm )
      {
	OP = _herm;
	term = (matrix_expression<VALTYPE>*)(term -> xnext(0));
      }

    return parse_lvalue(term,mtr,submtr,I,J,mask);

  }

  //----------------------
  
  template<typename VALTYPE>
  bool is_simple(matrix_expression<VALTYPE> *xpr)
  {
    matrix_expression<VALTYPE> *mtr;
    bool submtr;
    sub I,J;
    int op;
    return parse_term(xpr, mtr, submtr, I, J, op, _actual|_equals);
  }

  //----------------------
  
  template<typename VALTYPE>
  bool is_simple(vector_expression<VALTYPE> *xpr)
  {
    vector_expression<VALTYPE> *vtr;
    bool subvtr;
    sub I;
    return parse_lvalue(xpr, vtr, subvtr, I, _actual|_equals);
  }

  //------------------------------------------------------------------------------
  
  template<typename VALTYPE>
  void insert_tmp( abstract_expression * xpr,  matrix_expression<VALTYPE> *where )
  {
    xpr -> relink_tree( where, 
			new typename matrix_expression<VALTYPE>::equals( 
			    * new matrix<VALTYPE,_lace_storage::nonmatrix>, * where) );
  }

  //------------------------------------------------------------------------------

  template<typename VALTYPE>
  void insert_tmp( abstract_expression * xpr, vector_expression<VALTYPE> *where )
  {
    xpr -> relink_tree( where, 
			new typename vector_expression<VALTYPE>::equals( 
			    * new vector<VALTYPE,_lace_storage::nonvector>, * where) );
  }

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

    // Create equality for the convenience of transformations, if we are not already in equality
    XPR *equ;
    bool equ_created = false;
    if (   xpr -> gettype() & _equals  )
      equ = xpr;
    else
      {
	equ = new typename XPR::equals( *target, *xpr);
	equ_created = true;
      }
    reduce_expr<VALTYPE>(equ);

    // Canonicalize the top nodes
    abstract_expression *xequ = equ;
    canonical_expr<VALTYPE>(xequ);
    equ = (XPR*)xequ;

    // Perform calculation
    //    ((XPR*)(equ -> xnext(1))) -> calculate_expr(target,true);

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

};

#endif
