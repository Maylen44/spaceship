#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "SharedContent.h"

class EventHandler
{
public:
	ApplicationStatus fetchApplicationStatus(sf::Event& windowPollEvent);
	KeyboardEvent fetchKeyboardEvent();
	MouseEvent fetchMouseEvent();

private:
	void updateKeyboardState(sf::Event& event);
	void updateMouseState(sf::Event& event);

	std::unordered_map<InputEvent, bool> keyboardState;
	std::unordered_map<InputEvent, bool> mouseState;
};

#endif //EVENT_HANDLER_H