#ifndef _H_WORKSPACEMOLCAD
#define _H_WORKSPACEMOLCAD
#include <string>
#include <iosfwd>
#include <io/qpparser.hpp>
#include <geom/geom.hpp>
#include <geom/geom.hpp>
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkMolecule.h"
#include "vtkLight.h"
#include "vtkMoleculeMapper.h"
#include "vtkNew.h"
#include "vtkProperty.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkSmartPointer.h"
#include "Entity.hpp"



namespace molcad
{

const auto version = 1;

enum WorkspaceType{WT_QPP,WT_XYZ};

class Workspace
{
public:

	//Workspace name at the workspace inspector
	std::string ws_name;

	//Workspace filename
	std::string ws_filename;

	Entity *root;
	vtkSmartPointer<vtkActor> mol_actor;
	Workspace();
	WorkspaceType wtype;
	void LoadFromFile(std::ifstream *stream);

};

}
#endif
