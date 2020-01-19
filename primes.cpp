#include "primes.h"

Primes::Primes(bool isRangeSearch, int value) : isRangeSearch(isRangeSearch), value(value)
{

}

Primes::Primes(const Primes& primes) : isRangeSearch(primes.isRangeSearch), value(primes.value)
{
    for (Iterator it = primes.begin(); it != primes.end(); it++)
    {
        append(*it);
    }
}

Primes& Primes::operator=(const Primes& primes)
{
    clear();
    for (Iterator it = primes.begin(); it != primes.end(); it++)
    {
        append(*it);
    }
    return *this;
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

void Primes::clear()
{
    int s = size();
    for (int i = 0; i < s; i++)
    {
        Node* temp = head->next;
        delete head;
        head = temp;
    }
}

bool Primes::isPrime(int x) const
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
    if (isRangeSearch)
    {
        for (int i = 2; i <= value; i++)
        {
            if (isPrime(i))
            {
                append(i);
            }
        }
    }
    else
    {
        int addCounter = 0;
        int numberCounter = 2;

        while (addCounter < value)
        {
            if (isPrime(numberCounter))
            {
                append(numberCounter);
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

int Primes::sizeofNode() const
{
    return sizeof(Node);
}

Primes::~Primes()
{
    clear();
}
