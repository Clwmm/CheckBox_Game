#include "SFML/Graphics.hpp"
#include <iostream>
#include "CheckBox.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Window Title");
    sf::Color backgroudColor = sf::Color(25, 24, 37);

    std::vector<std::shared_ptr<CheckBox>> boxes;;
    auto a = std::make_shared<CheckBox>(boxes, sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x, window.getSize().y), backgroudColor, 1, 2);

    boxes.push_back(a);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                    for (auto x : boxes)
                    {
                        sf::FloatRect rect(x->out.getPosition().x - (x->out.getSize().x/2), x->out.getPosition().y - (x->out.getSize().x / 2), x->out.getSize().x, x->out.getSize().y);
                        if (rect.contains(worldPos))
                            x->clicked(true);
                    }
                }
            }

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
                
            case sf::Event::Resized:
                for (auto x : boxes)
                    x->resize(sf::Vector2f(event.size.width, event.size.height));
                break;

            default:
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }



        window.clear(backgroudColor); // Color background
        for (auto x : boxes)
            x->draw(window);
        window.display();
    }

    return 0;
}