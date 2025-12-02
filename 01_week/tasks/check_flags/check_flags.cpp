#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <vector>

enum class CheckFlags : uint8_t
{
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};

void PrintCheckFlags(CheckFlags flags)
{
    // throw std::runtime_error{"Not implemented"};
    uint8_t value = static_cast<uint8_t>(flags);

    // Проверка на выход за диапазон
    if (value > static_cast<uint8_t>(CheckFlags::ALL))
    {
        return;
    }

    std::vector<std::string> active_flags;

    // Проверяем каждый флаг в правильном порядке
    if (value & static_cast<uint8_t>(CheckFlags::TIME))
    {
        active_flags.push_back("TIME");
    }
    if (value & static_cast<uint8_t>(CheckFlags::DATE))
    {
        active_flags.push_back("DATE");
    }
    if (value & static_cast<uint8_t>(CheckFlags::USER))
    {
        active_flags.push_back("USER");
    }
    if (value & static_cast<uint8_t>(CheckFlags::CERT))
    {
        active_flags.push_back("CERT");
    }
    if (value & static_cast<uint8_t>(CheckFlags::KEYS))
    {
        active_flags.push_back("KEYS");
    }
    if (value & static_cast<uint8_t>(CheckFlags::DEST))
    {
        active_flags.push_back("DEST");
    }

    // Формируем вывод
    std::cout << "[";
    for (size_t i = 0; i < active_flags.size(); ++i)
    {
        if (i > 0)
        {
            std::cout << ",";
        }
        std::cout << active_flags[i];
    }
    std::cout << "]";
}
