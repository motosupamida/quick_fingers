#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

class TextGenerator
{	
private:

public:
	static std::wstring getRandomText(const unsigned short = 0, const unsigned short stringSize = 10u, const unsigned short spaceRate = 0u);
	static std::wstring getTextFromFile();
};

