#include "engine.h"

void Engine::Update() 
{
  systemManager->Update();
}

EntityManager* Engine::GetEntityManager() 
{
  return entityManager.get();
}
SystemManager* Engine::GetSystemManager() 
{
  return systemManager.get();
}
