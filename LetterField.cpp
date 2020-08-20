#include "LetterField.h"

LetterField::LetterField(const TextParameter textParameter, const wchar_t letter):
m_colorMistakeBackground(textParameter.colorMistakeBackground),
m_letter(letter)
{
	setFont(textParameter.font);
	setFillColor(textParameter.colorText);
	setStyle(textParameter.style);
	setCharacterSize(textParameter.charSize);
	setString(m_letter);
	m_background.setFillColor(textParameter.colorCorrectBackground);
}

void LetterField::setPosition(float x, float y)
{
	this->sf::Transformable::setPosition(x, y);
	m_background.setPosition(x, y + this->getCharacterSize() / 7);
}

void LetterField::render(sf::RenderTarget& target)
{
	target.draw(m_background);
	target.draw(*this);
}

void LetterField::highlightMistake()
{
	m_background.setFillColor(m_colorMistakeBackground);
}

wchar_t LetterField::getLetter()
{
	return m_letter;
}

