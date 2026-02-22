#include <cstddef>  // std::size_t
#include <string>
#include <utility>  // std::move, std::forward, std::swap

// Вспомогательная структура ControlBlock – управляющий блок для подсчёта ссылок
namespace detail {
struct ControlBlock {
    std::size_t strong_cnt;  // количество SharedPtr (владельцев)
    std::size_t weak_cnt;    // количество WeakPtr (наблюдателей)
    std::string* ptr;        // указатель на управляемый объект

    explicit ControlBlock(std::string* p) noexcept : strong_cnt(1), weak_cnt(0), ptr(p) {}

    void inc_strong() noexcept { ++strong_cnt; }
    void dec_strong() noexcept {
        if (--strong_cnt == 0) {
            delete ptr;  // объект больше не нужен
            ptr = nullptr;
            if (weak_cnt == 0) {
                delete this;  // и слабых ссылок нет – удаляем блок
            }
        }
    }

    void inc_weak() noexcept { ++weak_cnt; }
    void dec_weak() noexcept {
        if (--weak_cnt == 0 && strong_cnt == 0) {
            delete this;  // последний слабый указатель уходит
        }
    }
};
}  // namespace detail

//-----------------------------------------------------------------------------
// Класс SharedPtr – разделяемое владение строкой
//-----------------------------------------------------------------------------
class SharedPtr {
   public:
    // ---------------------------- Конструкторы ----------------------------
    SharedPtr() noexcept : ptr_(nullptr), cb_(nullptr) {}

    explicit SharedPtr(std::string* raw_ptr) : ptr_(raw_ptr), cb_(nullptr) {
        if (raw_ptr) {
            cb_ = new detail::ControlBlock(raw_ptr);
        }
    }

    SharedPtr(const SharedPtr& other) noexcept : ptr_(other.ptr_), cb_(other.cb_) {
        if (cb_) cb_->inc_strong();
    }

    SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), cb_(other.cb_) {
        other.ptr_ = nullptr;
        other.cb_ = nullptr;
    }

    ~SharedPtr() {
        if (cb_) cb_->dec_strong();
    }

    // ---------------------------- Присваивание ----------------------------
    SharedPtr& operator=(const SharedPtr& other) noexcept {
        if (this != &other) {
            SharedPtr tmp(other);  // copy-and-swap идиома
            Swap(tmp);
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            SharedPtr tmp(std::move(other));
            Swap(tmp);
        }
        return *this;
    }

    // ---------------------------- Модификаторы ----------------------------
    void Reset(std::string* raw_ptr = nullptr) {
        SharedPtr tmp(raw_ptr);
        Swap(tmp);
    }

    void Swap(SharedPtr& other) noexcept {
        std::swap(ptr_, other.ptr_);
        std::swap(cb_, other.cb_);
    }

    // ---------------------------- Наблюдатели ----------------------------
    std::string* Get() const noexcept { return ptr_; }
    std::size_t UseCount() const noexcept { return cb_ ? cb_->strong_cnt : 0; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    // ---------------------------- Операторы доступа -----------------------
    std::string& operator*() const noexcept { return *ptr_; }
    std::string* operator->() const noexcept { return ptr_; }

   private:
    std::string* ptr_;
    detail::ControlBlock* cb_;

    friend class WeakPtr;  // для доступа к control block
};

//-----------------------------------------------------------------------------
// Класс WeakPtr – наблюдатель за строкой
//-----------------------------------------------------------------------------
class WeakPtr {
   public:
    // ---------------------------- Конструкторы ----------------------------
    WeakPtr() noexcept : cb_(nullptr) {}

    WeakPtr(const SharedPtr& sp) noexcept : cb_(sp.cb_) {
        if (cb_) cb_->inc_weak();
    }

    WeakPtr(const WeakPtr& other) noexcept : cb_(other.cb_) {
        if (cb_) cb_->inc_weak();
    }

    WeakPtr(WeakPtr&& other) noexcept : cb_(other.cb_) { other.cb_ = nullptr; }

    ~WeakPtr() {
        if (cb_) cb_->dec_weak();
    }

    // ---------------------------- Присваивание ----------------------------
    WeakPtr& operator=(const WeakPtr& other) noexcept {
        if (this != &other) {
            WeakPtr tmp(other);
            Swap(tmp);
        }
        return *this;
    }

    WeakPtr& operator=(WeakPtr&& other) noexcept {
        if (this != &other) {
            WeakPtr tmp(std::move(other));
            Swap(tmp);
        }
        return *this;
    }

    WeakPtr& operator=(const SharedPtr& sp) noexcept {
        WeakPtr tmp(sp);
        Swap(tmp);
        return *this;
    }

    // ---------------------------- Модификаторы ----------------------------
    void Reset() noexcept {
        WeakPtr tmp;
        Swap(tmp);
    }

    void Swap(WeakPtr& other) noexcept { std::swap(cb_, other.cb_); }

    // ---------------------------- Наблюдатели ----------------------------
    std::size_t UseCount() const noexcept { return cb_ ? cb_->strong_cnt : 0; }

    bool Expired() const noexcept { return cb_ == nullptr || cb_->strong_cnt == 0; }

    SharedPtr Lock() const noexcept {
        if (Expired()) return SharedPtr();
        // объект жив – создаём SharedPtr с тем же control block
        SharedPtr sp;
        sp.ptr_ = cb_->ptr;
        sp.cb_ = cb_;
        sp.cb_->inc_strong();
        return sp;
    }

   private:
    detail::ControlBlock* cb_;
};

//-----------------------------------------------------------------------------
// Свободные функции Swap (для единообразия с STL)
//-----------------------------------------------------------------------------
inline void Swap(SharedPtr& lhs, SharedPtr& rhs) noexcept { lhs.Swap(rhs); }

inline void Swap(WeakPtr& lhs, WeakPtr& rhs) noexcept { lhs.Swap(rhs); }

//-----------------------------------------------------------------------------
// Фабричная функция MakeShared – создаёт SharedPtr, оптимально перемещая строку
//-----------------------------------------------------------------------------
template <typename T>
SharedPtr MakeShared(T&& str) {
    // Одно выделение памяти под std::string, control block создаётся отдельно.
    // Для production‑кода можно реализовать единый блок (как std::make_shared),
    // но в учебной задаче достаточно ясности и корректности.
    return SharedPtr(new std::string(std::forward<T>(str)));
}