#include "TextField.h"

TextField::TextField(const sf::Font& font, const unsigned short& charSize, const unsigned short& charLimit, const sf::Color& colorText,
	const sf::Color& colorBg, const sf::Text::Style& style) :
	m_charLimit(charLimit)
{
	setFont(font);
	setFillColor(colorText);
	setStyle(style);
	this->setCharacterSize(charSize);
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
	//background.setSize(sf::Vector2f(this->getGlobalBounds()));
}

void TextField::render(sf::RenderTarget& target) const
{
	target.draw(background);
	target.draw(*this);
}
