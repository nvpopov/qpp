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
    qtype_parameter     = 0x00002000,
    qtype_declaration   = 0x00004000,
    qtype_geometry      = 0x00008000,
    qtype_xgeometry     = 0x00010000,
    qtype_vectors       = 0x00020000,
    qtype_basis         = 0x00040000,
    qtype_manyfold      = 0x00080000,
    qtype_zmatrix       = 0x00100000,
    qtype_zpattern      = 0x00200000,
    qtype_zpt_bond      = 0x00400000,
    qtype_zpt_angle     = 0x00800000,
    qtype_zpt_dihedral  = 0x01000000,
    qtype_zpt_surfangle = 0x02000000,
    qtype_zpt_lindep    = 0x04000000,
    qtype_geom_builder  = 0x08000000,
    qtype_region        = 0x10000000,
    qtype_atom          = 0x20000000,
    qtype_molecule      = 0x40000000,
    qtype_shape         = 0x80000000,

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

  typedef long int qppobject_type;

  /*FIXME: Using structs in c++ */
  template<class T>
  struct qtype_data
  {
    static const qppobject_type type;
  };

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
    qpp_exception(qpp_object * __who);

    qpp_object & who();

    STRING what();
  };
  
  // --------------------------------------------------------------------------------------

  template <class T>
  class qpp_parameter : public qpp_object
  {
  protected:
    STRING _name, _error;
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
    {return qtype_parameter | qtype_data<T>::type;} 
    
    virtual void error(STRING const & what)
    {
      _error = what;
      throw qpp_exception(this);
    }

    virtual STRING error()
    {
      return _error;
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

    qpp_declaration(const STRING & __cat, const STRING & __name, int __line = 0);

    virtual STRING category() const;

    virtual qppobject_type gettype() const;

    int n_decl() const;

    qpp_object & nested_decl(int i) const;

    std::vector<qpp_object* > & nested_decl();

    void add_decl(qpp_object & p);
      
    void ins_decl(int i, qpp_object & p);

    void del_decl(int i);

    virtual int n_next() const;

    virtual qpp_object* next(int i);

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const;

    STRING env(const STRING & prm, int i=-1);

  };

};

#endif
