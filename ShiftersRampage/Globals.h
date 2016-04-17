#pragma once

namespace Globals
{
	const unsigned int SCREEN_WIDTH = 1024;
	const unsigned int SCREEN_HEIGHT = 768;
	const unsigned int FPS = 60;
}

namespace Side
{
	enum Side
	{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE
	};

	inline Side GetOppositeSide(Side side)
	{
		return side == TOP ? BOTTOM :
			   side == BOTTOM ? TOP :
			   side == LEFT ? RIGHT :
			   side == RIGHT ? LEFT :
			   NONE;
	}
}