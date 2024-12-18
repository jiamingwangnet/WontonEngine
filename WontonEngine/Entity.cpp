#include "include/WontonEngine/Entity.h"
#include "include/WontonEngine/Component.h"
#include "include/WontonEngine/Game.h"

won::Entity::Entity()
	: id{(unsigned int)-1}
{}

won::Entity::Entity(const EntId& id)
	: id{id}
{
}

std::vector<won::Component*> won::Entity::GetComponents() const
{
	std::vector<won::Component*> res{};
	
	return res;
}

won::EntId won::Entity::GetId() const
{
	return id;
}