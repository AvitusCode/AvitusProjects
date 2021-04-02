#include "rect_collider_component.h"
#include "transform_component.h"
#include "entity_manager.h"
#include "vec2.h"
#include "color.h"

#include "rectangle_render_component.h"

void CreateBorder(EntityManager *entity_manager, const Vec2 &size, const Vec2 &pos) 
{
  auto border = entity_manager->CreateEntity("border");

  border->Add<TransformComponent>(pos);
  border->Add<RectangleRenderComponent>(size, Pallite(BORDER));
  border->Add<RectColliderComponent>(size);
}