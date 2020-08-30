#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

class TextGenerator
{
public:
	enum class Language
	{
		ENGLISH,
		RUSSIAN
	};
	enum class GenerationType
	{
		RANDOM,
		FROM_FILE,
		FROM_WIKI,
		TEST
	};
	static std::wstring generate(Language language, GenerationType generationType);
private:
	static std::wstring getRandomText(Language language);
	static std::wstring getTextFromFile(Language language);
	static std::wstring getTextFromWiki(Language language);
	static std::wstring getTestText(Language language);
};

