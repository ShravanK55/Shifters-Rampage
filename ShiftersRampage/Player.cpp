#include "Player.h"

namespace PlayerConstants
{
	const float WALK_SPEED = 0.2f;
	const float GRAVITY = 0.02f;
	const float GRAVITY_CAP = 0.5f;
}

Player::Player() {}

Player::Player(Graphics& graphics, sf::Vector2i spawnPoint) :
	AnimatedGameSprite(graphics, "Spritesheets/Hero.png", 0, 0, 32, 32, spawnPoint.x, spawnPoint.y, 100.0f, 2.0f),
	dx(0.0f), dy(0.0f),
	grounded(false),
	state(IDLE)
{
	SetupAnimations();
	PlayAnimation("IdleRight");
	facing = RIGHT;
}

Player::~Player()
{}

bool Player::IsGrounded() const { return grounded; }
PlayerState Player::GetPlayerState() const { return state; }
void Player::SetGrounded(bool grounded) { this->grounded = grounded; }

void Player::Update(float elapsedTime)
{
	if (!grounded)
	{
		if (dy <= PlayerConstants::GRAVITY_CAP)
		{
			dy += PlayerConstants::GRAVITY;

			if (dy > 0)
				state = FALLING;
		}
	}

	position.x += dx * elapsedTime;
	position.y += dy * elapsedTime;
	sprite.setPosition(position);
	AnimatedGameSprite::Update(elapsedTime);
}

void Player::Draw(Graphics& graphics)
{
	AnimatedGameSprite::Draw(graphics);
}

void Player::MoveLeft()
{
	dx = -PlayerConstants::WALK_SPEED;
	PlayAnimation("RunLeft");
	facing = LEFT;
	state = RUNNING;
}

void Player::MoveRight()
{
	dx = PlayerConstants::WALK_SPEED;
	PlayAnimation("RunRight");
	facing = RIGHT;
	state = RUNNING;
}

void Player::StopMoving()
{
	dx = 0;
	PlayAnimation(facing == RIGHT ? "IdleRight" : "IdleLeft");
	state = IDLE;
}

void Player::Jump()
{
	dy = -0.4f;
	state = JUMPING_UP;
	grounded = false;
}

void Player::TransformRed()
{
	sprite.setColor(sf::Color(255, 0, 0));
}

void Player::TransformBlue()
{
	sprite.setColor(sf::Color(0, 0, 255));
}

void Player::Revert()
{
	sprite.setColor(sf::Color(255, 255, 255));
}

void Player::SetupAnimations()
{
	//AddAnimation("IdleLeft", 1, 0, 0, 16, 16, sf::Vector2f(0.0f, 0.0f));
	//AddAnimation("IdleRight", 1, 0, 16, 16, 16, sf::Vector2f(0.0f, 0.0f));
	//AddAnimation("RunLeft", 3, 0, 0, 16, 16, sf::Vector2f(0.0f, 0.0f));
	//AddAnimation("RunRight", 3, 0, 16, 16, 16, sf::Vector2f(0.0f, 0.0f));

	AddAnimation("IdleLeft", 4, 0, 96, 32, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("IdleRight", 4, 0, 0, 32, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("RunLeft", 6, 0, 64, 32, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("RunRight", 6, 0, 32, 32, 32, sf::Vector2f(0.0f, 0.0f));
}

void Player::AnimationDone(const std::string& currentAnimation)
{
}

void Player::HandleTileCollision(std::vector<sf::IntRect>& others)
{
	for (int i = 0; i < others.size(); i++)
	{
		Side::Side collisionSide = GetCollisionSide(others[i]);

		if (collisionSide != Side::NONE)
		{
			switch (collisionSide)
			{
			case Side::TOP:
				position.y = others[i].top + others[i].height + 1;
				dy = 0;
				break;

			case Side::BOTTOM:
				position.y = others[i].top - boundingBox.height - 1;
				dy = 0;
				grounded = true;
				break;

			case Side::LEFT:
				position.x = others[i].left + others[i].width + 1;
				break;

			case Side::RIGHT:
				position.x = others[i].left - boundingBox.width - 1;
				break;
			}
		}
	}
}
