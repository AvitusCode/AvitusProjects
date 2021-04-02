#pragma once

#include "system.h"
#include <memory>
#include <vector>

class SystemManager 
{
  std::vector<std::unique_ptr<SystemInterface>> systems;
  EntityManager *entity_manager;

 public:
  explicit SystemManager(EntityManager *entity_manager) : entity_manager(entity_manager) {}

  template<typename System, typename... Args>
  SystemManager *AddSystem(Args &&... args) 
  {
    auto system = new System(std::forward<Args>(args)...);
    system->entityManager = entity_manager;
    systems.push_back(std::unique_ptr<System>(system));
    return this;
  }

  void Update();
  void RemoveSystems();
  virtual ~SystemManager();
};
