#include "lvl_2_creator.h"
#include "entities.h"
#include "vec2.h"

extern int WIDTH;
extern int HEIGHT;


void Lvl2Creator::Init()
{
	InitEntities();
	InitSystems();
}

void Lvl2Creator::Dispose()
{
	engine->GetEntityManager()->RemoveEntities();
	engine->GetSystemManager()->RemoveSystems();
}

void Lvl2Creator::InitEntities()
{
	auto platform_pos = Vec2((WIDTH - 16.0) / 2, HEIGHT - 20.0);
	auto platform_size = Vec2(42, 7);

	CreatePlatform(engine->GetEntityManager(), platform_pos, platform_size);
	CreateBall(engine->GetEntityManager(), platform_pos, platform_size);
	CreateTextInfo(engine->GetEntityManager());

	CreateBricks();
	CreateBorders();
}

void Lvl2Creator::CreateBricks()
{
	int height = 12;
	int pos = 3, hp = 1;
	int R = 1, L = 1;
	
	R = L = height / 2;
	for (int i = pos; i < height; i++)
	{
		for (int j = L; j <= R; j++)
		{
			if (L == R)
				hp = 3;
			else if (j == L || j == R)
				hp = 2;
			else
				hp = 1;

			Vec2 size = Vec2(15, 8);
			CreateBrick(engine->GetEntityManager(), Vec2(8 + i * (size.getX() + 1), 12 + j * (size.getY() + 1)), size, hp);
		}

		if (i < height / 2) {
			R++; L--;
		}
		else {
			R--; L++;
		}
	}

}

void Lvl2Creator::CreateBorders()
{
	//Как и в первом уровне
	CreateBorder(engine->GetEntityManager(), Vec2(WIDTH, 6), Vec2(0, 0));
	CreateBorder(engine->GetEntityManager(), Vec2(6, HEIGHT), Vec2(0, 0)); 
	CreateBorder(engine->GetEntityManager(), Vec2(6, HEIGHT), Vec2(WIDTH - 6, 0)); 
}