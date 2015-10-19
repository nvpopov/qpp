#include "io/compile.hpp"
#include <data/molecule.hpp>
#include <data/atom.hpp>
#include <data/meta.hpp>
#include <data/globals.hpp>
#include <instr/shape.hpp>
#include <instr/builders.hpp>
#include <io/qpparser.hpp>

namespace qpp{

  template<class CREAL>
  lace::vector3d<CREAL> parm2vec(qpp_param_array * p)
  {
    lace::vector3d<CREAL> v;
    v.x() = p->parameter<double>("x")->value();
    v.y() = p->parameter<double>("y")->value();
    v.z() = p->parameter<double>("z")->value();    
    return v;
  }

  //---------------------------------------------------------------------

  template<class CREAL> 
  qpp_object* make_shape_box(qpp_param_array * p, metaparam_structure & str,
			     const STRING & name, qpp_object* owner)
  {
    lace::vector3d<CREAL> corner = parm2vec<CREAL>(p->parameter<STRING>("corner"));
    if (str.choice==0)
      {
	CREAL a,b,c;
	a = p->parameter<double>("a")->value();
	b = p->parameter<double>("b")->value();
	c = p->parameter<double>("c")->value();
	shape_box<CREAL> *s = new shape_box<CREAL>(a,b,c,name,owner);
	s->move(corner);
	return s; 
      }
    else if (str.choice==1)
      {
	lace::vector3d<CREAL> a,b,c;
	a = parm2vec<CREAL>(p->parameter<STRING>("a"));
	b = parm2vec<CREAL>(p->parameter<STRING>("b"));
	c = parm2vec<CREAL>(p->parameter<STRING>("c"));
	return new shape_box<CREAL>(a,b,c,corner,name,owner);
      }    
  }

  //---------------------------------------------------------------------

  template<class CREAL>
  qpp_shape<CREAL> * getshape(qpp_object * p)
  {
    if (p->gettype() == (qtype_parameter | qtype_data_string) )
      {
	STRING sname = ((qpp_parameter<STRING>*)p)->value();
	qpp_object * sh = p->owner()->find1(sname, qtype_any_shape, qscope_local);
	if (sh->gettype() & qtype_shape)
	  return (qpp_shape<CREAL>*)sh;
	else
	  p->error("Shape "+sname+" not found",p->line(),p->file());
      }
    else if (p->gettype() & qtype_shape)
      return (qpp_shape<CREAL>*)p;
    else
      p->error("Wrong shape ",p->line(),p->file());
  }

  //---------------------------------------------------------------------

  qpp_object * qpp_compile(qpp_object * r)
  {
    //debug
    std::cerr << "Compile: " << r->category()<< " | " << r->name() << " " 
	      << std::hex << r->gettype()<<  std::dec<< "\n";
    
    r->write(std::cerr);

    qppobject_type rtype = r->gettype();
    bool is_decl = (rtype == qtype_declaration);
    bool is_param = ((rtype == qtype_parameter | qtype_data_string) && r->n_nested()>0 );

    if ( !is_decl && !is_param)
      return r;

    std::cerr << "\n Compile: " << r->category()<< " | " << r->name() << " continue\n";

    qpp_array * parm;
    STRING cat,nam;
    
    if (is_decl)
      {
	qpp_declaration * d = (qpp_declaration*)r;
    
	for (int i=0; i<d->n_param(); i++)
	  d->set_param(i, *qpp_compile(d->param(i)));

	for (int i=0; i<d->n_decl(); i++)
	  d->set_decl(i, *qpp_compile(d->decl(i)));

	if (d->n_param()>0)
	  // fixme - kostyl
	  // How to process correctly the cases when not the header (parameters),
	  // but the body of declaration has to be identified with metaparameter?
	  parm = d->parameters();
	else
	  parm = d;
	cat = d->category();
	nam = d->name();
      }
    else 
      {
	qpp_parameter<STRING> * p = (qpp_parameter<STRING>*)r;
	//qpp_param_array * p = (qpp_param_array*)r;
	
	for (int i=0; i<p->n_nested(); i++)
	  {
	    qpp_object * pni = qpp_compile(p->nested(i));
	    p -> allow(p->allowed() | pni->gettype());
	    p->set(i, *pni);
	    
	    std::cerr << p->name() << " nested i= " << i 
		      << " type= " << std::hex << p->nested(i)->gettype() << std::dec << "\n";
	    p->nested(i)->write(std::cerr);
	    std::cerr << "\n";
	    
	  }

	parm = p;
	if (p->value()=="")
	  {
	    cat = p->name();
	    nam = "";
	  }
	else
	  {
	    cat = p->value();
	    nam = p->name();
	  }
      }

    metaparam_block * meta = global::meta(cat);
    if (meta==NULL)
      return r;

    std::cerr << "Meta found: " << meta->name() << "\n";

    qpp_param_array * normparm;
    metaparam_structure str(meta);
    int code = meta -> identify(*parm,str);

    parm->write(std::cerr);
    std::cerr << "\n";
    str.debug();

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
	else
	  r->error("real type for functions not defined", r->line(),r->file());
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
	    else 
	      r->error("real type for functions not defined", r->line(),r->file());
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
	    else
	      r->error("real type for functions not defined", r->line(),r->file());

	  }
	else
	  r->error("real type for coordinates not defined", r->line(),r->file());
	
      }
    // ------------------------------- Basis -----------------------------
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
	else
	  r->error("real type for functions not defined", r->line(),r->file());

      }
    else if (cat=="cell")
      {
	if (creal=="double")
	  return new periodic_cell<3,double>(normparm->parameter<double>("a")->value(),
					     normparm->parameter<double>("b")->value(),
					     normparm->parameter<double>("c")->value(),
					     normparm->parameter<double>("alpha")->value(),
					     normparm->parameter<double>("beta")->value(),
					     normparm->parameter<double>("gamma")->value(),
					     nam, r->owner());
	else if (creal=="float")
	  return new periodic_cell<3,float>(normparm->parameter<double>("a")->value(),
					    normparm->parameter<double>("b")->value(),
					    normparm->parameter<double>("c")->value(),
					    normparm->parameter<double>("alpha")->value(),
					    normparm->parameter<double>("beta")->value(),
					    normparm->parameter<double>("gamma")->value(),
					    nam, r->owner());
	else
	  r->error("real type for coordinates not defined", r->line(),r->file());
      }
    // ------------------------------- Shapes -----------------------------
    else if (cat=="sphere")
      {
	//debug
	//std::cerr << " ----- Compiling sphere ------------\n";

	double R = normparm->parameter<double>("R")->value();
	
	if (creal=="double")
	  {
	    lace::vector3d<double> c = parm2vec<double>(
		                       normparm->parameter<STRING>("center"));
	    return new shape_sphere<double>(R,c,nam,r->owner());	
	  }
	else if (creal == "float")
	  {
	    lace::vector3d<float> c = parm2vec<float>(
				      normparm->parameter<STRING>("center"));
	    return new shape_sphere<float>(R,c,nam,r->owner());	
	  }
	else
	  r->error("Real type not defined",r->line(),r->file());
      }
    else if (cat=="box")
      {
	if (creal=="double")
	  return make_shape_box<double>(normparm,str,nam,r->owner());	
	else if (creal=="float")
	  return make_shape_box<float>(normparm,str,nam,r->owner());	
      }
    else if (cat=="union")
      {
	if (creal=="double")
	  {
	    qpp_shape<double> * sh1 = getshape<double>(normparm->nested(0)),
	      * sh2 = getshape<double>(normparm->nested(1));
	    return new shape_union<double>(*sh1,*sh2,nam,r->owner());
	  }
	else if (creal=="float")
	  {
	    qpp_shape<float> * sh1 = getshape<float>(normparm->nested(0)),
	      * sh2 = getshape<float>(normparm->nested(1));
	    return new shape_union<float>(*sh1,*sh2,nam,r->owner());
	  }
      }
    else if (cat=="intersect")
      {
	if (creal=="double")
	  {
	    qpp_shape<double> * sh1 = getshape<double>(normparm->nested(0)),
	      * sh2 = getshape<double>(normparm->nested(1));
	    return new shape_intersect<double>(*sh1,*sh2,nam,r->owner());
	  }
	else if (creal=="float")
	  {
	    qpp_shape<float> * sh1 = getshape<float>(normparm->nested(0)),
	      * sh2 = getshape<float>(normparm->nested(1));
	    return new shape_intersect<float>(*sh1,*sh2,nam,r->owner());
	  }
      }
    else if (cat=="subtract")
      {
	if (creal=="double")
	  {
	    std::cerr << "subtract: parm= ";
	    normparm->nested(0)->write(std::cerr);
	    normparm->nested(1)->write(std::cerr);
	    std::cerr << "\n";

	    qpp_shape<double> * sh1 = getshape<double>(normparm->nested(0)),
	      * sh2 = getshape<double>(normparm->nested(1));
	    return new shape_subtract<double>(*sh1,*sh2,nam,r->owner());
	  }
	else if (creal=="float")
	  {
	    qpp_shape<float> * sh1 = getshape<float>(normparm->nested(0)),
	      * sh2 = getshape<float>(normparm->nested(1));
	    return new shape_subtract<float>(*sh1,*sh2,nam,r->owner());
	  }
      }
    //  ---------------- Geometry functions --------------------
    else if (cat=="replicate")
      {
	if (creal=="float")
	  return new function_replicate<float>(nam, r->owner(),*normparm);
	else if (creal=="double")
	  return new function_replicate<double>(nam, r->owner(),*normparm);
	else
	  r->error("Real type not defined",r->line(),r->file());	  
      }
    else if (cat=="replace")
      {
	/*
	qpp_parameter<STRING> * pgeom = normparm->parameter<STRING>("dst");
	qpp_object * geom = NULL;
	if (pgeom!=NULL)
	  geom = r->owner()->find(pgeom->value(), qtype_any_geom, qscope_local);
	if (geom==NULL)
	  r->error("replace: target geometry not found", r->line(), r->file());

	int tp, dim;

	tp = geom->gettype();
	
	if (tp & qtype_dim0)
	  dim = 0;
	else if (tp & qtype_dim1)
	  dim = 1;
	else if (tp & qtype_dim2)
	  dim = 2;
	else if (tp & qtype_dim3)
	  dim = 3;

	if (creal=="float")
	  switch(dim)
	    {
	    case 0:
	      return new function_replace<0,float>(nam,r->owner(),*normparm);
	      break;		         
	    case 1:
	      return new function_replace<1,float>(nam,r->owner(),*normparm);
	      break;		         
	    case 2:
	      return new function_replace<2,float>(nam,r->owner(),*normparm);
	      break;		         
	    case 3:
	      return new function_replace<3,float>(nam,r->owner(),*normparm);
	      break;		         
	    }
	else if (creal=="double")
	  switch(dim)
	    {
	    case 0:
	      return new function_replace<0,double>(nam,r->owner(),*normparm);
	      break;		         
	    case 1:
	      return new function_replace<1,double>(nam,r->owner(),*normparm);
	      break;		         
	    case 2:
	      return new function_replace<2,double>(nam,r->owner(),*normparm);
	      break;		         
	    case 3:
	      return new function_replace<3,double>(nam,r->owner(),*normparm);
	      break;		         
	    }      
	*/
	if (creal=="float")
	  return new function_replace<float>(nam, r->owner(),*normparm);
	else if (creal=="double")
	  return new function_replace<double>(nam, r->owner(),*normparm);
	else
	  r->error("Real type not defined",r->line(),r->file());	  
      }
    else
      return r;
  }

  void qpp_read_compile(ISTREAM & is, std::vector<qpp_object*> & decls, 
			qpp_array & owner)
  {
    tokenizer t(is);
    qpp_object * decl;
    while ( (decl=_qpp_internal::parse_declaration(t, &owner)) != NULL)
      {
	decl = qpp_compile(decl);
	decls.push_back(decl);
	owner.add(*decl);
      }
  }

  void qpp_read_compile(ISTREAM & is, qpp_object* & decl,
			qpp_array & owner)
  {
    qpp_read(is, decl, &owner);
    decl = qpp_compile(decl);
    owner.add(*decl);
  }
  
};
