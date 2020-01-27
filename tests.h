#ifndef TESTS_H
#define TESTS_H

#include <gtest/gtest.h>

#include "primes.h"
#include "functions.h"
#include "paramstorage.h"

TEST(ConstructorCheckCases, CopyConstructorCheck)
{
    // Создаем объект и вычисляем простые числа
    Primes firstPrimes;
    firstPrimes.calculatePrimes();

    // Вызываем конструктор копирования объекта
    Primes secondPrimes = firstPrimes;

    // Проверяем равенство длин списков
    ASSERT_EQ(firstPrimes.size(), secondPrimes.size());

    // Берем два итератора, указывающих на начало списка
    Primes::Iterator firstPrimesIter = firstPrimes.begin();
    Primes::Iterator secondPrimesIter = secondPrimes.begin();

    // Поэлементно проверяем совпадение контейнеров
    for (int i = 0; i < firstPrimes.size(); i++)
    {
        ASSERT_EQ(*firstPrimesIter, *secondPrimesIter);
        firstPrimesIter++;
        secondPrimesIter++;
    }
}

TEST(ConstructorCheckCases, MoveConstructorCheck)
{
    // Создаем объект и вычисляем простые числа
    Primes firstPrimes;
    firstPrimes.calculatePrimes();

    // Сохраняем его размер
    int firstPrimesSize = firstPrimes.size();

    // Сохраняем значения контейнера
    int array[firstPrimesSize];
    Primes::Iterator firstPrimesIter = firstPrimes.begin();
    for (int i = 0; i < firstPrimesSize; i++)
    {
        array[i] = *firstPrimesIter;
        firstPrimesIter++;
    }

    // Вызываем конструктор перемещения объекта
    Primes secondPrimes = std::move(firstPrimes);

    // Проверяем, что предыдущий контейнер пуст, а новый - той же длины, что предыдущий
    ASSERT_EQ(firstPrimes.size(), 0);
    ASSERT_EQ(secondPrimes.size(), firstPrimesSize);

    // Проверяем, что все данные перенеслись корректно
    Primes::Iterator secondPrimesIter = secondPrimes.begin();
    for (int i = 0; i < secondPrimes.size(); i++)
    {
        ASSERT_EQ(array[i], *secondPrimesIter);
        secondPrimesIter++;
    }
}

TEST(OperatorCheckCases, CopyOperatorCheck)
{
    // Создаем два разных контейнера простых чисел
    Primes firstPrimes(true, 100);
    firstPrimes.calculatePrimes();

    Primes secondPrimes(false, 200);
    secondPrimes.calculatePrimes();

    // Проверяем, что их длины не равны
    ASSERT_NE(firstPrimes.size(), secondPrimes.size());

    // Вызываем оператор копирования
    secondPrimes = firstPrimes;

    // Проверяем, что сейчас их длины равны
    ASSERT_EQ(firstPrimes.size(), secondPrimes.size());

    // Берем два итератора
    Primes::Iterator firstPrimesIter = firstPrimes.begin();
    Primes::Iterator secondPrimesIter = secondPrimes.begin();

    // Поэлементно проверяем совпадение контейнеров
    for (int i = 0; i < firstPrimes.size(); i++)
    {
        ASSERT_EQ(*firstPrimesIter, *secondPrimesIter);
        firstPrimesIter++;
        secondPrimesIter++;
    }
}

TEST(OperatorCheckCases, MoveOperatorCheck)
{
    // Создаем два разных контейнера простых чисел
    Primes firstPrimes(true, 100);
    firstPrimes.calculatePrimes();

    Primes secondPrimes(false, 200);
    secondPrimes.calculatePrimes();

    // Сохраняем длину первого
    int firstPrimesSize = firstPrimes.size();

    // Сохраняем значения первого
    int array[firstPrimesSize];
    Primes::Iterator firstPrimesIter = firstPrimes.begin();
    for (int i = 0; i < firstPrimesSize; i++)
    {
        array[i] = *firstPrimesIter;
        firstPrimesIter++;
    }

    // Проверяем, что длины не равны
    ASSERT_NE(firstPrimes.size(), secondPrimes.size());

    // Вызываем оператор перемещения
    secondPrimes = std::move(firstPrimes);

    // Проверяем, что первый обнулился, а второй - той же длины, что и предыдущий первый
    ASSERT_EQ(firstPrimes.size(), 0);
    ASSERT_EQ(secondPrimes.size(), firstPrimesSize);

    // Поэлементно проверяем значения перемещенного контейнера
    Primes::Iterator secondPrimesIter = secondPrimes.begin();
    for (int i = 0; i < secondPrimes.size(); i++)
    {
        ASSERT_EQ(array[i], *secondPrimesIter);
        secondPrimesIter++;
    }
}

TEST(IteratorCheckCases, IteratorEqualCheck)
{
    // Создаем контейнер и вычисляем простые числа
    Primes primes;
    primes.calculatePrimes();

    // Берем два итератора
    Primes::Iterator begin1 = primes.begin();
    Primes::Iterator begin2 = primes.begin();

    // Проверяем на равенство данных
    ASSERT_EQ(begin1, begin2);

    // Изменяем второй итератор, проверяем неравенство
    begin2++;
    ASSERT_NE(begin1, begin2);

    // Переводим первый итератор ко второму, проверяем равенство
    begin1++;
    ASSERT_EQ(begin1, begin2);
}

TEST(IteratorCheckCases, BeginCanReachEndCheck)
{
    // Создаем контейнер и вычисляем простые числа
    Primes primes;
    primes.calculatePrimes();

    // Задаем два итератора
    Primes::Iterator begin = primes.begin();
    Primes::Iterator end = primes.end();

    int size = primes.size();

    // size - 1 раз инкрементируем begin (единица вычтена намеренно)
    for (int i = 0; i < size - 1; i++)
    {
        begin++;
    }

    // Проверяем несовпадение
    ASSERT_NE(begin, end);

    // Добавляем отсутствующий инкремент, проверяем совпадение
    begin++;
    ASSERT_EQ(begin, end);
}

TEST(PrimesCalculationCases, CertainAmountCalculatingCheck)
{
    // Создаем контейнер в режиме поиска "определенное количество чисел"
    Primes primes(false, 100);
    primes.calculatePrimes();

    // Проверяем, что количество вычисленных чисел именно то, которое требовалось
    ASSERT_EQ(primes.size(), 100);
}

TEST(PrimesCalculationCases, UpperBoundCheck)
{
    // Создаем контейнер в режиме поиска "верхняя граница" с границей равной 100
    Primes primes(true, 100);
    primes.calculatePrimes();

    int value = 0;

    // Задаем стартовый итератор
    Primes::Iterator begin = primes.begin();

    // Находим последнее простое число в контейнере
    while (begin != primes.end())
    {
        value = *begin;
        begin++;
    }

    // Убеждаемся, что оно не превосходит верхнюю границу
    ASSERT_LT(value, 100);

    // Вычисляем следующее за последним простое число, убеждаемся что оно больше верхней границы
    int nextPrime = findNextPrimeGreaterThan(value);
    ASSERT_GT(nextPrime, 100);
}

TEST(OtherTestCases, ValueChangeCheck)
{
    // Создаем контейнер и вычисляем числа
    Primes primes;
    primes.calculatePrimes();

    // Создаем первый итератор begin, переводим его на следующее число, и изменяем это число
    Primes::Iterator begin1 = primes.begin();
    begin1++;
    *begin1 = 42;

    // Создаем второй итератор и переводим на следующее число
    Primes::Iterator begin2 = primes.begin();
    begin2++;

    // Проверяем, что значение по второму итератору так же изменилось (ибо значение меняется по ссылке)
    ASSERT_EQ(*begin2, *begin1);
}

TEST(NonMemberTestCases, IsPrimeCheck)
{
    ASSERT_EQ(isPrime(3), true);
    ASSERT_EQ(isPrime(42), false);
    ASSERT_NE(isPrime(25), true);
    ASSERT_NE(isPrime(79), false);
}

TEST(NonMemberTestCases, NextPrimeCheck)
{
    ASSERT_EQ(findNextPrimeGreaterThan(11), 13);
    ASSERT_NE(findNextPrimeGreaterThan(11), 12);
    ASSERT_EQ(findNextPrimeGreaterThan(50), 53);
    ASSERT_NE(findNextPrimeGreaterThan(53), 53);
}

TEST(NonMemberTestCases, SpecialSequencesCheck)
{
    // Первые несколько простых чисел Софи Жермен: 2, 3, 5, 11, 23, 29, 41, 53, 83, 89...
    ASSERT_EQ(checkSpecialPrimeType(1, 53), true);
    ASSERT_EQ(checkSpecialPrimeType(1, 83), true);
    ASSERT_EQ(checkSpecialPrimeType(1, 7), false);
    ASSERT_NE(checkSpecialPrimeType(1, 5), false);
    ASSERT_NE(checkSpecialPrimeType(1, 30), true);

    // Первые несколько простых чисел Мерсенна: 3, 7, 31, 127, 8191...
    ASSERT_EQ(checkSpecialPrimeType(2, 3), true);
    ASSERT_EQ(checkSpecialPrimeType(2, 7), true);
    ASSERT_EQ(checkSpecialPrimeType(2, 31), true);
    ASSERT_EQ(checkSpecialPrimeType(2, 63), false);
    ASSERT_NE(checkSpecialPrimeType(2, 127), false);
    ASSERT_NE(checkSpecialPrimeType(2, 512), true);
    ASSERT_NE(checkSpecialPrimeType(2, 255), true);

}

#endif // TESTS_H
