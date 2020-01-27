#ifndef PARAMSTORAGE_H
#define PARAMSTORAGE_H

#include <string>

using std::string;

struct ParamStorage
{
    bool isRangeSearch = true; // true - режим "диапазон", false - режим "количество чисел"
    int value = 100; // значение для заданного режима
    string filename; // Файл для вывода, по умолчанию не задан (если не задан - печать в консоль)
    bool isRowOutput = true; // true - режим печати в строчку, false - режим печати в столбец
    int sequenceType = 0; // 0 - по умолчанию (вывод всех простых чисел), >0 - спец. последовательность
    string logfile; // Файл для логирования информации

    void setParams(int argc, char** argv);
    string stringifyParams() const;
};

#endif // PARAMSTORAGE_H
