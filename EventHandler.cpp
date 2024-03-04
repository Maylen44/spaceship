#include "EventHandler.h"

void EventHandler::setEvents(std::vector<InputEvent>& events, sf::Event& windowPollEvent)
{
    events[0] = InputEvent_NoInput;
    if ((windowPollEvent.type == sf::Event::Closed) || keyboardState[sf::Keyboard::Escape])
    {
        events[0] = InputEvent_ESC;
    }
    else if (keyboardState[sf::Keyboard::R])
    {
        events[0] = InputEvent_Restart;
    }

    updateKeyboardState(windowPollEvent);
    updateMouseState(windowPollEvent);
    setKeyboardEvents(events);
    setMouseEvents(events);
}

void EventHandler::updateKeyboardState(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
        keyboardState[event.key.code] = true;
    else if (event.type == sf::Event::KeyReleased)
        keyboardState[event.key.code] = false;
}

void EventHandler::updateMouseState(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
        mouseState[event.mouseButton.button] = true;
    else if (event.type == sf::Event::MouseButtonReleased)
        mouseState[event.mouseButton.button] = false;
}

void EventHandler::setKeyboardEvents(std::vector<InputEvent>& events)
{
    events[1] = InputEvent_NoInput;

    if ((keyboardState[sf::Keyboard::W] && keyboardState[sf::Keyboard::A]) ||
        (keyboardState[sf::Keyboard::Up] && keyboardState[sf::Keyboard::Left]))
        events[1] = InputEvent_UpLeft;
    else if ((keyboardState[sf::Keyboard::W] && keyboardState[sf::Keyboard::D]) ||
        (keyboardState[sf::Keyboard::Up] && keyboardState[sf::Keyboard::Right]))
        events[1] = InputEvent_UpRight;
    else if ((keyboardState[sf::Keyboard::S] && keyboardState[sf::Keyboard::A]) ||
        (keyboardState[sf::Keyboard::Down] && keyboardState[sf::Keyboard::Left]))
        events[1] = InputEvent_DownLeft;
    else if ((keyboardState[sf::Keyboard::S] && keyboardState[sf::Keyboard::D]) ||
        (keyboardState[sf::Keyboard::Down] && keyboardState[sf::Keyboard::Right]))
        events[1] = InputEvent_DownRight;

    else if (keyboardState[sf::Keyboard::W] || keyboardState[sf::Keyboard::Up])
        events[1] = InputEvent_Up;
    else if (keyboardState[sf::Keyboard::S] || keyboardState[sf::Keyboard::Down])
        events[1] = InputEvent_Down;
    else if (keyboardState[sf::Keyboard::A] || keyboardState[sf::Keyboard::Left])
        events[1] = InputEvent_Left;
    else if (keyboardState[sf::Keyboard::D] || keyboardState[sf::Keyboard::Right])
        events[1] = InputEvent_Right;
}

void EventHandler::setMouseEvents(std::vector<InputEvent>& events)
{
    events[2] = InputEvent_NoInput;

    if (mouseState[sf::Mouse::Left] && mouseState[sf::Mouse::Right])
        events[2] = InputEvent_MouseLeftAndRight;
    else if (mouseState[sf::Mouse::Left])
        events[2] = InputEvent_MouseLeft;
    else if (mouseState[sf::Mouse::Right])
        events[2] = InputEvent_MouseRight;
}