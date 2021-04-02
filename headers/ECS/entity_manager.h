#pragma once

#include "entity.h"
#include <memory>
#include <vector>
#include <map>

class EntityManager 
{
private:
  std::vector<std::unique_ptr<Entity>> entities;
  size_t id_gen = 0;

 public:
  // для изменяемого типа и констант
  template<typename Functor>
  void ForEachMutable(Functor& func)
  {
    for (auto& entity : entities) 
      func(entity.get());
   
  }
  template<typename Functor>
  void ForEach(const Functor& func) 
  {
    for (auto& entity : entities)
      func(entity.get());
  }

  Entity* FindFirstByTag(const std::string& tag);
  Entity* CreateEntity(const std::string &str);
  void DeleteEntity(size_t id);
  void RemoveEntities();
  virtual ~EntityManager();
};
