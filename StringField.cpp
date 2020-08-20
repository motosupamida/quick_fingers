#include "StringField.h"

StringField::StringField(const TextParameter textParameter) :
	m_textParameter (textParameter),
	m_activeLetterNumber(0),
	m_x(0.0),
	m_y(0.0),
	m_width(0.0)
{
}

void StringField::charAppend(wchar_t& ch)
{
	if ((ch != L'\0') && (ch != L'\n'))
	{
		m_activeLetterNumber++;
		m_wstring += ch;
		m_vectorOfLetters.push_back(LetterField(m_textParameter, ch));
		m_width += m_textParameter.charSize;		
	}
}

void StringField::charDelete()
{
	m_vectorOfLetters.pop_back();
	m_activeLetterNumber--;
	m_width -= m_textParameter.charSize;
}

float StringField::getWidth()
{
	return (m_x + (m_activeLetterNumber * m_textParameter.charSize));
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

void StringField::setPosition(float x, float y)
{
	m_x = x;
	m_y = y;
	for (unsigned short i = 0; i < m_activeLetterNumber; i++)
	{
		m_vectorOfLetters[i].setPosition(x, y + (m_textParameter.charSize * i));
	}
}

void StringField::render(sf::RenderTarget& target)
{
	for (unsigned short i = 0; i <= m_activeLetterNumber; i++)
	{
		m_vectorOfLetters[i].render(target);
	}
}