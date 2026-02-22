#include <cstddef>  // std::size_t
#include <memory>   // std::unique_ptr, std::make_unique
#include <string>
#include <utility>  // std::move, std::forward, std::swap

// Класс SimpleList реализует упрощённый двусвязный список строк.
// Управление памятью основано на RAII: каждый узел хранится в std::unique_ptr,
// что гарантирует автоматическое освобождение цепочки при уничтожении списка.
// Для двунаправленной связи используется сырой указатель prev (не владеющий).
// Размер списка хранится в поле size_ для константной сложности Size().
class SimpleList {
   private:
    // Внутренняя структура узла списка.
    struct Node {
        std::string data;            // значение элемента
        Node* prev;                  // указатель на предыдущий узел (не владеющий)
        std::unique_ptr<Node> next;  // указатель на следующий узел (владеющий)

        // Конструкторы для удобного создания узлов из lvalue и rvalue строк.
        explicit Node(const std::string& value) : data(value), prev(nullptr) {}
        explicit Node(std::string&& value) : data(std::move(value)), prev(nullptr) {}
    };

    std::unique_ptr<Node> head_;  // владеет первым узлом (или nullptr)
    Node* tail_;                  // сырой указатель на последний узел (не владеющий)
    std::size_t size_;            // количество элементов (O(1) доступ)

   public:
    // ---------- Конструкторы и деструктор ----------

    // Конструктор по умолчанию: создаёт пустой список.
    SimpleList() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

    // Деструктор автоматически удаляет всю цепочку через std::unique_ptr.
    ~SimpleList() = default;

    // Копирующий конструктор: выполняет глубокое копирование всех узлов.
    SimpleList(const SimpleList& other) : head_(nullptr), tail_(nullptr), size_(0) {
        // Проходим по исходному списку и вставляем копии в конец.
        // Использование PushBack гарантирует корректное связывание узлов.
        Node* cur = other.head_.get();
        while (cur) {
            PushBack(cur->data);  // копируем строку
            cur = cur->next.get();
        }
    }

    // Перемещающий конструктор: забирает владение у other, оставляя other пустым.
    SimpleList(SimpleList&& other) noexcept
        : head_(std::move(other.head_)), tail_(other.tail_), size_(other.size_) {
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    // ---------- Присваивание ----------

    // Копирующее присваивание через идиому copy‑and‑swap (безопасно относительно исключений).
    SimpleList& operator=(const SimpleList& other) {
        if (this != &other) {       // защита от самоприсваивания (необязательна, но ускоряет)
            SimpleList tmp(other);  // может выбросить исключение
            swap(tmp);              // обмен не бросает исключений
        }
        return *this;
    }

    // Перемещающее присваивание: аналогично copy‑and‑swap, но с перемещённым временным объектом.
    SimpleList& operator=(SimpleList&& other) noexcept {
        if (this != &other) {  // при самоприсваивании ничего не делаем (требование теста)
            SimpleList tmp(std::move(other));  // other становится пустым
            swap(tmp);                         // обмен не бросает исключений
        }
        return *this;
    }

    // ---------- Состояние списка ----------

    // Возвращает количество элементов (константная сложность).
    std::size_t Size() const noexcept { return size_; }

    // Проверяет, пуст ли список.
    bool Empty() const noexcept { return size_ == 0; }

    // ---------- Доступ к элементам ----------

    // Возвращает ссылку на значение первого элемента (предполагается, что список не пуст).
    std::string& Front() noexcept { return head_->data; }

    const std::string& Front() const noexcept { return head_->data; }

    // Возвращает ссылку на значение последнего элемента (предполагается, что список не пуст).
    std::string& Back() noexcept { return tail_->data; }

    const std::string& Back() const noexcept { return tail_->data; }

    // ---------- Модификация ----------

    // Вставляет элемент в конец списка.
    // Принимает как lvalue, так и rvalue (универсальная ссылка) для минимизации копирований.
    template <typename S>
    void PushBack(S&& value) {
        // Создаём новый узел в динамической памяти.
        // std::forward<S> передаёт value с сохранением категории (lvalue → копия, rvalue →
        // перемещение).
        auto new_node = std::make_unique<Node>(std::forward<S>(value));
        Node* new_raw = new_node.get();

        if (tail_) {
            // Список не пуст: прицепляем новый узел после tail_.
            tail_->next = std::move(new_node);
            new_raw->prev = tail_;
            tail_ = new_raw;
        } else {
            // Список пуст: новый узел становится и головой, и хвостом.
            head_ = std::move(new_node);
            tail_ = head_.get();
        }
        ++size_;
    }

    // Вставляет элемент в начало списка (аналогично PushBack).
    template <typename S>
    void PushFront(S&& value) {
        auto new_node = std::make_unique<Node>(std::forward<S>(value));
        Node* new_raw = new_node.get();

        if (head_) {
            // Список не пуст: новый узел становится головой.
            head_->prev = new_raw;
            new_raw->next = std::move(head_);
            head_ = std::move(new_node);
        } else {
            head_ = std::move(new_node);
            tail_ = head_.get();
        }
        ++size_;
    }

    // Удаляет последний элемент (если список не пуст).
    void PopBack() noexcept {
        if (!tail_) return;

        if (tail_->prev) {
            // Есть предыдущий узел: отсоединяем tail_.
            Node* new_tail = tail_->prev;
            new_tail->next.reset();  // удаляет старый tail_
            tail_ = new_tail;
        } else {
            // Был единственный элемент.
            head_.reset();
            tail_ = nullptr;
        }
        --size_;
    }

    // Удаляет первый элемент (если список не пуст).
    void PopFront() noexcept {
        if (!head_) return;

        // Перемещаем head_ на следующий узел (старый head_ удаляется автоматически).
        head_ = std::move(head_->next);
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;  // список стал пустым
        }
        --size_;
    }

    // Очищает список (удаляет все элементы).
    void Clear() noexcept {
        head_.reset();  // удаляет всю цепочку
        tail_ = nullptr;
        size_ = 0;
    }

    // ---------- Обмен содержимым ----------

    // Обменивает содержимое двух списков (не бросает исключений).
    void Swap(SimpleList& other) noexcept {
        using std::swap;  // для вызова std::swap (определена в <utility>)
        swap(head_, other.head_);
        swap(tail_, other.tail_);
        swap(size_, other.size_);
    }

    // ---------- Дружественная функция для внешнего swap ----------
    friend void Swap(SimpleList& lhs, SimpleList& rhs) noexcept { lhs.Swap(rhs); }
};

// Внешняя функция swap (требуется тестом ExternalSwap).
// Определена в том же пространстве имён, что и SimpleList (глобальное).
void Swap(SimpleList& lhs, SimpleList& rhs) noexcept { lhs.Swap(rhs); }