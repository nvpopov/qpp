#ifndef _QPPDATA_H
#define _QPPDATA_H

#include <string>
#include <iostream>
#include <vector>

namespace qpp{

  enum{
    qppdata_parameter   = 1,
    qppdata_declaration = 2,
    qppdata_geometry  = 3,
    qppdata_vectors   = 4,
    qppdata_basis     = 5,
    qppdata_manyfold  = 6,
    qppdata_zmatrix   = 7,
    qppdata_zpattern  = 8,
    qppdata_zpt_bond  = 9,
    qppdata_zpt_angle = 10,
    qppdata_zpt_dihedral = 11,
    qppdata_zpt_surfangle = 12,
    
    qppdata_dim0      = 0x0010000,
    qppdata_dim1      = 0x0020000,
    qppdata_dim2      = 0x0040000,
    qppdata_dim3      = 0x0080000,
    qppdata_string    = 0x0100000,
    qppdata_int       = 0x0200000,
    qppdata_double    = 0x0400000
  };

  // -------------------------------------------------------
  template <class charT=std::string::value_type , class traits = std::char_traits<charT> >
  class qpp_object{
  public:

    typedef std::basic_string<charT,traits> string;

    virtual string category() =0;

    virtual string name() =0;

    virtual int gettype() =0;

    virtual void error(string const & what) =0;

    virtual string error() =0;

    virtual void write(std::basic_ostream<charT,traits> &os, int offset=0) =0;    
    
  };

  // --------------------------------------------------------------------------------------
  template <class charT=std::string::value_type , class traits = std::char_traits<charT> >
  class qpp_exception{
    
    qpp_object<charT,traits> * _who;

  public:
    qpp_exception(qpp_object<charT,traits> * __who)
    { _who = __who;}

    qpp_object<charT,traits> & who(){return _who;}

    typename qpp_object<charT,traits>::string what(){return _who->error();}
  };
  
  // --------------------------------------------------------------------------------------

  template <class charT=std::string::value_type, class traits = std::char_traits<charT> >
  class qpp_data_array
  {
  protected:
    std::vector<qpp_object<charT,traits>*> arr;

    typedef std::basic_string<charT,traits> string;

  public:
    
    int size(){return arr.size();}
    
    qpp_object<charT,traits> & operator[](int i){return *arr[i];}

    qpp_object<charT,traits> & operator()(string str, int i=0){}
    
    virtual void add(qpp_object<charT,traits> & p)
    {
      arr.push_back(&p);
    }

    string category(int i)
    { return arr[i]->category();}

    string name(int i)
    { return arr[i]->name();}
    
    ~qpp_data_array()
    {
      for (int i=0; i < arr.size(); i++)
	delete arr[i];
    }
    
    void debug(int shift=0)
    {
      std::cout << "list of size " << size() << "\n";
      for (int i=0; i<size(); i++)
	{
	  for (int j=0; j<shift+2; j++) std::cout << " "; 
	  std::cout << "node " << i << ":";
	  arr[i]->debug(shift+2);
	}
      for (int j=0; j<shift; j++) std::cout << " "; 
      std::cout << "end_of_list\n";
    }
    
  };

  // -------------------------------------------------------------

  template <class charT=std::string::value_type, class traits = std::char_traits<charT> >
  class qpp_parameter_tree;

  // -------------------------------------------------------------

  template <class charT=std::string::value_type, class traits = std::char_traits<charT> >
  class qpp_param_array : public qpp_data_array<charT,traits>
  {
    using typename qpp_data_array<charT,traits>::string;
    using qpp_data_array<charT,traits>::arr;

  public:

    virtual void add(qpp_object<charT,traits> & p)
    {
      if ( p.gettype() & qppdata_parameter )
	arr.push_back(&p);
      else
	{
	  // fixme - some error management? 
	}
    }

    string value(int i)
    {
      return ((qpp_parameter_tree<charT,traits>*)(arr[i])) -> value();
    }

  };

  // -------------------------------------------------------------

  template <class charT, class traits>
  class qpp_parameter_tree : public qpp_object<charT,traits>
  {

    using typename qpp_object<charT,traits>::string;
    string _name, _value;

  public:

    qpp_param_array<charT,traits> parameters;

    qpp_parameter_tree(string __name, string __value, int line=0)
    {
      _name = __name;
      _value = __value;
    }

    virtual string category()
    { return "parameter"; }

    virtual string name()
    { return _name; }

    string value()
    { return _value; }

    virtual int gettype(){return qppdata_parameter | qppdata_string;} 
    
    virtual void write(std::basic_ostream<charT,traits> &os, int offset=0)
    {

      for (int i=0; i<offset; i++)
	os << " ";
      if ( _name != "" && _value != "")
	os << _name << " = " << _value;
      else
	os << _name << _value;
      if (parameters.size()>0)
	{
	  os << "(";
	  for (int i=0; i<parameters.size(); i++)
	    {
	      parameters[i].write(os);
	      if (i<parameters.size()-1)
		os << ", ";
	    }
	  os << ")";	  
	}
      if (offset>0)
	os << ";\n";
    }
    
  };

  // ------------------------------------------------------------

  template <class charT, class traits = std::char_traits<charT> >
  class qpp_declaration_tree : public qpp_object<charT,traits>
  {
    using typename qpp_object<charT,traits>::string;
    
    string _cat, _name;
    int _line_number;

  public:

    qpp_data_array<charT,traits> declarations;
    qpp_param_array<charT,traits> parameters;

    qpp_declaration_tree(string __cat, string __name, int line=0)
    {
      _cat = __cat;
      _name = __name;
      _line_number = line;
    }

    virtual string category()
    { return _cat; }

    virtual string name()
    { return _name; }

    virtual int gettype(){return qppdata_declaration | qppdata_string;}

    /*
    virtual void debug(int shift)
    {
      //for (int i=0; i<shift; i++) std::cout << " ";
      std::cout << "declaration \"" << _field1 << "\" \"" << _field2 << "\"\n";
      if (parameters.size()>0)
	{
	  for (int i=0; i<shift; i++) std::cout << " ";
	  std::cout << "nested parameters ";
	  parameters.debug(shift);
	}
      if (declarations.size()>0)
	{
	  for (int i=0; i<shift; i++) std::cout << " ";
	  std::cout << "nested declarations ";
	  declarations.debug(shift);
	}
    }
    */

    virtual void write(std::basic_ostream<charT,traits> &os, int offset=0)
    {
      os << "declaration_tree write " << parameters.size() << " " << declarations.size() << "\n";
      
      for (int i=0; i<offset; i++)
	os << " ";
      if ( _cat != "" && _name != "")
	os << _cat << " " << _name;
      else
	os << _cat << _name;

      if (parameters.size()>0)
	{
	  os << "(";
	  for (int i=0; i<parameters.size(); i++)
	    {
	      parameters[i].write(os);
	      if (i<parameters.size()-1)
		os << ", ";
	    }
	  os << ")";
	}
      if (declarations.size()>0)
	{
	  os << "\n";
	  for (int i=0; i<offset+2; i++)
	    os << " ";
	  os << "{\n";
	  for (int i=0; i<declarations.size(); i++)
	    declarations[i].write(os,offset+4);
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
