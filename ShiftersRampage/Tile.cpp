#include "Tile.h"


Tile::Tile() {}

Tile::Tile(sf::Texture* tileset, sf::Vector2i size, sf::Vector2i tilesetPosition, sf::Vector2i position) :
	tileset(tileset), size(size),
	tilesetPosition(tilesetPosition), position(position)
{
	tileSprite.setTexture(*tileset);
	tileSprite.setPosition(position.x, position.y);
	tileSprite.setTextureRect(sf::IntRect(tilesetPosition.x, tilesetPosition.y, size.x, size.y));
}

Tile::~Tile()
{}

void Tile::Update(float elapsedTime) {}

void Tile::Draw(Graphics& graphics)
{
	graphics.BlitSurface(tileSprite, tileSprite.getTextureRect());
}