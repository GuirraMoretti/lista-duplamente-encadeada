#include "list.h"

List::iterator List::begin()
{
    return iterator(m_head->next);
}

List::iterator List::end()
{
    return iterator(m_head);
}

List::List()
{
    m_head = new Node(0, nullptr, nullptr);
    m_head->next = m_head;
    m_head->prev = m_head;
    m_size = 0;
}

List::List(const List& lst)
{
    m_head = new Node(0, nullptr, nullptr);
    m_head->next = m_head;
    m_head->prev = m_head;
    Node* aux = lst.m_head->next;
    Node* auxMain = m_head;
    while (aux != lst.m_head)
    {
        Node* newNode = new Node(aux->value, auxMain, m_head);
        auxMain->next = newNode;
        auxMain = auxMain->next;
        aux = aux->next;
    }
    m_head->prev = auxMain;
    m_size = lst.m_size;
}

void List::push_back(const int& v)
{
    Node* aux = new Node(v, m_head->prev, m_head);
    aux->prev->next = aux;
    m_head->prev = aux;
    m_size++;
}

void List::push_front(const int& v)
{
    Node* aux = new Node(v, m_head, m_head->next);
    m_head->next->prev = aux;
    m_head->next = aux;
    m_size++;
}

void List::pop_back()
{
    if (m_size != 0)
    {
        Node* aux = m_head->prev;
        aux->prev->next = m_head;
        m_head->prev = aux->prev;
        delete aux;
        m_size--;
    }
}

void List::pop_front()
{
    if (m_head->next != m_head)
    {
        Node* aux = m_head->next;
        m_head->next = aux->next;
        aux->next->prev = m_head;
        delete aux;
        m_size--;
    }
    else
    {
        throw std::out_of_range("Lista vazia");
    }
}

bool List::empty() const
{
    return m_size == 0;
}

size_t List::size() const
{
    return m_size;
}

int& List::front()
{
    if (m_head->next != m_head)
    {
        return m_head->next->value;
    }
    else
    {
        throw std::out_of_range("Nao tem elemento na lista");
    }
}

int& List::back()
{
    if (m_head->prev != m_head)
    {
        return m_head->prev->value;
    }
    else
    {
        throw std::out_of_range("Nao existe ultimo elemento");
    }
}


void List::clear()
{
    Node* aux = m_head->next;

    while (aux != m_head)
    {
        Node* nextNode = aux->next;
        delete aux;
        aux = nextNode;
    }

    m_head->next = m_head;
    m_head->prev = m_head;
    m_size = 0;
}

void List::remove(const int& val)
{
    Node* aux = m_head->next;

    while (aux != m_head)
    {
        if (aux->value == val)
        {
            aux->next->prev = aux->prev;
            aux->prev->next = aux->next;
            delete aux;
            aux = aux->prev; // Atualiza o ponteiro aux para o elemento anterior
            m_size--;
        }

        aux = aux->next;
    }
}


void List::bubbleSort(){
    if (m_size < 2)
    {
        return;
    }
    bool swap;

    do
    {
        swap == false;
        Node* current = m_head++;
        while (current++ != m_head)
        {
            if (current->value > current->next->value)
            {
            int aux = current->value;
            current->value = current->next->value;
            current->next->value = aux;
            swap = true;
            }
            current = current++;
        }
    }while (swap);
}

void List::insertionSort()
{
    if (m_size < 2){
        return;
    }

    Node* current = m_head->next->next;
    while (current != m_head)
    {
        int key = current->value;
        Node* before = current->prev;
        while (before != m_head && before->value > key)
        {
            before->next->value = before->value;
            before = before->prev;
        }
        before->next->value = key;
        current = current->next;
    }
}

void List::selectionSort()
{
    if (m_size <= 1)
        return;

    Node* current = m_head++;
    while (current++ != m_head)
    {
        Node* min = current;
        Node* temp = current++;
        while (temp != m_head)
        {
            if (temp->value < min->value)
                min = temp;
            temp = temp++;
        }
        if (min != current)
        {
            int tempValue = current->value;
            current->value = min->value;
            min->value = tempValue;
        }
        current = current++;
    }
}

