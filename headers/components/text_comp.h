#pragma once
#include "component.h"
#include "text_informer.h"
#include <memory>

class textComponent : public ComponentInterface
{
public:
	textComponent(const player_info &ifc) {
		ptr = std::make_unique<player_info>(ifc);
	}
	player_info *getTexter() {
		return ptr.get();
	}
private:
	std::unique_ptr<player_info> ptr;
};