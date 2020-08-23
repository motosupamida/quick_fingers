#include "QuickFingersCore.h"

QuickFingersCore::QuickFingersCore(unsigned short windowWidth, unsigned short windowHight) :
    m_window{ new sf::RenderWindow({ windowWidth, windowHight }, "QuickFingers", sf::Style::Close) },
    m_deltaTime { 0.f },
    m_elapsedTime { 0.f }
{
    m_window->setFramerateLimit(120);
    m_supportedFonts["CENTURY_GOTHIC"] = std::make_shared<sf::Font>();
    m_supportedFonts["CENTURY_GOTHIC"]->loadFromFile("CenturyGothic.ttf");
    m_textParameter.font = m_supportedFonts["CENTURY_GOTHIC"];
    m_textParameter.style = sf::Text::Style::Regular;
}

QuickFingersCore::~QuickFingersCore()
{
    delete m_window;
}

bool QuickFingersCore::mistakeCheck(TextField& taskText, TextField& enteredText)
{
    if (enteredText.getWString().length() < 2)
        return false;
    for (unsigned short i = 0; i < enteredText.getWString().length(); i++)
    {
        if (taskText.getWString()[i] != enteredText.getWString()[i])
            return true;
    }
    return true;
}

bool QuickFingersCore::challengeDone(TextField& taskText, TextField& enteredText)
{
    if (taskText.getWString().length() - 1 == enteredText.getWString().length()) // -1 for ignore '\n' char
    {
        for (unsigned short i = 0; i < taskText.getWString().length(); i++)
        {
            if (taskText.getWString()[i] != enteredText.getWString()[i])
                return false;
        }
        return true;
    }
    return false;
}

void QuickFingersCore::core()
{
    bool stop = false;
    std::wstring challengeMessageString = L"Done! Elapsed time is: ";
    TextField taskText(m_textParameter);
    TextField timerText(m_textParameter);
    taskText.setWString(TextGenerator::getRandomText(), m_window->getSize().x, m_window->getSize().y);
    taskText.setPosition(taskText.getCharacterSize(), taskText.getCharacterSize());
    timerText.setPosition(m_window->getSize().x / 2 - timerText.getWidth() / 2, taskText.getY() + taskText.getHeight() + taskText.getCharacterSize());
    timerText.setPosition(m_window->getSize().x / 2 - timerText.getWidth() / 2, timerText.getY());
    while (m_window->isOpen())
    {
        m_deltaTime = m_timer.restart().asSeconds();
        m_elapsedTime += m_deltaTime;
        timerText.setWString(std::to_wstring(static_cast<int>(m_elapsedTime)), m_window->getSize().x, m_window->getSize().y);
        for (sf::Event event; m_window->pollEvent(event);)
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }
            else
            {
                if ((event.type == sf::Event::TextEntered) && !stop)
                    taskText.handleInput(event, m_window->getSize().x, m_window->getSize().y);
            }
        m_window->clear();
        taskText.render(*m_window);
        timerText.setPosition(m_window->getSize().x / 2 - timerText.getWidth() / 2, timerText.getY());
        timerText.render(*m_window);  
        m_window->display();
    }
}
