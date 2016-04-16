#include "Game.h"


Game::Game() { GameLoop(); }
Game::~Game() {}


void Game::GameLoop()
{
	Graphics graphics;
	sf::Event windowEvent;
	sf::Clock clock;

	int previousFrameTime = clock.getElapsedTime().asMilliseconds();
	int currentFrameTime, elapsedTime;

	while (true)
	{
		currentFrameTime = clock.getElapsedTime().asMilliseconds();
		elapsedTime = currentFrameTime - previousFrameTime;
		previousFrameTime = currentFrameTime;

		if (graphics.GetRenderWindow().pollEvent(windowEvent))
		{
			switch (windowEvent.type)
			{
			case sf::Event::Closed:
				return;
			}
		}

		Update(elapsedTime);
		Draw(graphics);
	}
}

void Game::Update(float elapsedTime)
{
}

void Game::Draw(Graphics& graphics)
{
	graphics.ClearWindow();
	graphics.Render();
}