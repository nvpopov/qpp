#include "Workspace.hpp"

using namespace molcad;


void Workspace::LoadFromFile(std::ifstream *stream)
{
//	_qpp_internal::tokenizer t(*stream);
//	qpp::qpp_object *q = parse_declaration(t);
//	qpp::qpp_declaration * d =  (qpp::qpp_declaration*)q;

//	bool flag_add_first = false;
//	for (int i=0; i < d->n_decl(); i++)
//		if ( ((d->nested_decl(i).gettype() & qpp::data_geometry) ||
//			  (d->nested_decl(i).gettype() & qpp::data_xgeometry)) and (!flag_add_first) )
//		{
//			qpp::geometry<3> *geom = (qpp::geometry<3>*)(&d->nested_decl(i));
//			geom->build_type_table();
//			geom->ngbr.default_distance = 2.0;
//			geom->ngbr.build_disttable();
//			geom->ngbr.build();

//			flag_add_first = true;

//			vtkSmartPointer<vtkMolecule> mol = vtkSmartPointer<vtkMolecule>::New();
//			vtkSmartPointer<vtkMoleculeMapper> mol_map = vtkSmartPointer<vtkMoleculeMapper>::New();
//			mol_map->SetInputData(mol.GetPointer());

//			mol_map->UseBallAndStickSettings();

//			mol_actor = vtkSmartPointer<vtkActor>::New();

//			mol_actor->SetMapper(mol_map.GetPointer());
//			mol_actor->GetProperty()->SetAmbient(0.1);
//			mol_actor->GetProperty()->SetDiffuse(0.1);
//			mol_actor->GetProperty()->SetSpecular(0.1);
//			mol_actor->GetProperty()->SetSpecularPower(40);

//			for(int q=0; q<geom->nat(); q++)
//			{
//				std::cout<<geom->atom_of_type(geom->type_table(q))<<geom->coord(q)<<std::endl;
//				lace::vector3d<double> atompos = geom->coord(q);
//				mol->AppendAtom(8,atompos(0),atompos(1),atompos(2));
//			}

//			for(int j=0; j<geom->nat(); j++)
//				for(int k=0; k<geom->ngbr.n(j); k++)
//				{
//					mol->AppendBond(mol->GetAtom(j),mol->GetAtom(k));
//					//std::cout<<j<<k;
//				}
//		}

}

Workspace::Workspace()
{
	wtype=molcad::WT_QPP;
	//Test molecule
	ws_name = "New workspace";
	root = new Entity(NULL);
	std::ifstream inpf("example.qpp");
	LoadFromFile(&inpf);

}
