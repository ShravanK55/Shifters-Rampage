#include "Enemy.h"

namespace EnemyConstants
{
	const float MOVEMENT_SPEED = 0.03f;
	const float MAX_SPEED = 0.5f;
	const int MAX_DISTANCE = 10;
	const float FRIGHT_AMOUNT = 5.0f;
	const float ENEMY_DAMAGE = 3.0f;
}

Enemy::Enemy() {}

Enemy::Enemy(Graphics& graphics, sf::Vector2i spawnPoint, EnemyType type) :
	AnimatedGameSprite(graphics, "Spritesheets/ProtoEnemy.png", 0, 0, 48, 32, spawnPoint.x, spawnPoint.y, 100.0f, 1.0f),
	dx(0), dy(0),
	facing(RIGHT),
	type(type),
	playerDamaged(false),
	isDamaged(false),
	hp(100.0f),
	isDead(false)
{
	SetupAnimations();
	switch (type)
	{
	case EnemyType::GREEN:
		PlayAnimation("GreenFlyRight");
		break;

	case EnemyType::RED:
		PlayAnimation("RedFlyRight");
		break;

	case EnemyType::BLUE:
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

const float Enemy::GetDamageAmount() const { return EnemyConstants::ENEMY_DAMAGE; }
bool Enemy::IsDead() const { return isDead; }
int Enemy::GetHealth() const { return (int)hp; }
void Enemy::SetDamaged(bool damaged) { this->isDamaged = damaged; }
bool Enemy::IsDamaged() const {	return isDamaged; }
void Enemy::SetColor(sf::Color& color) { sprite.setColor(color); }
EnemyType Enemy::GetEnemyType() const { return type; }

void Enemy::Move(const sf::IntRect& playerBox)
{
	if (this->position.x < playerBox.left)
	{
		if (dx <= EnemyConstants::MAX_SPEED)
			dx += EnemyConstants::MOVEMENT_SPEED;
	}
	else
	{
		if (dx >= -EnemyConstants::MAX_SPEED)
			dx -= EnemyConstants::MOVEMENT_SPEED;
	}

	if (this->position.y < playerBox.top)
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
	case EnemyType::GREEN:
		PlayAnimation(dx > 0 ? "GreenFlyRight" : "GreenFlyLeft");
		break;

	case EnemyType::RED:
		PlayAnimation(dx > 0 ? "RedFlyRight" : "RedFlyLeft");
		break;

	case EnemyType::BLUE:
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

bool Enemy::CheckPlayerCollision(const sf::IntRect& playerRect)
{
	if (position.x > playerRect.left &&
		position.x < playerRect.left + playerRect.width &&
		position.y > playerRect.top &&
		position.y < playerRect.top + playerRect.height)
	{
		if (!playerDamaged)
		{
			playerDamaged = true;
			return true;
		}

		if (playerDamaged)
			return false;
	}

	else
	{
		playerDamaged = false;
		return false;
	}
}

void Enemy::DepleteHealth(float amount)
{
	hp -= amount;
	if (hp <= 0)
	{
		isDead = true;
		hp = 0;
	}
}

void Enemy::Knockback(float amount, Direction attackDirection)
{
	switch (attackDirection)
	{
	case LEFT:
		if (dx < 0)
			dx = -amount;
		else
			dx -= amount;
		break;

	case RIGHT:
		if (dx > 0)
			dx = amount;
		else
			dx += amount;
		break;
	}
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
