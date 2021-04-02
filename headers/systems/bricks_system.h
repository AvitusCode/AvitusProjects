#pragma once

#include "bonus_spawner.h"
#include "system.h"
#include "scene_manager.h"
#include <vector>

class BricksSystem : public SystemInterface
{
private:
  std::vector<size_t> to_delete;
  SceneManager *sceneManager;
  BonusSpawner bonus_spawner_;

 public:
  explicit BricksSystem(SceneManager *sceneManager);

 protected:
  bool Filter(Entity *entity) const override;
  void Update(Entity *entity) override;
  void OnPostUpdate() override;
};