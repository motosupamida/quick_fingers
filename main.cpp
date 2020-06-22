#include <iostream>

#include <sfml/graphics.hpp>

#include "TextField.h"
#include "TextGenerator.h"

int main()
{
    sf::Clock timer;
    float deltaTime;
    float elapsedTime = 0;
    sf::Font font;
    font.loadFromFile("CenturyGothic.ttf");
    sf::RenderWindow window({1000, 1000}, "QuickFingers", sf::Style::Close);
    window.setFramerateLimit(120);
    TextGenerator textGenerator;
    std::string taskString = textGenerator.getText();
    TextField textField(font, 32u);
    textField.setString(L"���� - �������");

    while (window.isOpen())
    {
        deltaTime = timer.restart().asSeconds();
        elapsedTime += deltaTime;
        system("cls");
        std::cout << "delta time:   " << deltaTime << std::endl;
        std::cout << "elapsed time: " << elapsedTime << std::endl;
        sf::Event event;
        for (sf::Event event; window.pollEvent(event);)
            if (event.type == sf::Event::Closed)
                window.close();
            else 
            {
                if (event.type == sf::Event::TextEntered)
                textField.handleInput(event);
            }
        window.clear();
        textField.render(window);
        window.display();
    }
    std::cout << "\nFinal time is " << elapsedTime << std::endl;
    return 0;
}