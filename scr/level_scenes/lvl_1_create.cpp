#include "lvl_1_creator.h"
#include "entities.h"
#include "vec2.h"

extern int WIDTH;
extern int HEIGHT;

void Lvl1Creator::Init()
{
  InitEntities();
  InitSystems();
}

void Lvl1Creator::Dispose()
{
  engine->GetEntityManager()->RemoveEntities();
  engine->GetSystemManager()->RemoveSystems();
}

void Lvl1Creator::InitEntities()
{
	auto platform_pos = Vec2((WIDTH - 16.0) / 2, HEIGHT - 20.0);
	auto platform_size = Vec2(42, 7);

	CreatePlatform(engine->GetEntityManager(), platform_pos, platform_size);
	CreateBall(engine->GetEntityManager(), platform_pos, platform_size);
	CreateTextInfo(engine->GetEntityManager());

	CreateBricks();
	CreateBorders();
}

void Lvl1Creator::CreateBricks()
{
	for (int i = 0; i < 13; i++)
		for (int j = 1; j < 4; j++)
		{
			Vec2 size = Vec2(15, 8);
			CreateBrick(engine->GetEntityManager(), Vec2(8 + i * (size.getX() + 1), 12 + j * (size.getY() + 1)), size);
		}
}
void Lvl1Creator::CreateBorders()
{
	//Ставим края для игрового поля, чтобы мячик от них отражался
	CreateBorder(engine->GetEntityManager(), Vec2(WIDTH, 6), Vec2(0, 0));  
	CreateBorder(engine->GetEntityManager(), Vec2(6, HEIGHT), Vec2(0, 0));
	CreateBorder(engine->GetEntityManager(), Vec2(6, HEIGHT), Vec2(WIDTH - 6, 0));
}