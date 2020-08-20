#pragma once

#include <iostream>
#include <sfml/graphics.hpp>
#include "TextField.h"
#include "TextGenerator.h"
#include "TextParameter.h"

class QuickFingersCore
{
private:
	TextParameter m_textParameter;
	sf::RenderWindow* m_window;
	bool challengeDone(TextField& taskText, TextField& enteredText);
	bool mistakeCheck(TextField& taskText, TextField& enteredText);
public:
	QuickFingersCore(unsigned short windowWidth = 800, unsigned short windowHight = 800);
	~QuickFingersCore();
	void core();
};

