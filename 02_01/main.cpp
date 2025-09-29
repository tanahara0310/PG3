#include <iostream>


template<typename T>
T Min(const T& num1, const T& num2) {
	return (num1 < num2) ? num1 : num2;
}

int main()
{
	std::cout << Min(10, 20) << std::endl; //int

	std::cout << Min(10.5f, 20.3f) << std::endl; // float

	std::cout << Min(10.5, 20.5) << std::endl; // double

	return 0;
}