#include "primes.h"

Primes::Primes(bool findType, int findTypeValue) : findType(findType), findTypeValue(findTypeValue)
{

}

Primes::Iterator Primes::begin() const
{
    return Iterator(head);
}

Primes::Iterator Primes::end() const
{
    return Iterator(nullptr);
}

void Primes::append(int value)
{
    Node* node = new Node(value);

    if (head == nullptr)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
}

bool Primes::isSimple(int x)
{
    for (int i = 2; i <= sqrt(x); i++)
    {
        if (!(x % i))
        {
            return false;
        }
    }
    return true;
}

void Primes::calculatePrimes()
{
    if (findType == false)
    {
        for (int i = 1; i <= findTypeValue; i++)
        {
            if (isSimple(i))
            {
                append(i);
            }
        }
    }
    else
    {
        int addCounter = 0;
        int numberCounter = 1;

        while (addCounter < findTypeValue)
        {
            if (isSimple(numberCounter))
            {
                addCounter++;
            }
            numberCounter++;
        }
    }
}

int Primes::size() const
{
    int s = 0;
    for (Iterator it = begin(); it != end(); it++)
    {
        s++;
    }
    return s;
}
