#include <cstdint>
#include <iostream>
#include <vector>

enum class CheckFlags : uint8_t {
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};
// Маска для валидных флагов (биты 0-5)
constexpr uint8_t VALID_MASK = 0x3F;

// Функция очистки от невалидных флагов
constexpr CheckFlags sanitize(CheckFlags flags) {
    return static_cast<CheckFlags>(static_cast<uint8_t>(flags) & VALID_MASK);
}

// Побитовое ИЛИ
CheckFlags operator|(CheckFlags lhs, CheckFlags rhs) {
    return static_cast<CheckFlags>(static_cast<uint8_t>(sanitize(lhs)) |
                                   static_cast<uint8_t>(sanitize(rhs)));
}

// Побитовое И
bool operator&(CheckFlags lhs, CheckFlags rhs) {
    auto lhs_clean = sanitize(lhs);
    auto rhs_clean = sanitize(rhs);

    // Если один из операндов NONE, возвращаем false
    if (lhs_clean == CheckFlags::NONE || rhs_clean == CheckFlags::NONE) {
        return false;
    }

    // Проверяем, содержит ли один операнд все активные флаги другого
    uint8_t l = static_cast<uint8_t>(lhs_clean);
    uint8_t r = static_cast<uint8_t>(rhs_clean);
    uint8_t intersection = l & r;

    return intersection == l || intersection == r;
}

// Оператор ^ (исключающее ИЛИ)
CheckFlags operator^(CheckFlags lhs, CheckFlags rhs) {
    return static_cast<CheckFlags>(static_cast<uint8_t>(sanitize(lhs)) ^
                                   static_cast<uint8_t>(sanitize(rhs)));
}

// Побитовое НЕ
CheckFlags operator~(CheckFlags flags) {
    return static_cast<CheckFlags>((~static_cast<uint8_t>(sanitize(flags))) & VALID_MASK);
}

// Оператор сдвига
std::ostream& operator<<(std::ostream& os, CheckFlags flags) {
    auto clean_flags = sanitize(flags);

    if (clean_flags == CheckFlags::NONE) {
        os << "NONE";
        return os;
    }

    // Проверяем флаги в порядке их объявления
    bool first = true;

    // Массив всех валидных флагов в порядке возрастания
    const CheckFlags all_flags[] = {CheckFlags::TIME, CheckFlags::DATE, CheckFlags::USER,
                                    CheckFlags::CERT, CheckFlags::KEYS, CheckFlags::DEST};

    // Соответствующие имена
    const char* flag_names[] = {"TIME", "DATE", "USER", "CERT", "KEYS", "DEST"};

    for (size_t i = 0; i < 6; ++i) {
        if ((static_cast<uint8_t>(clean_flags) & static_cast<uint8_t>(all_flags[i])) != 0) {
            if (!first) {
                os << ", ";
            }
            os << flag_names[i];
            first = false;
        }
    }

    return os;
}
