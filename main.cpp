/**
 * @file
 * @brief Главный исполняемый файл программы.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <functional>
#include <vector>

#include "primes.h"
#include "paramstorage.h"
#include "functions.h"

using namespace std::chrono;

/**
 * @brief Входная точка в программу.
 * @param argc Количество аргументов командной строки
 * @param argv Список аргументов командной строки
 * @return Статус завершения работы программы
 */
int main(int argc, char** argv)
{
    ParamStorage storage;
    storage.setParams(argc, argv);

    Primes p(storage.isRangeSearch, storage.value);

    auto start = std::chrono::steady_clock::now();
    p.calculatePrimes();
    auto finish = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    int memoryUsage = sizeof(Node) * p.size();

    print(p, storage);
    writeLog(storage, elapsed.count(), memoryUsage);

    return 0;
}

