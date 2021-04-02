#pragma once

#include "system.h"

class PhysX : public SystemInterface
{
 protected:
  void Update(Entity* entity) override;
  bool Filter(Entity* entity) const override;
private:
	double Vab(double one, double two);
};