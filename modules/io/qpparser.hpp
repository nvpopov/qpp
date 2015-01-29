#ifndef _QPPARSER_H
#define _QPPARSER_H

#include <algorithm>
#include <string>
#include <sstream>
#include <ios>
#include <iostream>
#include <data/qppdata.hpp>
#include <io/strfun.hpp>
#include <geom/geom.hpp>
#include <geom/geom_extras.hpp>
#include <basis/basis.hpp>
#include <stdlib.h>

namespace _qpp_internal{ 

  using qpp::s2t;
  using qpp::TRAITS;

  //  void parse_parameters(std::vector<qpp::qpp_object*> & lst, tokenizer & tok);
  
  qpp::qpp_param_array * create_parameter(const STRING & name, const STRING & value,
					  qpp::qpp_object *owner, int line=-1, const STRING & file="")
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
  
  // ----------------------------------------------------------------

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
    std::cout << "paramlist:";
    for (int i=0; i<lst.n_nested(); i++)
     lst.nested(i)->write(std::cerr);
    lst.write(std::cerr);
    std::cerr << "\n";
    
    //    return lst;
  }

  /*
  void parse_parameters(std::vector<qpp::qpp_object*> & lst, tokenizer & tok)
  {
    std::vector<qpp::qpp_parameter<STRING>*> parm;
    parse_parameters(parm,tok);
    lst.clear();
    for (int i=0; i<parm.size(); i++)
      lst.push_back(parm[i]);
  }
  */

  // ----------------------------------------------------------------

  template <int DIM, class VALTYPE> 
  qpp::geometry<DIM, VALTYPE> *  parse_geom(qpp::qpp_param_array & parm, 
					    STRING name, qpp::tokenizer & tok,
					    qpp::qpp_object * owner)
  {
    //debug
    std::cerr << "parse_geom\n";

    tok.separate("}");
    tok.dump("");

    bool xtra = false, xchrg = false, xmass = false;
    int nxr=0, nxi=0, nxb=0;
    STRING format;
    std::vector<STRING> rnames, inames, bnames;

    if (parm.n_nested()==0)
      format = "axyz";
    else
      {
	int i=0;
	qpp::qpp_param_array * p0 = (qpp::qpp_param_array*)parm[0];
	if ( (p0->name() == "" || qpp::tolower(p0->name())=="dim") && 
	     (p0->gettype() & (qpp::qtype_parameter | qpp::qtype_data_int) ) )
	  i=1;
	while (i < parm.n_nested())
	  {
	    STRING v = qpp::tolower(((qpp::qpp_parameter<STRING>*)parm[i]) -> value());
	    STRING pname = ((qpp::qpp_parameter<STRING>*)parm[i]) -> name();
	    if (v == "atom")
	      format += "a";
	    else if ( v == "x" || v == "y" || v == "z")
	      format += v;
	    /*
	    else if ( v == "charge")
	      {
		format += "q";
		xchrg = true;
	      }
	    */
	    else if ( v == "real")
	      {
		format += "r";
		nxr++;
		rnames.push_back(pname);
	      }
	    else if ( v == "int")
	      {
		format += "i";
		nxi++;
		inames.push_back(pname);
	      }
	    else if ( v == "bool")
	      {
		format += "b";
		nxb++;
		bnames.push_back(pname);
	      }
	    /*
	    else if ( v == "mass")
	      {
		format += "m";
		xmass = true;
	      }
	    else if ( v == "number" || v == "num" || v == "mendeleev" )
	      format += "n";
	    */
	    else
	      owner->error("Bad geometry format: unrecognized field "+v,tok.line(), tok.file());
	    i++;
	  }
	if (format=="")
	  format = "axyz";

	// debug
	//std::cout << format << "\n";
	if ( std::count(format.begin(),format.end(),'a') > 1)
	  owner->error("Bad geometry format: atoms requested more then once",
		       tok.line(), tok.file());
	if ( std::count(format.begin(),format.end(),'x') > 1)
	  owner->error("Bad geometry format: x coordinates requested more then once",
		       tok.line(), tok.file());
	if ( std::count(format.begin(),format.end(),'y') > 1)
	  owner->error("Bad geometry format: y coordinates requested more then once",
		       tok.line(), tok.file());
	if ( std::count(format.begin(),format.end(),'z') > 1)
	  owner->error("Bad geometry format: z coordinates requested more then once",
		       tok.line(), tok.file());
	if ( std::count(format.begin(),format.end(),'q') > 1)
	  owner->error("Bad geometry format: charges requested more then once",
		       tok.line(), tok.file());
      }

    bool xgeom = xchrg || nxr>0 || nxi>0 || nxb>0;

    //std::cerr << "parse_geom: xgeom= " << xgeom << "n r i b = " << nxr << " " 
    //	      << nxi << " " << nxb << "\n";

    qpp::geometry<DIM, VALTYPE> * geom;
    qpp::xtr_geometry<DIM, VALTYPE> * xtr_geom = NULL;

    if (xgeom)
      {
	xtr_geom = new qpp::xtr_geometry<DIM, VALTYPE>(nxr,nxi,nxb,name);
	geom = xtr_geom;
	for (int i=0; i<nxr; i++)
	  xtr_geom -> xreal_name(i) = rnames[i];
	for (int i=0; i<nxi; i++)
	  xtr_geom -> xint_name(i) = inames[i];
	for (int i=0; i<nxb; i++)
	  xtr_geom -> xbool_name(i) = bnames[i];
      }
    else
      geom = new qpp::geometry<DIM, VALTYPE>(name);

    geom -> setowner(owner);

    int nat = 0;

    while(true)
      {
	STRING line = tok.get();
	
	//debug
	//std::cerr << "\"" << line <<"\"" << "\n";

	if (line == "}")
	  break;
	if (line.find_first_not_of(" \t") == std::string::npos && tok.get() == "}")
	  break;

	//std::cerr << "before split\n";
	std::vector<STRING> fields = qpp::split(line);

	//debug
	//std::cerr << "after split\n";
	//for (int i=0; i<fields.size(); i++)
	//  std::cerr << "split:: \"" << fields[i] << "\"\n";

	if (fields.size() == 0)
	  continue;
  
	//std::cout << fields.size() << " " << format.size()<< "\n";
	//for (int i=0; i<fields.size(); i++)	
	//  std::cout << i << "|" << fields[i] << "\n";
	
  
	if ( fields.size() != format.size() )
	  {
	    //std::cerr << "format \"" << format << "\"\n";
	    owner->error("Error: wrong number of fields",tok.line(), tok.file());
	  }

	if (format == "axyz")
	  {
	    lace::vector3d<VALTYPE> r;
	    if ( (!s2t<VALTYPE>(fields[1], r(0))) || (!s2t<VALTYPE>(fields[2], r(1))) || 
		 (!s2t<VALTYPE>(fields[3], r(2))) )
	      owner->error("Error: coordinate (real number) expected",tok.line(), tok.file());
	    
	    geom -> add( fields[0], r);
	  }
	else
	  {
	    //debug
	    std::cerr << format << "\n";
	    geom -> add( "", VALTYPE(0), VALTYPE(0), VALTYPE(0));	 

	    STRING aname = "";
	    int anum = 0, ixr = 0, ixi = 0, ixb = 0;
	    VALTYPE ax = 0, ay = 0, az = 0, amass = 0, achrg = 0;
	    for (int i=0; i < fields.size(); i++)
	      {
		switch( format[i] )
		  {
		  case 'a': aname = fields[i];
		    break;
		    //case 'n': anum = s2t<int>(fields[i]);
		    // break;
		  case 'x': s2t<VALTYPE>(fields[i], ax);
		    break;
		  case 'y': s2t<VALTYPE>(fields[i], ay);
		    break;
		  case 'z': s2t<VALTYPE>(fields[i], az);
		    break;
		    //case 'q': achrg = s2t<VALTYPE>(fields[i]);
		    //  xtr_geom -> charge(nat) = achrg;		   
		    //  break;
		    //case 'm': amass = s2t<VALTYPE>(fields[i]);
		    //break;
		  case 'r': s2t<VALTYPE>(fields[i], xtr_geom -> xtr_real(ixr,nat));
		    ixr++; break;
		  case 'i': s2t<int>(fields[i], xtr_geom -> xtr_int(ixi,nat) );
		    ixi++; break;
		  case 'b': s2t<bool>(fields[i], xtr_geom -> xtr_bool(ixb,nat) );
		    ixb++; break;
		  }		
	      }
	    if ( xchrg || xmass )
	      geom -> atom(nat) = aname;
	    else
	      geom -> atom(nat) = aname;
	    geom -> coord(nat) = lace::vector3d<VALTYPE>(ax,ay,az);
	  }
	nat++;
      }

    tok.dump(" \t");
    tok.separate(",;{}()=");

    //geom -> write(std::cout);
    //std::cout << geom->gettype() << "\n";

    return geom;
  }

  // ---------------------------------------------------------

  qpp::qpp_object *parse_any_geom(qpp::qpp_param_array& parm, STRING name, 
				  qpp::tokenizer & tok, qpp::qpp_object * owner)
  {
    // determine the dimension first
    int dim = 0;
    bool defined=false;
    if (parm.n_nested() > 0)
      {
	qpp::qpp_param_array * p0 = (qpp::qpp_param_array*)parm[0];
	std::cerr << "defining dimension: " << qpp::tolower(p0->name()) << " " <<
	  p0->gettype() << " " << qpp::qtype_parameter << " " << 
	  qpp::qtype_data_int << " " << qpp::qtype_data_string << "\n";

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
      defined = owner -> parameter(dim,"dim",qpp::qscope_global);

    if (!defined)
      owner->error("Dimension of the geometry not defined",tok.line(),tok.file());
    // debug
    std::cerr << "=============== dimension = " << dim << "\n";

    if (dim == 0)
      return parse_geom<0,double>(parm,name,tok,owner);
    else if (dim == 1)
      return parse_geom<1,double>(parm,name,tok,owner);
    else if (dim == 2)
      return parse_geom<2,double>(parm,name,tok,owner);
    else if (dim == 3)
      return parse_geom<3,double>(parm,name,tok,owner);

  }

  // ---------------------------------------------------------

  template <int DIM, class VALTYPE>
  qpp::periodic_cell<DIM, VALTYPE> * parse_vectors(qpp::qpp_param_array  & parm, 
						   STRING name, qpp::tokenizer & tok, 
						   qpp::qpp_object * owner )
  {
    tok.separate("}");
    tok.dump("");

    qpp::periodic_cell<DIM, VALTYPE>  
      * cl = new qpp::periodic_cell<DIM, VALTYPE>(name);

    cl -> setowner(owner);
    int i = 0;
    while(true)
      {
	STRING line = tok.get();

	if (line == "}")
	  break;
	if (line.find_first_not_of(" \t") == std::string::npos && tok.get() == "}")
	  break;

	std::vector<STRING> fields = qpp::split(line);
	
	if (fields.size() == 0)
	  continue;

	if (fields.size() != 3)
	  cl->error("Error: wrong number of fields, should be 3",tok.line(),tok.file());
	if ( i == DIM)
	  cl->error("Number of vectors is not equal to cell dimension",tok.line(),tok.file());

	for (int j=0; j<3; j++)
	  s2t<VALTYPE>( fields[j], (*cl)(i,j) );

	i++;
      }

    if ( i < DIM)
      cl->error("Number of vectors is not equal to cell dimension",tok.line(),tok.file());

    tok.dump(" \t");
    tok.separate(",;{}()=");

    return cl;
  }

  // ---------------------------------------------------------

  qpp::qpp_object * parse_any_vectors(int dim, qpp::qpp_param_array  parm, 
				      STRING name, qpp::tokenizer & tok,
				      qpp::qpp_object * owner)
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

  // ---------------------------------------------------------

  template<class FREAL>
  qpp::qpp_object * parse_g98_basis(qpp::qpp_param_array& parm, 
				    STRING name, qpp::tokenizer & tok,
				    qpp::qpp_object * owner)
  {
    qpp::gencon_basis_data<FREAL> *bas = new qpp::gencon_basis_data<FREAL>(name);
    bas -> setowner(owner);

    tok.separate("}");
    tok.dump("");
    
    STRING line = tok.get();

    do{

      std::vector<STRING> lbls;
      qpp::split(line, lbls);

      bas -> new_rcrd();

      int n;
      if ( !s2t<int>(lbls[lbls.size()-1],n) || n!=0)
	bas->error("The list of atoms must terminate with 0",tok.line(), tok.file());
	
      for(int i=0; i<lbls.size()-1; i++)
	{
	  if ( s2t<int>(lbls[i],n) )
	    bas -> add_number(n);
	  else
	    bas -> add_label(lbls[i]);
	}

      int nr = bas->nrcrd()-1;
      //debug
      /*
      std::cout << "labels:";
      for(int i=0; i<bas->rcrd(nr).labels.size(); i++)
	std::cout << " " << bas->rcrd(nr).labels[i];
      std::cout << "\nnumbers:";
      for(int i=0; i<bas->rcrd(nr).numbers.size(); i++)
	std::cout << " " << bas->rcrd(nr).numbers[i];
      std::cout << "\n";
      */

      line = tok.get();
      do{
	
	line = qpp::tolower(line);
	qpp::split(line, lbls);
	if (lbls[0]=="****")
	  break;
	if (lbls.size()!=3)
	  bas->error("Orbital definition expected, must contain 3 fields",
		     tok.line(), tok.file());
	
	int l1,l2,np;
	if (lbls[0] == "s")
	  l1=l2=0;
	else if (lbls[0] == "p")
	  l1=l2=1;
	else if (lbls[0] == "d")
	  l1=l2=2;
	else if (lbls[0] == "f")
	  l1=l2=3;
	else if (lbls[0] == "g")
	  l1=l2=4;
	else if (lbls[0] == "sp")
	  { l1=0; l2=1; }
	else if (lbls[0] == "spd")
	  { l1=0; l2=2; }
	else
	  bas->error("Orbital type notation (s,p,d,..) expected",tok.line(), tok.file());
	
	if ( !s2t<int>(lbls[1],np) )
	  bas->error("Number of primitive gaussians expected",tok.line(), tok.file());
	
	qpp::gencon_shell<FREAL> sh(np,l2-l1+1);
	for (int i=0; i<=l2-l1; i++)
	  sh.l(i) = l1+i;

	//debug
	/*
	std::cout << "shell " << bas -> rcrd(nr).shells.size() << " nprim = " << np << " l =";
	for (int i=0; i<=l2-l1; i++)
	  std::cout << sh.l(i) << " ";
	std::cout << "\n";
	*/

	for (int p=0; p<np; p++)
	  {
	    line = tok.get();
	    std::vector<STRING> fld;
	    qpp::split(line, fld);
	    if (fld.size()!=l2-l1+2)
	      bas->error("Orbital exponent and contraction coefficient(s) expected",
			 tok.line(), tok.file());
	    if ( !s2t<FREAL>(fld[0], sh.alpha(p)) )
	      bas->error("Orbital exponent (real) expected",
			 tok.line(), tok.file());
	    for (int i=0; i<=l2-l1; i++)
	      if ( !s2t<FREAL>(fld[i+1], sh.coeff(i,p)) )
		bas->error("Contraction coefficient (real) expected",
			   tok.line(), tok.file());
	  }
	bas -> add_shell(sh);
	
	//debug
	bas -> rcrd(nr).shells[bas -> rcrd(nr).shells.size()-1].write_g98(std::cout);
	    
	line = tok.get();
      } while(true);
  
      line = tok.get();

      if (line == "}")
	break;
      if (line.find_first_not_of(" \t") == std::string::npos && tok.get() == "}")
	break;

    } while(true);

    tok.dump(" \t");
    tok.separate(",;{}()=");

    return bas;
  }

  // -------------------------------------------------------------------------------

  qpp::qpp_object * parse_any_basis(qpp::qpp_param_array & parm, 
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


  // -------------------------------------------------------------------------------

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

    qpp::qpp_param_array  * parm = new qpp::qpp_param_array;
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

    if ( field1 == "basis" && smb == "{" )
      return parse_any_basis(*parm, field2, tok, owner);
      
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

    // consider obj(val) case separately
    if ( smb != "{" && parm->n_nested()==1 && parm->nested(0)->name()=="" )
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

  void qpp_read(qpp::ISTREAM & is, std::vector<qpp::qpp_object*> & decls)
  {
    qpp::tokenizer t(is);
    qpp::qpp_object * decl;
    while ( (decl=parse_declaration(t,NULL)) != NULL)
      decls.push_back(decl);
  }  

  // ---------------------------------------------------------

  //  qpp::qpp_object *parse_any_geom(int dim, std::vector<qpp::qpp_object*>& parm, STRING name, tokenizer & tok);


  //  qpp::qpp_object * parse_any_vectors(int dim, std::vector<qpp::qpp_object*>& parm, 
  //				      STRING name, tokenizer & tok);
  // ---------------------------------------------------------

  //  qpp::qpp_object * parse_any_basis(std::vector<qpp::qpp_object*>& parm, 
  //				    STRING name, tokenizer & tok);
  // ---------------------------------------------------------
  
  //  qpp::qpp_object * parse_declaration(tokenizer & tok);

};

namespace qpp{

  using _qpp_internal::qpp_read;

};

#endif
