#pragma once

#include "component.h"
#include "vec2.h"

class MultiBallBonusComponent : public ComponentInterface
{
 public:
  int multiplier; // —колько спавнить м€чиков за один раз

  MultiBallBonusComponent(int mul) : multiplier(mul) {}
};