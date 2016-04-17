#pragma once
#include "Graphics.h"

class GameSprite
{
public:
	GameSprite();
	GameSprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height, int posX, int posY, float scale = 1.0f);
	virtual ~GameSprite();

	const sf::IntRect GetBoundingBox() const;

	virtual void Update(float elapsedTime);
	virtual void Draw(Graphics& graphics);

	const Side::Side GetCollisionSide(sf::IntRect& other) const;

protected:
	sf::Texture* spriteTexture;
	sf::Sprite sprite;
	sf::IntRect sourceRect;
	float scale;

	sf::IntRect boundingBox;

	sf::Vector2f position;

private:

};

