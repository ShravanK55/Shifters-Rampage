#include "Game.h"


Game::Game()
{
	MainMenuAction result = mainMenu.DisplayMenu(graphics);
	
	switch (result)
	{
	case MainMenuAction::PLAY:
		GameLoop();
		break;

	case MainMenuAction::EXIT:
		return;

	case MainMenuAction::NONE:
		break;
	}
}
Game::~Game() {}

void Game::GameLoop()
{
	level = Level("Map3Game", sf::Vector2i(100, 100), graphics);
	player = Player(graphics, level.GetSpawnPoint());
	enemy = Enemy(graphics, sf::Vector2i(300, 500));
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
		{
			PauseMenuAction result = pauseMenu.DisplayMenu(graphics);

			switch (result)
			{
			case PauseMenuAction::RESUME:
				break;

			case PauseMenuAction::QUIT:
				return;

			case PauseMenuAction::NONE:
				break;
			}
		}

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
	enemy.Move(player);
	enemy.Update(elapsedTime);
	level.Update(elapsedTime);

	std::vector<sf::IntRect> others;
	std::vector<sf::IntRect> enemyOthers;;
	others = level.CheckTileCollisions(player.GetBoundingBox());
	enemyOthers = level.CheckTileCollisions(enemy.GetBoundingBox());

	if (others.size() > 0)
		player.HandleTileCollision(others);
	if (enemyOthers.size() > 0)
		enemy.HandleTileCollision(enemyOthers);

	enemy.CheckPlayerCollision(player);
	std::cout << "Player health: " << player.GetHealth() << std::endl;
}

void Game::Draw(Graphics& graphics)
{
	graphics.ClearWindow();
	level.Draw(graphics);
	player.Draw(graphics);
	enemy.Draw(graphics);
	graphics.Render();
}