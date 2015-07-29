#include <io/qpparser.hpp>
#include <geom/geom.hpp>
#include <geom/geom.hpp>
#include <iostream>
#include <fstream>
#include <io/qpparser.hpp>
int main(int argc, char **argv)
{
  try{
    std::istream * inp;
    if (argc > 1)
      inp = new std::ifstream(argv[1]);
    else
      inp = & std::cin;

    qpp::tokenizer t(*inp);

    qpp::qpp_declaration global("decl","global");

    std::cout << "writing global\n";

    global.write(std::cout);
  
    std::cout << "reading decl\n";

    qpp::qpp_object *q = _qpp_internal::parse_declaration(t, &global);
    global.add(*q);
  
    std::cout << "done reading\n";

    q -> write(std::cout);
  
    qpp::qpp_declaration * d =  (qpp::qpp_declaration*)q;

    qpp::qpp_object * current=d;
  
    do{
      std::string env;
      std::cout << current->name() << "? ";
      std::getline(std::cin, env);
      std::vector<std::string> ff = qpp::split(env);
      if (ff.size()==0) continue;
      if (ff[0]=="cd")
	current = current -> getobject(ff[1],qpp::qscope_global);
      else if (ff[0]=="print")
	{
	  qpp::qpp_object * p = current;
	  if (ff.size()>1)
	    p = current->getobject(ff[1],qpp::qscope_global);
	  
	  if (p!=NULL)
	    {
	      std::cout << "type = " << std::hex << p->gettype() << std::dec << "\n";
	      p -> write(std::cout);
	    }
	  else
	    std::cout << "not defined\n";
	  
	}
      else if (ff[0]=="int")
	{
	  int i;
	  bool s = current->getparamvalue<int>(i,ff[1],qpp::qscope_global);
	  if (s)
	    std::cout << i << "\n";
	  else 
	    std::cout << "not defined\n";
	} 
      else if (ff[0]=="real")
	{
	  double d;
	  bool s = current->getparamvalue<double>(d,ff[1],qpp::qscope_global);
	  if (s)
	    std::cout << d << "\n";
	  else 
	    std::cout << "not defined\n";
	}
      else if (ff[0]=="bool")
	{
	  bool b;
	  bool s = current->getparamvalue<bool>(b,ff[1],qpp::qscope_global);
	  if (s)
	    std::cout << b << "\n";
	  else 
	    std::cout << "not defined\n";
	}
      else if (ff[0]=="list")
	{
	  for (int i=0; i<current->n_nested(); i++)
	    std::cout << i << " " << current->nested(i)->category() << " " 
		      << current->nested(i)->name() << "\n";
	}
      else if (ff[0]=="exit")
	break;
      std::cout << "\n\n";
    } while(true);


    /*  
    std::cout << " -------------------------- Types ---------------------------\n";

    for (int i=0; i < d->n_decl(); i++)
      {
	std::cout << "nested " << i << " type= " << d->decl(i)->gettype() << "\n";
	std::cout << "line " << d->decl(i)->line() << " filename " 
		  << d->decl(i)->fname() << "\n";
	d->decl(i)->write(std::cout);
	std::cout << "\n";
      }
  
    std::cout << " -------------------------- Geometries ---------------------------\n";
  
    for (int i=0; i < d->n_decl(); i++)
      if ( (d->decl(i)->gettype() & qpp::qtype_geometry) || 
	   (d->decl(i)->gettype() & qpp::qtype_xgeometry))
	d->decl(i)->write(std::cout);
    std::cout << " -------------------------- Basis sets ---------------------------\n";
    for (int i=0; i < d->n_decl(); i++)
      if ( (d->decl(i)->gettype() & qpp::qtype_basis) )
	d->decl(i)->write(std::cout);
    */
  }
  catch (qpp::qpp_exception & e)
    {
      std::cerr << "QPP exception:\n";
      std::cerr << e.what() << "\n";
    }
}

