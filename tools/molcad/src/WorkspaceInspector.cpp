#include "WorkspaceInspector.hpp"

using namespace molcad;

WorkspaceInspector::WorkspaceInspector(QWidget *parent):QListWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);
//	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(ShowContextMenu(const QPoint&)));
}

void WorkspaceInspector::ShowContextMenu(const QPoint &pos)
{
	QPoint globalPos = this->mapToGlobal(pos);

	QMenu myMenu;
	myMenu.addAction("Add new workspace window");
	myMenu.addAction("Tile windows");

	//Prevent incredible zooming
	//GetInteractor()->RightButtonReleaseEvent();

	QAction* selectedItem = myMenu.exec(globalPos);
	if (selectedItem)
	{
		if (selectedItem->text().toStdString()=="Add new workspace window")
		{
			int _id = this->row(this->currentItem());
			std::cout<<_id<<std::endl;
			emit this->SpawnWindowTrigger(_id);
		}
		if (selectedItem->text().toStdString()=="Tile windows")
		{
			emit this->TileWindowsTrigger();
		}
	}
	else
	{
		// nothing was chosen
	}
}


WorkspaceInspectorMaster::WorkspaceInspectorMaster(QWidget *parent):QWidget(parent)
{
	ws_insp = new WorkspaceInspector(this);
	this->setLayout(&lt);
	lt.addWidget(ws_insp);
}
