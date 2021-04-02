#pragma once

#include "system.h"

class MovementSystem : public SystemInterface
{
 protected:
  void Update(Entity* entity) override;
  bool Filter(Entity* entity) const override;
};