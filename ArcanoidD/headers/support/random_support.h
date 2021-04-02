#pragma once
#include <random>

class game_random
{
public:
	int NextInt(int minN, int maxN)
	{
		if (maxN <= minN)
			return maxN;
		std::random_device device;
		engine.seed(device());
		std::uniform_int_distribution<int> dist(minN, maxN - 1);
		return dist(engine);
	}
private:
	std::mt19937 engine;
};