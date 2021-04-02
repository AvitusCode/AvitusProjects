#pragma once
#include "scene.h"

class lose_scene : public SceneInterface
{
public:
	explicit lose_scene() {};
	void OnUpdate() override;
};