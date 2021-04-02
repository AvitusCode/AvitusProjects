
#include "multi_ball_bonus_component.h"
#include "movement_component.h"
#include "rect_collider_component.h"
#include "transform_component.h"
#include "entities.h"
#include "multi_ball_bonus_system.h"
#include "entity.h"
#include "entity_manager.h"

void ApplyBonus(Entity* bonus, EntityManager* entity_manager, Entity* platform) 
{
  auto bc = bonus->Get<MultiBallBonusComponent>();
  auto ball = entity_manager->FindFirstByTag("ball");
  Vec2 pos = ball->Get<TransformComponent>()->position;
  Vec2 dir = ball->Get<MovementComponent>()->direction;

  for (int i = 1; i < bc->multiplier; i++) 
  {
	pos += Vec2(10, 10);
    CreateBall(entity_manager, pos, dir * Vec2(-1, 1));
  }

}

void MultiBallBonusSystem::Update(Entity* entity)
{
  auto bc = entity->Get<MultiBallBonusComponent>();
  auto rc = entity->Get<RectColliderComponent>();

  for (auto& collision : rc->GetCollisions()) 
  {
    if (collision.entity->GetTag() != "platform") 
		continue;

	rc->is_sleeping = true;
	to_delete.push_back(entity->GetId());

    ApplyBonus(entity, GetEntityManager(), collision.entity);
  }
}

bool MultiBallBonusSystem::Filter(Entity* entity) const
{
  return entity->Contains<MultiBallBonusComponent>() && entity->Contains<RectColliderComponent>();
}

void MultiBallBonusSystem::OnPostUpdate()
{
	for (auto &id : to_delete)
	{
		GetEntityManager()->DeleteEntity(id);
	}
}