#include "EnemySpawn.h"

namespace EnemySpawnConstants
{
	const float ENEMY_SPAWN_TIME = 6500.0f;
};

EnemySpawn::EnemySpawn()
{
}

EnemySpawn::EnemySpawn(Graphics* graphics, sf::Vector2i spawnPoint, int randomSeed) :
	graphics(graphics),
	spawnPosition(spawnPoint),
	timeElapsed(0.0f)
{
	srand(randomSeed);
	int randNum = rand() % 3;
	Enemy* enemy;

	if (randNum == 0)
		enemy = new Enemy(*graphics, spawnPosition, EnemyType::RED);
	else if (randNum == 1)
		enemy = new Enemy(*graphics, spawnPosition, EnemyType::GREEN);
	else if (randNum == 2)
		enemy = new Enemy(*graphics, spawnPosition, EnemyType::BLUE);

	enemies.push_back(enemy);
}

EnemySpawn::~EnemySpawn()
{
	for (int i = 0; i < enemies.size(); i++)
		delete enemies[i];
	enemies.clear();
}

void EnemySpawn::UpdateSpawn(float elapsedTime)
{
	timeElapsed += elapsedTime;

	if (timeElapsed > EnemySpawnConstants::ENEMY_SPAWN_TIME)
	{
		timeElapsed = 0;
		int randNum = rand() % 3;

		Enemy* enemy;
		if (randNum == 0)
			enemy = new Enemy(*graphics, spawnPosition, EnemyType::RED);
		else if (randNum == 1)
			enemy = new Enemy(*graphics, spawnPosition, EnemyType::GREEN);
		else if (randNum == 2)
			enemy = new Enemy(*graphics, spawnPosition, EnemyType::BLUE);

		enemies.push_back(enemy);
	}
}
