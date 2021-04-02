#pragma once

template<typename T>
class game_counter
{
	using func_ptr = bool(*)(Entity*);

private:
	int counter = 0;
	func_ptr cmp = nullptr;

public:
	game_counter() {};
	game_counter(func_ptr func) {
		cmp = func;
	}
	void operator()(Entity* entity)
	{
		if (cmp)
		{
			if (entity->Contains<T>() && cmp(entity))
				counter++;
		}
		else
		{
			if (entity->Contains<T>())
				counter++;
		}
		
	}

	int get() const {
		return counter;
	}
};