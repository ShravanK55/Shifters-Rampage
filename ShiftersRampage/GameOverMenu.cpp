#include "GameOverMenu.h"


GameOverMenu::GameOverMenu() {}

GameOverMenu::GameOverMenu(int score, int enemiesKilled) :
	playerScore(score),
	killCount(enemiesKilled)
{
	menuFont.loadFromFile("Fonts/KenPixel Mini.ttf");
	std::stringstream pScore, pKilled;
	pScore << score;
	pKilled << enemiesKilled;
	this->score = sf::Text(sf::String(pScore.str()), menuFont, 40);
	this->score.setPosition(Globals::SCREEN_WIDTH / 2, 205);
	this->enemiesKilled = sf::Text(sf::String(pKilled.str()), menuFont, 40);
	this->enemiesKilled.setPosition(Globals::SCREEN_WIDTH / 2, 615);
	Init();
}

GameOverMenu::~GameOverMenu() {}

void GameOverMenu::Init()
{
	GameOverMenuItem play;
	play.optionRect = sf::IntRect(419, 320, 191, 46);
	play.action = GameOverMenuAction::YES;

	GameOverMenuItem exit;
	exit.optionRect = sf::IntRect(419, 391, 191, 46);
	exit.action = GameOverMenuAction::NO;

	menuItems.push_back(play);
	menuItems.push_back(exit);
}

GameOverMenuAction GameOverMenu::DisplayMenu(Graphics& graphics)
{
	sf::Texture* menuTexture = graphics.LoadImage("MenuScreen/GameOver.png");
	sf::Sprite menuSprite;
	menuSprite.setTexture(*menuTexture);

	sf::Event windowEvent;
	GameOverMenuAction mAction;

	while (true)
	{
		graphics.GetRenderWindow().pollEvent(windowEvent);

		switch (windowEvent.type)
		{
		case sf::Event::MouseButtonPressed:
			mAction = HandleClick(windowEvent.mouseButton.x, windowEvent.mouseButton.y);
			if (mAction != GameOverMenuAction::NONE)
				return mAction;
			break;

		case sf::Event::Closed:
			return GameOverMenuAction::NO;
		}

		std::stringstream pScore, pKilled;
		pScore << playerScore;
		pKilled << killCount;

		score.setString(pScore.str());
		score.setFont(menuFont);
		score.setCharacterSize(40);
		score.setPosition(Globals::SCREEN_WIDTH / 2 - score.getLocalBounds().width / 2, 195);
		enemiesKilled.setString(pKilled.str());
		enemiesKilled.setFont(menuFont);
		enemiesKilled.setCharacterSize(40);
		enemiesKilled.setPosition(Globals::SCREEN_WIDTH / 2 - enemiesKilled.getLocalBounds().width / 2, 605);

		graphics.ClearWindow();
		graphics.BlitSurface(menuSprite, menuSprite.getTextureRect());
		graphics.GetRenderWindow().draw(score);
		graphics.GetRenderWindow().draw(enemiesKilled);
		graphics.Render();
	}
}

GameOverMenuAction GameOverMenu::HandleClick(int x, int y)
{
	for (int i = 0; i < menuItems.size(); i++)
	{
		if (x > menuItems[i].optionRect.left &&
			x < menuItems[i].optionRect.left + menuItems[i].optionRect.width &&
			y > menuItems[i].optionRect.top &&
			y < menuItems[i].optionRect.top + menuItems[i].optionRect.height)
			return menuItems[i].action;
	}

	return GameOverMenuAction::NONE;
}