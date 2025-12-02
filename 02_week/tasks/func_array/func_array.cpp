#include <stdexcept>

double ApplyOperations(double a, double b, double (**operations)(double, double), size_t size)
{
    // throw std::runtime_error{"Not implemented"};
    if (operations == nullptr || size == 0)
    {
        return 0.0;
    }

    double sum = 0.0;
    for (size_t i = 0; i < size; ++i)
    {
        if (operations[i] != nullptr)
        {
            sum += operations[i](a, b);
        }
    }

    return sum;
}