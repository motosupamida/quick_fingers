#pragma once

#include <iostream>
#include <sfml/graphics.hpp>
#include "StringField.h"
#include "TextParameter.h"

class TextField : public sf::RectangleShape
{
public:
	bool checkMistakes();
	TextField(TextParameter textParameter);
	unsigned short getCharacterSize();
	unsigned short getCorrections();
	unsigned short getValidLetters();
	float getHeight();
	float getWidth();
	float getX();
	float getY();
	std::wstring getWString();
	void setPosition(float x, float y);
	void handleInput(const sf::Event& e, const unsigned short& winWidth, const unsigned short& winHigth);
	void render(sf::RenderTarget& target);
	void setWString(const std::wstring& wString, const unsigned short& winWidth = 800, const unsigned short& winHight = 800);
	void setState(LetterField::State state);
private:
	unsigned short m_validLetters;
	unsigned short m_corrections;
	unsigned short m_inputString;
	unsigned short m_inputLetter;
	TextParameter m_textParameter;
	std::wstring m_wString;
	std::vector<StringField> m_vectorOfStrings;
	unsigned short m_activeStringNumber;
	float m_x;
	float m_y;
	void vectorWStringAppend(std::wstring string);

};	