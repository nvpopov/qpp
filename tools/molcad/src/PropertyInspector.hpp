#ifndef _H_PROPERTYINSPECTOR
#define _H_PROPERTYINSPECTOR
#include <QWidget>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QHeaderView>
#include <QTableWidget>

namespace molcad
{
class PropertyInspector:public QTableWidget{
	Q_OBJECT
public:
	PropertyInspector(QWidget *parent = 0);
};
}
#endif
