#include <iostream>
#include "model.h"
#include "Smart_calculator.h"

int main()
{
	Model a;
	std::string input;
	std::cin >> input;
	a.Calculate(input);
	return 0;
}