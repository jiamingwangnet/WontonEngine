#include "include/WontonEngine/EntityManager.h"
#include "include/WontonEngine/Entity.h"

won::priv::EntityManager::EntityManager(ComponentManager& componentManager)
	: componentManager{ componentManager }, signatures( MAX_ENTITIES )
{
	// initialise queue with incrementing IDs (0 to MAX_ENTITIES)
	for (EntId i = 0; i < MAX_ENTITIES; i++)
	{
		availableIds.push((Entity)i);//  entity Ids must be between (0 to MAX_ENTITIES)
	}
}

won::Entity won::priv::EntityManager::CreateEntity()
{
	// take id from front of the queue
	// pop the id to set it as used
	Entity id = availableIds.front();
	availableIds.pop();
	entities++;
	created.insert(id.GetId());
	return id;
}

void won::priv::EntityManager::DestroyEntity(Entity entity)
{
	// call componentManager's EntityDestroyed !!IMPORTANT TO DO THIS FIRST!! always destroy components first

	// reset signature
	// reduce entity count
	// push the id to the back of the queue
	
	componentManager.EntityDestroyed(entity.GetId());

	signatures[entity.GetId()].reset();
	entities--;
	availableIds.push(entity.GetId());
	created.erase(entity.GetId());
}

void won::priv::EntityManager::Clear()
{
	std::size_t total = entities;
	for (std::size_t i = 0; i < total; i++)
	{
		DestroyEntity(*created.begin()); // TODO: optimise
	}
}

void won::priv::EntityManager::SetSignature(Entity entity, Signature sig)
{
	signatures[entity.GetId()] = sig;
}

won::priv::Signature won::priv::EntityManager::GetSignature(Entity entity)
{
	return signatures[entity.GetId()];
}
