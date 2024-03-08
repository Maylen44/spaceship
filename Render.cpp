#include "Renderer.h"

Renderer::Renderer()
	: m_windowMode()
	, m_windowTitel("SPACESHIP")
	, m_windowStyle(sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close)
	, m_window()
{
	m_windowMode.width = ConfigManager::instance()->getConfig(ConfigField_WindowResolution_X);
	m_windowMode.height = ConfigManager::instance()->getConfig(ConfigField_WindowResolution_Y);
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
	AssetsManager* s_AssetManager = AssetsManager::instance();

	m_window.clear();
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->draw(m_window);
	}
	for (int i = 0; i < Text::Text_MAX; i++)
	{
		m_window.draw(s_AssetManager->getText(static_cast<Text>(i)));
	}
	m_window.display();
}



void Renderer::closeWindow()
{
	m_window.close();
}
