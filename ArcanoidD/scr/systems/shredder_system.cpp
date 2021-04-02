#include "rect_collider_component.h"
#include "transform_component.h"
#include "shredder_system.h"
#include "entity.h"
#include "entity_manager.h"

extern int HEIGHT;

void ShredderSystem::Update(Entity *entity) 
{
  auto tc = entity->Get<TransformComponent>();
  auto cc = entity->Get<RectColliderComponent>();

  //Удаляем объекты, если они упали ниже нормы
  if (tc->position.getY() > (HEIGHT - cc->GetSize().getY())) 
  {
    to_delete.push_back(entity->GetId());
  }
}

void ShredderSystem::OnPostUpdate()
{
  for (auto id : to_delete)
    GetEntityManager()->DeleteEntity(id);

  to_delete.clear();
}

bool ShredderSystem::Filter(Entity *entity) const 
{
  return entity->Contains<TransformComponent>() && entity->Contains<RectColliderComponent>();
}
