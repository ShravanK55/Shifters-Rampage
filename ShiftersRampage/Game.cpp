#include "Game.h"


Game::Game() { GameLoop(); }
Game::~Game() {}

void Game::GameLoop()
{
	level = Level("Map2Game", sf::Vector2i(100, 100), graphics);
	player = Player(graphics, level.GetSpawnPoint());
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
		if (input.isKeyHeld(sf::Keyboard::A) && player.GetPlayerState() != ATTACKING)
			player.MoveLeft();
		else if (input.isKeyHeld(sf::Keyboard::D) && player.GetPlayerState() != ATTACKING)
			player.MoveRight();
		else if (!input.isKeyHeld(sf::Keyboard::A) && !input.isKeyHeld(sf::Keyboard::D) && player.IsGrounded() && player.GetPlayerState() != ATTACKING)
			player.StopMoving();

		if (input.wasKeyPressed(sf::Keyboard::Space) && player.IsGrounded())
			player.Jump();

		if (input.wasKeyPressed(sf::Keyboard::T) && player.IsGrounded())
		{
			player.Attack();
		}

		if (input.wasKeyPressed(sf::Keyboard::Z))
			player.TransformRed();
		if (input.wasKeyPressed(sf::Keyboard::X))
			player.TransformBlue();
		if (input.wasKeyPressed(sf::Keyboard::C))
			player.Revert();

		Update(elapsedTime);
		Draw(graphics);
	}
}

void Game::Update(float elapsedTime)
{
	player.Update(elapsedTime);
	level.Update(elapsedTime);

	std::vector<sf::IntRect> others;
	others = level.CheckTileCollisions(player.GetBoundingBox());

	if (others.size() > 0)
		player.HandleTileCollision(others);
}

void Game::Draw(Graphics& graphics)
{
	graphics.ClearWindow();
	level.Draw(graphics);
	player.Draw(graphics);
	graphics.Render();
}