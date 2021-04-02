#include "textSys.h"
#include "entity.h"
#include "text_comp.h"

void textSystem::Update(Entity *entity)
{
	auto text = entity->Get<textComponent>();
	Logger* to_print = text->getTexter();

	to_print->print_on_dislocation(Vec2(20, 180), 0, 5); //�������� ��������� ������
	
}

bool textSystem::Filter(Entity* entity) const
{
	return entity->Contains<textComponent>();
}