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
	delete enemySpawn1;
	delete enemySpawn2;
}

void Game::GameLoop()
{
	sf::Clock clock;
	sf::Event windowEvent;
	level = Level("Map3Game", sf::Vector2i(100, 100), graphics);
	player = Player(graphics, level.GetSpawnPoint());
	enemySpawn1 = new EnemySpawn(&graphics, level.GetEnemySpawns()[0], clock.getElapsedTime().asMilliseconds());
	enemySpawn2 = new EnemySpawn(&graphics, level.GetEnemySpawns()[1], clock.getElapsedTime().asSeconds() * 3);

	score = 0;
	enemiesKilled = 0;

	font.loadFromFile("Fonts/KenPixel Mini.ttf");

	std::stringstream pHealth, pScore;
	pHealth << "Health: " << player.GetHealth();
	pScore << "Score: " << score;

	playerHealth.setFont(font);
	playerHealth.setString(pHealth.str());
	playerHealth.setCharacterSize(15);
	playerHealth.setPosition(5, 5);

	playerScore.setFont(font);
	playerScore.setString(pScore.str());
	playerScore.setCharacterSize(15);
	playerScore.setPosition(5, 20);
	
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
			player.Attack();

		if (input.wasKeyPressed(sf::Keyboard::Z))
			player.TransformRed();
		if (input.wasKeyPressed(sf::Keyboard::X))
			player.TransformGreen();
		if (input.wasKeyPressed(sf::Keyboard::C))
			player.TransformBlue();

		Update(elapsedTime);
		Draw(graphics);
	}
}

void Game::Update(float elapsedTime)
{
	player.Update(elapsedTime);
	enemySpawn1->UpdateSpawn(elapsedTime);
	enemySpawn2->UpdateSpawn(elapsedTime);

	for (int i = 0; i < enemySpawn1->enemies.size(); i++)
	{
		enemySpawn1->enemies[i]->Move(player.GetBoundingBox());
		enemySpawn1->enemies[i]->Update(elapsedTime);
	}

	for (int i = 0; i < enemySpawn2->enemies.size(); i++)
	{
		enemySpawn2->enemies[i]->Move(player.GetBoundingBox());
		enemySpawn2->enemies[i]->Update(elapsedTime);
	}
	
	level.Update(elapsedTime);

	std::vector<sf::IntRect> others;
	others = level.CheckTileCollisions(player.GetBoundingBox());
	if (others.size() > 0)
		player.HandleTileCollision(others);



	for (int i = 0; i < enemySpawn1->enemies.size(); i++)
	{
		std::vector<sf::IntRect> enemyOthers;
		enemyOthers = level.CheckTileCollisions(enemySpawn1->enemies[i]->GetBoundingBox());
		if (enemyOthers.size() > 0)
			enemySpawn1->enemies[i]->HandleTileCollision(enemyOthers);
	}

	for (int i = 0; i < enemySpawn2->enemies.size(); i++)
	{
		std::vector<sf::IntRect> enemyOthers;
		enemyOthers = level.CheckTileCollisions(enemySpawn2->enemies[i]->GetBoundingBox());
		if (enemyOthers.size() > 0)
			enemySpawn2->enemies[i]->HandleTileCollision(enemyOthers);
	}



	for (int i = 0; i < enemySpawn1->enemies.size(); i++)
	{
		if (enemySpawn1->enemies[i]->CheckPlayerCollision(player.GetBoundingBox()))
		{
			player.DepleteHealth(enemySpawn1->enemies[i]->GetDamageAmount());
		}
	}

	for (int i = 0; i < enemySpawn2->enemies.size(); i++)
	{
		if (enemySpawn2->enemies[i]->CheckPlayerCollision(player.GetBoundingBox()))
		{
			player.DepleteHealth(enemySpawn2->enemies[i]->GetDamageAmount());
		}
	}



	if (player.GetPlayerState() == ATTACKING)
	{
		for (int i = 0; i < enemySpawn1->enemies.size(); i++)
		{
			if (player.CheckAttackHit(enemySpawn1->enemies[i]->GetBoundingBox()))
			{
				if (!enemySpawn1->enemies[i]->IsDamaged())
				{
					if ((enemySpawn1->enemies[i]->GetEnemyType() == EnemyType::RED && player.GetSwordForm() == SwordForm::RED) ||
						(enemySpawn1->enemies[i]->GetEnemyType() == EnemyType::GREEN && player.GetSwordForm() == SwordForm::GREEN) ||
						(enemySpawn1->enemies[i]->GetEnemyType() == EnemyType::BLUE && player.GetSwordForm() == SwordForm::BLUE))
					{
						enemySpawn1->enemies[i]->DepleteHealth(player.GetDamageAmount());
						enemySpawn1->enemies[i]->SetColor(sf::Color(255, 0, 0));
					}
					enemySpawn1->enemies[i]->Knockback(player.GetKnockbackAmount(), player.GetFacing());
					enemySpawn1->enemies[i]->SetDamaged(true);
				}
			}
			else
			{
				enemySpawn1->enemies[i]->SetDamaged(false);
				enemySpawn1->enemies[i]->SetColor(sf::Color(255, 255, 255));
			}

			if (enemySpawn1->enemies[i]->IsDead())
			{
				enemiesKilled++;
				score += 100;
				delete enemySpawn1->enemies[i];
				enemySpawn1->enemies.erase(enemySpawn1->enemies.begin() + i);
			}
		}

		for (int i = 0; i < enemySpawn2->enemies.size(); i++)
		{
			if (player.CheckAttackHit(enemySpawn2->enemies[i]->GetBoundingBox()))
			{
				if (!enemySpawn2->enemies[i]->IsDamaged())
				{
					if ((enemySpawn2->enemies[i]->GetEnemyType() == EnemyType::RED && player.GetSwordForm() == SwordForm::RED) ||
						(enemySpawn2->enemies[i]->GetEnemyType() == EnemyType::GREEN && player.GetSwordForm() == SwordForm::GREEN) ||
						(enemySpawn2->enemies[i]->GetEnemyType() == EnemyType::BLUE && player.GetSwordForm() == SwordForm::BLUE))
					{
						enemySpawn2->enemies[i]->DepleteHealth(player.GetDamageAmount());
						enemySpawn2->enemies[i]->SetColor(sf::Color(255, 0, 0));
					}
					enemySpawn2->enemies[i]->Knockback(player.GetKnockbackAmount(), player.GetFacing());
					enemySpawn2->enemies[i]->SetDamaged(true);
				}
			}
			else
			{
				enemySpawn2->enemies[i]->SetDamaged(false);
				enemySpawn2->enemies[i]->SetColor(sf::Color(255, 255, 255));
			}

			if (enemySpawn2->enemies[i]->IsDead())
			{
				enemiesKilled++;
				score += 100;
				delete enemySpawn2->enemies[i];
				enemySpawn2->enemies.erase(enemySpawn2->enemies.begin() + i);
			}
		}
	}

	std::stringstream pHealth, pScore;
	pHealth << "Health: " << player.GetHealth();
	pScore << "Score: " << score;

	playerHealth.setString(pHealth.str());
	playerScore.setString(pScore.str());
}

void Game::Draw(Graphics& graphics)
{
	graphics.ClearWindow();
	level.Draw(graphics);
	player.Draw(graphics);
	for (int i = 0; i < enemySpawn1->enemies.size(); i++)
		enemySpawn1->enemies[i]->Draw(graphics);
	for (int i = 0; i < enemySpawn2->enemies.size(); i++)
		enemySpawn2->enemies[i]->Draw(graphics);
	graphics.GetRenderWindow().draw(playerHealth);
	graphics.GetRenderWindow().draw(playerScore);
	graphics.Render();
}