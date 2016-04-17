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
	FALLING,
	ATTACKING
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

	void Attack();

	void TransformRed();
	void TransformBlue();
	void Revert();

	const int GetHealth() const;
	void DepleteHealth(float amount);

	void SetupAnimations();
	void SetupHitboxes();
	void AnimationDone(const std::string& currentAnimation);

	void HandleTileCollision(std::vector<sf::IntRect>& others);

private:
	float dx, dy;
	Direction facing;
	bool grounded;
	PlayerState state;
	float hp = 100.0f;

	std::map<std::string, std::vector<sf::IntRect> > hitBoxes;
};
