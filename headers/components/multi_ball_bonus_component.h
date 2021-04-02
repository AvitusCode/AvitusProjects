#pragma once

#include "component.h"
#include "vec2.h"

class MultiBallBonusComponent : public ComponentInterface
{
 public:
  int multiplier; // ������� �������� ������� �� ���� ���

  MultiBallBonusComponent(int mul) : multiplier(mul) {}
};