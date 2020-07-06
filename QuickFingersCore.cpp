#include "QuickFingersCore.h"

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

QuickFingersCore::QuickFingersCore(unsigned short windowWidth, unsigned short windowHight) :
    m_window{ new sf::RenderWindow({ windowWidth, windowHight }, "QuickFingers", sf::Style::Close) }
{
}

QuickFingersCore::~QuickFingersCore()
{
    delete m_window;
}

void QuickFingersCore::core()
{
    m_window->setFramerateLimit(120);
    sf::Clock timer;
    float deltaTime;
    float elapsedTime = 0;
    bool stop = false;
    sf::Font font;
    std::wstring challengeMessageString = L"Done! Elapsed time is: ";
    font.loadFromFile("CenturyGothic.ttf");
    TextField taskText(font, sf::Text::Style::Bold, sf::Color(135, 206, 250));
    TextField enteredText(font, sf::Text::Style::Italic, sf::Color(238, 130, 238), taskText.getCharacterSize());
    TextField challengeMessageText(font, sf::Text::Style::Regular, sf::Color(0, 100, 0), enteredText.getCharacterSize(), sf::Color::White);
    TextField timerText(font, sf::Text::Style::Regular, sf::Color(0, 130, 0), enteredText.getCharacterSize() / 2);
    taskText.setWString(TextGenerator::getRandomText(), m_window->getSize().x, m_window->getSize().y);
    taskText.setPosition(taskText.getCharacterSize(), taskText.getCharacterSize() * 1.5f);
    enteredText.setPosition(enteredText.getCharacterSize(), taskText.getHeight() + taskText.getCharacterSize());
    timerText.setPosition(timerText.getCharacterSize(), timerText.getCharacterSize());
    while (m_window->isOpen())
    {
        deltaTime = timer.restart().asSeconds();
        elapsedTime += deltaTime;
        timerText.setWString(std::to_wstring(elapsedTime), m_window->getSize().x, m_window->getSize().y);
        for (sf::Event event; m_window->pollEvent(event);)
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }
            else
            {
                if ((event.type == sf::Event::TextEntered) && !stop)
                    enteredText.handleInput(event, m_window->getSize().x, m_window->getSize().y);
            }
        m_window->clear();
        taskText.render(*m_window);
        enteredText.render(*m_window);
        challengeMessageText.render(*m_window);
        if (!stop)
            timerText.render(*m_window);
        if (challengeDone(taskText, enteredText) && !stop)
        {
            challengeMessageString += std::to_wstring(elapsedTime);
            challengeMessageText.setWString(challengeMessageString, m_window->getSize().x, m_window->getSize().y);
            challengeMessageText.setPosition(m_window->getSize().x / 2 - challengeMessageText.getWidth() / 2, challengeMessageText.getCharacterSize());
            stop = true;
        }
        m_window->display();
    }
}
