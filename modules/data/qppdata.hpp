#ifndef _QPPDATA_H
#define _QPPDATA_H

#include <vector>
#include <data/types.hpp>
#include <io/strfun.hpp>

namespace qpp{

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
    qtype_meta          = 0x200000000,
    qtype_shell         = 0x400000000,

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
    qtype_data_all     = qtype_data_int   | qtype_data_bool   | qtype_data_double | 
                         qtype_data_float | qtype_data_string,
    qtype_basis_pw     = 0x0200,
    qtype_basis_gauss  = 0x0400,
    qtype_basis_slater = 0x0800,
    qtype_basis_siesta = 0x1000
  };

  enum{
    qscope_local  = 0x01, 
    qscope_global = 0x02, 
    qscope_above  = 0x04,
    qscope_below  = 0x08,
    qscope_all    = qscope_below | qscope_above
  };

  typedef long int qppobject_type;

  typedef unsigned char qscope;

  template<class T>
  struct qtype_data
  {
    static const qppobject_type type;
    static const STRING name;
  };

  // -------------------------------------------------------------------------------------
  /*
  template<class T>
  bool qtype_convertable(qppobject_type t2)
  {}

  template<class T1,T2>
  T qtype_convert()
  */
  // -------------------------------------------------------------------------------------

  class qpp_exception;

  template <class T>
  class qpp_parameter;

  // -------------------------------------------------------
  class qpp_object{
  protected:

    STRING _name, _error;

    qpp_object* _owner;

    int _line;
    STRING _file;

  public:

    virtual STRING category() const=0;

    virtual qppobject_type gettype() const=0;

    virtual int n_nested() const =0;

    virtual qpp_object* nested(int i) const =0;

    virtual int n_param() const =0;
    
    virtual void set_n_param(int n) =0;

    virtual void write(OSTREAM &os, int offset=0) const =0;    
    
    virtual qpp_object * copy() const =0;

    virtual int run()
    // By default does nothing
    { return 0; }

    // --------------------------------------
    
    qpp_object(const STRING & __name = "", qpp_object * __owner = NULL,
	       int __line = -1, const STRING & __file = "")
    {
      _name = __name;
      _owner = __owner;
      _line = __line;
      _file = __file;
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

    int line() const
    { return _line;}

    void setline(int __line)
    { _line = __line;}

    STRING file() const
    { return _file; }

    void setfile(const STRING & __file)
    { _file = __file; }

    virtual qpp_object* getobject_lcl(const STRING & obj, qscope scp,
				      qpp_object * where) const
    {
      int i=obj.find('.');
      bool cmplx = (i != STRING::npos);
      STRING s = obj.substr(0,i);

      bool found = false;
      int iw = obj_index(where), n = n_nested(), j1=0, j2=n;

      bool above = true, below = true;
      if ( (scp & qscope_above) && ! (scp & qscope_below) )
	below = false;
      if ( !(scp & qscope_above) &&  (scp & qscope_below) )
	above = false;

      if ( !below && iw!=-1)
	j2 = iw;

      if ( !above && iw!=-1)
	j1 = iw;

      int j=j1;
      while (j<j2)
	{

	  //debug
	  //std::cerr << nested(j)->name() << "\n";
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
	  j=j1;
	  while (j<j2)
	    {
	      //debug
	      //std::cerr << nested(j)->category() << " " << nested(j)->name() << "\n";
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
	return nested(j) -> getobject_lcl(obj.substr(i+1), scp, where);
      else
	return nested(j);
    }

    virtual qpp_object* getobject_glbl(const STRING & obj, qscope scp,
				       qpp_object * where) const
    {
      qpp_object * p = getobject_lcl(obj,scp,where);
      if ( p == NULL && owner() != NULL)
	{
	  //debug
	  //std::cerr << "LVL UP\n";
	  p = owner()->getobject_glbl(obj,scp,where);
	}
      return p;
    }

    virtual qpp_object* getobject(const STRING & obj, 
				  qscope scp = qscope_global | qscope_all,
				  qpp_object * where = NULL) const
    {
      if (scp & qscope_local)
	return getobject_lcl(obj, scp, where);
      else if (scp & qscope_global)
	return getobject_glbl(obj, scp, where);
      else
	return NULL;
    }

    template <class T>
    qpp_parameter<T> * parameter(int i) const;

    template <class T>
    qpp_parameter<T> * parameter(const STRING & parm, 
				 qscope scp = qscope_local | qscope_all) const;

    template <class T>
    bool getparamvalue(T & val, int i) const;

    template <class T>
    bool getparamvalue(T & val, const STRING & parm, 
		  qscope scp = qscope_local | qscope_all) const;

    template <class T>
    bool setparamvalue(const T & val, int i);
    
    template <class T>
    bool setparamvalue(const T & val, const STRING & parm, 
		     qscope scp = qscope_local | qscope_all);

    int obj_index(qpp_object * p) const
    {
      int i; 
      bool found = false;
      for (i=0; i<n_nested(); i++)
	if (nested(i)==p)
	  {
	    found = true;
	    break;
	  }
      return found? i : -1;
    }

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

    qpp_array(const qpp_array & q) :
      qpp_object(q.name(),q.owner())
    {
      _mask = q._mask;
      for (int i = 0; i<q.n_nested(); i++)
	add( * q.nested(i)->copy() );
    }

    virtual int n_nested() const
    {
      return _array.size();
    }

    virtual qpp_object* nested(int i) const
    {
      return _array[i];
    }

    virtual int n_param() const
    { return 0; }
    
    virtual void set_n_param(int n)
    {
      //fixme - generate exception
    }

    qpp_object * operator[](int i) const
    {
      return _array[i];
    }
    
    qpp_object *& operator[](int i)
    {
      return _array[i];
    }
    /*
    virtual qpp_object* owner() const
    {
      return _owner;
    }
    */
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

    virtual qpp_object * copy() const
    {
      return new qpp_array(*this);
    }
    
  };
  
  // --------------------------------------------------------------------------------------

  class qpp_param_array : public qpp_array {
  public:

    qpp_param_array(const STRING & __name = "", qpp_object * __owner = NULL) : 
      qpp_array(__name,__owner, qtype_parameter | qtype_data_int | 
		qtype_data_bool | qtype_data_float | qtype_data_double | qtype_data_string)
    {}

    qpp_param_array(const qpp_param_array & q) :
      qpp_array(q)
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

    virtual int n_param() const
    { return n_nested(); }
    
    virtual void set_n_param(int n)
    {
      //fixme - generate exception
    }

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

    virtual qpp_object * copy() const
    {
      return new qpp_param_array(*this); 
    }

  };

  // --------------------------------------------------------------------------------------

  template <class T>
  class qpp_parameter : public qpp_param_array
  {
  protected:
    T *_value;

  public:

    qpp_parameter(const STRING & __name, const T & __value, qpp_object *__owner=NULL, 
		  int __line=-1, const STRING & __file="") :
      qpp_param_array(__name, __owner)
    {
      _value = new T(__value);
      setline(__line);
      setfile(__file);
    }

    qpp_parameter(const STRING & __name, T * __value, qpp_object *__owner=NULL, 
		  int __line=-1, const STRING & __file="") :
      qpp_param_array(__name, __owner)
    {
      _value = __value;
      setline(__line);
      setfile(__file);
    }

    qpp_parameter(const qpp_parameter<T> & q) :
      qpp_param_array(q)
    {
      _value = new T(*q._value);
      setline(q.line());
      setfile(q.file());
    }

    virtual STRING category() const
    { return "parameter"; }

    T value() const
    { return *_value; }

    T & value()
    { return *_value; }

    T * pointer()
    { return _value; }

    void setpointer(T * __value)
    {
      _value = __value;
    }

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

      STRING sval;
      sval = t2s<T>(value());

      bool valquote = false;
      if (split(sval).size()>1)
	valquote = true;
      if (sval=="" && n_nested()==0)
	valquote = true;

      if (valquote)
	os << name() << " = \"" << sval << "\"";
      else if ( name() != "" && sval != "")
	os << name() << " = " << sval;
      else
	os << name() << value();
      if (n_nested()>0)
	qpp_param_array::write(os,offset);
      //      if (offset>0)
      //	os << ";\n";
    }

    virtual qpp_object * copy() const
    {
      return new qpp_parameter<T>(*this);
    }
    
  };

  // ----------------------------------------------------------------

  class qpp_declaration : public qpp_array
  {
  protected:

    STRING _category;
    qpp_param_array * _parm;

  public:

    qpp_declaration(const STRING & __category, const STRING & __name, 
		    qpp_object *__owner = NULL, qpp_param_array * __parm = NULL, 
		    int __line=-1, const STRING & __file="") : 
      qpp_array(__name,__owner)
    {
      _category = __category;
      setline(__line);
      setfile(__file);

      _parm = __parm;
      if (_parm == NULL)
	_parm = new qpp_param_array;
      _parm->setowner(this);

      for (int i=0; i<_parm->n_nested(); i++)
	add(*_parm->nested(i));
    }

    qpp_declaration(const qpp_declaration & q) :
      qpp_array(q.name(),q.owner())
    {
      _category = q._category;
      setline(q.line());
      setfile(q.file());
      _parm = new qpp_param_array(*q._parm);
      for (int i=0; i<q._parm->n_nested(); i++)
	add(*q._parm->nested(i));
      for (int i=0; i<q.n_decl(); i++)
	add(*q.decl(i));
    }

    virtual STRING category() const
    {
      return _category;
    }
    
    virtual qppobject_type gettype() const
    {
      return qtype_declaration;
    }

    virtual int n_param() const
    {
      return _parm->n_nested();
    }
    
    virtual void set_n_param(int n)
    {
      delete _parm;
      _parm = new qpp_param_array("",this);
      for (int i=0; i<n; i++)
	_parm -> add( *nested(i) );
    }

    qpp_object * param(int i) const
    {
      return _parm->nested(i);
    }

    qpp_param_array * parameters()
    {
      return _parm;
    }

    void insert_param(int i, qpp_object & q)
    {
      _parm -> insert(i,q);
      insert(i,q);
    }

    void add_param(qpp_object & q)
    {
      int nparm = _parm->n_nested();
      _parm -> insert(nparm,q);
      insert(nparm,q);
    }

    void erase_param(int i)
    {
      _parm->erase(i);
      erase(i);
    }

    void set_param(int i, qpp_object & q)
    {
      (*_parm)[i] = &q;
      (*this)[i] = &q;
    }

    void insert_decl(int i, qpp_object & q)
    {
      insert(_parm->n_nested()+i,q);
    }

    void add_decl(qpp_object & q)
    {
      add(q);
    }

    void erase_decl(int i)
    {
      erase(_parm->n_nested()+i);
    }

    void set_decl(int i, qpp_object & q)
    {
      (*this)[_parm->n_nested()+i] = &q;
    }

    int n_decl() const
    {
      return n_nested()-_parm->n_nested();
    }

    qpp_object * decl(int i) const
    {
      return nested(_parm->n_nested()+i);
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

    virtual qpp_object * copy() const
    {
      return new qpp_declaration(*this);
    }

  };

  // -----------------------------------------------
  template <class T>
  qpp_parameter<T> * qpp_object::parameter(int i) const
  {
    if (n_nested()>i && nested(i)->gettype()==(qtype_parameter | qtype_data<T>::type) )
      return (qpp_parameter<T>*)nested(i);
    else
      return NULL;
  }

  template <class T>
  qpp_parameter<T> * qpp_object::parameter(const STRING & parm, qscope scp) const
  {
    qpp_object * p = getobject(parm,scp);

    //debug
    /*
    std::cerr << "looking for " << parm << " in ";
    write(std::cerr);
    std::cerr << "owner = " <<  owner() << "\n";
    if (owner()!=NULL) owner()->write(std::cerr);
    std::cerr << "\n";
    if (p!=NULL)
      {
	std::cerr << "------ parameter " << parm << " -----------\n";
	p->write(std::cout);
      }
    */

    if (p!=NULL && p->gettype()==(qtype_parameter | qtype_data<T>::type) )
      return (qpp_parameter<T>*)p;
    else
      return NULL;
  }


  template <class T>
  bool qpp_object::getparamvalue(T & val, int i) const
  {
    bool res = (i<n_nested() && nested(i)!=NULL && 
		(nested(i)->gettype() & (qtype_parameter | qtype_data<T>::type)));
    if (res)
      val = ((qpp_parameter<T>*)nested(i)) -> value();
    return res;
  }

  template <class T>
  bool qpp_object::getparamvalue(T & val, const STRING & parm, qscope scp) const
  {
    qpp_parameter<T>* p = parameter<T>(parm,scp);
    if (p!=NULL)
      val = p->value();
    return p!=NULL;
  }

  template <class T>
  bool qpp_object::setparamvalue(const T & val, int i)
  {
    bool res = (i<n_nested() && nested(i)!=NULL && 
		(nested(i)->gettype() & (qtype_parameter | qtype_data<T>::type)));
    if (res)
      ((qpp_parameter<T>*)nested(i)) -> value() = val;
    return res;
  }

  template <class T>
  bool qpp_object::setparamvalue(const T & val, const STRING & parm, qscope scp)
  {
    qpp_parameter<T>* p = parameter<T>(parm,scp);
    if (p!=NULL)
      p->value() = val;
    return p!=NULL;
  }

  // --------------------------------------------------------------------------------------
  /*
  template <class T>
  qpp_parameter<T> * getparam_copy(qpp_object * owner, const STRING & parm, 
				   const T & dflt, qscope scope = qscope_local + qscope_all)
  {
    qpp_parameter<T> *p;
    p = owner->parameter<T>(parm,scope);

    if (p!=NULL)
      return p->copy();
    else
      return new qpp_parameter<T>(parm,dflt);
  }
  */
  // --------------------------------------------------------------------------------------

};

#endif
