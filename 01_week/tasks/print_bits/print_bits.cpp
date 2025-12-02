#include <cstddef>
#include <stdexcept>
#include <iostream>

void PrintBits(long long value, size_t bytes)
{
    // throw std::runtime_error{"Not implemented"};
    //  Проверяем допустимость размера
    if (bytes == 0 || bytes > 8)
    {
        return;
    }

    // Вычисляем общее количество битов
    size_t total_bits = bytes * 8;

    // Создаем маску для извлечения нужного количества байтов
    unsigned long long mask = 0;
    if (bytes == 8)
    {
        mask = ~0ULL; // Все биты установлены в 1
    }
    else
    {
        mask = (1ULL << total_bits) - 1;
    }

    // Приводим значение к беззнаковому типу и применяем маску
    unsigned long long unsigned_value = static_cast<unsigned long long>(value);
    unsigned_value &= mask;

    // Выводим префикс
    std::cout << "0b";

    // Выводим биты группами по 4
    for (int i = static_cast<int>(total_bits) - 1; i >= 0; i--)
    {
        // Получаем текущий бит
        unsigned long long bit = (unsigned_value >> i) & 1;
        std::cout << (bit ? '1' : '0');

        // Добавляем апостроф после каждой группы из 4 битов (кроме последней)
        if (i > 0 && i % 4 == 0)
        {
            std::cout << "'";
        }
    }

    // Завершаем вывод переводом строки
    std::cout << "\n";
}
