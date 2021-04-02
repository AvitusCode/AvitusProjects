#pragma once

#include "system.h"
#include "scene_manager.h"
#include <vector>

class BallControlSystem : public SystemInterface
{
  std::vector<size_t> to_delete;
  SceneManager *sceneManager;

 public:
  explicit BallControlSystem(SceneManager *sceneManager);

 protected:
  void OnUpdate() override;
  void Update(Entity *entity) override;
  bool Filter(Entity *entity) const override;
};
