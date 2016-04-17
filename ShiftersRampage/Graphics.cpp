#include "Graphics.h"



Graphics::Graphics()
{
	window.create(sf::VideoMode(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT), "Shifter's Rampage");
	window.setFramerateLimit(Globals::FPS);
}

Graphics::~Graphics()
{
	for (auto itr = textureCache.begin(); itr != textureCache.end(); itr++)
	{
		delete itr->second;
	}
	textureCache.clear();

	window.close();
}


sf::RenderWindow& Graphics::GetRenderWindow() { return window; }

sf::Texture* Graphics::LoadImage(const std::string& filePath)
{
	if (textureCache.count(filePath) == 0)
	{
		textureCache[filePath] = new sf::Texture();
		textureCache[filePath]->loadFromFile(filePath);
	}

	return textureCache[filePath];
}

void Graphics::ClearWindow()
{
	window.clear();
}

void Graphics::BlitSurface(sf::Sprite& sprite, sf::IntRect sourceRect)
{
	sprite.setTextureRect(sourceRect);
	window.draw(sprite);
}

void Graphics::Render()
{
	window.display();
}