#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

#include "Graphics.h"
#include "Tile.h"
#include "tinyxml2.h"

struct Tileset
{
	sf::Texture* texture;
	int firstGid;

	Tileset() { firstGid = -1; }

	Tileset(sf::Texture* texture, int tilesetFirstGid) :
		texture(texture), firstGid(tilesetFirstGid)
	{}
};

class Level
{
public:
	Level();
	Level(const std::string& name, sf::Vector2i spawnPoint, Graphics& graphics);
	~Level();

	void Update(float elapsedTime);
	void Draw(Graphics& graphics);

	const sf::Vector2i GetSpawnPoint() const;

	std::vector<sf::IntRect> CheckTileCollisions(const sf::IntRect& other);

private:
	std::string mapName;
	sf::Vector2i spawnPoint;

	sf::Vector2i tileSize;
	sf::Vector2i mapSize;

	sf::Texture background;

	std::vector<Tile> tileList;
	std::vector<Tileset> tilesetList;
	std::vector<sf::IntRect> collisionRects;

	void LoadMap(const std::string& mapName, Graphics& graphics);
};

