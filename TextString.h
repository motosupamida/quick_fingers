#pragma once

#include <iostream>
#include <sfml/graphics.hpp>

class TextString : public sf::Text
{
private:
	std::wstring m_wString;
	sf::RectangleShape background;
public:
	TextString(const sf::Font& font, const sf::Text::Style& style = sf::Text::Style::Regular, const sf::Color& colorText = sf::Color::White,
				const unsigned short& charSize = 36, const sf::Color& colorBg = sf::Color(35, 35, 35));
	void setPosition(float x, float y);
	void handleInput(const sf::Event& e);
	void render(sf::RenderTarget& target)const;
	void setMWString(std::wstring wString);
	};

