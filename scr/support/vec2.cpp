#include "vec2.h"

double Distance(const Vec2 &lhs, const Vec2 &rhs)
{
	double x1 = lhs.getX() - rhs.getX();
	double y1 = lhs.getY() - rhs.getY();

	return std::sqrt(x1 * x1 + y1 * y1);
}