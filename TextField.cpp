#include "TextField.h"

TextField::TextField(const sf::Font &font, const unsigned short& maxChars, const sf::Color &colorText, 
					 const sf::Color &colorBg, const sf::Text::Style &style) :
	m_charLimit(maxChars * 16) //number of pixels for one char
{
	setFont(font);
	setFillColor(colorText);
	setStyle(style);
	background.setFillColor(colorBg);
}

void TextField::setPosition(float x, float y)
{
	sf::Transformable::setPosition(x, y);
	background.setPosition(x, y);
}

void TextField::handleInput(const sf::Event &e)
{
	if (e.text.unicode == 8)    // Delete key
	{
		m_string = m_string.substr(0, m_string.size() - 1);
	}
	else if (m_string.size() < m_charLimit) 
	{
		m_string += e.text.unicode;
	}
	setString(m_string);
}

void TextField::render(sf::RenderTarget& target) const
{
	target.draw(background);
	target.draw(*this);
}
