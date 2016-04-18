#include "Player.h"

namespace PlayerConstants
{
	const float JUMP_HEIGHT = -0.6f;
	const float WALK_SPEED = 0.4f;
	const float GRAVITY = 0.03f;
	const float GRAVITY_CAP = 0.5f;
	const float AIR_DRAG = 1.2f;
	const float ATTACK_DAMAGE = 50.0f;
	const float KNOCKBACK_AMOUNT = 1.2f;
}

Player::Player() {}

Player::Player(Graphics& graphics, sf::Vector2i spawnPoint) :
	AnimatedGameSprite(graphics, "Spritesheets/Hero.png", 0, 0, 48, 32, spawnPoint.x, spawnPoint.y, 100.0f, 2.0f),
	dx(0.0f), dy(0.0f),
	grounded(false),
	state(IDLE),
	currentHitbox(sf::IntRect())
{
	SetupAnimations();
	SetupHitboxes();
	PlayAnimation("IdleRight");
	facing = RIGHT;
}

Player::~Player()
{}

bool Player::IsGrounded() const { return grounded; }
Direction Player::GetFacing() const { return facing; }
PlayerState Player::GetPlayerState() const { return state; }
const float Player::GetDamageAmount() const { return PlayerConstants::ATTACK_DAMAGE; }
void Player::SetGrounded(bool grounded) { this->grounded = grounded; }
const float Player::GetKnockbackAmount() const { return PlayerConstants::KNOCKBACK_AMOUNT; }

void Player::Update(float elapsedTime)
{
	if (!grounded)
	{
		if (dy <= PlayerConstants::GRAVITY_CAP)
		{
			dy += PlayerConstants::GRAVITY;

			if (dx != 0)
				dx = dx / PlayerConstants::AIR_DRAG;
		}
	}

	position.x += dx * elapsedTime;
	position.y += dy * elapsedTime;
	sprite.setPosition(position);

	AnimatedGameSprite::Update(elapsedTime);

	if (this->GetPlayerState() == ATTACKING)
		currentHitbox = sf::IntRect(hitBoxes[currentAnimation][frameIndex].left + position.x, 
									hitBoxes[currentAnimation][frameIndex].top + position.y, 
									hitBoxes[currentAnimation][frameIndex].left + hitBoxes[currentAnimation][frameIndex].width + position.x,
									hitBoxes[currentAnimation][frameIndex].top + hitBoxes[currentAnimation][frameIndex].height + position.y);
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
	dy = PlayerConstants::JUMP_HEIGHT;
	state = JUMPING_UP;
	grounded = false;
}

void Player::Attack()
{
	dx /= 2.0f;
	state = ATTACKING;
	PlayAnimation(facing == RIGHT ? "AttackRight" : "AttackLeft");
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

const int Player::GetHealth() const { return (int)hp; }

void Player::DepleteHealth(float amount)
{
	hp -= amount;
	if (hp < 0.0f)
		hp = 0.0f;
}

bool Player::CheckAttackHit(const sf::IntRect& enemyBox)
{
	if (currentHitbox.intersects(enemyBox))
		return true;
	else
		return false;
}

void Player::SetupAnimations()
{
	AddAnimation("IdleLeft", 4, 0, 96, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("IdleRight", 4, 0, 0, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("RunLeft", 6, 0, 64, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("RunRight", 6, 0, 32, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("AttackRight", 4, 0, 128, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("AttackLeft", 4, 0, 160, 48, 32, sf::Vector2f(0.0f, 0.0f));
}

void Player::SetupHitboxes()
{
	std::vector<sf::IntRect> hitBoxRight;
	hitBoxRight.push_back(sf::IntRect(0, 0, 0, 0));
	hitBoxRight.push_back(sf::IntRect(0, 0, 0, 0));
	hitBoxRight.push_back(sf::IntRect(17, 10, 30, 22));
	hitBoxRight.push_back(sf::IntRect(0, 0, 0, 0));

	std::vector<sf::IntRect> hitBoxLeft;
	hitBoxLeft.push_back(sf::IntRect(0, 0, 0, 0));
	hitBoxLeft.push_back(sf::IntRect(0, 0, 0, 0));
	hitBoxLeft.push_back(sf::IntRect(0, 10, 30, 22));
	hitBoxLeft.push_back(sf::IntRect(0, 0, 0, 0));

	hitBoxes.insert(std::pair<std::string, std::vector<sf::IntRect> >("AttackRight", hitBoxRight));
	hitBoxes.insert(std::pair<std::string, std::vector<sf::IntRect> >("AttackLeft", hitBoxLeft));
}

void Player::AnimationDone(const std::string& currentAnimation)
{
	if (currentAnimation == "AttackRight" || currentAnimation == "AttackLeft")
	{
		PlayAnimation(facing == RIGHT ? "IdleRight" : "IdleLeft");
		state = IDLE;
	}
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
