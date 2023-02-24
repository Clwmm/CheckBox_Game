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
    sf::Vector2f screenSize = sf::Vector2f(800, 800);

    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Window Title");
    window.setFramerateLimit(30);

    sf::View view(sf::Vector2f(screenSize.x/2, screenSize.y/2), sf::Vector2f(screenSize.x, screenSize.y));
    window.setView(view);

    sf::Color backgroudColor = sf::Color(25, 24, 37);


    int noGen = 1;
    std::vector<CheckBox*>* boxes = new std::vector<CheckBox*>;
    CheckBox* a = new CheckBox(boxes, view.getCenter(), sf::Vector2f(static_cast<float>(view.getSize().x), static_cast<float>(view.getSize().y)), backgroudColor, 1, noGen, true);
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
                view.setSize(sf::Vector2f(event.size.width, event.size.height));
                /*for (auto x : *boxes)
                    x->resize(sf::Vector2f(static_cast<float>(event.size.width), static_cast<float>(event.size.height)), view.getCenter(), true);*/
                a->resize(sf::Vector2f(static_cast<float>(event.size.width), static_cast<float>(event.size.height)), view.getCenter(), true);
                for (auto x : *boxes)
                    x->resized = false;
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                    
                case sf::Keyboard::E:
                    for (auto p : *boxes)
                        delete p;
                    boxes->clear();
                    noGen++;
                    {
                        CheckBox* num1 = new CheckBox(boxes, view.getCenter(), sf::Vector2f(static_cast<float>(view.getSize().x), static_cast<float>(view.getSize().y)), backgroudColor, 1, noGen, true);
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
    resizing boxes when window is resized

    features:
        when level is cleared animate boxes and create new ones with animation

*/