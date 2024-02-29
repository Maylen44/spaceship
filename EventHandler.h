#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "SharedContent.h"

class EventHandler
{
public:
	InputEvent fetchApplicationStatus(sf::Event& windowPollEvent);
	InputEvent fetchKeyboardEvent();
	InputEvent fetchMouseEvent();

private:
	void updateKeyboardState(sf::Event& event);
	void updateMouseState(sf::Event& event);

	std::unordered_map<sf::Keyboard::Key, bool> keyboardState;
	std::unordered_map<sf::Mouse::Button, bool> mouseState;
};

#endif //EVENT_HANDLER_H