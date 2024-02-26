#ifndef RENDERER_H
#define RENDERER_H

#include "IGameObject.h"

class Renderer
{
public:
	Renderer();

	sf::Event& pollWindowEvent();
	void const renderContent(const std::vector<IGameObject*>& objects, 
								sf::Text scoreText,
								sf::Text hpText);
	void closeWindow();

private:
	sf::VideoMode m_windowMode;
	const std::string m_windowTitel;
	const sf::Uint64 m_windowStyle;
	sf::RenderWindow m_window;

};

#endif //RENDERER_H