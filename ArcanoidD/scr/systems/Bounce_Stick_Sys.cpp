#include "Bounce_Stick_Sys.h"
#include "bounce_and_stick_comp.h"
#include "entity.h"
#include "rebound_bonus.h"
#include "linking_bonus.h"
#include "rect_collider_component.h"
#include "entity_manager.h"

#include <exception>
#include <iostream>


void BounceStickSys::Update(Entity *entity)
{
	auto rc = entity->Get<RectColliderComponent>();
	auto bn = entity->Get<BounceAndStickC>();

	for (auto &collision : rc->GetCollisions())
	{
		//TODO: очень редко бывает проблема, почему? - выяснить
		try {
			if (collision.entity->GetTag() != "platform")
				continue;
		}catch (std::bad_alloc err){
			std::cout << err.what() << std::endl;
			continue;
		}

		if (bn->is_linking)
		{
			auto ball = GetEntityManager()->FindFirstByTag("ball");
			auto bb = ball->Get<BounceAndStickC>();
			bb->is_linking = true;
		}
		else if (bn->is_rebound)
		{
			auto ball = GetEntityManager()->FindFirstByTag("ball");
			auto bb = ball->Get<BounceAndStickC>();
			bb->is_rebound = true;
		}

		if (entity->GetTag() == "bonus_link" || entity->GetTag() == "bonus_reb")
			to_delete.push_back(entity->GetId());
	}
}

bool BounceStickSys::Filter(Entity *entity) const
{
	return entity->Contains<BounceAndStickC>() && entity->Contains<RectColliderComponent>();
}

void BounceStickSys::OnPostUpdate()
{
	for (auto &id : to_delete)
	{
		GetEntityManager()->DeleteEntity(id);
	}
}