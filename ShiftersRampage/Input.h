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

	bool wasKeyPressed(sf::Keyboard::Key key);
	bool wasKeyReleased(sf::Keyboard::Key key);
	bool isKeyHeld(sf::Keyboard::Key key);

private:
	std::map<sf::Keyboard::Key, bool> pressedKeys;
	std::map<sf::Keyboard::Key, bool> releasedKeys;
	std::map<sf::Keyboard::Key, bool> heldKeys;
};

