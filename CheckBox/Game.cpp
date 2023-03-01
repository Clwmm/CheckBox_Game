#include "Game.h"

Game::Game()
{
	if (!icon.loadFromFile("res/check.png"))
		close = true;
	if (!logoTexture.loadFromFile("res/logo.png"))
		close = true;
}

Game::~Game()
{
	for (auto p : *boxes)
		delete p;
	boxes->clear();

	delete window;
	delete boxes;
}

void Game::logoLoading()
{
	window = new sf::RenderWindow(sf::VideoMode(670, 200), "Check Box Game", sf::Style::None);

	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	float a = 0;
	float fadecolor = 255;
	sf::Sprite logo;
	logo.setTexture(logoTexture);
	logo.setOrigin(sf::Vector2f(logo.getTexture()->getSize().x / 2, logo.getTexture()->getSize().y / 2));
	logo.setPosition(window->getSize().x / 2, window->getSize().y / 2);

	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window->setFramerateLimit(240);
	window->display();

	sf::Event evnt;

	float deltatime = 0;

	clock.restart().asSeconds();

	while (window->isOpen())
	{
		deltatime = clock.restart().asSeconds();
		while (window->pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				close = true;
				window->close();
				delete window;
				return;
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape)
				{
					close = true;
					window->close();
					delete window;
					return;
				}
				else
				{
					window->close();
					delete window;
					return;
				}
				break;
			}
		}

		a += deltatime;

		if (a > 0.3)
		{
			if (a > 3)
				fadecolor *= 1 + (deltatime * 8);
			else
				fadecolor *= 1 - (deltatime * 2);
		}
		if (fadecolor >= 255)
			fadecolor = 255;
		logo.setColor(sf::Color(255, 255, 255, -fadecolor));

		window->clear();
		window->draw(logo);
		window->display();

		if (a >= 3.8)
		{
			window->close();
			delete window;
			return;
		}
	}
}

void Game::init()
{
	if (close)
		return;

	logoLoading();

	screenSize = sf::Vector2f(800, 800);
	window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(screenSize.x), static_cast<unsigned int>(screenSize.y)), "Check Box Game");
	window->setFramerateLimit(120);

	sf::View view(sf::Vector2f(screenSize.x / 2, screenSize.y / 2), sf::Vector2f(screenSize.x, screenSize.y));
	window->setView(view);

	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    backgroundColor = sf::Color(25, 24, 37);

	while (!close)
		game();
}

void Game::game()
{
	CheckBox* a = new CheckBox(boxes, view.getSize(), view.getCenter(), sf::Vector2i(0, 0), backgroundColor, 1, noGen);
	boxes->push_back(a);

	for (int i = 0; i < noGen; i++)
		for (auto x : *boxes)
			if (x->generation == i)
				x->generateNextGen();

    bool initialization = true;
    bool endAnim = false;

    while (window->isOpen() && !close)
    {
        sf::Event event;
        while (window->pollEvent(event))
        {

            if (event.type == sf::Event::MouseButtonPressed && !win)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
                    sf::Vector2f worldPos = window->mapPixelToCoords(pixelPos);
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
                window->close();
                close = true;
                return;

            case sf::Event::Resized:
                view.setSize(sf::Vector2f(static_cast<float>(event.size.width), static_cast<float>(event.size.height)));
                for (auto x : *boxes)
                    x->resize(view.getSize());
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window->close();
                    close = true;
                    return;

                case sf::Keyboard::R:
                    for (auto p : *boxes)
                    {
                        p->active = false;
                        p->updateColor();
                    }
                    break;

                /*case sf::Keyboard::E:
                    for (auto p : *boxes)
                        delete p;
                    boxes->clear();
                    noGen++;
                    return;

                case sf::Keyboard::Q:
                    for (auto p : *boxes)
                        delete p;
                    boxes->clear();
                    noGen--;
                    return;*/

                default:
                    break;
                }

            default:
                break;
            }
            if (event.type == sf::Event::Closed)
            {
                window->close();
                close = true;
                return;
            }
        }
        deltaTime = clock.restart().asSeconds();
        win = true;
        for (auto x : *boxes)
            if (!x->active)
                win = false;

        window->setView(view);
        window->clear(backgroundColor); // Color background
        for (auto x : *boxes)
        {
            if (win)
                endAnim = x->animation(deltaTime);
            x->draw(*window);
        }
        window->display();

        if (endAnim)
        {
            for (auto p : *boxes)
                delete p;
            boxes->clear();
            noGen++;
            return;
        }
    }
}
