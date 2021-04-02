#pragma once

#include "component.h"
#include "glut.h"

class PlayerControlComponent : public ComponentInterface
{
	using BUTTON = int;

public:
	BUTTON left = GLUT_KEY_LEFT;
	BUTTON right = GLUT_KEY_RIGHT;
	BUTTON f1 = GLUT_KEY_F1;

	double border_size = 6;
};