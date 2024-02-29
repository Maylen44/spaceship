#include "EventHandler.h"

InputEvent EventHandler::fetchApplicationStatus(sf::Event& windowPollEvent)
{
    InputEvent status = NoInput;

    updateKeyboardState(windowPollEvent);
    updateMouseState(windowPollEvent);

    if ((windowPollEvent.type == sf::Event::Closed) || keyboardState[sf::Keyboard::Escape])
    {
        status = ESC;
    }
    else if (keyboardState[sf::Keyboard::R])
    {
        status = Restart;
    }
    return status;
}

InputEvent EventHandler::fetchKeyboardEvent()
{
    InputEvent result = NoInput;

    if ((keyboardState[sf::Keyboard::W] && keyboardState[sf::Keyboard::A]) ||
        (keyboardState[sf::Keyboard::Up] && keyboardState[sf::Keyboard::Left]))
        result = UpLeft;
    else if ((keyboardState[sf::Keyboard::W] && keyboardState[sf::Keyboard::D]) ||
        (keyboardState[sf::Keyboard::Up] && keyboardState[sf::Keyboard::Right]))
        result = UpRight;
    else if ((keyboardState[sf::Keyboard::S] && keyboardState[sf::Keyboard::A]) ||
        (keyboardState[sf::Keyboard::Down] && keyboardState[sf::Keyboard::Left]))
        result = DownLeft;
    else if ((keyboardState[sf::Keyboard::S] && keyboardState[sf::Keyboard::D]) ||
        (keyboardState[sf::Keyboard::Down] && keyboardState[sf::Keyboard::Right]))
        result = DownRight;

    else if (keyboardState[sf::Keyboard::W] || keyboardState[sf::Keyboard::Up])
        result = Up;
    else if (keyboardState[sf::Keyboard::S] || keyboardState[sf::Keyboard::Down])
        result = Down;
    else if (keyboardState[sf::Keyboard::A] || keyboardState[sf::Keyboard::Left])
        result = Left;
    else if (keyboardState[sf::Keyboard::D] || keyboardState[sf::Keyboard::Right])
        result = Right;

    return result;
}

InputEvent EventHandler::fetchMouseEvent()
{
    InputEvent result = NoInput;
    if(mouseState[sf::Mouse::Left] && mouseState[sf::Mouse::Right])
        result = MouseLeftAndRight;
    else if(mouseState[sf::Mouse::Left])
        result = MouseLeft;
    else if (mouseState[sf::Mouse::Right])
        result = MouseRight;

    return result;
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
