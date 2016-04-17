#pragma once
#include "AnimatedGameSprite.h"
#include "Player.h"

enum EnemyType
{
	GREEN,
	RED,
	BLUE
};

class Enemy : public AnimatedGameSprite
{
public:
	Enemy();
	Enemy(Graphics& graphics, sf::Vector2i spawnPoint);
	~Enemy();

	void Update(float elapsedTime);
	void Draw(Graphics& graphics);

	void Move(Player& player);
	void StopMoving();

	void CheckPlayerCollision(Player& player);
	void DamagePlayer(Player& player);

	void SetupAnimations();
	void AnimationDone(const std::string& currentAnimation);

	void HandleTileCollision(std::vector<sf::IntRect>& others);

protected:
	float dx, dy;
	Direction facing;
	EnemyType type;
	bool playerDamaged;
	int hp;

private:

};

