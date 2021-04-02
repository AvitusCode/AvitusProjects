#include "lvl_2_creator.h"

#include "game_scene.h"
#include "ball_control_system.h"
#include "bricks_system.h"
#include "circle_render_system.h"
#include "collision_system.h"
#include "movement_system.h"
#include "multi_ball_bonus_system.h"
#include "physics_system.h"
#include "player_control_system.h"
#include "rectangle_render_system.h"
#include "resize_bonus_system.h"
#include "shredder_system.h"
#include "line_system.h"
#include "engine.h"
#include "scene.h"
#include "Bounce_Stick_Sys.h"
#include "texture_sys.h"
#include "textSys.h"

void Lvl2Creator::InitSystems()
{
	engine->GetSystemManager()
		->AddSystem<CollisionSystem>()
		->AddSystem<BallControlSystem>(scene_manager)
		->AddSystem<PhysX>()
		->AddSystem<MovementSystem>()
		->AddSystem<PlayerControlSystem>()
		->AddSystem<ShredderSystem>()
		->AddSystem<MultiBallBonusSystem>()
		->AddSystem<BounceStickSys>()
		->AddSystem<ResizeBonusSystem>()
		->AddSystem<BricksSystem>(scene_manager)
		->AddSystem<CircleRenderSystem>()
		->AddSystem<RectangleRenderSystem>()
		->AddSystem<TextureSys>()
		->AddSystem<textSystem>();
}