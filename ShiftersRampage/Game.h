#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Globals.h"
#include "Graphics.h"
#include "GameSprite.h"
#include "Input.h"

class Game
{
public:
	Game();
	~Game();

private:
	Graphics graphics;
	Input input;

	GameSprite player;

	void Update(float elapsedTime);
	void Draw(Graphics& graphics);
	void GameLoop();
};