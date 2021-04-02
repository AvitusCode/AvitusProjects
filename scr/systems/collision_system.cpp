#include "collision_system.h"
#include "entity_manager.h"
#include "math_support.h"

void CollisionSystem::Update(Entity *entity) 
{
  auto tc = entity->Get<TransformComponent>();
  auto cc = entity->Get<RectColliderComponent>();
  auto box = cc->GetQUAD(tc->position);

  if (cc->is_sleeping)
    return;

  GetEntityManager()->ForEach([cc, box, entity](Entity *e) 
  {
    if (!e->Contains<RectColliderComponent>() || e->GetId() == entity->GetId())
      return;

    auto tc2 = e->Get<TransformComponent>();
    auto cc2 = e->Get<RectColliderComponent>();
    QUAD box2 = cc2->GetQUAD(tc2->position);

	if (cc2->is_sleeping)
		return;

    Diversity set = Intersection(box, box2);
    if (set.intersecting)
	{
      cc->Collide(e, set);
    }
  });
}

void CollisionSystem::OnUpdate() 
{
  GetEntityManager()->ForEach([](Entity *e) 
  {
    if (e->Contains<RectColliderComponent>())
      e->Get<RectColliderComponent>()->Clear();
  });
}

bool CollisionSystem::Filter(Entity *entity) const
{
  return entity->Contains<TransformComponent>() && entity->Contains<RectColliderComponent>();
}
