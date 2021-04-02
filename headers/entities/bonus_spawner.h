#pragma once

#include "bonus_interface.h"
#include "random_support.h"
#include "entity_manager.h"
#include "vec2.h"
#include <memory>
#include <vector>

class BonusSpawner 
{
private:
  game_random random;
  std::vector<std::unique_ptr<BonusBuilderInterface>> builders;
 public:
  BonusSpawner();
  void spawn(EntityManager* em, const Vec2& pos);
};