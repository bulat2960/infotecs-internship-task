/**
 * @file
 * @brief Заголовочный файл структуры для хранения параметров программы.
 */

#ifndef PARAMSTORAGE_H
#define PARAMSTORAGE_H

#include <string>

using std::string;

/**
 * @brief Структура, хранящая настройки программы, вводимые с командной строки.
 */
struct ParamStorage
{
    bool isRangeSearch = true; ///< Тип поиска чисел. true - режим "диапазон", false - режим "количество чисел"
    int value = 100; ///< Значение для заданного режима (по умолчанию 100)
    string filename; ///< Файл для вывода. По умолчанию не задан (если не задан - печать в консоль)
    bool isRowOutput = true; ///< Тип вывода. true - режим печати в строчку, false - режим печати в столбец
    int sequenceType = 0; ///< Тип последовательности. 0 - по умолчанию (вывод всех чисел), 1,2... - спец. последовательность
    string logfile; ///< Файл для логирования информации

    /**
     * @brief Функция для установки параметров, вводимых с командной строки
     * @param argc Число параметров, принимаемых с командной строки
     * @param argv Массив самих параметров
     */
    void setParams(int argc, char** argv);

    /**
     * @brief Функция, переводящая параметры в удобный строковый формат
     * @return Строка, содержащая описание всех параметров и их значения
     */
    string stringifyParams() const;
};

#endif // PARAMSTORAGE_H
