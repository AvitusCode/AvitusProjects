#include "movement_component.h"
#include "transform_component.h"
#include "movement_system.h"
#include "entity.h"
#include "glut.h"

bool MovementSystem::Filter(Entity* entity) const
{
  return entity->Contains<TransformComponent>() && entity->Contains<MovementComponent>();
}

//double true_frame()
//{
//	static size_t frame;
//	frame++;
//
//	time = glutGet(GLUT_ELAPSED_TIME);
//	if (time - timebase > 1000) {
//		timebase = time;
//		return frame * 1000.0 / (time - timebase);
//		frame = 0;
//	}
//	else
//		return time;
//}

void MovementSystem::Update(Entity* entity)
{
  auto tc = entity->Get<TransformComponent>();
  auto mc = entity->Get<MovementComponent>();

  auto dt = [](double type) {
	  if (type >= 0.03)
		  return 0.025;
	  else
		  return type;
  };


  tc->position += mc->direction * mc->speed * dt(static_cast<double>(glutGet(GLUT_ELAPSED_TIME)));
}
