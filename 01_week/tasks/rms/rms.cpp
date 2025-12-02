#include <cstddef>
#include <stdexcept>

double CalculateRMS(double values[], size_t size)
{
    // throw std::runtime_error{"Not implemented"};
    //  Обработка особых случаев: пустой массив или nullptr
    if (values == nullptr || size == 0)
    {
        return 0.0;
    }

    // Вычисление суммы квадратов элементов
    double sum_of_squares = 0.0;
    for (size_t i = 0; i < size; ++i)
    {
        sum_of_squares += values[i] * values[i];
    }

    // Вычисление среднего значения квадратов и извлечение корня
    double mean_of_squares = sum_of_squares / size;
    return std::sqrt(mean_of_squares);
}