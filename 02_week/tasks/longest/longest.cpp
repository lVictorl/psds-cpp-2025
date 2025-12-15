#include <stdexcept>

const char *FindLongestSubsequence(const char *begin, const char *end, size_t &count)
{
    // throw std::runtime_error{"Not implemented"};
    // Проверка на некорректные указатели или диапазон
    if (begin == nullptr || end == nullptr || begin > end)
    {
        count = 0;
        return nullptr;
    }

    // Проверка на пустой диапазон
    if (begin == end)
    {
        count = 0;
        return nullptr;
    }

    const char *current_start = begin;
    const char *longest_start = begin;
    size_t current_length = 1;
    size_t max_length = 1;

    const char *current = begin + 1;

    while (current < end)
    {
        // Если текущий символ совпадает с символом в current_start
        if (*current == *(current_start))
        {
            current_length++;
        }
        else
        {
            // Если текущая подпоследовательность длиннее максимальной
            if (current_length > max_length)
            {
                max_length = current_length;
                longest_start = current_start;
            }
            // Начинаем новую подпоследовательность
            current_start = current;
            current_length = 1;
        }
        current++;
    }

    // Проверяем последнюю подпоследовательность
    if (current_length > max_length)
    {
        max_length = current_length;
        longest_start = current_start;
    }

    count = max_length;
    return longest_start;
}
