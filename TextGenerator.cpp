#include "TextGenerator.h"


std::wstring TextGenerator::getRandomText(const unsigned short stringSize)
{
    srand(time(NULL));
    std::wstring result = L"";
    for (unsigned short i = 0; i < stringSize; i++)
    {
        //std::cout << (160 + rand() % 85) << "  ";
        result += (160 + rand() % 85);
    }
    return result;
}
