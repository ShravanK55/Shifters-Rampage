#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>

#include "Globals.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	sf::RenderWindow& GetRenderWindow();

	sf::Texture* LoadImage(const std::string& filePath);

	void ClearWindow();
	void BlitSurface(sf::Sprite& sprite, sf::IntRect sourceRect);
	void Render();

private:
	sf::RenderWindow window;
	std::map<std::string, sf::Texture*> textureCache;
};

