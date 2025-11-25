#include <cstddef>
#include <stdexcept>
#include <cctype>

size_t CharChanger(char array[], size_t size, char delimiter = ' ')
{
    // throw std::runtime_error{"Not implemented"};
    size_t j = 0;
    size_t i = 0;

    while (i < size && array[i] != '\0')
    {
        if (array[i] == ' ')
        {
            // Пропускаем все пробелы
            size_t spaces = 0;
            while (i < size && array[i] == ' ')
            {
                i++;
                spaces++;
            }

            // Записываем разделитель если нужно
            if (spaces > 0)
            {
                if (j == 0 || array[j - 1] != delimiter)
                {
                    if (j < size - 1)
                    {
                        array[j] = delimiter;
                        j++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            // Определяем длину последовательности одинаковых символов
            char original = array[i];
            size_t count = 0;
            while (i + count < size && array[i + count] == original && array[i + count] != '\0')
            {
                count++;
            }

            // Преобразуем символ
            char current = original;
            if (std::isdigit(static_cast<unsigned char>(original)))
            {
                current = '*';
            }
            else if (std::islower(static_cast<unsigned char>(original)))
            {
                current = std::toupper(static_cast<unsigned char>(original));
            }
            else if (!std::isupper(static_cast<unsigned char>(original)))
            {
                current = '_';
            }

            // Записываем результат с учетом правила повторений
            if (count == 1)
            {
                if (j < size - 1)
                {
                    array[j] = current;
                    j++;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (j + 1 < size - 1)
                {
                    array[j] = current;
                    if (count >= 10)
                    {
                        array[j + 1] = '0';
                    }
                    else
                    {
                        array[j + 1] = '0' + count;
                    }
                    j += 2;
                }
                else
                {
                    break;
                }
            }

            i += count;
        }
    }

    // Завершаем строку
    if (j < size)
    {
        array[j] = '\0';
    }
    else if (size > 0)
    {
        array[size - 1] = '\0';
    }

    return j;
}
