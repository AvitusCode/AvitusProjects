#include "color.h"


RGB Pallite(const COLORS &col)
{
	switch (col)
	{
	case UP_RESIZE_BON: return RGB(255, 20, 147);
	case DOWN_RESIZE_BON: return RGB(139, 0, 9);
	case MULTI_BALL_BON: return RGB(0, 255, 127);
	case LINKING_BON: return RGB(224, 255, 255);
	case BOUNCE_BON: return RGB(106, 90, 205);
	case PLATFORM: return RGB(255, 255, 0);
	case BORDER: return RGB(0, 0, 255);
	case BALL: return RGB(255, 0, 0);
	case BRICK_1: return RGB(255, 20, 255);
	case BRICK_2: return RGB(128, 128, 0);
	case BRICK_3: return RGB(75, 0, 30);
		
	default:
		return RGB(0, 0, 0);
	}
}