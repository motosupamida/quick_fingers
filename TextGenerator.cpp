#include "TextGenerator.h"

std::wstring TextGenerator::getRandomText(const unsigned short language, const unsigned short stringSize, const unsigned short spaceRate)
{
    /*
    wchar_t alphabet[5][33] =
    { {L'a', L'b', L'c', L'd', L'e', L'f', L'g', L'h', L'i', L'j', L'k', L'l', L'm', L'n', L'o', L'p', L'q', L'r', L's', L't', L'u', L'v', L'w', L'x', L'y', L'z' },
    {L'A', },
    {},
    {} };
    std::wstring result = L"";
    srand(time(NULL));
    for (unsigned short i = 0; i < stringSize; i++)
    {
        result += (160 + rand() % 85);
        if (spaceRate > 0)
            if ((spaceRate == (rand() % spaceRate)) && (i < stringSize + 1))
                result += L" ";
    }
    return result;*/
    //return L"ААА";
    return L"Я родился в Москве в семидесятом на краю города моча рано ударила в голову в четыре активно ругался матом, в детском саду девочки впервые показали мне пизду потом школа, вонючая форма, драки, клей так я становился сильней";
}

std::wstring TextGenerator::getTextFromFile()
{
    //std::wstring result = L"";
    //return result;
    return L"Большой тестовый текст";
}
