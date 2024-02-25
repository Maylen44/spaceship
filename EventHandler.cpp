#include "EventHandler.h"

ApplicationStatus EventHandler::fetchApplicationStatus(sf::Event& windowPollEvent)
{
    ApplicationStatus status = Processing;

    updateKeyboardState(windowPollEvent);
    updateMouseState(windowPollEvent);

    if ((windowPollEvent.type == Closed) || keyboardState[ESC])
    {
        status = ClossingApplication;
    }
    else if (keyboardState[R])
    {
        status = RestartingApplication;
    }
    return status;
}

KeyboardEvent EventHandler::fetchKeyboardEvent()
{
    KeyboardEvent result = NoKeyboardInput;

    if (keyboardState[W] && keyboardState[A])
        result = MoveUpLeft;
    else if (keyboardState[W] && keyboardState[D])
        result = MoveUpRight;
    else if (keyboardState[S] && keyboardState[A])
        result = MoveDownLeft;
    else if (keyboardState[S] && keyboardState[D])
        result = MoveDownRight;
    else if (keyboardState[Up] && keyboardState[Left])
        result = MoveUpLeft;
    else if (keyboardState[Up] && keyboardState[Right])
        result = MoveUpRight;
    else if (keyboardState[Down] && keyboardState[Left])
        result = MoveDownLeft;
    else if (keyboardState[Down] && keyboardState[Right])
        result = MoveDownRight;

    else if (keyboardState[W])
        result = MoveUp;
    else if (keyboardState[Up])
        result = MoveUp;
    else if (keyboardState[S])
        result = MoveDown;
    else if (keyboardState[Down])
        result = MoveDown;
    else if (keyboardState[A])
        result = MoveLeft;
    else if (keyboardState[Left])
        result = MoveLeft;
    else if (keyboardState[D])
        result = MoveRight;
    else if (keyboardState[Right])
        result = MoveRight;

    return result;
}

MouseEvent EventHandler::fetchMouseEvent()
{
    MouseEvent result = NoMouseInput;
    if(mouseState[MouseLeft] && mouseState[MouseRight])
        result = RightAndLeftClick;
    else if (keyboardState[Space])
        result = RightClick;
    else if(mouseState[MouseLeft])
        result = LeftClick;
    else if (mouseState[MouseRight])
        result = RightClick;

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
