#include "text_informer.h"
#include <algorithm>
#include "glut.h"


void player_info::Log(std::string &str)
{
	if (logger.size() < max_size)
		logger.push_front(std::move(str));
	else
	{
		logger.pop_back();
		logger.push_front(std::move(str));
	}
}

void player_info::LogCount(int some)
{
	count_info += some;
}

void player_info::erase(const std::string &str)
{
	
	auto iter = std::remove_if(logger.begin(), logger.end(), [str](const std::string& text) { return str == text; });
	logger.erase(iter);
}

void player_info::clear() {
	logger.clear();
}

void player_info::print_on_dislocation(const Vec2 &pos, int shift, int new_str)
{
	int line = 0;
	double x = pos.getX(), y = pos.getY();
	double start = x;

	glColor3ub(255, 255, 255);
	std::string tex = "INFO: Player score  " + std::to_string(count_info);
	for (size_t i = 0; i < tex.size(); i++)
	{
		glRasterPos2f(x, y);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, tex[i]);
		x += glutBitmapWidth(GLUT_BITMAP_HELVETICA_10, tex[i]);
		
	}
	x = start;
	y += 10;

	for (const std::string &text : logger)
		for (size_t i = 0; i < text.size(); i++)
		{
			glRasterPos2f(x, y);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]);
			x += glutBitmapWidth(GLUT_BITMAP_HELVETICA_10, text[i]) + shift;
			line++;
			if (line >= new_str)
			{
				x = start;
				y += 10;
				line = 0;
			}
		}
}