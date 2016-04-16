#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Globals.h"
#include "Graphics.h"
#include "AnimatedGameSprite.h"
#include "Input.h"

class Game
{
public:
	Game();
	~Game();

private:
	Graphics graphics;
	Input input;

	AnimatedGameSprite player;

	void Update(float elapsedTime);
	void Draw(Graphics& graphics);
	void GameLoop();
};