#include "LetterField.h"
#define DEFAULT_OFFSET (getCharacterSize() / 7)
//shift the background by 1/7 so that the letters "p", "q", etc., do not go over the edge

LetterField::LetterField(const TextParameter textParameter, const wchar_t letter)
	: m_neutralColor(textParameter.neutralColor),
	m_correctColor(textParameter.correctColor),
	m_mistakeColor(textParameter.mistakeColor),
	m_letter(letter),
	sf::Text { "", *textParameter.font, textParameter.charSize }
{
	setFillColor(textParameter.colorText);
	setStyle(textParameter.style);
	setString(letter);
	if (m_letter == L' ')
		setCharacterSize(textParameter.charSize * 2); //increase the size of the spaces to improve the readability of the text
	m_background.setFillColor(textParameter.neutralColor);
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

void LetterField::setState(State& state)
{
	m_state = state;
	switch (state)
	{
	case LetterField::State::NEUTRAL: m_background.setFillColor(m_neutralColor);
		break;
	case LetterField::State::MISTAKE: m_background.setFillColor(m_mistakeColor);
		break;
	case LetterField::State::CORRECT: m_background.setFillColor(m_correctColor);
		break;
	}
}

LetterField::State LetterField::getState()
{
	return m_state;
}

wchar_t LetterField::getChar()
{
	return m_letter;
}

