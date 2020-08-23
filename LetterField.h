#pragma once

#include <iostream>
#include <sfml/graphics.hpp>
#include "TextParameter.h"


class LetterField : public sf::Text
{
public:
	enum class State
	{
	NEUTRAL,
	MISTAKE,
	CORRECT
	};
	LetterField(const TextParameter textParameter, const wchar_t letter);
	void setPosition(float x, float y);
	void render(sf::RenderTarget& target);
	void setState(static State &state);
	State getState();
	wchar_t getChar();
private:
	sf::RectangleShape m_background;
	sf::Color m_neutralColor;
	sf::Color m_mistakeColor;
	sf::Color m_correctColor;
	wchar_t m_letter;
	State m_state;
};