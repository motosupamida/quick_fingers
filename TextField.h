#pragma once

#include <iostream>
#include <sfml/graphics.hpp>
#include "TextString.h"

class TextField : public sf::RectangleShape
{
private:
	std::wstring m_wString;
	std::vector<TextString> m_textVector;
	sf::RectangleShape m_background;
	sf::Font m_font;
	sf::Text::Style m_style;
	sf::Color m_colorText;
	sf::Color m_colorBg;
	unsigned short m_charSize;
	unsigned short m_activeStringNumber;
public:
	TextField(const sf::Font& font, const sf::Text::Style& style = sf::Text::Style::Regular, const sf::Color& colorText = sf::Color::White,
			  const unsigned short& charSize = 36, const sf::Color& colorBg = sf::Color(35, 35, 35));
	unsigned short getCharacterSize();
	unsigned short getHeight();
	unsigned short getWidth();
	std::wstring getWString();
	void setPosition(float x, float y, unsigned short i = 0);
	void handleInput(const sf::Event &e, const unsigned short& winWidth, const unsigned short& winHigth);
	void render(sf::RenderTarget& target)const;
	void setWString(const std::wstring& wString, const unsigned short& winWidth, const unsigned short& winHight);
};	