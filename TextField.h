#pragma once

#include <iostream>

#include <sfml/graphics.hpp>

class TextField : public sf::Text
{
private:
	unsigned short m_charLimit;
	std::wstring m_string;
	sf::RectangleShape background;
public:
	TextField(const sf::Font& font, const sf::Text::Style& style = sf::Text::Style::Regular, const sf::Color& colorText = sf::Color::White,
			  const unsigned short& charSize = 36, const unsigned short& charLimit = 32u, const sf::Color& colorBg = sf::Color(35, 35, 35));
	void setPosition(float x, float y);
	void handleInput(const sf::Event &e);
	void render(sf::RenderTarget& target)const;
};	