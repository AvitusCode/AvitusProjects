#pragma once

#include "component.h"
#include "vec2.h"

class TransformComponent : public ComponentInterface
{
 public:
  Vec2 position;
  explicit TransformComponent(const Vec2& position) : position(position) {}
};