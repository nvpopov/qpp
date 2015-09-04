#include "io/compile.hpp"
#include <data/molecule.hpp>
#include <data/atom.hpp>
#include <data/meta.hpp>
#include <data/globals.hpp>
#include <geom/shape.hpp>

namespace qpp{

  qpp_object * qpp_compile(qpp_object * r)
  {
    //debug
    std::cerr << "Compile: " << r->category()<< " | " << r->name() << " " 
	      << std::hex << r->gettype()<<  std::dec<< "\n";

    qppobject_type rtype = r->gettype();

    if (rtype != qtype_declaration && ! (rtype & qtype_parameter) )
      return r;

    std::cerr << "Compile: " << r->category()<< " | " << r->name() << " continue\n";

    qpp_param_array * parm;
    STRING cat,nam;
    
    if (rtype ==  qtype_declaration)
      {
	qpp_declaration * d = (qpp_declaration*)r;
    
	for (int i=0; i<d->n_param(); i++)
	  d->set_param(i, *qpp_compile(d->param(i)));

	for (int i=0; i<d->n_decl(); i++)
	  d->set_decl(i, *qpp_compile(d->decl(i)));

	parm = d->parameters();
	cat = d->category();
	nam = d->name();
      }
    else
      {
	qpp_param_array * p = (qpp_param_array*)r;

	for (int i=0; i<p->n_nested(); i++)
	  {
	    p->set(i, *qpp_compile(p->nested(i)));

	    std::cerr << p->name() << " nested i= " << i 
		      << " type= " << std::hex << p->nested(i)->gettype() << std::dec << "\n";
	    p->nested(i)->write(std::cerr);
	    std::cerr << "\n";
	    
	  }

	parm = p;
	cat = p->name();
	nam = "";
      }

    metaparam_block * meta = global::meta(cat);
    if (meta==NULL)
      return r;

    std::cerr << "Meta found: " << meta->name() << "\n";

    qpp_param_array * normparm;
    metaparam_structure str(meta);
    int code = meta -> identify(*parm,str);
    if (code > 0)
      r -> error(metaparam_idf_error(code),r->line(), r->file());
    normparm = str.get_params();
    normparm -> setowner(r);
	    
    //debug
    std::cerr << "Compile: " << r->category() << "|" << r->name() << " Normalized parameters: ";
    normparm->write(std::cerr);
    std::cerr << " Parameters now: ";
    parm->write(std::cerr);
    std::cerr << "\n";

    /*
    if (rtype == qtype_declaration)
      {
	
      }
    else
      r = parm;
    */

    //debug
    //std::cerr << "Compile: alive2\n";


    // Get the values of crucial parameters
    //
    // creal & freal - real types for coordinates and functions

    STRING creal = "", freal = "";
    qpp_parameter<STRING> * pcreal =  normparm->parameter<STRING>("creal",qscope_global);
    qpp_parameter<STRING> * pfreal =  normparm->parameter<STRING>("freal",qscope_global);
    if (pcreal==NULL)
      pcreal = normparm->parameter<STRING>("real",qscope_global);
    if (pfreal==NULL)
      pfreal = normparm->parameter<STRING>("real",qscope_global);


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
    qpp_parameter<int> * pdim = normparm->parameter<int>("dim",qscope_global);
    if (pdim != NULL)
      dim = pdim->value();

    qpp_bastype bastype = qbas_gauss;
    qpp_parameter<STRING> * pbastype =  normparm->parameter<STRING>("bastype",qscope_global);
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
    if (cat == "atom")
      {

	//debug
	//std::cerr << "Compile: alive atom 1\n";


	if (freal=="float")
	  return new qpp_atom<float>((qpp_declaration*)r);
	else if (freal=="double")
	  return new qpp_atom<double>((qpp_declaration*)r);
      }
    else if (cat == "molecule")
      {
	if (creal=="float")
	  {
	    if (freal == "float")
	      switch (dim) 
		{
		case 0:
		  return new molecule<0,float,float>((qpp_declaration*)r);  break;
		case 1:
		  return new molecule<1,float,float>((qpp_declaration*)r);  break;
		case 2:
		  return new molecule<2,float,float>((qpp_declaration*)r);  break;
		case 3:
		  return new molecule<3,float,float>((qpp_declaration*)r);  break;
		}
	    else if (freal == "double")
	      switch (dim) 
		{
		case 0:
		  return new molecule<0,float,double>((qpp_declaration*)r);  break;
		case 1:
		  return new molecule<1,float,double>((qpp_declaration*)r);  break;
		case 2:
		  return new molecule<2,float,double>((qpp_declaration*)r);  break;
		case 3:
		  return new molecule<3,float,double>((qpp_declaration*)r);  break;
		}
	  }
	else if (creal=="double")
	  {
	    if (freal == "float")
	      switch (dim) 
		{
		case 0:
		  return new molecule<0,double,float>((qpp_declaration*)r);  break;
		case 1:
		  return new molecule<1,double,float>((qpp_declaration*)r);  break;
		case 2:
		  return new molecule<2,double,float>((qpp_declaration*)r);  break;
		case 3:
		  return new molecule<3,double,float>((qpp_declaration*)r);  break;
		}
	    else if (freal == "double")
	      switch (dim) 
		{
		case 0:
		  return new molecule<0,double,double>((qpp_declaration*)r);  break;
		case 1:
		  return new molecule<1,double,double>((qpp_declaration*)r);  break;
		case 2:
		  return new molecule<2,double,double>((qpp_declaration*)r);  break;
		case 3:
		  return new molecule<3,double,double>((qpp_declaration*)r);  break;
		}
	  }
	
      }
    else if (cat == "basis")
      {
	if (freal=="float")
	  switch (bastype)
	    {
	    case qbas_gauss:
	      return new qpp_basis_data<qbas_gauss,float>((qpp_declaration*)r); break;
	    case qbas_slater:
	      return new qpp_basis_data<qbas_slater,float>((qpp_declaration*)r); break;
	      /*case qbas_siesta:
	      return new qpp_basis_data<qbas_siesta,float>(q); break;
	    case qbas_pw:
	    return new qpp_basis_data<qbas_pw,float>(q); break;*/
	    }
	else if (freal=="double")
	  switch (bastype)
	    {
	    case qbas_gauss:
	      return new qpp_basis_data<qbas_gauss,double>((qpp_declaration*)r); break;
	    case qbas_slater:
	      return new qpp_basis_data<qbas_slater,double>((qpp_declaration*)r); break;
	      /*case qbas_siesta:
	      return new qpp_basis_data<qbas_siesta,double>(q); break;
	    case qbas_pw:
	    return new qpp_basis_data<qbas_pw,double>(q); break;*/
	    }
      }
    else if (cat=="sphere")
      {
	std::cerr << " ----- Compiling sphere ------------\n";

	double R = ((qpp_parameter<double>*)(normparm->nested(0)))->value();
	lace::vector3d<double> c;
	c.x() = ((qpp_parameter<double>*)(normparm->nested(1)->nested(0)))->value();
	c.y() = ((qpp_parameter<double>*)(normparm->nested(1)->nested(1)))->value();
	c.z() = ((qpp_parameter<double>*)(normparm->nested(1)->nested(2)))->value();
	
	if (creal=="double")
	  return new qpp_shape_sphere<double>(R,c,nam,r->owner());	
	else if (creal == "float")
	  {
	    lace::vector3d<float> fc;
	    for (int i=0; i<3; i++)
	      fc(i) = c(i);
	    return new qpp_shape_sphere<float>(R,fc,nam,r->owner());	
	  }
      }
    else
      return r;
  }
  
};
