#include <iostream>
#include "scene_manager.h"
#include "game_scene.h"
#include "win_scene.h"
#include "lose_scnene.h"
#include "level_interface.h"
#include "lvl_1_creator.h"
#include "lvl_2_creator.h"
#include "Texture.h"
#include <array>
#include "glut.h"

//global parametrs for window - нужны, потому что не знаю, как с glut без них обойтись
int WIDTH;
int HEIGHT;
int PATH;
extern std::array<std::shared_ptr<Texture>, 3> textures;
unsigned char ACTION = 'o';

//Leader game class
class ArcanoidApplication
{
public:
	void Init()
	{
		// Просто добавляем любые уровни, сцены и текстуры
		s_m.Add<GameScene<Lvl1Creator>>("lev1");
		s_m.Add<GameScene<Lvl2Creator>>("lev2");
		s_m.Add<win_scene>("win_scene");
		s_m.Add<lose_scene>("lose_map");
		s_m.SetScene(0);

		textures[DEFAULT_TEX] = std::make_shared<Texture>("brick2.tga");
		textures[TEX_1] = std::make_shared<Texture>("brick3.tga");
		textures[TEX_2] = std::make_shared<Texture>("brick4.tga");
		
	}
	void Draw()
	{
		//Отрисовка и обновление всех объектов
		s_m.OnUpdate();
	}
	void Dispose()
	{
		//Изъятие объектов из памяти, если требуется
		s_m.OnDispose();
	}

private:
	SceneManager s_m{};
};
ArcanoidApplication app;

// Neccessary glut functions
void Drawing()
{
	glClear(GL_COLOR_BUFFER_BIT);

	app.Draw();

	glutSwapBuffers();
}

void Timer(int value)
{
	Drawing();
}

void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, HEIGHT, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	app.Init();
}

void changeSize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void pressKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:  PATH = GLUT_KEY_LEFT;  break;
	case GLUT_KEY_RIGHT: PATH = GLUT_KEY_RIGHT; break;
	default: break;
	}
}

void releaseKey(int key, int x, int y)
{
	PATH = GLUT_KEY_F1;
}

void keyboard(unsigned char key, int x, int y)
{
	// Exit from game
	if (key == 27)
	{
		app.Dispose();
		exit(EXIT_SUCCESS);
	}
	if (key == 'q')
		ACTION = 'q';
}

void keyboardUp(unsigned char key, int x, int y)
{
	ACTION = 'o';
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//======================
	HEIGHT = 250;
	WIDTH = 225;
	//======================
	glutInitWindowPosition(WIDTH, HEIGHT);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Arcanoid 2: redux");

	//Glut main preparations and loop function
	Init();

	glutSpecialFunc(pressKey);
	glutIgnoreKeyRepeat(GLUT_KEY_REPEAT_ON);
	glutSpecialUpFunc(releaseKey);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);

	/*glutReshapeFunc(changeSize);*/
	glutDisplayFunc(Drawing);
	glutIdleFunc(Drawing);
	glutTimerFunc(33, Timer, 0);

	glutMainLoop();
	return EXIT_SUCCESS;
}