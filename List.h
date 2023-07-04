#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdexcept>

struct Node
{
    int value;
    Node* prev;
    Node* next;

    Node(const int& val, Node* prevPtr, Node* nextPtr)
    {
        value = val;
        prev = prevPtr;
        next = nextPtr;
    }

    ~Node()
    {
        std::cout << "removido: " << value << std::endl;
    }
};

class List
{
private:
    Node* m_head;
    size_t m_size;

public:
    class iterator
    {
    private:
        Node* pointer;

    public:
        iterator()
        {
            pointer = nullptr;
        }

        iterator(const iterator& it)
        {
            pointer = it.pointer;
        }

        iterator(Node* ptr)
        {
            pointer = ptr;
        }

        bool operator!=(const iterator& it)
        {
            return this->pointer != it.pointer;
        }

        bool operator==(const iterator& it)
        {
            return this->pointer == it.pointer;
        }

        int& operator*()
        {
            return pointer->value;
        }

        iterator operator++()
        {
            pointer = pointer->next;
            return *this;
        }

        iterator operator++(int)
        {
            iterator it_old(pointer);
            pointer = pointer->next;
            return it_old;
        }

        iterator operator=(const iterator& it)
        {
            pointer = it.pointer;
            return *this;
        }
    };

    iterator begin();
    iterator end();
    List();
    List(const List& lst);
    void push_back(const int& v);
    void push_front(const int& v);
    void pop_back();
    bool empty() const;
    size_t size() const;
    int& front();
    int& back();
    void pop_front();
    void clear();
    void remove(const int& val);
    
    void bubbleSort();
    void insertionSort();
    void selectionSort();
    //void mergeSort();
    //QuickSort
};

#endif
