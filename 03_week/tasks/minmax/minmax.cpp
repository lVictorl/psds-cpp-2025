#include <utility>
#include <vector>

std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> MinMax(
    const std::vector<int>& vec) {
    // Обработка пустого вектора
    if (vec.empty()) {
        return {vec.cend(), vec.cend()};
    }

    // Начинаем с первого элемента
    size_t min_idx = 0;
    size_t max_idx = 0;

    // Проходим по всем элементам
    for (size_t i = 1; i < vec.size(); ++i) {
        // Обновляем минимум при нахождении меньшего элемента
        if (vec[i] < vec[min_idx]) {
            min_idx = i;
        }
        // Обновляем максимум при нахождении большего или равного элемента
        else if (vec[i] >= vec[max_idx]) {
            max_idx = i;
        }
    }

    // Возвращаем итераторы на найденные позиции
    return {vec.begin() + min_idx, vec.begin() + max_idx};
}