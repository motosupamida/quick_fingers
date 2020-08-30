#include "TextGenerator.h"

std::wstring TextGenerator::generate(Language language, GenerationType generationType)
{
    switch (generationType)
    {
    case GenerationType::FROM_FILE :
        return getTextFromFile(language);
        break;
    case GenerationType::FROM_WIKI :
        return getTextFromWiki(language);
        break;
    case GenerationType::RANDOM :
        return getRandomText(language);
        break;
    case GenerationType::TEST:
        return getTestText(language);
        break;
    default:
        return L"TYPE OF GENERATION ERROR";
        break;
    }
}

std::wstring TextGenerator::getTestText(Language language)
{
    switch (language)
    {
    case TextGenerator::Language::ENGLISH:
        return L"The five boxing wizards jump quickly.";
        break;
    case TextGenerator::Language::RUSSIAN:
        return L"Съешь ещё этих мягких французских булок, да выпей же чаю.";
        break;
    default:
        return L"INVALID LANGUAGE TO TEST TEXT GENERATION!";
        break;
    }
}

std::wstring TextGenerator::getRandomText(Language language)
{
    switch (language)
    {
    case TextGenerator::Language::ENGLISH:
        return L"Random text generation in this language is still in development.";
        break;
    case TextGenerator::Language::RUSSIAN:
        return L"Рандомная генерация текста на этом языке еще в разработке.";
        break;
    default:
        return L"INVALID LANGUAGE TO RANDOM TEXT GENERATION!";
        break;
    }
}

std::wstring TextGenerator::getTextFromFile(Language language)
{
    switch (language)
    {
    case TextGenerator::Language::ENGLISH:
        return L"Reading from file in this language is still in development.";
        break;
    case TextGenerator::Language::RUSSIAN:
        return L"Чтение из файла на этом языке еще в разработке.";
        break;
    default:
        return L"INVALID LANGUAGE TO TEXT FROM FILE GENERATION!";
        break;
    }
}

std::wstring TextGenerator::getTextFromWiki(Language language)
{
    switch (language)
    {
    case TextGenerator::Language::ENGLISH:
        return L"Wiki parser in this language is still in development.";
        break;
    case TextGenerator::Language::RUSSIAN:
        return L"Вики парсер на этом языке еще в разработке.";
        break;
    default:
        return L"INVALID LANGUAGE TO TEXT FROM WIKI GENERATION!";
        break;
    }
}
