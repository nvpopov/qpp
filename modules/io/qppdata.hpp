#ifndef _QPPDATA_H
#define _QPPDATA_H

#include <string>
#include <iostream>
#include <vector>

namespace qpp{

#ifdef WCHAR

#define CHAR wchar
#define STRING std::wstring

#else

#define CHAR char
#define STRING std::string

#endif

  typedef std::char_traits<CHAR> TRAITS;

  enum{
    data_parameter     = 0x000200,
    data_declaration   = 0x000400,
    data_geometry      = 0x000800,
    data_xgeometry     = 0x001000,
    data_vectors       = 0x002000,
    data_basis         = 0x004000,
    data_manyfold      = 0x008000,
    data_zmatrix       = 0x010000,
    data_zpattern      = 0x020000,
    data_zpt_bond      = 0x040000,
    data_zpt_angle     = 0x080000,
    data_zpt_dihedral  = 0x100000,
    data_zpt_surfangle = 0x200000,
    data_geom_modifier = 0x400000,
    data_region        = 0x800000,

    // additional bits for some of these types
    data_dim0        = 0x001,
    data_dim1        = 0x002,
    data_dim2        = 0x004,
    data_dim3        = 0x008,
    data_type_int    = 0x010,
    data_type_bool   = 0x020,
    data_type_double = 0x040,
    data_type_float  = 0x080,
    data_type_string = 0x100,
  };

  typedef long int qppobject_type;

  template<class T>
  struct data_type
  {
    static const qppobject_type type;
  };

  // fixme - this should not be in .hpp file
  template<>
  const qppobject_type data_type<int>::type = data_type_int;
  template<>
  const qppobject_type data_type<bool>::type = data_type_bool;
  template<>
  const qppobject_type data_type<double>::type = data_type_double;
  template<>
  const qppobject_type data_type<float>::type = data_type_float;
  template<>
  const qppobject_type data_type<STRING>::type = data_type_string;

  // -------------------------------------------------------
  class qpp_object{
  public:

    virtual int n_next() const =0;

    virtual qpp_object* next(int i) =0;

    virtual STRING category() const=0;

    virtual STRING name() const=0;

    virtual qppobject_type gettype() const=0;

    virtual void error(STRING const & what) =0;

    virtual STRING error() =0;

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const =0;    
    
  };

  // --------------------------------------------------------------------------------------
  class qpp_exception{
    
    qpp_object * _who;

  public:
    qpp_exception(qpp_object * __who)
    { _who = __who;}

    qpp_object & who(){return * _who;}

    typename STRING what(){return _who->error();}
  };
  
  // --------------------------------------------------------------------------------------

  template <class T>
  class qpp_parameter : public qpp_object
  {
  protected:
    STRING _name;
    T _value;

    // fixme - this actually should be array of parameters
    std::vector<qpp_object*> _nested_parm;
    int _line;

  public:

    qpp_parameter(const STRING & __name, const T & __value, int __line=0)
    {
      _name = __name;
      _value = __value;
      _line = __line;
    }

    int n_parm() const
    {
      _nested_parm.size();
    }

    qpp_object & nested_parm(int i) const
    {
      return * _nested_parm[i];
    }

    std::vector<qpp_object* > & nested_parm() 
    {
      return _nested_parm;
    }

    void add_parm(qpp_object & p)
    {
      _nested_parm.push_back(&p);
    }
      
    void ins_parm(int i, qpp_object & p)
    {
      _nested_parm.insert(_nested_parm.begin(),&p);
    }    

    void del_parm(int i)
    {
      _nested_parm.erase(_nested_parm.begin()+i);
    }

    virtual int n_next() const
    {
      return n_parm();
    }

    virtual qpp_object* next(int i)
    {
      return &nested_parm(i);
    }

    virtual STRING category() const
    { return "parameter"; }

    virtual STRING name() const
    { return _name; }

    T value() const
    { return _value; }

    T & value()
    { return _value; }

    int line() const
    { return _line;}

    virtual qppobject_type gettype() const
    {return data_parameter | data_type<T>::type;} 
    
    virtual void error(STRING const & what)
    {
      //fixme
    }

    virtual STRING error()
    {
      //fixme
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {

      //debug
      //os << "parameter " << name() << " = " << "\"" << value() << "\"" 
      //<< " nested= " << _nested_parm.size() << "\n";
      //std::cerr << "parameter " << name() << " = " << "\"" << value() << "\"" 
      //	 << " nested= " << _nested_parm.size() << "\n";

      for (int i=0; i<offset; i++)
	os << " ";
      if ( _name != "" && _value != "")
	os << _name << " = " << _value;
      else
	os << _name << _value;
      if (n_parm()>0)
	{
	  os << "(";
	  for (int i=0; i<n_parm(); i++)
	    {
	      nested_parm(i).write(os);
	      if (i<n_parm()-1)
		os << ", ";
	    }
	  os << ")";	  
	}
      if (offset>0)
	os << ";\n";
    }
    
  };

  // ------------------------------------------------------------

  class qpp_declaration : public qpp_parameter<STRING>
  {
  protected:
    STRING _cat;
    std::vector<qpp_object*> _nested_decl;

  public:

    qpp_declaration(const STRING & __cat, const STRING & __name, int __line = 0) : 
      qpp_parameter<STRING>(__name,"",__line)
    {
      _cat = __cat;
    }

    virtual STRING category() const
    { return _cat; }

    virtual qppobject_type gettype() const
    {return data_declaration;}

    int n_decl() const
    {
      _nested_decl.size();
    }

    qpp_object & nested_decl(int i) const
    {
      return * _nested_decl[i];
    }

    std::vector<qpp_object* > & nested_decl() 
    {
      return _nested_decl;
    }

    void add_decl(qpp_object & p)
    {
      _nested_decl.push_back(&p);
    }
      
    void ins_decl(int i, qpp_object & p)
    {
      _nested_decl.insert(_nested_decl.begin(),&p);
    }    

    void del_decl(int i)
    {
      _nested_decl.erase(_nested_decl.begin()+i);
    }

    virtual int n_next() const
    {
      return n_parm()+n_decl();
    }

    virtual qpp_object* next(int i)
    {
      if (0<=i && i<n_parm())
	return &nested_parm(i);
      else if (n_parm()<=i && i<n_parm()+n_decl())
	return &nested_decl(i-n_parm());
      //      else error();
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      //debug
      //os << "declaration_tree write " << n_parm() << " " << n_decl() << "\n";
      
      for (int i=0; i<offset; i++)
	os << " ";
      if ( _cat != "" && name() != "")
	os << _cat << " " << name();
      else
	os << _cat << name();

      if (n_parm()>0)
	{
	  os << "(";
	  for (int i=0; i<n_parm(); i++)
	    {
	      //	      _nested_parm[i]->write(os);
	      //os << nested_parm(i).category() << "\n";
	      nested_parm(i).write(os);
	      if (i<n_parm()-1)
		os << ", ";
	    }
	  os << ")";
	}
      if (n_decl()>0)
	{
	  os << "\n";
	  for (int i=0; i<offset+2; i++)
	    os << " ";
	  os << "{\n";
	  for (int i=0; i<n_decl(); i++)
	    nested_decl(i).write(os,offset+4);
	  for (int i=0; i<offset+2; i++)
	    os << " ";
	  os << "}\n";
	}
      else
	os << ";\n";
    }

  };

};

#endif
