#include "MainMenu.h"



MainMenu::MainMenu() { Init(); }
MainMenu::~MainMenu() {}

void MainMenu::Init()
{
	MainMenuItem play;
	play.optionRect = sf::IntRect(419, 320, 191, 46);
	play.action = MainMenuAction::PLAY;

	MainMenuItem exit;
	exit.optionRect = sf::IntRect(419, 391, 191, 46);
	exit.action = MainMenuAction::EXIT;

	menuItems.push_back(play);
	menuItems.push_back(exit);
}

MainMenuAction MainMenu::DisplayMenu(Graphics& graphics)
{
	sf::Texture* menuTexture = graphics.LoadImage("MenuScreen/MainMenu.png");
	sf::Sprite menuSprite;
	menuSprite.setTexture(*menuTexture);

	sf::Event windowEvent;
	MainMenuAction mAction;

	while (true)
	{
		graphics.GetRenderWindow().pollEvent(windowEvent);

		switch (windowEvent.type)
		{
		case sf::Event::MouseButtonPressed:
			mAction = HandleClick(windowEvent.mouseButton.x, windowEvent.mouseButton.y);
			if (mAction != MainMenuAction::NONE)
				return mAction;
			break;

		case sf::Event::Closed:
			return MainMenuAction::EXIT;
		}

		graphics.ClearWindow();
		graphics.BlitSurface(menuSprite, menuSprite.getTextureRect());
		graphics.Render();
	}
}

MainMenuAction MainMenu::HandleClick(int x, int y)
{
	for (int i = 0; i < menuItems.size(); i++)
	{
		if (x > menuItems[i].optionRect.left &&
			x < menuItems[i].optionRect.left + menuItems[i].optionRect.width &&
			y > menuItems[i].optionRect.top &&
			y < menuItems[i].optionRect.top + menuItems[i].optionRect.height)
			return menuItems[i].action;
	}

	return MainMenuAction::NONE;
}