#include "EventHandler.h"

void EventHandler::setEvents(std::vector<InputEvent>& events, sf::Event& windowPollEvent)
{
    events[0] = NoInput;
    if ((windowPollEvent.type == sf::Event::Closed) || keyboardState[sf::Keyboard::Escape])
    {
        events[0] = ESC;
    }
    else if (keyboardState[sf::Keyboard::R])
    {
        events[0] = Restart;
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
    events[1] = NoInput;

    if ((keyboardState[sf::Keyboard::W] && keyboardState[sf::Keyboard::A]) ||
        (keyboardState[sf::Keyboard::Up] && keyboardState[sf::Keyboard::Left]))
        events[1] = UpLeft;
    else if ((keyboardState[sf::Keyboard::W] && keyboardState[sf::Keyboard::D]) ||
        (keyboardState[sf::Keyboard::Up] && keyboardState[sf::Keyboard::Right]))
        events[1] = UpRight;
    else if ((keyboardState[sf::Keyboard::S] && keyboardState[sf::Keyboard::A]) ||
        (keyboardState[sf::Keyboard::Down] && keyboardState[sf::Keyboard::Left]))
        events[1] = DownLeft;
    else if ((keyboardState[sf::Keyboard::S] && keyboardState[sf::Keyboard::D]) ||
        (keyboardState[sf::Keyboard::Down] && keyboardState[sf::Keyboard::Right]))
        events[1] = DownRight;

    else if (keyboardState[sf::Keyboard::W] || keyboardState[sf::Keyboard::Up])
        events[1] = Up;
    else if (keyboardState[sf::Keyboard::S] || keyboardState[sf::Keyboard::Down])
        events[1] = Down;
    else if (keyboardState[sf::Keyboard::A] || keyboardState[sf::Keyboard::Left])
        events[1] = Left;
    else if (keyboardState[sf::Keyboard::D] || keyboardState[sf::Keyboard::Right])
        events[1] = Right;
}

void EventHandler::setMouseEvents(std::vector<InputEvent>& events)
{
    events[2] = NoInput;

    if (mouseState[sf::Mouse::Left] && mouseState[sf::Mouse::Right])
        events[2] = MouseLeftAndRight;
    else if (mouseState[sf::Mouse::Left])
        events[2] = MouseLeft;
    else if (mouseState[sf::Mouse::Right])
        events[2] = MouseRight;
}