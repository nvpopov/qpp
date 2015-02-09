#ifndef _QPPDATA_H
#define _QPPDATA_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

namespace qpp{

#ifdef WCHAR

#define CHAR wchar
#define STRING std::wstring

#else

#define CHAR char
#define STRING std::string

#endif

#undef assert

  typedef std::char_traits<CHAR> TRAITS;

  typedef std::basic_ostream<CHAR,TRAITS> OSTREAM;

  typedef std::basic_istream<CHAR,TRAITS> ISTREAM;

  typedef std::basic_stringstream<CHAR,TRAITS> SSTREAM;

  enum{
    qtype_parameter     = 0x00002000,
    qtype_body          = 0x00004000,
    qtype_declaration   = 0x00008000,
    qtype_geometry      = 0x00010000,
    qtype_xgeometry     = 0x00020000,
    qtype_vectors       = 0x00040000,
    qtype_basis         = 0x00080000,
    qtype_manyfold      = 0x00100000,
    qtype_zmatrix       = 0x00200000,
    qtype_zpattern      = 0x00400000,
    qtype_zpt_bond      = 0x00800000,
    qtype_zpt_angle     = 0x01000000,
    qtype_zpt_dihedral  = 0x02000000,
    qtype_zpt_surfangle = 0x04000000,
    qtype_zpt_lindep    = 0x08000000,
    qtype_geom_builder  = 0x10000000,
    qtype_region        = 0x20000000,
    qtype_atom          = 0x40000000,
    qtype_molecule      = 0x80000000,
    qtype_shape         = 0x100000000,

    // additional bits for some of these types
    qtype_dim0         = 0x0001,
    qtype_dim1         = 0x0002,
    qtype_dim2         = 0x0004,
    qtype_dim3         = 0x0008,
    qtype_data_int     = 0x0010,
    qtype_data_bool    = 0x0020,
    qtype_data_double  = 0x0040,
    qtype_data_float   = 0x0080,
    qtype_data_string  = 0x0100,
    qtype_basis_pw     = 0x0200,
    qtype_basis_gauss  = 0x0400,
    qtype_basis_slater = 0x0800,
    qtype_basis_siesta = 0x1000
  };

  enum qscope {
    qscope_local  = 0x01, 
    qscope_global = 0x02, 
    qscope_above  = 0x04,
    qscope_below  = 0x08,
    qscope_all    = 0x10
  };

  typedef long int qppobject_type;

  /*FIXME: Using structs in c++ */
  template<class T>
  struct qtype_data
  {
    static const qppobject_type type;
  };

  // --------------------------------------------------------------------------------------


  
  // -------------------------------------------------------------------------------------

  class qpp_exception;

  // -------------------------------------------------------
  class qpp_object{
  protected:

    STRING _name, _error;

    qpp_object* _owner;

  public:

    virtual STRING category() const=0;

    virtual qppobject_type gettype() const=0;

    virtual int n_nested() const =0;

    virtual qpp_object* nested(int i) const =0;

    virtual void write(OSTREAM &os, int offset=0) const =0;    

    // --------------------------------------
    
    qpp_object(const STRING & __name = "", qpp_object * __owner = NULL)
    {
      _name = __name;
      _owner = __owner;
    }

    virtual STRING name() const
    {
      return _name;
    }

    virtual void setname(const STRING & __name)
    {
      _name = __name;
    }

    virtual void error(STRING const & what, int line = -1, STRING const & fname = "");

    virtual void assert(bool cond, STRING const & what)
    {
      if (!cond)
	error(what);
    }
    
    virtual STRING geterror()
    {
      return _error;
    }

    virtual qpp_object* owner() const
    {
      return _owner;
    }

    virtual void setowner(qpp_object * __owner = NULL)
    {
      _owner = __owner;
    }

    virtual qpp_object* getobject_lcl(const STRING & obj) const
    {
      int i=obj.find('.');
      bool cmplx = (i != STRING::npos);
      STRING s = obj.substr(0,i);

      bool found = false;
      int j=0;
      while (j<n_nested())
	{
	  std::cerr << nested(j)->name() << "\n";
	  if (nested(j)->name() == s)
	    {
	      found = true;
	      break;
	    }
	  j++;
	}

      // try to find the first nameless object with category == obj
      if (!found)
	{
	  j=0;
	  while (j<n_nested())
	    {
	      std::cerr << nested(j)->category() << " " << nested(j)->name() << "\n";
	      if (nested(j)->name() == "" && nested(j)->category() == s)
		{
		  found = true;
		  break;
		}
	      j++;
	    } 
	}
      
      if ( !found)
	return NULL;
      else if (cmplx)
	return nested(j) -> getobject_lcl(obj.substr(i+1));
      else
	return nested(j);
    }

    virtual qpp_object* getobject_glbl(const STRING & obj) const
    {
      qpp_object * p = getobject_lcl(obj);
      if ( p == NULL && owner() != NULL)
	{
	  std::cerr << "LVL UP\n";
	  p = owner()->getobject_glbl(obj);
	}
      return p;
    }

    virtual qpp_object* getobject(const STRING & obj, qscope scp) const
    {
      if (scp==qscope_local)
	return getobject_lcl(obj);
      else if (scp==qscope_global)
	return getobject_glbl(obj);
    }

    template <class T>
    bool parameter(T & res, int i) const;

    template <class T>
    bool parameter(T & res, STRING parm, qscope scp);

  };

  // --------------------------------------------------------------------------------------

  class qpp_exception{
    
    qpp_object * _who;

  public:

    qpp_exception(qpp_object * __who)
    { _who = __who;}
    
    qpp_object & who()
    {return * _who;}
    
    STRING what()
    {return _who->geterror();}

  };

  // ------------------------------------------------------------


  // ------------------------------------------------------------

  class qpp_array : public qpp_object{
  protected:

    std::vector<qpp_object*> _array;

    qppobject_type _mask;

  public:

    qpp_array(const STRING & __name = "", qpp_object * __owner = NULL, int __mask = ~0x0) : 
      qpp_object(__name,__owner)
    {
      _mask = __mask;
    }

    virtual int n_nested() const
    {
      return _array.size();
    }

    virtual qpp_object* nested(int i) const
    {
      return _array[i];
    }

    qpp_object * operator[](int i) const
    {
      return _array[i];
    }

    virtual qpp_object* owner()
    {
      return _owner;
    }

    virtual STRING category() const
    {
      return "";
    }

    virtual qppobject_type gettype() const
    {
      return qtype_body;
    }

    void allow(qppobject_type __mask)
    {
      _mask = __mask;
    }

    qppobject_type allowed() const
    {
      return _mask;
    }

    void add(qpp_object & q)
    {
      assert( q.gettype() & _mask, "This type of object cannot be added");
      _array.push_back(&q);
      q.setowner(this);
    }

    void insert(int i, qpp_object & q)
    {
      assert( q.gettype() & _mask, "This type of object cannot be added");
      _array.insert(_array.begin()+i,&q);
      q.setowner(this);
    }

    void erase(int i)
    {
      _array.erase(_array.begin()+i);
    }

    void set(int i, qpp_object & q)
    {
      assert( q.gettype() & _mask, "This type of object cannot be added");
      _array[i] = &q;
      q.setowner(this);
    }

    void clear()
    {
      _array.clear();
    }

    virtual void write(OSTREAM &os, int offset=0) const
    {
      for (int i=0; i<_array.size(); i++)
	_array[i]->write(os,offset);
    }
    
  };
  
  // --------------------------------------------------------------------------------------

  class qpp_param_array : public qpp_array {
  public:

    qpp_param_array(const STRING & __name = "", qpp_object * __owner = NULL) : 
      qpp_array(__name,__owner, qtype_parameter | qtype_data_int | 
		qtype_data_bool | qtype_data_float | qtype_data_double | qtype_data_string)
    {}

    /*
    STRING param_name(int i) const
    {
      return nested(i).name();
    }

    STRING param_val(int i) const
    {
      
    }
    */

    virtual void write(OSTREAM &os, int offset=0) const
    {
      //      if (offset==0)
      //	{
      os << "(";
      for (int i=0; i<_array.size(); i++)
	{
	  if (i>0)
	    os << ", ";
	  _array[i]->write(os,offset);
	}
      os << ")";
	  /*	}
      else
	{
	  for (int i=0; i<offset; i++)
	    os << " ";
	  os << "{";
	  for (int i=0; i<_array.size(); i++)
	    _array[i]->write(os,offset+2);
	  for (int i=0; i<offset; i++)
	    os << " ";
	  os << "}";
	}
	  */
    }

  };

  // --------------------------------------------------------------------------------------

  template <class T>
  class qpp_parameter : public qpp_param_array
  {
  protected:
    T _value;
    int _line;
    STRING _file;

  public:

    qpp_parameter(const STRING & __name, const T & __value, qpp_object *__owner=NULL, 
		  int __line=-1, const STRING & __file="") :
      qpp_param_array(__name, __owner)
    {
      _value = __value;
      _line = __line;
      _file = __file;
    }

    virtual STRING category() const
    { return "parameter"; }

    T value() const
    { return _value; }

    T & value()
    { return _value; }

    int line() const
    { return _line;}

    STRING file() const
    { return _file; }

    virtual qppobject_type gettype() const
    {return qtype_parameter | qtype_data<T>::type;} 
    
    virtual void write(OSTREAM &os, int offset=0) const
    {

      //debug
      //os << "parameter " << name() << " = " << "\"" << value() << "\"" 
      //<< " nested= " << _nested_parm.size() << "\n";
      //std::cerr << "parameter " << name() << " = " << "\"" << value() << "\"" 
      //	 << " nested= " << _nested_parm.size() << "\n";

      for (int i=0; i<offset; i++)
	os << " ";
      SSTREAM val;
      val << value();
      if ( name() != "" && val.str() != "")
	os << name() << " = " << value();
      else
	os << name() << value();
      if (n_nested()>0)
	qpp_param_array::write(os,offset);
      //      if (offset>0)
      //	os << ";\n";
    }
    
  };

  // ----------------------------------------------------------------

  class qpp_declaration : public qpp_array
  {
  protected:

    STRING _category;
    int _line;
    STRING _file;
    int _nparm;

  public:

    qpp_declaration(const STRING & __category, const STRING & __name, 
		    qpp_object *__owner = NULL, qpp_param_array * __parm = NULL, 
		    int __line=-1, const STRING & __file="") : 
      qpp_array(__name,__owner)
    {
      _category = __category;
      _line = __line;
      _file = __file;

      if (__parm != NULL)
	{
	  for (int i=0; i<__parm->n_nested(); i++)
	    add(*__parm->nested(i));
	  _nparm =__parm->n_nested(); 
	}
      else
	_nparm = 0;
    }

    virtual STRING category() const
    {
      return _category;
    }
    
    virtual qppobject_type gettype() const
    {
      return qtype_declaration;
    }

    int n_param() const
    {
      return _nparm;
    }

    qpp_object * param(int i) const
    {
      return nested(i);
    }

    void insert_param(int i, qpp_object & q)
    {
      insert(i,q);
      _nparm++;
    }

    void add_param(qpp_object & q)
    {
      insert(_nparm,q);
      _nparm++;
    }

    void erase_param(int i)
    {
      erase(i);
      _nparm--;
    }

    void insert_decl(int i, qpp_object & q)
    {
      insert(_nparm+i,q);
    }

    void add_decl(qpp_object & q)
    {
      add(q);
    }

    void erase_decl(int i)
    {
      erase(_nparm+i);
    }

    int n_decl() const
    {
      return n_nested()-_nparm;
    }

    qpp_object * decl(int i) const
    {
      return nested(_nparm+i);
    }

    void write(OSTREAM &os, int offset =0) const
    {
     
      for (int i=0; i<offset; i++)
	os << " ";
      if ( category() != "" && name() != "")
	os << category() << " " << name();
      else
	os << category() << name();

      if (n_param()>0)
	{
	  os << "(";
	  for (int i=0; i<n_param(); i++)
	    {
	      //	      _nested_parm[i]->write(os);
	      //os << nested_parm(i).category() << "\n";
	      param(i)->write(os);
	      if (i<n_param()-1)
		os << ", ";
	    }
	  os << ")";
	}
      if (n_nested()>n_param())
	{
	  os << "\n";
	  for (int i=0; i<offset+2; i++)
	    os << " ";
	  os << "{\n";
	  for (int i=n_param(); i<n_nested(); i++)
	    {
	      nested(i)->write(os,offset+4);
	      if (nested(i)->gettype() & qtype_parameter)
		os << ";\n";
	    }
	  for (int i=0; i<offset+2; i++)
	    os << " ";
	  os << "}\n";
	}
      else
	os << ";\n";
    }

  };

  // -----------------------------------------------
  template <class T>
  bool qpp_object::parameter(T & res, int i) const
  {
    bool success = false;
    if (n_nested()>i && nested(i)->gettype()==(qtype_parameter | qtype_data<T>::type) )
      {
	success = true;
	res = ((qpp_parameter<T>*)nested(i))->value();
      }
    return success;
  }

  template <class T>
  bool qpp_object::parameter(T & res, STRING parm, qscope scp)
  {
    qpp_object * p = getobject(parm,scp);
    bool success = false;
    if (p!=NULL && p->gettype()==(qtype_parameter | qtype_data<T>::type) )
      {
	success = true;
	res = ((qpp_parameter<T>*)p)->value();
      }
    return success;
  }

};

#endif
