#pragma once
#include "Globals.h"
#include "AnimatedGameSprite.h"


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

	const float GetDamageAmount() const;
	bool IsDead() const;
	int GetHealth() const;
	void SetDamaged(bool damaged);
	bool IsDamaged() const;

	void Move(const sf::IntRect& playerBox);
	void StopMoving();

	bool CheckPlayerCollision(const sf::IntRect& playerRect);

	void DepleteHealth(float amount);

	void Knockback(float amount, Direction attackDirection);

	void SetupAnimations();
	void AnimationDone(const std::string& currentAnimation);

	void HandleTileCollision(std::vector<sf::IntRect>& others);

protected:
	float dx, dy;
	Direction facing;
	EnemyType type;
	bool playerDamaged;
	bool isDamaged;
	int hp;
	bool isDead;

private:

};

