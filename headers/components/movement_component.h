#pragma once

#include "component.h"
#include "vec2.h"

class MovementComponent : public ComponentInterface
{
 public:
  Vec2 speed;
  Vec2 direction;

  explicit MovementComponent(const Vec2 &speed, const Vec2 &dir = ZeroVec2) : speed(speed), direction(dir) {}
};
