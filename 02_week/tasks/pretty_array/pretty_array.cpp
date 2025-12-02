#include <stdexcept>
#include <iostream>

void PrintArray(const int *begin, const int *end, size_t limit = 0)
{
    // throw std::runtime_error{"Not implemented"};
    // Проверка на nullptr или пустой массив
    if (begin == nullptr || end == nullptr)
    {
        std::cout << "[]\n";
        return;
    }

    // Вычисляем количество элементов
    size_t count = 0;
    bool reverse = false;
    const int *current = nullptr;

    if (end > begin)
    {
        // Обычный порядок
        count = end - begin;
        current = begin;
        reverse = false;
    }
    else if (end < begin)
    {
        // Обратный порядок
        count = begin - end;
        current = begin;
        reverse = true;
    }
    else
    {
        // Пустой массив
        std::cout << "[]\n";
        return;
    }

    std::cout << '[';

    if (limit == 0 || limit >= count)
    {
        // Вывод без ограничения
        for (size_t i = 0; i < count; ++i)
        {
            if (i > 0)
                std::cout << ", ";
            std::cout << *current;

            if (reverse)
            {
                --current;
            }
            else
            {
                ++current;
            }
        }
        std::cout << "]\n";
        return;
    }

    // Вывод с ограничением
    size_t elements_printed = 0;
    size_t elements_in_current_line = 0;

    while (elements_printed < count)
    {
        if (elements_in_current_line > 0)
        {
            std::cout << ", ";
        }

        std::cout << *current;
        ++elements_printed;
        ++elements_in_current_line;

        // Переход к следующему элементу
        if (reverse)
        {
            --current;
        }
        else
        {
            ++current;
        }

        // Проверяем, нужно ли переносить строку
        if (elements_in_current_line == limit && elements_printed < count)
        {
            std::cout << ", ...\n ";
            elements_in_current_line = 0;
        }
    }

    std::cout << "]\n";
}