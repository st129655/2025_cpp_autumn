#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>


double evaluateRPN(const std::string& expr)
{
    std::istringstream stream(expr);
    std::stack<double> sol;
    std::string oper;

    while (stream >> oper) 
    {
        if (oper == "+" || oper == "-" || oper == "*" || oper == "/") 
        {
            double second_operand = sol.top(); sol.pop();
            double first_operand = sol.top(); sol.pop();
            if (oper == "+") sol.push(first_operand + second_operand);
            else if (oper == "-") sol.push(first_operand - second_operand);
            else if (oper == "*") sol.push(first_operand * second_operand);
            else sol.push(first_operand / second_operand);
        }
        else 
        {
            sol.push(std::stod(oper));
        }
    }
    return sol.top();
}

int main(int argc,char** argv) {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    std::string line;
    while (std::getline(in, line)) 
    {
        double result = evaluateRPN(line);
        out << line << " = " << result << std::endl;
    }
    return 0;
}
