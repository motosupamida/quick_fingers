#include <iostream>

#include <sfml/graphics.hpp>

#include "TextField.h"
#include "TextGenerator.h"

int main()
{
    sf::Font font;
    font.loadFromFile("CenturyGothic.ttf");
    sf::RenderWindow window({1000, 1000}, "QuickFingers", sf::Style::Close);
    window.setFramerateLimit(120);
    TextGenerator textGenerator;
    std::string taskString = textGenerator.getText();
    TextField textField(font, 32u);
    textField.setString(L"Ваня - Кодзима");
    //textField.getString();

    while (window.isOpen())
    {
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
    return 0;
}