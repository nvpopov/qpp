#include <io/qpparser.hpp>
#include <geom/geom.hpp>
#include <geom/geom.hpp>
#include <iostream>
#include <fstream>
#include <io/qpparser.hpp>
#include <io/compile.hpp>
#include <data/meta.hpp>

STRING red(const STRING & s)
{
 return  "\033[1;31m" + s + "\033[0m";
}


template <class T> 
void editval(qpp::metaparam_structure * parm)
{
  T val;

  if (parm -> producer -> has_value_list())
    {
      std::cout << "Select value from the list:\n";
      std::vector<STRING> svals;
      parm -> producer -> value_list(svals);

      int i;
      for (i=0; i<svals.size(); i++)
	std::cout << i << ") " << svals[i] << "\n";
      std::cin >> i;
      if (i<0 || i>=svals.size() )
	{
	  std::cout << "Bad selection\n";
	  return;
	}
      
      parm -> choice = i;
      val = ((qpp::metaparameter<T>*)(parm -> producer)) -> values[i].value;
    }
  else
    {
      std::cout << "Enter new parameter value (" << qpp::qtype_data<T>::name << "):\n";
      STRING s;
      std::cin >> s;
      if (!qpp::s2t<T>(s,val))
	{
	  std::cout << "Wrong " << qpp::qtype_data<T>::name << " value\n";
	  return;
	}  
    }

  if (parm -> instance == NULL)
    parm -> instance = new qpp::qpp_parameter<T>(parm -> producer -> name(), val);
  else
    ((qpp::qpp_parameter<T>*)(parm -> instance)) -> value() = val;
}


int main(int argc, char **argv)
{
  try{
    std::istream * inp;
    if (argc > 1)
      inp = new std::ifstream(argv[1]);
    else
      inp = & std::cin;
    
    qpp::tokenizer t(*inp);
    
    qpp::qpp_array global("global");
    
    qpp::qpp_object *q = _qpp_internal::parse_declaration(t, &global);
    global.add(*q);
    
    std::cout << "\n---------------------------------------------\n";      
    q->write(std::cout);

    qpp::metaparam_block * meta = create_metaparam(*(qpp::qpp_declaration*)q, &global);

    std::cout << "\n---------------------------------------------\n";      
    meta->write(std::cout);
    std::cout << "----structure----\n";

    qpp::metaparam_structure str(meta);
    str.create_all();

    std::vector<int> irep, idx;
    qpp::metaparam_structure * current = &str;

    meta->write(std::cout);

    while(true)
      {
	str.debug(0,current);
	
	std::cout << "-----------------------------------------------------\n";
	std::cout << "Current pos=";
	for (int i=0; i<irep.size(); i++)
	  std::cout << " (" << irep[i] << "," << idx[i] << ")";
	std::cout << "\n";

	std::cout << "Num reps = " << current->n_repetitions();
	std::cout << " Num elems =";
	for (int i=0; i<current->n_repetitions(); i++)
	  std::cout << " " << current->n_elements(i);
	std::cout << "\n";

	std::cout << "e" << red("X") + "it | level" + red("U") + "p | level" 
	  + red("D") +"own ";

	qpp::qmetatypes tp = current->producer->metatype();

	switch(tp)
	  {
	  case qpp::qmetparam:
	    std::cout << "| " + red("E") + "dit";
	    if (current->producer->name() == "*")
	      std::cout << " | edit " + red("N")+"ame";
	    break;
	  case qpp::qmetselect:
	    std::cout << "| " + red("S") + "elect";
	    break;
	  case qpp::qmetobject: std::cout << "| " + red("E") + "dit";
	    break;
	  }
	
	bool can_add = current -> possible_to_add();
	bool can_insert = can_add && current -> n_repetitions() > 0;
	bool can_erase = current -> possible_to_erase();

	if (can_add)
	  std::cout << "| " + red("A") + "dd ";
	if (can_insert)
	  std::cout << "| " + red("I") + "nsert ";
	if (can_erase)
	  std::cout << "| e" + red("R") + "ase";
	  	
	std::cout << "\n";
	
	STRING cmd;
	std::getline(std::cin,cmd);

	cmd = qpp::tolower(cmd);
	if (cmd=="x")
	  break;
	else if (cmd=="u")
	  {
	    if (current->owner!=NULL)
	      {
		current = current->owner;
		irep.pop_back();
		idx.pop_back();	    
	      }
	  }
	else if (cmd=="d")
	  {
	    int i,j;
	    if (current->n_repetitions() > 1)
	      {
		std::cout << "repetition= ";
		std::cin >> i;
	      }
	    else 
	      i=0;
	    std::cout << "element= ";
	    std::cin >> j;
	    if (current->element_exist(j,i) &&
		current -> element(j,i) != NULL)
	      {
		current = current->element(j,i);
		irep.push_back(i);
		idx.push_back(j);
	      }
	  }
	else if (cmd=="e" && tp==qpp::qmetobject)
	  {
	    qpp::qpp_object * dcl, * obj;
	    qpp::qpp_read(std::cin, dcl);
	    dcl -> setowner(&qpp::global::root);

	    std::cerr << dcl->gettype() << "\n";
	    dcl -> write(std::cerr);
	    obj = qpp::qpp_compile(dcl);

	    std::cerr << "alive\n";
	    obj->write(std::cerr);
	    current->instance = obj;
	  }
	else if (cmd=="e" && tp==qpp::qmetparam)
	  {
	    if (current->producer->gettype() & qpp::qtype_data_int)
	      editval<int>(current);
	    else if (current->producer->gettype() & qpp::qtype_data_string)
	      editval<STRING>(current);
	    else if (current->producer->gettype() & qpp::qtype_data_double)
	      editval<double>(current);
	    else if (current->producer->gettype() & qpp::qtype_data_float)
	      editval<float>(current);
	    else if (current->producer->gettype() & qpp::qtype_data_bool)
	      editval<bool>(current);
	    else current->producer->error("Unknown parameter data type",
					  current->producer->line(), current->producer->file());

	  }
	else if (cmd=="n" && tp==qpp::qmetparam && current->producer->name() == "*")
	  {
	    std::cout << "Enter new parameter name:\n";
	    STRING s;
	    std::cin >> s;
	    if (current->instance == NULL)
	      {
		if (current->producer->gettype() & qpp::qtype_data_bool)
		  current->instance = new qpp::qpp_parameter<bool>(s,false);
		else if (current->producer->gettype() & qpp::qtype_data_int)
		  current->instance = new qpp::qpp_parameter<int>(s,0);
		else if (current->producer->gettype() & qpp::qtype_data_float)
		  current->instance = new qpp::qpp_parameter<float>(s,0e0);
		else if (current->producer->gettype() & qpp::qtype_data_double)
		  current->instance = new qpp::qpp_parameter<double>(s,0e0);
		else if (current->producer->gettype() & qpp::qtype_data_string)
		  current->instance = new qpp::qpp_parameter<std::string>(s,"");
	      }
	    else
	      current->instance->setname(s);
	  }
	else if (cmd=="s" && tp==qpp::qmetselect)
	  {
	    std::cout << "Enter new choice:\n";
	    int new_choice;
	    std::cin >> new_choice;
	    

	    if (current->choice!=new_choice && current->element_exist(new_choice))
	      {
		//current->rptns[0][current->choice] = NULL;
		// fixme - properly delete it
		current->choice = new_choice;
		if (current->element(new_choice)==NULL)
		  current->create_structure(new_choice);
	      }
	  }
	else if (cmd=="a" && can_add)
	  {
	    int n = current -> n_repetitions();
	    current -> add_repetition();
	    for (int i = 0; i<current->n_elements(n); i++)
	      current -> create_structure(i,n);
	  }
	else if (cmd=="i" && can_insert)
	  {
	    std::cout << "Which element to insert?\n";
	    int n;
	    std::cin >> n;
	    current -> insert_repetition(n);
	    for (int i = 0; i<current->n_elements(n); i++)
	      current -> create_structure(i,n);
	  }
	else if (cmd=="r" && can_erase)
	  {
	    std::cout << "Which element to erase?\n";
	    int n;
	    std::cin >> n;
	    current -> erase_repetition(n);
	  }
      }
    std::cout << "resulting parameters:\n";
    str.get_params() -> write(std::cout);
    std::cout << "\n";
  }
  catch (qpp::qpp_exception & e)
    {
      std::cerr << "QPP exception:\n";
      std::cerr << e.what() << "\n";
    }
}
