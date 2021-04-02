#include "ball_component.h"
#include "movement_component.h"
#include "rect_collider_component.h"
#include "rigid_body_component.h"
#include "transform_component.h"
#include "ball_control_system.h"
#include "entity.h"
#include "entity_manager.h"
#include "math_support.h"
#include "platform_component.h"
#include "bounce_and_stick_comp.h"
#include "counter.h"

#include "glut.h"
#include <iostream>

extern unsigned char ACTION;
extern int HEIGHT;

void BallControlSystem::Update(Entity *entity) 
{
  auto tc = entity->Get<TransformComponent>();
  auto mc = entity->Get<MovementComponent>();
  auto rc = entity->Get<RigidBodyComponent>();
  auto cc = entity->Get<RectColliderComponent>();
  auto bo = entity->Get<BounceAndStickC>();

  //Проверка на отскок (Фантомная платформа)
  if ((tc->position.getY() > (HEIGHT - 10)) && bo->is_rebound)
  {
	  mc->direction.MulY(-1);
	  mc->direction.MulX(-1);
	  bo->is_rebound = false;
	  return;
  }

  if (cc->AnyCollisions() && bo->on_board == false)
  {
    for (const auto &collision : cc->GetCollisions()) 
	{
		if (collision.entity->GetTag() == "bonus")
			continue;

      Vec2 v = collision.set.normal;
	  //Double не сравнить с нулем D:
      if (v.getX() > 0 || v.getX() < 0) 
	  {
        mc->direction.MulX(-1);
      }
      if (v.getY() > 0 || v.getY() < 0)
	  {
        mc->direction.MulY(-1);
      }

      if (collision.entity->Contains<PlatformComponent>())
	  {
        auto rc_p = collision.entity->Get<RectColliderComponent>();
        double width = rc_p->GetSize().getX() / 3.5;

		//Проверка на прилипание (можно захватить один из мячиков)
		if (bo->is_linking)
		{
			bo->on_board = true;
			auto plat = GetEntityManager()->FindFirstByTag("platform");
			auto mp = plat->Get<MovementComponent>();
			mc->direction = mp->direction;
			mc->speed = mp->speed;
		}

        if (std::abs(collision.set.vec.getX()) > width)
          mc->direction.MulX(-1);
      }
    }
  }
  else if (bo->is_linking && bo->on_board)
  {
	  //Если мячик прилип и на платформе, то либо отлипаем по нажатию, либо перемещаемся с платформой

	  if (ACTION == 'q')
	  {
		  bo->is_linking = false;
		  bo->on_board = false;
		  mc->direction = Vec2(1, -1).Normalize();
		  mc->speed = Vec2(150.0, 150.0);
	  }
	  else
	  {
		  auto plat = GetEntityManager()->FindFirstByTag("platform");
		  auto mp = plat->Get<MovementComponent>();
		  mc->direction = mp->direction;
	  }
  }
}

bool BallControlSystem::Filter(Entity *entity) const 
{
  return entity->Contains<BallComponent>() && entity->Contains<TransformComponent>() &&
         entity->Contains<MovementComponent>() && entity->Contains<RectColliderComponent>() &&
         entity->Contains<RigidBodyComponent>() && entity->Contains<BounceAndStickC>();
}
void BallControlSystem::OnUpdate()
{
  game_counter<BallComponent> counter;
  GetEntityManager()->ForEachMutable(counter);

  if (counter.get() == 0) 
  {
	  //Maybe make exit or chagne game?
	  std::cout << "The ball is falling out!" << std::endl;
	  sceneManager->SetScene("lose_map");
  }
}

BallControlSystem::BallControlSystem(SceneManager *sceneManager) : sceneManager(sceneManager) {}
