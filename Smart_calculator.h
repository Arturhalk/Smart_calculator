#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <ctype.h>
#include <math.h>
#include "model.h"

std::string Model::TransformToRPN(std::string const &input)
{
	std::map<char, unsigned> priority = {{'(', -1}, {'+', 0}, {'-', 0}, {'*', 1}, {'/', 1}, {'^', 2}};
	std::string output = "";
	std::stack<char> operators;
	bool prevIsOperator = true;

	for (auto it = input.begin(); it != input.end(); ++it)
	{
		if (isdigit(*it) || *it == '.')
		{
			while (it != input.end() && (isdigit(*it) || *it == '.'))
			{
				output += *it;
				++it;
			}
			output += " ";
			--it;
			prevIsOperator = false;
		}
		else if (*it == ' ')
		{
			continue;
		}
		else if (*it == '(')
		{
			operators.push(*it);
			prevIsOperator = true;
		}
		else if (*it == ')')
		{
			while (!operators.empty() && operators.top() != '(')
			{
				output += operators.top();
				operators.pop();
			}
			operators.pop();
			prevIsOperator = false;
		}
		else if (*it == '-' && (prevIsOperator || operators.size() && operators.top() == '('))
		{
			operators.push('u');
			prevIsOperator = true;
		}
		else
		{
			while (!operators.empty() && priority[operators.top()] >= priority[*it] && operators.top() != '(')
			{
				output += operators.top();
				operators.pop();
			}
			operators.push(*it);
			prevIsOperator = true;
		}
	}
	while (!operators.empty())
	{
		output += operators.top();
		operators.pop();
	}
	return output;
}

std::string Model::ParsNumb(std::string::const_iterator &it)
{
	std::string exitString = "";
	while (isdigit(*it) || *it == '.')
	{
		exitString += *it;
		++it;
	}
	return exitString;
}

double Model::CalculateRPN(std::string const &RPN)
{
	std::stack<double> numbers;
	for (auto it = RPN.begin(); it < RPN.end(); ++it)
	{
		if (isdigit(*it))
		{
			double n = std::stod(ParsNumb(it));
			numbers.push(n);
		}
		else if (*it == 'u')
		{
			double a = numbers.top();
			numbers.pop();
			numbers.push(-a);
		}
		else
		{
			double a = numbers.top();
			numbers.pop();
			double b = numbers.top();
			numbers.pop();
			double result = 0;
			switch (*it)
			{
			case '+':
				result = a + b;
				break;
			case '-':
				result = b - a;
				break;
			case '*':
				result = a * b;
				break;
			case '/':
				result = b / a;
				break;
			case '^':
				result = pow(b, a);
				break;
			}
			numbers.push(result);
		}
	}
	return numbers.top();
}

void Model::Calculate(std::string const &input)
{
	std::cout << CalculateRPN(TransformToRPN(input));
}