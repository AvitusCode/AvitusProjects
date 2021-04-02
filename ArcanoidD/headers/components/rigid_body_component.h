#pragma once

#include "component.h"
#include "vec2.h"

class RigidBodyComponent : public ComponentInterface
{
 public:
  double mass = 1.0;
  double impuls = 0;
  double deg = 1.0;
  bool is_kinematic = true;
};