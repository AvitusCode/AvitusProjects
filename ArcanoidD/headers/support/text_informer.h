#pragma once
#include "text_interface.h"
#include <deque>

class player_info : public Logger
{
public:
	explicit player_info(std::size_t size) : max_size(size), count_info(0) {
	}

	void Log(std::string &str);
	void LogCount(int some);
	void erase(const std::string &str);
	void clear();
	void print_on_dislocation(const Vec2 &pos, int shift = 0, int new_str = 0);

	std::size_t getSize() const {
		return max_size;
	}
private:
	std::deque<std::string> logger;
	std::size_t max_size;
	int count_info;
};