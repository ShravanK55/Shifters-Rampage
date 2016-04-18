#pragma once
#include <sstream>
#include "Graphics.h"

enum class GameOverMenuAction
{
	YES,
	NO,
	NONE
};

struct GameOverMenuItem
{
	sf::IntRect optionRect;
	GameOverMenuAction action;
};

class GameOverMenu
{
public:
	GameOverMenu();
	GameOverMenu(int score, int enemiesKilled);
	~GameOverMenu();

	void Init();
	GameOverMenuAction DisplayMenu(Graphics& graphics);
	GameOverMenuAction HandleClick(int x, int y);

private:
	std::vector<GameOverMenuItem> menuItems;
	sf::Font menuFont;
	sf::Text score;
	sf::Text enemiesKilled;

	int playerScore, killCount;
};

