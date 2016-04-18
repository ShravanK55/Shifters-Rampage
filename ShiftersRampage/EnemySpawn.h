#pragma once
#include "Enemy.h"

class EnemySpawn
{
public:
	std::vector<Enemy*> enemies;

	EnemySpawn();
	EnemySpawn(Graphics* graphics, sf::Vector2i spawnPoint, int randomSeed);
	~EnemySpawn();

	std::vector<Enemy*>& GetEnemies();

	void UpdateSpawn(float elapsedTime);

private:
	float timeElapsed;
	sf::Vector2i spawnPosition;
	Graphics* graphics;
};

