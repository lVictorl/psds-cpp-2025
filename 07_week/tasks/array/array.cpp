#include <initializer_list>

template <typename T, std::size_t N>
class Array {
   private:
    T data_[N];

   public:
    // Конструктор по умолчанию
    Array() : data_{} {}

    // Конструктор от std::initializer_list.
    // Копирует элементы из списка, остальные инициализируются значением T()
    Array(std::initializer_list<T> init) : data_{} {
        std::size_t to_copy = init.size() < N ? init.size() : N;
        const T* src = init.begin();
        for (std::size_t i = 0; i < to_copy; ++i) {
            data_[i] = src[i];
        }
        // Остальные уже value-инициализированы благодаря data_{}
    }

    // Конструктор копирования (генерируется компилятором)
    Array(const Array&) = default;

    // Конструктор перемещения (генерируется компилятором)
    Array(Array&&) = default;

    // Оператор присваивания копированием (генерируется компилятором)
    Array& operator=(const Array&) = default;

    // Оператор присваивания перемещением ( компилятором)
    Array& operator=(Array&&) = default;

    // Деструктор (компилятором)
    ~Array() = default;

    // Оператор индексирования (неконстантный)
    T& operator[](std::size_t index) { return data_[index]; }

    // Оператор индексирования (константный)
    const T& operator[](std::size_t index) const { return data_[index]; }

    // Доступ к первому элементу разными способами
    T& Front() { return data_[0]; }

    const T& Front() const { return data_[0]; }

    // Доступ к последнему элементу аналогично
    T& Back() { return data_[N - 1]; }

    const T& Back() const { return data_[N - 1]; }

    // Прямой доступ к памяти
    T* Data() { return data_; }

    const T* Data() const { return data_; }

    // Проверка на пустоту
    bool Empty() const { return N == 0; }

    // Размер контейнера
    std::size_t Size() const { return N; }

    // Заполнение массива заданным значением (ручной цикл)
    void Fill(const T& value) {
        for (std::size_t i = 0; i < N; ++i) {
            data_[i] = value;
        }
    }

    // Обмен содержимым с другим массивом (поэлементный обмен с перемещением)
    void Swap(Array& other) {
        for (std::size_t i = 0; i < N; ++i) {
            T tmp = static_cast<T&&>(data_[i]);  // аналог std::move
            data_[i] = static_cast<T&&>(other.data_[i]);
            other.data_[i] = static_cast<T&&>(tmp);
        }
    }

    // Поддержка range-based for: begin/end (неконстантные)
    T* begin() { return data_; }

    const T* begin() const { return data_; }

    T* end() { return data_ + N; }

    const T* end() const { return data_ + N; }

    // Константные итераторы (для cbegin/cend)
    const T* cbegin() const { return data_; }

    const T* cend() const { return data_ + N; }
};

//    Внешние функции

// Операторы сравнения
template <typename T, std::size_t N>
bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}
// Не равно
template <typename T, std::size_t N>
bool operator!=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(lhs == rhs);
}
// Равно
template <typename T, std::size_t N>
bool operator<(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
        if (lhs[i] < rhs[i]) return true;
        if (rhs[i] < lhs[i]) return false;
    }
    return false;  // равны
}

// Меньше
template <typename T, std::size_t N>
bool operator<=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(rhs < lhs);
}
// Больше
template <typename T, std::size_t N>
bool operator>(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return rhs < lhs;
}
// Больше или равно
template <typename T, std::size_t N>
bool operator>=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(lhs < rhs);
}

// Шаблон для внешней функции swap, вызывающая метод Swap
template <typename T, std::size_t N>
void swap(Array<T, N>& a, Array<T, N>& b) {
    a.Swap(b);
}

// Функция get для доступа по индексу I (шаблонный параметр)
// Неконстантная версия для lvalue
template <std::size_t I, typename T, std::size_t N>
T& get(Array<T, N>& arr) {
    static_assert(I < N, "Index out of bounds");
    return arr[I];
}

// Константная версия для lvalue
template <std::size_t I, typename T, std::size_t N>
const T& get(const Array<T, N>& arr) {
    static_assert(I < N, "Index out of bounds");
    return arr[I];
}

// Версия для временного массива (rvalue)
template <std::size_t I, typename T, std::size_t N>
T&& get(Array<T, N>&& arr) {
    static_assert(I < N, "Index out of bounds");
    return static_cast<T&&>(arr[I]);  // аналог std::move
}