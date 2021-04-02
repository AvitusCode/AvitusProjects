#pragma once

//Structure for colors
struct RGB
{
	unsigned char r, g, b;
	RGB(unsigned char a, unsigned char c, unsigned char d) :
		r(a), g(c), b(d) {};
};

enum COLORS
{
	UP_RESIZE_BON,
	DOWN_RESIZE_BON,
	MULTI_BALL_BON,
	LINKING_BON,
	BOUNCE_BON,

	PLATFORM,
	BORDER,
	BALL,
	BRICK_1,
	BRICK_2,
	BRICK_3
};

RGB Pallite(const COLORS &col);

//To perfect work the user needs to create a color buffer in main file