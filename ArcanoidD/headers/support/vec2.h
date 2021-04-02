#pragma once

#include <cmath>

class Vec2 
{
private:
	double x;
	double y;

 public:
  constexpr Vec2() noexcept : x(0.0), y(0.0) {}
  constexpr Vec2(double x, double y) noexcept : x(x), y(y) {}

  void MulX(const double c) {
	  x *= c;
  }
  void MulY(const double c) {
	  y *= c;
  }
  double getX() const {
	  return x;
  }
  double getY() const {
	  return y;
  }
  void setX(const double c) {
	  x = c;
  }
  void setY(const double c) {
	  y = c;
  }

  bool operator==(const Vec2 &rhs) const {
    return (x == rhs.x) && (y == rhs.y);
  }
  bool operator!=(const Vec2 &rhs) const {
    return !(rhs == *this);
  }

  Vec2 operator+(const Vec2 &rhs) const {
    return Vec2(x + rhs.x, y + rhs.y);
  }

  Vec2 operator+=(const Vec2 &rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  Vec2 operator-(const Vec2 &rhs) const {
    return Vec2(x - rhs.x, y - rhs.y);
  }

  Vec2 operator*(double c) const {
    return Vec2(x * c, y * c);
  }

  Vec2 operator*=(double c) {
    x *= c;
    y *= c;
    return *this;
  }

  Vec2 operator*(const Vec2 &rhs) const {
    return Vec2(x * rhs.x, y * rhs.y);
  }

  Vec2 operator*=(const Vec2 &rhs) {
    x *= rhs.x;
    y *= rhs.y;
    return *this;
  }

  void rotationAngle(double angle) {
	  double x1 = x * std::cos(angle) + y * std::sin(angle);
	  y = -x * std::sin(angle) + y * std::cos(angle);
	  x = x1;
  }
  double DotProd(const Vec2 &rhs) const {
    return x * rhs.x + y * rhs.y;
  }

  double CrossProd(const Vec2 &rhs) const {
    return x * rhs.y - y * rhs.x;
  }

  Vec2 Abs() const {
    return Vec2(std::abs(x), std::abs(y));
  }

  // 2d Евклидово пространство (для нормировки)
  double base() const {
    return std::sqrt(x * x + y * y);
  }

  Vec2 Normalize() {
    auto m = base();
	if (m <= 0.000000001)
		x = y = 0;
	else {
      x /= m;
      y /= m;
    }

    return *this;
  }

};

//Набор универсальных констант
const Vec2 DownVec2(0, 1);
const Vec2 RightVec2(1, 0);
const Vec2 LeftVec2(-1, 0);
const Vec2 ZeroVec2(0, 0);
const Vec2 UpVec2(0, -1);

double Distance(const Vec2 &lhs, const Vec2 &rhs);