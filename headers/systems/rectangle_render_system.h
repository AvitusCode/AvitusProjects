#pragma once

#include "system.h"

class RectangleRenderSystem : public SystemInterface
{
 protected:
  void Update(Entity* entity) override;
  bool Filter(Entity* entity) const override;
};
