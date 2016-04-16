#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Globals.h"
#include "Graphics.h"

class Game
{
public:
	Game();
	~Game();

private:
	void Update(float elapsedTime);
	void Draw(Graphics& graphics);
	void GameLoop();
};