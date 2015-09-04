#ifndef _QPPMETA_H
#define _QPPMETA_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <data/qppdata.hpp>

namespace qpp{
  
  enum qmetatypes{
    qmetarray,
    qmetparam,
    qmetselect,
    qmetrepeat,
    qmetobject
  };

  class metaparam_block;

  // ----------------------------------------------------------

  class metaparam_structure{
  public:
    
    metaparam_block * producer;
    qpp_object * instance;
    std::vector<std::vector<metaparam_structure*> > rptns;
    // rptns[i][j] == i-th repetition of j-th element of producer
    metaparam_structure * owner;

    int choice;
    
    metaparam_structure(metaparam_block *__producer, metaparam_structure * __owner=NULL);

    void add_repetition();

    void insert_repetition(int i);

    void erase_repetition(int i);

    bool possible_to_add();

    bool possible_to_erase();

    int min_repeatitions();

    int max_repeatitions();

    int n_repetitions();

    int n_elements(int i_rep=0);

    bool element_exist(int i_element, int i_repetition = 0);

    metaparam_structure * element(int i_element, int i_repetition = 0);

    metaparam_structure * parameter(const STRING & pname);

    void create_structure(int i_element, int i_repetition = 0);

    void create_all();

    //    void create_instance(void * val);

    // bool create_instance(const STRING & s);

    //    void set_value(void * val);

    //bool set_value(const STRING & s);

    bool is_array();

    bool is_repetition();

    bool is_selection();

    bool is_parameter();
 
    bool value_defined();

    template <class T>
    T value();

    template <class T>
    void setvalue(const T & val);

    bool defined();

    //bool identify(qpp_param_array * parm);

    qpp_param_array * get_params();

    qpp_declaration * get_options();
  
    void debug(int offset=0, metaparam_structure * current=NULL);

  };

  // ----------------------------------------------------------

  class metaparam_block : public qpp_object
  {
  public:

    bool required;
 
    virtual int identify(const qpp_param_array & q, 
			 metaparam_structure & s, int & i1, int & i2) =0;

    virtual qmetatypes metatype() const =0;

    virtual int min_repetitions() const =0;

    virtual int max_repetitions() const =0;

    virtual bool has_value() const =0;

    virtual bool has_default_value() const =0;

    virtual qpp_object* default_param() const =0;
    /*
    virtual qpp_object * create_parameter(void * val) const =0;

    virtual void change_parameter(qpp_object * parm, void * val) const =0;

    virtual void * string2val(const STRING & s) =0;

    virtual STRING val2string(void *val) =0;
    */
    virtual bool has_value_list() const =0;

    virtual void value_list(std::vector<STRING> & vals) =0;

    virtual bool has_choice() const =0;

    virtual bool has_default_choice() const =0;

    virtual int default_choice() const =0;

    metaparam_block(const STRING & __name = "", qpp_object * __owner = NULL, bool __required = false);

    virtual qppobject_type gettype() const;

    virtual int n_param() const;
    
    virtual void set_n_param(int n);

    int identify(const qpp_param_array & q, metaparam_structure & s);

    //std::vector<metaparam_structure*> instances;

  };

  // -------------------------------------------------------------

  metaparam_block * create_metaparam(qpp_declaration & q, qpp_object * owner = NULL);

  // -------------------------------------------------------------

  class metaparam_array : public metaparam_block
  {
  public:

    bool ordered;

    std::vector<metaparam_block*> array;

    metaparam_array(const STRING & __name = "", qpp_object * __owner = NULL, bool __required = false);

    metaparam_array(qpp_declaration & decl, qpp_object * __owner = NULL);

    virtual int  identify(const qpp_param_array & q, 
			  metaparam_structure & s, int & i1, int & i2);

    virtual int min_repetitions() const;

    virtual int max_repetitions() const;

    virtual bool has_value() const;

    virtual bool has_default_value() const;

    virtual qpp_object* default_param() const;

    virtual bool has_value_list() const;

    virtual bool has_choice() const;

    virtual bool has_default_choice() const;

    virtual int default_choice() const;

    virtual void value_list(std::vector<STRING> & vals);

    virtual qmetatypes metatype() const;

    virtual STRING category() const;

    virtual int n_nested() const;

    virtual qpp_object* nested(int i) const;

    virtual void write(OSTREAM &os, int offset=0) const;

    virtual qpp_object * copy() const;

  };


  // -------------------------------------------------------------

  class metaparam_repeat : public metaparam_array
  {
  public:

    int min_rep, max_rep;

    metaparam_repeat(const STRING & __name = "", qpp_object * __owner = NULL, bool __required = false);

    metaparam_repeat(qpp_declaration & decl, qpp_object * __owner = NULL);

    virtual int identify(const qpp_param_array & q, 
			 metaparam_structure & s, int & i1, int & i2);

    virtual int min_repetitions() const;

    virtual int max_repetitions() const;

    virtual qmetatypes metatype() const;

    virtual STRING category() const;

    virtual int n_nested() const;

    virtual qpp_object* nested(int i) const;

    virtual void write(OSTREAM &os, int offset=0) const;

    virtual qpp_object * copy() const;

  };
  // -------------------------------------------------------------

  class metaparam_select : public metaparam_array
  {
  public:

    int dflt;

    metaparam_select(const STRING & __name = "", qpp_object * __owner = NULL, bool __required = false);

    metaparam_select(qpp_declaration & decl, qpp_object * __owner = NULL);

    virtual int identify(const qpp_param_array & q, 
			 metaparam_structure & s, int & i1, int & i2);

    virtual qmetatypes metatype() const;

    virtual bool has_choice() const;

    virtual bool has_default_choice() const;

    virtual int default_choice() const;

    virtual STRING category() const;

    virtual int n_nested() const;

    virtual qpp_object* nested(int i) const;

    virtual void write(OSTREAM &os, int offset=0) const;

    virtual qpp_object * copy() const;

  };

  // -------------------------------------------------------------

  template<class T>
  class metaparameter : public metaparam_block
  {
  public:

    std::vector<STRING> synonyms;

    metaparam_block * _nested;

    bool is_default;
    T * val_default;

    /*
    bool val_range, val_default;
    T * v1, * v2, *dflt;
    */
    
    struct val_record{
      T value;
      std::vector<STRING> synonyms;      
      metaparam_block * _nested;

      val_record( const T & _value)
      { 
	value = _value; 
	_nested = NULL;
      }

    };
    
    std::vector<val_record> values; 
    
    virtual int min_repetitions() const
    {
      return n_nested()>0 ? 1:0;
    }

    virtual int max_repetitions() const
    {
      return 1;
    }

    virtual bool has_value() const
    {
      return true;
    }

    virtual bool has_default_value() const
    {
      return is_default;
    }

    virtual qpp_object* default_param() const
    {
      if (is_default)
	return new qpp_parameter<T>(name(),*val_default);
      else
	return NULL;
    }

    /*
    virtual qpp_object * create_parameter(void * _val) const
    {
      return new qpp_parameter<T>(name(), *((T*)_val));
    }

    virtual void change_parameter(qpp_object * parm, void * val) const
    {
      ((qpp_parameter<T>*)parm)->value() = *((T*)val);
    }
    
    virtual void * string2val(const STRING & s)
    {
      T * val = new T;
      if (s2t<T>(s,*val))
	return val;
      else
	{
	  delete val;
	  return NULL;
	}
    }

    virtual STRING val2string(void *val)
    {
      SSTREAM ss;
      ss << * ((T*)(val));
      return ss.str();
    }
    */
    virtual bool has_value_list() const
    {
      return values.size()>0;
    }

    virtual void value_list(std::vector<STRING> & vals)
    {
      vals.clear();
      if (values.size()>0)
	for (int i=0; i<values.size(); i++)
	  vals.push_back(t2s<T>(values[i].value));
    }

    virtual bool has_choice() const
    { 
      if (_nested != NULL)
	return false;
      bool found=false;
      for (int i=0; i<values.size(); i++)
	if (values[i]._nested != NULL)
	  {
	    found = true;
	    break;
	  }
      return found;
    }

    virtual bool has_default_choice() const
    {
      return has_choice() && is_default;
    }

    virtual int default_choice() const
    {
      if (has_default_choice())
	{
	  for (int i=0; i<values.size(); i++)
	    if (values[i].value == *val_default )
	      return i;
	}
      else 
	return -1;
    }

    virtual int identify(const qpp_param_array & q, 
			 metaparam_structure & s, int & i1, int & i2);

    virtual qmetatypes metatype() const
    {
      return qmetparam;
    }

    virtual qppobject_type gettype() const
    {
      return qtype_meta | qtype_parameter | qtype_data<T>::type;
    }

    virtual STRING category() const
    {
      return "metaparameter";
    }

    virtual int n_nested() const
    {
      if (_nested != NULL) 
	return 1;

      bool found = false;
      for (int i=0; i<values.size(); i++)
	if (values[i]._nested != NULL)
	  {
	    found = true;
	    break;
	  }

      return found? values.size() : 0;
    }

    virtual qpp_object* nested(int i) const
    {
      if (i==0 && _nested != NULL)
	return _nested;
      
      else if (i>=0 && i<values.size())
	return values[i]._nested;
      
      else return NULL;
    }

    virtual void write(OSTREAM &os, int offset=0) const
    {
      for (int i=0; i<offset; i++)
	os << " ";
      if ( category() != "" && name() != "")
	os << category() << " " << name();
      else
	os << category() << name();

      os << "( type = "; 

      switch(qtype_data<T>::type)
	{
	case qtype_data_int:
	  os << "int"; break;
	case qtype_data_bool:
	  os << "bool"; break;
	case qtype_data_double:
	  os << "double"; break;
	case qtype_data_float:
	  os << "float"; break;
	case qtype_data_string:
	  os << "string"; break;
	}
      
      os << ")\n";
      for (int i=0; i<offset+2; i++)
	os << " ";
      os << "{\n";
      for (int i=0; i<offset+4; i++)
	os << " ";
      os << "required = " << (required? "yes" : "no") << ";\n";

      if (synonyms.size()>0)
	{
	  for (int i=0; i<offset+4; i++) os << " ";
	  os << "synonyms(";
	  for (int i=0; i<synonyms.size(); i++)
	    {
	      os << synonyms[i];
	      if (i<synonyms.size()-1)
		os << ", ";
	    }
	  os << ");\n";
	}

      if (is_default)
	{
	  for (int i=0; i<offset+4; i++) os << " ";
	  STRING svaldef = t2s<T>(*val_default);
	  if (svaldef=="")
	    os << "default = \"\";\n";
	  else
	    os << "default = " << (svaldef) << ";\n";
	}

      if (_nested != NULL)
	_nested -> write(os,offset+4);

      if (values.size()>0)
	for (int i=0; i<values.size(); i++)
	  {
	    for (int k=0; k<offset+4; k++) os << " ";
	    os << "value(" << values[i].value << ")\n";
	    for (int k=0; k<offset+6; k++) os << " ";
	    os << "{\n";
	    if (values[i].synonyms.size()>0)
	      {
		for (int k=0; k<offset+8; k++) os << " ";
		os << "synonyms(";
		for (int j=0; j<values[i].synonyms.size(); j++)
		  os << values[i].synonyms[j] << 
		    (j+1<values[i].synonyms.size() ? "," : ");\n");
	      }
	    if (values[i]._nested!=NULL)
	      values[i]._nested -> write(os,offset+8);
	    for (int k=0; k<offset+6; k++) os << " ";
	    os << "}\n";	    
	  }

      for (int i=0; i<offset+2; i++)
	os << " ";
      os << "}\n";
    }

    virtual qpp_object * copy() const 
    {
      return new metaparameter<T>(*this);
    }

    metaparameter(const STRING & __name = "", qpp_object * __owner = NULL, bool __required = false):
      metaparam_block(__name,__owner,__required)
    {
      is_default = false;
      val_default = NULL;

      _nested = NULL;
    }

    metaparameter(qpp_declaration & decl, qpp_object * __owner = NULL) :
      metaparam_block(decl.name(),__owner)
    {
      //debug
      //std::cerr << "--- metaparameter constructor ---\n";

      int n = decl.n_nested();
      bool used[n];
      for (int i=0; i<n; i++)
	used[i] = false;

      qpp_object *p = decl.getobject("synonyms", qscope_local);

      //std::cerr << "p= \n";
      //p->write(std::cerr);

      if (p!=NULL)
	{
	  if ( p->gettype() == qtype_parameter | qtype_data_string)
	    {
	      qpp_parameter<STRING> * s = (qpp_parameter<STRING>*)p;
	      if (s->n_nested()==0)
		synonyms.push_back( s->value() );
	      else
		for (int i=0; i<s->n_nested(); i++)
		  synonyms.push_back( ((qpp_parameter<STRING>*)s->nested(i))->value() );
	    }
	  else
	    p->error("Illegal synonyms declaration");
	  
	  used[decl.obj_index(p)] = true;
	}

      p = decl.getobject("required", qscope_local);

      /*
      std::cerr << boost::format("type(p) = %X %X\n") % p->gettype() %
	(qtype_parameter | qtype_data_bool);
      p->write(std::cerr);
      */

      if (p!=NULL)
	{
	  if ( p->gettype() == (qtype_parameter | qtype_data_bool))
	    required = ((qpp_parameter<bool>*)p) -> value();
	  else
	    p->error("Illegal \"required\" declaration", decl.line(), decl.file());

	  used[decl.obj_index(p)] = true;
	}
      else
	required = false;

      p = decl.getobject("default", qscope_local);
      if (p!=NULL)
	{
	  std::cerr << "==== debug ===\n";
	  p->write(std::cerr);
	  std::cerr << " type= " << std::hex << p->gettype() << std::dec << "\n";
	  if ( p->gettype() == (qtype_parameter | qtype_data<T>::type))
	    {
	      is_default = true;
	      val_default = new T(((qpp_parameter<T>*)p) -> value());
	    }
	  else if (qtype_data<T>::type == qtype_data_float && 
		   p->gettype() == (qtype_parameter | qtype_data_double))
	    {
	      is_default = true;
	      float * v = new float(((qpp_parameter<double>*)p) -> value());
	      val_default = (T*)v;
	    }
	  else
	    p->error("Illegal \"default\" declaration", decl.line(), decl.file());
	 
	  used[decl.obj_index(p)] = true;
	}
      else
	{
	  is_default = false;
	  val_default = NULL;
	}

      p = decl.getobject("values", qscope_local);
      if (p!=NULL)
	{
	  bool success =  (p->gettype() == qtype_declaration) && 
	    (((qpp_declaration*)p)->n_decl() == 0);

	  //debug
	  //std::cerr << "metaparam constructor:values alive1 success = " << success << "\n";
	  //p->write(std::cerr);

	  if (success)
	    for (int i=0; i<((qpp_declaration*)p)->n_param(); i++)
	      if (((qpp_declaration*)p)->param(i)->gettype() == 
		  qtype_parameter | qtype_data<T>::type )
		{
		  qpp_parameter<T> * v = (qpp_parameter<T>*) (((qpp_declaration*)p)->param(i));
		  if (v->name()=="")
		      values.push_back(*new val_record(v->value()));
		  else
		    {
		      success = false;
		      //debug
		      //std::cerr << "metaparam constructor:values break1 i= " << i << "\n";
		      break;
		    }
		}
	      else
		{
		  success = false;
		  //debug
		  //std::cerr << "metaparam constructor:values break2 i= " << i << "\n";
		  break;
		}

	  if (!success)
	    p->error("Illegal \"values\" declaration", decl.line(), decl.file());
	  
	  used[decl.obj_index(p)] = true;
	}
	
      int j;
      bool found = false;
      for(j=0; j<n; j++)
	if (decl.nested(j)->category() == "metaparam_array" ||
	    decl.nested(j)->category() == "metaparam_repeat" ||
	    decl.nested(j)->category() == "metaparam_select" ||
	    decl.nested(j)->category() == "metaparameter" )
	  {
	    found = true;
	    break;
	  }
      if (found)
	{
	  if (decl.nested(j)->gettype() == qtype_declaration)
	    _nested =create_metaparam(*((qpp_declaration*)decl.nested(j)));
	  else
	    decl.error("Illegal nested declaration", decl.line(), decl.file());
	  used[j] = true;
	}
      else
	_nested = NULL;

      for (j=0; j<n; j++)
	if (decl.nested(j)->gettype() == qtype_declaration &&
	    decl.nested(j)->category() == "value")
	  {
	    qpp_declaration * vdecl = (qpp_declaration*)decl.nested(j);
	    if (vdecl->n_param() != 1 || 
		!(vdecl->param(0)->gettype() & qtype_data<T>::type) )
	      vdecl -> error("Invalid value definition",vdecl->line(),vdecl->file());
	    val_record vrec(((qpp_parameter<T>*)(vdecl->param(0)))->value());

	    p = vdecl->getobject("synonyms",qscope_local);
	    if (p!=NULL)
	      {
		if ( p->gettype() == qtype_parameter | qtype_data_string)
		  {
		    qpp_parameter<STRING> * s = (qpp_parameter<STRING>*)p;
		    if (s->n_nested()==0)
		      vrec.synonyms.push_back( s->value() );
		    else
		      for (int i=0; i<s->n_nested(); i++)
			vrec.synonyms.push_back( 
			  ((qpp_parameter<STRING>*)s->nested(i))->value() );
		  }
		else
		  p->error("Illegal synonyms declaration");
	      }

	    int k;
	    bool found1 = false;
	    for(k=0; k<vdecl->n_decl(); k++)
	      if (vdecl->decl(k)->category() == "metaparam_array" ||
		  vdecl->decl(k)->category() == "metaparam_repeat" ||
		  vdecl->decl(k)->category() == "metaparam_select" ||
		  vdecl->decl(k)->category() == "metaparameter" )
		{
		  found1 = true;
		  break;
		}
	    if (found1)
	      {
		if (_nested!=NULL)
		  decl.error("Value specific nested declarations are not allowed if general nested declaration is present", decl.line(), decl.file());
		if (vdecl->gettype() == qtype_declaration)
		  vrec._nested =create_metaparam( *((qpp_declaration*)(vdecl->decl(k))));
		else
		  decl.error("Illegal nested declaration", decl.line(), decl.file());
	      }
	    else
	      vrec._nested = NULL;
	    
	    values.push_back(vrec);
	  }
      //debug
      //std::cerr << "--- metaparameter constructor: finished ---\n";
    }
    
  };

  // -------------------------------------------------------------

  class metaparam_object : public metaparam_block
  {
  public:

    qppobject_type mask;
 
    metaparam_object(qppobject_type _mask, const STRING & __name = "", qpp_object * __owner = NULL, bool __required = false);

    metaparam_object(const metaparam_object & q);

    metaparam_object(qpp_declaration & decl, qpp_object * __owner = NULL);

    virtual int identify(const qpp_param_array & q, 
			 metaparam_structure & s, int & i1, int & i2);

    virtual qmetatypes metatype() const;

    virtual int min_repetitions() const;

    virtual int max_repetitions() const;

    virtual bool has_value() const;

    virtual bool has_default_value() const;

    virtual qpp_object* default_param() const;
  
    virtual bool has_value_list() const;

    virtual void value_list(std::vector<STRING> & vals);

    virtual bool has_choice() const;

    virtual bool has_default_choice() const;

    virtual int default_choice() const;

    int identify(const qpp_param_array & q, metaparam_structure & s);

    virtual STRING category() const;

    virtual int n_nested() const;

    virtual qpp_object* nested(int i) const;

    virtual void write(OSTREAM &os, int offset=0) const;    
    
    virtual qpp_object * copy() const;

  };

  // ---------------------------------------------------------------

  enum {
    mtprm_idf_OK     = 0,  // identified OK
    mtprm_idf_UNRGZ  = 1,  // unrecognized parameter
    mtprm_idf_RQNF   = 2,  // required parameter not found
    mtprm_idf_ILLVAL = 3,  // illegal parameter value
    mtprm_idf_RPXPTD = 4,  // another repetition expected
    mtprm_idf_OUTRNG = 5,  // index out of range
    mtprm_idf_ILLOBJ = 6,  // illegal object
    mtprm_idf_URQNF  = -1  // optional parameter not found
  };

  STRING metaparam_idf_error(int code);
  
  // -----------------------------------------------------------------------

  template<class T>
  int metaparameter<T>::identify(const qpp_param_array & q, 
				 metaparam_structure & s, int & i1, int & i2)
  { 
    //debug
    /*
    std::cerr << "metaparameter::identify\n";
    write(std::cerr);
    std::cerr << " i1= " << i1 << " i2= " << i2 << " q= ";
    q.write(std::cerr);
    std::cerr << "\n";
    s.debug();
    */

    if (i1<0 || i1>=q.n_nested() || q.nested(i1)==NULL)
      return mtprm_idf_OUTRNG;

    bool typematch = q.nested(i1)->gettype() == qtype_parameter + qtype_data<T>::type;

    // fixme - remove kostyl
    bool double2float = (qtype_data<T>::type == qtype_data_float) &&
      (q.nested(i1)->gettype() == qtype_parameter + qtype_data_double);
    bool int2real = (qtype_data<T>::type & ( qtype_data_float + qtype_data_double )) &&
      (q.nested(i1)->gettype() == qtype_parameter + qtype_data_int);

    /*
    qppobject_type ptype = q.nested(i1)->gettype() & qtype_data_all;
    bool typematch = (q.nested(i1)->gettype() == qtype_parameter + ptp) && 
      qtype_convertable(qtype_data<T>::type, ptype);
    */
    bool res = false;
    int code = required? mtprm_idf_RQNF : mtprm_idf_URQNF;
    T val;
    int ival;
    STRING nm = name();

    if (typematch || double2float || int2real)
      {
	qpp_object * p = q.nested(i1);
	
	if (name()=="*")
	  {
	    res = true;
	    nm = p->name();
	  }
	else if (name()==p->name() || p->name() =="" )
	  res = true;
	else
	  for (int i=0; i<synonyms.size(); i++)
	    if (synonyms[i] == p->name())
	      {
		res = true;
		break;
	      }

	if (res)
	  {
	    // check that value is allowed
	    //	    val = qtype_convert<T>( p->value() );
	    if (typematch)
	      val = ((qpp_parameter<T>*)p)->value();
	    else if (double2float)
	      val = ((qpp_parameter<double>*)p)->value();
	    else if (int2real)
	      val = ((qpp_parameter<int>*)p)->value();
		     
	    if (values.size()>0)
	      {
		bool valfound = false;
		for (ival=0; ival<values.size(); ival++)
		  if (val == values[ival].value)
		    {
		      valfound = true;
		      s.choice = ival;
		      break;
		    }
		if (!valfound)
		  {
		    res = false;
		    code = mtprm_idf_ILLVAL;
		  }
	      }
	  }
      }

    bool checksynonyms;

    if (qtype_data<T>::type != qtype_data_string)
      checksynonyms = !typematch && q.nested(i1)->gettype() == qtype_parameter + qtype_data_string;
    else
      checksynonyms = typematch;

    //debug
    //std::cerr << "identify chk0.1  checksynonyms= " << checksynonyms <<  "\n";

    if (!res && checksynonyms)
      // Check value synonyms
      {
	qpp_parameter<STRING> * p = (qpp_parameter<STRING> *)(q.nested(i1));
	bool valfound=false;
	for (ival = 0; ival<values.size(); ival++)
	  {
	    for (int isyn = 0; isyn < values[ival].synonyms.size(); isyn++)
	      if ( p->value() == values[ival].synonyms[isyn] )
		{
		  valfound = true;
		  break;
		}

	    if (qtype_data<T>::type == qtype_data_string)
	      if ( ((qpp_parameter<T>*)q.nested(i1))->value() == values[ival].value )
		valfound = true;

	    //debug
	    //std::cerr << "identify chk0.2 ival= " << ival << " val= " << values[ival].value << " p= ";
	    //p-> write(std::cerr);
	    //std::cerr << " type= " << std::hex << p->gettype() << std::dec << " p->value= " 
	    //<< p->value() << " valfound= " << valfound <<  "\n";

	    if (valfound) break;
	  }

	if (valfound)
	  {
	    res = true;
	    code = mtprm_idf_OK;
	    //val = qtype_convert<T>(values[ival].value);
	    val = values[ival].value;
	    s.choice = ival;
	  }

      }

    //debug
    //std::cerr << "identify chk1 code= " << code << " i1= " << i1 << " i2= " << i2 << "\n";

    if (res)
      {
	s.instance = new qpp_parameter<T>(nm, val);
	//debug
	//std::cerr << "metaparam::identify chk1.5\n ";
	// Check nested

	metaparam_block * nest = NULL;
	qpp_param_array * np = (qpp_param_array*)q.nested(i1);

	//debug
	/*
	std::cerr << "metaparam::identify chk2 ";
	s.instance->write(std::cerr);
	std::cerr << "\n";
	*/


	if (_nested!=NULL)
	  {
	    nest = _nested;
	    ival = 0;
	  }
	else if (values.size()>0)
	  nest = values[ival]._nested;

	//debug
	/*
	std::cerr << "metaparam::identify chk2.5 nested = ";
	if (nest==NULL)
	  std::cerr << "NULL";
	else
	  nest->write(std::cerr);
	std::cerr << "\n";
	*/
	if (nest != NULL)
	  {
	    int j1=0, j2 = -1;
	    s.create_structure(ival);
	    code = nest -> identify(*np, *(s.rptns[0][ival]), j1, j2);
	    res = (code == 0);
	    if (res)
	      {
		res = (j2+1 == np->n_nested());
		if (!res)
		  code = mtprm_idf_UNRGZ;
	      }
	    
	  }
	else
	  {
	    res = (np->n_nested() == 0);
	    if (!res)
	      code = mtprm_idf_UNRGZ;
	  }

	if (res)
	  {
	    i2 = i1;	
	    code = mtprm_idf_OK;
	  }
      }

    //debug
    //std::cerr << "identify chk3 res= " << res << " i1= " << i1 << " i2= " << i2 << "\n";

    return code;

  }

    template <class T>
    T metaparam_structure::value()
    {
      if (instance != NULL && instance->gettype() == qtype_parameter | qtype_data<T>::type)
	return ((qpp_parameter<T>*)instance) -> value();
    }

    template <class T>
    void metaparam_structure::setvalue(const T & val)
    {
      if (instance == NULL)
	instance = new qpp_parameter<T>(producer->name(),val);
      else 
	((qpp_parameter<T>*)instance)->value() = val;
	
    }

};

#endif
