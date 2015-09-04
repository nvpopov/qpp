#include "meta.hpp"

namespace qpp{
  

  metaparam_block::metaparam_block(const STRING & __name, qpp_object * __owner, 
				   bool __required) : qpp_object(__name,__owner)
  {
    required = __required;
  }
  
  qppobject_type metaparam_block::gettype() const
  {
    return qtype_meta;
  }
  
  int metaparam_block::n_param() const
  {  return 0; }
  
  void metaparam_block::set_n_param(int n)
  {}
  
  // -------------------------------------------------------------


  metaparam_array::metaparam_array(const STRING & __name, qpp_object * __owner, 
				   bool __required) : metaparam_block(__name,__owner,__required)
  {}

  metaparam_array::metaparam_array(qpp_declaration & decl, qpp_object * __owner) :
    metaparam_block(decl.name(),__owner)
  {
    //debug
    //std::cerr << "--- metaparam array constructor ---\n";

    required = true;
    for (int i=0; i<decl.n_nested(); i++)
      if (decl.nested(i)->gettype() & (qtype_parameter | qtype_data_bool))
	{
	  qpp_parameter<bool> * od = (qpp_parameter<bool> *)(decl.nested(i));
	  if (od->name() == "ordered")
	    ordered = od -> value();
	  else 
	    decl.error("unexpected option", decl.line(),decl.file());
	}
      else if (decl.nested(i)->gettype() & qtype_declaration)
	array.push_back(create_metaparam(*((qpp_declaration*)decl.nested(i)), this));
      else
	decl.error("Only metaparameters declaration or \"ordered\" option are allowed here", 
		   decl.line(),decl.file());
    //debug
    //std::cerr << "--- metaparam array constructor: finished ---\n";
  }

  int metaparam_array::min_repetitions() const
  {
    return 1;
  }

  int metaparam_array::max_repetitions() const
  {
    return 1;
  }

  bool metaparam_array::has_value() const
  {
    return false;
  }

  bool metaparam_array::has_default_value() const
  {
    return false;
  }

  qpp_object* metaparam_array::default_param() const
  { return NULL; }


  bool metaparam_array::has_value_list() const
  {
    return false;
  }

  bool metaparam_array::has_choice() const
  { return false;}

  bool metaparam_array::has_default_choice() const
  { return false;}

  int metaparam_array::default_choice() const
  { return -1;}

  void metaparam_array::value_list(std::vector<STRING> & vals)
  {}

  qmetatypes metaparam_array::metatype() const
  {
    return qmetarray;
  }

  STRING metaparam_array::category() const
  {
    return "metaparam_array";
  }

  int metaparam_array::n_nested() const
  {
    return array.size();
  }

  qpp_object* metaparam_array::nested(int i) const
  {
    return array[i];
  }

  void metaparam_array::write(OSTREAM &os, int offset) const
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

  qpp_object * metaparam_array::copy() const
  {
    return new metaparam_array(*this);
  }


  // -------------------------------------------------------------


  metaparam_repeat::metaparam_repeat(const STRING & __name , qpp_object * __owner, 
				     bool __required): metaparam_array(__name,__owner,__required)
  {
    min_rep = 0;
    max_rep = -1;
  }

  metaparam_repeat:: metaparam_repeat(qpp_declaration & decl, qpp_object * __owner) :
    metaparam_array(decl.name(),__owner)
  {
    //debug
    //std::cerr << "--- metaparam repeat constructor ---\n";

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
    //debug
    //std::cerr << "--- metaparam repeat constructor: finished ---\n";
  }

  int metaparam_repeat::min_repetitions() const
  {
    return min_rep;
  }

  int metaparam_repeat::max_repetitions() const
  {
    return max_rep;
  }

  qmetatypes metaparam_repeat::metatype() const
  {
    return qmetrepeat;
  }

  STRING metaparam_repeat::category() const
  {
    return "metaparam_repeat";
  }

  int metaparam_repeat::n_nested() const
  {
    return array.size();
  }

  qpp_object* metaparam_repeat::nested(int i) const
  {
    return array[i];
  }

  void metaparam_repeat::write(OSTREAM &os, int offset) const
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

  qpp_object * metaparam_repeat::copy() const
  {
    return new metaparam_repeat(*this);
  }

  // -------------------------------------------------------------


  metaparam_select::metaparam_select(const STRING & __name, qpp_object * __owner, 
				     bool __required):metaparam_array(__name,__owner,__required)
  {
    dflt = 0;
  }

  metaparam_select::metaparam_select(qpp_declaration & decl, qpp_object * __owner) :
    metaparam_array(decl.name(),__owner)
  {
    //debug
    //std::cerr << "--- metaparam select constructor ---\n";

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
    //debug
    //std::cerr << "--- metaparam select constructor: finished ---\n";
  }

  qmetatypes metaparam_select::metatype() const
  {
    return qmetselect;
  }

  bool metaparam_select::has_choice() const
  { return true; }

  bool metaparam_select::has_default_choice() const
  { return true; }

  int metaparam_select::default_choice() const
  { return dflt; }

  STRING metaparam_select::category() const
  {
    return "metaparam_select";
  }

  int metaparam_select::n_nested() const
  {
    return array.size();
  }

  qpp_object* metaparam_select::nested(int i) const
  {
    return array[i];
  }

  void metaparam_select::write(OSTREAM &os, int offset) const
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

  qpp_object * metaparam_select::copy() const
  {
    return new metaparam_select(*this);
  }

  // -------------------------------------------------------------
 
  metaparam_object::metaparam_object(qppobject_type _mask, const STRING & __name, 
				     qpp_object * __owner, bool __required):
    metaparam_block(__name,__owner,__required)
  {mask = _mask;}

  metaparam_object::metaparam_object(const metaparam_object & q):
    metaparam_block(q.name(), q.owner(), q.required)
  {
    mask = q.mask;
  }

  metaparam_object::metaparam_object(qpp_declaration & decl, qpp_object * __owner) :
    metaparam_block(decl.name(),decl.owner())
  {
    qpp_parameter<bool> * preq = decl.parameter<bool>("required",qscope_local);
    if (preq!=NULL)
      required = preq->value();
    else
      required = false;

    qpp_parameter<STRING> * pmask = decl.parameter<STRING>("mask",qscope_local);
    
    if (pmask!=NULL)
      {
	//read hexidecimal
	SSTREAM s(pmask->value());
	s >> std::hex >> mask;
      }
    else
      mask = ~0x0;
  }

  qmetatypes  metaparam_object::metatype() const
  { return qmetobject;}

  int  metaparam_object::min_repetitions() const
  { return 0;}

  int  metaparam_object::max_repetitions() const
  { return 0;}

  bool  metaparam_object::has_value() const
  { return false;}

  bool  metaparam_object::has_default_value() const
  { return false;}

  qpp_object* metaparam_object:: default_param() const
  { return NULL;}
  
  bool  metaparam_object::has_value_list() const
  { return false;}

  void  metaparam_object::value_list(std::vector<STRING> & vals)
  {}

  bool  metaparam_object::has_choice() const
  { return false;}

  bool  metaparam_object::has_default_choice() const
  { return false;}

  int  metaparam_object::default_choice() const
  { return 0;}

  STRING metaparam_object::category() const
  {
    return "metaparam_object";
  }

  int metaparam_object::n_nested() const
  {
    return 0;
  }

  qpp_object* metaparam_object::nested(int i) const
  {
    return NULL;
  }

  void metaparam_object::write(OSTREAM &os, int offset) const
  {
    for (int i=0; i<offset; i++)
      os << " ";
    if ( category() != "" && name() != "")
      os << category() << " " << name();
    else
      os << category() << name();
    os << "( required = " << (required? "yes" : "no") << ", " 
       << "mask = 0x" << std::hex << mask << std::dec << ");\n";
  }

  qpp_object * metaparam_object::copy() const
  {
    return new metaparam_object(*this);
  }

  // -------------------------------------------------------------

  metaparam_block * create_metaparam(qpp_declaration & q, qpp_object * owner)
  {
    STRING cat = q.category();

    //debug
    //std::cerr << "--- create metaparam: " << cat << " " << q.name() << "\n";

    if (cat == "metaparam_array")
      return new metaparam_array(q,owner);
    else if (cat == "metaparam_select")
      return new metaparam_select(q,owner);
    else if (cat == "metaparam_repeat")
      return new metaparam_repeat(q,owner);
    else if (cat == "metaparam_object")
      return new metaparam_object(q,owner);
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
    if (producer->has_choice() && producer->has_default_choice())
      choice = producer -> default_choice();
    if (producer->metatype()==qmetparam && producer->has_default_value())
      {
	instance = producer -> default_param();
      }
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

  metaparam_structure * metaparam_structure::parameter(const STRING & pname)
  {
    for (int i=0; i<rptns.size(); i++)
      for (int j=0; j<rptns[i].size(); j++)
	{
	  metaparam_structure * res = rptns[i][j];
	  if ( res!=NULL && res->is_parameter() && res->producer->name() == pname)
	    return res;
	}
    return NULL;
  }

  void metaparam_structure::create_structure(int i_element, int i_repetition)
  {
    //debug
    //std::cerr << "create_structure alive1\n";

    if (i_repetition >= rptns.size())
      return;

    //std::cerr << "create_structure alive1.1 irep=" << i_repetition << " idx=" << i_element << "\n";
    //" size=" << rptns[i_repetition].size() << "\n";

    if (i_element >= rptns[i_repetition].size())
      return;

    //std::cerr << "create_structure alive1.2\n";

    if (producer->nested(i_element) == NULL)
      {
	rptns[i_repetition][i_element] = NULL;
	//debug
	//std::cerr << "create_structure alive2\n";
	return;
      }

    //debug
    //std::cerr << "create_structure alive1.3\n";
    //producer->nested(i_element)->write(std::cerr);
    //std::cerr << "--------------------\n";
    

    metaparam_structure *p = 
      new metaparam_structure((metaparam_block*)(producer->nested(i_element)),this);
    rptns[i_repetition][i_element] = p;

    //    if (p->producer->metatype() == qmetselect)
    //p->create_structure(p->choice);
    /*
      if (p->producer->has_choice())
      {
      //debug
      p->producer->write(std::cerr);
      std::cerr << "choice = " << p->choice << "\n";

      p->create_structure(p->choice);
      }
      else
    */

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

  /*
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
  */
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
	int i;

	if (producer -> has_choice() )
	  i = choice;
	else
	  i = 0;

	if (producer->nested(i) != NULL)
	  nest_defined = rptns[0][i]->defined();

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

  /*  
      bool metaparam_structure::identify(qpp_object * parm)
      {}
  */

  qpp_param_array * metaparam_structure::get_params()
  {
    //debug
    //std::cerr << "---- get_param begin-----\n";
    //debug(0,this);

    qpp_param_array * res;
    if (producer->metatype()==qmetparam)
      res = (qpp_param_array*)instance;
    else
      res = new qpp_param_array;
    bool has_choice = producer -> has_choice();
    //(producer->metatype() == qmetselect) ||
    //(producer->metatype()==qmetparam && producer->n_nested()>0);
    
    if (has_choice)
      {
	qpp_param_array * sub = rptns[0][choice]->get_params();
	if (sub == NULL)
	  {
	    // Check for required parameters
	  }
	else if (sub->gettype() & qtype_parameter)
	  {
	    // debug
	    /*
	      std::cerr << "adding sub: type= " << std::hex << sub->gettype() << std::dec << " ";
	      sub->write(std::cerr);
	      std::cerr << "\nto res: ";
	      res->write(std::cerr);
	    */
	    res->add(*sub);

	    //debug
	    //std::cerr << "alive\n";
	  }
	else
	  {
	    for (int k=0; k<sub->n_nested(); k++)
	      {
		//debug
		/*
		  std::cerr << "adding nested: type= " << std::hex << 
		  sub->nested(k)->gettype() << std::dec << " ";
		  sub ->nested(k) ->write(std::cerr);
		  std::cerr << "\nto res: ";
		  res->write(std::cerr);
		*/
		res->add(* sub->nested(k));
		
		//debug
		//std::cerr<<"alive\n";
	      }
	    delete sub;
	    
	  }
      }
    else
      for (int i=0; i<rptns.size(); i++)
	for (int j=0; j<rptns[i].size(); j++)
	  {
	    qpp_param_array * sub = rptns[i][j]->get_params();
	    if (sub == NULL)
	      {
		//check for required parameters
	      }
	    else if (sub->gettype() & qtype_parameter)
	      {
		// debug
		/*
		std::cerr << "adding sub: type= " << std::hex << sub->gettype() << std::dec << " ";
		sub->write(std::cerr);
		std::cerr << "\nto res: ";
		res->write(std::cerr);
		*/
		res->add(*sub);

		//debug
		//std::cerr << "\nalive\n";
	      }
	    else
	      {
		for (int k=0; k<sub->n_nested(); k++)
		  {
		    //debug
		    /*
		    std::cerr << "adding nested: type= " << std::hex << 
		      sub->nested(k)->gettype() << std::dec << " ";
		    sub ->nested(k) ->write(std::cerr);
		    std::cerr << "\nto res: ";
		    res->write(std::cerr);
		    */
		    res->add(* sub->nested(k));
		    
		    //debug
		    //std::cerr<<"alive\n";
		  }
		delete sub;
	      }
	  }

    return res;
  }

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
	    std::cout << s << " = NULL";
	  }
	else
	  {
	    instance->write(std::cout);
	    /*
	      if (has_default_value())
	      {
	      std::cout 
	      }
	    */
	  }
	int nelem=0;
	for (int i=0; i<rptns.size(); i++)
	  nelem += rptns[i].size();
	if (nelem>0 )
	  {
	    std::cout << "\n";
	    for (int i=0; i<offset; i++)
	      std::cout << " ";
	    std::cout << "-------- nested choice = " << choice << " ---------";
	  }
	std::cout << "\n";
	  
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
      //if (producer->metatype()!=qmetselect || choice == i)
      {
	bool choiceonly = producer -> has_choice();
	/*false;
	  if (producer->metatype()==qmetselect) 
	  choiceonly = true;
	  if (producer->metatype()==qmetparam && producer->n_nested()>0)
	  choiceonly = true;
	*/
	for (int j=0; j<rptns[i].size(); j++)
	  //if (!choiceonly || j == choice)
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

  // ---------------------------------------------------------------
  
  int metaparam_array::identify(const qpp_param_array & q, 
				metaparam_structure & s, int & i1, int & i2)
  { 
    //debug
    /*
    std::cerr << "metaparam_array::identify\n";
    write(std::cerr);
    std::cerr << " i1= " << i1 << " i2= " << i2 << " q= ";
    q.write(std::cerr);
    std::cerr << "\n";
    s.debug();
    */
    // 1. ordered case
    if (ordered)
      {
	int j1=i1, j2=i1;
	for (int k = 0; k<array.size(); k++)
	  // identify k-th element
	  {
	    s.create_structure(k);

	    //debug
	    /*
	    std::cerr << "metaparam_array idf chk0 k= " << k << "\n";
	    array[k]->write(std::cerr);
	    q.nested(i1)->write(std::cerr);
	    std::cerr << "\n";
	    */

	    int code = array[k]->identify(q,*(s.rptns[0][k]),j1,j2);
	    bool success = (code==0);

	    if (!success && array[k]->required)
	      return mtprm_idf_RQNF;

	    //debug
	    //std::cerr << "metaparam_array idf chk1 k= " << k << " code= " << code << "\n";

	    if (!success && array[k]->has_default_value())
	    s.rptns[0][k]->instance = array[k]->default_param();

	    if (success)
	      {
		j1 = j2+1;
		j2 = j1;
	      }
	  }
	i2 = j2-1;

	//debug
	/*
	std::cerr << "metaparam_array idf return OK i1= " << i1 << " i2=" << i2  << " q= ";
	q.write(std::cerr);
	std::cerr << "\n";
	s.debug();
	*/

	return mtprm_idf_OK;
	
      }
    // 2. non-ordered case
    else
      {
	//fixme - implement
      }
  }

  // -----------------------------------------------------------------------

  int metaparam_repeat::identify(const qpp_param_array & q, 
				 metaparam_structure & s, int & i1, int & i2)
  { 
    //debug
    /*
    std::cerr << "metaparam_repeat::identify\n";
    write(std::cerr);
    std::cerr << " i1= " << i1 << " i2= " << i2 << " q= ";
    q.write(std::cerr);
    std::cerr << "\n";
    s.debug();
    */
    int n_rep=0;
    int jj1=i1, j1=i1, jj2=i2, j2=i1;
    bool broken = false;	
    int code = 0;

    while (n_rep <= max_rep || max_rep<0 )
      {
	jj1 = j1;
	jj2 = j2;
	if (n_rep >= min_rep)
	  s.add_repetition();
	
	//debug
	//std::cerr << " chk1 -- n_rep = " << n_rep << "\n";
	
	for (int k = 0; k<array.size(); k++)
	  // identify k-th element
	  {

	    //debug
	    //std::cerr << " chk2 -- n_rep = " << n_rep << " k= " << k << "\n";

	    s.create_structure(k,n_rep);

	    //debug
	    //std::cerr << " chk3 -- n_rep = " << n_rep << " k= " << k << "\n";
	    //s.rptns[n_rep][k]->debug();
	    
	    code = array[k]->identify(q,*(s.rptns[n_rep][k]),j1,j2);
	    bool success = (code == 0);

	    //debug
	    //std::cerr << " chk4\n";
	    //s.rptns[n_rep][k]->debug();

	    if (!success && array[k]->required)
	      {
		broken = true;
		break;
	      }

	    //if (!success && array[k]->has_default_value())
	    //s.rptns[0][k]->instance = array[k]->default_param();

	    if (success)
	      {
		j1 = j2+1;
		j2 = j1;
	      }
	  }

	// debug
	//std::cerr << "-------- n_rep = " << n_rep << " ------------- \n";
	//s.debug();

	if (broken) break;

	n_rep++;
      }
    
    if (n_rep < min_rep)
      return mtprm_idf_RPXPTD;

    if (broken)
      {
	i2 = jj2-1;
	s.erase_repetition(n_rep);
      }
    else
      i2 = j2-1;

    return mtprm_idf_OK;
	
  }

  // -----------------------------------------------------------------------

  int metaparam_select::identify(const qpp_param_array & q, 
				 metaparam_structure & s, int & i1, int & i2)
  { 

    int code;
    bool success = false;
    for (int k = 0; k < array.size(); k++)
      {
	if (s.element(k) == NULL)
	  s.create_structure(k);
	code = array[k]->identify(q,*(s.element(k)),i1,i2);
	if (code == mtprm_idf_OK)
	  {
	    success = true;
	    s.choice = k;
	    break;
	  }
      }
    
    if (success)
      return mtprm_idf_OK;
    else
      return required ? mtprm_idf_RQNF : mtprm_idf_URQNF;
  }

  int  metaparam_object::identify(const qpp_param_array & q, 
				  metaparam_structure & s, int & i1, int & i2)
  { 
    if (i1<0 || i1>=q.n_nested() || q.nested(i1)==NULL)
      return mtprm_idf_OUTRNG;
    
    if ( q.nested(i1)->gettype() & mask )
      {
	i2 = i1;
	s.instance = q.nested(i1);
	return mtprm_idf_OK;
      }
    else
      return mtprm_idf_ILLOBJ;
	
  }

  int metaparam_block::identify(const qpp_param_array & q, metaparam_structure & s)
  {
    int i1=0, i2=-1;
    int code = identify(q,s,i1,i2);
    if (code == 0 && i2+1 < q.n_nested())
      code = mtprm_idf_UNRGZ;
    return code;
  }

  STRING metaparam_idf_error(int code)
  {
    switch (code)
      {
      case mtprm_idf_OK:     return "Parameters identification OK";
      case mtprm_idf_UNRGZ:  return "Unrecognized parameter";
      case mtprm_idf_RQNF:   return "Required parameter not found";
      case mtprm_idf_ILLVAL: return "Illegal parameter value";
      case mtprm_idf_RPXPTD: return "Another parameters repetition expected";
      case mtprm_idf_OUTRNG: return "Parameters identification internal error: index out of range";
      case mtprm_idf_ILLOBJ: return "Illegal object (type mismatch)";
      case mtprm_idf_URQNF:  return "optional parameter not found";
      default: return "metaparm_idf_error(int code): unknown code";
      }
  }

};

