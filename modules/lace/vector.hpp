#ifndef _LACE_VECTOR_H
#define _LACE_VECTOR_H


#include <boost/format.hpp>

#include <lace/storage.hpp>
#include <lace/matrix_expressions.hpp>
#include <lace/vector_expressions.hpp>

namespace _lace_expressions{

  using _lace_storage::vector_storage;
  using _lace_storage::vector_shape;
  using _lace_storage::vector_type;
  //  using _lace_storage::empty_shape;

  template<typename VALTYPE, vector_type VTYPE = _lace_storage::dense>
  class vector : public vector_expression<VALTYPE>
  {

    /*
    friend class _lace_main::m_unary_engine<VALTYPE>;
    friend class _lace_main::v_unary_engine<VALTYPE>;
    friend class _lace_main::m_convertor_engine<VALTYPE>;
    friend class _lace_main::v_convertor_engine<VALTYPE>;
    friend class _lace_main::mm_binary_engine<VALTYPE>;
    friend class _lace_main::vv_binary_engine<VALTYPE>;
    friend class _lace_main::vm_binary_engine<VALTYPE>;
    friend class _lace_main::mmm_ternary_engine<VALTYPE>;
    friend class _lace_main::vmv_ternary_engine<VALTYPE>;

    friend class _lace_main::v_unary<VALTYPE,VTYPE>;
    */
  public:
    vector_storage<VALTYPE,VTYPE> *_vtr;
  private:

    typedef  vector<VALTYPE,VTYPE> SELF;

    void _print_me_vector(int shift = 0)
    {
      if (shift==0)
	std::cout << " VCTR " << ((SELF*)this) -> getUID() << " ";
      else
	{	  
	  indent(shift);
	  std::cout << _lace_storage::vtype_spelling[VTYPE] << " vector " 
		    <<  " x " << _vtr->size() << " : UID = " << ((SELF*)this) -> getUID() 
		    << " nref = " << ((SELF*)this) -> nref  << " nbound = " << ((SELF*)this) -> nbound<< "\n";
	}
    }

    void _print_me_proto(int shift = 0)
    {
      if (shift==0)
	std::cout << "VTMP" << ((SELF*)this) -> getUID();
      else
	{
	  indent(shift);
	  std::cout << "Protovector with UID = " << ((SELF*)this) -> getUID() 
		    << " nref = " << ((SELF*)this) -> nref << "\n";
	}
    }

  public:
    vector()
    {
      _vtr = NULL;
      ((SELF*)this) -> setref();
    }

    vector(int n)
    {
      _vtr = new vector_storage<VALTYPE,VTYPE>( vector_shape(VTYPE,n) );
      ((SELF*)this) -> setref();
    }

    vector(vector_shape shp)
    {
      _vtr = new vector_storage<VALTYPE,VTYPE>( shp );
      ((SELF*)this) -> setref();
    }

    //----------------------  Assignment ------------------------
    
    vector<VALTYPE,VTYPE>& operator=(vector_expression<VALTYPE> &xpr)
    {
      vector_expression<VALTYPE> *trg = this;
      /*temp
      process_expr<VALTYPE,vector_expression<VALTYPE> >(trg, &xpr);
      */
      return *this;
    }

    vector<VALTYPE,VTYPE>& operator=(vector<VALTYPE,VTYPE> &x)
    {
      if (is_empty())
	reshape(x.shape());
      else
	assert( shape() == x.shape() && "Shape doesn not conform in vector assignment");
      copy(x);
      return *this;
    }

    //------------------ Access operator ------------------------

    inline VALTYPE *ptr(int i)
    {
      return _vtr->ptr(i);      
    }

    inline VALTYPE& operator()(int i)
    {
      return (*_vtr)(i);
    }

    //    virtual vector_expression<VALTYPE>& operator()(sub I)
    virtual subvector<VALTYPE>& operator()(sub I)
    {
      return * new subvector<VALTYPE>( * new subrange_expression(I), *this);
    }

    //-------------------- Size and shape functions ---------------

    virtual bool is_empty(){ return _vtr == NULL; }    

    inline int size()
    {
      if ( _vtr != NULL)
	return _vtr -> size();
      else 
	return 0;
    }

    void empty()
    {
      if ( !is_empty() )
	_vtr->nref--;
      _vtr = NULL;
    }

    void resize(int n)
    {
      empty();
      _vtr = new vector_storage<VALTYPE,VTYPE>( vector_shape(VTYPE,n) );
    }

    virtual void reshape( vector_shape shp )
    {
      empty();
       _vtr = new vector_storage<VALTYPE,VTYPE>( shp );
    }

    inline bool defined(int i)
    {
      return _vtr -> defined(i);
    }
  
    inline bool unique(int i)
    {
      return _vtr -> unique(i);
    }  

    //------------------- Copy and scale functions ----------

    inline void setval(VALTYPE s)
    {
      _vtr -> setval(s);
    }

    inline void scale(VALTYPE s)
    {
      _vtr->scale(s);
    }

    inline void copy(vector<VALTYPE,VTYPE> &s)
    {     
      assert( _vtr->shape() == s._vtr->shape() && "Shape does not conform in vector copy!");
      _vtr->copy( *(s._vtr) );
    }

    vector<VALTYPE,VTYPE> & operator=(VALTYPE s)
    {
      _vtr -> setval(s);
      return *this;
    }

    vector<VALTYPE,VTYPE> & operator*=(VALTYPE s)
    {
      _vtr->scale(s);
    }

    //-------------------- Service functions -------------------
    
    virtual bool is_same(vector_expression<VALTYPE> &a)
    {
      if ( a.gettype() == gettype() && a.type() == VTYPE )
	{
	  return ((vector<VALTYPE,VTYPE>*)(&a)) -> _vtr == _vtr;
	}
      else
	return false;
    }  

    virtual bool equiv(_lace_tree::tree_node *tree)
    {      
      if ( tree -> gettype() & _lace_expressions::_vector)
	return is_same( *((vector_expression<VALTYPE>*)tree) );
    };
    
    virtual int gettype()
    {
      if (VTYPE == _lace_storage::nonvector)
	return _proto + _vector;
      else 
	return _actual + _vector;
    }

    virtual vector_shape shape()
    {
      //      std::cout << "Actual shape requested\n";
      if ( ! is_empty() )
	return _vtr->shape();
      else
	return vector_shape();
    }

    // fixme :: implement this!!!
    virtual abstract_expression* copy(int mask = 0){};

    // ----------------- Debug  printing --------------------

    virtual void debug(int lvl)
    {
      indent(lvl);
      if (_vtr != NULL )
	std::cout << _lace_storage::vtype_spelling[VTYPE] << " vector " 
		  <<  " x " << _vtr->size() << " UID " <<((SELF*)this) -> getUID() << " with nref " << ((SELF*)this) -> nref << "\n";
      else
	std::cout << _lace_storage::vtype_spelling[VTYPE] << " empty vector\n";
    }

    virtual void print_me(int shift = 0)
    {
      if (VTYPE == _lace_storage::nonvector)
	_print_me_proto(shift);
      else
	_print_me_vector(shift);	
    }

    virtual void print_tree(int shift = 0){ print_me(shift);}


    // --------------------- Destructor -------------------------

//     ~vector()
//     {
//       // Just debug
//       std::cout << "I am dying!!!  \n";
//       debug(0);
//       empty();
//     }

    virtual void free(){ delete (SELF*)this;}

  };

};

#endif
