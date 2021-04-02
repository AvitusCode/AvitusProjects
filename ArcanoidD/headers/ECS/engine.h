#pragma once

#include "entity_manager.h"
#include "system_manager.h"
#include <memory>
#include <vector>

class Engine 
{
 private:
	 std::unique_ptr<EntityManager> entityManager;
	 std::unique_ptr<SystemManager> systemManager;

 public:
	 explicit Engine() : entityManager(std::make_unique<EntityManager>()),
		 systemManager(std::make_unique<SystemManager>(entityManager.get())) {};

	 void Update();
	 EntityManager* GetEntityManager();
	 SystemManager* GetSystemManager();
};
