#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>

class TextGenerator
{	
private:

public:
	static std::wstring getRandomText(const unsigned short stringSize = 30u);
};

