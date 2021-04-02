#pragma once

#include "system.h"
#include <vector>

class ResizeBonusSystem : public SystemInterface
{
private:
	std::vector<size_t> to_delete;
 protected:
  bool Filter(Entity *entity) const override;
  void Update(Entity *entity) override;
  void OnPostUpdate() override;
};