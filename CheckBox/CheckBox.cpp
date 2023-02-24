#include "CheckBox.h"

CheckBox::CheckBox(std::vector<CheckBox*>* ptr, sf::Vector2f position, sf::Vector2f windowSize, sf::Color bcgColor, int gen, int _noGen, bool first)
	:boxes{ ptr }, pos{ position }, backgroundColor{ bcgColor }, generation{ gen }, noGen{_noGen}
{
	if (noGen <= 6)
		out.setOutlineThickness(2);
	else
		out.setOutlineThickness(1);
	fill.setFillColor(backgroundColor);
	in.setFillColor(inColor);
	

	if (first)
	{
		pos = position;
		if(noGen <= 2)
			distanceBetween = windowSize.x * 0.05;
		else if (noGen <= 8)
			distanceBetween = windowSize.x * 0.01;
		else if (noGen <= 13)
			distanceBetween = 5;
		else
			distanceBetween = 3;
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
		if (two != nullptr)
			two->clicked(false);
		if (four != nullptr)
			four->clicked(false);
		if (five != nullptr)
			five->clicked(false);
		if (seven != nullptr)
			seven->clicked(false);

		/*if (one != nullptr)
			one->clicked(false);
		if (three != nullptr)
			three->clicked(false);
		if (six != nullptr)
			six->clicked(false);
		if (eight != nullptr)
			eight->clicked(false);*/

		active = !active;
		this->updateColor();
	}
	else
	{
		active = !active;
		this->updateColor();
	}
}

void CheckBox::generateNextGen()
{
	if (one == nullptr)
	{
		sf::Vector2f tempPos = sf::Vector2f(pos.x - size.x - distanceBetween, pos.y - size.x - distanceBetween);
		one = new CheckBox(boxes, tempPos, size, backgroundColor, generation + 1, noGen, false);
		one->distanceBetween = this->distanceBetween;
		one->eight = this;
		if (this->two != nullptr)
		{
			one->five = two;
			two->four = one;
		}
		if (this->four != nullptr)
		{
			one->seven = four;
			four->two = one;
		}
		boxes->push_back(one);
	}
	else
	{
		one->eight = this;
		if (this->two != nullptr)
		{
			one->five = two;
			two->four = one;
		}
		if (this->four != nullptr)
		{
			one->seven = four;
			four->two = one;
		}
	}

	if (two == nullptr)
	{
		sf::Vector2f tempPos = sf::Vector2f(pos.x, pos.y - size.x - distanceBetween);
		two = new CheckBox(boxes, tempPos, size, backgroundColor, generation + 1, noGen, false);
		two->distanceBetween = this->distanceBetween;
		two->seven = this;
		if (this->one != nullptr)
		{
			two->four = one;
			one->five = two;
		}
		if (this->three != nullptr)
		{
			two->five = three;
			three->four = two;
		}
		if (this->four != nullptr)
		{
			two->six = four;
			four->three = two;
		}
		if (this->five != nullptr)
		{
			two->eight = five;
			five->one = two;
		}
		boxes->push_back(two);
	}
	else
	{
		two->seven = this;
		if (this->one != nullptr)
		{
			two->four = one;
			one->five = two;
		}
		if (this->three != nullptr)
		{
			two->five = three;
			three->four = two;
		}
		if (this->four != nullptr)
		{
			two->six = four;
			four->three = two;
		}
		if (this->five != nullptr)
		{
			two->eight = five;
			five->one = two;
		}
	}

	if (three == nullptr)
	{
		sf::Vector2f tempPos = sf::Vector2f(pos.x + size.x + distanceBetween, pos.y - size.x - distanceBetween);
		three = new CheckBox(boxes, tempPos, size, backgroundColor, generation + 1, noGen, false);
		three->distanceBetween = this->distanceBetween;
		three->six = this;
		if (this->two != nullptr)
		{
			three->four = two;
			two->five = three;
		}
		if (this->five != nullptr)
		{
			three->seven = five;
			five->two = three;
		}
		boxes->push_back(three);
	}
	else
	{
		three->six = this;
		if (this->two != nullptr)
		{
			three->four = two;
			two->five = three;
		}
		if (this->five != nullptr)
		{
			three->seven = five;
			five->two = three;
		}
	}

	if (four == nullptr)
	{
		sf::Vector2f tempPos = sf::Vector2f(pos.x - size.x - distanceBetween, pos.y);
		four = new CheckBox(boxes, tempPos, size, backgroundColor, generation + 1, noGen, false);
		four->distanceBetween = this->distanceBetween;
		four->five = this;
		if (this->one != nullptr)
		{
			four->two = one;
			one->seven = four;
		}
		if (this->six != nullptr)
		{
			four->seven = six;
			six->two = four;
		}
		if (this->two != nullptr)
		{
			four->three = two;
			two->six = four;
		}
		if (this->seven != nullptr)
		{
			four->eight = seven;
			seven->one = four;
		}
		boxes->push_back(four);
	}
	else
	{
		four->five = this;
		if (this->one != nullptr)
		{
			four->two = one;
			one->seven = four;
		}
		if (this->six != nullptr)
		{
			four->seven = six;
			six->two = four;
		}
		if (this->two != nullptr)
		{
			four->three = two;
			two->six = four;
		}
		if (this->seven != nullptr)
		{
			four->eight = seven;
			seven->one = four;
		}
	}

	if (five == nullptr)
	{
		sf::Vector2f tempPos = sf::Vector2f(pos.x + size.x + distanceBetween, pos.y);
		five = new CheckBox(boxes, tempPos, size, backgroundColor, generation + 1, noGen, false);
		five->distanceBetween = this->distanceBetween;
		five->four = this;
		if (this->three != nullptr)
		{
			five->two = three;
			three->seven = five;
		}
		if (this->eight != nullptr)
		{
			five->seven = eight;
			eight->two = five;
		}
		if (this->two != nullptr)
		{
			five->one = two;
			two->eight = five;
		}
		if (this->seven != nullptr)
		{
			five->six = seven;
			seven->three = five;
		}
		boxes->push_back(five);
	}
	else
	{
		five->four = this;
		if (this->three != nullptr)
		{
			five->two = three;
			three->seven = five;
		}
		if (this->eight != nullptr)
		{
			five->seven = eight;
			eight->two = five;
		}
		if (this->two != nullptr)
		{
			five->one = two;
			two->eight = five;
		}
		if (this->seven != nullptr)
		{
			five->six = seven;
			seven->three = five;
		}
	}

	if (six == nullptr)
	{
		sf::Vector2f tempPos = sf::Vector2f(pos.x - size.x - distanceBetween, pos.y + size.x + distanceBetween);
		six = new CheckBox(boxes, tempPos, size, backgroundColor, generation + 1, noGen, false);
		six->distanceBetween = this->distanceBetween;
		six->three = this;
		if (this->four != nullptr)
		{
			six->two = four;
			four->seven = six;
		}
		if (this->seven != nullptr)
		{
			six->five = seven;
			seven->four = six;
		}
		boxes->push_back(six);
	}
	else
	{
		six->three = this;
		if (this->four != nullptr)
		{
			six->two = four;
			four->seven = six;
		}
		if (this->seven != nullptr)
		{
			six->five = seven;
			seven->four = six;
		}
	}

	if (seven == nullptr)
	{
		sf::Vector2f tempPos = sf::Vector2f(pos.x, pos.y + size.x + distanceBetween);
		seven = new CheckBox(boxes, tempPos, size, backgroundColor, generation + 1, noGen, false);
		seven->distanceBetween = this->distanceBetween;
		seven->two = this;
		if (this->six != nullptr)
		{
			seven->four = six;
			six->five = seven;
		}
		if (this->eight != nullptr)
		{
			seven->five = eight;
			eight->four = seven;
		}
		if (this->four != nullptr)
		{
			seven->one = four;
			four->eight = seven;
		}
		if (this->five != nullptr)
		{
			seven->three = five;
			five->six = seven;
		}
		boxes->push_back(seven);
	}
	else
	{
		seven->two = this;
		if (this->six != nullptr)
		{
			seven->four = six;
			six->five = seven;
		}
		if (this->eight != nullptr)
		{
			seven->five = eight;
			eight->four = seven;
		}
		if (this->four != nullptr)
		{
			seven->one = four;
			four->eight = seven;
		}
		if (this->five != nullptr)
		{
			seven->three = five;
			five->six = seven;
		}
	}

	if (eight == nullptr)
	{
		sf::Vector2f tempPos = sf::Vector2f(pos.x + size.x + distanceBetween, pos.y + size.x + distanceBetween);
		eight = new CheckBox(boxes, tempPos, size, backgroundColor, generation + 1, noGen, false);
		eight->distanceBetween = this->distanceBetween;
		eight->one = this;
		if (this->seven != nullptr)
		{
			eight->four = seven;
			seven->five = eight;
		}
		if (this->five != nullptr)
		{
			eight->two = five;
			five->seven = eight;
		}
		boxes->push_back(eight);
	}
	else
	{
		eight->one = this;
		if (this->seven != nullptr)
		{
			eight->four = seven;
			seven->five = eight;
		}
		if (this->five != nullptr)
		{
			eight->two = five;
			five->seven = eight;
		}
	}
}

void CheckBox::resize(sf::Vector2f newWindowSize, sf::Vector2f centerPos, bool first)
{
	if (!resized)
	{
		if (first)
		{
			pos = centerPos;
			if (noGen <= 4)
				distanceBetween = newWindowSize.x * 0.05;
			else if (noGen <= 8)
				distanceBetween = newWindowSize.x * 0.01;
			else if (noGen <= 13)
				distanceBetween = 5;
			else
				distanceBetween = 3;
			int noBox = 1;
			for (int i = 0; i < noGen - 1; i++)
				noBox += 2;
			if (newWindowSize.y >= newWindowSize.x)
			{
				size.x = (newWindowSize.x - (distanceBetween * noBox)) / noBox;
				size.y = (newWindowSize.x - (distanceBetween * noBox)) / noBox;
			}
			else
			{
				size.x = (newWindowSize.y - (distanceBetween * noBox)) / noBox;
				size.y = (newWindowSize.y - (distanceBetween * noBox)) / noBox;
			}

			if (one != nullptr)
			{
				one->distanceBetween = this->distanceBetween;
				one->resize(size, sf::Vector2f(pos.x - size.x - distanceBetween, pos.y - size.x - distanceBetween), false);
			}
				
			if (two != nullptr)
			{
				two->distanceBetween = this->distanceBetween;
				two->resize(size, sf::Vector2f(pos.x, pos.y - size.x - distanceBetween), false);
			}
				
			if (three != nullptr)
			{
				three->distanceBetween = this->distanceBetween;
				three->resize(size, sf::Vector2f(pos.x + size.x + distanceBetween, pos.y - size.x - distanceBetween), false);
			}
				
			if (four != nullptr)
			{
				four->distanceBetween = this->distanceBetween;
				four->resize(size, sf::Vector2f(pos.x - size.x - distanceBetween, pos.y), false);
			}
				
			if (five != nullptr)
			{
				five->distanceBetween = this->distanceBetween;
				five->resize(size, sf::Vector2f(pos.x + size.x + distanceBetween, pos.y), false);
			}
				
			if (six != nullptr)
			{
				six->distanceBetween = this->distanceBetween;
				six->resize(size, sf::Vector2f(pos.x - size.x - distanceBetween, pos.y + size.x + distanceBetween), false);
			}
				
			if (seven != nullptr)
			{
				seven->distanceBetween = this->distanceBetween;
				seven->resize(size, sf::Vector2f(pos.x, pos.y + size.x + distanceBetween), false);
			}
				
			if (eight != nullptr)
			{
				eight->distanceBetween = this->distanceBetween;
				eight->resize(size, sf::Vector2f(pos.x + size.x + distanceBetween, pos.y + size.x + distanceBetween), false);
			}
				
		}
		else
		{
			size = newWindowSize;
			pos = centerPos;
			/*if (one != nullptr)
				one->resize(size, sf::Vector2f(pos.x - size.x - distanceBetween, pos.y - size.x - distanceBetween), false);
			if (two != nullptr)
				two->resize(size, sf::Vector2f(pos.x, pos.y - size.x - distanceBetween), false);
			if (three != nullptr)
				three->resize(size, sf::Vector2f(pos.x + size.x + distanceBetween, pos.y - size.x - distanceBetween), false);
			if (four != nullptr)
				four->resize(size, sf::Vector2f(pos.x - size.x - distanceBetween, pos.y), false);
			if (five != nullptr)
				five->resize(size, sf::Vector2f(pos.x + size.x + distanceBetween, pos.y), false);
			if (six != nullptr)
				six->resize(size, sf::Vector2f(pos.x - size.x - distanceBetween, pos.y + size.x + distanceBetween), false);
			if (seven != nullptr)
				seven->resize(size, sf::Vector2f(pos.x, pos.y + size.x + distanceBetween), false);
			if (eight != nullptr)
				eight->resize(size, sf::Vector2f(pos.x + size.x + distanceBetween, pos.y + size.x + distanceBetween), false);*/
		}

		resized = true;
		updatePosSize();
	}
	/*else
	{
		if (one != nullptr)
			one->resize(size, sf::Vector2f(pos.x - size.x - distanceBetween, pos.y - size.x - distanceBetween), false);
		if (two != nullptr)
			two->resize(size, sf::Vector2f(pos.x, pos.y - size.x - distanceBetween), false);
		if (three != nullptr)
			three->resize(size, sf::Vector2f(pos.x + size.x + distanceBetween, pos.y - size.x - distanceBetween), false);
		if (four != nullptr)
			four->resize(size, sf::Vector2f(pos.x - size.x - distanceBetween, pos.y), false);
		if (five != nullptr)
			five->resize(size, sf::Vector2f(pos.x + size.x + distanceBetween, pos.y), false);
		if (six != nullptr)
			six->resize(size, sf::Vector2f(pos.x - size.x - distanceBetween, pos.y + size.x + distanceBetween), false);
		if (seven != nullptr)
			seven->resize(size, sf::Vector2f(pos.x, pos.y + size.x + distanceBetween), false);
		if (eight != nullptr)
			eight->resize(size, sf::Vector2f(pos.x + size.x + distanceBetween, pos.y + size.x + distanceBetween), false);
	}*/
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
