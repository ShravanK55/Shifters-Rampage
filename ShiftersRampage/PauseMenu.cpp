#include "PauseMenu.h"



PauseMenu::PauseMenu() { Init(); }
PauseMenu::~PauseMenu() {}

void PauseMenu::Init()
{
	PauseMenuItem resume;
	resume.optionRect = sf::IntRect(419, 320, 191, 46);
	resume.action = PauseMenuAction::RESUME;

	PauseMenuItem quit;
	quit.optionRect = sf::IntRect(419, 391, 191, 46);
	quit.action = PauseMenuAction::QUIT;

	menuItems.push_back(resume);
	menuItems.push_back(quit);
}

PauseMenuAction PauseMenu::DisplayMenu(Graphics& graphics)
{
	sf::Texture* menuTexture = graphics.LoadImage("MenuScreen/PauseMenu.png");
	sf::Sprite menuSprite;
	menuSprite.setTexture(*menuTexture);

	sf::Event windowEvent;
	PauseMenuAction mAction;

	while (true)
	{
		graphics.GetRenderWindow().pollEvent(windowEvent);

		switch (windowEvent.type)
		{
		case sf::Event::MouseButtonPressed:
			mAction = HandleClick(windowEvent.mouseButton.x, windowEvent.mouseButton.y);
			if (mAction != PauseMenuAction::NONE)
				return mAction;
			break;

		case sf::Event::Closed:
			return PauseMenuAction::QUIT;
		}

		graphics.ClearWindow();
		graphics.BlitSurface(menuSprite, menuSprite.getTextureRect());
		graphics.Render();
	}
}

PauseMenuAction PauseMenu::HandleClick(int x, int y)
{
	for (int i = 0; i < menuItems.size(); i++)
	{
		if (x > menuItems[i].optionRect.left &&
			x < menuItems[i].optionRect.left + menuItems[i].optionRect.width &&
			y > menuItems[i].optionRect.top &&
			y < menuItems[i].optionRect.top + menuItems[i].optionRect.height)
			return menuItems[i].action;
	}

	return PauseMenuAction::NONE;
}