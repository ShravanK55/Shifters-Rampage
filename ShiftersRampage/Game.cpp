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
Game::~Game()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
	}
	enemies.clear();
}

void Game::GameLoop()
{
	level = Level("Map3Game", sf::Vector2i(100, 100), graphics);
	player = Player(graphics, level.GetSpawnPoint());
	enemy = new Enemy(graphics, sf::Vector2i(300, 500));
	enemy2 = new Enemy(graphics, sf::Vector2i(600, 500));
	enemies.push_back(enemy);
	enemies.push_back(enemy2);
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

		if (input.wasKeyPressed(sf::Keyboard::T))
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

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Move(player.GetBoundingBox());
		enemies[i]->Update(elapsedTime);
	}
	
	level.Update(elapsedTime);

	std::vector<sf::IntRect> others;
	others = level.CheckTileCollisions(player.GetBoundingBox());
	if (others.size() > 0)
		player.HandleTileCollision(others);

	for (int i = 0; i < enemies.size(); i++)
	{
		std::vector<sf::IntRect> enemyOthers;
		enemyOthers = level.CheckTileCollisions(enemies[i]->GetBoundingBox());
		if (enemyOthers.size() > 0)
			enemies[i]->HandleTileCollision(enemyOthers);
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->CheckPlayerCollision(player.GetBoundingBox()))
		{
			player.DepleteHealth(enemies[i]->GetDamageAmount());
			std::cout << "Player health: " << player.GetHealth() << std::endl;
		}
	}

	if (player.GetPlayerState() == ATTACKING)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			if (player.CheckAttackHit(enemies[i]->GetBoundingBox()))
			{
				if (!enemies[i]->IsDamaged())
				{
					enemies[i]->DepleteHealth(player.GetDamageAmount());
					enemies[i]->Knockback(player.GetKnockbackAmount(), player.GetFacing());
					enemies[i]->SetDamaged(true);
					std::cout << "Enemy health: " << enemies[i]->GetHealth() << std::endl;
				}
			}
			else
				enemies[i]->SetDamaged(false);

			if (enemies[i]->IsDead())
			{
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
			}
		}
	}

	
}

void Game::Draw(Graphics& graphics)
{
	graphics.ClearWindow();
	level.Draw(graphics);
	player.Draw(graphics);
	for (int i = 0; i < enemies.size(); i++)
		enemies[i]->Draw(graphics);
	graphics.Render();
}