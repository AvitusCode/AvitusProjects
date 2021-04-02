#pragma once
#include "system.h"
#include <vector>

class BounceStickSys : public SystemInterface
{
private:
	std::vector<size_t> to_delete{};
protected:
	void Update(Entity* entity) override;
	bool Filter(Entity* entity) const override;
	void OnPostUpdate() override;
};