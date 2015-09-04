#ifndef _QPPGLOBALS_H
#define _QPPGLOBALS_H

#include <data/meta.hpp>

namespace qpp{
  
  class global{
  public:    

    static STRING data_dir;
    static STRING init_data_dir();

    static std::vector<STRING> keywords;

    static std::vector<metaparam_block*> metas;
    static std::vector<metaparam_block*> init_metas();

    static qpp_declaration root;

    static metaparam_block * meta(const STRING & cat);
    //globals();

  };
  
  //globals globals_init;

};

#endif
