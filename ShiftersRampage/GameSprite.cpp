#include "GameSprite.h"



GameSprite::GameSprite() :
	sprite(),
	sourceRect(0, 0, 0, 0),
	scale(1.0f)
{}

GameSprite::GameSprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height, int posX, int posY, float scale)
{
	position = sf::Vector2f(posX, posY);
	this->scale = scale;
	spriteTexture = graphics.LoadImage(filePath);
	sprite.setTexture(*spriteTexture);
	sprite.setPosition(position.x, position.y);
	sprite.setScale(scale, scale);

	sourceRect.left = sourceX;
	sourceRect.top = sourceY;
	sourceRect.width = width;
	sourceRect.height = height;

	boundingBox = sf::IntRect(position.x, position.y, width * scale, height * scale);
}

GameSprite::~GameSprite()
{}

const sf::IntRect GameSprite::GetBoundingBox() const { return boundingBox; }

void GameSprite::Update(float elapsedTime)
{
	boundingBox = sf::IntRect(position.x, position.y, sourceRect.width * scale, sourceRect.height * scale);
}

void GameSprite::Draw(Graphics& graphics)
{
	graphics.BlitSurface(sprite, sourceRect);
}

const Side::Side GameSprite::GetCollisionSide(sf::IntRect& other) const
{
	int amtRight, amtLeft, amtTop, amtBottom;

	amtRight = boundingBox.left + boundingBox.width - other.left;
	amtLeft = other.left + other.width - boundingBox.left;
	amtTop = other.top + other.height - boundingBox.top;
	amtBottom = boundingBox.top + boundingBox.height - other.top;

	int values[4] = { abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom) };
	int lowest = values[0];
	for (int i = 0; i < 4; i++)
	{
		if (values[i] < lowest)
			lowest = values[i];
	}

	return lowest == abs(amtRight) ? Side::RIGHT :
		   lowest == abs(amtLeft) ? Side::LEFT :
		   lowest == abs(amtTop) ? Side::TOP :
		   lowest == abs(amtBottom) ? Side::BOTTOM :
		   Side::NONE;
}
