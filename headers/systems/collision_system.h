#pragma once

#include "rect_collider_component.h"
#include "transform_component.h"
#include "system.h"

class CollisionSystem : public SystemInterface
{
 protected:
  void OnUpdate() override;
  void Update(Entity* entity) override;
  bool Filter(Entity* entity) const override;
};