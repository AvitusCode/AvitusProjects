#pragma once
#include "system.h"

class TextureSys : public SystemInterface
{
protected:
	void Update(Entity* entity) override;
	bool Filter(Entity* entity) const override;
};