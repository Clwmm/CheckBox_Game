#include "CheckBox.h"

CheckBox::CheckBox(std::vector<std::shared_ptr<CheckBox>>& ptr, sf::Vector2f position, sf::Vector2f windowSize, sf::Color bcgColor, int gen, int noGen)
	:boxes{ &ptr }, pos{ position }, backgroundColor{ bcgColor }, generation{ gen }
{
	out.setOutlineThickness(2);
	fill.setFillColor(backgroundColor);
	in.setFillColor(inColor);
	

	if (pos.x == 0)
	{
		pos.x = windowSize.x / 2;
		pos.y = windowSize.y / 2;
		distanceBetween = windowSize.x * 0.05;
		int noBox = 1;
		for (int i = 0; i < noGen - 1; i++)
			noBox += 2;
		if (windowSize.y >= windowSize.x)
		{
			size.x = (windowSize.x - (distanceBetween * noBox)) / noBox;
			size.y = (windowSize.x - (distanceBetween * noBox)) / noBox;
		}
		else
		{
			size.x = (windowSize.y - (distanceBetween * noBox)) / noBox;
			size.y = (windowSize.y - (distanceBetween * noBox)) / noBox;
		}
	}
	else
		size = windowSize;

	
	this->updatePosSize();
	this->updateColor();
}

void CheckBox::clicked(bool first)
{
	if (first)
	{
		active = !active;
		this->updateColor();
	}
	else
	{
		if (one != nullptr)
			one->clicked(false);
		if (two != nullptr)
			two->clicked(false);
		if (three != nullptr)
			three->clicked(false);
		if (four != nullptr)
			four->clicked(false);
		if (five != nullptr)
			five->clicked(false);
		if (six != nullptr)
			six->clicked(false);
		if (seven != nullptr)
			seven->clicked(false);
		if (eight != nullptr)
			eight->clicked(false);
		active = !active;
		this->updateColor();
	}
}

void CheckBox::generateNextGen()
{
	if (one == nullptr)
	{
		sf::Vector2f tempPos = sf::Vector2f(pos.x - size.x - distanceBetween, pos.y - size.x - distanceBetween);
		one = std::make_shared<CheckBox>(boxes, tempPos, sf::Vector2f(0, 0), backgroundColor, generation + 1, 0);
		one->distanceBetween = this->distanceBetween;
		//boxes->push_back(one);
	}
}

void CheckBox::resize(sf::Vector2f newWindowSize)
{
}

void CheckBox::draw(sf::RenderWindow& window)
{
	if (active)
	{
		window.draw(out);
		window.draw(fill);
		window.draw(in);
	}
	else
		window.draw(out);
}

void CheckBox::updatePosSize()
{
	out.setPosition(pos);
	out.setSize(sf::Vector2f(size.x, size.y));
	out.setOrigin(sf::Vector2f(out.getSize().x / 2, out.getSize().y / 2));
	fill.setPosition(pos);
	fill.setSize(sf::Vector2f(size.x * 0.7, size.y * 0.7));
	fill.setOrigin(sf::Vector2f(fill.getSize().x / 2, fill.getSize().y / 2));
	in.setPosition(pos);
	in.setSize(sf::Vector2f(size.x * 0.4, size.y * 0.4));
	in.setOrigin(sf::Vector2f(in.getSize().x / 2, in.getSize().y / 2));
}

void CheckBox::updateColor()
{
	if (active)
	{
		out.setFillColor(inColor);
		out.setOutlineColor(inColor);
	}
	else
	{
		out.setFillColor(backgroundColor);
		out.setOutlineColor(outColor);
	}
}
