#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <iomanip> 
#include <sfml/graphics.hpp>
#include "TextField.h"
#include "TextGenerator.h"
#include "TextParameter.h"
#include "KeyboardVisualizer.h"

class QuickFingersCore
{
public:
	QuickFingersCore();
	~QuickFingersCore();
	void start();
private:
	void startScreen();
	void countdownScreen(const unsigned short time, const TextGenerator::Language language);
	TextGenerator::GenerationType selectGenerationType();
	TextGenerator::Language selectLanguage();
	TextParameter m_textParameter;
	sf::RenderWindow* m_window;
	std::map<std::string, std::shared_ptr<sf::Font>> m_supportedFonts;
};

