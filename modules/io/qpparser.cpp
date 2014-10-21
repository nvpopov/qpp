#include "io/qpparser.hpp"

namespace qpp{

  // -----------------------------------------------------------
  template<>
  bool s2t<bool>(const STRING & s, bool & val)
  {
    STRING s1 = s;
    _qpp_internal::tolower(s1);
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

  void qpp_read(std::basic_istream<CHAR,TRAITS> & is, std::vector<qpp::qpp_object*> & decls)
  {
    _qpp_internal::tokenizer t(is);
    qpp::qpp_object * decl;
    while ( (decl=parse_declaration(t)) != NULL)
      decls.push_back(decl);
  }

};


namespace _qpp_internal{
  

  tokenizer::tokenizer(std::basic_istream<CHAR,TRAITS> & input)
  {
    _input = & input;
    _dump = " \t";
    _line_number = 0;
    sstr = false;
  }
  
  tokenizer:: tokenizer(const STRING & str)
  {
    _input = new std::basic_stringstream<CHAR,TRAITS>(str);
    _dump = " \t";
    _line_number = 0;
    sstr = true;
  }

  tokenizer::~tokenizer()
  {
    if (sstr)
      delete _input;
  }
    
  void tokenizer::dump(const STRING & smb)
  {
    _dump = smb;
  }
    
  void tokenizer::separate(const STRING & smb)
  {
    _sepr = smb;
  }
    
  STRING tokenizer::get()
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
    
  void tokenizer::back(STRING s)
  {
    _buff = s + " " + _buff;
  }
    
  bool tokenizer::eof()
  {
    return _input -> eof() && _buff == "";
  }
    
  int tokenizer::line_number()
  {
    return _line_number;
  }



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

  void split(const STRING &s, std::vector<STRING> &elems, STRING delims ) 
  // fixme - not efficient!
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

  std::vector<STRING> split(const STRING &s, STRING delims) 
  {
    std::vector<STRING> elems;
    split(s, elems, delims);
    return elems;
  }

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

  // -------------------------------------------------------------------------------

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

  // -------------------------------------------------------------------------------

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


  // -------------------------------------------------------------------------------

  qpp::qpp_object * parse_declaration(tokenizer & tok)
  {
    STRING field1, field2, smb;
    
    tok.dump(" \t");
    tok.separate(",;{}()=");
    
    field1 = tok.get();

    if (field1 == "")
      return NULL;

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
