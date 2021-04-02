#pragma once
#include "component.h"
#include "vec2.h"
#include "color.h"

class LineRenderComponent : public ComponentInterface
{
public:
	Vec2 size;
	RGB color;

	LineRenderComponent(const Vec2 &size, const RGB &color, bool filled = true)
		: size(size), color(color) {}
};