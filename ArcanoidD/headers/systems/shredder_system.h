#pragma once

#include "system.h"
#include <vector>

class ShredderSystem : public SystemInterface
{
private:
  std::vector<size_t> to_delete;

 protected:
  void Update(Entity *entity) override;
  void OnPostUpdate() override;
  bool Filter(Entity *entity) const override;
};