#include "include/WontonEngine/Component.h"
#include "include/WontonEngine/Entity.h"

won::Component::Component(Entity entity, Game* game)
	: entity{entity}, game{game}
{}
