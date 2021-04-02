#pragma once

#include "level_interface.h"

class Lvl1Creator : public LevelCreatorInterface
{
	void InitSystems();
	void InitEntities();
	void CreateBricks();
    void CreateBorders();

 public:
    Lvl1Creator(Engine *engine, SceneManager *scene_manager) : LevelCreatorInterface(engine, scene_manager) {};
    void Init() override;
    void Dispose() override;
};