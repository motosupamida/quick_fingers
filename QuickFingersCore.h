#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <sfml/graphics.hpp>
#include "TextField.h"
#include "TextGenerator.h"
#include "TextParameter.h"
#include "KeyboardVisualizer.h"

class QuickFingersCore
{
public:
	QuickFingersCore(unsigned short windowWidth = 800, unsigned short windowHight = 800);
	~QuickFingersCore();
	void core();
private:
	bool stop;
	TextParameter m_textParameter;
	sf::RenderWindow* m_window;
	sf::Clock m_timer;
	float m_deltaTime;
	float m_elapsedTime;
	std::map<std::string, std::shared_ptr<sf::Font>> m_supportedFonts;
};

