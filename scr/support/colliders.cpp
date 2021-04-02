#include "math_support.h"
#include "vec2.h"

bool IsIntersecting(const QUAD &a, const QUAD &b)
{
  if ((a.max.getX() < b.min.getX() || a.min.getX() > b.max.getX()) ||
	  a.max.getY() < b.min.getY() || a.min.getY() > b.max.getY())
	  return false;

  return true;
}

Diversity Intersection(const QUAD &a, const QUAD &b)
{
  Vec2 centre_cord = a.Center() - b.Center();

  double a_hx = (a.max.getX() - a.min.getX()) / 2;
  double b_hx = (b.max.getX() - b.min.getX()) / 2;

  double a_hy = (a.max.getY() - a.min.getY()) / 2;
  double b_hy = (b.max.getY() - b.min.getY()) / 2;

  double x_overlap = a_hx + b_hx - std::abs(centre_cord.getX());
  double y_overlap = a_hy + b_hy - std::abs(centre_cord.getY());
  Vec2 overlap = Vec2(x_overlap, y_overlap);

  if (x_overlap > 0 && y_overlap > 0) 
  {
    if (x_overlap < y_overlap) 
	{
      if (centre_cord.getX() < 0)
        return Diversity(overlap, LeftVec2, x_overlap, true, centre_cord);
	  else 
        return Diversity(overlap, RightVec2, x_overlap, true, centre_cord);
 
    } 
	else 
	{
      if (centre_cord.getY() < 0)
        return Diversity(overlap, UpVec2, y_overlap, true, centre_cord);
	  else 
		  return Diversity(overlap, DownVec2, y_overlap, true, centre_cord);
    }
  }

  return Diversity(ZeroVec2, ZeroVec2, 0, false, centre_cord);
}