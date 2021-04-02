#pragma once
#include "system.h"

class LineRenderSystem : public SystemInterface
{
protected:
	void Update(Entity* entity) override;
	bool Filter(Entity* entity) const override;
};