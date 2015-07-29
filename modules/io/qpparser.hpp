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
					  qpp::qpp_object *owner, int line=-1, const STRING & file="");
  // ----------------------------------------------------------------

  void parse_parameters(qpp::qpp_param_array & lst, qpp::tokenizer & tok);

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
    //std::cerr << "parse_geom\n";

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
	    //std::cerr << format << "\n";
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
				  qpp::tokenizer & tok, qpp::qpp_object * owner);

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

  qpp::qpp_object * parse_any_vectors(int dim, qpp::qpp_param_array & parm, 
				      STRING name, qpp::tokenizer & tok,
					  qpp::qpp_object * owner);

  // ---------------------------------------------------------

  template<class FREAL>
  qpp::qpp_object * parse_g98_basis(qpp::qpp_param_array & parm, 
				    STRING name, qpp::tokenizer & tok,
				    qpp::qpp_object * owner)
  {
    qpp::qpp_basis_data<qpp::qbas_gauss,FREAL> *bas = 
      new qpp::qpp_basis_data<qpp::qbas_gauss,FREAL>(name);
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

      int nr = bas->n_rcrd()-1;
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
	
	qpp::qpp_shell<qpp::qbas_gauss,FREAL> sh(np,l2-l1+1);
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
	//bas -> rcrd(nr).shells[bas -> rcrd(nr).shells.size()-1].write_g98(std::cout);
	    
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

  qpp::qpp_object * parse_non_native_basis(qpp::qpp_param_array & parm, 
					   STRING name, qpp::tokenizer & tok,
					   qpp::qpp_object * owner );


  // -------------------------------------------------------------------------------

  template<qpp::qpp_bastype ST, class FREAL>
  qpp::qpp_object * parse_shell(qpp::qpp_param_array& parm, 
				STRING name, qpp::tokenizer & tok,
				qpp::qpp_object * owner)

  /* -------------------------------------------------------------------------------

  template<class FREAL>
  qpp::qpp_object * parse_shell<qpp::qbas_gauss,FREAL>(qpp::qpp_param_array& parm, 
						       STRING name, qpp::tokenizer & tok,
						       qpp::qpp_object * owner)*/
  {

    if (ST==qpp::qbas_gauss || ST==qpp::qbas_slater)
      {

	tok.separate("}");
	tok.dump("");

	qpp::qpp_angtype angtype=qpp::qang_spherical;
    
	qpp::qpp_parameter<STRING> * pang = parm.parameter<STRING>("angtype");
	if (pang==NULL)
	  pang = owner -> parameter<STRING>("angtype");

	if (pang!=NULL)
	  if (pang->value()=="cartesian")
	    angtype = qpp::qang_cartesian;

	std::vector<FREAL> exps;
	std::vector<std::vector<FREAL> > coeffs;
	std::vector<int> l;
	std::vector<STRING> lbl;

	for (int i = 0; i < parm.n_nested(); i++)
	  if (parm.nested(i)->gettype() & qpp::qtype_data_int)
	    {
	      lbl.push_back(parm.nested(i)->name());
	      l.push_back(((qpp::qpp_parameter<int>*)parm.nested(i))->value());
	    }

	int nl = l.size(), np=0;
	coeffs.resize(nl);

	while(true)
	  {
	    STRING line = tok.get();
	
	    if (line == "}")
	      break;
	    if (line.find_first_not_of(" \t") == std::string::npos && tok.get() == "}")
	      break;

	    std::vector<STRING> fields = qpp::split(line);

	    if (fields.size() != nl+1)
	      owner->error("Wrong number of fields",tok.line(),tok.file());

	    FREAL r;
	    bool OK = s2t<FREAL>(fields[0],r);
	    if (!OK) owner->error("Real number expected",tok.line(),tok.file());
	    exps.push_back(r);

	    for (int i=0; i<nl; i++)
	      {
		OK = s2t<FREAL>(fields[i+1],r);
		if (!OK) owner->error("Real number expected",tok.line(),tok.file());
		coeffs[i].push_back(r);
	      }

	    np++;
	
	  }


	if (ST == qpp::qbas_gauss)
	  {
	    qpp::qpp_shell<qpp::qbas_gauss,FREAL> * sh = 
	      new qpp::qpp_shell<qpp::qbas_gauss,FREAL>(np,nl,angtype);
	
	    for (int j=0; j<np; j++)
	      {
		sh->alpha(j) = exps[j];
		for (int i=0; i<nl; i++)
		  sh->coeff(i,j) = coeffs[i][j];
	      }
	    for (int i=0; i<nl; i++)
	      {
		sh->l(i) = l[i];
		sh->label(i) = lbl[i];
	      }

	    tok.dump(" \t");
	    tok.separate(",;{}()=");
	
	    return sh;
	  }

	else 
	  {
	    /*
	    qpp::qpp_shell<qpp::qbas_slater,FREAL> * sh = 
	      new qpp::qpp_shell<qpp::qbas_slater,FREAL>(np,nl,angtype);
	
	    for (int j=0; j<np; j++)
	      {
		sh->alpha(j) = exps[j];
		for (int i=0; i<nl; i++)
		  sh->coeff(i,j) = coeffs[i][j];
	      }
	    for (int i=0; i<nl; i++)
	      sh->l(i) = l[i];

	    tok.dump(" \t");
	    tok.separate(",;{}()=");
	
	    return sh;
	    */
	  }
      }
  }

  // -------------------------------------------------------------------------------

  qpp::qpp_object * parse_any_shell(qpp::qpp_param_array & parm, 
				    STRING name, qpp::tokenizer & tok,
				    qpp::qpp_object * owner );

  // -------------------------------------------------------------------------------

  qpp::qpp_object * parse_declaration(qpp::tokenizer & tok, qpp::qpp_object * owner );

  void qpp_read(qpp::ISTREAM & is, std::vector<qpp::qpp_object*> & decls);

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
  //  using _qpp_internal::qpp_compile;

};

#endif
