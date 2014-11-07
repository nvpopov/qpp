#include "WorkspaceWindow.hpp"
using namespace molcad;

WorkspaceWindow::WorkspaceWindow(QWidget *parent) : QVTKWidget(parent,Qt::Window
															   | Qt::WindowStaysOnTopHint
															   | Qt::X11BypassWindowManagerHint
															   | Qt::FramelessWindowHint )
{
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(ShowContextMenu(const QPoint&)));

	ren = vtkSmartPointer<vtkRenderer>::New();

	renwin = vtkSmartPointer<vtkRenderWindow>::New();
	renwin->AddRenderer(ren);

	window_info = vtkSmartPointer<vtkTextActor>::New();
	window_info->SetInput("Window info");
	window_info->SetDisplayPosition(10,10);
	window_info->GetTextProperty()->SetFontSize(14);
	ren->AddActor(window_info);
	SetRenderWindow(renwin);

}

void WorkspaceWindow::ShowContextMenu(const QPoint& pos) // this is a slot
{

	QPoint globalPos = this->mapToGlobal(pos);

	QMenu myMenu;
	myMenu.addAction("Edit");
	myMenu.addAction("Actions");
	myMenu.addAction("Scripts");
	myMenu.addAction("Selection");

	//Prevent incredible zooming
	GetInteractor()->RightButtonReleaseEvent();

	QAction* selectedItem = myMenu.exec(globalPos);
	if (selectedItem)
	{
		std::cout<<selectedItem->text().toStdString()<<std::endl;
	}
	else
	{
		// nothing was chosen
	}
}

void WorkspaceWindow::ConnectToWorkspace(Workspace *workspace){
//	ren->RemoveActor(workspace->mol_actor);
	ren->AddActor(workspace->mol_actor);
	ws = workspace;
}
