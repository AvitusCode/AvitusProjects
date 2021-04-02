#pragma once

#include "entity.h"
#include "math_support.h"

class Collision 
{
 public:
  Entity *entity;
  Diversity set;

  explicit Collision(Entity *entity, Diversity d) : entity(entity), set(std::move(d)) {};

  bool operator<(const Collision &rhs) const {
    return entity < rhs.entity;
  }
  bool operator>(const Collision &rhs) const {
    return rhs < *this;
  }
  bool operator<=(const Collision &rhs) const {
    return !(rhs < *this);
  }
  bool operator>=(const Collision &rhs) const {
    return !(*this < rhs);
  }
};