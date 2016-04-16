#include "Graphics.h"



Graphics::Graphics()
{
	window.create(sf::VideoMode(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT), "Shifter's Rampage");
	window.setFramerateLimit(Globals::FPS);
}

Graphics::~Graphics()
{
	std::map<std::string, sf::Texture*>::iterator itr;

	for (itr = textureCache.begin(); itr != textureCache.end(); itr++)
	{
		delete itr->second;
		textureCache.erase(itr);
	}

	window.close();
}


sf::RenderWindow& Graphics::GetRenderWindow() { return window; }

sf::Texture* Graphics::LoadImage(const std::string& filePath)
{
	sf::Texture* texture = new sf::Texture();

	if (!texture->loadFromFile(filePath))
	{
		std::cout << "Could not load the texture!\n" << std::endl;
		return nullptr;
	}

	textureCache.insert(std::pair<std::string, sf::Texture*> (filePath, texture));
	return texture;
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