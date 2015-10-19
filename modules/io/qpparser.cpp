#include "io/qpparser.hpp"
#include <data/meta.hpp>
#include <data/globals.hpp>

namespace _qpp_internal
{

  qpp::qpp_param_array * create_parameter(const STRING & name, const STRING & value,
					  qpp::qpp_object *owner, int line, const STRING & file)
  {
    double dval;
    int ival;
    bool bval;

    bool perverse_real =  (value[0] == 'f' || value[0] == 'F');

    if (!perverse_real && s2t<int>(value,ival))
      return new qpp::qpp_parameter<int>(name, ival, owner, line, file);
    // important - all real numbers are being red as double
    else if ( !perverse_real && s2t<double>(value,dval))
      return new qpp::qpp_parameter<double>(name, dval, owner, line, file);
    else if (s2t<bool>(value,bval))
      return new qpp::qpp_parameter<bool>(name, bval, owner, line, file);
    else
      return new qpp::qpp_parameter<STRING>(name, value, owner, line, file);
  }

  STRING parse_quoted_string(qpp::tokenizer & tok)
  {
    tok.dump("");
    tok.separate("\"");
    STRING res = "", s;

    while ( (s = tok.get()) != "\"")
      {
	res += s;
	if (tok.eof())
	  qpp::global::root.error("Unexpected end of file", tok.line(), tok.file());
      }
    return res;
  }

  void parse_parameters(qpp::qpp_param_array & lst, qpp::tokenizer & tok)
  {
    //std::vector<qpp::qpp_object*> nested_lst;
    tok.dump(" \t");
    tok.separate(",;{}()=\"");

    STRING field1, field2, smb;
    bool first = true;
    lst.clear();

    do
      {
	bool nextparm = false, qstring = false, nested = false;

	field1 = tok.get();
	field2 = "";

	if ( field1.find_first_of(",;{}()\"") != std::string::npos )
	  {
	    if (field1 == ")" && first)
	      // empty parameter list
	      return;
	    else if (field1 == "\"")
	      // quoted string
	      {
		field1 = parse_quoted_string(tok);
		tok.dump(" \t");
		tok.separate(",;{}()=\"");		
		qstring = true;
	      }
	    else
	      lst.error("Incorrect parameter list", tok.line(), tok.file());
	  }

	// Check that field1 is identifier
	bool identif = !qstring && qpp::is_identifier(field1);
	
	smb = tok.get();

	if (!identif)
	  // , value, case
	  {
	    if ( smb != "," && smb != ")" )
	      lst.error("Incorrect parameter list (\',\' expected)", tok.line(), tok.file());
	    field2 = field1;
	    field1 = "";
	  }
	else
	  {
	    if (smb=="," || smb == ")")
	      // , value, case
	      {
		field2 = field1;
		field1 = "";
	      }
	    else if (smb=="=")
	      // , name=value case
	      {
		field2 = tok.get();
		if (field2 == "\"")
		  // quoted string
		  {
		    field2 = parse_quoted_string(tok);
		    tok.dump(" \t");
		    tok.separate(",;{}()=\"");		
		  }	
		smb = tok.get();
	      }

	    // Now smb can be only ',' or ')' (we are finished) or '(' (nested list)
	    if (smb=="(")
	      nested = true;
	    else if (smb != "," && smb != ")" )
	      lst.error("Incorrect parameter list (\',\' expected)", tok.line(), tok.file());
	  }

	qpp::qpp_param_array * pn = 
	  create_parameter(field1,field2,&lst,tok.line(),tok.file());
	
	if (nested)
	  {
	    parse_parameters(*pn, tok);
	    smb = tok.get();
	  }

	// consider obj(val) case separately
	if ( field2=="" && pn->n_nested()==1 && pn->nested(0)->name()=="" )
	  {
	    qpp::qpp_object *pval = pn->nested(0);
	    delete pn;
	    pval->setname(field1);
	    pval->setowner(&lst);
	    pn = (qpp::qpp_param_array*)pval;
	  }

	lst.add(*pn);

	if (smb == ")")
	  // We are finished
	  break;

	if (smb != ",")
	  lst.error("Error: \',\' expected in parameter list", tok.line(), tok.file());

      } while(true);

    //debug
    /*
      std::cout << "paramlist:";
      for (int i=0; i<lst.n_nested(); i++)
      lst.nested(i)->write(std::cerr);
      lst.write(std::cerr);
      std::cerr << "\n";
    */

    //    return lst;
  }

  qpp::qpp_object * parse_any_vectors(qpp::qpp_param_array & parm,
				      STRING name, qpp::tokenizer & tok,
				      qpp::qpp_object * owner)
  {
    //debug
    std::cerr << "parse_any_vectors: owner= " << owner->category() << " " << owner->name() << "\n";
    //std::cerr << "param owner = " << parm.owner()->category() << " " << parm.owner()->name() << "\n";

    //qpp::metaparam_block * vmeta = qpp::global::meta("vectors");
    //qpp::metaparam_structure vstr(vmeta);
    //int code = vmeta -> identify(parm,vstr);
    //if (code > 0)
    //owner -> error(qpp::metaparam_idf_error(code),tok.line(), tok.file());

    //if (!vstr.parameter("dim")->value_defined())
    //{

    qpp::qpp_parameter<int> *pdim = parm.parameter<int>("dim",qpp::qscope_global);
    if (pdim==NULL)
      owner->error("Dimension not defined", tok.line(), tok.file());
    int dim = pdim -> value();

    qpp::qpp_parameter<STRING> * pcreal = parm.parameter<STRING>("creal",qpp::qscope_global);
    if (pcreal==NULL)
      pcreal =  parm.parameter<STRING>("real",qpp::qscope_global);
    if (pcreal==NULL)
      owner->error("coordinate real not defined", tok.line(), tok.file());
    STRING real = pcreal -> value();

    //vstr.parameter("dim")->setvalue(dl->value());
    //}
    /*
      if (!vstr.parameter("creal")->value_defined())
      {
      if (rl == NULL)
      rl = owner -> parameter<STRING>("creal",qpp::qscope_global);
      vstr.parameter("creal")->setvalue(rl->value());
      }
    */
    //qpp::qpp_param_array * vparm = vstr.get_params();

    //int dim = ((qpp::qpp_parameter<int>*)vparm->nested(0))->value();
    //STRING real = ((qpp::qpp_parameter<STRING>*)vparm->nested(1))->value();
  
    if (real == "double")
      {
	switch(dim)
	  {
	  case 0:	return parse_vectors<0,double>(parm,name,tok,owner); break;
	  case 1: return parse_vectors<1,double>(parm,name,tok,owner); break;
	  case 2:	return parse_vectors<2,double>(parm,name,tok,owner); break;
	  case 3: return parse_vectors<3,double>(parm,name,tok,owner); break;
	  case 4: return parse_vectors<4,double>(parm,name,tok,owner); break;
	  case 5: return parse_vectors<5,double>(parm,name,tok,owner); break;
	  default: owner->error("dim must be before 0 and 5",tok.line(),tok.file());
	  }
      }
    else if (real == "float")
      {
	switch(dim)
	  {
	  case 0:	return parse_vectors<0,float>(parm,name,tok,owner); break;
	  case 1: return parse_vectors<1,float>(parm,name,tok,owner); break;
	  case 2:	return parse_vectors<2,float>(parm,name,tok,owner); break;
	  case 3: return parse_vectors<3,float>(parm,name,tok,owner); break;
	  case 4: return parse_vectors<4,float>(parm,name,tok,owner); break;
	  case 5: return parse_vectors<5,float>(parm,name,tok,owner); break;
	  default: owner->error("dim must be before 0 and 5",tok.line(),tok.file());
	  }
      }
    else
      owner->error("Bad real. Allowed values are \"double\" and \"float\"",tok.line(),tok.file());
  }

  qpp::qpp_object *parse_any_geom(qpp::qpp_param_array& parm, STRING name,
				  qpp::tokenizer & tok, qpp::qpp_object * owner)
  {
    qpp::qpp_parameter<int> *pdim = parm.parameter<int>("dim",qpp::qscope_global);
    if (pdim==NULL)
      owner->error("Dimension not defined", tok.line(), tok.file());
    int dim = pdim -> value();

    qpp::qpp_parameter<STRING> * pcreal = parm.parameter<STRING>("creal",qpp::qscope_global);
    if (pcreal==NULL)
      pcreal =  parm.parameter<STRING>("real",qpp::qscope_global);
    if (pcreal==NULL)
      owner->error("coordinate real not defined", tok.line(), tok.file());
    STRING real = pcreal -> value();


    if (real == "double")
      {
	switch(dim)
	  {
	  case 0: return parse_geom<0,double,
		         qpp::periodic_cell<0,double> >( parm,name,tok,owner); break;
	  case 1: return parse_geom<1,double,
		         qpp::periodic_cell<1,double> >( parm,name,tok,owner); break;
	  case 2: return parse_geom<2,double,
		         qpp::periodic_cell<2,double> >( parm,name,tok,owner); break;
	  case 3: return parse_geom<3,double,
		         qpp::periodic_cell<3,double> >( parm,name,tok,owner); break;
	  default: owner->error("dim must be before 0 and 3",tok.line(),tok.file());
	  }
      }
    else if (real == "float")
      {
	switch(dim)
	  {
	  case 0: return parse_geom<0,float,
		         qpp::periodic_cell<0,float> >( parm,name,tok,owner); break;
	  case 1: return parse_geom<1,float,
		         qpp::periodic_cell<1,float> >( parm,name,tok,owner); break;
	  case 2: return parse_geom<2,float,
		         qpp::periodic_cell<2,float> >( parm,name,tok,owner); break;
	  case 3: return parse_geom<3,float,
		         qpp::periodic_cell<3,float> >( parm,name,tok,owner); break;
	  default: owner->error("dim must be before 0 and 3",tok.line(),tok.file());
	  }
      }
    else
      owner->error("Bad real. Allowed values are \"double\" and \"float\"",tok.line(),tok.file());

  }

  void qpp_read(qpp::ISTREAM & is, std::vector<qpp::qpp_object*> & decls, 
		qpp::qpp_object * __owner)
  {
    qpp::tokenizer t(is);
    qpp::qpp_object * decl;
    while ( (decl=parse_declaration(t,__owner)) != NULL)
      decls.push_back(decl);
  }

  void qpp_read(qpp::ISTREAM & is, qpp::qpp_object* & decl,
		qpp::qpp_object * __owner)
  {
    qpp::tokenizer t(is);
    decl=parse_declaration(t,__owner);
  }

  qpp::qpp_object * parse_non_native_basis(qpp::qpp_param_array & parm,
					   STRING name, qpp::tokenizer & tok,
					   qpp::qpp_object * owner )
  {
    // fixme - parameters treating
    if (parm.n_nested()>0)
      {
	STRING basfmt = ((qpp::qpp_parameter<STRING>*)parm.nested(0))->value();
	// fixme - what if it's not string
	if (basfmt == "g98" || basfmt == "gauss" || basfmt == "gaussian")
	  return parse_g98_basis<double>(parm,name,tok,owner);
      }
  }

  qpp::qpp_object * parse_any_shell(qpp::qpp_param_array & parm,
				    STRING name, qpp::tokenizer & tok,
				    qpp::qpp_object * owner )
  {
    // Get real type
    //    STRING real = "double";
    STRING freal = "";
    qpp::qpp_parameter<STRING> * pfreal =  parm.parameter<STRING>("freal",qpp::qscope_global);
    if (pfreal==NULL)
      pfreal = parm.parameter<STRING>("real",qpp::qscope_global);
    if (pfreal != NULL)
      freal = pfreal -> value();  

    // Get basis type
    qpp::qpp_bastype bastype = qpp::qbas_none;
    qpp::qpp_parameter<STRING> * pbastype =  parm.parameter<STRING>("bastype",qpp::qscope_global);
    if (pbastype != NULL)
      {
	if (pbastype->value()=="gauss")
	  bastype = qpp::qbas_gauss;
	else if (pbastype->value()=="slater")
	  bastype = qpp::qbas_slater;
	else if (pbastype->value()=="siesta")
	  bastype = qpp::qbas_siesta;
	else if (pbastype->value()=="pw")
	  bastype = qpp::qbas_pw;
	else
	  owner -> error("bastype parameter not found",tok.line(),tok.file());
      }

    if (freal == "double")
      switch(bastype)
	{
	case qpp::qbas_gauss:  return parse_shell<qpp::qbas_gauss,double>(parm,name,tok,owner);
	case qpp::qbas_slater: return parse_shell<qpp::qbas_slater,double>(parm,name,tok,owner);
	case qpp::qbas_siesta: return parse_shell<qpp::qbas_siesta,double>(parm,name,tok,owner);
	case qpp::qbas_pw:     return parse_shell<qpp::qbas_pw,double>(parm,name,tok,owner);
	}
    else if (freal == "float")
      switch(bastype)
	{
	case qpp::qbas_gauss:  return parse_shell<qpp::qbas_gauss,float>(parm,name,tok,owner);
	case qpp::qbas_slater: return parse_shell<qpp::qbas_slater,float>(parm,name,tok,owner);
	case qpp::qbas_siesta: return parse_shell<qpp::qbas_siesta,float>(parm,name,tok,owner);
	case qpp::qbas_pw:     return parse_shell<qpp::qbas_pw,float>(parm,name,tok,owner);
	}
    else
      owner -> error("function real not defined",tok.line(),tok.file());
  }


  bool non_native_basis(const  qpp::qpp_param_array & parm)
  {
    qpp::qpp_parameter<STRING> *fmt = parm.parameter<STRING>(0);
    if (fmt!=NULL)
      {
	STRING format = fmt->value();
	if (format == "g98" )
	  return true;
      }
    return false;
  }

  qpp::qpp_object * parse_declaration(qpp::tokenizer & tok, qpp::qpp_object * owner )
  {
    STRING field1, field2, smb;

    tok.dump(" \t");
    tok.separate(",;{}()=\"");

    field1 = tok.get();

    if (field1 == "")
      return NULL;

    //if ( field1.find_first_of(",;{}()=") != std::string::npos )
    if ( ! qpp::is_identifier(field1) )
      owner->error("Error: identifier expected", tok.line(), tok.file());

    field2 = tok.get();

    if (field2 == "=")
      // obj = func(....); or
      // obj = val;        case
      {
	field2 = tok.get();

	bool identif = false;
	if (field2=="\"")
	  {
	    field2 = parse_quoted_string(tok);
	    tok.dump(" \t");
	    tok.separate(",;{}()=\"");		  
	  }
	else if ( field2.find_first_of(",;{}()=") != std::string::npos )
	  owner->error("Error: value expected after \'=\' sign ",tok.line(), tok.file());
	else if (qpp::is_identifier(field2))
	  // precondition for obj=func(....); case
	  identif = true;

	qpp::qpp_param_array * pn = create_parameter(field1,field2,owner,
						     tok.line(), tok.file());
	smb = tok.get();

	if (smb=="(")
	  {
	    if (!identif)
	      owner -> error("Error: must be identifier to have nested parameters",
			     tok.line(), tok.file());
	    parse_parameters(*pn, tok);
	    smb = tok.get();
	  }
	//	else
	// pn -> parameters = new qpp_parameter_list;

	if (smb!=";")
	  owner -> error("Error: \';\' expected ",tok.line(), tok.file());

	return pn;
      }

    if ( field2.find_first_of(",;{}()=") != std::string::npos )
      {
	smb = field2;
	field2 = "";
      }
    else
      smb = tok.get();

    //std::cout << "debug1: f1= " << field1 << " f2= " << field2 << " smb= " << smb << "\n";

    qpp::qpp_param_array  * parm = new qpp::qpp_param_array("",owner);
	
    //std::cerr << "Parameters created: owner= " << owner << "\n";
    //if (owner!=NULL)
    //  owner->write(std::cerr);
    //std::cerr << owner->category() << " " << owner->name() << "\n";

    bool must_have_nested = true;

    if (smb == "(")
      // object name() case
      {
	parse_parameters(*parm,tok);
	must_have_nested = false;
	smb = tok.get();

      }

    /*
      if (field1 == "geometry" || field1 == "fragment" || field1 == "vectors" ||
      field1 == "shell" || 
      (field1 == "basis" && smb == "{" && non_native_basis(*parm)))
    */

    if ( field1 == "geometry" || field1 == "fragment" || field1 == "vectors" ||
	 ( field1 == "basis" && smb == "{" && non_native_basis(*parm)) ||
	 field1 == "shell" || field1 == "molecule" )
      {
	qpp::metaparam_block *meta = qpp::global::meta(field1);
	qpp::metaparam_structure str(meta);
	int code = meta -> identify(*parm,str);
	if (code > 0)
	  {
	    std::cerr << "Parsing " << field1 << " " << field2 << "\n";
	    owner -> error(qpp::metaparam_idf_error(code),tok.line(), tok.file());
	  }
	parm = str.get_params();
	parm -> setowner(owner);
	    
	//debug
	std::cerr << "Normalized parameters: " << field1 << " " << field2;
	parm->write(std::cerr);
	std::cerr << "\n";
      }		  

    if ( field1 == "geometry" || field1 == "fragment" )
      return parse_any_geom( *parm, field2, tok, owner);

    else if ( field1 == "vectors")
      return parse_any_vectors(*parm, field2, tok, owner);

    else if ( field1 == "basis" && smb == "{" && non_native_basis(*parm))
      // fixme - this should be done only for non-native basis formats (g98,gms)
      return parse_non_native_basis(*parm, field2, tok, owner);
	
    else if (field1 == "shell" )
      return parse_any_shell(*parm, field2, tok, owner);

    /*
      for (int i=0; i<parm.size(); i++)
      pn -> add_parm(*parm[i]);
    */

    //else
    //  pn -> parlist = new qpp_parameter_list;

    //std::cout << "debug2: nparams= " << pn->parlist->size() << " musthave= " << must_have_nested << "\n";

    if ( must_have_nested && smb != "{")
      owner -> error("Error: \'{\' block expected ",tok.line(),tok.file());

    //std::cout << "debug2.1: " << smb  << " bool " << (smb == "{") << "\n";

    // convert obj(val) case into obj = val 
    if ( smb != "{" && parm->n_nested()==1 && parm->nested(0)->name()=="" )
      // exceptions which should not be converted
      if (field1 != "center" && field1 != "replicate" && field1 != "replace" &&
	  field1 != "values" && field1 != "value"     && field1 != "synonyms")
	{
	  qpp::qpp_object *pval = parm->nested(0);
	  delete parm;
	  pval->setname(field1);
	  pval->setowner(owner);
	  return pval;
	}

    qpp::qpp_declaration * decl = new qpp::qpp_declaration(field1,field2,owner,parm,
							   tok.line(), tok.file());

    if ( smb == "{" )
      {
	//std::cout << "debug2.2: " << smb << "\n";
	smb = tok.get();
	while ( smb != "}")
	  {
	    //std::cout << "debug3: " << smb << "\n";
	    tok.back(smb);
	    decl -> add( * parse_declaration(tok,decl) );
	    smb = tok.get();
	  }
      }

    else if (smb != ";")
      decl->error("Error: \';\' expected ",tok.line(),tok.file());

    return decl;

  }

};

