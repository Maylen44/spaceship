#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "SharedContent.h"

class EventHandler
{
public:
	void setEvents(std::vector<InputEvent>& events, sf::Event& windowPollEvent);
private:
	void updateKeyboardState(sf::Event& event);
	void updateMouseState(sf::Event& event);
	void setKeyboardEvents(std::vector<InputEvent>& events);
	void setMouseEvents(std::vector<InputEvent>& events);
	std::unordered_map<sf::Keyboard::Key, bool> keyboardState;
	std::unordered_map<sf::Mouse::Button, bool> mouseState;
};

#endif //EVENT_HANDLER_H