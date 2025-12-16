#include <vector>

void Filter(std::vector<int>& vec, bool (*predicate)(int)) {
    // Если предикат nullptr или вектор пуст, ничего не делаем
    if (!predicate || vec.empty()) {
        return;
    }

    // Ищем первый элемент, который нужно удалить
    size_t write_pos = 0;
    while (write_pos < vec.size() && predicate(vec[write_pos])) {
        ++write_pos;
    }

    // Если все элементы удовлетворяют предикату, ничего не делаем
    if (write_pos == vec.size()) {
        return;
    }

    // Проходим по оставшимся элементам
    for (size_t read_pos = write_pos + 1; read_pos < vec.size(); ++read_pos) {
        if (predicate(vec[read_pos])) {
            vec[write_pos] = vec[read_pos];
            ++write_pos;
        }
    }

    // Уменьшаем размер вектора
    vec.resize(write_pos);
}