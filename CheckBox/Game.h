#pragma once

#include <SFML/Graphics.hpp>
#include "CheckBox.h"

class Game
{
private:
	sf::Vector2f screenSize;
	sf::RenderWindow* window = nullptr;
	sf::Image icon;
	sf::View view;
	sf::Texture logoTexture;

	sf::Color backgroundColor;

	std::vector<CheckBox*>* boxes = new std::vector<CheckBox*>;

	bool win = true;
	bool close = false;
	int noGen = 1;

	float deltaTime = 0;
	sf::Clock clock;

public:
	Game();
	~Game();
	void init();

private:
	void logoLoading();
	void game();
};

