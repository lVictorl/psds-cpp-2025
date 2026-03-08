// Собственная реализация forward (аналог std::forward) закомментирована,
// чтобы избежать конфликта со стандартной версией, подключаемой через тесты.
/*
template <typename T>
T&& forward(typename std::remove_reference<T>::type& arg) noexcept {
    return static_cast<T&&>(arg);
}

template <typename T>
T&& forward(typename std::remove_reference<T>::type&& arg) noexcept {
    return static_cast<T&&>(arg);
}

// Собственная реализация remove_reference (для forward)
template <typename T>
struct remove_reference {
    using type = T;
};
template <typename T>
struct remove_reference<T&> {
    using type = T;
};
template <typename T>
struct remove_reference<T&&> {
    using type = T;
};

// Собственная реализация unique_ptr (только для одиночных объектов, без поддержки массивов)
template <typename T>
class unique_ptr {
   private:
    T* ptr;

   public:
    // Конструктор по умолчанию
    unique_ptr() noexcept : ptr(nullptr) {}

    // Конструктор от сырого указателя
    explicit unique_ptr(T* p) noexcept : ptr(p) {}

    // Запрет копирования
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    // Перемещение
    unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr) { other.ptr = nullptr; }

    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            reset();
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Деструктор
    ~unique_ptr() { reset(); }

    // Освобождение ресурса
    void reset(T* p = nullptr) noexcept {
        if (ptr) {
            delete ptr;
        }
        ptr = p;
    }

    // Отдача указателя
    T* release() noexcept {
        T* tmp = ptr;
        ptr = nullptr;
        return tmp;
    }

    // Доступ к объекту
    T* get() const noexcept { return ptr; }

    T& operator*() const noexcept { return *ptr; }

    T* operator->() const noexcept { return ptr; }

    // Проверка на nullptr
    explicit operator bool() const noexcept { return ptr != nullptr; }
};
*/

// Подключаем стандартные компоненты, необходимые для MakeUnique
#include <memory>   // std::unique_ptr
#include <utility>  // std::forward

// Собственная функция MakeUnique, использующая стандартные std::unique_ptr и std::forward
template <typename T, typename... Args>
std::unique_ptr<T> MakeUnique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}