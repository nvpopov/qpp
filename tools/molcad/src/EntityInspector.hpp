#ifndef _H_ENTITYINSPECTOR
#define _H_ENTITYINSPECTOR
#include <QWidget>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QHeaderView>
#include <QLabel>

namespace molcad
{
class EntityInspector:public QTreeWidget{
	Q_OBJECT
public:
	EntityInspector(QWidget *parent = 0);
};
}
#endif
