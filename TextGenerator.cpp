#include "TextGenerator.h"


std::wstring TextGenerator::getRandomText(const unsigned short stringSize)
{
    srand(time(NULL));
    std::wstring result = L"";
    for (unsigned short i = 0; i < stringSize; i++)
    {
        result += (160 + rand() % 85);
    }
    //return result;
    return L"Тестовый текст";
}

std::wstring TextGenerator::getTextFromFile()
{
    std::wstring result = L"";

    //return result;
    return L"Тестовый текст";
}
