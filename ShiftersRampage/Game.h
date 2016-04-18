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

	Player player;
	std::vector<Enemy*> enemies;
	Enemy* enemy;
	Enemy* enemy2;
	EnemySpawn enemySpawn;
	Level level;

	int enemiesKilled;
	int score;

	void Update(float elapsedTime);
	void Draw(Graphics& graphics);
	void GameLoop();
};