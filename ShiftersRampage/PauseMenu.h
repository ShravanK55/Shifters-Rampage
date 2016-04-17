#pragma once
#include "Graphics.h"

enum class PauseMenuAction
{
	RESUME,
	QUIT,
	NONE
};

struct PauseMenuItem
{
	sf::IntRect optionRect;
	PauseMenuAction action;
};

class PauseMenu
{
public:
	PauseMenu();
	~PauseMenu();

	void Init();
	PauseMenuAction DisplayMenu(Graphics& graphics);
	PauseMenuAction HandleClick(int x, int y);

private:
	std::vector<PauseMenuItem> menuItems;
};
