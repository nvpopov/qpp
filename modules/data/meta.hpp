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
    qmetrepeat
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

    void create_structure(int i_element, int i_repetition = 0);

    void create_all();

    void create_instance(void * val);

    bool create_instance(const STRING & s);

    void set_value(void * val);

    bool set_value(const STRING & s);

    bool is_array();

    bool is_repetition();

    bool is_selection();

    bool is_parameter();
 
    bool value_defined();

    bool defined();

    bool identify(qpp_object * parm);

    qpp_param_array * get_params();

    qpp_declaration * get_options();
  
    void debug(int offset=0, metaparam_structure * current=NULL);

  };

  // ----------------------------------------------------------

  class metaparam_block : public qpp_object
  {
  public:

    bool required;
 
    virtual bool identify(qpp_array & q) =0;

    virtual qmetatypes metatype() const =0;

    virtual int min_repetitions() const =0;

    virtual int max_repetitions() const =0;

    virtual bool has_value() const =0;

    virtual bool has_default_value() const =0;

    virtual qpp_object * create_parameter(void * val) const =0;

    virtual void change_parameter(qpp_object * parm, void * val) const =0;

    virtual void * string2val(const STRING & s) =0;

    metaparam_block(const STRING & __name = "", qpp_object * __owner = NULL, bool __required = false) :
      qpp_object(__name,__owner)
    {
      required = __required;
    }

    virtual qppobject_type gettype() const
    {
      return qtype_meta;
    }

    //std::vector<metaparam_structure*> instances;

  };

  // -------------------------------------------------------------

  metaparam_block * create_metaparam(qpp_declaration & q, qpp_object * owner = NULL);

  // -------------------------------------------------------------

  class metaparam_array : public metaparam_block
  {
  public:
    std::vector<metaparam_block*> array;

    metaparam_array(const STRING & __name = "", qpp_object * __owner = NULL, bool __required = false):
      metaparam_block(__name,__owner,__required)
    {}

    metaparam_array(qpp_declaration & decl, qpp_object * __owner = NULL) :
      metaparam_block(decl.name(),__owner)
    {
      required = false;
      for (int i=0; i<decl.n_nested(); i++)
	if (decl.nested(i)->gettype() & (qtype_parameter | qtype_data_bool))
	  {
	    qpp_parameter<bool> * rq = (qpp_parameter<bool> *)(decl.nested(i));
	    if (rq->name() == "required")
	      required = rq -> value();
	    else 
	      decl.error("unexpected option", decl.line(),decl.file());
	  }
	else if (decl.nested(i)->gettype() & qtype_declaration)
	  array.push_back(create_metaparam(*((qpp_declaration*)decl.nested(i)), this));
	else
	  decl.error("Only metaparameters declaration or \"required\" option are allowed here", 
		     decl.line(),decl.file());
    }

    virtual bool identify(qpp_array & q)
    {}

    virtual int min_repetitions() const
    {
      return required? 1:0;
    }

    virtual int max_repetitions() const
    {
      return 1;
    }

    virtual bool has_value() const
    {
      return false;
    }

    virtual bool has_default_value() const
    {
      return false;
    }

    virtual qpp_object * create_parameter(void * _val) const
    {
      return NULL;
    }

    virtual void change_parameter(qpp_object * parm, void * val) const
    {}

    virtual void * string2val(const STRING & s)
    {
      return NULL;
    }

    virtual qmetatypes metatype() const
    {
      return qmetarray;
    }

    virtual STRING category() const
    {
      return "metaparam_array";
    }

    virtual int n_nested() const
    {
      return array.size();
    }

    virtual qpp_object* nested(int i) const
    {
      return array[i];
    }

    virtual void write(OSTREAM &os, int offset=0) const
    {
      for (int i=0; i<offset; i++)
	os << " ";
      if ( category() != "" && name() != "")
	os << category() << " " << name();
      else
	os << category() << name();
      os << "\n";
      for (int i=0; i<offset+2; i++)
	os << " ";
      os << "{\n";
      for (int i=0; i<offset+4; i++)
	os << " ";
      os << "required = " << (required? "yes" : "no") << ";\n";
      for (int i=0; i<array.size(); i++)
	array[i]->write(os,offset+4);
      for (int i=0; i<offset+2; i++)
	os << " ";
      os << "}\n";
    }

    virtual qpp_object * copy() const
    {
      return new metaparam_array(*this);
    }

  };


  // -------------------------------------------------------------

  class metaparam_repeat : public metaparam_array
  {
  public:

    int min_rep, max_rep;

    metaparam_repeat(const STRING & __name = "", qpp_object * __owner = NULL, bool __required = false):
      metaparam_array(__name,__owner,__required)
    {
      min_rep = 0;
      max_rep = -1;
    }

    metaparam_repeat(qpp_declaration & decl, qpp_object * __owner = NULL) :
      metaparam_array(decl.name(),__owner)
    {
      int n = decl.n_nested();
      bool used[n];
      for (int i=0; i<n; i++)
	used[i] = false;

      required = false;
      min_rep = 0;
      max_rep = -1;
      
      qpp_object *p = decl.getobject("required",qscope_local);
      if (p!=NULL)
	{
	  if ( p->gettype() == (qtype_parameter | qtype_data_bool))
	    required = ((qpp_parameter<bool>*)p) -> value();
	  else
	    p->error("Illegal \"required\" declaration", decl.line(), decl.file());
	  
	  used[decl.obj_index(p)] = true;
	}
      
      p = decl.getobject("repeat_min",qscope_local);      
      if (p!=NULL)
	{
	  if ( p->gettype() == (qtype_parameter | qtype_data_int))
	    min_rep = ((qpp_parameter<int>*)p) -> value();
	  else
	    p->error("Illegal \"repeat_min\" declaration", decl.line(), decl.file());
	  
	  used[decl.obj_index(p)] = true;
	}

      p = decl.getobject("repeat_max",qscope_local);      
      if (p!=NULL)
	{
	  if ( p->gettype() == (qtype_parameter | qtype_data_int))
	    max_rep = ((qpp_parameter<int>*)p) -> value();
	  else
	    p->error("Illegal \"repeat_max\" declaration", decl.line(), decl.file());
	  
	  used[decl.obj_index(p)] = true;
	}
      
      for (int i=0; i<n; i++)
	if (!used[i])
	  {
	    if (decl.nested(i)->gettype() & qtype_declaration)
	      array.push_back(create_metaparam(*((qpp_declaration*)decl.nested(i)), this));
	    else
	      decl.error("Only metaparameters declaration or \"required\" option are allowed here", 
			 decl.line(),decl.file());
	  }
    }

    virtual bool identify(qpp_array & q)
    {}

    virtual int min_repetitions() const
    {
      return min_rep;
    }

    virtual int max_repetitions() const
    {
      return max_rep;
    }

    virtual qmetatypes metatype() const
    {
      return qmetrepeat;
    }

    virtual STRING category() const
    {
      return "metaparam_repeat";
    }

    virtual int n_nested() const
    {
      return array.size();
    }

    virtual qpp_object* nested(int i) const
    {
      return array[i];
    }

    virtual void write(OSTREAM &os, int offset=0) const
    {
      for (int i=0; i<offset; i++)
	os << " ";
      if ( category() != "" && name() != "")
	os << category() << " " << name();
      else
	os << category() << name();
      os << "\n";
      for (int i=0; i<offset+2; i++)
	os << " ";
      os << "{\n";

      for (int i=0; i<offset+4; i++) os << " ";
      os << "required = " << (required? "yes" : "no") << ";\n";

      for (int i=0; i<offset+4; i++) os << " ";
      os << "repeat_min = " << min_rep << ";\n";

      for (int i=0; i<offset+4; i++) os << " ";
      os << "repeat_max = " << max_rep << ";\n";

      for (int i=0; i<array.size(); i++)
	array[i]->write(os,offset+4);
      for (int i=0; i<offset+2; i++)
	os << " ";
      os << "}\n";
    }

    virtual qpp_object * copy() const
    {
      return new metaparam_repeat(*this);
    }

  };
  // -------------------------------------------------------------

  class metaparam_select : public metaparam_array
  {
  public:

    int dflt;

    metaparam_select(const STRING & __name = "", qpp_object * __owner = NULL, bool __required = false):
      metaparam_array(__name,__owner,__required)
    {
      dflt = 0;
    }

    metaparam_select(qpp_declaration & decl, qpp_object * __owner = NULL) :
      metaparam_array(decl.name(),__owner)
    {
      int n = decl.n_nested();
      bool used[n];
      for (int i=0; i<n; i++)
	used[i] = false;

      required = false;
      dflt = 0;
      
      qpp_object *p = decl.getobject("required",qscope_local);
      if (p!=NULL)
	{
	  if ( p->gettype() == (qtype_parameter | qtype_data_bool))
	    required = ((qpp_parameter<bool>*)p) -> value();
	  else
	    p->error("Illegal \"required\" declaration", decl.line(), decl.file());
	  
	  used[decl.obj_index(p)] = true;
	}
      
      p = decl.getobject("default",qscope_local);      
      if (p!=NULL)
	{
	  if ( p->gettype() == (qtype_parameter | qtype_data_int))
	    dflt = ((qpp_parameter<int>*)p) -> value();
	  else
	    p->error("Illegal \"repeat_min\" declaration", decl.line(), decl.file());
	  
	  used[decl.obj_index(p)] = true;
	}
      
      for (int i=0; i<n; i++)
	if (!used[i])
	  {
	    if (decl.nested(i)->gettype() & qtype_declaration)
	      array.push_back(create_metaparam(*((qpp_declaration*)decl.nested(i)), this));
	    else
	      decl.error("Only metaparameters declaration or \"required\" option are allowed here", 
			 decl.line(),decl.file());
	  }
    }

    virtual bool identify(qpp_array & q)
    {}

    virtual qmetatypes metatype() const
    {
      return qmetselect;
    }

    virtual STRING category() const
    {
      return "metaparam_select";
    }

    virtual int n_nested() const
    {
      return array.size();
    }

    virtual qpp_object* nested(int i) const
    {
      return array[i];
    }

    virtual void write(OSTREAM &os, int offset=0) const
    {
      for (int i=0; i<offset; i++)
	os << " ";
      if ( category() != "" && name() != "")
	os << category() << " " << name();
      else
	os << category() << name();
      os << "\n";
      for (int i=0; i<offset+2; i++)
	os << " ";
      os << "{\n";

      for (int i=0; i<offset+4; i++) os << " ";
      os << "required = " << (required? "yes" : "no") << ";\n";

      for (int i=0; i<offset+4; i++) os << " ";
      os << "default = " << dflt << ";\n";

      for (int i=0; i<array.size(); i++)
	array[i]->write(os,offset+4);
      for (int i=0; i<offset+2; i++)
	os << " ";
      os << "}\n";
    }

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
    
    bool val_list;

    struct val_record{
      T* value;
      std::vector<STRING> synonyms;      
      metaparam_block * _nested;
    };
    
    std::vector<val_record> values; 
    
    virtual int min_repetitions() const
    {
      return required? 1:0;
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

    virtual bool identify(qpp_array & q)
    {}

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
      int n=0;
      if (_nested != NULL) n++;
      return n;
    }

    virtual qpp_object* nested(int i) const
    {
      if (i==0 && _nested != NULL)
	return _nested;
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
	  os << "default = " << (t2s<T>(*val_default)) << ";\n";
	}

      if (_nested != NULL)
	_nested -> write(os,offset+4);

      if (values.size()>0)
	for (int i=0; i<values.size(); i++)
	  {
	    for (int k=0; k<offset+4; k++) os << " ";
	    os << "value(" << *(values[i].value) << ")\n";
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
	  if ( p->gettype() == (qtype_parameter | qtype_data<T>::type))
	    {
	      is_default = true;
	      val_default = new T(((qpp_parameter<T>*)p) -> value());
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
	    val_record vrec;
	    vrec.value = new T(((qpp_parameter<T>*)vdecl->param(0))->value());

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
	    
	    
	    values.push_back(vrec);
	  }
    }
    
  };

  metaparam_block * create_metaparam(qpp_declaration & q, qpp_object * owner)
  {
    STRING cat = q.category();
    if (cat == "metaparam_array")
      return new metaparam_array(q,owner);
    else if (cat == "metaparam_select")
      return new metaparam_select(q,owner);
    else if (cat == "metaparam_repeat")
      return new metaparam_repeat(q,owner);
    else if (cat == "metaparameter")
      {
	STRING tp;
	bool found = q.parameters()->getparamvalue<STRING>(tp,"type",qscope_local);
	if (!found)
	  tp = "string";
	if (tp == "int")
	  return new metaparameter<int>(q,owner);
	else if (tp == "bool")
	  return new metaparameter<bool>(q,owner);
	else if (tp == "double")
	  return new metaparameter<double>(q,owner);
	else if (tp == "float")
	  return new metaparameter<float>(q,owner);
	else if (tp == "string")
	  return new metaparameter<STRING>(q,owner);
      }
    else q.error("metaparameter declaration expected", q.line(), q.file());
  }

  // ---------------------------------------------------------
  metaparam_structure::metaparam_structure(metaparam_block *__producer,
					 metaparam_structure * __owner)
  {
    producer = __producer;
    owner = __owner;
    instance = NULL;
    //producer->instances.push_back(this);
    for (int i=0; i<producer->min_repetitions(); i++)
      add_repetition();
    choice=0;
    if (producer->metatype()==qmetselect)
      choice = ((metaparam_select*)producer) -> dflt;
  }

  void metaparam_structure::add_repetition()
  {
    int n = rptns.size();
    rptns.resize(n+1);
    for (int i=0; i<producer->n_nested(); i++)
      rptns[n].push_back(NULL);
  }

  void metaparam_structure::insert_repetition(int i)
  {
    std::vector<metaparam_structure*> empty;
    rptns.insert(rptns.begin()+i,empty);
    for (int j=0; j<producer->n_nested(); j++)
      rptns[i].push_back(NULL);
  }

  void metaparam_structure::erase_repetition(int i)
  {
    rptns.erase(rptns.begin()+i);
  }

  bool metaparam_structure::possible_to_add()
  {
    return (producer->max_repetitions()==-1) || (producer->max_repetitions()>rptns.size() );
  }

  bool metaparam_structure::possible_to_erase()
  {
    return producer->min_repetitions() < rptns.size();
  }

  int metaparam_structure::min_repeatitions()
  {
    return producer->min_repetitions();
  }

  int metaparam_structure::max_repeatitions()
  {
    return producer->max_repetitions();
  }

  int metaparam_structure::n_repetitions()
  {
    return rptns.size();
  }

  int metaparam_structure::n_elements(int i_rep)
  {
    return rptns[i_rep].size();
  }

  bool metaparam_structure::element_exist(int i_element, int i_repetition)
  {
    return i_repetition < rptns.size() && 
			  i_element < rptns[i_repetition].size();
  }

  metaparam_structure * metaparam_structure::element(int i_element, int i_repetition) 
  {
    if (i_repetition < rptns.size() &&
	i_element < rptns[i_repetition].size() )
      return rptns[i_repetition][i_element];
    else
      return NULL;
  }

  void metaparam_structure::create_structure(int i_element, int i_repetition)
  {
    if (i_repetition > rptns.size())
      return;
    if (i_element > rptns[i_repetition].size())
      return;
    metaparam_structure *p = 
      new metaparam_structure((metaparam_block*)(producer->nested(i_element)),this);
    rptns[i_repetition][i_element] = p;
    if (p->producer->metatype() == qmetselect)
      p->create_structure(p->choice);
    else
      for (int ii=0; ii < p->rptns.size(); ii++)
	for (int jj=0; jj < p->rptns[ii].size(); jj++)
	  p->create_structure(jj,ii);
  }
  
  void metaparam_structure::create_all()
  {
    if (is_selection())
      create_structure(choice);
    else
      for (int i=0; i<rptns.size(); i++)
	for (int j=0; j<rptns[i].size(); j++)
	  create_structure(j,i);
  }

  void metaparam_structure::create_instance(void * val)
  {
    instance = producer -> create_parameter(val);
  }

  bool metaparam_structure::create_instance(const STRING & s)
  {
    void * val = producer->string2val(s);
    if (val!=NULL)
      {
	create_instance(val);
	return true;
      }
    else
      return false;
  }

  void metaparam_structure::set_value(void * val)
  {
    producer -> change_parameter(instance,val);
  }

  bool metaparam_structure::set_value(const STRING & s)
  {    
    void * val = producer->string2val(s);
    if (val!=NULL)
      {
	set_value(val);
	return true;
      }
    else
      return false;
  }

  bool metaparam_structure::is_array()
  {
    return producer->metatype() == qmetarray;
  }

  bool metaparam_structure::is_repetition()
  {
    return producer->metatype() == qmetrepeat;
  }

  bool metaparam_structure::is_selection()
  {
    return producer->metatype() == qmetselect;
  }

  bool metaparam_structure::is_parameter()
  {
    return producer->has_value();
  }
 
  bool metaparam_structure::value_defined()
  {
    if (!is_parameter())
      return false;
    else if (instance!=NULL)
      return true;
    else
      return producer->has_default_value();
  }

  bool metaparam_structure::defined()
  {
    if (producer->metatype() == qmetselect)
      return rptns[0][choice]->defined();
    else if (producer->metatype() == qmetparam)
      // fixme - various nested paramblocks!
      {
	bool nest_defined = true;
	if (producer->nested(0) != NULL)
	  nest_defined = rptns[0][0]->defined();
	return value_defined() && nest_defined;
      }
    else
      {
	for (int i=0; i<rptns.size(); i++)
	  for (int j=0; j<rptns[i].size(); j++)
	    if (!rptns[i][j]->defined())
	      return false;

	return true;
      }
  }
  
  bool metaparam_structure::identify(qpp_object * parm)
  {}

  qpp_param_array * metaparam_structure::get_params()
  {}

  qpp_declaration * metaparam_structure::get_options()
  {}

  void metaparam_structure::debug(int offset, metaparam_structure * current)
  {
    if (this==current)
      std::cout << "\033[1;31m";

    if (producer->metatype()==qmetparam)
      {
	if (instance==NULL)
	  {
	    STRING s=producer->name();
	    if (split(s).size()!=1)
	      s = "\'" + s + "\'";
	    std::cout << s << " = NULL\n";
	  }
	else
	  {
	    instance->write(std::cout);
	    if (n_repetitions()>0)
	      {
		std::cout << "\n";
		for (int i=0; i<offset; i++)
		  std::cout << " ";
		std::cout << "-------- nested ---------";
	      }
	    std::cout << "\n";
	  }
      }
    else if (producer->metatype()==qmetselect)
      {
	//	for (int k=0; k<offset; k++) std::cout << " ";
	std::cout << "selection = " << choice << "\n";
	for (int k=0; k<offset; k++) std::cout << " ";
      }
    else
      {
	if (producer->metatype()==qmetarray)
	  std::cout << "--- array ---\n";
	else
	  std::cout << "--- repetition ---\n";
      }
    for (int i=0; i<rptns.size(); i++)
      {
	for (int j=0; j<rptns[i].size(); j++)
	  {
	    for (int k=0; k<offset; k++) std::cout << " ";	    
	    if (producer->metatype()==qmetrepeat)
	      std::cout << i << "." << j << ". ";
	    else
	      std::cout << j << ". ";
	    if (rptns[i][j]==NULL)
	      {
		for (int k=0; k<offset; k++) std::cout << " ";
		std::cout << "undefined\n";
	      }
	    else
	      rptns[i][j]->debug(offset+2,current);
	  }
      }
    if (this==current)
      std::cout << "\033[0m";
  }
  
};

#endif
