#include "Renderer.h"

Renderer::Renderer()
	: m_windowMode()
	, m_windowTitel("SPACESHIP")
	, m_windowStyle(sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close)
	, m_window()
{
	if (g_sharedContent == nullptr)
	{
		g_sharedContent = new SharedContent();
	}
	m_windowMode.width = g_sharedContent->WINDOW_RESOLUTION.x;
	m_windowMode.height = g_sharedContent->WINDOW_RESOLUTION.y;
	m_window.create(m_windowMode, m_windowTitel, m_windowStyle);
}

sf::Event& Renderer::pollWindowEvent()
{
	sf::Event pollRequest;
	m_window.pollEvent(pollRequest);
	return pollRequest;
}

void const Renderer::renderContent(const std::vector<IGameObject*>& objects)
{
	m_window.clear();
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->draw(m_window);
	}
	m_window.draw(g_sharedContent->TXT_SCORE);
	m_window.draw(g_sharedContent->TXT_HEALTHPOINTS_PLAYER);
	m_window.display();
}



void Renderer::closeWindow()
{
	m_window.close();
}
