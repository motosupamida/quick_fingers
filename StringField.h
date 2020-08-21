#pragma once

#include <iostream>
#include <sfml/graphics.hpp>
#include "TextParameter.h"
#include "LetterField.h"

class StringField
{
private:
	TextParameter m_textParameter;
	std::vector<LetterField> m_vectorOfLetters;
	short m_activeLetterNumber;
	std::wstring m_wstring;
	float m_x;
	float m_y;
public:
	StringField(const TextParameter textParameter);
	void setPosition(float x, float y, unsigned short i = 0);
	void render(sf::RenderTarget& target);
	void charAppend(wchar_t& ch);
	void charDelete();
	float getWidth();
	float getX();
	float getY();
	std::wstring getWString();
};

