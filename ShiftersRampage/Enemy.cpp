#include "Enemy.h"

namespace EnemyConstants
{
	const float MOVEMENT_SPEED = 0.03f;
	const float MAX_SPEED = 0.5f;
	const int MAX_DISTANCE = 10;
	const float FRIGHT_AMOUNT = 5.0f;
	const float ENEMY_DAMAGE = 10.0f;
}

Enemy::Enemy() {}

Enemy::Enemy(Graphics& graphics, sf::Vector2i spawnPoint) :
	AnimatedGameSprite(graphics, "Spritesheets/ProtoEnemy.png", 0, 0, 48, 32, spawnPoint.x, spawnPoint.y, 100.0f, 1.0f),
	dx(0), dy(0),
	facing(RIGHT),
	type(RED),
	playerDamaged(false)
{
	SetupAnimations();
	switch (type)
	{
	case GREEN:
		PlayAnimation("GreenFlyRight");
		break;

	case RED:
		PlayAnimation("RedFlyRight");
		break;

	case BLUE:
		PlayAnimation("BlueFlyRight");
		break;
	}
	facing = RIGHT;
}

Enemy::~Enemy() {}

void Enemy::Update(float elapsedTime)
{
	position.x += dx * elapsedTime;
	position.y += dy * elapsedTime;
	sprite.setPosition(position);
	AnimatedGameSprite::Update(elapsedTime);
}

void Enemy::Draw(Graphics& graphics)
{
	AnimatedGameSprite::Draw(graphics);
}

void Enemy::Move(Player& player)
{
	if (this->position.x < player.GetBoundingBox().left)
	{
		if (dx <= EnemyConstants::MAX_SPEED)
			dx += EnemyConstants::MOVEMENT_SPEED;
	}
	else
	{
		if (dx >= -EnemyConstants::MAX_SPEED)
			dx -= EnemyConstants::MOVEMENT_SPEED;
	}

	if (this->position.y < player.GetBoundingBox().top)
	{
		if (dy <= EnemyConstants::MAX_SPEED)
			dy += EnemyConstants::MOVEMENT_SPEED;
	}
	else
	{
		if (dy >= -EnemyConstants::MAX_SPEED)
			dy -= EnemyConstants::MOVEMENT_SPEED;
	}

	switch (type)
	{
	case GREEN:
		PlayAnimation(dx > 0 ? "GreenFlyRight" : "GreenFlyLeft");
		break;

	case RED:
		PlayAnimation(dx > 0 ? "RedFlyRight" : "RedFlyLeft");
		break;

	case BLUE:
		PlayAnimation(dx > 0 ? "BlueFlyRight" : "BlueFlyLeft");
		break;
	}
	facing = dx > 0 ? RIGHT : LEFT;
}

void Enemy::StopMoving()
{
	dx = 0;
	dy = 0;
}

void Enemy::CheckPlayerCollision(Player& player)
{
	if (position.x > player.GetBoundingBox().left &&
		position.x < player.GetBoundingBox().left + player.GetBoundingBox().width &&
		position.y > player.GetBoundingBox().top &&
		position.y < player.GetBoundingBox().top + player.GetBoundingBox().height)
	{
		if (!playerDamaged)
		{
			DamagePlayer(player);
			playerDamaged = true;
		}
	}

	else
		playerDamaged = false;

}

void Enemy::DamagePlayer(Player& player)
{
	player.DepleteHealth(EnemyConstants::ENEMY_DAMAGE);
}

void Enemy::SetupAnimations()
{
	AddAnimation("GreenFlyLeft", 4, 0, 0, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("GreenFlyRight", 4, 0, 32, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("RedFlyLeft", 4, 0, 64, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("RedFlyRight", 4, 0, 96, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("BlueFlyLeft", 4, 0, 128, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("BlueFlyRight", 4, 0, 160, 48, 32, sf::Vector2f(0.0f, 0.0f));
}

void Enemy::AnimationDone(const std::string& currentAnimation)
{
}

void Enemy::HandleTileCollision(std::vector<sf::IntRect>& others)
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
				dy = -dy;
				break;

			case Side::BOTTOM:
				position.y = others[i].top - boundingBox.height - 1;
				dy = -dy;
				break;

			case Side::LEFT:
				position.x = others[i].left + others[i].width + 1;
				dx = -dx;
				break;

			case Side::RIGHT:
				position.x = others[i].left - boundingBox.width - 1;
				dx = -dx;
				break;
			}
		}
	}
}
