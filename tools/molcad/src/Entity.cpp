#include "Entity.hpp"
using namespace molcad;

Entity::Entity(Entity *ent)
{
	this->parent = ent;
}

void Entity::PrintDebug(int deep)
{
	deep += 1;

	for(int i=0; i<deep; i++){std::cout<<"-";};
	std::cout<<this->ent_name<<std::endl;
	for(int i=0; i<this->nodes.size(); i++)
	{
		nodes.at(i)->PrintDebug(deep);
	}
	deep -=1;
}

void Entity::addChild(Entity *child)
{
	this->nodes.push_back(child);
	child->parent = this;
}

bool Entity::HasActor()
{
	return false;
}

vtkActor *Entity::GetActor()
{
	return NULL;
}
