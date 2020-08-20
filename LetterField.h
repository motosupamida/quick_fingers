#pragma once

#include <iostream>
#include <sfml/graphics.hpp>
#include "TextParameter.h"


class LetterField : public sf::Text
{
private:
	sf::RectangleShape m_background;
	sf::Color m_colorMistakeBackground;
	wchar_t m_letter;
public:
	LetterField(const TextParameter textParameter, const wchar_t letter);
	void setPosition(float x, float y);
	void render(sf::RenderTarget& target);
	void highlightMistake();
	wchar_t getLetter();
};