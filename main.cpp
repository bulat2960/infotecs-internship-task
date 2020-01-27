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

#include "tests.h"

/**
 * @brief Входная точка в программу.
 * @param argc Количество аргументов командной строки
 * @param argv Список аргументов командной строки
 * @return Статус завершения работы программы
 */
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

