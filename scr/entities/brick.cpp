#include "brick_component.h"
#include "rect_collider_component.h"
#include "rectangle_render_component.h"
#include "transform_component.h"
#include "entity_manager.h"
#include "texture_comp.h"
#include "Texture.h"
#include "vec2.h"
#include "color.h"


void CreateBrick(EntityManager *entity_manager, const Vec2 &pos, const Vec2 &size, int hp) 
{
  auto brick = entity_manager->CreateEntity("brick");

  auto col = [](int hep) {
	  switch (hep)
	  {
	  case 1:
		  return Pallite(BRICK_1);
	  case 2:
		  return Pallite(BRICK_2);
	  case 3:
		  return Pallite(BRICK_3);
	  default:
		  return Pallite(BRICK_1);
	  }
  };

  brick->Add<TransformComponent>(pos);
  brick->Add<RectangleRenderComponent>(size, col(hp));
  brick->Add<RectColliderComponent>(size);
  brick->Add<BrickComponent>(hp);
  brick->Add<TextureComp>((getTextureByHp(hp)));

  //Experimental
  /*brick->Add<MusicComponent>("brick.wav");*/
}