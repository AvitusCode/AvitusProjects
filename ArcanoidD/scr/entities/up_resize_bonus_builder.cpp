
#include "resize_bonus_component.h"
#include "movement_component.h"
#include "rect_collider_component.h"
#include "rectangle_render_component.h"
#include "transform_component.h"
#include "up_resize_bonus_builder.h"
#include "entity_manager.h"
#include "color.h"

void UpResizeBonusBuilder::build(EntityManager* entity_manager, const Vec2& pos) 
{
  double power = 1.25;
  auto bonus = entity_manager->CreateEntity("bonus");
  auto size = Vec2(13, 6);
  auto speed = Vec2(200, 200);
  auto dir = DownVec2;

  RGB color = Pallite(UP_RESIZE_BON);

  bonus->Add<TransformComponent>(pos);
  bonus->Add<RectColliderComponent>(size);
  bonus->Add<MovementComponent>(speed, dir);
  bonus->Add<ResizeBonusComponent>(power);
  bonus->Add<RectangleRenderComponent>(size, color, true);
}
