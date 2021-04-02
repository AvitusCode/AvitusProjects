#include "system_manager.h"

void SystemManager::Update() 
{
  for (auto &system : systems) 
  {
    system->Update();
  }
}
void SystemManager::RemoveSystems() 
{
  systems.clear();
}
SystemManager::~SystemManager() 
{
  systems.clear();
}
