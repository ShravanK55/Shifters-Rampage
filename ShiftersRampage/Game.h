#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Globals.h"
#include "Graphics.h"
#include "Player.h"
#include "Input.h"
#include "Level.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Enemy.h"
#include "EnemySpawn.h"
#include "GameOverMenu.h"

class Game
{
public:
	Game();
	~Game();

private:
	Graphics graphics;
	Input input;

	MainMenu mainMenu;
	PauseMenu pauseMenu;
	GameOverMenu gameOverMenu;

	Player player;
	EnemySpawn* enemySpawn1;
	EnemySpawn* enemySpawn2;
	Level level;

	sf::Font font;
	sf::Text playerHealth;
	sf::Text playerScore;

	int enemiesKilled;
	int score;

	void Reset();

	void Update(float elapsedTime);
	void Draw(Graphics& graphics);
	void GameLoop();
};
