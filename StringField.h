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
	unsigned short m_activeLetterNumber;
	std::wstring m_wstring;
	float m_x;
	float m_y;
	float m_width;
public:
	StringField(const TextParameter textParameter);
	void setPosition(float x, float y);
	void render(sf::RenderTarget& target);
	void charAppend(wchar_t& ch);
	void charDelete();
	float getWidth();
	float getX();
	float getY();
	std::wstring getWString();
};

