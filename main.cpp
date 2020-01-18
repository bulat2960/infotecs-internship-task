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
            else if (param== "-o" || param == "--option")
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
        cout << "Type: " << (isRangeSearch ? "range search" : "certain amount of numbers") << endl;
        cout << "Value: " << value << endl;
        cout << "Filename: " << filename << endl;
        cout << "Output type: " << (isRowOutput ? "row" : "column") << endl;

        string s;
        if (sequenceType == 0)
        {
            s = "all simple numbers";
        }
        if (sequenceType == 1)
        {
            s = "Sophie Germain prime numbers";
        }
        if (sequenceType == 2)
        {
            s = "Mersenn prime numbers";
        }
        cout << "Sequence type: " << s << endl;
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

    auto checkSophieGermainPrime = [primes](int n) // Простое число Софи Жермен (такое, что 2*p + 1 - простое)
    {
        return primes.isPrime(2 * n + 1);
    };

    auto checkMersennPrime = [](int n) // Простое число Мерсенна (число вида 2^n - 1)
    {
        n += 1;

        int start = 1;
        while (start <= n)
        {
            if (start == n)
            {
                return true;
            }
            start *= 2;
        }
        return false;
    };

    for (auto it = primes.begin(); it != primes.end(); it++)
    {
        int value = *it;

        if (sequenceType == 1)
        {
            if (!checkSophieGermainPrime(value))
            {
                continue;
            }
        }
        if (sequenceType == 2)
        {
            if (!checkMersennPrime(value))
            {
                continue;
            }
        }

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
