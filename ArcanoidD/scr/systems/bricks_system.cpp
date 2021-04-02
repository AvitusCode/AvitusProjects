#include "ball_component.h"
#include "brick_component.h"
#include "rect_collider_component.h"
#include "rectangle_render_component.h"
#include "transform_component.h"
#include "entities.h"
#include "bricks_system.h"
#include "math_support.h"
#include "entity_manager.h"
#include "counter.h"

#include "text_comp.h"
#include <cstdlib>

bool BricksSystem::Filter(Entity *entity) const 
{
  return entity->Contains<BrickComponent>() && entity->Contains<RectColliderComponent>() &&
         entity->Contains<TransformComponent>() && entity->Contains<RectangleRenderComponent>();
}
void BricksSystem::Update(Entity *entity) 
{
  auto tc = entity->Get<TransformComponent>();
  auto bc = entity->Get<BrickComponent>();
  auto rc = entity->Get<RectColliderComponent>();
  auto render = entity->Get<RectangleRenderComponent>();

  auto info = GetEntityManager()->FindFirstByTag("game_info");
  player_info *info2 = nullptr;
  if (info != nullptr)
	  info2 = info->Get<textComponent>()->getTexter();


  for (const auto &collision : rc->GetCollisions())
  {
    if (collision.entity->Contains<BallComponent>()) 
	{
		//Добавление очков игроку
		if (info2)
			info2->LogCount(1);
      if (bc->decreeaseHp() > 0) 
		  continue;
      to_delete.push_back(entity->GetId());
      bonus_spawner_.spawn(GetEntityManager(), tc->position);
    }
  }
}

bool compare(Entity* entity) 
{
	if (!entity->Contains<BrickComponent>())
		return false;

	auto bc = entity->Get<BrickComponent>();
	if (bc->getHp() > 3)
		return false;

	return true;
}

void BricksSystem::OnPostUpdate() 
{
  for (auto id : to_delete) 
  {
    GetEntityManager()->DeleteEntity(id);
  }
  to_delete.clear();

  game_counter<BrickComponent> counter(compare);
  GetEntityManager()->ForEachMutable(counter);
  if (counter.get() == 0) 
  {
    sceneManager->NextScene();
  }
}
BricksSystem::BricksSystem(SceneManager *sceneManager) : sceneManager(sceneManager) {}
