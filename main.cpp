#include <iostream>
#include <string>
#include <fstream>

#include "primes.h"

using namespace std;

struct ParamStorage
{
    bool isRangeSearch = true; // true - режим "диапазон", false - режим "количество чисел"
    int value = 100; // значение для заданного режима
    string filename; // Файл для вывода, по умолчанию не задан (если не задан - печать в консоль)
    bool isRowOutput = false; // true - режим печати в строчку, false - режим печати в столбец
    int sequenceType = 0; // 0 - по умолчанию (вывод всех простых чисел), >0 - спец. последовательность

    void setParams(int argc, char** argv)
    {
        for (int i = 1; i < argc; i += 2)
        {
            string param = string(argv[i]);

            if (param == "-t" || param == "--type")
            {
                isRangeSearch = atoi(argv[i + 1]);
            }
            else if (param == "-n" || param == "--number")
            {
                value = atoi(argv[i + 1]);
            }
            else if (param == "-f" || param == "--filename")
            {
                filename = string(argv[i + 1]);
            }
            else if (param== "-o" || param == "-option")
            {
                isRowOutput = atoi(argv[i + 1]);
            }
            else if (param == "-s" || param == "--sequence")
            {
                sequenceType = atoi(argv[i + 1]);
            }
        }
    }

    void printParams()
    {
        cout << "Type - range search? " << isRangeSearch << endl;
        cout << "Value = " << value << endl;
        cout << "Filename = " << filename << endl;
        cout << "Is row output? " << isRowOutput << endl;
        cout << "Sequence type = " << sequenceType << endl;
    }
};

void print(const Primes& primes, string filename, bool isRowOutput, int sequenceType)
{
    ofstream fout;

    bool isFileOutput = false;

    if (!filename.empty())
    {
        fout.open(filename);
        isFileOutput = true;
    }

    string separator = (isRowOutput) ? " " : "\n";

    for (auto it = primes.begin(); it != primes.end(); it++)
    {
        int value = *it;

        if (isFileOutput)
        {
            fout << value << separator;
        }
        else
        {
            cout << value << separator;
        }
    }
}

int main(int argc, char** argv)
{
    ParamStorage storage;
    storage.setParams(argc, argv);
    storage.printParams();

    Primes p(storage.isRangeSearch, storage.value);
    p.calculatePrimes();
    print(p, storage.filename, storage.isRowOutput, storage.sequenceType);

    return 0;
}
