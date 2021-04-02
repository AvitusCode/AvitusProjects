#include "entity.h"
#include "entity_manager.h"
#include <algorithm>
#include <memory>

Entity* EntityManager::CreateEntity(const std::string &str)
{
  auto entity = new Entity();

  entities.push_back(std::unique_ptr<Entity>(entity));
  entity->id = ++id_gen;
  entity->SetTag(str);

  return entity;
}

void EntityManager::DeleteEntity(size_t id)
{
  auto iter = std::remove_if(entities.begin(), entities.end(), [id](const auto& entity) { return entity->GetId() == id; });
  entities.erase(iter, entities.end());
}

EntityManager::~EntityManager() 
{
  entities.clear();
}

void EntityManager::RemoveEntities() 
{
  entities.clear();
}

Entity* EntityManager::FindFirstByTag(const std::string& tag)
{
  for (auto& entity : entities) {
    if (entity->tag == tag) 
		return entity.get();
  }

  return nullptr;
}
