#ifndef _LACE_MATRIX_H
#define _LACE_MATRIX_H

#include <iostream>
#include <vector>
#include <string>

#include <boost/format.hpp>

#include <lace/storage.hpp>
#include <lace/matrix_expressions.hpp>
#include <lace/vector_expressions.hpp>
#include <lace/element.hpp>
#include <lace/globals.hpp>

namespace _lace_expressions{

//   using _lace_expressions::abstract_expression;
//   using _lace_expressions::matrix_expression;
//   using _lace_expressions::vector_expression;
//   using _lace_expressions::rawvector_expression;
//   using _lace_expressions::scalar_expression;
//   using _lace_expressions::sub;
//   using _lace_expressions::subrange_expression;
//   using _lace_expressions::submatrix;
  using _lace_storage::matrix_storage;
  using _lace_storage::matrix_shape;
  using _lace_storage::matrix_type;
//   using _lace_basic::matrix_shape_banded;
//   using _lace_basic::matrix_shape_triang;
  using _lace_storage::empty_shape;
  using _lace_storage::_element;

  // Just for debug
//   using _lace_expressions::indent;
  
  template <typename VALTYPE, matrix_type MTRTYPE = _lace_storage::rectang>
  class matrix : public matrix_expression<VALTYPE>
  {

  public:
    matrix_storage<VALTYPE,MTRTYPE> *_mtr;
  private:
    typedef matrix<VALTYPE,MTRTYPE> SELF;

    void _print_me_matrix(int shift = 0)
    {
      if (shift==0)
	std::cout << " MTRX " << ((SELF*)this) -> getUID() << " ";
      else
	{	  
	  indent(shift);
	  std::cout << _lace_storage::mtype_spelling[MTRTYPE] << " matrix " 
		    << _mtr->size(0) << " x " << _mtr->size(1) << " : UID = " << ((SELF*)this) -> getUID() 
		    << " nref = " << ((SELF*)this) -> nref  << " nbound = " << ((SELF*)this) -> nbound<< "\n";
	}
    }

    void _print_me_proto(int shift = 0)
    {
      if (shift==0)
	std::cout << "TMP" << ((SELF*)this) -> getUID();
      else
	{
	  indent(shift);
	  std::cout << "Protomatrix with UID = " << ((SELF*)this) -> getUID() 
		    << " nref = " << ((SELF*)this) -> nref << "\n";
	}
    }

  public:

    //----------------------- Constructors ----------------------

    matrix() 
    { 
      _mtr = NULL; ((SELF*)this) -> setref();
    }

    matrix(int n, int m=-1)
    {
      _mtr = new matrix_storage<VALTYPE,MTRTYPE>( matrix_shape(MTRTYPE,n,m) ); ((SELF*)this) -> setref();
    }

    matrix(int n, int m, int k, int l=-1)
    {
      _mtr = new matrix_storage<VALTYPE,MTRTYPE>( matrix_shape(MTRTYPE,n,m,k,l) ); ((SELF*)this) -> setref();
    }

    matrix(int n, matrix_shape::uplo tag)
    {
      _mtr = new matrix_storage<VALTYPE,MTRTYPE>( matrix_shape(MTRTYPE,n,tag) ); ((SELF*)this) -> setref();
    }

    matrix( matrix_shape shp ){
      _mtr = new matrix_storage<VALTYPE,MTRTYPE>( shp); ((SELF*)this) -> setref();
    }

    matrix(matrix<VALTYPE,MTRTYPE> &A )
    {
      ((SELF*)this) -> setref();
      if (!A.is_empty())
	{
	  _mtr = new matrix_storage<VALTYPE,MTRTYPE>( A.shape() );
	  copy(A);      
	}
      else
	_mtr = NULL; 	
    }

//     matrix(VALTYPE *a[], int n, int m=-1)
//     {
//       _mtr = new matrix_storage<VALTYPE,MTRTYPE>( matrix_shape(MTRTYPE,n,m) ); ((SELF*)this) -> setref();
//       for (int i=0; i<n; i++)
// 	for (int j=0; j<m; j++)
// 	  if (_mtr -> unique(i,j))
// 	    (*_mtr)(i,j) = a[i][j];
//     }

    //----------------- Typecast constructor --------------------

    //    matrix( matrix_expression<VALTYPE> &xpr );

    //----------------------  Assignment ------------------------

    virtual matrix<VALTYPE,MTRTYPE>& operator=(matrix_expression<VALTYPE> &xpr)
    {      
      matrix_expression<VALTYPE> *trg = this;
      process_expr<VALTYPE,matrix_expression<VALTYPE> >(trg, &xpr);
      return *this;
    }

    matrix<VALTYPE,MTRTYPE>& operator=(matrix<VALTYPE,MTRTYPE> &M)
    {      
      matrix_expression<VALTYPE> *trg = this;
      if (is_empty() || lace::globals::auto_reshape )
	reshape(M.shape());
      else
	assert( shape() == M.shape() && "Shape does not conform in matrix assignment");
      copy(M);
      return *((matrix<VALTYPE,MTRTYPE>*)trg);
    }

//     matrix(matrix_expression<VALTYPE> &xpr)
//     {
      
//     }

    //------------------ Access operator ------------------------

    inline VALTYPE *ptr(int i, int j)
    {
      return _mtr->ptr(i,j);
    }

    inline typename _element<VALTYPE,MTRTYPE>::type  operator()(int i, int j)
    { return (*_mtr)(i,j);}

    virtual matrix_expression<VALTYPE> & operator()(sub I, sub J)
    {
      return * new submatrix<VALTYPE>( * new subrange_expression(I), * new subrange_expression(J), *this);
    }

    //Ugly and nasty way to do this 
    // fixme - this is temporary
    vector_expression<VALTYPE> & operator()(sub I, int j)
    {
      I.reduce(0,size(0));
      vector<VALTYPE,_lace_storage::dense> *v = new vector<VALTYPE,_lace_storage::dense>(I.size());
      for(int i=0; i < v->size(); i++)
	(*v)(i) = (*this)(I.idx(i),j);
      return *v;
    }

    //Ugly and nasty way to do this 
    // fixme - this is temporary
    VALTYPE trace()
    {
      VALTYPE s = VALTYPE(0);
      for (int i=0; i < size(0) && i < size(1); i++)
	s += (*this)(i,i);
      return s;
    }

   //--------------- Size and shape manipulation ---------------

    virtual bool is_empty(){ return _mtr == NULL; }

    inline int size(int dim) 
    {
      if ( !is_empty() ) return _mtr->size(dim);
      else return 0;
    }

    void empty()
    {
      if ( !is_empty() )
	_mtr->nref--;
      _mtr = NULL;
    }

    void resize(int n, int m=-1)
    {
      if (m==-1) m=n;
      empty();
      _mtr = new matrix_storage<VALTYPE,MTRTYPE>( matrix_shape(MTRTYPE,n,m) );
    }

    void resize(int n, int m, int k, int l=-1)
    { 
      empty();
      _mtr = new matrix_storage<VALTYPE,MTRTYPE>( matrix_shape(MTRTYPE,n,m,k,l) );
    }

    void resize(int n, int m, matrix_shape::uplo tag)
    {
      empty();
      _mtr = new matrix_storage<VALTYPE,MTRTYPE>( matrix_shape(MTRTYPE,n,m,tag) );
    }

    virtual void reshape( matrix_shape shp )
    {
      empty();
       _mtr = new matrix_storage<VALTYPE,MTRTYPE>( shp );
    }

    inline bool defined(int i, int j)
    {
      return _mtr -> defined(i,j);
    }
  
    inline bool unique(int i, int j)
    {
      return _mtr -> unique(i,j);
    }  

    void reference(matrix<VALTYPE,MTRTYPE> &s)
    {
      empty();
      _mtr = s._mtr;
      _mtr -> nref++;
    }

//     virtual matrix_shape shape()
//     {
//       return _mtr -> shape();
//     }

    //------------------ Copy and scale functions ----------------

    inline void copy( matrix<VALTYPE,MTRTYPE> &s)
    {     
      assert( _mtr->shape() == s._mtr->shape() && "Shape does not conform in matrix copy!");
      _mtr->copy( *(s._mtr) );
    }

    inline void scale(VALTYPE s)
    {
      _mtr->scale(s);
    }

    matrix<VALTYPE,MTRTYPE>& operator=(VALTYPE s)
    {
      _mtr->setval(s);
      return *this;
    }

    //---------------- Service function -- not for users -----------------

    virtual bool is_same(matrix_expression<VALTYPE> &a)
    {
      if ( a.gettype() == gettype() && a.type() == MTRTYPE )
	{
	  return ((matrix<VALTYPE,MTRTYPE>*)(&a)) -> _mtr == _mtr;
	}
      else
	return false;
    }  

    virtual bool equiv(_lace_tree::tree_node *tree)
    {      
      if ( tree -> gettype() & _lace_expressions::_matrix)
	return is_same( *((matrix_expression<VALTYPE>*)tree) );
    };
    
    //  inline VALTYPE* pointer(){ return _mtr.pointer(); }

    //    virtual matrix_object<VALTYPE>* compress(){return this;}

//     virtual bool is_matrix()
//     {return true;}

    virtual matrix_type mtype(){return MTRTYPE;}

    virtual matrix_shape shape()
    {
      //      std::cout << "Actual shape requested\n";
      if ( ! is_empty() )
	return _mtr->shape();
      else
	return empty_shape();
    }


    virtual int gettype()
    {
      if (MTRTYPE == _lace_storage::nonmatrix)	
	return _lace_expressions::_matrix + _lace_expressions::_proto;
      else
	return _lace_expressions::_matrix + _lace_expressions::_actual;
    }

    // fixme :: implement this!!!
    virtual abstract_expression* copy(int mask = 0){};
    
    // --- debug printing ---

    virtual void debug(int lvl)
    {
      indent(lvl);
      if (_mtr != NULL )
	std::cout << _lace_storage::mtype_spelling[MTRTYPE] << " matrix " 
		  << _mtr->size(0) << " x " << _mtr->size(1) << " UID " <<((SELF*)this) -> getUID() << " with nref " << ((SELF*)this) -> nref << "\n";
      else
	std::cout << _lace_storage::mtype_spelling[MTRTYPE] << " empty matrix\n";
    }

    virtual void print_me(int shift = 0)
    {
      if (MTRTYPE == _lace_storage::nonmatrix)
	_print_me_proto(shift);
      else
	_print_me_matrix(shift);	
    }


    virtual void print_tree(int shift = 0){ print_me(shift);}

    //------------------------ Destructor -----------------------

    ~matrix()
    {
      // Just debug
      if (lace::globals::debug)
	{
	  std::cout << "I am dying!!!  \n";
	  debug(0);
	}
      empty();
    }

    virtual void free(){delete (SELF*)this;}

    //debug
    void print_data()
    {
      for (int i=0; i<size(0); i++)
	{
	  for (int j=0; j<size(1); j++)
	    std::cout << (*this)(i,j) << " ";
	  std::cout << "\n";
	}
    }

  };


};

#endif
