﻿#include "LetterField.h"
#define DEFAULT_OFFSET (getCharacterSize() / 7)
//shift the background by 1/7 so that the letters "p", "q", etc., do not go over the edge

LetterField::LetterField(const TextParameter textParameter, const wchar_t letter)
	: m_colorMistakeBackground(textParameter.colorMistakeBackground),
	m_letter(letter),
	sf::Text { "", *textParameter.font, textParameter.charSize }
{
	setFillColor(textParameter.colorText);
	setStyle(textParameter.style);
	setString(m_letter);
	if (m_letter == L' ')
		setCharacterSize(textParameter.charSize * 2); //increase the size of the spaces to improve the readability of the text
	m_background.setFillColor(textParameter.colorCorrectBackground);
}

void LetterField::setPosition(float x, float y)
{
	this->sf::Transformable::setPosition(x, y);
	if (m_letter != L' ')
		m_background.setSize(sf::Vector2f(this->getGlobalBounds().width + DEFAULT_OFFSET, this->getCharacterSize()));
	else //change the display of the space
		m_background.setSize(sf::Vector2f(this->getGlobalBounds().width + DEFAULT_OFFSET / 2, this->getCharacterSize() / 2.8));
	m_background.setPosition(x, y + DEFAULT_OFFSET);
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

