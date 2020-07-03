#include "TextField.h"

TextField::TextField(const sf::Font& font, const sf::Text::Style& style, const sf::Color& colorText,
	const unsigned short& charSize, const sf::Color& colorBg) :
	m_font(font),
	m_style(style),
	m_colorText(colorText),
	m_charSize(charSize),
	m_colorBg(colorBg)
{
	textVector.push_back(TextString(m_font, m_style, m_colorText, m_charSize, m_colorBg));
	activeStringNumber = 0;
}

unsigned short TextField::getCharacterSize()
{
	return m_charSize;
}

std::wstring TextField::getWString()
{
	return m_wString;
}

void TextField::render(sf::RenderTarget& target) const
{
	for (unsigned short i = 0; i <= activeStringNumber; i++)
	{
		textVector[i].render(target);
	}
}

void TextField::setPosition(float x, float y, unsigned short i)
{
	for (; i <= activeStringNumber; i++)
	{
		textVector[i].setPosition(x, y + (m_charSize * i));
	}
}

//void TextField::setWString(std::wstring wString)
//{
//
//}

void TextField::handleInput(const sf::Event &e, const unsigned short& winWidth, const unsigned short& winHight)
{
	if (e.text.unicode == 8)    // Delete key
	{
		if (textVector[activeStringNumber].getString().getSize() > 0)
		{
			textVector[activeStringNumber].handleInput(e);
			m_wString = m_wString.substr(0, m_wString.size() - 1);
		}
		else if (activeStringNumber > 0)
		{
			textVector.pop_back();
			activeStringNumber--;
			m_wString = m_wString.substr(0, m_wString.size() - 1);
			textVector[activeStringNumber].handleInput(e);
		}
	}
	else
	{
		if (textVector[activeStringNumber].getGlobalBounds().width + 10.f + m_charSize < winWidth)
		{
			textVector[activeStringNumber].handleInput(e);
			m_wString += e.text.unicode;
		}
		else
		{
			std::wstring editableWString = textVector[activeStringNumber].getString();
			std::wstring nextLineWString = L"";
			if (e.text.unicode == L' ')
			{
				m_wString += e.text.unicode;
				textVector[activeStringNumber].handleInput(e);
				textVector.push_back(TextString(m_font, m_style, m_colorText, m_charSize, m_colorBg));
				activeStringNumber++;
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
				textVector[activeStringNumber].setString(editableWString);
				textVector.push_back(TextString(m_font, m_style, m_colorText, m_charSize, m_colorBg));
				activeStringNumber++;
				textVector[activeStringNumber].setString(nextLineWString);
				textVector[activeStringNumber].handleInput(e);
				m_wString += e.text.unicode;
			}
			this->setPosition(textVector[0].getPosition().x, textVector[0].getPosition().y, activeStringNumber);
		}
	}
}

 