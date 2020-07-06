#include "TextString.h"

TextString::TextString(const sf::Font& font, const sf::Text::Style& style, const sf::Color& colorText,
	const unsigned short& charSize, const sf::Color& colorBg)
{
	setFont(font);
	setFillColor(colorText);
	setStyle(style);
	this->setCharacterSize(charSize);
	m_background.setFillColor(colorBg);
}

void TextString::charAppend(wchar_t ch)
{
	if ((ch != L'\0') && (ch != L'\n'))
		setString(static_cast<std::wstring>(getString()) + ch);
}

void TextString::setPosition(float x, float y)
{
	sf::Transformable::setPosition(x, y);
	m_background.setPosition(x, y + this->getCharacterSize() / 7);
	//move down the background one-seventh of the font size so that it matches the bottom of letters such as 'y' or 'p' or 'q'
}

void TextString::handleInput(const sf::Event& e)
{
	std::wstring str = static_cast<std::wstring>(getString());
	if (e.text.unicode == 8)    // Delete key
	{
		setString(str.substr(0, (str.length() - 1)));
	}
	else
	{
		setString(str + static_cast<wchar_t>(e.text.unicode));
	}
}

void TextString::correctBackground()
{
	m_background.setSize(sf::Vector2f(this->getGlobalBounds().width + getCharacterSize() / 7, this->getCharacterSize()));
	// add one-seventh of the font size to the background width size to fit the italiñ style
}

void TextString::render(sf::RenderTarget& target) const
{
	target.draw(m_background);
	target.draw(*this);
}

