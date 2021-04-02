#pragma once
#include "vec2.h"
#include "entity.h"
#include <random>

class QUAD 
{
public:
	const Vec2 min;  // Верхняя левая точка
	const Vec2 max;  // Правая нижняя точка

	QUAD(const Vec2 &min, const Vec2 &max) : min(min), max(max) {}

	Vec2 Center() const {
		return Vec2((max.getX() + min.getX()) / 2, (max.getY() + min.getY()) / 2);
	}

};

class Diversity
{
public:
	const Vec2 overlap;
	const Vec2 normal;
	const double penetration;
	const bool intersecting;
	const Vec2 vec;
	/*
	@param: 
	overlap- координата точки совпадения "внутренних" частей объекта; normal - нормаль касания; 
	penetrarion- пересечение по координате x или y; intersection- is the intersection correct? 
	vec - координата нового центра;
	*/
	explicit Diversity(const Vec2 &overlap, const Vec2 &normal, const double penetration, const bool intersecting, const Vec2 vec)
		: overlap(overlap), normal(normal), penetration(penetration), intersecting(intersecting), vec(vec) {}

};

//Help functions
bool IsIntersecting(const QUAD &a, const QUAD &b);
Diversity Intersection(const QUAD &a, const QUAD &b);