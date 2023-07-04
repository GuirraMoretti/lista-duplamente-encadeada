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

Node* List::get(int i){
    if (i >= m_size || i < 0)
    {
        throw std::out_of_range("Fora da lista");
    }

    Node* aux = m_head->next;
    while (i != 0 )
    {
        aux = aux->next;
        i--;
    }
    return aux;
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

void List::bubbleSort()
{
    if (m_size < 2)
    {
        return;
    }

    bool swapped;

    do
    {
        swapped = false;
        Node* current = m_head->next;

        while (current != m_head->prev)
        {
            if (current->value > current->next->value)
            {
                std::swap(current->value, current->next->value);
                swapped = true;
            }

            current = current->next;
        }
    } while (swapped);
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
    if (m_size < 2)
        return;

    Node* current = m_head->next;
    while (current->next != m_head)
    {
        Node* min = current;
        Node* temp = current->next;
        while (temp != m_head)
        {
            if (temp->value < min->value)
                min = temp;
            temp = temp->next;
        }
        if (min != current)
        {
            int tempValue = current->value;
            current->value = min->value;
            min->value = tempValue;
        }
        current = current->next;
    }
}

//QuickSort
void List::quickSort(){
    quickSortRecursive(m_head->next,m_head->prev);
}

void List::quickSortRecursive(Node* low, Node* high){
    if (low != high && low != m_head && high != m_head && low != high->next){
        Node* pivo = partition(low, high);
        quickSortRecursive(low, pivo->prev);
        quickSortRecursive(pivo->next, high);
    }
}

Node* List::partition(Node* low, Node* high){
    int pivot = high->value;
    Node* aux = low->prev;

    for (Node* j = low; j != high; j = j->next)
    {
        if (j->value <= pivot)
        {
            aux = (aux == nullptr) ? low : aux->next;
            std::swap(aux->value, j->value);
        }
    }

     aux = (aux == nullptr) ? low : aux->next;
    std::swap(aux->value, high->value);

    return aux;
}
//QuickSort

//MergeSort
void List::mergeSort(){
      if (m_size < 2) {
        return;
    }
    
    this->merge(0, this->m_size - 1);
}

void List::merge(int l, int r){
    if (l == r) return;
    int mid = (l+r) / 2;

    merge(l,mid);
    merge(mid+1,r);

    // criar listas l
    List leftHalf;
    List rightHalf;
    
    for(int i = l; i <= mid; i++) {
        leftHalf.push_back(get(i)->value);
    }

    for (int i = mid + 1; i <= r; i++)
    {
        rightHalf.push_back(get(i)->value);
    }

    leftHalf.push_back(INT32_MAX);
    rightHalf.push_back(INT32_MAX);
 
    for (int i = l, i1 = 0, i2 = 0; i <= r; ++ i)
    {
         if(leftHalf.get(i1)->value < rightHalf.get(i2)->value) 
            this->get(i)->value = leftHalf.get(i1 ++)->value;
        else 
            this->get(i)->value = rightHalf.get(i2 ++)->value;
    }
}

void List::shellSort()
{
    int n = m_size;
    int gap = n / 2;

    while (gap > 0)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = get(i)->value;
            int j = i;

            while (j >= gap && get(j - gap)->value > temp)
            {
                get(j)->value = get(j - gap)->value;
                j -= gap;
            }

            get(j)->value = temp;
        }

        gap /= 2;
    }
}

