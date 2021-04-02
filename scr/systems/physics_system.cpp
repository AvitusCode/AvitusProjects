#include "rect_collider_component.h"
#include "rigid_body_component.h"
#include "transform_component.h"
#include "physics_system.h"
#include "movement_component.h"

bool PhysX::Filter(Entity* entity) const
{
  return entity->Contains<TransformComponent>() && entity->Contains<RectColliderComponent>() &&
         entity->Contains<RigidBodyComponent>();
}

void PhysX::Update(Entity* entity)
{
  auto tc = entity->Get<TransformComponent>();
  auto cc = entity->Get<RectColliderComponent>();
  auto rc = entity->Get<RigidBodyComponent>();
  auto mv = entity->Get<MovementComponent>();

  //Если объект не обладает кинематикой, то он статичен
  if (!rc->is_kinematic)
    return;

  Vec2 vect(0, 0);
  for (const auto& collision : cc->GetCollisions()) 
  {
    vect += collision.set.normal * collision.set.penetration;

	//if collision body have Rigid and Move component - we can estimate the impuls in simple case;
	if (collision.entity->Contains<RigidBodyComponent>() && collision.entity->Contains<MovementComponent>())
	{
		auto mv2 = collision.entity->Get<MovementComponent>();
		double MIN_I = 8.0; // minimum of impuls

		rc->impuls = MIN_I - (1 + rc->deg) * Vab(mv->speed.getX() - mv2->speed.getX(), mv->speed.getY() - mv2->speed.getY());
	}
	else
	{
		rc->impuls = 0;
	}
	mv->speed.setX(mv->speed.getX() + (rc->impuls * collision.set.normal.getX()) / rc->mass);
	mv->speed.setY(mv->speed.getY() + (rc->impuls * collision.set.normal.getY()) / rc->mass);

	if (mv->speed.getX() > 250)
		mv->speed.setX(250);
	if (mv->speed.getY() > 250)
		mv->speed.setY(250);
  }

  tc->position += vect;
}

double PhysX::Vab(double one, double two)
{
	return one + two; // Можно улучшить, например, добавив вектор угловой скорости (обработка вращений - на будущее)
}
