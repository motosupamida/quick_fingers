#include "QuickFingersCore.h"

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
    sf::Font font;
    font.loadFromFile("CenturyGothic.ttf");
    //TextField taskText(font, sf::Text::Style::Bold, sf::Color(135, 206, 250));
    TextField enteredText(font, sf::Text::Style::Italic, sf::Color(238, 130, 238));
    //taskText.setString(TextGenerator::getRandomText());
    //taskText.setPosition(10.0f, 10.0f);
    enteredText.setPosition(10.0f,  90.0f);

    while (m_window->isOpen())
    {
        deltaTime = timer.restart().asSeconds();
        elapsedTime += deltaTime;
        system("cls");
        std::cout << "delta time: " << deltaTime << " seconds" << std::endl;
        std::cout << "elapsed time: " << elapsedTime << " seconds" << std::endl;
        for (sf::Event event; m_window->pollEvent(event);)
            if (event.type == sf::Event::Closed)
                m_window->close();
            else
            {
                if (event.type == sf::Event::TextEntered)
                    enteredText.handleInput(event, m_window->getSize().x, m_window->getSize().y);
            }
        m_window->clear();
        taskText.render(*m_window);
        enteredText.render(*m_window);
        m_window->display();
    }
    std::cout << "\nFinal time is " << elapsedTime << " seconds" << std::endl;
}
