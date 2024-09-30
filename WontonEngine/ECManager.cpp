#include "include/WontonEngine/ECManager.h"
#include "include/WontonEngine/Game.h"
#include "include/WontonEngine/ComponentManager.h"
#include "include/WontonEngine/EntityManager.h"

won::priv::ComponentManager& won::priv::ECManager::GetComponentManager()
{
	return Game::compManager;
}

won::priv::EntityManager& won::priv::ECManager::GetEntityManager()
{
	return Game::entityManager;
}