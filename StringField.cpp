#include "StringField.h"

StringField::StringField(const TextParameter textParameter) :
	m_textParameter (textParameter),
	m_activeLetterNumber(-1),//no letters at the time of creation
	m_x(0.0),
	m_y(0.0)
{
}

void StringField::charAppend(wchar_t& ch)
{
	if ((ch != L'\0') && (ch != L'\n'))
	{
		m_wstring += ch;
		m_vectorOfLetters.push_back(LetterField(m_textParameter, ch));
		m_activeLetterNumber++;
		this->setPosition(m_x, m_y, m_activeLetterNumber);

	}
}

void StringField::charDelete()
{
	m_vectorOfLetters.pop_back();
	m_activeLetterNumber--;
}

float StringField::getWidth()
{
	if (m_activeLetterNumber < 0)//return zero width if there are no letters
		return 0.f;
	else
		return m_vectorOfLetters[m_activeLetterNumber].getGlobalBounds().left + m_vectorOfLetters[m_activeLetterNumber].getGlobalBounds().width - m_x;
}

float StringField::getX()
{
	return m_x;
}

float StringField::getY()
{
	return m_y;
}

std::wstring StringField::getWString()
{
	return m_wstring;
}

void StringField::setPosition(float x, float y, unsigned short i)
{
	m_x = x;
	m_y = y;

	for (; i < m_vectorOfLetters.size(); i++)
	{
		if (!i)
			m_vectorOfLetters[i].setPosition(x, y);
		else
			m_vectorOfLetters[i].setPosition(m_vectorOfLetters[i-1].getGlobalBounds().left + m_vectorOfLetters[i-1].getGlobalBounds().width, y);
	}
}

void StringField::render(sf::RenderTarget& target)
{
	for (unsigned short i = 0; i < m_activeLetterNumber; i++)
	{
		m_vectorOfLetters[i].render(target);
	}
}