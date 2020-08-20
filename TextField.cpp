#include "TextField.h"

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
	m_y(0.0)
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
	return (m_x + ((m_activeStringNumber + 1) * m_textParameter.charSize));
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

/* to do */void TextField::setWString(const std::wstring& wString, const unsigned short& winWidth, const unsigned short& winHight)
{
	while (m_activeStringNumber > 0)
	{
		m_vectorOfStrings.pop_back();
		m_activeStringNumber--;
	}
	m_vectorOfStrings.pop_back();
	m_vectorOfStrings.push_back(StringField(m_textParameter));
	m_activeStringNumber = 0;
	for (unsigned short i = 0; i <= wString.length(); i++)
	{
		wchar_t ch = wString[i];
		if (m_vectorOfStrings[m_activeStringNumber].getWidth() + 2 * m_textParameter.charSize < winWidth)
		{
			m_vectorOfStrings[m_activeStringNumber].charAppend(ch);
			//m_vectorOfStrings[m_activeStringNumber].correctBackground();
			m_wString += ch;
		}
		else
		{
			std::wstring editableWString = m_vectorOfStrings[m_activeStringNumber].getWString();
			std::wstring nextLineWString = L"";
			if (ch == L' ')
			{
				m_vectorOfStrings[m_activeStringNumber].charAppend(ch);
				//m_vectorOfStrings[m_activeStringNumber].correctBackground();
				m_wString += ch;
				m_vectorOfStrings.push_back(StringField(m_textParameter));
				m_activeStringNumber++;
			}
			else
			{
				for (unsigned short i = editableWString.length(); i > 0; --i)
				{
					if (editableWString[i] == ' ')
					{
						nextLineWString.append(editableWString, i + 1, editableWString.length());
						editableWString.erase(i + 1, editableWString.length());
						break;
					}
				}
				vectorWStringAppend(editableWString);
				//m_vectorOfStrings[m_activeStringNumber].correctBackground();
				m_vectorOfStrings.push_back(StringField(m_textParameter));
				m_activeStringNumber++;
				vectorWStringAppend(nextLineWString);
				m_vectorOfStrings[m_activeStringNumber].charAppend(ch);
				//m_vectorOfStrings[m_activeStringNumber].correctBackground();
				m_wString += ch;
			}
			this->setPosition(m_vectorOfStrings[0].getX(), m_vectorOfStrings[0].getY());
		}
	}
}

void TextField::setPosition(float x, float y)
{
	for (unsigned short i = 0; i <= m_activeStringNumber; i++)
	{
		m_vectorOfStrings[i].setPosition(x, y + (m_textParameter.charSize * i));
	}
}

/* to do void TextField::handleInput(const sf::Event &e, const unsigned short& winWidth, const unsigned short& winHight)
{
	if (e.text.unicode == 13 || e.text.unicode == 9 || e.text.unicode == 27)
	{
		return; //ignore Tab, Enter, Esc buttons
	}
	if (e.text.unicode == 8)    // Delete key
	{
		if (m_vectorOfStrings[m_activeStringNumber].getWString().length() > 0)
		{
			//m_vectorOfStrings[m_activeStringNumber].handleInput(e);
			m_vectorOfStrings[m_activeStringNumber].charAppend(static_cast<wchar_t>(e.text.unicode));
			//m_vectorOfStrings[m_activeStringNumber].correctBackground();
			m_wString = m_wString.substr(0, m_wString.size() - 1);
		}
		else if (m_activeStringNumber > 0)
		{
			m_vectorOfStrings.pop_back();
			m_activeStringNumber--;
			m_wString = m_wString.substr(0, m_wString.size() - 1);
			//m_vectorOfStrings[m_activeStringNumber].handleInput(e);
			m_vectorOfStrings[m_activeStringNumber].charAppend(static_cast<wchar_t>(e.text.unicode));
			//m_vectorOfStrings[m_activeStringNumber].correctBackground();
		}
	}
	else
	{
		if (m_vectorOfStrings[m_activeStringNumber].getGlobalBounds().width + m_charSize * 2 < winWidth)
		{
			m_vectorOfStrings[m_activeStringNumber].handleInput(e);
			m_vectorOfStrings[m_activeStringNumber].correctBackground();
			m_wString += e.text.unicode;
		}
		else
		{
			std::wstring editableWString = m_vectorOfStrings[m_activeStringNumber].getString();
			std::wstring nextLineWString = L"";
			if (e.text.unicode == L' ')
			{
				m_wString += e.text.unicode;
				m_vectorOfStrings[m_activeStringNumber].handleInput(e);
				m_vectorOfStrings[m_activeStringNumber].correctBackground();
				m_vectorOfStrings.push_back(TextString(m_textParameter));
				m_activeStringNumber++;
			}
			else
			{
				for (unsigned short i = editableWString.length(); i > 0; --i)
				{
					if (editableWString[i] == ' ')
					{
						nextLineWString.append(editableWString, i + 1, editableWString.length());
						editableWString.erase(i+1, editableWString.length());
						break;
					}
				}
				m_vectorOfStrings[m_activeStringNumber].setString(editableWString);
				m_vectorOfStrings[m_activeStringNumber].correctBackground();
				m_vectorOfStrings.push_back(TextString(m_textParameter));
				m_activeStringNumber++;
				m_vectorOfStrings[m_activeStringNumber].setString(nextLineWString);
				m_vectorOfStrings[m_activeStringNumber].handleInput(e);
				m_vectorOfStrings[m_activeStringNumber].correctBackground();
				m_wString += e.text.unicode;
			}
			this->setPosition(m_vectorOfStrings[0].getPosition().x, m_vectorOfStrings[0].getPosition().y, m_activeStringNumber);
		}
	}
}
*/
 