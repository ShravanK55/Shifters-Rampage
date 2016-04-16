#include "GameSprite.h"



GameSprite::GameSprite() :
	spriteTexture(NULL),
	sprite(),
	sourceRect(0, 0, 0, 0)
{}

GameSprite::GameSprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height, int posX, int posY, float scale)
{
	position = sf::Vector2f(posX, posY);
	spriteTexture = graphics.LoadImage(filePath);
	sprite.setTexture(*spriteTexture);
	sprite.setPosition(position.x, position.y);
	sprite.setScale(scale, scale);

	sourceRect.left = sourceX;
	sourceRect.top = sourceY;
	sourceRect.width = width;
	sourceRect.height = height;
}

GameSprite::~GameSprite()
{
}

void GameSprite::Update(float elapsedTime)
{
}

void GameSprite::Draw(Graphics& graphics)
{
	graphics.BlitSurface(sprite, sourceRect);
}