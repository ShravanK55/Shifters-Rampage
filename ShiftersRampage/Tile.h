#pragma once
#include "Globals.h"
#include "Graphics.h"

class Tile
{
public:
	Tile();
	Tile(sf::Texture* tileset, sf::Vector2i size, sf::Vector2i tilesetPosition, sf::Vector2i position);
	~Tile();

	void Update(float elapsedTime);
	void Draw(Graphics& graphics);

private:
	sf::Sprite tileSprite;
	sf::Texture* tileset;
	sf::Vector2i size;
	sf::Vector2i tilesetPosition;
	sf::Vector2i position;
};

