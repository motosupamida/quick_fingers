#pragma once

#include <sfml/graphics.hpp>

struct TextParameter
{
	std::shared_ptr<sf::Font> font;
	sf::Text::Style style = sf::Text::Style::Regular;
	sf::Color colorText = sf::Color::White;
	unsigned short charSize = 36u;
	sf::Color colorCorrectBackground = sf::Color(35, 35, 35);
	sf::Color colorMistakeBackground = sf::Color(100, 0, 0);
};