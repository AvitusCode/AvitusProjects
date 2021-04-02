#include "rectangle_render_component.h"
#include "transform_component.h"
#include "rectangle_render_system.h"
#include "entity.h"
#include "glut.h"

void RectangleRenderSystem::Update(Entity* entity) 
{
  auto rect = entity->Get<RectangleRenderComponent>();
  auto tr   = entity->Get<TransformComponent>();

  glBegin(GL_POLYGON);
  glColor3ub(rect->color.r, rect->color.g, rect->color.b);

  glVertex2d(tr->position.getX(), tr->position.getY());
  glVertex2d(tr->position.getX() + rect->size.getX(), tr->position.getY());
  glVertex2d(tr->position.getX() + rect->size.getX(), tr->position.getY() + rect->size.getY());
  glVertex2d(tr->position.getX(), tr->position.getY() + rect->size.getY());

  glEnd();
}

bool RectangleRenderSystem::Filter(Entity* entity) const 
{
  return entity->Contains<RectangleRenderComponent>() && entity->Contains<TransformComponent>();
}
