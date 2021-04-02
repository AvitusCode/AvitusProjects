#pragma once

#include "component.h"
#include <string>

class Entity;

class ResizeBonusComponent : public ComponentInterface
{
 public:
  double power;

  explicit ResizeBonusComponent(double power) : power(power) {};
};