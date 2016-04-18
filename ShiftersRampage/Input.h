#pragma once
#include <map>
#include <SFML/Window.hpp>

class Input
{
public:
	Input();
	~Input();

	void BeginNewFrame();

	void KeyUpEvent(sf::Event keyEvent);
	void KeyDownEvent(sf::Event keyEvent);
	void MouseButtonPressed(sf::Event buttonEvent);
	void MouseButtonReleased(sf::Event buttonEvent);

	bool wasKeyPressed(sf::Keyboard::Key key);
	bool wasKeyReleased(sf::Keyboard::Key key);
	bool isKeyHeld(sf::Keyboard::Key key);
	bool wasMouseButtonPressed(sf::Mouse::Button button);
	bool wasMouseButtonReleased(sf::Mouse::Button button);
	bool isMouseButtonHeld(sf::Mouse::Button button);

private:
	std::map<sf::Keyboard::Key, bool> pressedKeys;
	std::map<sf::Keyboard::Key, bool> releasedKeys;
	std::map<sf::Keyboard::Key, bool> heldKeys;
	std::map<sf::Mouse::Button, bool> pressedMouseButtons;
	std::map<sf::Mouse::Button, bool> releasedMouseButtons;
	std::map<sf::Mouse::Button, bool> heldMouseButtons;
};

