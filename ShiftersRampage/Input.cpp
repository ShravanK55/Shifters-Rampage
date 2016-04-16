#include "Input.h"



Input::Input() {}
Input::~Input() {}

void Input::BeginNewFrame()
{
	pressedKeys.clear();
	releasedKeys.clear();
}

void Input::KeyUpEvent(sf::Event keyEvent)
{
	releasedKeys[keyEvent.key.code] = true;
	heldKeys[keyEvent.key.code] = false;
}

void Input::KeyDownEvent(sf::Event keyEvent)
{
	pressedKeys[keyEvent.key.code] = true;
	heldKeys[keyEvent.key.code] = true;
}

bool Input::wasKeyPressed(sf::Keyboard::Key key) { return pressedKeys[key]; }
bool Input::wasKeyReleased(sf::Keyboard::Key key) {	return releasedKeys[key]; }
bool Input::isKeyHeld(sf::Keyboard::Key key) { return heldKeys[key]; }