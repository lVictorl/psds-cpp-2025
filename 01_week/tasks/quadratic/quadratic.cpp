#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

void PrintRoot(double root)
{
    if (std::abs(root) < 1e-10)
    { // Проверяем, близок ли корень к нулю
        std::cout << "0";
    }
    else
    {
        std::cout << root;
    }
}

void SolveQuadratic(int a, int b, int c)
{
    // throw std::runtime_error{"Not implemented"};
    std::cout << std::setprecision(6);

    // Случай: a = 0 (линейное уравнение)
    if (a == 0)
    {
        // Случай: b = 0
        if (b == 0)
        {
            if (c == 0)
            {
                std::cout << "infinite solutions";
            }
            else
            {
                std::cout << "no solutions";
            }
        }
        else
        {
            // Линейное уравнение: bx + c = 0
            double root = -static_cast<double>(c) / b;
            PrintRoot(root);
        }
        return;
    }

    // Квадратное уравнение
    double discriminant = static_cast<double>(b) * b - 4.0 * a * c;

    if (discriminant < 0)
    {
        std::cout << "no solutions";
    }
    else if (discriminant == 0)
    {
        // Один корень
        double root = -static_cast<double>(b) / (2.0 * a);
        PrintRoot(root);
    }
    else
    {
        // Два корня
        double sqrt_d = std::sqrt(discriminant);
        double root1 = (-b - sqrt_d) / (2.0 * a);
        double root2 = (-b + sqrt_d) / (2.0 * a);

        // Упорядочиваем корни по возрастанию
        if (root1 > root2)
        {
            std::swap(root1, root2);
        }

        PrintRoot(root1);
        std::cout << " ";
        PrintRoot(root2);
    }
}
