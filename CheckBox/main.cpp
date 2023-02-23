#include "SFML/Graphics.hpp"
#include <iostream>
#include "CheckBox.h"
#include  <random>
#include  <iterator>

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Window Title");
    window.setFramerateLimit(30);
    sf::Color backgroudColor = sf::Color(25, 24, 37);

    std::vector<CheckBox*>* boxes = new std::vector<CheckBox*>;
    CheckBox* a = new CheckBox(boxes, sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x, window.getSize().y), backgroudColor, 1, 4);
    boxes->push_back(a);

    a->generateNextGen();
    for (auto x : *boxes)
        if (x->generation == 2)
            x->generateNextGen();
    for (auto x : *boxes)
        if (x->generation == 3)
            x->generateNextGen();
       

    /*CheckBox* rand = *select_randomly(boxes->begin(), boxes->end());
    rand->active = true;
    rand->updateColor();*/

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
                    for (auto x : *boxes)
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
                for (auto x : *boxes)
                    x->resize(sf::Vector2f(event.size.width, event.size.height));
                break;

            default:
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }



        window.clear(backgroudColor); // Color background
        for (auto x : *boxes)
            x->draw(window);
        window.display();
    }

    return 0;
}

/*
ToDo:
    clearing vector without memory leaks
    create game class
    resizing boxes when window is resized

    features:
        when level is cleared animate boxes and create new ones with animation

*/