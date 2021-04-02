#pragma once

#include <memory>

class EntityManager;
class Entity;

class SystemInterface 
{
  friend class SystemManager;
  EntityManager* entityManager{};

 public:
  void Update();
  virtual ~SystemInterface() = default;

 protected:
  virtual void OnUpdate(){};
  virtual void Update(Entity* entity){};
  virtual void OnPostUpdate(){};
  virtual bool Filter(Entity* entity) const;

  EntityManager* GetEntityManager();
};
