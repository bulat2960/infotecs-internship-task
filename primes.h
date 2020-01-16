#ifndef PRIMES_H
#define PRIMES_H

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

    int length = 0;
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

    Primes();

    Iterator begin() const;
    Iterator end() const;

    void append(int value);
    void print() const;

    int size() const;
};

#endif // PRIMES_H
