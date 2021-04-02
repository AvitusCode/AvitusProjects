#pragma once

#include "bonus_interface.h"
class DownResizeBonusBuilder : public BonusBuilderInterface
{
 public:
  void build(EntityManager* entity_manager, const Vec2& pos) override;
};
