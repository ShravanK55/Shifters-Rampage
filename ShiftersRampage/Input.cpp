#include "Input.h"



Input::Input() {}
Input::~Input() {}

void Input::BeginNewFrame()
{
	pressedKeys.clear();
	releasedKeys.clear();
	pressedMouseButtons.clear();
	releasedMouseButtons.clear();
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

void Input::MouseButtonPressed(sf::Event buttonEvent)
{
	pressedMouseButtons[buttonEvent.mouseButton.button] = true;
	heldMouseButtons[buttonEvent.mouseButton.button] = true;
}

void Input::MouseButtonReleased(sf::Event buttonEvent)
{
	releasedMouseButtons[buttonEvent.mouseButton.button] = true;
	heldMouseButtons[buttonEvent.mouseButton.button] = false;
}

bool Input::wasKeyPressed(sf::Keyboard::Key key) { return pressedKeys[key]; }
bool Input::wasKeyReleased(sf::Keyboard::Key key) {	return releasedKeys[key]; }
bool Input::isKeyHeld(sf::Keyboard::Key key) { return heldKeys[key]; }
bool Input::wasMouseButtonPressed(sf::Mouse::Button button) { return pressedMouseButtons[button]; }
bool Input::wasMouseButtonReleased(sf::Mouse::Button button) { return releasedMouseButtons[button]; }
bool Input::isMouseButtonHeld(sf::Mouse::Button button) { return heldMouseButtons[button]; }