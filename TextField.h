#pragma once

#include <iostream>
#include <sfml/graphics.hpp>
#include "StringField.h"
#include "TextParameter.h"

class TextField : public sf::RectangleShape
{
private:
	TextParameter m_textParameter;
	std::wstring m_wString;
	std::vector<StringField> m_vectorOfStrings;
	unsigned short m_activeStringNumber;
	float m_x;
	float m_y;
	void vectorWStringAppend(std::wstring string);
public:
	TextField(TextParameter textParameter);
	unsigned short getCharacterSize();
	float getHeight();
	float getWidth();
	float getX();
	float getY();
	std::wstring getWString();
	void setPosition(float x, float y);
	void handleInput(const sf::Event &e, const unsigned short& winWidth, const unsigned short& winHigth);
	void render(sf::RenderTarget& target);
	void setWString(const std::wstring& wString, const unsigned short& winWidth, const unsigned short& winHight);
};	