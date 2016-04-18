#pragma once
#include "Enemy.h"

class EnemySpawn
{
public:
	EnemySpawn();
	EnemySpawn(Graphics* graphics, sf::Vector2i spawnPoint);
	~EnemySpawn();

	std::vector<Enemy*>& GetEnemies();

	void UpdateSpawn(float elapsedTime);

private:
	std::vector<Enemy*> enemies;
	float timeElapsed;
	sf::Vector2i spawnPosition;
	Graphics* graphics;
};

