#ifndef _QPPARSER_H
#define _QPPARSER_H

#include <algorithm>
#include <string>
#include <sstream>
#include <ios>
#include <iostream>
#include <io/qppdata.hpp>
#include <geom/geom.hpp>
#include <geom/geom_extras.hpp>
#include <basis/basis.hpp>
//#include <geom/atom.hpp>

#include <stdlib.h>

namespace qpp{

  // -------------------------------- string to type T convertor ----------------------------
  
  template<typename T>
  bool s2t(const STRING & s, T & val)
  {
    std::basic_stringstream<CHAR,TRAITS> ss(s);
    ss >> val;
    return !ss.fail();
  }
  
  template<>
  bool s2t<bool>(const STRING & s, bool & val);

  // -------------------------------------------------------------

  template<typename T>
  STRING t2s(const T & val)
  {
    std::basic_stringstream<CHAR,TRAITS> ss;
    ss << val;
    return ss.str();
  }

  // -------------------------------------------------------------

  void qpp_read(std::basic_istream<CHAR,TRAITS> & is, std::vector<qpp::qpp_object*> & decls);

};

namespace _qpp_internal{

  using qpp::s2t;
  using qpp::TRAITS;

  // -------------------- Simple tokenizer -----------------------------------

  class tokenizer
  {
    std::basic_istream<CHAR,TRAITS> * _input;
    STRING _buff, _dump, _sepr;
    int _line_number;
    bool sstr;
    
  public:
    
    tokenizer(std::basic_istream<CHAR,TRAITS> & input);

    tokenizer(const STRING & str);

    ~tokenizer();
    
    void dump(const STRING & smb);
    
    void separate(const STRING & smb);
    
    STRING get();
    
    void back(STRING s);
    
    bool eof();
    
    int line_number();
    
  };

  // -----------------------------------------------------------
  
  void qpp_data_error(STRING s, int l);

  // -----------------------------------------------------------

  void tolower(STRING & s);

  // -----------------------------------------------------------  

  void split(const STRING &s, std::vector<STRING> &elems, STRING delims = " \t");

  // -----------------------------------------------------------

  std::vector<STRING> split(const STRING &s, STRING delims = " \t");

  // ----------------------------------------------------------------

  void parse_parameters(std::vector<qpp::qpp_object*> & lst, tokenizer & tok);
  void parse_parameters(std::vector<qpp::qpp_parameter<STRING>*> & lst, tokenizer & tok);

  // ----------------------------------------------------------------

  template <int DIM, class VALTYPE> 
  qpp::geometry<DIM, VALTYPE> *  parse_geom(std::vector<qpp::qpp_object*> & parm, 
					    STRING name, tokenizer & tok)
  {
    //debug
    // std::cerr << "parse_geom\n";

    tok.separate("}");
    tok.dump("");

    bool xtra = false, xchrg = false, xmass = false;
    int nxr=0, nxi=0, nxb=0;
    STRING format;
    std::vector<STRING> rnames, inames, bnames;

    if (parm.size()==0)
      format = "axyz";
    else
      {
	int i=0;
	STRING sd = ((qpp::qpp_parameter<STRING>*)parm[0]) -> value();
	if ( sd == "3d" || sd == "2d" || 
	     sd == "1d" || sd == "0d")
	  i=1;
	while (i < parm.size())
	  {
	    STRING v = ((qpp::qpp_parameter<STRING>*)parm[i]) -> value();
	    STRING pname = ((qpp::qpp_parameter<STRING>*)parm[i]) -> name();
	    tolower(v);
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
	      qpp_data_error("Bad geometry format: unrecognized field "+v,tok.line_number());
	    i++;
	  }
	if (format=="")
	  format = "axyz";

	// debug
	//std::cout << format << "\n";
	if ( std::count(format.begin(),format.end(),'a') > 1)
	  qpp_data_error("Bad geometry format: atoms requested more then once",tok.line_number());
	if ( std::count(format.begin(),format.end(),'x') > 1)
	  qpp_data_error("Bad geometry format: x coordinates requested more then once",tok.line_number());
	if ( std::count(format.begin(),format.end(),'y') > 1)
	  qpp_data_error("Bad geometry format: y coordinates requested more then once",tok.line_number());
	if ( std::count(format.begin(),format.end(),'z') > 1)
	  qpp_data_error("Bad geometry format: z coordinates requested more then once",tok.line_number());
	if ( std::count(format.begin(),format.end(),'q') > 1)
	  qpp_data_error("Bad geometry format: charges requested more then once",tok.line_number());
      }

    bool xgeom = xchrg || nxr>0 || nxi>0 || nxb>0;

    //std::cout << "parse_geom: xgeom= " << xgeom << "n r i b = " << nxr << " " 
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

    int nat = 0;

    while(true)
      {
	STRING line = tok.get();
	
	//debug
	//std::cout << "\"" << line <<"\"" << "\n";

	if (line == "}")
	  break;
	if (line.find_first_not_of(" \t") == std::string::npos && tok.get() == "}")
	  break;

	std::vector<STRING> fields = split(line);

	//debug
	//for (int i=0; i<fields.size(); i++)
	//  std::cout << "split:: \"" << fields[i] << "\"\n";

	if (fields.size() == 0)
	  continue;
  
	/*	std::cout << fields.size() << " " << format.size()<< "\n";
	for (int i=0; i<fields.size(); i++)	
	std::cout << i << "|" << fields[i] << "\n";
	*/
  
	if ( fields.size() != format.size() )
	  {
	    std::cerr << "format \"" << format << "\"\n";
	    qpp_data_error("Error: wrong number of fields",tok.line_number());
	  }

	if (format == "axyz")
	  {
	    lace::vector3d<VALTYPE> r;
	    if ( (!s2t<VALTYPE>(fields[1], r(0))) || (!s2t<VALTYPE>(fields[2], r(1))) || 
		 (!s2t<VALTYPE>(fields[3], r(2))) )
	      qpp_data_error("Error: coordinate (real number) expected",tok.line_number());
	    
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

  qpp::qpp_object *parse_any_geom(int dim, std::vector<qpp::qpp_object*>& parm, STRING name, tokenizer & tok);

  // ---------------------------------------------------------
  template <int DIM, class VALTYPE>
  qpp::periodic_cell<DIM, VALTYPE> * parse_vectors(std::vector<qpp::qpp_object*> & parm, 
						   STRING name, tokenizer & tok)
  {
    tok.separate("}");
    tok.dump("");

    qpp::periodic_cell<DIM, VALTYPE>  
      * cl = new qpp::periodic_cell<DIM, VALTYPE>(name);
    int i = 0;
    while(true)
      {
	STRING line = tok.get();

	if (line == "}")
	  break;
	if (line.find_first_not_of(" \t") == std::string::npos && tok.get() == "}")
	  break;

	std::vector<STRING> fields = split(line);
	
	if (fields.size() == 0)
	  continue;

	if (fields.size() != 3)
	  qpp_data_error("Error: wrong number of fields, should be 3",tok.line_number());
	if ( i == DIM)
	  qpp_data_error("Number of vectors is not equal to cell dimension",tok.line_number());

	for (int j=0; j<3; j++)
	  s2t<VALTYPE>( fields[j], (*cl)(i,j) );

	i++;
      }

    if ( i < DIM)
      qpp_data_error("Number of vectors is not equal to cell dimension",tok.line_number());

    tok.dump(" \t");
    tok.separate(",;{}()=");

    return cl;
  }

  // ---------------------------------------------------------

  qpp::qpp_object * parse_any_vectors(int dim, std::vector<qpp::qpp_object*>& parm, 
				      STRING name, tokenizer & tok);
  // ---------------------------------------------------------

  template<class FREAL>
  qpp::qpp_object * parse_g98_basis(std::vector<qpp::qpp_object*>& parm, 
				    STRING name, tokenizer & tok)
  {
    qpp::gencon_basis_data<FREAL> *bas = new qpp::gencon_basis_data<FREAL>(name);

    tok.separate("}");
    tok.dump("");
    
    STRING line = tok.get();

    do{

      std::vector<STRING> lbls;
      split(line, lbls);

      bas -> new_rcrd();

      int n;
      if ( !s2t<int>(lbls[lbls.size()-1],n) || n!=0)
	qpp_data_error("The list of atoms must terminate with 0",tok.line_number());
	
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
	
	tolower(line);
	split(line, lbls);
	if (lbls[0]=="****")
	  break;
	if (lbls.size()!=3)
	  qpp_data_error("Orbital definition expected, must contain 3 fields",tok.line_number());
	
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
	  qpp_data_error("Orbital type notation (s,p,d,..) expected",tok.line_number());
	
	if ( !s2t<int>(lbls[1],np) )
	  qpp_data_error("Number of primitive gaussians expected",tok.line_number());
	
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
	    split(line, fld);
	    if (fld.size()!=l2-l1+2)
	      qpp_data_error("Orbital exponent and contraction coefficient(s) expected",tok.line_number());
	    if ( !s2t<FREAL>(fld[0], sh.alpha(p)) )
	      qpp_data_error("Orbital exponent (real) expected",tok.line_number());
	    for (int i=0; i<=l2-l1; i++)
	      if ( !s2t<FREAL>(fld[i+1], sh.coeff(i,p)) )
		qpp_data_error("Contraction coefficient (real) expected",tok.line_number());
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

  // ---------------------------------------------------------

  qpp::qpp_object * parse_any_basis(std::vector<qpp::qpp_object*>& parm, 
				    STRING name, tokenizer & tok);
  // ---------------------------------------------------------
  
  qpp::qpp_object * parse_declaration(tokenizer & tok);

};


#endif
