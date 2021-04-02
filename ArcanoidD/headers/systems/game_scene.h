#pragma once

#include "level_interface.h"
#include "game_scene.h"
#include "vec2.h"
#include <memory>
#include "glut.h"

class LevelCreatorInterface;

template<typename LevelCreator>
class GameScene : public SceneInterface
{
private:
  std::unique_ptr<LevelCreatorInterface> level_creator;
  std::unique_ptr<Engine> engine;

 public:
  explicit GameScene() : engine(std::make_unique<Engine>())
  {
	  level_creator = std::make_unique<LevelCreator>(engine.get(), GetSceneManager());
  }

  void OnCreate() override {
    level_creator->Init();
  }
  void OnUpdate() override {
	  engine->Update();
  }
  void OnDispose() override {
	  level_creator->Dispose();
  }

  ~GameScene() override = default;
};