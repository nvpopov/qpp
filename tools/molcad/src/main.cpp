#include "MainWindow.hpp"
#include "App.hpp"

#include <QApplication>
#include <QVBoxLayout>
#include <QSplitter>
#include <QFile>
#include <vtkRenderer.h>

int main (int argc, char *argv[])
{
	QApplication app(argc, argv);

	app.setStyleSheet("QMdiArea:{border: 1px solid black;background-color:red;}");

	molcad::MainWindow molcadmw;

	for(int i=0; i<0; i++){
	molcadmw.AddSubWorkspaceWindow(molcadmw.mapp.workspaces[0]);}
	molcadmw.mapp.workspaces[0]->ws_name="workspace1";
	molcadmw.mapp.workspaces[1]->ws_name="workspace2";
	molcadmw.mdi->tileSubWindows();
	molcadmw.UpdateMolcad();



	molcadmw.show();

	app.exec();

	return EXIT_SUCCESS;
}


