#include "Level.h"


Level::Level() {}

Level::Level(const std::string& name, sf::Vector2i spawnPoint, Graphics& graphics) :
	mapName(name),
	spawnPoint(spawnPoint),
	mapSize(sf::Vector2i(0, 0))
{
	LoadMap(mapName, graphics);
}

Level::~Level()
{}

void Level::Update(float elapsedTime) {}

void Level::Draw(Graphics& graphics)
{
	for (int i = 0; i < tileList.size(); i++)
	{
		tileList[i].Draw(graphics);
	}
}

const sf::Vector2i Level::GetSpawnPoint() const { return spawnPoint; }

std::vector<sf::IntRect> Level::CheckTileCollisions(const sf::IntRect& other)
{
	std::vector<sf::IntRect> others;

	for (int i = 0; i < collisionRects.size(); i++)
	{
		if (collisionRects[i].intersects(other))
			others.push_back(collisionRects[i]);
	}

	return others;
}

void Level::LoadMap(const std::string& mapName, Graphics& graphics)
{
	tinyxml2::XMLDocument document;
	std::stringstream docPath;
	docPath << "Maps/" << mapName << ".tmx";
	document.LoadFile(docPath.str().c_str());

	tinyxml2::XMLElement* mapNode = document.FirstChildElement("map");

	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	mapSize = sf::Vector2i(width, height);

	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	tileSize = sf::Vector2i(tileWidth, tileHeight);

	tinyxml2::XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset != nullptr)
	{
		while (pTileset)
		{
			int firstGid;
			const char* source = pTileset->FirstChildElement("image")->Attribute("source");

			std::stringstream filePath;
			filePath << source;

			pTileset->QueryIntAttribute("firstgid", &firstGid);

			sf::Texture* texture;
			texture = graphics.LoadImage(filePath.str());

			tilesetList.push_back(Tileset(texture, firstGid));

			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}

	tinyxml2::XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer != nullptr)
	{
		while (pLayer)
		{
			tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != nullptr)
			{
				while (pData)
				{
					tinyxml2::XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != nullptr)
					{
						int tileCounter = 0;
						while (pTile)
						{
							if (pTile->IntAttribute("gid") == 0)
							{
								tileCounter++;

								if (pTile->NextSiblingElement("tile"))
								{
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}

								else break;
							}

							int gid = pTile->IntAttribute("gid");
							Tileset tls;
							for (int i = 0; i < tilesetList.size(); i++)
							{
								if (tilesetList[i].firstGid <= gid)
								{
									tls = tilesetList[i];
									break;
								}
							}

							if (tls.firstGid == -1)
							{
								tileCounter++;

								if (pTile->NextSiblingElement("tile"))
								{
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}

								else break;
							}

							int xx = 0, yy = 0;
							xx = tileCounter % width;
							xx *= tileWidth;
							yy += tileHeight * (tileCounter / width);
							sf::Vector2i finalTilePosition(xx, yy);

							int tilesetWidth = tls.texture->getSize().x;
							int tilesetHeight = tls.texture->getSize().y;

							int tsxx = (gid % (tilesetWidth / tileWidth)) - 1;
							tsxx *= tileWidth;
							int amount = gid / (tilesetWidth / tileWidth);
							int tsyy = tileHeight * amount;
							
							sf::Vector2i finalTilesetPosition(tsxx, tsyy);
							Tile tile(tls.texture, sf::Vector2i(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
							tileList.push_back(tile);
							tileCounter++;

							pTile = pTile->NextSiblingElement("tile");
						}
					}

					pData = pData->NextSiblingElement("data");
				}
			}

			pLayer = pLayer->NextSiblingElement("layer");
		}
	}

	tinyxml2::XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
	if (pObjectGroup != nullptr)
	{
		while (pObjectGroup)
		{
			const char* name = pObjectGroup->Attribute("name");
			std::stringstream ss;
			ss << name;
			if (ss.str() == "CollisionBoxes")
			{
				tinyxml2::XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL)
				{
					while (pObject)
					{
						int x, y, rectWidth, rectHeight;
						x = pObject->IntAttribute("x");
						y = pObject->IntAttribute("y");
						rectWidth = pObject->IntAttribute("width");
						rectHeight = pObject->IntAttribute("height");

						collisionRects.push_back(sf::IntRect(x, y, rectWidth, rectHeight));

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}

			else if (ss.str() == "SpawnPoint")
			{
				tinyxml2::XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL)
				{
					while (pObject)
					{
						int x = pObject->IntAttribute("x");
						int y = pObject->IntAttribute("y");
						const char* name = pObject->Attribute("name");
						std::stringstream ss;
						ss << name;

						if (ss.str() == "Spawn Point")
						{
							spawnPoint = sf::Vector2i(x, y);
						}

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}

			pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
		}
	}
}
