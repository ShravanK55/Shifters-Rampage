#pragma once
#include "AnimatedGameSprite.h"

enum Direction
{
	LEFT,
	RIGHT
};

enum PlayerState
{
	IDLE,
	RUNNING,
	JUMPING_UP,
	FALLING
};

class Player : public AnimatedGameSprite
{
public:
	Player();
	Player(Graphics& graphics, sf::Vector2i spawnPoint);
	~Player();

	bool IsGrounded() const;
	PlayerState GetPlayerState() const;
	void SetGrounded(bool grounded);

	void Update(float elapsedTime);
	void Draw(Graphics& graphics);

	void MoveLeft();
	void MoveRight();
	void StopMoving();

	void Jump();

	void TransformRed();
	void TransformBlue();
	void Revert();

	void SetupAnimations();
	void AnimationDone(const std::string& currentAnimation);

	void HandleTileCollision(std::vector<sf::IntRect>& others);

private:
	float dx, dy;
	Direction facing;
	bool grounded;
	PlayerState state;
};
