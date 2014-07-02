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

namespace _qpp_internal{

  using qpp::TRAITS;

  // -------------------- Simple tokenizer -----------------------------------

  class tokenizer
  {
    std::basic_istream<CHAR,TRAITS> * _input;
    STRING _buff, _dump, _sepr;
    int _line_number;
    bool sstr;
    
  public:
    
    tokenizer(std::basic_istream<CHAR,TRAITS> & input)
    {
      _input = & input;
      _dump = " \t";
      _line_number = 0;
      sstr = false;
    }

    tokenizer(const STRING & str)
    {
      _input = new std::basic_stringstream<CHAR,TRAITS>(str);
      _dump = " \t";
      _line_number = 0;
      sstr = true;
    }

    ~tokenizer()
    {
      if (sstr)
	delete _input;
    }
    
    void dump(const STRING & smb)
    {
      _dump = smb;
    }
    
    void separate(const STRING & smb)
    {
      _sepr = smb;
    }
    
    STRING get()
    {
      int i;
      if (_buff == "" )
	{
	  std::getline(*_input, _buff);

	  _line_number++;
	}

      do
	{
	  i = _buff.find_first_not_of(_dump);
	  
	  //debug
	  //std::cout << "i = " << i << "\""  << _buff << "\"\n";
	  if (i != std::string::npos)
	    {
	      _buff = _buff.substr(i);
	      break;
	    }
	  else if ( !_input -> eof() )
	    {
	      std::getline(*_input, _buff);	
	      _line_number++;
	    }
	  else
	    {
	      _buff = "";
	      break;
	    }
	} while ( true );
      
      if ( _input -> eof() && _buff.size()==0 )
	return "";
      
      //debug
      //std::cout << "\"" << _buff << "\"\n";

      STRING rez;
      i = _buff.find_first_of(_sepr + _dump);
      if (i==0)
	{
	  //debug
	  //std::cout << "here1\n";

	  rez = _buff.substr(0,1);
	  _buff = _buff.substr(1);
	  
	}
      else if (i != std::string::npos)
	{
	  //debug
	  //std::cout << "here2\n";

	  rez =  _buff.substr(0,i);
	  _buff = _buff.substr(i);
	}
      else
	{
	  //debug
	  //std::cout << "here3\n";

	  rez =  _buff;
	  _buff = "";
	}
      return rez;
    }
    
    void back(STRING s)
    {
      _buff = s + " " + _buff;
    }
    
    bool eof()
    {
      return _input -> eof() && _buff == "";
    }
    
    int line_number()
    {
      return _line_number;
    }
    
  };

  // -----------------------------------------------------------
  
  void qpp_data_error(STRING s, int l)
  // fixme - think of some error management
  {
    std::cerr << s << " in line " << l << "\n";
    exit(1);
  }

  // -----------------------------------------------------------

  void tolower(STRING & s)
  {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
  }

  // -----------------------------------------------------------  

  void split(const STRING &s, std::vector<STRING> &elems, STRING delims = " \t") 
  {
    tokenizer tok(s);
    tok.dump(delims);
    tok.separate("");
    elems.clear();

    do {
      STRING item = tok.get();
      //std::cout << "split:\"" << item << "\"";
      if (item.size()==0)
	break;
      elems.push_back(item);
    } while(true);
    
  }

  // -----------------------------------------------------------

  std::vector<STRING> split(const STRING &s, STRING delims = " \t") 
  {
    std::vector<STRING> elems;
    split(s, elems, delims);
    return elems;
  }
  
  // -------------------------------- string to type T convertor ----------------------------
  
  template<typename T>
  bool s2t(const STRING & s, T & val)
  {
    std::basic_stringstream<CHAR,TRAITS> ss(s);
    ss >> val;
    return !ss.fail();
  }
  
  template<>
  bool s2t<bool>(const STRING & s, bool & val)
  {
    STRING s1 = s;
    tolower(s1);
    if ( (s1 == "y") || (s1 == "yes") || (s1 == "true") || (s1 == "t") || (s1 == "1"))
      {
	val = true;
	return true;
      }
    else if ((s1 == "n") || (s1 == "no") || (s1 == "false") || (s1 == "f") || (s1 == "0"))
      {
	val = false;
	return true;
      }
    else
      {
	return false;
      }
  }

  // ----------------------------------------------------------------

  void parse_parameters(std::vector<qpp::qpp_object*> & lst, tokenizer & tok);

  // ----------------------------------------------------------------

  void parse_parameters(std::vector<qpp::qpp_parameter<STRING>*> & lst, tokenizer & tok)
  {
    std::vector<qpp::qpp_object*> nested_lst;
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
	      qpp_data_error("Incorrect parameter list", tok.line_number());
	  }
	
	// now field1 != one of special characters
	
	field2 = tok.get();
	
	if (field2 == "=")
	  // parameter=value case
	  {
	    field2 = tok.get();
	    if ( field2.find_first_of(",;{}()") != std::string::npos )
	      qpp_data_error("Error after \'=\' sign in parameter list", tok.line_number());
	    
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
	
	if (smb == "(")
	  // nested parameter list
	  {
	    parse_parameters(nested_lst, tok);
	    nested = true;
	    smb = tok.get();
	  }
	else
	  nested = false;
	
	if (nested && field1 == "")
	  {
	    field1 = field2;
	    field2 = "";
	  }
	
	qpp::qpp_parameter<STRING> * pn = new qpp::qpp_parameter<STRING>(field1,field2);
	if (nested)
	  for (int i=0; i<nested_lst.size(); i++)
	    pn -> add_parm(*nested_lst[i]);
	
	
	lst.push_back(pn);
	
	if (smb == ")")
	  // We are finished
	  break;
	
	if (smb != ",")
	  qpp_data_error("Error: \',\' expected in parameter list", tok.line_number());
	
      } while(true);

    //debug
    //std::cout << "paramlist:";
    //for (int i=0; i<lst.size(); i++)
    //  lst[i]->write(std::cout);
    
    //    return lst;
  }

  void parse_parameters(std::vector<qpp::qpp_object*> & lst, tokenizer & tok)
  {
    std::vector<qpp::qpp_parameter<STRING>*> parm;
    parse_parameters(parm,tok);
    lst.clear();
    for (int i=0; i<parm.size(); i++)
      lst.push_back(parm[i]);
  }

  // ---------------------------------------------------------
  
  template <int DIM, class VALTYPE> 
  qpp::geometry<DIM, VALTYPE> *  parse_geom(std::vector<qpp::qpp_object*> & parm, 
					    STRING name, tokenizer & tok)
  {
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

	// debug
	std::cout << format << "\n";
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
	  qpp_data_error("Error: wrong number of fields",tok.line_number());

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
		  case 'r': s2t<VALTYPE>(fields[i], xtr_geom -> xtr_real(nat,ixr));
		    ixr++; break;
		  case 'i': s2t<int>(fields[i], xtr_geom -> xtr_int(nat,ixi) );
		    ixi++; break;
		  case 'b': s2t<bool>(fields[i], xtr_geom -> xtr_bool(nat,ixb) );
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

    // geom -> write(std::cout);

    return geom;
  }
  

  // ---------------------------------------------------------

  qpp::qpp_object *parse_any_geom(int dim, std::vector<qpp::qpp_object*>& parm, STRING name, tokenizer & tok)
  {

    if (dim == 0)
      return parse_geom<0,double>(parm,name,tok);
    else if (dim == 1)
      return parse_geom<1,double>(parm,name,tok);
    else if (dim == 2)
      return parse_geom<2,double>(parm,name,tok);
    else if (dim == 3)
      return parse_geom<3,double>(parm,name,tok);

  }


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
				      STRING name, tokenizer & tok)
  {

    if (dim == 0)
      return parse_vectors<0,double>(parm,name,tok);
    else if (dim == 1)
      return parse_vectors<1,double>(parm,name,tok);
    else if (dim == 2)
      return parse_vectors<2,double>(parm,name,tok);
    else if (dim == 3)
      return parse_vectors<3,double>(parm,name,tok);

  }

  // ---------------------------------------------------------

  template<class FREAL>
  qpp::qpp_object * parse_g98_basis(std::vector<qpp::qpp_object*>& parm, 
				    STRING name, tokenizer & tok)
  {
    qpp::gencon_basis<FREAL> *bas = new qpp::gencon_basis<FREAL>(name);

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

      //debug
      std::cout << "labels:";
      int nr = bas->nrcrd()-1;
      for(int i=0; i<bas->rcrd(nr).labels.size(); i++)
	std::cout << " " << bas->rcrd(nr).labels[i];
      std::cout << "\nnumbers:";
      for(int i=0; i<bas->rcrd(nr).numbers.size(); i++)
	std::cout << " " << bas->rcrd(nr).numbers[i];
      std::cout << "\n";

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
	std::cout << "shell " << bas -> rcrd(nr).shells.size() << " nprim = " << np << " l =";
	for (int i=0; i<=l2-l1; i++)
	  std::cout << sh.l(i) << " ";
	std::cout << "\n";

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
				    STRING name, tokenizer & tok)
  {
    if (parm.size()>0)
      {
	STRING basfmt = ((qpp::qpp_parameter<STRING>*)parm[0])->value();
	if (basfmt == "g98" || basfmt == "gauss" || basfmt == "gaussian")
	  return parse_g98_basis<double>(parm,name,tok);
      }
  }

  // ---------------------------------------------------------
  
  qpp::qpp_object * parse_declaration(tokenizer & tok)
  {
    STRING field1, field2, smb;
    
    tok.dump(" \t");
    tok.separate(",;{}()=");
    
    field1 = tok.get();
    if ( field1.find_first_of(",;{}()=") != std::string::npos )
      qpp_data_error("Error: identifier expected, special character found", tok.line_number());
    
    field2 = tok.get();
    
    if (field2 == "=")
      // obj = func(....); or
      // obj = val;        case
      {
	field2 = tok.get();
	if ( field2.find_first_of(",;{}()=") != std::string::npos )
	  qpp_data_error("Error: identifier expected after \'=\' sign ",tok.line_number());
	
	qpp::qpp_parameter<STRING> * pn = new qpp::qpp_parameter<STRING>(field1,field2);
	smb = tok.get();
	
	if (smb=="(")
	  {
	    parse_parameters(pn -> nested_parm(), tok);
	    smb = tok.get();
	  }
	//	else
	// pn -> parameters = new qpp_parameter_list;
	
	if (smb!=";")
	  qpp_data_error("Error: \';\' expected ",tok.line_number());
	
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

    std::vector<qpp::qpp_object*>  parm;
    bool must_have_nested = true;
    
    if (smb == "(")
      // object name() case
      {
	parse_parameters(parm,tok);
	must_have_nested = false;
	smb = tok.get();
      }

    if ( field1 == "geometry" || field1 == "fragment" )
      {
	// determine the dimension first
	int dim = 0;
	if (parm.size() > 0)
	  {
	    STRING s = ((qpp::qpp_parameter<STRING>*)parm[0])->value();
	    if ( s == "3d" )
	      dim = 3;
	    else if ( s == "2d" )
	      dim = 2;
	    else if ( s == "1d" )
	      dim = 1;
	  }
	// debug
	//std::cout << "=============== dimension = " << dim << "\n";

	// fixme - what about VALTYPE?
	return parse_any_geom(dim, parm, field2, tok);

      }

    if ( field1 == "vectors")
      {
		// determine the dimension first
	int dim = 3;
	if ( parm.size() > 0)
	  {
	    STRING s = ((qpp::qpp_parameter<STRING>*)
	       parm[0])->value();
	    if ( s == "3d" )
	      dim = 3;
	    else if ( s == "2d" )
	      dim = 2;
	    else if ( s == "1d" )
	      dim = 1;
	  }
	return parse_any_vectors(dim, parm, field2, tok);
      }

    if ( field1 == "basis" && smb == "{" )
      return parse_any_basis(parm, field2, tok);
      
    qpp::qpp_declaration * pn = new qpp::qpp_declaration(field1,field2);

    for (int i=0; i<parm.size(); i++)
      pn -> add_parm(*parm[i]);

    //else
    //  pn -> parlist = new qpp_parameter_list;
    
    //std::cout << "debug2: nparams= " << pn->parlist->size() << " musthave= " << must_have_nested << "\n";
    
    if ( must_have_nested && smb != "{")
      qpp_data_error("Error: \'{\' block expected ",tok.line_number());
    
    //std::cout << "debug2.1: " << smb  << " bool " << (smb == "{") << "\n";
  
    if ( smb == "{" )
      {
	//std::cout << "debug2.2: " << smb << "\n";
	smb = tok.get();
	while ( smb != "}")
	  {
	    //std::cout << "debug3: " << smb << "\n";
	    tok.back(smb);
	    pn -> add_decl( * parse_declaration(tok) );	
	    smb = tok.get();
	  }
      }
    
    else if (smb != ";")
      qpp_data_error("Error: \';\' expected ",tok.line_number());
    
    return pn;
    
  }

};


#endif
