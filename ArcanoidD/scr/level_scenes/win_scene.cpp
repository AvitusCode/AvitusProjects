#include "win_scene.h"
#include "scene_manager.h"
#include "glut.h"

extern int HEIGHT;

void win_scene::OnUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT);

	int x = 10, y = HEIGHT / 2;
	std::string text = "YOU HAVE ALREADY\n WON!\n Please key exit.\n";

	glColor3ub(255, 255, 255);
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