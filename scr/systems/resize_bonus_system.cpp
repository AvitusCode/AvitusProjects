
#include "resize_bonus_component.h"
#include "rect_collider_component.h"
#include "rectangle_render_component.h"
#include "resize_bonus_system.h"
#include "entity.h"
#include "entity_manager.h"


void ApplyBonus(Entity* entity, Entity* bonus) 
{
  auto bc = bonus->Get<ResizeBonusComponent>();
  auto render = entity->Get<RectangleRenderComponent>();
  auto box = entity->Get<RectColliderComponent>();

  box->size.MulX(bc->power);
  render->size.MulX(bc->power);
}

bool ResizeBonusSystem::Filter(Entity* entity) const
{
  return entity->Contains<ResizeBonusComponent>() && entity->Contains<RectColliderComponent>();
}

void ResizeBonusSystem::Update(Entity* entity) 
{
  auto bc = entity->Get<ResizeBonusComponent>();
  auto rc = entity->Get<RectColliderComponent>();

  for (auto& collision : rc->GetCollisions())
  {
    if (collision.entity->GetTag() != "platform") 
		continue;

	rc->is_sleeping = true;
	to_delete.push_back(entity->GetId());

    ApplyBonus(collision.entity, entity);
  }
}

void ResizeBonusSystem::OnPostUpdate()
{
	for (auto &id : to_delete)
	{
		GetEntityManager()->DeleteEntity(id);
	}
}
