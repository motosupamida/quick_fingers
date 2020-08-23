#pragma once

#include <iostream>
#include <sfml/graphics.hpp>
#include "TextParameter.h"
#include "LetterField.h"

class StringField
{
public:
	StringField(const TextParameter textParameter);
	void setPosition(float x, float y, unsigned short i = 0);
	void render(sf::RenderTarget& target);
	void charAppend(const wchar_t& ch);
	void charDelete();
	void setLetterState(const unsigned short& number, LetterField::State state);
	LetterField::State getLetterState(const unsigned short& number);
	unsigned short getSize();
	float getWidth();
	float getX();
	float getY();
	wchar_t getChar(const unsigned short& number);
	std::wstring getWString();
private:
	TextParameter m_textParameter;
	std::vector<LetterField> m_vectorOfLetters;
	short m_activeLetterNumber;
	std::wstring m_wstring;
	float m_x;
	float m_y;

};

