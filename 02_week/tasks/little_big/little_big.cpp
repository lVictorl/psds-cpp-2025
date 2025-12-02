#include <cstring>
#include <stdexcept>
#include <iostream>

void PrintMemory(int value, bool reverse)
{
    // throw std::runtime_error{"Not implemented"};
    unsigned char bytes[sizeof(int)];
    std::memcpy(bytes, &value, sizeof(int));

    std::cout << "0x";
    if (reverse)
    {
        // Big-endian
        for (int i = sizeof(int) - 1; i >= 0; --i)
        {
            // Ручной вывод hex
            unsigned char high = (bytes[i] >> 4) & 0x0F;
            unsigned char low = bytes[i] & 0x0F;
            std::cout.put(high < 10 ? '0' + high : 'A' + (high - 10));
            std::cout.put(low < 10 ? '0' + low : 'A' + (low - 10));
        }
    }
    else
    {
        // Little-endian
        for (size_t i = 0; i < sizeof(int); ++i)
        {
            unsigned char high = (bytes[i] >> 4) & 0x0F;
            unsigned char low = bytes[i] & 0x0F;
            std::cout.put(high < 10 ? '0' + high : 'A' + (high - 10));
            std::cout.put(low < 10 ? '0' + low : 'A' + (low - 10));
        }
    }
    std::cout.put('\n');
}

void PrintMemory(double value, bool reverse)
{
    // throw std::runtime_error{"Not implemented"};
    unsigned char bytes[sizeof(double)];
    std::memcpy(bytes, &value, sizeof(double));

    std::cout << "0x";
    if (reverse)
    {
        // Big-endian
        for (int i = sizeof(double) - 1; i >= 0; --i)
        {
            unsigned char high = (bytes[i] >> 4) & 0x0F;
            unsigned char low = bytes[i] & 0x0F;
            std::cout.put(high < 10 ? '0' + high : 'A' + (high - 10));
            std::cout.put(low < 10 ? '0' + low : 'A' + (low - 10));
        }
    }
    else
    {
        // Little-endian
        for (size_t i = 0; i < sizeof(double); ++i)
        {
            unsigned char high = (bytes[i] >> 4) & 0x0F;
            unsigned char low = bytes[i] & 0x0F;
            std::cout.put(high < 10 ? '0' + high : 'A' + (high - 10));
            std::cout.put(low < 10 ? '0' + low : 'A' + (low - 10));
        }
    }
    std::cout.put('\n');
}

// Перегрузки с одним параметром
void PrintMemory(int value)
{
    PrintMemory(value, false);
}

void PrintMemory(double value)
{
    PrintMemory(value, false);
}