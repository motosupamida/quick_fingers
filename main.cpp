#include <iostream>

#include <sfml/graphics.hpp>

#include "TextField.h"
#include "TextGenerator.h"

int main()
{
    sf::RenderWindow window({ 800, 800 }, "QuickFingers", sf::Style::Close);
    window.setFramerateLimit(120);
    sf::Clock timer;
    float deltaTime;
    float elapsedTime = 0;
    sf::Font font;
    font.loadFromFile("CenturyGothic.ttf");
    TextField taskText(font, sf::Text::Style::Bold, sf::Color(135, 206, 250));
    TextField enteredText(font, sf::Text::Style::Italic, sf::Color(238, 130, 238));
    taskText.setString(TextGenerator::getRandomText());
    taskText.setPosition((window.getSize().x - taskText.getGlobalBounds().width) / 2, 10.0f);
    //task text alignment

    while (window.isOpen())
    {
        deltaTime = timer.restart().asSeconds();
        elapsedTime += deltaTime;
        system("cls");
        std::cout << "delta time: " << deltaTime << " seconds" << std::endl;
        std::cout << "elapsed time: " << elapsedTime << " seconds" << std::endl;
        sf::Event event;
        for (sf::Event event; window.pollEvent(event);)
            if (event.type == sf::Event::Closed)
                window.close();
            else 
            {
                if (event.type == sf::Event::TextEntered)
                enteredText.handleInput(event);
                enteredText.setPosition((window.getSize().x - enteredText.getGlobalBounds().width) / 2, taskText.getGlobalBounds().height + enteredText.getCharacterSize());
                //entered text alignment
            }
        window.clear();
        taskText.render(window);
        enteredText.render(window);
        window.display();
    } 
    std::cout << "\nFinal time is " << elapsedTime <<" seconds"<< std::endl;
    return 0;
}