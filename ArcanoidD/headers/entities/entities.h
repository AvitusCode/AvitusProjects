#pragma once

#include "vec2.h"
#include "color.h"
#include <string>

class EntityManager;

void CreateTextInfo(EntityManager *entity_manager);
void CreateBrick(EntityManager *entity_manager, const Vec2 &pos, const Vec2 &size, int hp = 1);
void CreateBorder(EntityManager *entity_manager, const Vec2 &size, const Vec2 &pos);
void CreatePlatform(EntityManager *entity_manager, const Vec2 &platform_pos, const Vec2 &platform_size);
void CreateBall(EntityManager *entity_manager, const Vec2 &platform_pos, const Vec2 &platform_size);