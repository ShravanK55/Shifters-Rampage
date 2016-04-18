#include "EnemySpawn.h"

namespace EnemySpawnConstants
{
	const float ENEMY_SPAWN_TIME = 5000.0f;
};

EnemySpawn::EnemySpawn()
{
}

EnemySpawn::EnemySpawn(Graphics* graphics, sf::Vector2i spawnPoint) :
	graphics(graphics),
	spawnPosition(spawnPoint),
	timeElapsed(0)
{
	srand(time(NULL));
	enemies.push_back(new Enemy(*graphics, spawnPoint, EnemyType::GREEN));
	enemies.push_back(new Enemy(*graphics, spawnPoint, EnemyType::BLUE));
}

EnemySpawn::~EnemySpawn()
{
	for (int i = 0; i < enemies.size(); i++)
		delete enemies[i];
	enemies.clear();
}

std::vector<Enemy*>& EnemySpawn::GetEnemies() {	return enemies; }

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
