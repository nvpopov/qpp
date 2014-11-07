#include "MainWindow.hpp"
using namespace molcad;

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseMove)
	{
	}
	return false;
}

/*constructor*/
MainWindow::MainWindow()
{
	mapp.mainwindow = this;
	mapp.Init();

	mdi = new QMdiArea(this);

	main_widget = new QWidget(this);

	setCentralWidget(main_widget);

	CreateWidgets();
	SetupLayouts();
	CreateMenus();

	resize(1024,768);
	qApp->installEventFilter(this);

	timer = new QTimer(this);

	connect(workinsp_m,SIGNAL(SpawnWindowTrigger(int)),this,SLOT(ReceiveSpawnWindowTrigger(int)));
	connect(workinsp_m,SIGNAL(TileWindowsTrigger()),this,SLOT(ReceiveTileWindowTrigger()));

	SetupToolBar();
}

void MainWindow::CreateWidgets()
{
	main_widget->setContentsMargins(0,0,0,0);

	main_widget->setObjectName("main_widget");
	main_widget->setStyleSheet("#main_widget{background-color:#888888; border: 1px solid black;}");
	fancybar_widget = new QWidget(this);
	fancybar_widget->show();
	fancybar_widget->setStyleSheet(
				"border: 1px solid black;background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #585858 , stop: 1 #888888);");

	inspector_widget = new QWidget(this);
	inspector_widget->show();
	inspector_widget->setObjectName("insp_widget");
	inspector_widget->setStyleSheet("#insp_widget {background-color:#C0C0C0	; border: 1px solid black;}");

	ent_insp = new EntityInspector(this);
	prop_insp = new PropertyInspector(this);
	workinsp_m = new WorkspaceInspector(inspector_widget);
	workinsp_m->show();

	label_ws = new QLabel(this);
	label_ws->setText(tr("Workspaces:"));
	label_ws->setStyleSheet(molcad::STYLE_LABEL);
	label_ent = new QLabel(this);
	label_ent->setText(tr("Entities:"));
	label_ent->setStyleSheet(molcad::STYLE_LABEL);
	label_prop = new QLabel(this);
	label_prop->setText(tr("Properties:"));
	label_prop->setStyleSheet(molcad::STYLE_LABEL);

	fb_welcome = new QPushButton(tr("Start\nScreen"),this);
	fb_editor = new QPushButton(tr("Visual\nEditor"),this);
	fb_script = new QPushButton(tr("Script\nEditor"),this);

	fb_welcome->setMinimumHeight(65);
	fb_welcome->setIcon(style()->standardIcon(QStyle::SP_ComputerIcon));
	fb_welcome->setStyleSheet("text-align: right");

	fb_editor->setMinimumHeight(65);
	fb_editor->setIcon(style()->standardIcon(QStyle::SP_DialogApplyButton));
	fb_editor->setStyleSheet("text-align: right");

	fb_script->setMinimumHeight(65);
	fb_script->setIcon(style()->standardIcon(QStyle::SP_CommandLink));
	fb_script->setStyleSheet("text-align: right");

	fb_welcome->setStyleSheet(molcad::STYLE_FANCYBUTTON);
	fb_editor->setStyleSheet(molcad::STYLE_FANCYBUTTON);
	fb_script->setStyleSheet(molcad::STYLE_FANCYBUTTON);
}

void MainWindow::AddWorkspaceWindow(QWidget* widget)
{

}

/*create dock widget and layout*/
void MainWindow::SetupLayouts()
{

	main_layout = new QHBoxLayout();
	main_layout->setContentsMargins(0,0,0,0);
	main_layout->setMargin(0);
	main_layout->setSpacing(0);
	main_widget->setLayout(main_layout);

	QSizePolicy spmdi(QSizePolicy::Preferred, QSizePolicy::Preferred);
	spmdi.setHorizontalStretch(5);
	mdi->setSizePolicy(spmdi);

	QSizePolicy spisn(QSizePolicy::Preferred, QSizePolicy::Preferred);
	spisn.setHorizontalStretch(2);

	inspector_widget->setMinimumWidth(180);
	inspector_widget->setMaximumWidth(240);
	inspector_widget->setSizePolicy(spisn);

	fancybar_widget->setMaximumWidth(80);
	fancybar_widget->setMinimumWidth(80);

	main_layout->addWidget(fancybar_widget);
	inspector_layout = new QVBoxLayout();
	inspector_layout->setContentsMargins(1,0,1,1);
	inspector_widget->setLayout(inspector_layout);
	inspector_layout->addWidget(label_ws);

	QSizePolicy sp_ws(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sp_ws.setVerticalStretch(1);
	QSizePolicy sp_ent(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sp_ent.setVerticalStretch(3);
	QSizePolicy sp_prop(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sp_prop.setVerticalStretch(6);

	workinsp_m->setSizePolicy(sp_ws);
	ent_insp->setSizePolicy(sp_ent);
	prop_insp->setSizePolicy(sp_prop);

	inspector_layout->setSpacing(0);
	inspector_layout->addWidget(workinsp_m);
	inspector_layout->addWidget(label_ent);
	inspector_layout->addWidget(ent_insp);
	inspector_layout->addWidget(label_prop);
	inspector_layout->addWidget(prop_insp);

	main_layout->addWidget(inspector_widget);

	main_layout->addWidget(mdi);

	mdi->show();

	fancybar_layout = new QVBoxLayout();
	fancybar_layout->setMargin(0);
	fancybar_layout->setSpacing(0);
	fancybar_layout->setAlignment(Qt::AlignTop);
	fancybar_widget->setLayout(fancybar_layout);
	fancybar_layout->addWidget(fb_welcome);
	fancybar_layout->addWidget(fb_editor);
	fancybar_layout->addWidget(fb_script);
}

/*create top menu*/
void MainWindow::CreateMenus(){
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addSeparator();
	editMenu = menuBar()->addMenu(tr("&Edit"));
	viewMenu = menuBar()->addMenu(tr("&View"));
	viewMenu->addSeparator();
	QMenu* wmenu = viewMenu->addMenu(tr("Widgets"));
	QMenu* wmolviewer = wmenu->addMenu(tr("Show/Hide Molecule viewer"));
	QMenu* wobjinsp = wmenu->addMenu(tr("Show/Hide Object Inspector"));
	QMenu* wconsole = wmenu->addMenu(tr("Show/Hide Console"));
	menuBar()->addSeparator();
	helpMenu = menuBar()->addMenu(tr("&Help"));
}

void MainWindow::AddSubWorkspaceWindow(molcad::Workspace *ws)
{
	molcad::WorkspaceWindow *wsw = new molcad::WorkspaceWindow(this);
	wsw->ConnectToWorkspace(ws);
	this->mapp.workspace_win.push_back(wsw);
	QMdiSubWindow *subw = this->mdi->addSubWindow(wsw,Qt::WindowTitleHint | Qt::WindowShadeButtonHint | Qt::WindowMaximizeButtonHint);
	wsw->show();
	mdi->tileSubWindows();
}

void MainWindow::UpdateWindows(Workspace *_ws)
{
	for(int i=0; i<mapp.workspace_win.size(); i++)
		if((mapp.workspace_win.at(i)!=NULL)&&(mapp.workspace_win.at(i)->ws==_ws))
		{
			mapp.workspace_win.at(i)->renwin->Render();
		}
}

void MainWindow::TimerUpdate()
{
//	vtkVector3f pos = mapp.workspaces[0]->mol->GetAtomPosition(1);
//	pos[1]=pos[1]+0.1;
//	mapp.workspaces[0]->mol->SetAtomPosition(1,pos);
//	UpdateWindows(mapp.workspaces[0]);
}

void MainWindow::UpdateMolcad()
{
	workinsp_m->clear();
	for(int i=0; i<this->mapp.workspaces.size(); i++)
		workinsp_m->addItem(QString::fromStdString(mapp.workspaces.at(i)->ws_name));
	Bootstrap();

	//if not ws selected, select one

}

void MainWindow::SetupToolBar()
{
	toolbar = this->addToolBar("Main toolbar");
	statusBar()->showMessage(tr("Ready"));
	new_workspace = new QAction(style()->standardIcon(QStyle::SP_FileDialogNewFolder), tr("New workspace"),this);
	new_workspace->setToolTip(tr("Create new workspace"));
	delete_workspace = new QAction(style()->standardIcon(QStyle::SP_DialogCancelButton), tr("Delete workspace"),this);
	delete_workspace->setToolTip(tr("Delete workspace"));
	open_workspace = new QAction(style()->standardIcon(QStyle::SP_DialogOpenButton), tr("Open workspace"),this);
	open_workspace->setToolTip(tr("Open workspace"));
	add_window = new QAction(style()->standardIcon(QStyle::SP_BrowserReload), tr("Add new workspace window"),this);
	add_window->setToolTip(tr("Add new workspace window"));
	tile_window = new QAction(style()->standardIcon(QStyle::SP_DialogApplyButton), tr("Tile windows"),this);
	tile_window->setToolTip(tr("Tile windows"));

	//QAction *playAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
	toolbar->addAction(new_workspace);
	toolbar->addAction(delete_workspace);
	toolbar->addAction(open_workspace);
	toolbar->addSeparator();
	toolbar->addAction(add_window);
	toolbar->addAction(tile_window);

	connect(add_window,SIGNAL(triggered()),this,SLOT(ReceiveSpawnWindowTriggerCurrent()));
	connect(tile_window,SIGNAL(triggered()),this,SLOT(ReceiveTileWindowTrigger()));


}

void MainWindow::Bootstrap()
{
	//If we have no windows, spawn one
	if((this->mapp.workspace_win.size()==0)&&(this->mapp.workspaces.size()>0))
	{
		this->AddSubWorkspaceWindow(mapp.workspaces.at(0));
	}
}

void MainWindow::ToolBarMessage(std::string message)
{
	this->statusBar()->showMessage(QString::fromStdString(message));
}

void MainWindow::ToolBarMessage(QString message)
{
	this->statusBar()->showMessage(message);
}

void MainWindow::WorkspaceSelected(const QModelIndex &index)
{
	//
}

void MainWindow::ReceiveSpawnWindowTrigger(const int ws_id)
{
	this->AddSubWorkspaceWindow(mapp.workspaces[ws_id]);

}

void MainWindow::ReceiveSpawnWindowTriggerCurrent()
{
	int curws = workinsp_m->row(workinsp_m->currentItem());
	if(curws<0)
	{
		QMessageBox msgBox;
		msgBox.setText("Please select workspace!");
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
	}else
	{
		ReceiveSpawnWindowTrigger(curws);
	}
}

void MainWindow::ReceiveTileWindowTrigger()
{
	mdi->tileSubWindows();
}
