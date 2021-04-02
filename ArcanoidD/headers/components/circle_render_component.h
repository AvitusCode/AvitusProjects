#pragma once

#include "component.h"
#include "color.h"

class CircleRenderComponent : public ComponentInterface
{
 public:
  int radius;
  RGB color;

  CircleRenderComponent(int radius, const RGB &color, bool filled = true)
	  : radius(radius), color(color) {};
};