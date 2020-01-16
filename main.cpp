#include <iostream>
#include "primes.h"
#include <list>

using namespace std;

void print(const Primes& primes)
{
    for (auto it = primes.begin(); it != primes.end(); it++)
    {
        cout << *it << endl;
    }
}

int main(int argc, char** argv)
{
    Primes p;
    p.append(10);
    p.append(20);
    p.append(30);
    p.append(40);

    print(p);

    return 0;
}
