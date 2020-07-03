#pragma once

#include <iostream>
#include <sfml/graphics.hpp>
#include "TextField.h"
#include "TextGenerator.h"

class QuickFingersCore
{
private:
	sf::RenderWindow* m_window;
public:
	QuickFingersCore(unsigned short windowWidth = 800, unsigned short windowHight = 800);
	~QuickFingersCore();
	void core();
};

