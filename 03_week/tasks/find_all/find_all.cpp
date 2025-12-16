#include <cstddef>
#include <vector>

std::vector<size_t> FindAll(const std::vector<int>& vec, bool (*predicate)(int)) {
    if (!predicate) {
        return {};
    }

    std::vector<size_t> result;

    // Можно сразу зарезервировать память, но не обязательно
    // result.reserve(vec.size() / 2); // Для IsEven

    for (size_t i = 0; i < vec.size(); ++i) {
        if (predicate(vec[i])) {
            result.push_back(i);
        }
    }

    // Для выполнения теста CapacityOptimization
    // shrink_to_fit обеспечит capacity == size
    result.shrink_to_fit();

    return result;
}