#include "KeyboardVisualizer.h"

#define KEYBOARD_SIZE 107
#define INVISIBLE sf::Color(0, 0, 0, 0)

/*
void KeyboardVisualizer::setKeyboardLayout(unsigned short keycode)
{
	if (m_lastKeycode == keycode)
	{
		m_keyboardLayout += "\n";
	}
	else
	{
		m_keyboardLayout += (std::to_string(keycode));
		m_keyboardLayout += ", ";
		m_lastKeycode = keycode;
	}
}

void KeyboardVisualizer::getKeyboardLayout()
{
	std::cout << m_keyboardLayout;
}
*/ //DEBUG

KeyboardVisualizer::KeyboardVisualizer()
{
	for (short i = 0; i < KEYBOARD_SIZE; i++)
	{
		m_keys[i].setFillColor(INVISIBLE);
	}
	for (unsigned short string = 0; string < 5; string++)
	{
		for (unsigned short i = 0; m_layoutOrderOfButtons[string][i] >= 0; i++)
		{
			m_keys[m_layoutOrderOfButtons[string][i]].setSize(sf::Vector2f(m_keySize, m_keySize));
			m_keys[m_layoutOrderOfButtons[string][i]].setFillColor(m_disableColor);
		}
	}
	//x-axis scaling
	m_keys[59].setSize(sf::Vector2f(m_keySize * 2, m_keySize));//backspace
	m_keys[60].setSize(sf::Vector2f(m_keySize * 1.5, m_keySize));//tab
	m_keys[53].setSize(sf::Vector2f(m_keySize * 1.5, m_keySize));//slash
	m_keys[100].setSize(sf::Vector2f(m_keySize * 1.8, m_keySize));//capslock
	m_keys[58].setSize(sf::Vector2f(m_keySize * 2.3, m_keySize));//enter
	m_keys[38].setSize(sf::Vector2f(m_keySize * 2.6, m_keySize));//left shift
	m_keys[42].setSize(sf::Vector2f(m_keySize * 2.6, m_keySize));//right shifl
	m_keys[37].setSize(sf::Vector2f(m_keySize * 1.5, m_keySize));//left ctrl
	m_keys[39].setSize(sf::Vector2f(m_keySize * 1.2, m_keySize));//left alt
	m_keys[57].setSize(sf::Vector2f(m_keySize * 7.4, m_keySize));//space
	m_keys[43].setSize(sf::Vector2f(m_keySize * 1.2, m_keySize));//right alt
	m_keys[41].setSize(sf::Vector2f(m_keySize * 1.3, m_keySize));//right ctrl
}

void KeyboardVisualizer::render(sf::RenderTarget& target)
{
	for (unsigned short i = 0; i < KEYBOARD_SIZE; i++)
	{
		target.draw(m_keys[i]);
	}
}

void KeyboardVisualizer::setPosition(float x, float y)
{
	m_x = x;
	m_y = y;
	//m_keys[m_layoutOrderOfButtons[0][0]].setPosition(x, y);
	for (unsigned short string = 0; string < 5; string++)
	{
		for (unsigned short i = 0; m_layoutOrderOfButtons[string][i] >= 0; i++)
		{
			if (i == 0)
			{
				if (string == 0)
				{
					m_keys[m_layoutOrderOfButtons[string][i]].setPosition(x, y);
				}
				else
				{
					m_keys[m_layoutOrderOfButtons[string][i]].setPosition(x, m_keys[m_layoutOrderOfButtons[string - 1][i]].getGlobalBounds().top + m_keySize + m_distanceBetweenButtons);
				}
			}
			else
				m_keys[m_layoutOrderOfButtons[string][i]].setPosition(m_keys[m_layoutOrderOfButtons[string][i - 1]].getGlobalBounds().left + m_keys[m_layoutOrderOfButtons[string][i - 1]].getGlobalBounds().width + m_distanceBetweenButtons, m_keys[m_layoutOrderOfButtons[string][i - 1]].getGlobalBounds().top);
		}
	}
}

void KeyboardVisualizer::setState(State state, short keycode)
{
	switch (keycode)
	{
	case -1://ignore invalid keycodes.
	case 40://ignore left system button
	case 44://ignore right system button
		return;
	}
	if (state == State::ENABLE)
		m_keys[keycode].setFillColor(m_enableColor);
	else
		m_keys[keycode].setFillColor(m_disableColor);
}

float KeyboardVisualizer::getX()
{
	return m_x;
}

float KeyboardVisualizer::getY()
{
	return m_y;
}

float KeyboardVisualizer::getHeight()
{
	return ((m_keys[41].getGlobalBounds().top + m_keys[41].getGlobalBounds().height) - m_y);
}

float KeyboardVisualizer::getWidth()
{
	return ((m_keys[41].getGlobalBounds().left + m_keys[41].getGlobalBounds().width) - m_x);
}



