#include "TaskCore.h"

#define ESC_KEYCODE 36
#define DEFAULT_INDENT 10

TaskCore::TaskCore(
    sf::RenderWindow* window, 
    const TextParameter textParameter, 
    const TextGenerator::Language language, 
    const TextGenerator::GenerationType generationType):

	m_deltaTime(0.f), //frametime
	m_elapsedTime(0.f), //time taken to enter text
	m_stop(false), //end of task, text entered correctly
	m_taskText(textParameter), //text for typing 
	m_timerText(textParameter), //indication of elapsed time
	m_accuracyText(textParameter), //indication of accuracy 
	m_velocityText(textParameter), //indication of char per minute 
	m_window(window) //window for render

{
    m_taskText.setWString(TextGenerator::generate(language, generationType), m_window->getSize().x, m_window->getSize().y);
    m_taskText.setPosition(m_taskText.getCharacterSize(), m_taskText.getCharacterSize());
    m_velocityText.setWString(L"0 chars per minute");
    m_visualizer.setPosition(0, 0);
    m_visualizer.setPosition(m_window->getSize().x / 2 - m_visualizer.getWidth() / 2, m_window->getSize().y - m_visualizer.getHeight() - 50);

    while (m_window->isOpen())
    {
        if (!m_stop)
        {
            m_deltaTime = m_timer.restart().asSeconds();
            m_elapsedTime += m_deltaTime;
            unsigned short letters = m_taskText.getValidLetters();
            if (letters)
                m_velocityText.setWString(std::to_wstring(static_cast<int>(m_taskText.getValidLetters() / (m_elapsedTime / 60))) += L" chars per minute");
        }
        m_velocityText.setPosition(m_window->getSize().x / 2 - m_velocityText.getWidth() / 2, m_visualizer.getY() - m_velocityText.getCharacterSize() * 2);
        for (sf::Event event; m_window->pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                m_window->close();
            }
            else
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    m_visualizer.setState(KeyboardVisualizer::State::ENABLE, event.key.code);
                    //std::cout << std::to_string(event.key.code) << std::endl; //debug function
                }
                if (event.type == sf::Event::KeyReleased)
                {
                    m_visualizer.setState(KeyboardVisualizer::State::DISABLE, event.key.code);
                    if (event.key.code == ESC_KEYCODE)
                        return;
                }
                if ((event.type == sf::Event::TextEntered) && !m_stop)
                {
                    m_taskText.handleInput(event, m_window->getSize().x, m_window->getSize().y);
                }
            }
        }
        m_window->clear();
        m_taskText.render(*m_window);
        m_timerText.render(*m_window);
        m_accuracyText.render(*m_window);
        m_velocityText.render(*m_window);
        m_visualizer.render(*m_window);
        if (!m_taskText.checkMistakes())
        {
            if (!m_stop)
            {
                std::wstringstream timerStream;
                timerStream.precision(2);
                timerStream << L"Elapsed time: " << std::fixed << m_elapsedTime << L" seconds";
                m_timerText.setWString(timerStream.str());
                m_timerText.setPosition(m_window->getSize().x / 2 - m_timerText.getWidth() / 2, m_velocityText.getY() - m_timerText.getCharacterSize() - DEFAULT_INDENT);
                std::wstringstream accuracyStream;
                accuracyStream << std::setprecision(3);
                if ((m_taskText.getCorrections()) > (m_taskText.getWString().length()))
                    accuracyStream << L"Accuracy: 0%";
                else
                    accuracyStream << L"Accuracy: " << 100.f - (static_cast<float>(m_taskText.getCorrections()) / (m_taskText.getWString().length()) * 100) << L"%";
                m_accuracyText.setWString(accuracyStream.str());
                m_accuracyText.setPosition(m_window->getSize().x / 2 - m_accuracyText.getWidth() / 2, m_timerText.getY() - m_accuracyText.getCharacterSize() - DEFAULT_INDENT);
                m_stop = true;
            }
        }
        m_window->display();
    }
}
