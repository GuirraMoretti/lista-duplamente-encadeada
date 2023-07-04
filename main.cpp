#include <iostream>
#include "list.h"

int main()
{
    List myList;
    myList.push_back(3);
    myList.push_back(1);
    myList.push_back(4);
    myList.push_back(2);
    myList.push_back(10);
    myList.push_back(9);

    std::cout << "Lista antes da ordenação: ";
    for (List::iterator it = myList.begin(); it != myList.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << myList.get(3)->value << std::endl;

    myList.shellSort();

    std::cout << "Lista após a ordenação: ";
    for (List::iterator it = myList.begin(); it != myList.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
