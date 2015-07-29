#include "io/compile.hpp"
#include <data/molecule.hpp>
#include <data/atom.hpp>

namespace qpp{

  qpp_object * qpp_compile(qpp_object * r)
  {
    // fixme - use here metaparameters to check the headers of objects 
    // and bring them to standard form

    //debug
    // std::cerr << "Compile: alive1\n";

    if (r->gettype() != qpp::qtype_declaration)
      return r;

    qpp_declaration * q = (qpp_declaration*)r;
    
    //debug
    //std::cerr << "Compile: alive2\n";


    // Get the values of crucial parameters
    //
    // creal & freal - real types for coordinates and functions

    STRING creal = "double", freal = "double";
    qpp_parameter<STRING> * pcreal =  q->parameter<STRING>("creal",qscope_global);
    qpp_parameter<STRING> * pfreal =  q->parameter<STRING>("freal",qscope_global);
    if (pcreal==NULL)
      pcreal = q->parameter<STRING>("real",qscope_global);
    if (pfreal==NULL)
      pfreal = q->parameter<STRING>("real",qscope_global);


    //debug
    //std::cerr << "Compile: alive3\n";


    if (pcreal != NULL)
      creal = pcreal -> value();
    if (pfreal != NULL)
      freal = pfreal -> value();

    //debug
    //std::cerr << "Compile: alive4\n";

    // dim - dimension of periodical system
    int dim = 0;
    qpp_parameter<int> * pdim = q->parameter<int>("dim",qscope_global);
    if (pdim != NULL)
      dim = pdim->value();

    qpp_bastype bastype = qbas_gauss;
    qpp_parameter<STRING> * pbastype =  q->parameter<STRING>("bastype",qscope_global);
    if (pbastype != NULL)
      {
	if (pbastype->value()=="slater")
	  bastype = qbas_slater;
	else if (pbastype->value()=="siesta")
	  bastype = qbas_siesta;
	else if (pbastype->value()=="pw")
	  bastype = qbas_pw;
      }
    
    //debug
    //std::cerr << "Compile: alive5\n";


    // the category of compiled object
    STRING cat = q->category();
    if (cat == "atom")
      {

	//debug
	//std::cerr << "Compile: alive atom 1\n";


	if (freal=="float")
	  return new qpp_atom<float>(q);
	else if (freal=="double")
	  return new qpp_atom<double>(q);
      }
    else if (cat == "molecule")
      {
	if (creal=="float")
	  {
	    if (freal == "float")
	      switch (dim) 
		{
		case 0:
		  return new molecule<0,float,float>(q);  break;
		case 1:
		  return new molecule<1,float,float>(q);  break;
		case 2:
		  return new molecule<2,float,float>(q);  break;
		case 3:
		  return new molecule<3,float,float>(q);  break;
		}
	    else if (freal == "double")
	      switch (dim) 
		{
		case 0:
		  return new molecule<0,float,double>(q);  break;
		case 1:
		  return new molecule<1,float,double>(q);  break;
		case 2:
		  return new molecule<2,float,double>(q);  break;
		case 3:
		  return new molecule<3,float,double>(q);  break;
		}
	  }
	else if (creal=="double")
	  {
	    if (freal == "float")
	      switch (dim) 
		{
		case 0:
		  return new molecule<0,double,float>(q);  break;
		case 1:
		  return new molecule<1,double,float>(q);  break;
		case 2:
		  return new molecule<2,double,float>(q);  break;
		case 3:
		  return new molecule<3,double,float>(q);  break;
		}
	    else if (freal == "double")
	      switch (dim) 
		{
		case 0:
		  return new molecule<0,double,double>(q);  break;
		case 1:
		  return new molecule<1,double,double>(q);  break;
		case 2:
		  return new molecule<2,double,double>(q);  break;
		case 3:
		  return new molecule<3,double,double>(q);  break;
		}
	  }
	
      }
    else if (cat == "basis")
      {
	if (freal=="float")
	  switch (bastype)
	    {
	    case qbas_gauss:
	      return new qpp_basis_data<qbas_gauss,float>(q); break;
	    case qbas_slater:
	      return new qpp_basis_data<qbas_slater,float>(q); break;
	      /*case qbas_siesta:
	      return new qpp_basis_data<qbas_siesta,float>(q); break;
	    case qbas_pw:
	    return new qpp_basis_data<qbas_pw,float>(q); break;*/
	    }
	else if (freal=="double")
	  switch (bastype)
	    {
	    case qbas_gauss:
	      return new qpp_basis_data<qbas_gauss,double>(q); break;
	    case qbas_slater:
	      return new qpp_basis_data<qbas_slater,double>(q); break;
	      /*case qbas_siesta:
	      return new qpp_basis_data<qbas_siesta,double>(q); break;
	    case qbas_pw:
	    return new qpp_basis_data<qbas_pw,double>(q); break;*/
	    }
      }

    else
      return q;
  }
  
};
