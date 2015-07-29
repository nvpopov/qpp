#include "io/qpparser.hpp"

namespace _qpp_internal
{
qpp::qpp_object * parse_any_vectors(int dim, qpp::qpp_param_array & parm,
					STRING name, qpp::tokenizer & tok,
					qpp::qpp_object * owner)
{
  STRING real = "double";
  qpp::qpp_parameter<STRING> * rl = parm.parameter<STRING>("real");
  if (rl == NULL)
    rl = owner -> parameter<STRING>("creal",qpp::qscope_global);
  if (rl == NULL)
    rl = owner -> parameter<STRING>("real",qpp::qscope_global);
  if (rl != NULL)
    real = rl->value();

  if (real == "double")
    {
      if (dim == 0)
	return parse_vectors<0,double>(parm,name,tok,owner);
      else if (dim == 1)
	return parse_vectors<1,double>(parm,name,tok,owner);
      else if (dim == 2)
	return parse_vectors<2,double>(parm,name,tok,owner);
      else if (dim == 3)
	return parse_vectors<3,double>(parm,name,tok,owner);
    }
  else if (real == "float")
   {
      if (dim == 0)
	return parse_vectors<0,float>(parm,name,tok,owner);
      else if (dim == 1)
	return parse_vectors<1,float>(parm,name,tok,owner);
      else if (dim == 2)
	return parse_vectors<2,float>(parm,name,tok,owner);
      else if (dim == 3)
	return parse_vectors<3,float>(parm,name,tok,owner);
    }
  else
    owner->error("Bad real",tok.line(),tok.file());
}
qpp::qpp_param_array * create_parameter(const STRING & name, const STRING & value,
					qpp::qpp_object *owner, int line, const STRING & file)
{
  double dval;
  int ival;
  bool bval;

  if (s2t<int>(value,ival))
	return new qpp::qpp_parameter<int>(name, ival, owner, line, file);
  else if (s2t<double>(value,dval))
	return new qpp::qpp_parameter<double>(name, dval, owner, line, file);
  else if (s2t<bool>(value,bval))
	return new qpp::qpp_parameter<bool>(name, bval, owner, line, file);
  else
	return new qpp::qpp_parameter<STRING>(name, value, owner, line, file);
}

void parse_parameters(qpp::qpp_param_array & lst, qpp::tokenizer & tok)
{
	//std::vector<qpp::qpp_object*> nested_lst;
	tok.dump(" \t");
	tok.separate(",;{}()=");

	STRING field1, field2, smb;
	bool first = true, nested = false;
	lst.clear();

	do
	{
		field1 = tok.get();

		if ( field1.find_first_of(",;{}()") != std::string::npos )
		{
			if (field1 == ")" && first)
				// empty parameter list
				return;
			else
				lst.error("Incorrect parameter list", tok.line(), tok.file());
		}

		// now field1 != one of special characters

		field2 = tok.get();

		if (field2 == "=")
			// parameter=value case
		{
			field2 = tok.get();
			if ( field2.find_first_of(",;{}()") != std::string::npos )
				lst.error("Error after \'=\' sign in parameter list", tok.line(), tok.file());

			smb = tok.get();
		}
		else
			// value case
		{
			smb = field2;
			field2 = field1;
			field1 = "";

			//std::cout << " f1= " << field1 << " f2= " << field2 << " smb= " << smb << "\n";

		}
		/*
  if (smb == "(")
	// nested parameter list
	{
	  //	    parse_parameters(nested_lst, tok);
	  nested = true;
	  smb = tok.get();
	}
  else
	nested = false;
  */

		nested = (smb == "(");

		if (nested && field1 == "")
		{
			field1 = field2;
			field2 = "";
		}

		qpp::qpp_param_array * pn = create_parameter(field1,field2,&lst,tok.line(),tok.file());
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

qpp::qpp_object *parse_any_geom(qpp::qpp_param_array& parm, STRING name,
				qpp::tokenizer & tok, qpp::qpp_object * owner)
{
  // determine the dimension first
  int dim = 0;
  bool defined=false;
  if (parm.n_nested() > 0)
	{
  qpp::qpp_param_array * p0 = (qpp::qpp_param_array*)parm[0];

  //debug
  /*
  std::cerr << "defining dimension: " << qpp::tolower(p0->name()) << " " <<
	p0->gettype() << " " << qpp::qtype_parameter << " " <<
	qpp::qtype_data_int << " " << qpp::qtype_data_string << "\n";
  */

  if ( (p0->name() == "" || qpp::tolower(p0->name())=="dim") &&
	   (p0->gettype() == qpp::qtype_parameter + qpp::qtype_data_int ) )
	{
	  dim = ((qpp::qpp_parameter<int>*)p0)->value();
	  defined = true;
	}

  // kostyl
  if (!defined && (p0->gettype() == qpp::qtype_parameter + qpp::qtype_data_string ) &&
	  (p0->name() == "" || qpp::tolower(p0->name())=="dim") )
	{
	  STRING sdim = ((qpp::qpp_parameter<STRING>*)p0)->value();
	  if (qpp::tolower(sdim)=="0d")
		{
	  dim = 0;
	  defined=true;
		}
	  else if (qpp::tolower(sdim)=="1d")
		{
	  dim = 1;
	  defined=true;
		}
	  else if (qpp::tolower(sdim)=="2d")
		{
	  dim = 2;
	  defined=true;
		}
	  else if (qpp::tolower(sdim)=="3d")
		{
	  dim = 3;
	  defined=true;
		}
	}
	}
  if (!defined)
    {
      qpp::qpp_parameter<int> * pdim = owner -> parameter<int>("dim",qpp::qscope_global);
      defined = (pdim != NULL);
      if (defined)
	dim = pdim->value();
    }

  if (!defined)
	owner->error("Dimension of the geometry not defined",tok.line(),tok.file());
  // debug
  //std::cerr << "=============== dimension = " << dim << "\n";

  if (dim == 0)
	return parse_geom<0,double>(parm,name,tok,owner);
  else if (dim == 1)
	return parse_geom<1,double>(parm,name,tok,owner);
  else if (dim == 2)
	return parse_geom<2,double>(parm,name,tok,owner);
  else if (dim == 3)
	return parse_geom<3,double>(parm,name,tok,owner);

}

void qpp_read(qpp::ISTREAM & is, std::vector<qpp::qpp_object*> & decls)
{
	qpp::tokenizer t(is);
	qpp::qpp_object * decl;
	while ( (decl=parse_declaration(t,NULL)) != NULL)
		decls.push_back(decl);
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
    // Get basis type
    qpp::qpp_bastype bastype = qpp::qbas_gauss;
    // Get real type
    STRING real = "double";

    // fixme - implement this    

    if (bastype==qpp::qbas_gauss)
      {
	if (real=="double")
	  return parse_shell<qpp::qbas_gauss,double>(parm,name,tok,owner);
	else if (real=="float")
	  return parse_shell<qpp::qbas_gauss,float>(parm,name,tok,owner);
      }
    else if (bastype==qpp::qbas_slater)
      {
	if (real=="double")
	  return parse_shell<qpp::qbas_slater,double>(parm,name,tok,owner);
	else if (real=="float")
	  return parse_shell<qpp::qbas_slater,float>(parm,name,tok,owner);
      }
    else if (bastype==qpp::qbas_siesta)
      {
	if (real=="double")
	  return parse_shell<qpp::qbas_siesta,double>(parm,name,tok,owner);
	else if (real=="float")
	  return parse_shell<qpp::qbas_siesta,float>(parm,name,tok,owner);
      }
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
	tok.separate(",;{}()=");

	field1 = tok.get();

	if (field1 == "")
		return NULL;

	if ( field1.find_first_of(",;{}()=") != std::string::npos )
		owner->error("Error: identifier expected, special character found",
					 tok.line(), tok.file());

	field2 = tok.get();

	if (field2 == "=")
		// obj = func(....); or
		// obj = val;        case
	{
		field2 = tok.get();
		if ( field2.find_first_of(",;{}()=") != std::string::npos )
			owner->error("Error: identifier expected after \'=\' sign ",tok.line(), tok.file());

		// fixme - not necessarily STRING
		qpp::qpp_param_array * pn = create_parameter(field1,field2,owner,
							     tok.line(), tok.file());
		smb = tok.get();

		if (smb=="(")
		{
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
	bool must_have_nested = true;

	if (smb == "(")
		// object name() case
	{
		parse_parameters(*parm,tok);
		must_have_nested = false;
		smb = tok.get();
	}

	if ( field1 == "geometry" || field1 == "fragment" )
	{

		// fixme - what about VALTYPE?
		return parse_any_geom( *parm, field2, tok, owner);

	}

	if ( field1 == "vectors")
	{
		// determine the dimension first
	        // fixme - rewrite this
		int dim = 3;
		if ( parm->n_nested() > 0)
		{
			STRING s = ((qpp::qpp_parameter<STRING>*)parm->nested(0))->value();
			if ( s == "3d" )
				dim = 3;
			else if ( s == "2d" )
				dim = 2;
			else if ( s == "1d" )
				dim = 1;
		}
		return parse_any_vectors(dim, *parm, field2, tok, owner);
	}

	if ( field1 == "basis" && smb == "{" && non_native_basis(*parm))
	  // fixme - this should be done only for non-native basis formats (g98,gms)
	  return parse_non_native_basis(*parm, field2, tok, owner);
	
	if (field1 == "shell" )
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
	      field1 != "values")
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

  /*
  qpp::qpp_object * qpp_compile( qpp::qpp_object * q)
  {
    if (q->gettype() == qpp::qtype_declaration)
      {}
  }
  */
};

