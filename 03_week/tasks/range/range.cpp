#include <vector>

std::vector<int> Range(int from, int to, int step = 1) {
    std::vector<int> result;

    // Обработка некорректных параметров
    if (step == 0) {
        return result;
    }

    // Проверяем, имеет ли смысл генерировать диапазон
    bool should_generate = (step > 0 && from < to) || (step < 0 && from > to);
    if (!should_generate) {
        return result;
    }

    // Подсчитываем количество элементов

    int count = 0;
    if (step > 0) {
        // Используем деление для вычисления размера
        count = (to - from + step - 1) / step;  // Округление вверх
        if (count > 0 && from + (count - 1) * step >= to) {
            count--;
        }
    } else {
        int abs_step = -step;
        count = (from - to + abs_step - 1) / abs_step;  // Округление вверх
        if (count > 0 && from + (count - 1) * step <= to) {
            count--;
        }
    }

    if (count > 0) {
        result.reserve(count);
        for (int i = 0, value = from; i < count; ++i, value += step) {
            result.push_back(value);
        }
    }

    return result;
}