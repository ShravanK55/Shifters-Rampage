#include "Player.h"


Player::Player() {}

Player::Player(Graphics& graphics, sf::Vector2f spawnPoint) :
	AnimatedGameSprite(graphics, "Spritesheets/MyChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100.0f, 2.0f),
	dx(0.0f), dy(0.0f),
	walkSpeed(0.2f)
{
	SetupAnimations();
	PlayAnimation("IdleRight");
	facing = RIGHT;
}

Player::~Player()
{
}

void Player::Update(float elapsedTime)
{
	position.x += dx * elapsedTime;
	sprite.setPosition(position);
	AnimatedGameSprite::Update(elapsedTime);
}

void Player::Draw(Graphics& graphics)
{
	AnimatedGameSprite::Draw(graphics);
}

void Player::MoveLeft()
{
	dx = -walkSpeed;
	PlayAnimation("RunLeft");
	facing = LEFT;
}

void Player::MoveRight()
{
	dx = walkSpeed;
	PlayAnimation("RunRight");
	facing = RIGHT;
}

void Player::StopMoving()
{
	dx = 0;
	PlayAnimation(facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::SetupAnimations()
{
	AddAnimation("IdleLeft", 1, 0, 0, 16, 16, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("IdleRight", 1, 0, 16, 16, 16, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("RunLeft", 3, 0, 0, 16, 16, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("RunRight", 3, 0, 16, 16, 16, sf::Vector2f(0.0f, 0.0f));
}

void Player::AnimationDone(const std::string& currentAnimation)
{
}