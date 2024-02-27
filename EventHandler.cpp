#include "EventHandler.h"

InputEvent EventHandler::fetchApplicationStatus(sf::Event& windowPollEvent)
{
    InputEvent status = NoInput;

    updateKeyboardState(windowPollEvent);
    updateMouseState(windowPollEvent);

    if ((windowPollEvent.type == sf::Event::Closed) || keyboardState[ESC])
    {
        status = ESC;
    }
    else if (keyboardState[Restart])
    {
        status = Restart;
    }
    return status;
}

InputEvent EventHandler::fetchKeyboardEvent()
{
    InputEvent result = NoInput;

    if ((keyboardState[W] && keyboardState[A]) || 
        (keyboardState[Up] && keyboardState[Left]))
        result = UpLeft;
    else if ((keyboardState[W] && keyboardState[D]) || 
        (keyboardState[Up] && keyboardState[Right]))
        result = UpRight;
    else if ((keyboardState[S] && keyboardState[A]) || 
        (keyboardState[Down] && keyboardState[Left]))
        result = DownLeft;
    else if ((keyboardState[S] && keyboardState[D]) || 
        (keyboardState[Down] && keyboardState[Right]))
        result = DownRight;

    else if (keyboardState[W] || keyboardState[Up])
        result = Up;
    else if (keyboardState[S] || keyboardState[Down])
        result = Down;
    else if (keyboardState[A] || keyboardState[Left])
        result = Left;
    else if (keyboardState[D] || keyboardState[Right])
        result = Right;

    return result;
}

InputEvent EventHandler::fetchMouseEvent()
{
    InputEvent result = NoInput;
    if(mouseState[MouseLeft] && mouseState[MouseRight])
        result = MouseLeftAndRight;
    else if(mouseState[MouseLeft])
        result = MouseLeft;
    else if (mouseState[MouseRight])
        result = MouseRight;

    return result;
}

void EventHandler::updateKeyboardState(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
        keyboardState[static_cast<InputEvent>(event.key.code)] = true;
    else if (event.type == sf::Event::KeyReleased)
        keyboardState[static_cast<InputEvent>(event.key.code)] = false;
}

void EventHandler::updateMouseState(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
        mouseState[static_cast<InputEvent>(event.mouseButton.button)] = true;
    else if (event.type == sf::Event::MouseButtonReleased)
        mouseState[static_cast<InputEvent>(event.mouseButton.button)] = false;
}
