#include "TextField.h"
#define DEFAULT_INTERLIGNE 1.3
#define DELETE_KEY 8


void TextField::vectorWStringAppend(std::wstring string)
{
	for (unsigned short i = 0; i < string.length(); i++)
	{
		m_vectorOfStrings[m_activeStringNumber].charAppend(string[i]);
	}
}

TextField::TextField(TextParameter textParameter) :
	m_textParameter(textParameter),
	m_x(0.0),
	m_y(0.0),
	m_inputString(0u),
	m_inputLetter(0u)
{
	m_vectorOfStrings.push_back(StringField(m_textParameter));
	m_activeStringNumber = 0;
}

unsigned short TextField::getCharacterSize()
{
	return m_textParameter.charSize;
}

float TextField::getHeight()
{
	return m_vectorOfStrings[m_activeStringNumber].getY() + m_textParameter.charSize;
}

float TextField::getWidth()
{
	return m_vectorOfStrings[0].getWidth();
}

float TextField::getX()
{
	return m_x;
}

float TextField::getY()
{
	return m_y;
}

std::wstring TextField::getWString()
{
	return m_wString;
}

void TextField::render(sf::RenderTarget& target) 
{
	for (unsigned short i = 0; i <= m_activeStringNumber; i++)
	{
		m_vectorOfStrings[i].render(target);
	}
}

void TextField::setWString(const std::wstring& wString, const unsigned short& winWidth, const unsigned short& winHight)
{
	while (m_activeStringNumber > 0)
	{
		m_vectorOfStrings.pop_back();
		m_activeStringNumber--;
	}
	m_vectorOfStrings.pop_back();
	m_vectorOfStrings.push_back(StringField(m_textParameter));
	for (unsigned short i = 0; i <= wString.length(); i++)
	{
		wchar_t ch = wString[i];
		if (m_vectorOfStrings[m_activeStringNumber].getWidth() + m_textParameter.charSize * 2< winWidth)
		{
			m_vectorOfStrings[m_activeStringNumber].charAppend(ch);
			m_wString += ch;
		}
		else
		{
			std::wstring editableWString = m_vectorOfStrings[m_activeStringNumber].getWString();
			std::wstring nextLineWString = L"";
			if (ch == L' ')
			{
				m_vectorOfStrings[m_activeStringNumber].charAppend(ch);
				m_wString += ch;
				m_vectorOfStrings.push_back(StringField(m_textParameter));
				m_activeStringNumber++;
			}
			else
			{
				for (unsigned short i = editableWString.length(); i > 0; --i)
				{
					if (editableWString[i-1] == L' ')
					{
						nextLineWString.append(editableWString, i, editableWString.length());
						break;
					}
					m_vectorOfStrings[m_activeStringNumber].charDelete();
				}
				m_vectorOfStrings.push_back(StringField(m_textParameter));
				m_activeStringNumber++;
				vectorWStringAppend(nextLineWString);
				m_vectorOfStrings[m_activeStringNumber].charAppend(ch);
				m_wString += ch;
			}
		}
	}
}

void TextField::setPosition(float x, float y)
{
	m_x = x;
	m_y = y;
	for (unsigned short i = 0; i <= m_activeStringNumber; i++)
	{
		m_vectorOfStrings[i].setPosition(x, y + i * (m_textParameter.charSize * DEFAULT_INTERLIGNE));
	}
}

void TextField::handleInput(const sf::Event &e, const unsigned short& winWidth, const unsigned short& winHight)
{
	if (e.text.unicode == 13 || e.text.unicode == 9 || e.text.unicode == 27)
	{
		return; //ignore Tab, Enter, Esc buttons
	}
	if (e.text.unicode == DELETE_KEY)
	{
		if ((m_inputString == 0) && (m_inputLetter == 0))
		{
			m_vectorOfStrings[m_inputString].setLetterState(m_inputLetter, LetterField::State::NEUTRAL);
			return;
		}
		if (m_inputLetter > 0)
		{
			m_inputLetter--;
			m_vectorOfStrings[m_inputString].setLetterState(m_inputLetter, LetterField::State::NEUTRAL);

		}
		else
		{
			m_inputString--;
			m_inputLetter = m_vectorOfStrings[m_inputString].getSize();
			m_vectorOfStrings[m_inputString].setLetterState(m_inputLetter, LetterField::State::NEUTRAL);
		}
	}
	else
	{
		if ((m_inputString == m_activeStringNumber) && (m_inputLetter > m_vectorOfStrings[m_inputString].getSize()))
			return;//end of string, no more letters	

		if (m_inputLetter > m_vectorOfStrings[m_inputString].getSize())
		{
			m_inputString++;
			m_inputLetter = 0;
		}
		if (static_cast<wchar_t>(e.text.unicode) == m_vectorOfStrings[m_inputString].getChar(m_inputLetter))
		{
			m_vectorOfStrings[m_inputString].setLetterState(m_inputLetter, LetterField::State::CORRECT);
			m_inputLetter++;
		}
		else
		{
			m_vectorOfStrings[m_inputString].setLetterState(m_inputLetter, LetterField::State::MISTAKE);
			m_inputLetter++;
		}
	}
}

 