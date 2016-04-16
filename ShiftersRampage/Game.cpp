#include "Game.h"


Game::Game() { GameLoop(); }
Game::~Game() {}

void Game::GameLoop()
{
	player = Player(graphics, sf::Vector2f(50.0f, 50.0f));
	sf::Event windowEvent;
	sf::Clock clock;

	int previousFrameTime = clock.getElapsedTime().asMilliseconds();
	int currentFrameTime, elapsedTime;

	while (true)
	{
		currentFrameTime = clock.getElapsedTime().asMilliseconds();
		elapsedTime = currentFrameTime - previousFrameTime;
		previousFrameTime = currentFrameTime;

		input.BeginNewFrame();

		if (graphics.GetRenderWindow().pollEvent(windowEvent))
		{
			switch (windowEvent.type)
			{
			case sf::Event::Closed:
				return;

			case sf::Event::KeyPressed:
				input.KeyDownEvent(windowEvent);
				break;

			case sf::Event::KeyReleased:
				input.KeyUpEvent(windowEvent);
				break;

			default:
				break;
			}
		}

		if (input.wasKeyPressed(sf::Keyboard::Escape))
			return;
		if (input.isKeyHeld(sf::Keyboard::A))
			player.MoveLeft();
		else if (input.isKeyHeld(sf::Keyboard::D))
			player.MoveRight();
		else if (!(input.isKeyHeld(sf::Keyboard::A)) && !(input.isKeyHeld(sf::Keyboard::D)))
			player.StopMoving();

		Update(elapsedTime);
		Draw(graphics);
	}
}

void Game::Update(float elapsedTime)
{
	player.Update(elapsedTime);
}

void Game::Draw(Graphics& graphics)
{
	graphics.ClearWindow();
	player.Draw(graphics);
	graphics.Render();
}