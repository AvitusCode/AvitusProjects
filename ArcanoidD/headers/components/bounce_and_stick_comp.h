#pragma once
#include "component.h"

class BounceAndStickC : public ComponentInterface
{
public:
	bool is_linking = false; // Link to platform
	bool is_rebound = false; // Jump from the deep
	bool on_board = false;

	BounceAndStickC() {};
	BounceAndStickC(bool link, bool rebound) : is_linking(link), is_rebound(rebound) {};
};