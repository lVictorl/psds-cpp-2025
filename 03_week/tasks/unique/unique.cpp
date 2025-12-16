#include <vector>

std::vector<int> Unique(const std::vector<int>& vec) {
    // Если вектор пуст, возвращаем пустой вектор
    if (vec.empty()) {
        return {};
    }

    // Создаем результирующий вектор
    std::vector<int> result;

    // Резервируем память - в худшем случае все элементы уникальны
    result.reserve(vec.size());

    // Первый элемент всегда добавляем
    result.push_back(vec[0]);

    // Проходим по вектору, начиная со второго элемента
    for (size_t i = 1; i < vec.size(); ++i) {
        // Если текущий элемент отличается от предыдущего (и предыдущего в результате)
        if (vec[i] != result.back()) {
            result.push_back(vec[i]);
        }
    }

    // Освобождаем лишнюю память (чтобы capacity == size)
    result.shrink_to_fit();

    return result;
}