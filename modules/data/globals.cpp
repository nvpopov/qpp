#include "globals.hpp"
#include <io/qpparser.hpp>
#include <cstdlib>

namespace qpp{

  qpp_declaration global::root("root","");

  std::vector<STRING> global::keywords;
  
  STRING global::data_dir = global::init_data_dir();

  STRING global::init_data_dir()
  {
    char * p = getenv("QPP_DATA_DIR");
    STRING res = "";
    if (p!=NULL)
      res = p;
    return res;
  }

  std::vector<metaparam_block*> global::metas = global::init_metas();

  std::vector<metaparam_block*> global::init_metas()
  {
    //debug
    std::cerr << "------------- QPP initialization ----------------\n";
    std::cerr.flush();
    
    std::vector<metaparam_block*> res;
    
    STRING mfname = data_dir+"/meta.qpp";
    IFSTREAM metaqpp(mfname.c_str());

    if (metaqpp.is_open())
      {
	std::vector<qpp_object*> decls;
	qpp_read(metaqpp,decls);
	/*
	std::cerr << "alive\n";
	for (int i=0; i<decls.size(); i++)
	  {
	    std::cerr << "----------------\n";
	    decls[i]->write(std::cerr);
	  }
	*/
	
	for (int i=0; i<decls.size(); i++)
	  {
	    metaparam_block * r = create_metaparam(*(qpp::qpp_declaration*)decls[i]);
	    
	  
	    std::cout << "=====================\n";
	    r->write(std::cout);
	  
	    keywords.push_back(r->name());
	    res.push_back(r);
	    
	    std::cout << "...done-------------\n";
	  }

	//std::cerr << "alive1\n";

	metaparam_block * geom = meta("geometry");
	keywords.push_back("fragment");
	res.push_back(geom);

	//std::cerr << "alive2\n";
      }
    else
      {
	std::cerr << "Fatal: meta.qpp not not found!\n";
	root.error("Fatal: meta.qpp not not found!");
      }
    
    //std::cout << "...Initialization done\n";
    return res;
  }

  metaparam_block * global::meta(const STRING & cat)
  {
    for (int i=0; i<metas.size(); i++)
      if (cat == keywords[i])
	return metas[i];
    return NULL;
  }

}
