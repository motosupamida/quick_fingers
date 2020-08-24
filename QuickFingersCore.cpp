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

void QuickFingersCore::core()
{
    std::wstring message = L"Done! Elapsed time is: ";
    bool stop = false;
    TextField taskText(m_textParameter);
    TextField timerText(m_textParameter);
    TextField messageText(m_textParameter);
    taskText.setWString(TextGenerator::getRandomText(), m_window->getSize().x, m_window->getSize().y);
    taskText.setPosition(taskText.getCharacterSize(), taskText.getCharacterSize());
    timerText.setPosition(m_window->getSize().x / 2 - timerText.getWidth() / 2, taskText.getY() + taskText.getHeight() + taskText.getCharacterSize());
    messageText.setPosition(m_window->getSize().x / 2 - timerText.getWidth() / 2, taskText.getY() + taskText.getHeight() + taskText.getCharacterSize());
    while (m_window->isOpen())
    {
        if (!stop)
        {
            m_deltaTime = m_timer.restart().asSeconds();
            m_elapsedTime += m_deltaTime;
        }
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
        if (!taskText.checkMistakes())
        {     
            if (!stop)
            {
                message += std::to_wstring(m_elapsedTime);
                message += L" seconds";
                messageText.setWString(message, m_window->getSize().x, m_window->getSize().y);
                messageText.setPosition(m_window->getSize().x / 2 - messageText.getWidth() / 2, timerText.getY());
            }
            stop = true;
            messageText.render(*m_window);
        }
        m_window->display();
    }
}
