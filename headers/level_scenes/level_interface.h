#pragma once

#include "engine.h"
#include "scene_manager.h"

class LevelCreatorInterface
{
 protected:
    Engine* engine;
    SceneManager* scene_manager;

 public:
	 LevelCreatorInterface(Engine* engine, SceneManager* scene) : engine(engine), scene_manager(scene) {};
    virtual ~LevelCreatorInterface() = default;

    virtual void Init() = 0;
    virtual void Dispose() = 0;
};