#pragma once
#include "AnimatedGameSprite.h"

enum Direction
{
	LEFT,
	RIGHT
};

class Player : public AnimatedGameSprite
{
public:
	Player();
	Player(Graphics& graphics, sf::Vector2f spawnPoint);
	~Player();

	void Update(float elapsedTime);
	void Draw(Graphics& graphics);

	void MoveLeft();
	void MoveRight();
	void StopMoving();

	void SetupAnimations();
	void AnimationDone(const std::string& currentAnimation);

private:
	float dx, dy;
	Direction facing;
	float walkSpeed;
};
