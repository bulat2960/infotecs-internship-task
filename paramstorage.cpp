#include "paramstorage.h"

void ParamStorage::setParams(int argc, char** argv)
{
    for (int i = 1; i < argc; i += 2)
    {
        string param = string(argv[i]);

        if (param == "-t" || param == "--type") // Установка режима ("диапазон" или "количество чисел"
        {
            isRangeSearch = atoi(argv[i + 1]);
        }
        else if (param == "-n" || param == "--number") // Установка значения
        {
            value = atoi(argv[i + 1]);
        }
        else if (param == "-f" || param == "--filename") // Установка имени файла
        {
            filename = string(argv[i + 1]);
        }
        else if (param== "-o" || param == "--option") // Установка режима вывода (столбец / строка)
        {
            isRowOutput = atoi(argv[i + 1]);
        }
        else if (param == "-s" || param == "--sequence") // Установка типа специальной последовательности
        {
            sequenceType = atoi(argv[i + 1]);
        }
        else if (param == "-l" || param == "--log") // Установка имени логфайла
        {
            logfile = string(argv[i + 1]);
        }
    }
}

string ParamStorage::stringifyParams() const
{
    string s;

    // Параметр типа поиска
    s += string("Search type: ");
    s += string(isRangeSearch ? "range search" : "certain amount of numbers") + "\n";

    // Параметр режима (поиск "диапазон" или "количество чисел")
    s += string(isRangeSearch ? "Upper bound value: " : "Amount of prime numbers: ");
    s += std::to_string(value) + "\n";

    // Тип вывода (стоблец или строка)
    s += string("Output type: ");
    s += string(isRowOutput ? "row" : "column") + "\n";

    // Тип выводимой последовательности (общий вид или специальный, название специального вида)
    string type;
    if (sequenceType == 0)
    {
        type = "all simple numbers";
    }
    if (sequenceType == 1)
    {
        type = "Sophie Germain prime numbers";
    }
    if (sequenceType == 2)
    {
        type = "Mersenn prime numbers";
    }
    s += string("Sequence type: ") + type + "\n";

    // Имя файла с запрашиваемой последовательностью
    s += string("File with sequence: ");
    s += string(filename.empty() ? "None (console output)" : filename);

    return s;
}
