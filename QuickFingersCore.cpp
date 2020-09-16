#include "QuickFingersCore.h"
#include "TaskCore.h"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1200
#define ESC_KEYCODE 36
#define UP_KEYCODE 73
#define DOWN_KEYCODE 74
#define ENTER_KEYCODE 58
#define INVISIBLE_COLOR sf::Color(0, 0, 0, 0)
#define DEFAULT_INDENT 100

QuickFingersCore::QuickFingersCore() :
    m_window{ new sf::RenderWindow({WINDOW_WIDTH, WINDOW_HEIGHT}, "QuickFingers", sf::Style::Close) }
{
    m_window->setFramerateLimit(120);
    m_supportedFonts["CENTURY_GOTHIC"] = std::make_shared<sf::Font>();
    m_supportedFonts["CENTURY_GOTHIC"]->loadFromFile("CenturyGothic.ttf");
    m_textParameter.font = m_supportedFonts["CENTURY_GOTHIC"];
}

QuickFingersCore::~QuickFingersCore()
{
    delete m_window;
}

void QuickFingersCore::startScreen()
{
    while (m_window->isOpen())
    {
        m_window->clear();

        m_window->display();
    }
}

void QuickFingersCore::countdownScreen(const unsigned short time, const TextGenerator::Language language)
{
    TextField languageMessage(m_textParameter);  
    switch (language)
    {
    case TextGenerator::Language::ENGLISH :
        languageMessage.setWString(L"Enable ENG keyboard layout.");
        break;
    case TextGenerator::Language::RUSSIAN :
        languageMessage.setWString(L"Enable RUS keyboard layout.");
        break;
    default:
        languageMessage.setWString(L"Unknow language.");
        break;
    }
    languageMessage.setPosition(m_window->getSize().x / 2 - languageMessage.getWidth() / 2, DEFAULT_INDENT + languageMessage.getCharacterSize());
    TextField timerMessage(m_textParameter);
    timerMessage.setWString(L"Start in x");
    timerMessage.setPosition(m_window->getSize().x / 2 - timerMessage.getWidth() / 2, m_window->getSize().y / 2);
    sf::Clock m_timer;
    float m_deltaTime(0);
    float m_elapsedTime(0);
    m_timer.restart().asSeconds();
    while (m_window->isOpen())
    {  
        for (sf::Event event; m_window->pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }
        }
        if (m_elapsedTime >= time)
            return;
        m_deltaTime = m_timer.restart().asSeconds();
        m_elapsedTime += m_deltaTime;
        std::wstringstream timerStream;
        timerStream << L"Start in " << time - static_cast<int>(m_elapsedTime);
        timerMessage.setWString(timerStream.str());
        timerMessage.setPosition(m_window->getSize().x / 2 - timerMessage.getWidth() / 2, m_window->getSize().y / 2);
        m_window->clear();
        languageMessage.render(*m_window);
        timerMessage.render(*m_window);
        m_window->display();
    }
}

TextGenerator::GenerationType QuickFingersCore::selectGenerationType()
{
    TextParameter requestTextParameter = m_textParameter;
    requestTextParameter.neutralColor = INVISIBLE_COLOR;
    TextField requestMessage(requestTextParameter);
    requestMessage.setWString(L"Please select generation type");
    std::vector<TextField> typesMessage;
    std::vector<TextGenerator::GenerationType> types;
    unsigned short selectedType(0);

    typesMessage.push_back(m_textParameter);
    typesMessage[0].setWString(L"Text from file");
    types.push_back(TextGenerator::GenerationType::FROM_FILE);

    typesMessage.push_back(m_textParameter);
    typesMessage[1].setWString(L"Text from wiki");
    types.push_back(TextGenerator::GenerationType::FROM_WIKI);

    typesMessage.push_back(m_textParameter);
    typesMessage[2].setWString(L"Random text");
    types.push_back(TextGenerator::GenerationType::RANDOM);

    typesMessage.push_back(m_textParameter);
    typesMessage[3].setWString(L"Test text (pangram)");
    types.push_back(TextGenerator::GenerationType::TEST);

    requestMessage.setPosition(m_window->getSize().x / 2 - requestMessage.getWidth() / 2, DEFAULT_INDENT);
    for (unsigned short i = 0; i < types.size(); i++)
        typesMessage[i].setPosition(m_window->getSize().x / 2 - typesMessage[i].getWidth() / 2, requestMessage.getY() + requestMessage.getHeight() + DEFAULT_INDENT * i);

    typesMessage[0].setState(LetterField::State::CORRECT);

    while (m_window->isOpen())
    {
        m_window->clear();
        for (sf::Event event; m_window->pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }
            else
            {
                if (event.type == sf::Event::KeyReleased)
                {
                    switch (event.key.code)
                    {
                    case ESC_KEYCODE:
                        m_window->close();
                        break;
                    case UP_KEYCODE:
                        if (selectedType > 0)
                        {
                            typesMessage[selectedType].setState(LetterField::State::NEUTRAL);
                            selectedType--;
                            typesMessage[selectedType].setState(LetterField::State::CORRECT);
                        }
                        break;
                    case DOWN_KEYCODE:
                        if (selectedType < types.size() - 1)
                        {
                            typesMessage[selectedType].setState(LetterField::State::NEUTRAL);
                            selectedType++;
                            typesMessage[selectedType].setState(LetterField::State::CORRECT);
                        }
                        break;
                    case ENTER_KEYCODE:
                        return types[selectedType];
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        
        requestMessage.render(*m_window);
        for (unsigned short i = 0; i < types.size(); i++)
            typesMessage[i].render(*m_window);
        m_window->display();
    }
}

TextGenerator::Language QuickFingersCore::selectLanguage()
{
    TextParameter requestTextParameter = m_textParameter;
    requestTextParameter.neutralColor = INVISIBLE_COLOR;
    TextField requestMessage(requestTextParameter);
    requestMessage.setWString(L"Please select language");
    std::vector<TextField> languagesMessage;
    std::vector<TextGenerator::Language> languages;
    unsigned short selectedLanguage(0);

    languagesMessage.push_back(m_textParameter);
    languagesMessage[0].setWString(L"English");
    languages.push_back(TextGenerator::Language::ENGLISH);

    languagesMessage.push_back(m_textParameter);
    languagesMessage[1].setWString(L"Russian");
    languages.push_back(TextGenerator::Language::RUSSIAN);

    requestMessage.setPosition(m_window->getSize().x / 2 - requestMessage.getWidth() / 2, DEFAULT_INDENT);
    for (unsigned short i = 0; i < languages.size(); i++)
        languagesMessage[i].setPosition(m_window->getSize().x / 2 - languagesMessage[i].getWidth() / 2, requestMessage.getY() + requestMessage.getHeight() + DEFAULT_INDENT * i);
    
    languagesMessage[0].setState(LetterField::State::CORRECT);

    while (m_window->isOpen())
    {
        m_window->clear();
        for (sf::Event event; m_window->pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }
            else
            {
                if (event.type == sf::Event::KeyReleased)
                {
                    switch (event.key.code)
                    {
                    case ESC_KEYCODE:
                        m_window->close();
                        break;
                    case UP_KEYCODE:
                        if (selectedLanguage > 0)
                        {
                            languagesMessage[selectedLanguage].setState(LetterField::State::NEUTRAL);
                            selectedLanguage--;
                            languagesMessage[selectedLanguage].setState(LetterField::State::CORRECT);
                        }
                        break;
                    case DOWN_KEYCODE:
                        if (selectedLanguage < languages.size() - 1)
                        {
                            languagesMessage[selectedLanguage].setState(LetterField::State::NEUTRAL);
                            selectedLanguage++;
                            languagesMessage[selectedLanguage].setState(LetterField::State::CORRECT);
                        }
                        break;
                    case ENTER_KEYCODE:
                        return languages[selectedLanguage];
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        requestMessage.render(*m_window);
        for (unsigned short i = 0; i < languages.size(); i++)
            languagesMessage[i].render(*m_window);
        m_window->display();
    }
}

void QuickFingersCore::start()
{
    TextGenerator::GenerationType generationType;
    TextGenerator::Language language;
    //startScreen();
    while (m_window->isOpen())
    {
        language = selectLanguage();
        generationType = selectGenerationType();
        countdownScreen(3, language);
        TaskCore* task;
        task = new TaskCore(m_window, m_textParameter, language, generationType);
        delete task;
    }
}