#include <stdexcept>
const int *FindLastElement(const int *begin, const int *end, bool (*predicate)(int))
{
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
}