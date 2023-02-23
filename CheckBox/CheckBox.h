#pragma once

#include "SFML/Graphics.hpp"
/*
1	2	3
4		5
6	7	8
*/

class CheckBox
{
public:
	std::shared_ptr<CheckBox> one = nullptr;
	std::shared_ptr<CheckBox> two = nullptr;
	std::shared_ptr<CheckBox> three = nullptr;
	std::shared_ptr<CheckBox> four = nullptr;
	std::shared_ptr<CheckBox> five = nullptr;
	std::shared_ptr<CheckBox> six = nullptr;
	std::shared_ptr<CheckBox> seven = nullptr;
	std::shared_ptr<CheckBox> eight = nullptr;
private:
	int generation = 0;
	bool active = true;

	sf::Color outColor = sf::Color(227, 132, 255);
	sf::Color inColor = sf::Color(134, 93, 255);

public:
	sf::RectangleShape out;
private:
	sf::RectangleShape in;
	sf::RectangleShape fill;
	sf::Vector2f pos;
	sf::Color backgroundColor;
	sf::Vector2f size;

	std::vector<std::shared_ptr<CheckBox>>* boxes = nullptr;
public:
	float distanceBetween = 0;

	CheckBox(std::vector<std::shared_ptr<CheckBox>>& ptr, sf::Vector2f position, sf::Vector2f windowSize, sf::Color bcgColor, int gen, int noGen);
	void clicked(bool first);
	void generateNextGen();
	void resize(sf::Vector2f newWindowSize);
	void draw(sf::RenderWindow& window);
	void updatePosSize();
	void updateColor();
};

