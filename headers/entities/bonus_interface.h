#pragma once

#include "entity_manager.h"
#include "vec2.h"

class BonusBuilderInterface
{
 public:
  virtual void build(EntityManager* entity_manager, const Vec2& pos) = 0;
  virtual ~BonusBuilderInterface() = default;
};