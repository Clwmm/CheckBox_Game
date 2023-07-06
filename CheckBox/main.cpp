#include "SFML/Graphics.hpp"
#include <iostream>
#include "CheckBox.h"
#include  <random>
#include  <iterator>
#include <Windows.h>
#include "Game.h"

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

class LastSave
{
    int vecMax = 50;
    int noVec = 0;
    int vecIte = 0;

    std::vector<CheckBox> tempVec;
    std::vector<std::vector<CheckBox>> lastStates;

public:

    void push(std::vector<CheckBox*> a)
    {
        if (noVec < vecMax)
        {
            tempVec.clear();
            for (auto i : a)
                tempVec.push_back(*i);
            lastStates.push_back(tempVec);
            
            noVec++;
            
            return;
        }
        else
        {
            lastStates.erase(lastStates.begin());

            tempVec.clear();
            for (auto i : a)
                tempVec.push_back(*i);
            lastStates.push_back(tempVec);

            return;
        }
    }
    void munisIte()
    {
        if (vecIte > 0)
            vecIte--;
    }
    void plusIte()
    {
        if (vecIte < vecMax - 1)
            vecIte++;
    }

    void draw(sf::RenderWindow& window)
    {
        if (noVec < vecMax)
            vecMax = noVec;
        for (auto x : lastStates[vecIte])
            x.draw(window);
    }
};

int main()
{
    sf::Vector2f screenSize = sf::Vector2f(800, 800);

    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(screenSize.x), static_cast<unsigned int>(screenSize.y)), "Check Box Game");
    window.setFramerateLimit(0);

    sf::View view(sf::Vector2f(screenSize.x/2, screenSize.y/2), sf::Vector2f(screenSize.x, screenSize.y));
    window.setView(view);

    sf::Image icon;
    icon.loadFromFile("res/check.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Color backgroudColor = sf::Color(25, 24, 37);

    bool win = true;
    bool close = false;
    int noGen = 3;
    std::vector<CheckBox*>* boxes = new std::vector<CheckBox*>;
    CheckBox* a = new CheckBox(boxes, screenSize, view.getCenter(), sf::Vector2i(0, 0), backgroudColor, 1, noGen);
    boxes->push_back(a);

    for (int i = 0; i < noGen; i++)
        for (auto x : *boxes)
            if (x->generation == i)
                x->generateNextGen();

    LastSave save;

    sf::Clock deltaClock;
    float deltaTime = 0;
    unsigned int iter = 0;
    double time = 0;

    bool withDisplay = false;

    sf::Event event;

    if (withDisplay)
    {
        while (window.isOpen())
        {
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
                            sf::FloatRect rect(x->out.getPosition().x - (x->out.getSize().x / 2), x->out.getPosition().y - (x->out.getSize().x / 2), x->out.getSize().x, x->out.getSize().y);
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

                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    default:
                        break;
                    }
                default:
                    break;
                }
            }

            if (!close)
            {
                time += deltaClock.restart().asSeconds();
                CheckBox* rand = *select_randomly(boxes->begin(), boxes->end());
                rand->clicked(true);

                win = true;
                for (auto x : *boxes)
                    if (!x->active)
                        win = false;
                iter++;
                if (win)
                {
                    std::cout << "Time: " << time << " s" << std::endl;
                    std::cout << "Nr iter: " << iter << std::endl;
                    close = true;
                }
                    
            }

            window.setView(view);
            window.clear(backgroudColor); // Color background
            for (auto x : *boxes)
                x->draw(window);
            window.display();
        }
    }
    else
    {
        while (!close)
        {
        time += deltaClock.restart().asSeconds();
        CheckBox* rand = *select_randomly(boxes->begin(), boxes->end());
        rand->clicked(true);

        win = true;
        for (auto x : *boxes)
            if (!x->active)
                win = false;
        save.push(*boxes);
        iter++;
        if (win)
            close = true;
        }
        std::cout << "Time: " << time << " s" << std::endl;
        std::cout << "Nr iter: " << iter << std::endl;


        while (window.isOpen())
        {
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
                            sf::FloatRect rect(x->out.getPosition().x - (x->out.getSize().x / 2), x->out.getPosition().y - (x->out.getSize().x / 2), x->out.getSize().x, x->out.getSize().y);
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

                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;

                    case sf::Keyboard::Q:
                        save.munisIte();
                        break;

                    case sf::Keyboard::E:
                        save.plusIte();
                        break;

                    default:
                        break;
                    }
                default:
                    break;
                }
            }

            window.setView(view);
            window.clear(backgroudColor); // Color background

            save.draw(window);

            /*for (auto x : *boxes)
                x->draw(window);*/

            window.display();
        }
    }


    for (auto p : *boxes)
        delete p;
    boxes->clear();
    delete boxes;
    return 0;



    /*
    1 mil iterations:
        - 1st save algo - 42.1238 s
        - 2nd save algo - 19.5178 s
        - 3rd save algo - 18.9477 s
    
    */

    

    //while (window.isOpen() && !close)
    //{
    //    
    //    while (window.pollEvent(event))
    //    {

    //        if (event.type == sf::Event::MouseButtonPressed)
    //        {
    //            if (event.mouseButton.button == sf::Mouse::Left)
    //            {
    //                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    //                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    //                for (auto x : *boxes)
    //                {
    //                    sf::FloatRect rect(x->out.getPosition().x - (x->out.getSize().x/2), x->out.getPosition().y - (x->out.getSize().x / 2), x->out.getSize().x, x->out.getSize().y);
    //                    if (rect.contains(worldPos))
    //                        x->clicked(true);
    //                        
    //                }
    //            }
    //        }

    //        switch (event.type)
    //        {
    //        case sf::Event::Closed:
    //            window.close();
    //            break;
    //            
    //        case sf::Event::Resized:
    //            view.setSize(sf::Vector2f(static_cast<float>(event.size.width), static_cast<float>(event.size.height)));
    //            for (auto x : *boxes)
    //                x->resize(view.getSize());
    //            break;

    //        case sf::Event::KeyPressed:
    //            switch (event.key.code)
    //            {
    //            case sf::Keyboard::Escape:
    //                window.close();
    //                break;
    //                
    //            case sf::Keyboard::R:
    //                for (auto p : *boxes)
    //                {
    //                    p->active = false;
    //                    p->updateColor();
    //                }
    //                break;

    //            case sf::Keyboard::E:
    //                for (auto p : *boxes)
    //                    delete p;
    //                boxes->clear();
    //                noGen++;
    //                {
    //                    CheckBox* num1 = new CheckBox(boxes, view.getSize(), view.getCenter(), sf::Vector2i(0, 0), backgroudColor, 1, noGen);
    //                    boxes->push_back(num1);

    //                    for (int i = 0; i < noGen; i++)
    //                        for (auto x : *boxes)
    //                            if (x->generation == i)
    //                                x->generateNextGen();
    //                }

    //                break;

    //            case sf::Keyboard::Q:
    //                for (auto p : *boxes)
    //                    delete p;
    //                boxes->clear();
    //                if (noGen > 1)
    //                    noGen--;
    //                {
    //                    CheckBox* num1 = new CheckBox(boxes, view.getSize(), view.getCenter(), sf::Vector2i(0, 0), backgroudColor, 1, noGen);
    //                    boxes->push_back(num1);

    //                    for (int i = 0; i < noGen; i++)
    //                        for (auto x : *boxes)
    //                            if (x->generation == i)
    //                                x->generateNextGen();
    //                }

    //                break;

    //            default:
    //                break;
    //            }

    //        default:
    //            break;
    //        }
    //        if (event.type == sf::Event::Closed)
    //            window.close();
    //    }
    //    deltaTime = deltaClock.restart().asSeconds();
    //    win = true;
    //    for (auto x : *boxes)
    //        if (!x->active)
    //            win = false;
    //    
    //    window.setView(view);
    //    window.clear(backgroudColor); // Color background
    //    for (auto x : *boxes)
    //    {
    //        if (win)
    //            if (x->sinAnim(deltaTime))
    //                close = true;
    //        x->draw(window);
    //    }
    //    window.display();
    //}

    //for (auto p : *boxes)
    //    delete p;
    //boxes->clear();
    //delete boxes;

    //return 0;
}

/*
ToDo:
    clearing vector without memory leaks [done]
    create game class [done]
    resizing boxes when window is resized [done]

    features:
        when level is cleared animate boxes and create new ones with animation [done only with clearing]

*/