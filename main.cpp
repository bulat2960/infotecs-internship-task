#include <iostream>
#include <string>

#include "primes.h"

using namespace std;

struct ParamStorage
{
    bool findType = false; // false - режим "диапазон", true - режим "количество чисел"
    int findTypeValue = 100; // значение для заданного режима
    string filename; // Файл для вывода, по умолчанию не задан
    bool printOption = false; // false - режим печати в строчку, true - режим печати в столбец
    int sequenceType = 0; // 0 - по умолчанию (вывод всех простых чисел), >0 - спец. последовательность

    void setParams(int argc, char** argv)
    {
        for (int i = 1; i < argc; i += 2)
        {
            string param = string(argv[i]);

            if (param == "-t" || param == "--type")
            {
                findType = atoi(argv[i + 1]);
            }
            else if (param == "-n" || param == "--number")
            {
                findTypeValue = atoi(argv[i + 1]);
            }
            else if (param == "-f" || param == "--filename")
            {
                filename = string(argv[i + 1]);
            }
            else if (param== "-o" || param == "-option")
            {
                printOption = atoi(argv[i + 1]);
            }
            else if (param == "-s" || param == "--sequence")
            {
                sequenceType = atoi(argv[i + 1]);
            }
        }
    }

    void printParams()
    {
        cout << "Find type: " << findType << endl;
        cout << "Find type value: " << findTypeValue << endl;
        cout << "Filename: " << filename << endl;
        cout << "Print option: " << printOption << endl;
        cout << "Sequence type: " << sequenceType << endl;
    }
};

void print(const Primes& primes)
{
    for (auto it = primes.begin(); it != primes.end(); it++)
    {
        cout << *it << endl;
    }
}

int main(int argc, char** argv)
{
    ParamStorage storage;
    storage.setParams(argc, argv);
    storage.printParams();

    Primes p;
    p.append(10);
    p.append(20);
    p.append(30);
    p.append(40);

    print(p);

    return 0;
}
