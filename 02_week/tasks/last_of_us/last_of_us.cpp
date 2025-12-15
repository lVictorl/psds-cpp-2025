#include <stdexcept>

<<<<<<< HEAD
const int *FindLastElement(const int *begin, const int *end, bool (*predicate)(int))
{
    // throw std::runtime_error{"Not implemented"};
    //  Проверка на некорректные указатели
    if (begin == nullptr || end == nullptr)
    {
        return end; // Если end тоже nullptr, вернется nullptr
    }

    // Проверка на некорректный диапазон (begin > end)
    if (begin > end)
    {
        return end;
    }

    // Если диапазон пустой
    if (begin == end)
    {
        return end;
    }

    // Ищем последний элемент, удовлетворяющий условию
    const int *current = end - 1; // Начинаем с последнего элемента

    while (current >= begin)
    {
        if (predicate(*current))
        {
            return current;
        }

        // Проверяем, не вышли ли за начало массива
        if (current == begin)
        {
            break;
        }
        current--;
    }

    // Если элемент не найден, возвращаем end
    return end;
=======

/* return_type */ FindLastElement(/* ptr_type */ begin, /* ptr_type */ end, /* func_type */ predicate) {
    throw std::runtime_error{"Not implemented"};
>>>>>>> 4477f12d1d360b59708503f7b0b325acb0c5bc52
}