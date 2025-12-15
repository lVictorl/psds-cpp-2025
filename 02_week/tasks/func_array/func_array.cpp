#include <stdexcept>

<<<<<<< HEAD
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
=======

double ApplyOperations(double a, double b /* other arguments */) {
    throw std::runtime_error{"Not implemented"};
>>>>>>> 4477f12d1d360b59708503f7b0b325acb0c5bc52
}