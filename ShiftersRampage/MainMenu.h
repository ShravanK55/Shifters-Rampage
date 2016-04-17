#pragma once
#include "Graphics.h"

enum class MainMenuAction
{
	PLAY,
	EXIT,
	NONE
};

struct MainMenuItem
{
	sf::IntRect optionRect;
	MainMenuAction action;
};

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void Init();
	MainMenuAction DisplayMenu(Graphics& graphics);
	MainMenuAction HandleClick(int x, int y);

private:
	std::vector<MainMenuItem> menuItems;
};

