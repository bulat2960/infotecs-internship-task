#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

#include "primes.h"

using namespace std;

struct ParamStorage
{
    bool isRangeSearch = true; // true - режим "диапазон", false - режим "количество чисел"
    int value = 100; // значение для заданного режима
    string filename; // Файл для вывода, по умолчанию не задан (если не задан - печать в консоль)
    bool isRowOutput = false; // true - режим печати в строчку, false - режим печати в столбец
    int sequenceType = 0; // 0 - по умолчанию (вывод всех простых чисел), >0 - спец. последовательность
    string logfile; // Файл для логирования информации

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
            else if (param == "-l" || param == "--log")
            {
                logfile = string(argv[i + 1]);
            }
        }
    }

    string stringifyParams()
    {
        string s;
        s += string("Search type: ") + (isRangeSearch ? "range search" : "certain amount of numbers") + "\n";
        s += (isRangeSearch ? string("Upper bound value: ") : string("Amount of prime numbers: ")) + std::to_string(value) + "\n";
        s += string("File with sequence: ") + filename + "\n";
        s += string("Output type: ") + (isRowOutput ? "row" : "column") + "\n";

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
        s += string("Sequence type: ") + type;

        return s;
    }

    void printParams()
    {
        cout << stringifyParams() << endl;
    }
};

void writeLog(ParamStorage storage, int count, int memoryUsage)
{
    if (storage.logfile.empty())
    {
        cout << "There is no log file name in command line params. Log will not be written." << endl;
        return;
    }

    ofstream fout(storage.logfile, ios::app);

    if (!fout.is_open())
    {
        cout << "Can't open log file! It will not be written." << endl;
        return;
    }

    fout << "----------START RECORDING----------" << endl;
    fout << "Record takes " << (count * 1.0 / 1000) << " seconds." << endl;
    fout << "Memory usage is " << (memoryUsage * 1.0 / 1000000) << " MB." << endl;
    fout << storage.stringifyParams() << endl;
    fout << "----------FINISH RECORDING---------" << endl << endl;
}

void print(const Primes& primes, const ParamStorage& storage)
{
    ofstream fout;

    bool isFileOutput = false;

    if (!storage.filename.empty())
    {
        fout.open(storage.filename);

        if (!fout.is_open())
        {
            cout << "Can't open file to write sequence! Result will be written to console." << endl;
            isFileOutput = false;
        }
        else
        {
            isFileOutput = true;
        }
    }

    string separator = (storage.isRowOutput) ? " " : "\n";

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

        if (storage.sequenceType == 1)
        {
            if (!checkSophieGermainPrime(value))
            {
                continue;
            }
        }
        if (storage.sequenceType == 2)
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
    print(p, storage);

    auto start = std::chrono::steady_clock::now();
    p.calculatePrimes();
    auto finish = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    writeLog(storage, elapsed.count(), p.sizeofNode() * p.size());
    print(p, storage);

    return 0;
}
