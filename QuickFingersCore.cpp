#include <sstream>
#include <iomanip> 

#include "QuickFingersCore.h"

QuickFingersCore::QuickFingersCore(unsigned short windowWidth, unsigned short windowHight) :
    m_window{ new sf::RenderWindow({ windowWidth, windowHight }, "QuickFingers", sf::Style::Close) },
    m_deltaTime{ 0.f },
    m_elapsedTime{ 0.f },
    stop(0)
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
    bool start = false;
    KeyboardVisualizer m_Visualizer;
    TextField taskText(m_textParameter);
    TextField timerText(m_textParameter);
    TextField accuracyText(m_textParameter);
    TextField velocityText(m_textParameter);
    taskText.setWString(TextGenerator::getRandomText(), m_window->getSize().x, m_window->getSize().y);
    taskText.setPosition(taskText.getCharacterSize(), taskText.getCharacterSize());
    velocityText.setWString(L"0 chars per minute");
    m_Visualizer.setPosition(0,0);
    m_Visualizer.setPosition(m_window->getSize().x / 2 -  m_Visualizer.getWidth() / 2, m_window->getSize().y - m_Visualizer.getHeight() - 50);

    while (m_window->isOpen())
    {
        if (!stop && start)
        {
            m_deltaTime = m_timer.restart().asSeconds();
            m_elapsedTime += m_deltaTime;
            unsigned short letters = taskText.getValidLetters();
            if (letters)
                velocityText.setWString(std::to_wstring(static_cast<int>(taskText.getValidLetters() / (m_elapsedTime / 60))) += L" chars per minute");
        }
        velocityText.setPosition(m_window->getSize().x / 2 - velocityText.getWidth() / 2, taskText.getHeight() + velocityText.getCharacterSize());
        for (sf::Event event; m_window->pollEvent(event);)
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }
            else
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    m_Visualizer.setState(KeyboardVisualizer::State::ENABLE, event.key.code);
                    std::cout << std::to_string(event.key.code) << std::endl;
                }
                if (event.type == sf::Event::KeyReleased)
                {
                    m_Visualizer.setState(KeyboardVisualizer::State::DISABLE, event.key.code);
                }
                if ((event.type == sf::Event::TextEntered) && !stop)
                {
                    taskText.handleInput(event, m_window->getSize().x, m_window->getSize().y);
                    if (!start)
                    {
                        start = true;
                        m_deltaTime = m_timer.restart().asSeconds();
                    }
                }
            }
        m_window->clear();
        taskText.render(*m_window);
        timerText.render(*m_window);
        accuracyText.render(*m_window);
        velocityText.render(*m_window);
        m_Visualizer.render(*m_window);
        if (!taskText.checkMistakes())
        {     
            if (!stop)
            {
                std::wstringstream timerStream;
                timerStream.precision(2);
                timerStream << L"Elapsed time: " << std::fixed << m_elapsedTime << L" seconds";
                timerText.setWString(timerStream.str());
                timerText.setPosition(m_window->getSize().x / 2 - timerText.getWidth() / 2, velocityText.getHeight() + timerText.getCharacterSize());
                std::wstringstream accuracyStream;
                accuracyStream << std::setprecision(3);
                accuracyStream << L"Accuracy: " << 100.f - (static_cast<float>(taskText.getCorrections()) / (taskText.getWString().length()) * 100) << L"%";
                accuracyText.setWString(accuracyStream.str());
                accuracyText.setPosition(m_window->getSize().x / 2 - accuracyText.getWidth() / 2, timerText.getHeight() + accuracyText.getCharacterSize());
                stop = true;
            }
        }
        m_window->display();
    }
}
