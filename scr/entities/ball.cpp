
#include "ball_component.h"
#include "circle_render_component.h"
#include "movement_component.h"
#include "rect_collider_component.h"
#include "rigid_body_component.h"
#include "transform_component.h"
#include "bounce_and_stick_comp.h"

#include "entities.h"
#include "entity_manager.h"
#include "vec2.h"
#include "color.h"


void CreateBallSupportFunc(EntityManager *entity_manager, const Vec2 &ball_pos, const Vec2 &dir) 
{
  auto br = 5.0;
  auto ball_speed = 150.0;
  auto ball_size = Vec2(br, br);
  auto ball = entity_manager->CreateEntity("ball");


  ball->Add<TransformComponent>(ball_pos);
  ball->Add<RectColliderComponent>(ball_size);
  ball->Add<MovementComponent>(Vec2(ball_speed, ball_speed), dir);
  ball->Add<CircleRenderComponent>(br, Pallite(BALL), true);
  ball->Add<BallComponent>();
  ball->Add<RigidBodyComponent>();
  ball->Add<BounceAndStickC>();

  //Experimental
 /* ball->Add<MusicComponent>("ball.wav");*/
}

void CreateBall(EntityManager *entity_manager, const Vec2 &platform_pos, const Vec2 &platform_size)
{
	auto br = 3.0;
	auto ball_pos = Vec2(platform_pos.getX() + platform_size.getX() / 2 - br / 2, platform_pos.getY() - br);

	CreateBallSupportFunc(entity_manager, ball_pos, Vec2(1, -1).Normalize());
}