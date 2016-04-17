#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Globals.h"
#include "Graphics.h"
#include "Player.h"
#include "Input.h"
#include "Level.h"

class Game
{
public:
	Game();
	~Game();

private:
	Graphics graphics;
	Input input;

	Player player;
	Level level;

	void Update(float elapsedTime);
	void Draw(Graphics& graphics);
	void GameLoop();
};