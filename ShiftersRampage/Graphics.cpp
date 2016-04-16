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

	window.close();
}


sf::RenderWindow& Graphics::GetRenderWindow() { return window; }

sf::Texture* Graphics::LoadImage(const std::string& filePath)
{
	auto itr = textureCache.find(filePath);

	if (itr == textureCache.end())
	{
		sf::Texture* texture = new sf::Texture();

		if (!texture->loadFromFile(filePath))
		{
			std::cout << "Could not load the texture!\n" << std::endl;
			delete texture;
			return nullptr;
		}

		textureCache.insert(std::pair<std::string, sf::Texture*>(filePath, texture));
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