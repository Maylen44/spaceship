#include "Renderer.h"

Test* gTest = nullptr;

Renderer::Renderer()
	: m_windowMode( WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y)
	, m_windowTitel("SPACESHIP")
	, m_windowStyle(sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close)
	, m_window(m_windowMode, m_windowTitel, m_windowStyle)
{}

sf::Event& Renderer::pollWindowEvent()
{
	if (gTest == nullptr)
	{
		gTest = new Test();
	}
	gTest->ini;
	sf::Event pollRequest;
	m_window.pollEvent(pollRequest);
	return pollRequest;
}

void const Renderer::renderContent(const std::vector<IGameObject*>& objects, 
										sf::Text scoreText,
										sf::Text hpText)
{
	m_window.clear();
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->draw(m_window);
	}
	m_window.draw(scoreText);
	m_window.draw(hpText);
	m_window.display();
}



void Renderer::closeWindow()
{
	m_window.close();
}
