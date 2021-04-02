#pragma once
#include <string>
#include "vec2.h"

// text interface
class Logger
{
public:
	virtual void Log(std::string &str) = 0;
	virtual void erase(const std::string &str) = 0;
	virtual void clear() = 0;
	virtual void print_on_dislocation(const Vec2 &pos, int shift = 0, int new_str = 0) = 0;
};