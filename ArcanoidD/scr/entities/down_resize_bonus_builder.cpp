
#include "resize_bonus_component.h"
#include "movement_component.h"
#include "rect_collider_component.h"
#include "rectangle_render_component.h"
#include "transform_component.h"
#include "down_resize_bonus_builder.h"
#include "color.h"

void DownResizeBonusBuilder::build(EntityManager* entity_manager, const Vec2& pos)
{
  double power = 0.5;
  auto bonus = entity_manager->CreateEntity("bonus");
  Vec2 size = Vec2(13, 6);
  Vec2 speed = Vec2(100, 100);
  Vec2 dir = DownVec2;

  RGB color = Pallite(DOWN_RESIZE_BON);

  bonus->Add<TransformComponent>(pos);
  bonus->Add<RectColliderComponent>(size, ZeroVec2, false);
  bonus->Add<MovementComponent>(speed, dir);
  bonus->Add<ResizeBonusComponent>(power);
  bonus->Add<RectangleRenderComponent>(size, color, true);
}
