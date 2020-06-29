#include "TextField.h"

TextField::TextField(const sf::Font& font, const sf::Text::Style& style, const sf::Color& colorText,
					 const unsigned short& charSize, const unsigned short& charLimit, const sf::Color& colorBg) :
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
	background.setPosition(x, y + this->getCharacterSize() / 7); 
	//move down the background one-seventh of the font size so that it matches the bottom of letters such as 'y' or 'p' or 'q'
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
	background.setSize(sf::Vector2f(this->getGlobalBounds().width + getCharacterSize() / 7, this->getCharacterSize()));
	// add one-seventh of the font size to the background width size to fit the italiñ style
}

void TextField::render(sf::RenderTarget& target) const
{
	target.draw(background);
	target.draw(*this);
}
