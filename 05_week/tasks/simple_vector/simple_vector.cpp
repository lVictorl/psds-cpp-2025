// simple_vector.cpp
#include <cstring>  // memcpy, memmove
#include <string>   // для std::string, если требуется в других частях проекта

class SimpleVector {
   public:
    // Конструкторы
    SimpleVector() noexcept : data_(nullptr), size_(0), capacity_(0) {}

    explicit SimpleVector(size_t size) : data_(nullptr), size_(size), capacity_(size) {
        if (size_) {
            data_ = new int[capacity_]();  // value-initialization -> нули
        }
    }

    SimpleVector(size_t size, int value) : data_(nullptr), size_(size), capacity_(size) {
        if (size_) {
            data_ = new int[capacity_];
            for (size_t i = 0; i < size_; ++i) data_[i] = value;
        }
    }

    SimpleVector(std::initializer_list<int> init)
        : data_(nullptr), size_(init.size()), capacity_(init.size()) {
        if (size_) {
            data_ = new int[capacity_];
            size_t i = 0;
            for (auto it = init.begin(); it != init.end(); ++it) data_[i++] = *it;
        }
    }

    // Копирование
    SimpleVector(const SimpleVector& other)
        : data_(nullptr), size_(other.size_), capacity_(other.size_) {
        if (size_) {
            data_ = new int[capacity_];
            std::memcpy(data_, other.data_, size_ * sizeof(int));
        }
    }

    // Перемещение
    SimpleVector(SimpleVector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = other.capacity_ = 0;
    }

    ~SimpleVector() { delete[] data_; }

    // Операторы присваивания
    SimpleVector& operator=(const SimpleVector& other) {
        if (this != &other) {
            SimpleVector temp(other);
            Swap(temp);
        }
        return *this;
    }

    SimpleVector& operator=(SimpleVector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
        return *this;
    }

    // Доступ
    int& operator[](size_t i) { return data_[i]; }
    const int& operator[](size_t i) const { return data_[i]; }

    // Размер и емкость
    size_t Size() const noexcept { return size_; }
    size_t Capacity() const noexcept { return capacity_; }
    bool Empty() const noexcept { return size_ == 0; }
    const int* Data() const noexcept { return data_; }

    // Итераторы для range-based for
    int* begin() noexcept { return data_; }
    int* end() noexcept { return data_ + size_; }
    const int* begin() const noexcept { return data_; }
    const int* end() const noexcept { return data_ + size_; }

    // Операции
    void Swap(SimpleVector& other) noexcept {
        int* tmp_data = data_;
        data_ = other.data_;
        other.data_ = tmp_data;
        size_t tmp_size = size_;
        size_ = other.size_;
        other.size_ = tmp_size;
        size_t tmp_cap = capacity_;
        capacity_ = other.capacity_;
        other.capacity_ = tmp_cap;
    }

    void PushBack(int value) {
        if (size_ == capacity_) {
            size_t new_cap = capacity_ ? capacity_ * 2 : 1;
            Reserve(new_cap);
        }
        data_[size_++] = value;
    }

    void PopBack() noexcept {
        if (size_) --size_;
    }

    int* Insert(const int* pos, int value) {
        if (pos < data_ || pos > data_ + size_) return end();

        size_t offset = pos - data_;
        if (size_ == capacity_) Reserve(capacity_ ? capacity_ * 2 : 1);

        int* insert_pos = data_ + offset;
        std::memmove(insert_pos + 1, insert_pos, (size_ - offset) * sizeof(int));
        *insert_pos = value;
        ++size_;
        return insert_pos;
    }

    int* Erase(const int* pos) {
        if (pos < data_ || pos >= data_ + size_) return end();

        int* erase_pos = data_ + (pos - data_);
        std::memmove(erase_pos, erase_pos + 1, (size_ - (pos - data_) - 1) * sizeof(int));
        --size_;
        return erase_pos;
    }

    void Clear() noexcept { size_ = 0; }

    void Resize(size_t new_size, int value = 0) {
        if (new_size < size_) {
            size_ = new_size;
        } else if (new_size > size_) {
            if (new_size > capacity_) Reserve(new_size);
            for (size_t i = size_; i < new_size; ++i) data_[i] = value;
            size_ = new_size;
        }
    }

    void Reserve(size_t new_cap) {
        if (new_cap > capacity_) {
            int* new_data = new int[new_cap];
            if (size_) std::memcpy(new_data, data_, size_ * sizeof(int));
            delete[] data_;
            data_ = new_data;
            capacity_ = new_cap;
        }
    }

   private:
    int* data_;
    size_t size_;
    size_t capacity_;
};

// Внешние функции
bool operator==(const SimpleVector& lhs, const SimpleVector& rhs) {
    if (lhs.Size() != rhs.Size()) return false;
    for (size_t i = 0; i < lhs.Size(); ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

bool operator!=(const SimpleVector& lhs, const SimpleVector& rhs) { return !(lhs == rhs); }

void swap(SimpleVector& lhs, SimpleVector& rhs) noexcept { lhs.Swap(rhs); }