#include "movement_component.h"
#include "player_control_component.h"
#include "rect_collider_component.h"
#include "transform_component.h"
#include "player_control_system.h"
#include "entity.h"
#include "vec2.h"

extern int WIDTH;
extern int PATH;

void PlayerControlSystem::Update(Entity* entity)
{
	auto movec = entity->Get<MovementComponent>();
	auto tr = entity->Get<TransformComponent>();
	auto colidec = entity->Get<RectColliderComponent>();
	auto player = entity->Get<PlayerControlComponent>();

	movec->direction = ZeroVec2;

	if (player->right == PATH)
	{
		if (tr->position.getX() < WIDTH - colidec->GetSize().getX() - player->border_size)
			movec->direction = RightVec2;
	}
	if (player->left == PATH)
	{
		if (tr->position.getX() > player->border_size)
			movec->direction = LeftVec2;
	}
}
bool PlayerControlSystem::Filter(Entity* entity) const 
{
  return entity->Contains<PlayerControlComponent>() && entity->Contains<MovementComponent>()
	  && entity->Contains<RectColliderComponent>();
}
