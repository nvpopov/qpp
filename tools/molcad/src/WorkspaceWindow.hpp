#ifndef _H_WORKSPACEWINDOW
#define _H_WORKSPACEWINDOW
#include <QVTKWidget.h>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include "Workspace.hpp"
#include <vtkColor.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>

namespace molcad{

class WorkspaceWindow:public QVTKWidget{
	Q_OBJECT
public:
	explicit WorkspaceWindow(QWidget *parent = 0);

	//System and rendering related
	vtkSmartPointer<vtkRenderer>                ren ;
	vtkSmartPointer<vtkRenderWindow>            renwin;

	vtkSmartPointer<vtkTextActor>          window_info;

	Workspace* ws;
	void ConnectToWorkspace(Workspace* workspace);

public slots:
	void ShowContextMenu(const QPoint& pos);
};

}
#endif
