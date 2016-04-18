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
	currentHitbox(sf::IntRect()),
	form(SwordForm::BLUE)
{
	SetupAnimations();
	SetupHitboxes();

	switch (form)
	{
	case SwordForm::RED:
		PlayAnimation("RedIdleRight");
		facing = RIGHT;
		break;

	case SwordForm::GREEN:
		PlayAnimation("GreenIdleRight");
		facing = RIGHT;
		break;

	case SwordForm::BLUE:
		PlayAnimation("BlueIdleRight");
		facing = RIGHT;
		break;
	}
}

Player::~Player()
{}

bool Player::IsGrounded() const { return grounded; }
Direction Player::GetFacing() const { return facing; }
PlayerState Player::GetPlayerState() const { return state; }
const float Player::GetDamageAmount() const { return PlayerConstants::ATTACK_DAMAGE; }
void Player::SetGrounded(bool grounded) { this->grounded = grounded; }
const float Player::GetKnockbackAmount() const { return PlayerConstants::KNOCKBACK_AMOUNT; }
SwordForm Player::GetSwordForm() const { return form; }

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

	switch (form)
	{
	case SwordForm::RED:
		PlayAnimation("RedRunLeft");
		break;

	case SwordForm::GREEN:
		PlayAnimation("GreenRunLeft");
		break;

	case SwordForm::BLUE:
		PlayAnimation("BlueRunLeft");
		break;
	}
	
	facing = LEFT;
	state = RUNNING;
}

void Player::MoveRight()
{
	dx = PlayerConstants::WALK_SPEED;

	switch (form)
	{
	case SwordForm::RED:
		PlayAnimation("RedRunRight");
		break;

	case SwordForm::GREEN:
		PlayAnimation("GreenRunRight");
		break;

	case SwordForm::BLUE:
		PlayAnimation("BlueRunRight");
		break;
	}

	
	facing = RIGHT;
	state = RUNNING;
}

void Player::StopMoving()
{
	dx = 0;
	switch (form)
	{
	case SwordForm::RED:
		PlayAnimation(facing == RIGHT ? "RedIdleRight" : "RedIdleLeft");
		break;

	case SwordForm::GREEN:
		PlayAnimation(facing == RIGHT ? "GreenIdleRight" : "GreenIdleLeft");
		break;

	case SwordForm::BLUE:
		PlayAnimation(facing == RIGHT ? "BlueIdleRight" : "BlueIdleLeft");
		break;
	}
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
	switch (form)
	{
	case SwordForm::RED:
		PlayAnimation(facing == RIGHT ? "RedAttackRight" : "RedAttackLeft");
		break;

	case SwordForm::GREEN:
		PlayAnimation(facing == RIGHT ? "GreenAttackRight" : "GreenAttackLeft");
		break;

	case SwordForm::BLUE:
		PlayAnimation(facing == RIGHT ? "BlueAttackRight" : "BlueAttackLeft");
		break;
	}
}

void Player::TransformRed()
{
	if (form != SwordForm::RED)
	{
		form = SwordForm::RED;
		state = IDLE;
		PlayAnimation(facing == RIGHT ? "RedIdleRight" : "RedIdleLeft");
	}
}

void Player::TransformGreen()
{
	if (form != SwordForm::GREEN)
	{
		form = SwordForm::GREEN;
		state = IDLE;
		PlayAnimation(facing == RIGHT ? "GreenIdleRight" : "GreenIdleLeft");
	}
}

void Player::TransformBlue()
{
	if (form != SwordForm::BLUE)
	{
		form = SwordForm::BLUE;
		state = IDLE;
		PlayAnimation(facing == RIGHT ? "BlueIdleRight" : "BlueIdleLeft");
	}
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
	AddAnimation("BlueIdleRight", 4, 0, 0, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("BlueRunRight", 6, 0, 32, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("BlueRunLeft", 6, 0, 64, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("BlueIdleLeft", 4, 0, 96, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("BlueAttackRight", 4, 0, 128, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("BlueAttackLeft", 4, 0, 160, 48, 32, sf::Vector2f(0.0f, 0.0f));

	AddAnimation("RedIdleRight", 4, 0, 192, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("RedRunRight", 6, 0, 224, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("RedRunLeft", 6, 0, 256, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("RedIdleLeft", 4, 0, 288, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("RedAttackRight", 4, 0, 320, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("RedAttackLeft", 4, 0, 352, 48, 32, sf::Vector2f(0.0f, 0.0f));

	AddAnimation("GreenIdleRight", 4, 0, 384, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("GreenRunRight", 6, 0, 416, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("GreenRunLeft", 6, 0, 448, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("GreenIdleLeft", 4, 0, 480, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("GreenAttackRight", 4, 0, 512, 48, 32, sf::Vector2f(0.0f, 0.0f));
	AddAnimation("GreenAttackLeft", 4, 0, 544, 48, 32, sf::Vector2f(0.0f, 0.0f));
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

	hitBoxes.insert(std::pair<std::string, std::vector<sf::IntRect> >("BlueAttackRight", hitBoxRight));
	hitBoxes.insert(std::pair<std::string, std::vector<sf::IntRect> >("BlueAttackLeft", hitBoxLeft));
	hitBoxes.insert(std::pair<std::string, std::vector<sf::IntRect> >("RedAttackRight", hitBoxRight));
	hitBoxes.insert(std::pair<std::string, std::vector<sf::IntRect> >("RedAttackLeft", hitBoxLeft));
	hitBoxes.insert(std::pair<std::string, std::vector<sf::IntRect> >("GreenAttackRight", hitBoxRight));
	hitBoxes.insert(std::pair<std::string, std::vector<sf::IntRect> >("GreenAttackLeft", hitBoxLeft));
}

void Player::AnimationDone(const std::string& currentAnimation)
{
	if (currentAnimation == "BlueAttackRight" || currentAnimation == "BlueAttackLeft")
	{
		PlayAnimation(facing == RIGHT ? "BlueIdleRight" : "BlueIdleLeft");
		state = IDLE;
	}
	else if (currentAnimation == "GreenAttackRight" || currentAnimation == "GreenAttackLeft")
	{
		PlayAnimation(facing == RIGHT ? "GreenIdleRight" : "GreenIdleLeft");
		state = IDLE;
	}
	else if (currentAnimation == "RedAttackRight" || currentAnimation == "RedAttackLeft")
	{
		PlayAnimation(facing == RIGHT ? "RedIdleRight" : "RedIdleLeft");
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
