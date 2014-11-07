#ifndef _H_MOLCADMAINWINDOW
#define _H_MOLCADMAINWINDOW
#include <QMainWindow>
#include <QDockWidget>
#include <QVTKWidget.h>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QMdiArea>
#include <QPushButton>
#include <QTimer>
#include <vtkMolecule.h>
#include "console.hpp"
#include "EntityInspector.hpp"
#include "PropertyInspector.hpp"
#include "WorkspaceInspector.hpp"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderWindow.h"
#include "App.hpp"
#include "Workspace.hpp"
#include <QToolBar>
#include <QMessageBox>
#include <QTabBar>
#include <QLabel>

namespace molcad{
class MainWindow : public QMainWindow{
	 Q_OBJECT
public:
	 MainWindow();
	 bool eventFilter(QObject *obj, QEvent *event);

	 /*Routines*/
	 void SetupLayouts();
	 void CreateWidgets();
	 /*Menus routines,actions and variables*/
	 void CreateMenus();
	 QMenu *fileMenu;
	 QMenu *editMenu;
	 QMenu *viewMenu;
	 QMenu *helpMenu;
	 /**/

	 /*Variables*/
	 QDockWidget *dock;
	 QWidget* viewers;

	 /*Widgets*/
	 Console *console;
	 EntityInspector *ent_insp;
	 PropertyInspector *prop_insp;
	 WorkspaceInspector *workinsp_m;

	 QMdiArea *mdi;
	 molcad::App mapp;

	 //Event loop via timer
	 QTimer *timer;

	 //Toolbar
	 QToolBar *toolbar;
	 QTabBar *tabbar;

	 //Actions
	 QAction *new_workspace,
			 *delete_workspace,
			 *open_workspace,
			 *add_window,
			 *tile_window;

	 //Layouts
	 QHBoxLayout *main_layout;
	 QVBoxLayout *inspector_layout;
	 QWidget *main_widget,*fancybar_widget,*inspector_widget,*separator;

	 QVBoxLayout *fancybar_layout;
	 QPushButton *fb_welcome,*fb_editor,*fb_script;
	 QLabel *label_ws,*label_ent,*label_prop;

	 void AddWorkspaceWindow(QWidget* widget);
	 void AddSubWorkspaceWindow(molcad::Workspace *ws);
	 void UpdateWindows(molcad::Workspace *ws);
	 void UpdateMolcad();
	 void SetupToolBar();
	 void Bootstrap();
	 void ToolBarMessage(std::string message);
	 void ToolBarMessage(QString message);

public slots:
	 void TimerUpdate();
	 void WorkspaceSelected(const QModelIndex &index);
	 void ReceiveSpawnWindowTrigger(const int ws_id);
	 void ReceiveSpawnWindowTriggerCurrent();
	 void ReceiveTileWindowTrigger();
};
};
#endif
