#include "lose_scnene.h"
#include "scene_manager.h"
#include <string>

#include "glut.h"

extern int HEIGHT;

void lose_scene::OnUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT);

	int x = 10, y = HEIGHT / 2;
	std::string text = "GAME OVER, DUDE!\n Please key exit.\n";

	for (size_t i = 0; i < text.size(); i++)
	{
		glRasterPos2f(x, y);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		x += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, text[i]);
		if (text[i] == '\n')
		{
			x = 10;
			y += 20;
		}
	}

}