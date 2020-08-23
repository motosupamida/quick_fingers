#pragma once

#include <sfml/graphics.hpp>

struct TextParameter
{
	std::shared_ptr<sf::Font> font;
	sf::Text::Style style = sf::Text::Style::Regular;
	sf::Color colorText = sf::Color::White;
	unsigned short charSize = 36u;
	sf::Color neutralColor = sf::Color(33, 33, 33);
	sf::Color mistakeColor = sf::Color(100, 0, 0);
	sf::Color correctColor = sf::Color(0, 100, 0);
};