#pragma once

#include "system.h"

class PlayerControlSystem : public SystemInterface
{
 protected:
  void Update(Entity* entity) override;
  bool Filter(Entity* entity) const override;
};