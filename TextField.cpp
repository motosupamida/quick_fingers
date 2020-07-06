#include "TextField.h"

#define textOptions m_font, m_style, m_colorText, m_charSize, m_colorBg

TextField::TextField(const sf::Font& font, const sf::Text::Style& style, const sf::Color& colorText,
	const unsigned short& charSize, const sf::Color& colorBg) :
	m_font(font),
	m_style(style),
	m_colorText(colorText),
	m_charSize(charSize),
	m_colorBg(colorBg)
{
	m_textVector.push_back(TextString(textOptions));
	m_activeStringNumber = 0;
}

unsigned short TextField::getCharacterSize()
{
	return m_charSize;
}

unsigned short TextField::getHeight()
{
	return m_textVector[m_activeStringNumber].getGlobalBounds().top + m_charSize;
}

unsigned short TextField::getWidth()
{
	return m_textVector[0].getGlobalBounds().width;
}

std::wstring TextField::getWString()
{
	return m_wString;
}

void TextField::render(sf::RenderTarget& target) const
{
	for (unsigned short i = 0; i <= m_activeStringNumber; i++)
	{
		m_textVector[i].render(target);
	}
}

void TextField::setWString(const std::wstring& wString, const unsigned short& winWidth, const unsigned short& winHight)
{
	while (m_activeStringNumber > 0)
	{
		m_textVector.pop_back();
		m_activeStringNumber--;
	}
	m_textVector.pop_back();
	m_textVector.push_back(TextString(textOptions));
	m_activeStringNumber = 0;
	for (unsigned short i = 0; i <= wString.length(); i++)
	{
		wchar_t ch = wString[i];
		if (m_textVector[m_activeStringNumber].getGlobalBounds().width + 10.f + m_charSize < winWidth)
		{
			m_textVector[m_activeStringNumber].charAppend(ch);
			m_textVector[m_activeStringNumber].correctBackground();
			m_wString += ch;
		}
		else
		{
			std::wstring editableWString = m_textVector[m_activeStringNumber].getString();
			std::wstring nextLineWString = L"";
			if (ch == L' ')
			{
				m_textVector[m_activeStringNumber].charAppend(ch);
				m_textVector[m_activeStringNumber].correctBackground();
				m_wString += ch;
				m_textVector.push_back(TextString(textOptions));
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
				m_textVector[m_activeStringNumber].setString(editableWString);
				m_textVector[m_activeStringNumber].correctBackground();
				m_textVector.push_back(TextString(textOptions));
				m_activeStringNumber++;
				m_textVector[m_activeStringNumber].setString(nextLineWString);
				m_textVector[m_activeStringNumber].charAppend(ch);
				m_textVector[m_activeStringNumber].correctBackground();
				m_wString += ch;
			}
			this->setPosition(m_textVector[0].getPosition().x, m_textVector[0].getPosition().y, m_activeStringNumber);
		}
	}
}

void TextField::setPosition(float x, float y, unsigned short i)
{
	for (; i <= m_activeStringNumber; i++)
	{
		m_textVector[i].setPosition(x, y + (m_charSize * i));
	}
}

void TextField::handleInput(const sf::Event &e, const unsigned short& winWidth, const unsigned short& winHight)
{
	if (e.text.unicode == 13 || e.text.unicode == 9 || e.text.unicode == 27)
	{
		return; //ignore Tab, Enter, Esc buttons
	}
	if (e.text.unicode == 8)    // Delete key
	{
		if (m_textVector[m_activeStringNumber].getString().getSize() > 0)
		{
			m_textVector[m_activeStringNumber].handleInput(e);
			m_textVector[m_activeStringNumber].correctBackground();
			m_wString = m_wString.substr(0, m_wString.size() - 1);
		}
		else if (m_activeStringNumber > 0)
		{
			m_textVector.pop_back();
			m_activeStringNumber--;
			m_wString = m_wString.substr(0, m_wString.size() - 1);
			m_textVector[m_activeStringNumber].handleInput(e);
			m_textVector[m_activeStringNumber].correctBackground();
		}
	}
	else
	{
		if (m_textVector[m_activeStringNumber].getGlobalBounds().width + m_charSize * 2 < winWidth)
		{
			m_textVector[m_activeStringNumber].handleInput(e);
			m_textVector[m_activeStringNumber].correctBackground();
			m_wString += e.text.unicode;
		}
		else
		{
			std::wstring editableWString = m_textVector[m_activeStringNumber].getString();
			std::wstring nextLineWString = L"";
			if (e.text.unicode == L' ')
			{
				m_wString += e.text.unicode;
				m_textVector[m_activeStringNumber].handleInput(e);
				m_textVector[m_activeStringNumber].correctBackground();
				m_textVector.push_back(TextString(textOptions));
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
				m_textVector[m_activeStringNumber].setString(editableWString);
				m_textVector[m_activeStringNumber].correctBackground();
				m_textVector.push_back(TextString(textOptions));
				m_activeStringNumber++;
				m_textVector[m_activeStringNumber].setString(nextLineWString);
				m_textVector[m_activeStringNumber].handleInput(e);
				m_textVector[m_activeStringNumber].correctBackground();
				m_wString += e.text.unicode;
			}
			this->setPosition(m_textVector[0].getPosition().x, m_textVector[0].getPosition().y, m_activeStringNumber);
		}
	}
}

 