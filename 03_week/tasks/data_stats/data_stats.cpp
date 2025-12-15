#include <stdexcept>
#include <vector>
#include <cmath>

struct DataStats
{
    double avg = 0.0;
    double sd = 0.0;
};

DataStats CalculateDataStats(const std::vector<int> &data)
{
    DataStats res;

    // Ветор пуст?
    if (data.empty())
    {
        return res; // Значения по умолчанию
    }

    long long sum = 0;
    long long sum_squares = 0;

    for (int value : data)
    {
        sum += value;
        sum_squares += static_cast<long long>(value) * value;
    }

    // Мат.ожидание
    std::vector<int>::size_type n = data.size();
    res.avg = static_cast<double>(sum) / n;

    // Дисперсия и СКО
    double mean_of_squares = static_cast<double>(sum_squares) / n;
    double mean_in_square = res.avg * res.avg;
    double dispersion = mean_in_square - mean_of_squares;

    // Защита от ошибок округления (дисперсия не может быть отрицательной)
    if (dispersion < 0.0)
    {
        dispersion = 0.0;
    }
    res.sd = std::sqrt(dispersion);

    return res;
}
