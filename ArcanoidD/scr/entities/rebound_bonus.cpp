#include "Rebound_bonus.h"
#include "entity_manager.h"
#include "transform_component.h"
#include "movement_component.h"
#include "rect_collider_component.h"
#include "rectangle_render_component.h"
#include "color.h"

#include "bounce_and_stick_comp.h"


void ReboundBonusBuilder::build(EntityManager* entity_manager, const Vec2& pos)
{
	auto bonus = entity_manager->CreateEntity("bonus");
	auto size = Vec2(13, 6);
	auto speed = Vec2(200, 200);
	auto dir = DownVec2;

	RGB color = Pallite(BOUNCE_BON);

	bonus->Add<TransformComponent>(pos);
	bonus->Add<RectColliderComponent>(size);
	bonus->Add<MovementComponent>(speed, dir);
	bonus->Add<RectangleRenderComponent>(size, color, true);
	bonus->Add<BounceAndStickC>(false, true);
}