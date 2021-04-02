#pragma once

#include "bonus_interface.h"

class UpResizeBonusBuilder : public BonusBuilderInterface
{
 public:
  void build(EntityManager* entity_manager, const Vec2& pos) override;
};