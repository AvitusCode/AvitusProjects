#pragma once
#include "Scene.h"

class win_scene : public SceneInterface
{
public:
	explicit win_scene() {};
	void OnUpdate() override;
};