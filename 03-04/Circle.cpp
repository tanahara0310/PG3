#include "Circle.h"
#include <iostream>

Circle::Circle(float r) : radius(r), area(0.0f)
{
}

void Circle::Size() {

	area = 3.14f * radius * radius;
}

void Circle::Draw() {

	std::cout << "Circle Area: " << area << std::endl;
}
