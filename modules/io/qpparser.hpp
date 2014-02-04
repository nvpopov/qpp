#ifndef _QPPARSER_H
#define _QPPARSER_H

#include <algorithm>
#include <string>
#include <sstream>
#include <ios>
#include <iostream>
#include <io/qppdata.hpp>
#include <geom/geom.hpp>
#include <geom/atom.hpp>

#include <stdlib.h>

namespace _qpp_internal{

  // -------------------- Simple tokenizer -----------------------------------

  template<typename _CharT, class _Traits = std::char_traits<_CharT> >
  class tokenizer
  {
    std::basic_istream<_CharT, _Traits> * _input;
    std::basic_string<_CharT> _buff, _dump, _sepr;
    int _line_number;
    
  public:
    
    tokenizer(std::basic_istream<_CharT, _Traits> & input)
    {
      _input = & input;
      _dump = " \t";
      _line_number = 0;
    }

    tokenizer(std::basic_string<_CharT> str)
    {
      _input = new std::stringstream(str);
      _dump = " \t";
      _line_number = 0;
    }
    
    void dump(std::basic_string<_CharT> smb)
    {
      _dump = smb;
    }
    
    void separate(std::basic_string<_CharT> smb)
    {
      _sepr = smb;
    }
    
    std::basic_string<_CharT> get()
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
	  if (i != std::string::npos)
	    {
	      _buff = _buff.substr(i);
	      break;
	    }
	  std::getline(*_input, _buff);	
	  _line_number++;
	} while ( !_input -> eof() );
      
      if ( _input -> eof() )
	return "";
      
      std::basic_string<_CharT> rez;
      i = _buff.find_first_of(_sepr + _dump);
      if (i==0)
	{
	  rez = _buff.substr(0,1);
	  _buff = _buff.substr(1);
	  
	}
      else if (i != std::string::npos)
	{
	  rez =  _buff.substr(0,i);
	  _buff = _buff.substr(i);
	}
      else
	{
	  rez =  _buff;
	  _buff = "";
	}
      return rez;
    }
    
    void back(std::basic_string<_CharT> s)
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
  
  void qpp_data_error(std::string s, int l)
  // fixme - think of some error management
  {
    std::cerr << s << " in line " << l << "\n";
    exit(1);
  }

  // -----------------------------------------------------------

  void tolower(std::string s)
  {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
  }

  
  std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) 
  {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) 
      if (item.size()>0)
	elems.push_back(item);
    
    return elems;
  }

  std::vector<std::string> split(const std::string &s, char delim = ' ') 
  {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
  }
  
  // -------------------------------- string to type T convertor ----------------------------
  
  template<typename T>
  T s2t(std::string val);
  
  template<>
  double s2t<double>(std::string val)
  {
    return atof(val.c_str());
  }

  template<>
  float s2t<float>(std::string val)
  {
    return atof(val.c_str());
  }
  
  template<>
  int s2t<int>(std::string val)
  {
    return atoi(val.c_str());
  }

  template<>
  bool s2t<bool>(std::string val)
  {
    tolower(val);
    if ( (val == "y") || (val == "yes") || (val == "true") || (val == "t") || (val == "1"))
      return true;
    else if ((val == "n") || (val == "no") || (val == "false") || (val == "f") || (val == "0"))
      return false;
    else
      {} //fixme - error handling
  }
  // ----------------------------------------------------------------

  template <class charT, class traits>
  qpp::qpp_param_array<charT,traits> * parse_parameters(tokenizer<charT,traits> & tok)
  {
    tok.dump(" \t");
    tok.separate(",;{}()=");
    qpp::qpp_param_array<charT,traits> * lst = new  qpp::qpp_param_array<charT,traits>, * nested_lst = NULL;
    
    std::string field1, field2, smb;
    bool first = true, nested = false;
    
    do
      {
	field1 = tok.get();
	
	if ( field1.find_first_of(",;{}()") != std::string::npos )
	  {
	    if (field1 == ")" && first)
	      // empty parameter list
	      return lst;
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
	    nested_lst = parse_parameters(tok);
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
	
	qpp::qpp_parameter_tree<charT,traits> * pn = new qpp::qpp_parameter_tree<charT,traits>(field1,field2);
	if (nested)
	  pn -> parameters = *nested_lst;
	
	lst -> add(*pn);
	
	if (smb == ")")
	  // We are finished
	  break;
	
	if (smb != ",")
	  qpp_data_error("Error: \',\' expected in parameter list", tok.line_number());
	
      } while(true);
    
    return lst;
  }

  // ---------------------------------------------------------

  template <int DIM, class VALTYPE, class charT, class traits>
  qpp::geometry<qpp::qpp_atom*, DIM, VALTYPE, charT,traits> * 
  parse_geom(qpp::qpp_param_array<charT,traits> * parm, std::basic_string<charT,traits> name, 
	     tokenizer<charT,traits> & tok)
  {
    tok.separate("}");
    tok.dump("");

    bool xtra = false, xchrg = false, xmass = false;
    int nxr=0, nxi=0, nxb=0;
    std::string format;

    if (parm == NULL)
      format = "axyz";
    else
      {
	int i=0;
	if ( parm -> value(0) == "3d" || parm -> value(0) == "2d" || 
	     parm -> value(0) == "1d" || parm -> value(0) == "0d")
	  i=1;
	while (i < parm->size())
	  {
	    std::string v = parm -> value(i);
	    tolower(v);
	    if (v == "atom")
	      format += "a";
	    else if ( v == "x" || v == "y" || v == "z")
	      format += v;
	    else if ( v == "charge")
	      {
		format += "q";
		xchrg = true;
	      }
	    else if ( v == "real")
	      {
		format += "r";
		nxr++;
	      }
	    else if ( v == "int")
	      {
		format += "i";
		nxi++;
	      }
	    else if ( v == "bool")
	      {
		format += "b";
		nxb++;
	      }
	    else if ( v == "mass")
	      {
		format += "m";
		xmass = true;
	      }
	    else if ( v == "number" || v == "num" || v == "mendeleev" )
	      format += "n";
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
    qpp::geometry<qpp::qpp_atom*, DIM, VALTYPE, charT,traits> * geom;
    qpp::xtr_geometry<qpp::qpp_atom*, DIM, VALTYPE, charT,traits> * xtr_geom = NULL;

    if (xgeom)
      {
	xtr_geom = new qpp::xtr_geometry<qpp::qpp_atom*, DIM, VALTYPE, charT,traits>(xchrg,nxr,nxi,nxb,name);
	geom = xtr_geom;
      }
    else
      geom = new qpp::geometry<qpp::qpp_atom*, DIM, VALTYPE, charT,traits>(name);

    int nat = 0;

    while(true)
      {
	std::basic_string<charT,traits> line = tok.get();
	//std::cout << "\"" << line <<"\"" << "\n";
	if (line == "}")
	  break;
	std::vector<std::basic_string<charT,traits> > fields = split(line);

	if (fields.size() == 0)
	  continue;

	/*	std::cout << fields.size() << " " << format.size()<< "\n";
	for (int i=0; i<fields.size(); i++)	
	std::cout << i << "|" << fields[i] << "\n";
	*/
	
	if ( fields.size() != format.size() )
	  qpp_data_error("Error: wrong number of fields",tok.line_number());

	if (format == "axyz")
	  geom -> add_point( new qpp::qpp_atom(fields[0]), s2t<VALTYPE>(fields[1]), 
			     s2t<VALTYPE>(fields[2]), s2t<VALTYPE>(fields[3]) );
	else
	  {
	    geom -> add_point( NULL, VALTYPE(0), VALTYPE(0), VALTYPE(0));	 

	    std::string aname = "";
	    int anum = 0, ixr = 0, ixi = 0, ixb = 0;
	    VALTYPE ax = 0, ay = 0, az = 0, amass = 0, achrg = 0;
	    for (int i=0; i < fields.size(); i++)
	      {
		switch( format[i] )
		  {
		  case 'a': aname = fields[i];
		    break;
		  case 'n': anum = s2t<int>(fields[i]);
		    break;
		  case 'x': ax = s2t<VALTYPE>(fields[i]);
		    break;
		  case 'y': ay = s2t<VALTYPE>(fields[i]);
		    break;
		  case 'z': az = s2t<VALTYPE>(fields[i]);
		    break;
		  case 'q': achrg = s2t<VALTYPE>(fields[i]);
		    xtr_geom -> charge(nat) = achrg;		   
		    break;
		  case 'm': amass = s2t<VALTYPE>(fields[i]);
		    break;
		  case 'r': xtr_geom -> xtr_real(nat,ixr) = s2t<VALTYPE>(fields[i]);
		    ixr++; break;
		  case 'i': xtr_geom -> xtr_int(nat,ixi) = s2t<int>(fields[i]);
		    ixi++; break;
		  case 'b': xtr_geom -> xtr_bool(nat,ixb) = s2t<bool>(fields[i]);
		    ixb++; break;
		  }		
	      }
	    if ( xchrg || xmass )
	      geom -> atom(nat) = new qpp::classical_atom(aname, anum, achrg, amass);
	    else
	      geom -> atom(nat) = new qpp::qpp_atom(aname, anum);
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

  template <class charT, class traits>
  qpp::qpp_object<charT,traits> * parse_any_geom(int dim, qpp::qpp_param_array<charT,traits> * parm, 
						 std::basic_string<charT,traits> name, tokenizer<charT,traits> & tok)
  {
    if (dim == 0)
      return parse_geom<0,double,charT,traits>(parm,name,tok);
    else if (dim == 1)
      return parse_geom<1,double,charT,traits>(parm,name,tok);
    else if (dim == 2)
      return parse_geom<2,double,charT,traits>(parm,name,tok);
    else if (dim == 3)
      return parse_geom<3,double,charT,traits>(parm,name,tok);
  }

  // ---------------------------------------------------------
  template <int DIM, class VALTYPE, class charT, class traits>
  qpp::periodic_cell<DIM, VALTYPE, charT,traits> * 
  parse_vectors(qpp::qpp_param_array<charT,traits> * parm, std::basic_string<charT,traits> name, 
	     tokenizer<charT,traits> & tok)
  {
    tok.separate("}");
    tok.dump("");

    qpp::periodic_cell<DIM, VALTYPE, charT,traits>  * cl = new qpp::periodic_cell<DIM, VALTYPE, charT,traits>(name);
    int i = 0;
    while(true)
      {
	std::basic_string<charT,traits> line = tok.get();
	if (line == "}")
	  break;
	std::vector<std::basic_string<charT,traits> > fields = split(line);
	
	if (fields.size() == 0)
	  continue;

	if (fields.size() != 3)
	  qpp_data_error("Error: wrong number of fields, should be 3",tok.line_number());
	if ( i == DIM)
	  qpp_data_error("Number of vectors is not equal to cell dimension",tok.line_number());

	for (int j=0; j<3; j++)
	  (*cl)(i,j) = s2t<VALTYPE>(fields[j]);

	i++;
      }

    if ( i < DIM)
      qpp_data_error("Number of vectors is not equal to cell dimension",tok.line_number());

    return cl;
  }

  // ---------------------------------------------------------

  template <class charT, class traits>
  qpp::qpp_object<charT,traits> * parse_any_vectors(int dim, qpp::qpp_param_array<charT,traits> * parm, 
						 std::basic_string<charT,traits> name, tokenizer<charT,traits> & tok)
  {
    if (dim == 0)
      return parse_vectors<0,double,charT,traits>(parm,name,tok);
    else if (dim == 1)
      return parse_vectors<1,double,charT,traits>(parm,name,tok);
    else if (dim == 2)
      return parse_vectors<2,double,charT,traits>(parm,name,tok);
    else if (dim == 3)
      return parse_vectors<3,double,charT,traits>(parm,name,tok);
  }

  // ---------------------------------------------------------
  
  template <class charT, class traits>
  qpp::qpp_object<charT,traits> * parse_declaration(tokenizer<charT,traits> & tok)
  {
    std::basic_string<charT,traits> field1, field2, smb;
    
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
	
	qpp::qpp_parameter_tree<charT,traits> * pn = new qpp::qpp_parameter_tree<charT,traits>(field1,field2);
	smb = tok.get();
	
	if (smb=="(")
	  {
	    pn -> parameters = * parse_parameters(tok);
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

    qpp::qpp_param_array<charT,traits>  *parm = NULL;
    bool must_have_nested = true;
    
    if (smb == "(")
      // object name() case
      {
	parm = parse_parameters(tok);
	must_have_nested = false;
	smb = tok.get();
      }

    if ( field1 == "geometry" || field1 == "fragment" )
      {
	// determine the dimension first
	int dim = 0;
	if (parm != NULL && parm -> size() > 0)
	  {
	    if ( parm->value(0) == "3d" )
	      dim = 3;
	    else if ( parm->value(0) == "2d" )
	      dim = 2;
	    else if ( parm->value(0) == "1d" )
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
	if (parm != NULL && parm -> size() > 0)
	  {
	    if ( parm->value(0) == "3d" )
	      dim = 3;
	    else if ( parm->value(0) == "2d" )
	      dim = 2;
	    else if ( parm->value(0) == "1d" )
	      dim = 1;
	  }
	return parse_any_vectors(dim, parm, field2, tok);
      }
      
    qpp::qpp_declaration_tree<charT,traits> * pn = new qpp::qpp_declaration_tree<charT,traits>(field1,field2);

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
	    pn -> declarations.add( * parse_declaration(tok) );	
	    smb = tok.get();
	  }
      }
    
    else if (smb != ";")
      qpp_data_error("Error: \';\' expected ",tok.line_number());
    
    return pn;
    
  }

};


#endif
