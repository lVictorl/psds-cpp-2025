#include <algorithm>  // std::min
#include <cstring>
#include <string>

class StringView {
   public:
    // Статическая константа, обозначающая "до конца строки" (аналог std::string::npos)
    static constexpr size_t npos = size_t(-1);

    //  Конструкторы

    // Конструктор по умолчанию – пустое представление
    constexpr StringView() noexcept : data_(nullptr), size_(0) {}

    // Конструктор от std::string (принимаем по const&, чтобы избежать копирования)
    // pos – начальная позиция, count – количество символов (npos = все до конца)
    StringView(const std::string& str, size_t pos = 0, size_t count = npos) noexcept
        : data_(nullptr), size_(0) {
        if (pos <= str.size()) {
            size_t remaining = str.size() - pos;
            size_ = (count == npos) ? remaining : std::min(count, remaining);
            data_ = str.data() + pos;
        }
        // иначе остаётся пустым (data_ = nullptr, size_ = 0)
    }

    // Конструктор от C-строки (nullptr даёт пустое представление)
    StringView(const char* str) noexcept : data_(nullptr), size_(0) {
        if (str) {
            size_ = std::strlen(str);
            data_ = str;
        }
    }

    // Конструктор от C-строки с явным указанием длины
    // Если передан nullptr, представление всегда пустое (даже если len > 0)
    StringView(const char* str, size_t len) noexcept : data_(nullptr), size_(0) {
        if (str) {
            data_ = str;
            size_ = len;
        }
    }

    // Наблюдатели
    const char* Data() const noexcept { return data_; }
    size_t Size() const noexcept { return size_; }
    size_t Length() const noexcept { return size_; }
    bool Empty() const noexcept { return size_ == 0; }

    // Доступ к символам (без проверки границ, как и в std::string_view)
    const char& operator[](size_t idx) const noexcept { return data_[idx]; }
    const char& Front() const noexcept { return data_[0]; }
    const char& Back() const noexcept { return data_[size_ - 1]; }

    // Удалить n символов с начала
    void RemovePrefix(size_t n) noexcept {
        n = std::min(n, size_);
        data_ += n;
        size_ -= n;
    }

    // Удалить n символов с конца
    void RemoveSuffix(size_t n) noexcept {
        n = std::min(n, size_);
        size_ -= n;
    }

    // Возвращает новое представление, являющееся подстрокой текущего
    // Если pos выходит за границы, возвращается пустое представление
    StringView Substr(size_t pos, size_t count = npos) const noexcept {
        if (pos > size_) return StringView();
        size_t new_size = (count == npos) ? (size_ - pos) : std::min(count, size_ - pos);
        return StringView(data_ + pos, new_size);
    }

    // Поиск символа, начиная с позиции pos
    size_t Find(char c, size_t pos = 0) const noexcept {
        if (pos >= size_) return npos;
        for (size_t i = pos; i < size_; ++i) {
            if (data_[i] == c) return i;
        }
        return npos;
    }

    // Поиск подстроки (другого StringView), начиная с позиции pos
    // Реализация – наивный алгоритм (O(n*m)), достаточный для тестов и большинства применений
    size_t Find(const StringView& sv, size_t pos = 0) const noexcept {
        // Пустая подстрока всегда "находится" в позиции pos, если она допустима
        if (sv.Empty()) {
            return (pos <= size_) ? pos : npos;
        }
        if (pos >= size_ || sv.size_ > size_ - pos) return npos;

        for (size_t i = pos; i <= size_ - sv.size_; ++i) {
            bool match = true;
            for (size_t j = 0; j < sv.size_; ++j) {
                if (data_[i + j] != sv.data_[j]) {
                    match = false;
                    break;
                }
            }
            if (match) return i;
        }
        return npos;
    }

    // Преобразование в std::string
    std::string ToString() const { return std::string(data_, size_); }

   private:
    const char* data_;  // указатель на начало наблюдаемой строки (не владеет памятью)
    size_t size_;       // длина наблюдаемой части
};