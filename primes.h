#ifndef PRIMES_H
#define PRIMES_H

#include <cmath>

class Primes
{
private:
    struct Node
    {
        Node() : next(nullptr) {}
        Node(int data) : data(data), next(nullptr) {}

        int data;
        Node* next;
    };

    Node* head = nullptr;
    Node* tail = nullptr;

    bool isRangeSearch;
    int value;
private:
    void append(int value);
    void clear();
public:
    class Iterator
    {
    private:
        Node* node;
    public:
        Iterator(Node* node) {this->node = node;}
        Iterator operator++(int) {Iterator it = *this; node = node->next; return it;}
        int& operator*() {return node->data;}
        bool operator==(const Iterator& it) {return node == it.node;}
        bool operator!=(const Iterator& it) {return node != it.node;}
    };

    Primes(bool isRangeSearch, int value);
    Primes(const Primes& primes);
    Primes(Primes&& primes);

    Primes& operator=(const Primes& primes);
    Primes& operator=(Primes&& primes);

    void calculatePrimes();

    bool isPrime(int x) const;

    Iterator begin() const;
    Iterator end() const;

    int size() const;
    int sizeofNode() const;

    ~Primes();
};

#endif // PRIMES_H
