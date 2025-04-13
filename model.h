#pragma once
#include <string>

class Model
{
    std::string TransformToRPN(std::string const &input);

    std::string ParsNumb(std::string::const_iterator &it);

    double CalculateRPN(std::string const &RPN);

public:
    void Calculate(std::string const &input);
};
