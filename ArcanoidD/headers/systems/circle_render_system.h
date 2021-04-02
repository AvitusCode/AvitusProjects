#pragma once

#include "system.h"
#include <memory>

class CircleRenderSystem : public SystemInterface
{
 protected:
  void Update(Entity* entity) override;
  bool Filter(Entity* entity) const override;
};