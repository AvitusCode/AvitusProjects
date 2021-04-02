
#include "multi_ball_bonus_component.h"
#include "movement_component.h"
#include "rect_collider_component.h"
#include "rectangle_render_component.h"
#include "transform_component.h"
#include "multi_ball_bonus_builder.h"
#include "color.h"

void MultiBallBonusBuilder::build(EntityManager* entity_manager, const Vec2& pos)
{
  auto bonus = entity_manager->CreateEntity("bonus");
  Vec2 size = Vec2(13, 6);
  Vec2 speed = Vec2(200, 200);
  Vec2 dir = DownVec2;

  RGB color = Pallite(MULTI_BALL_BON);

  bonus->Add<TransformComponent>(pos);
  bonus->Add<RectColliderComponent>(size);
  bonus->Add<MovementComponent>(speed, dir);
  bonus->Add<MultiBallBonusComponent>(2);
  bonus->Add<RectangleRenderComponent>(size, color, true);
}
