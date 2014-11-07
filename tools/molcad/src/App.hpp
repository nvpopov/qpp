#ifndef _H_MOLCADAPP
#define _H_MOLCADAPP

#include "utils.hpp"
#include <string>

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTextProperty.h>
#include <vtkProperty.h>
#include <vtkMoleculeMapper.h>
#include <vtkGlyph3DMapper.h>
#include <vtkMolecule.h>
#include <vtkGlyph3D.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxisActor.h>
#include <vtkCamera.h>
#include <Python.h>
#include "WorkspaceWindow.hpp"
#include <QMainWindow>

namespace molcad{
class App:QObject{
	Q_OBJECT
public:
	std::string CurrentFileName;

	//System and rendering related
	vtkSmartPointer<vtkRenderer>                ren,ren1;
	vtkSmartPointer<vtkRenderWindow>            renwin,renwin1;
	vtkSmartPointer<vtkRenderWindowInteractor>  renwinit;

	//Widgets, stuff
	vtkSmartPointer<vtkOrientationMarkerWidget> ormark;
	vtkSmartPointer<vtkAxisActor>               axactor;

	//AH
	std::vector<Workspace* > workspaces;
	std::vector<WorkspaceWindow*> workspace_win;

	void InitGUI();
	void Init();
	void InitAtomRepr();
	void Update();
	void ReadMolecule(std::string filename);

//QMainwindow pointer
	QMainWindow* mainwindow;
public slots:
	void onCommand(QString);
};
}
#endif
