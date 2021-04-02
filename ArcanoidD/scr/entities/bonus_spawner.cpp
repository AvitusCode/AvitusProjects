#include "bonus_spawner.h"
#include "multi_ball_bonus_builder.h"
#include "down_resize_bonus_builder.h"
#include "up_resize_bonus_builder.h"
#include "linking_bonus.h"
#include "rebound_bonus.h"
#include "entity_manager.h"

// Ќе забывать добавл€ть сюда новые бонусы
BonusSpawner::BonusSpawner() 
{
  builders.push_back(std::make_unique<UpResizeBonusBuilder>());
  builders.push_back(std::make_unique<DownResizeBonusBuilder>());
  builders.push_back(std::make_unique<MultiBallBonusBuilder>());
  builders.push_back(std::make_unique<LinkingBonusBuilder>());
  builders.push_back(std::make_unique<ReboundBonusBuilder>());
}
void BonusSpawner::spawn(EntityManager* em, const Vec2 &pos) 
{
  auto id = random.NextInt(-3, builders.size());
  if (id < 0) 
	  return;

  builders.at(id)->build(em, pos);
}
