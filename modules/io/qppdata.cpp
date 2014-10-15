#include "io/qppdata.hpp"

namespace qpp{

  template<>
  const qppobject_type qtype_data<int>::type = qtype_data_int;
  template<>
  const qppobject_type qtype_data<bool>::type = qtype_data_bool;
  template<>
  const qppobject_type qtype_data<double>::type = qtype_data_double;
  template<>
  const qppobject_type qtype_data<float>::type = qtype_data_float;
  template<>
  const qppobject_type qtype_data<STRING>::type = qtype_data_string;
  
  // --------------------------------------------------------------------------------------

  qpp_exception::qpp_exception(qpp_object * __who)
  { _who = __who;}
  
  qpp_object & qpp_exception::who()
  {return * _who;}
  
  STRING qpp_exception::what()
  {return _who->error();}
  
  // --------------------------------------------------------------------------------------

  qpp_declaration::qpp_declaration(const STRING & __cat, const STRING & __name, int __line) : 
    qpp_parameter<STRING>(__name,"",__line)
  {
    _cat = __cat;
  }

  STRING qpp_declaration::category() const
  { return _cat; }

  qppobject_type qpp_declaration::gettype() const
  {return qtype_declaration;}

  int qpp_declaration::n_decl() const
  {
    _nested_decl.size();
  }

  qpp_object & qpp_declaration::nested_decl(int i) const
  {
    return * _nested_decl[i];
  }

  std::vector<qpp_object* > & qpp_declaration::nested_decl() 
  {
    return _nested_decl;
  }

  void qpp_declaration::add_decl(qpp_object & p)
  {
    _nested_decl.push_back(&p);
  }
      
  void qpp_declaration::ins_decl(int i, qpp_object & p)
  {
    _nested_decl.insert(_nested_decl.begin(),&p);
  }    

  void qpp_declaration::del_decl(int i)
  {
    _nested_decl.erase(_nested_decl.begin()+i);
  }

  int qpp_declaration::n_next() const
  {
    return n_parm()+n_decl();
  }

  qpp_object* qpp_declaration::next(int i)
  {
    if (0<=i && i<n_parm())
      return &nested_parm(i);
    else if (n_parm()<=i && i<n_parm()+n_decl())
      return &nested_decl(i-n_parm());
    //      else error();
  }

  void qpp_declaration::write(std::basic_ostream<CHAR,TRAITS> &os, int offset) const
  {
     
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

  STRING qpp_declaration::env(const STRING & prm, int i)
  {
    if (i==-1)
      i = n_decl()-1;
    bool found = false;
    STRING res="";
    for (int j=0; j<=i; j++)
      if ( (nested_decl(j).gettype() & qtype_parameter) && 
	   ((qpp_parameter<STRING>*)&nested_decl(j)) -> n_parm() == 0 &&
	   ((qpp_parameter<STRING>*)&nested_decl(j)) -> name() == prm)
	{
	  found = true;
	  res = ((qpp_parameter<STRING>*)&nested_decl(j)) -> value();
	  break;
	}
    return res;
  }

};
