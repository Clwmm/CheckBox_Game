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
	CheckBox* one = nullptr;
	CheckBox* two = nullptr;
	CheckBox* three = nullptr;
	CheckBox* four = nullptr;
	CheckBox* five = nullptr;
	CheckBox* six = nullptr;
	CheckBox* seven = nullptr;
	CheckBox* eight = nullptr;
	
	int generation = 0;
	bool active = false;

private:
	int noGen = 0;
	float distanceBetween = 0;
	sf::Vector2i index = sf::Vector2i(0, 0);
	sf::Color outColor = sf::Color(227, 132, 255);
	sf::Color inColor = sf::Color(134, 93, 255);

public:
	sf::RectangleShape out;
private:
	sf::RectangleShape in;
	sf::RectangleShape fill;

	sf::Vector2f pos;
	sf::Vector2f centerPos;

	sf::Color backgroundColor;
	sf::Vector2f size;

	std::vector<CheckBox*>* boxes = nullptr;
public:
	CheckBox(std::vector<CheckBox*>* ptr, sf::Vector2f windowSize, sf::Vector2f _centerPos, sf::Vector2i _index, sf::Color bcgColor, int gen, int _noGen);
private:
	CheckBox(std::vector<CheckBox*>* ptr, sf::Vector2f _size, float disBetween, sf::Vector2f _centerPos, sf::Vector2i _index, sf::Color bcgColor, int gen, int _noGen);
public:
	void clicked(bool first);
	void generateNextGen();
	void resize(sf::Vector2f newWindowSize);
	void draw(sf::RenderWindow& window);
	void updatePosSize();
	void updateColor();
};

