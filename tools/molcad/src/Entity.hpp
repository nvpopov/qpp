#ifndef _H_ENTITY_
#define _H_ENTITY_
#include <iostream>
#include <QObject>
#include <QString>
#include <vtkActor.h>

namespace molcad
{

const int entity_module_version=2;

class Entity;

class Entity
{
public:

	Entity *parent;
	std::vector<Entity*> nodes;
	Entity(Entity *ent);

	void PrintDebug(int deep);
	void addChild(Entity *child);
	bool HasActor();
	vtkActor* GetActor();

	std::string ent_name;
	int ent_id;
};
}

#endif
