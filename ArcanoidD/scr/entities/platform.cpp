#include "movement_component.h"
#include "platform_component.h"
#include "player_control_component.h"
#include "rect_collider_component.h"
#include "rectangle_render_component.h"
#include "transform_component.h"
#include "entities.h"
#include "entity.h"
#include "entity_manager.h"
#include "color.h"

void CreatePlatform(EntityManager *entity_manager, const Vec2 &platform_pos, const Vec2 &platform_size) 
{
  double platform_speed = 250;
  auto platform = entity_manager->CreateEntity("platform");

  platform->Add<PlayerControlComponent>();
  platform->Add<PlatformComponent>();
  platform->Add<MovementComponent>(Vec2(platform_speed, 0));
  platform->Add<TransformComponent>(platform_pos);
  platform->Add<RectColliderComponent>(platform_size);
  platform->Add<RectangleRenderComponent>(platform_size, Pallite(PLATFORM), true);
}