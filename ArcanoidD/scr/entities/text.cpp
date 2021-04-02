#include "entities.h"
#include "entity_manager.h"
#include "text_comp.h"

void CreateTextInfo(EntityManager *entity_manager)
{
	auto text = entity_manager->CreateEntity("game_info");


	text->Add<textComponent>(player_info(3));
}