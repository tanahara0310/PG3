#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(float w, float h) : width(w), height(h), area(0.0f)
{
}

void Rectangle::Size()
{
	area = width * height;
}

void Rectangle::Draw()
{
	std::cout << "Rectangle Area: " << area << std::endl;
}
