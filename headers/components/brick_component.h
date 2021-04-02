#pragma once

#include "component.h"

class BrickComponent : public ComponentInterface
{
private:
	int hp = 1;
 public:
  explicit BrickComponent(int health = 1) : hp(health) {
	  if (health == 3) hp = 1 << 7; // It`s makes God brick
  }

  int getHp() const {
	  return hp;
  }
  int decreeaseHp() {
	  return --hp;
  }
};