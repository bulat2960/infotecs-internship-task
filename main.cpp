#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <functional>
#include <vector>

#include "primes.h"
#include "paramstorage.h"

using namespace std;

bool checkSpecialPrimeType(const Primes& primes, int sequenceType, int value);
void writeLog(const ParamStorage& storage, int count, int memoryUsage);
void print(const Primes& primes, const ParamStorage& storage);


int main(int argc, char** argv)
{
    ParamStorage storage;
    storage.setParams(argc, argv);
    cout << storage.stringifyParams() << endl;

    Primes p(storage.isRangeSearch, storage.value);

    auto start = std::chrono::steady_clock::now();
    p.calculatePrimes();
    auto finish = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    int memoryUsage = sizeof(Node) * p.size();

    writeLog(storage, elapsed.count(), memoryUsage);
    print(p, storage);

    return 0;
}



bool checkSpecialPrimeType(const Primes& primes, int sequenceType, int value)
{
    if (sequenceType == 0) // Если не выбрана специальная последовательность - разрешать выводить всё
    {
        return true;
    }

    auto checkSophieGermainPrime = [primes](int n) -> bool // Простое число Софи Жермен (такое, что 2*p + 1 - простое)
    {
        return primes.isPrime(2 * n + 1);
    };

    auto checkMersennPrime = [](int n) -> bool // Простое число Мерсенна (число вида 2^n - 1)
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

    vector<function<bool(int)>> checks = {checkSophieGermainPrime, checkMersennPrime};

    return checks[sequenceType - 1](value);
}

void writeLog(const ParamStorage& storage, int count, int memoryUsage)
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
    fout << "Memory usage is " << (memoryUsage * 1.0 / 1000000) << " MB." << endl << endl;
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

    for (auto it = primes.begin(); it != primes.end(); it++)
    {
        int value = *it;

        bool needOutput = checkSpecialPrimeType(primes, storage.sequenceType, value);

        if (!needOutput)
        {
            continue;
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

    if (isFileOutput)
    {
        fout << endl;
    }
    else
    {
        cout << endl;
    }
}


