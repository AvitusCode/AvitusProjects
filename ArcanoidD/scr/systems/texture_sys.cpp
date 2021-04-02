#include "entity.h"
#include "texture_comp.h"
#include "texture_sys.h"
#include "transform_component.h"
#include "rectangle_render_component.h"
#include "circle_render_component.h"

#include "glut.h"
#include <memory>

void TextureSys::Update(Entity * entity)
{
	auto tex = entity->Get<TextureComp>();
	auto tr = entity->Get<TransformComponent>();

	if (tex->getT()->getId() == 0)
		return;
	char what = entity->Contains<RectangleRenderComponent>() == true ? 'r' : 'c';

	if (what == 'r')
	{
		auto rect = entity->Get<RectangleRenderComponent>();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex->getT()->getId());
		glPushMatrix();
		glBegin(GL_POLYGON);

		glTexCoord2i(0, 0); glVertex2i(tr->position.getX(), tr->position.getY());
		glTexCoord2i(1, 0); glVertex2i(tr->position.getX() + rect->size.getX(), tr->position.getY());
		glTexCoord2i(1, 1); glVertex2i(tr->position.getX() + rect->size.getX(), tr->position.getY() + rect->size.getY());
		glTexCoord2i(0, 1); glVertex2i(tr->position.getX(), tr->position.getY() + rect->size.getY());

		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		//Если понадобится натягивать текстуру на шаровые объекты
		auto circ = entity->Get<CircleRenderComponent>();
		return;
	}

}

bool TextureSys::Filter(Entity *entity) const
{
	return entity->Contains<TransformComponent>() && entity->Contains<TextureComp>();
}