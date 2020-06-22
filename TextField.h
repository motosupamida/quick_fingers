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
	TextField(const sf::Font& font, const unsigned short& maxChars = 32u, const sf::Color& colorText = sf::Color::White, 
			  const sf::Color& colorBg = sf::Color(70,70,70), const sf::Text::Style& style = sf::Text::Italic);
	void setPosition(float x, float y);
	void handleInput(const sf::Event &e);
	void render(sf::RenderTarget& target)const;
};