#include "primes.h"

Primes::Primes()
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

    length++;
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
