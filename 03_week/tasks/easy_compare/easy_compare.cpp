#include <tuple>

struct Date {
    unsigned year;
    unsigned month;
    unsigned day;

    bool operator==(const Date& other) const {
        return std::tie(year, month, day) == std::tie(other.year, other.month, other.day);
    }

    bool operator<(const Date& other) const {
        return std::tie(year, month, day) < std::tie(other.year, other.month, other.day);
    }
};

bool operator!=(const Date& lhs, const Date& rhs) { return !(lhs == rhs); }
bool operator<=(const Date& lhs, const Date& rhs) { return !(rhs < lhs); }
bool operator>(const Date& lhs, const Date& rhs) { return rhs < lhs; }
bool operator>=(const Date& lhs, const Date& rhs) { return !(lhs < rhs); }

struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;

    bool operator==(const StudentInfo& other) const {
        return mark == other.mark && score == other.score;
    }

    bool operator<(const StudentInfo& other) const {
        // Вспомогательная лямбда для преобразования оценки в числовой приоритет
        auto mark_priority = [](char m) {
            switch (m) {
                case 'A':
                    return 5;
                case 'B':
                    return 4;
                case 'C':
                    return 3;
                case 'D':
                    return 2;
                case 'Z':
                    return 1;
                default:
                    return 0;
            }
        };

        // Сравниваем по правилам из условия
        if (mark_priority(mark) != mark_priority(other.mark)) {
            return mark_priority(mark) > mark_priority(other.mark);  // Обратный порядок
        }
        if (score != other.score) {
            return score > other.score;  // Обратный порядок
        }
        if (course != other.course) {
            return course > other.course;  // Обратный порядок
        }
        return birth_date > other.birth_date;  // Обратный порядок (моложе = лучше)
    }
};

// Остальные операторы для StudentInfo определяем через == и <
bool operator!=(const StudentInfo& lhs, const StudentInfo& rhs) { return !(lhs == rhs); }
bool operator<=(const StudentInfo& lhs, const StudentInfo& rhs) { return !(rhs < lhs); }
bool operator>(const StudentInfo& lhs, const StudentInfo& rhs) { return rhs < lhs; }
bool operator>=(const StudentInfo& lhs, const StudentInfo& rhs) { return !(lhs < rhs); }
