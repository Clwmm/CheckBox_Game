#include "SFML/Graphics.hpp"
#include <iostream>
#include "CheckBox.h"
#include  <random>
#include  <iterator>
#include <Windows.h>

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
    FreeConsole();

    sf::Vector2f screenSize = sf::Vector2f(800, 800);

    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(screenSize.x), static_cast<unsigned int>(screenSize.y)), "Check Box Game");
    window.setFramerateLimit(30);

    sf::View view(sf::Vector2f(screenSize.x/2, screenSize.y/2), sf::Vector2f(screenSize.x, screenSize.y));
    window.setView(view);

    sf::Image icon;
    icon.loadFromFile("res/check.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Color backgroudColor = sf::Color(25, 24, 37);


    int noGen = 1;
    std::vector<CheckBox*>* boxes = new std::vector<CheckBox*>;
    CheckBox* a = new CheckBox(boxes, view.getSize(), view.getCenter(), sf::Vector2i(0, 0), backgroudColor, 1, noGen);
    boxes->push_back(a);

    for (int i = 0; i < noGen; i++)
        for (auto x : *boxes)
            if (x->generation == i)
            {
                x->generateNextGen();
                /*window.clear(backgroudColor);
                for (auto x : *boxes)
                    x->draw(window);
                window.display();*/
            }
       

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
                view.setSize(sf::Vector2f(static_cast<float>(event.size.width), static_cast<float>(event.size.height)));
                for (auto x : *boxes)
                    x->resize(view.getSize());
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                    
                case sf::Keyboard::R:
                    for (auto p : *boxes)
                    {
                        p->active = false;
                        p->updateColor();
                    }
                    break;

                case sf::Keyboard::E:
                    for (auto p : *boxes)
                        delete p;
                    boxes->clear();
                    noGen++;
                    {
                        CheckBox* num1 = new CheckBox(boxes, view.getSize(), view.getCenter(), sf::Vector2i(0, 0), backgroudColor, 1, noGen);
                        boxes->push_back(num1);

                        for (int i = 0; i < noGen; i++)
                            for (auto x : *boxes)
                                if (x->generation == i)
                                    x->generateNextGen();
                    }

                    break;

                case sf::Keyboard::Q:
                    for (auto p : *boxes)
                        delete p;
                    boxes->clear();
                    if (noGen > 1)
                        noGen--;
                    {
                        CheckBox* num1 = new CheckBox(boxes, view.getSize(), view.getCenter(), sf::Vector2i(0, 0), backgroudColor, 1, noGen);
                        boxes->push_back(num1);

                        for (int i = 0; i < noGen; i++)
                            for (auto x : *boxes)
                                if (x->generation == i)
                                    x->generateNextGen();
                    }

                    break;

                default:
                    break;
                }

            default:
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.setView(view);
        window.clear(backgroudColor); // Color background
        for (auto x : *boxes)
            x->draw(window);
        window.display();
    }

    return 0;
}

/*
ToDo:
    clearing vector without memory leaks [done]
    create game class
    resizing boxes when window is resized [done]

    features:
        when level is cleared animate boxes and create new ones with animation

*/