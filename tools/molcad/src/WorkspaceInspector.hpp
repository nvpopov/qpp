#ifndef _H_FILEINSPECTOR
#define _H_FILEINSPECTOR
#include <QWidget>
#include <QListWidget>
#include "Workspace.hpp"
#include <QMenu>
#include <QVBoxLayout>

namespace molcad
{
class WorkspaceInspector;
class WorkspaceInspectorMaster:public QWidget
{
	Q_OBJECT
public:
	WorkspaceInspector *ws_insp;
	QVBoxLayout lt;
	WorkspaceInspectorMaster(QWidget *parent = 0);
};

class WorkspaceInspector:public QListWidget
{
  Q_OBJECT
public:
	WorkspaceInspector(QWidget *parent = 0);
public slots:
	void ShowContextMenu(const QPoint& pos);
signals:
	void SpawnWindowTrigger(const int ws_id);
	void TileWindowsTrigger();
};

}
#endif
