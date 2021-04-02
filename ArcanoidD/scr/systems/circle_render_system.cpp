#include "circle_render_component.h"
#include "transform_component.h"
#include "circle_render_system.h"
#include "entity.h"

#include "glut.h"
#include <cmath>

void CircleRenderSystem::Update(Entity* entity)
{
    auto circ = entity->Get<CircleRenderComponent>();
	auto tr = entity->Get<TransformComponent>();

	double const PI = 3.141592653;

	glBegin(GL_POLYGON);
	glColor3ub(circ->color.r, circ->color.g, circ->color.b);

	for (double i = 0; i < 2 * PI; i += PI / 6)
		glVertex2d(tr->position.getX() + circ->radius * cos(i), tr->position.getY() + circ->radius * sin(i));

	glEnd();
}

bool CircleRenderSystem::Filter(Entity* entity) const 
{
     return entity->Contains<CircleRenderComponent>() && entity->Contains<TransformComponent>();
}
