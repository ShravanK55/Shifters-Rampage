#pragma once
#include "Graphics.h"

class GameSprite
{
public:
	GameSprite();
	GameSprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height, int posX, int posY, float scale = 1.0f);
	virtual ~GameSprite();

	virtual void Update(float elapsedTime);
	void Draw(Graphics& graphics);

protected:
	sf::Texture* spriteTexture;
	sf::Sprite sprite;
	sf::IntRect sourceRect;

	int x, y;

private:

};

