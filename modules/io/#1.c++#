#include <qpparser.hpp>
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

template<typename _CharT> 
struct param_list;

template<typename _CharT> 
struct param_node{

  std::basic_string<_CharT> param, val;

  param_list<_CharT> * list;

  param_node(std::basic_string<_CharT> _param, std::basic_string<_CharT> _val)
  {
    param = _param; val = _val;
    list = NULL;
  }

  param_node(std::basic_string<_CharT> _param, param_list<_CharT> * _list)
  {
    param = _param; val = "";
    list = _list;
  }

  void reduce()
  {
    if (list != NULL && list->size()==1 && (*list)[0].param=="" )
      {
	val = (*list)[0].val;
	delete list;
	list = NULL;
      }
  }

  ~param_node()
  {
    if (list != NULL)
      delete list;
  }

};

// ----------------------------------------------------------------------

template<typename _CharT> 
struct param_list{

  std::vector<param_node<_CharT>*> list;

  param_node<_CharT> & operator[](int i){return *list[i];}

  int size(){return list.size();}

  void debug(int shift)
  {
    for (int j=0; j<shift; j++) std::cout << " ";
    std::cout << "list size = " << size() << "\n";
    for (int i=0; i<size(); i++){
      for (int j=0; j<shift; j++) std::cout << " ";
      std::cout << "\"" << list[i] -> param << "\"";
      if (list[i]->list == NULL)
	std::cout << " = \"" <<  list[i]->val << "\"\n";
      else
	{
	  std::cout << "(\n";
	  list[i]->list->debug(shift+3);
	  for (int j=0; j<shift; j++) std::cout << " ";
	  std::cout << ")\n";
	}
    }
  }

  ~param_list()
  {
    for (int i=0; i<size(); i++)
      delete list[i];
  }
};

// ----------------------------------------------------------------------

template<typename _CharT> 
struct qpp_data_node{
  std::basic_string<_CharT> object_name, object_type;

  param_list<_CharT> * plist;

  std::vector<qpp_data_node<_CharT>*> body;

  qpp_data_node(){plist=NULL;}

  void debug(int shift)
  {
    for (int j=0; j<shift; j++) std::cout << " ";
    std::cout << "type: " << object_type << " name: " << object_name << "\n";
    if (plist != 0) plist->debug(shift);
    if (body.size()>0) 
      {
	for (int j=0; j<shift; j++) std::cout << " ";
	std::cout << "nested:\n";
	for (int i=0; i<body.size(); i++)
	  body[i] -> debug(shift+3);
	for (int j=0; j<shift; j++) std::cout << " ";
	std::cout << "end nested:\n";
      }
  }
};

// ----------------------------------------------------------------------

template<typename _CharT> 
void remove_blanks(std::basic_string<_CharT> & str)
{
  //debug
  // std::cout << "remove blanks \"" << str << "\"\n";
  int i = str.find_first_not_of(" \t");
  if (i == std::string::npos)
    str = "";
  else
    str = str.substr(i);
  //std::cout << "removed \"" << str << "\"\n";
}

template<typename _CharT>
std::basic_string<_CharT> first_field(std::basic_string<_CharT> & str)
{
  remove_blanks(str);
  int j;
  
  if (str[0] == '\"')
    {
      // special case - the string value in ""
      j = str.substr(1).find_first_of('\"');
      assert( j!=std::string::npos && "!!! Missing closing \" !!!");
      j+=2;
    }
  else
    j = str.find_first_not_of(
        "abcdefghijklmnopqrstuvwxyzABCDEDFGIJKLMNOPQRSTUVWXYZ1234567890.-+_");
  
  std::basic_string<_CharT> result = str.substr(0,j);
  if (j < str.size())
    {
      str = str.substr(j);
      remove_blanks(str);
    }
  else
    str = "";
  return result;
}

template<typename _CharT, class _Traits>
std::basic_string<_CharT> get_nonempty_line(std::basic_istream<_CharT, _Traits>  & input)
{
  std::basic_string<_CharT> str;
  do
    {
      std::getline(input,str);
      remove_blanks(str);
    } while ( str == "" && input.eof());
  return str;
}

template<typename _CharT, class _Traits>
void first_nonempty_symbols(std::basic_string<_CharT> & line, std::basic_istream<_CharT, _Traits>  & input)
{
  int i;
  while ( (i = line.find_first_not_of(" \t")) == std::string::npos )
    {
      if ( ! input.eof() )
	std::getline(input,line);
      else
	{
	  i = 0;
	  break;
	}
    }
  line = line.substr(i);
  //std::cout << "nonempty: \"" << line << "\"\n";
}

template<typename _CharT, class _Traits>
param_list<_CharT>* parse_parameters(std::basic_string<_CharT> & first_line, 
				    std::basic_istream<_CharT, _Traits>  & input)
{
  std::basic_string<_CharT> line = first_line;
  first_nonempty_symbols(line,input);
  
  assert(line[0]=='(' && "!!! Block of parameters must start with \'(\' !!!");
  line = line.substr(1);

  bool finished = false;
  int i = 0;
  
  param_list<_CharT>* list = new param_list<_CharT>;

  do
    {
      std::basic_string<_CharT> field1 = first_field(line), field2="";
      bool nested = false;
     
      while (field1 == "")
	{
	  assert( line == "" && "!!! Unrecognized symbols instead of parameter !!!");
	  line = get_nonempty_line(input);
	  assert( !input.eof() && "!!! Unexpected end of input !!!");
	  field1 = first_field(line);
	}
      
      if (line == "")
	{
	  line = get_nonempty_line(input);
	  assert( !input.eof() && "!!! Unexpected end of input !!!");
	}      
      
      _CharT delim = line[0];

      if (line[0]=='=')
	{
	  // parameter = value
	  line = line.substr(1);
	  field2 = first_field(line); 
	  while (field2 == "")
	    {
	      assert( line == "" && "!!! Unrecognized symbols instead of parameter !!!");
	      line = get_nonempty_line(input);
	      assert( !input.eof() && "!!! Unexpected end of input !!!");
	      field2 = first_field(line);
	    }   
	  
	  std::cout << "parameter[" << i << "] = " << field1 << " value[" << i << "] = " << field2 << "\n";
	  list -> list.push_back( new param_node<_CharT>(field1,field2) );

	  if (line == "")
	    {
	      line = get_nonempty_line(input);
	      assert( !input.eof() && "!!! Unexpected end of input !!!");
	    }      
	  
	  delim = line[0];
	  
	}
      else if (delim == '(' )
	{
	  // nested parameters block
	  std::cout << "parameter[" <<  i << "] = " << field1 << "\n";
	  std:: cout << "nested parameters block\n";
	  list -> list.push_back( new param_node<_CharT>(field1,
							 parse_parameters(line,input)));
	  std::cout << "debug:\n" << '\"' << line << "\"\n";
	  std:: cout << "end nested parameters block\n";
	  
	  if (line == "")
	    {
	      line = get_nonempty_line(input);
	      assert( !input.eof() && "!!! Unexpected end of input !!!");
	    }      
	  delim = line[0];
	  nested = true;
	}
      
      if ( delim ==')' || delim == ',')
	{
	  if ( delim ==')')
	    finished = true;
	  line = line.substr(1);
	  
	  if (field2=="" && ! nested)
	    {
	      std::cout << "parameter[" << i << "] = \"\" value[" << i << "] = " << field1 << "\n";
	      list -> list.push_back( new param_node<_CharT>("",field1) );
	    }
	}
      else 
	assert(false && "!!! Unrecognized delimiter symbol in parameter lits!!!");

      i++;

    } while (!finished);
  first_line = line;
  return list;
}

//----------------------------------------------------------------------------

template<typename _CharT, class _Traits>
qpp_data_node<_CharT> * parse_qpp_statement(std::basic_string<_CharT> & first_line, 
					    std::basic_istream<_CharT, _Traits>  & input, int level)
{
  std::basic_string<_CharT> line = first_line;
  first_nonempty_symbols(line,input);

  std::basic_string<_CharT> field1="", field2="";

  field1 = first_field(line);

  if (field1 == "")
    return NULL;
  else
    {      
      qpp_data_node<_CharT> *node = new qpp_data_node<_CharT>;
      
      first_nonempty_symbols(line,input);
      assert( !input.eof() && "!!! Unexpected end of input !!!");

      if (line[0]=='=')
	{
	  // name = object() form found
	  line = line.substr(1);

	  first_nonempty_symbols(line,input);
	  field2 = first_field(line);

	  assert(field2 != "" && "!!! Identifier or value expected !!!");

	  first_nonempty_symbols(line,input);

	  node -> object_type = field1;
	  node -> object_name = field2;
	  if (line[0]=='(')
	    node -> plist = parse_parameters(line,input);
	  else
	    node -> plist = NULL;
	}
      else
	{
	  node -> object_type = field1;

	  field2 = first_field(line);
	  first_nonempty_symbols(line,input);
	  node -> object_name = field2;

	  std::cout << "statement " << field1 << " " << field2 << "\n";

	  if (line[0]=='(')
	    node -> plist = parse_parameters(line,input);
	  
	  first_nonempty_symbols(line,input);

	  if (line[0]=='{')
	    {	    
	      // check for special blocks
	      if ( node -> object_type == "fragment" ||  node -> object_type == "geometry" ||
		   node -> object_type ==  "geom" )
		{ 
		  // read geometry		  
		  do 
		    {
		      std::getline(input, line);
		      std::cout << line << "\n";
		    }
		  while ( line.find_first_of('}') == std::string::npos );
		  line = line.substr( line.find_first_of('}')+1);
		  first_nonempty_symbols(line,input);
		  std::cout << "here1\n";
		}
	      else if (node -> object_type == "vectors" ||  node -> object_type == "cell")
		{ 
		  // read vectors		  
		  do 
		    {
		      std::getline(input, line);
		      std::cout << line << "\n";
		    }
		  while ( line.find_first_of('}') == std::string::npos );
		  line = line.substr( line.find_first_of('}')+1);	    
		  first_nonempty_symbols(line,input);
		  std::cout << "here2\n";
		}
	      else
		{
		  line = line.substr(1);
		  first_nonempty_symbols(line,input);
		  qpp_data_node<_CharT> * nested;
		  while ( (nested = parse_qpp_statement(line,input,level+1)) != NULL)
		    {
		      node -> body.push_back(nested);
		      std::cout << "level= " << level << "\n";
		      nested -> debug(level+3);
		    }
		  first_nonempty_symbols(line,input);
		  assert(line[0]=='}' && "!!! } expected");
		  line = line.substr(1);
		}
	    }
	}
      first_line = line;
      return node;
    }
}

int main()
{

  std::string s;
  /*  std::getline(std::cin,s);
  first_nonempty_symbols(s,std::cin);
  if (s[0]=='{')
    {
      s=s.substr(1);
      do
	{
	  qpp_data_node<char>* dn =  parse_qpp_statement(s,std::cin);
	  dn -> debug(1);
	  first_nonempty_symbols(s,std::cin);
	} while (s[0]!='}');
    }
  */
  std::vector<qpp_data_node<char>*> inp;
  std::fstream f("example.qpp");
  std::getline(f,s);
  first_nonempty_symbols(s,f);
  do
    {
      qpp_data_node<char>* dn =  parse_qpp_statement(s,f,0);
      if (dn != NULL) inp.push_back(dn);
      first_nonempty_symbols(s,f);
    } while ( ! f.eof() );
  
  for (int i=0; i<inp.size(); i++)
    inp[i] -> debug(1);  
}
