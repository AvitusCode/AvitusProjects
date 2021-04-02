#pragma once

#include "collision.h"
#include "entity.h"
#include "component.h"
#include "math_support.h"
#include "vec2.h"
#include <set>
#include <utility>

class RectColliderComponent : public ComponentInterface
{
private:
	std::set<Collision> collisions{};

 public:
  Vec2 size;
  Vec2 offset;
  bool is_sleeping;

  explicit RectColliderComponent(const Vec2 &size, const Vec2 &offset = ZeroVec2, bool is_sleeping = false)
      : size(size), offset(offset), is_sleeping(is_sleeping) {}

  const std::set<Collision> &GetCollisions() const {
    return collisions;
  }

  bool AnyCollisions() const {
    return !collisions.empty();
  }

  void Collide(Entity *entity, const Diversity &set) {
    collisions.emplace(Collision{entity, set});
  }

  void Clear() {
    collisions.clear();
  }

  QUAD GetQUAD(const Vec2 &pos) const {
    return QUAD(offset + pos, size + offset + pos);
  }

  Vec2 GetSize() const {
    return size;
  }
};