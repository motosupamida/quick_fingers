#pragma once

#include <iostream>
#include <sfml/graphics.hpp>

class KeyboardVisualizer
{
public:
	enum class State
	{
		DISABLE,
		ENABLE
	};
	KeyboardVisualizer();
	void render(sf::RenderTarget& target);
	void setPosition(float x, float y);
	void setState(State state, short keycode);
	float getX();
	float getY();
	float getHeight();
	float getWidth();


	/* void setKeyboardLayout(unsigned short keycode); DEBUG
	void getKeyboardLayout(); DEBUG */

private:
	const sf::Color m_disableColor = sf::Color(255,255,255,20);
	const sf::Color m_enableColor = sf::Color(255,255,255,70);
	float m_x = 0;
	float m_y = 0;
	float m_keySize = 40;
	float m_distanceBetweenButtons = 4;
	sf::RectangleShape m_keys[107];
	//use '-1' for empty elements and like a '\n' in strings, becase '0' using for 'A' keycode.
	const short m_layoutOrderOfButtons[5][15] = {
	{54, 27, 28, 29, 30, 31, 32, 33, 34, 35, 26, 56, 55, 59, -1},
	{60, 16, 22, 4, 17, 19, 24, 20, 8, 14, 15, 46, 47, 53, -1},
	{100, 0, 18, 3, 5, 6, 7, 9, 10, 11, 48, 51, 58, -1, -1},
	{38, 25, 23, 2, 21, 1, 13, 12, 49, 50, 52, 42, -1, -1, -1},
	{37, 40, 39, 57, 43, 44, 45, 41, -1, -1, -1, -1, -1, -1, -1}};



	/*short m_lastKeycode = -1; DEBUG
	std::string m_keyboardLayout = ""; DEBUG*/
};

