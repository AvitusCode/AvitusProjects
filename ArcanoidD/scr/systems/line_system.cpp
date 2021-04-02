#include "line_system.h"
#include "line_component.h"
#include "transform_component.h"
#include "entity.h"
#include "glut.h"

void LineRenderSystem::Update(Entity *entity)
{
	auto line = entity->Get<LineRenderComponent>();
	auto tr   = entity->Get<TransformComponent>();

	glBegin(GL_LINE);
	glColor3ub(line->color.r, line->color.g, line->color.b);
	glLineWidth(10);
	glVertex2d(tr->position.getX(), tr->position.getY());
	glVertex2d(line->size.getX(), line->size.getY());
	glEnd();
}

bool LineRenderSystem::Filter(Entity *entity) const
{
	return entity->Contains<LineRenderComponent>() && entity->Contains<TransformComponent>();
}