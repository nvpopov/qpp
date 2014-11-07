#include "EntityInspector.hpp"

using namespace molcad;

EntityInspector::EntityInspector(QWidget *parent):QTreeWidget(parent)
{
	header()->hide();
}
