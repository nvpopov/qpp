#ifndef _QPP_BUILDERS_H
#define _QPP_BUILDERS_H

#include <mathf/constants.hpp>
#include <data/qppdata.hpp>
#include <geom/geom.hpp>
#include <lace/lace3d.hpp>
#include <instr/shape.hpp>
#include <instr/geomanip.hpp>

namespace qpp{
  
  /*
  class qpp_function : public qpp_param_array{
  public:

    STRING dst_name;
    qpp_object * dst;
    qppobject_type dst_type;    
    
    qpp_function( const STRING & __name, qpp_object * __owner, const STRING & __dst_name,
		  const qppobject_type & __dst_type) : 
      qpp_param_array(__name,__owner)
    {
      dst_name = __dst_name;      
      dst_type = __dst_type;

      if (dst_name!="")
	add(* new qpp_parameter<STRING>("dst",dst_name));
    }

    qpp_function( const STRING & __name, qpp_object * __owner, qpp_param_array & parm,
		  const qppobject_type & __dst_type ) : 
      qpp_param_array(__name,__owner)
    {
      setline(parm.line());
      setfile(parm.file());

      allow(qtype_any);

      for (int i=0; i<parm.n_nested(); i++)
	add(*parm.nested(i));

      qpp_parameter<STRING> * dn = parm.parameter<STRING>("dst");
      if (dn != NULL)
	dst_name = dn->value();
      else
	dst_name = "";
      
      dst_type = __dst_type;
    }

    virtual int run()
    {      
      dst = NULL;
      if (dst_name!="")
	dst = owner() -> find(dst_name,dst_type,qscope_local);
      else 
	dst = owner() -> find(name(),dst_type,qscope_local);      
      return 0;
    }

    void postrun(qpp_object * res)
    {
      if (dst == res)
	return;

      qpp_declaration * downer = (qpp_declaration*)owner();

      int i = downer -> obj_index(dst);
      if ( i >= downer->n_param() && i < downer->n_nested() )
	{
	  downer -> erase(i);
	  downer -> insert(i,*res);
	}
      else
	downer -> add(*res);
    }
    
    /*
    geom_builder(const geom_builder<DIM,CREAL,TRANSFORM> & gb) :
      qpp_param_array(gb)
    {
      dst_name = gb.dst_name;
      dst = gb.dst; 
      if (dst_name!="")
	add(* new qpp_parameter<STRING>("dst",dst_name));
    }
    

    virtual void write(OSTREAM &os, int offset=0) const
    {
      for (int i=0; i<offset; i++)
	os << " ";
      if ( category() != "" && name() != "")
	os << category() << " " << name();
      else
	os << category() << name();
      qpp_param_array::write(os,offset);
    }
    
    
  };
  */
  // -----------------------------------------------------------------------

  //  template<int DIM, int DIM2, class CREAL, class TRANSFORM = periodic_cell<DIM,CREAL>,
  //	   class TRANSFORM2 = periodic_cell<DIM2,CREAL> >
  template<class CREAL>
  class function_replicate : public qpp_param_array
  {
  public:
    
    STRING geom_name, uc_name, shape_name, symm_name;
    qpp_shape<CREAL> * shape;
    int qmode;
    CREAL vicinity;

    /*
    geometry<DIM2,CREAL,TRANSFORM2> * src;
    geometry<DIM,CREAL,TRANSFORM> * res;
    TRANSFORM2 * cell;
    */
    /*
    function_replicate( const STRING & __name, qpp_object * __owner, 
			const STRING & __dst_name, const STRING & __src_name) :
      qpp_function(__name,__owner,__dst_name,
		   qtype_geometry | qtype_xgeometry | 
		   qtype_data<CREAL>::type | qtype_dim<DIM>::type)
    {
      src_name = __src_name;
    }
    */

    function_replicate( const STRING & __name, qpp_object * __owner, 
			qpp_param_array & parm) :
      qpp_param_array(__name,__owner)
    {
      allow(qtype_any);
      setline(parm.line());
      setfile(parm.file());
      // geom
      qpp_parameter<STRING> * pname = parm.parameter<STRING>("geom",qscope_local);
      if (pname != NULL && pname->value()!="" ) 
	{
	  geom_name = pname->value();
	  add(* new qpp_parameter<STRING>("geom", &geom_name));
	}
      else
	geom_name = __name;

      // uc
      pname = parm.parameter<STRING>("uc",qscope_local);
      uc_name = pname->value();
      add(* new qpp_parameter<STRING>("uc", &uc_name));

      // symm
      pname = parm.parameter<STRING>("symm",qscope_local);
      if (pname!=NULL)
	{
	  symm_name = pname -> value();
	  add(* new qpp_parameter<STRING>("symm", &symm_name));
	}

      // shape
      qpp_object * p = parm.find1("shape", qtype_parameter | qtype_data_string |
				  qtype_any_shape, qscope_local);

      if ( p->gettype() == (qtype_parameter | qtype_data_string) )
	{
	  shape_name = ((qpp_parameter<STRING>*)p) -> value();
	  shape = NULL;
	  add(* new qpp_parameter<STRING>("shape", &shape_name));	  
	}
      else //if ( p->gettype() & (qtype_shape | qtype_data<CREAL>::type) )
	// fixme - do we need better type check here?
	{
	  shape = (qpp_shape<CREAL>*)p;
	  add(*shape);
	}
      
      pname = parm.parameter<STRING>("mode");
      STRING mode1, mode2;

      mode1 = pname->value();
      if (mode1=="")
	{
	  mode1 = pname->parameter<STRING>(0)->value();
	  mode2 = pname->parameter<STRING>(1)->value();
	}

      std::cerr << "replicator alive6\n";

      if (mode2 == "merge")
	qmode |= qmode_merge;
      else if (mode2 == "exclude")
	qmode |= qmode_exclude;
      else if (mode2 == "join")
	qmode |= qmode_join;
      else if (mode2 == "atomwise")
	qmode |= qmode_atomwise;
      else if (mode2 == "cellwise")
	qmode |= qmode_cellwise;

      if (mode1 == "merge")
	qmode |= qmode_merge;
      else if (mode1 == "exclude")
	qmode |= qmode_exclude;
      else if (mode1 == "join")
	qmode |= qmode_join;
      else if (mode1 == "atomwise")
	qmode |= qmode_atomwise;
      else if (mode1 == "cellwise")
	qmode |= qmode_cellwise;
      
      add(* (pname->copy()));

      // Other parameters
      qpp_parameter<double> * vcnty = parm.parameter<double>("close",qscope_local);
      vicinity = vcnty->value();
      add(*new qpp_parameter<CREAL>("close",&vicinity));

      // All parameters done	
    }

    virtual STRING category() const
    { return "replicate";}

    virtual void write(OSTREAM &os, int offset=0) const
    {
      if (name()!="")
	os << name() << " = ";
      os << "replicate";
      qpp_param_array::write(os,offset);
    }

    template<int DIM>
    qpp_object * dreplicate(int uc_dim, qpp_object * uc, qpp_object *symm, 
			   qpp_object * shape, int qmode, double vicinity)
    {
      qpp_object * result;
      switch(uc_dim)
	{
	case 1: result = 
	    replicate<DIM,1,CREAL,periodic_cell<DIM,CREAL>,periodic_cell<1,CREAL> >(
		      *((geometry<1,CREAL>*)uc),*((periodic_cell<1,CREAL>*)symm),
		      *((qpp_shape<CREAL>*)shape),qmode,vicinity);
	  break;
	case 2: result = 
	    replicate<DIM,2,CREAL,periodic_cell<DIM,CREAL>,periodic_cell<2,CREAL> >(
		      *((geometry<2,CREAL>*)uc),*((periodic_cell<2,CREAL>*)symm),
		      *((qpp_shape<CREAL>*)shape),qmode,vicinity);
	  break;
	case 3: result = 
	    replicate<DIM,3,CREAL,periodic_cell<DIM,CREAL>,periodic_cell<3,CREAL> >(
		      *((geometry<3,CREAL>*)uc),*((periodic_cell<3,CREAL>*)symm),
		      *((qpp_shape<CREAL>*)shape),qmode,vicinity);
	  break;
	}
      return result;
    }


    virtual int run()
    {
      std::cerr << "replicate::run\n";

      qpp_object * geom, * uc, * symm;      
      int uc_dim, geom_dim;
      // geom
      std::cout << " geom_name= " << geom_name << "\n";

      geom = owner() -> find1(geom_name, qtype_any_geom, qscope_local);
      if (geom!=NULL)
	geom_dim = getdim(geom->gettype());
      else
	geom_dim = owner()->parameter<int>("dim",qscope_local)->value();

      std::cerr << "replicate:alive1\n";

      // uc
      uc  = owner() -> find1(uc_name, qtype_any_geom, qscope_local);
      if (uc==NULL)
	owner()->error("replicate: unit cell to replicate not found", line(), file());

      uc_dim = getdim(uc->gettype());

      std::cerr << "replicate:alive2\n";

      // symm
      if (symm_name != "")
	{
	  symm = owner()->find1(symm_name, qtype_any_vectors, qscope_local);
	  if (symm==NULL)
	    owner()->error("replicate: vectors(symmetry) to replicate not found", 
			   line(), file());
	}
      else
	symm = NULL;

      std::cerr << "replicate:alive3\n";

      //      else if (&(cell->symm())!=NULL)
      //	symm = &(cell->symm());
      //      else 
      //	owner()->error("replicate: vectors not found", line(), file());    

      // shape
      if (shape==NULL)
	{
	  qpp_object * sh = owner()->find1(shape_name, qtype_any_shape, qscope_local);
	  if (sh==NULL)
	    owner()->error("replicate: shape not found", line(), file());    
	  shape = (qpp_shape<CREAL>*)sh;
	}

      write(std::cerr);
      std::cerr << "replicate: ready geom_dim= " << geom_dim << " cell_dim= " 
		<< geom_dim <<"\ncell:\n";
      uc->write(std::cerr);
      std::cerr << "symm:\n";
      symm->write(std::cerr);
      std::cerr << "shape:\n";
      shape->write(std::cerr);

      qpp_object * result;

      switch(geom_dim)
	{
	case 0:
	  result = dreplicate<0>(uc_dim,uc,symm,shape,qmode,vicinity);
	  break;
	case 1:
	  result = dreplicate<1>(uc_dim,uc,symm,shape,qmode,vicinity);
	  break;
	case 2:
	  result = dreplicate<2>(uc_dim,uc,symm,shape,qmode,vicinity);
	  break;
	case 3:
	  result = dreplicate<3>(uc_dim,uc,symm,shape,qmode,vicinity);
	  break;
	}

      result->setname(geom_name);
      qpp_declaration * downer = (qpp_declaration*)owner();
      if (geom!=NULL)
	{
	  int i = downer->obj_index(geom);
	  downer->erase(i);
	  downer->insert(i,*result);
	}
      else
	downer->add(*result);

      return 0;
    }
    
  };

  // -----------------------------------------------------------------

  template<class CREAL>
  class function_replace : public qpp_param_array
  {
  public:
    
    STRING geom_name, shape_name, atom_what, atom_with;
    qpp_shape<CREAL> * shape;
    int dim;

    function_replace(const STRING & __name, qpp_object * __owner, 
		     const STRING & __geom_name, const STRING & __shape_name,
		     const STRING & __atom_what, const STRING & __atom_with) :
      qpp_param_array(__name,__owner)
    {
      geom_name = __geom_name;
      add(* new qpp_parameter<STRING>("geom", &geom_name));

      shape_name = __shape_name;
      add(* new qpp_parameter<STRING>("shape", &shape_name));
      shape = NULL;

      atom_what = __atom_what;
      add(* new qpp_parameter<STRING>("what", &atom_what));

      atom_with = __atom_with;
      add(* new qpp_parameter<STRING>("with", &atom_with));      
    }

    function_replace(const STRING & __name, qpp_object * __owner, 
		     const STRING & __geom_name, qpp_shape<CREAL> * __shape,
		     const STRING & __atom_what, const STRING & __atom_with) :
      qpp_param_array(__name,__owner)
    {
      geom_name = __geom_name;
      add(* new qpp_parameter<STRING>("geom", &geom_name));
      
      shape = __shape;
      shape -> setname("shape");
      add( *shape );

      atom_what = __atom_what;
      add(* new qpp_parameter<STRING>("what", &atom_what));

      atom_with = __atom_with;
      add(* new qpp_parameter<STRING>("with", &atom_with));      
    }

    function_replace(const STRING & __name, qpp_object * __owner, 
		     qpp_param_array & parm) :
      qpp_param_array(__name,__owner)
    {
      allow( allowed() | qtype_any_shape);
      qpp_parameter<STRING> * p = parm.parameter<STRING>("geom");
      geom_name = p->value();
      add(* new qpp_parameter<STRING>("geom", &geom_name));
      
      // Shape
      qpp_object * sh = parm.find1("shape", qtype_parameter | qtype_data_string |
				   qtype_any_shape, qscope_local);

      if ( sh->gettype() == (qtype_parameter | qtype_data_string) )
	{
	  shape_name = ((qpp_parameter<STRING>*)sh) -> value();
	  add(* new qpp_parameter<STRING>("shape", &shape_name));	  
	  shape = NULL;
	}
      else
	{
	  shape = (qpp_shape<CREAL>*)sh;
	  add(*shape);
	}

      p = parm.parameter<STRING>("what");
      atom_what = p->value();
      add(* new qpp_parameter<STRING>("what", &atom_what));      

      p = parm.parameter<STRING>("with");
      atom_with = p->value();
      add(* new qpp_parameter<STRING>("with", &atom_with));      

      std::cout << "replace created  geom = " << geom_name  << " shape= ";
      shape->write(std::cout);
      std::cout << " what= " << atom_what << " with= " << atom_with << std::endl;
      
    }

    virtual STRING category() const
    { return "replace";}

    virtual int run()
    {
      std::cout << "replace::run()" << std::endl;
      std::cout << " replace dst_name= " << std::endl;

      qpp_object * p = owner()->find1(geom_name, qtype_any_geom, qscope_local);
      if (p==NULL)
	owner()->error("replace: target geometry not found", line(), file());
      
      qpp_object * geom = p;
      dim = getdim(p->gettype());
      
      //qpp_function::run();
      if (shape==NULL)
	{
	  p = owner()->find1(shape_name,qtype_any_shape,qscope_local);
	  if (p==NULL )
	    owner()->error("replace: shape not found",line(),file());
	  shape = (qpp_shape<CREAL>*)p;
	}

      std::cout << "replace ready: geom = " << geom->name() << " dim= " << dim << " shape= ";
      shape->write(std::cout);
      std::cout << " what= " << atom_what << " with= " << atom_with << std::endl;
      
      switch (dim)
	{
	case 0:
	  replace(*((geometry<0,CREAL>*)geom),*shape,atom_what,atom_with);
	  break;
	case 1:
	  replace(*((geometry<1,CREAL>*)geom),*shape,atom_what,atom_with);
	  break;
	case 2:
	  replace(*((geometry<2,CREAL>*)geom),*shape,atom_what,atom_with);
	  break;
	case 3:
	  replace(*((geometry<3,CREAL>*)geom),*shape,atom_what,atom_with);
	  break;
	}

      return 0;
    }

  };
  

};

#endif
