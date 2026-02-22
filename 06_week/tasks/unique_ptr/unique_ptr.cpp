#include <cassert>  // для assert в отладочных проверках
#include <string>
#include <utility>  // для std::swap, std::move

/**
 * @brief Класс UniquePtr реализует умный указатель с уникальным владением строкой std::string.
 *
 * Соответствует семантике std::unique_ptr для строк. Запрещает копирование,
 * разрешает перемещение. Все ресурсы освобождаются в деструкторе.
 */
class UniquePtr {
   public:
    /// Конструктор по умолчанию – создаёт нулевой указатель.
    UniquePtr() noexcept : ptr_(nullptr) {}

    /// Конструктор из сырого указателя – принимает владение.
    explicit UniquePtr(std::string* raw_ptr) noexcept : ptr_(raw_ptr) {}

    /// Запрет копирования (класс с уникальным владением не может копироваться).
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    /// Перемещающий конструктор – передаёт владение, источник обнуляется.
    UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) { other.ptr_ = nullptr; }

    /// Перемещающее присваивание – освобождает текущий ресурс и забирает владение у other.
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        // Проверка на самоприсваивание (защита от x = std::move(x))
        if (this != &other) {
            delete ptr_;           // освобождаем старый ресурс
            ptr_ = other.ptr_;     // копируем указатель
            other.ptr_ = nullptr;  // источник больше не владеет
        }
        return *this;
    }

    /// Деструктор – освобождает владеемую строку.
    ~UniquePtr() { delete ptr_; }

    /// Возвращает сырой указатель (не освобождая владение).
    std::string* Get() const noexcept { return ptr_; }

    /// Освобождает владение и возвращает сырой указатель. После вызова указатель становится
    /// нулевым.
    std::string* Release() noexcept {
        std::string* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    /// Заменяет управляемый объект новым (старый удаляется). Если new_ptr нулевой, просто очищает.
    void Reset(std::string* new_ptr = nullptr) noexcept {
        delete ptr_;
        ptr_ = new_ptr;
    }

    /// Обменивается содержимым с другим UniquePtr.
    void Swap(UniquePtr& other) noexcept { std::swap(ptr_, other.ptr_); }

    /// Оператор разыменования – предоставляет доступ к строке.
    /// В отладочной сборке проверяет, что указатель не нулевой.
    std::string& operator*() const {
        assert(ptr_ != nullptr && "Dereferencing null UniquePtr");
        return *ptr_;
    }

    /// Оператор доступа к членам – позволяет вызывать методы строки через ->.
    std::string* operator->() const noexcept { return ptr_; }

    /// Преобразование к bool – проверяет, владеет ли указатель объектом.
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

   private:
    std::string* ptr_;  ///< Сырой указатель на управляемую строку.
};

/// Свободная функция Swap для обмена двух UniquePtr.
inline void Swap(UniquePtr& lhs, UniquePtr& rhs) noexcept { lhs.Swap(rhs); }

/**
 * @brief Создаёт UniquePtr, владеющий новой копией строки (или перемещённой строкой).
 *
 * Перегрузка для lvalue-ссылки – строка копируется.
 */
inline UniquePtr MakeUnique(const std::string& str) { return UniquePtr(new std::string(str)); }

/**
 * @brief Создаёт UniquePtr, владеющий новой строкой, сконструированной перемещением из str.
 *
 * Перегрузка для rvalue-ссылки – строка перемещается, избегая лишнего копирования.
 */
inline UniquePtr MakeUnique(std::string&& str) {
    return UniquePtr(new std::string(std::move(str)));
}

// Примечание: можно было бы написать одну шаблонную функцию с perfect forwarding,
// но для ясности и простоты используем две явные перегрузки.